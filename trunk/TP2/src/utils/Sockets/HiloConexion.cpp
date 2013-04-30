#include "HiloConexion.h"

HiloConexion::HiloConexion(void){
	this->detenerActividad();		// El hilo arranca sin actividad
}

HiloConexion::~HiloConexion(void){

}

void* HiloConexion::run(void* parametrosRun){
	stParametrosRun* parametros = ((stParametrosRun*)parametrosRun);
	this->rutina(parametros);
	return NULL;
}

void HiloConexion::correrConexion(stParametrosRun parametrosRun){
	this->mutexCorriendo.lockEscritura(__FILE__,__LINE__);
	this->corriendo = true;
	this->mutexCorriendo.unlock(__FILE__,__LINE__);
	this->parametrosRun = parametrosRun;
	this->start(&(this->parametrosRun)); 
	return void();
}

void HiloConexion::detenerActividad(void){
	this->mutexCorriendo.lockEscritura(__FILE__,__LINE__);
	this->corriendo = false;
	this->mutexCorriendo.unlock(__FILE__,__LINE__);
}

bool HiloConexion::estaActivo(void){
	this->mutexCorriendo.lockLectura(__FILE__,__LINE__);
	bool estadoCorriendo = this->corriendo;
	this->mutexCorriendo.unlock(__FILE__,__LINE__);
	return estadoCorriendo;
}

void HiloConexion::rutina(HiloConexion::stParametrosRun* parametros){
	char tipoDeCola = parametros->opcion;
	Mutex* pMutexEsIndividual = parametros->pMutexEsIndividual;		
	pMutexEsIndividual->lockLectura(__FILE__,__LINE__);
	bool esIndividual = *(parametros->pEsIndividual);
	pMutexEsIndividual->unlock(__FILE__,__LINE__);

	while(this->estaActivo() == true){
		pMutexEsIndividual->lockLectura(__FILE__,__LINE__);
		esIndividual = *(parametros->pEsIndividual);
		pMutexEsIndividual->unlock(__FILE__,__LINE__);

		if( esIndividual == true ){		// Por ahora si es individual no va a hacer nada ya que se usan el enviarDirecto() y recibirDirecto(), o sea no usan colas
			switch (tipoDeCola){
				case 'E': this->loopEntradaIndividual(parametros);
					break;
				case 'S': this->loopSalidaIndividual(parametros);
					break;
				default: this->delay();
					break;
			}
		}else{
			switch (tipoDeCola){
				case 'E': this->loopEntradaMasivo(parametros);
					break;
				case 'S': this->loopSalidaMasivo(parametros);
					break;
				default: this->delay();
					break;
			}
		}
	}
	return void();
}

void HiloConexion::loopEntradaIndividual(stParametrosRun* parametrosEntrada){
	return this->delay(); // Hago este sleep para que el while no se quede dando vueltas con tanta velocidad
}

void HiloConexion::loopEntradaMasivo(stParametrosRun* parametrosEntrada){
	// Si estos punteros son todos != NULL, quiere decir que este hilo fue iniciado por una instancia de Servidor, eso quiere decir que tengo que usar el pColaMasiva
	bool esColaMasiva = ( (parametrosEntrada->pColaEntradaMasiva != NULL) && (parametrosEntrada->pMutexMasivo != NULL) && (parametrosEntrada->pIdMasivoConError != NULL) );
	
	long idCliente = parametrosEntrada->idCliente;
	SocketApp* pSocket = parametrosEntrada->pSocket;
	std::list<std::string>* pColaEntrada = parametrosEntrada->pCola;
	Mutex* pMutexColaEntrada = parametrosEntrada->pMutexCola;
	
	// Para el caso de hilo desde un servidor
	std::list<std::string>* pColaEntradaMasiva = parametrosEntrada->pColaEntradaMasiva;
	std::list<long>* pIdMasivoConError = parametrosEntrada->pIdMasivoConError;
	Mutex* pMutexMasivo = parametrosEntrada->pMutexMasivo;

	// Elijo el destino de la cola de entrada
	if( esColaMasiva == true ){
		pColaEntrada = pColaEntradaMasiva;
		pMutexColaEntrada = pMutexMasivo;
	}

	char* cadena = NULL;		// Ac� recibo la cadena de caracteres, es instanciada por el recibir()
	unsigned int cantidad;		// Tama�o del mensaje

	// Usa el selectLectura() para no quedar bloqueado por el recibir(). Con esto solo hago recibir() sii el cliente quiere enviarme algo
	bool selectOk = pSocket->selectLectura(DELAY_HILO_CONEXION); 
	while( (this->estaActivo() == true) && (selectOk == false) ){
			selectOk = pSocket->selectLectura(DELAY_HILO_CONEXION);
	} // Este while termina si (this->estaActivo() == false) o si (selectOk == true)

	if ( (this->estaActivo() == true) && (selectOk == true) ){

		bool exito = pSocket->recibir(&cadena,cantidad); // El recibir() hace un new			
		if (exito==true){

			//std::stringstream sstr;
			//sstr<<"Hilo ID: "<< this->getId()<<" Recibo "<<cantidad<<" bytes\n";
			//std::cout<<sstr.str();

			std::string str(cadena,cantidad);
			pMutexColaEntrada->lockEscritura(__FILE__,__LINE__);
			pColaEntrada->push_back(str);
			pMutexColaEntrada->unlock(__FILE__,__LINE__);
			delete[] cadena;  // Borro el new que hizo el recibir
		}else{

			// Ac� entro si se produjo error.
			// Si el hilo es de un cliente masivo, instanciado desde el servidor, reporto el ID del cliente que tuvo el error en la lista de clientes con error
			if ( esColaMasiva = true ){
				pMutexMasivo->lockEscritura(__FILE__,__LINE__);
				pIdMasivoConError->push_back(idCliente);
				pMutexMasivo->unlock(__FILE__,__LINE__);
			}
			
			this->detenerActividad();

		}

	}
	return void();
}

void HiloConexion::loopSalidaIndividual(stParametrosRun* parametrosSalida){
	return this->delay(); // Hago este sleep para que el while no se quede dando vueltas con tanta velocidad
}

void HiloConexion::loopSalidaMasivo(stParametrosRun* parametrosSalida){
	long idCliente = parametrosSalida->idCliente;
	SocketApp* pSocket = parametrosSalida->pSocket;
	std::list<std::string>* pColaSalida = parametrosSalida->pCola;
	Mutex* pMutexColaSalida = parametrosSalida->pMutexCola;

	pMutexColaSalida->lockLectura(__FILE__,__LINE__);
	bool colaVacia = pColaSalida->empty();
	pMutexColaSalida->unlock(__FILE__,__LINE__);

	if( colaVacia == false ){	// Solo trabaja si la cola tiene datos
		pMutexColaSalida->lockLectura(__FILE__,__LINE__);
		std::string str(pColaSalida->front());
		pMutexColaSalida->unlock(__FILE__,__LINE__);

		// Usa el selectEscritura() para no quedar bloqueado por el enviar(). Con esto solo hago enviar() sii el cliente est� dispuesto a recibir lo que le mando
		bool selectOk = pSocket->selectEscritura(DELAY_HILO_CONEXION); // 500000 uSeg = 500 mSeg = 0,5 seg

		// Lo retengo hasta que haya alguna actividad
		while( (this->estaActivo() == true) && (selectOk == false) ){
				selectOk = pSocket->selectEscritura(DELAY_HILO_CONEXION);
		} // Este while termina si (this->estaActivo() == false) o si (selectOk == true)

		if ( (this->estaActivo() == true) && (selectOk == true) ){

			if ( pSocket->enviar(str.c_str(),(unsigned int)str.size())==true){  // NO envio el caracter nulo, ya que al recibir ser� agregado de nuevo
							
				//std::stringstream sstr;
				//sstr<<"Hilo ID: "<< this->getId()<<" Envio "<<str.size()<<" bytes\n";
				//std::cout<<sstr.str();
							
				pMutexColaSalida->lockEscritura(__FILE__,__LINE__);
				pColaSalida->pop_front();
				pMutexColaSalida->unlock(__FILE__,__LINE__);
			}else{
				this->detenerActividad();
			}

		}

	}else{
		// Caso: La cola est� vacia. Se podr�a poner un delay pero se ver�a un
		//       retraso en el caso donde en la proxima vuelta la cola tenga datos
	}

	return void();
}

void HiloConexion::delay(void){
	std::cout << "(esIndividual == true) > Aplico delay de: 1000 milisegundos\n";
	Sleep(1000);
	return void();
}