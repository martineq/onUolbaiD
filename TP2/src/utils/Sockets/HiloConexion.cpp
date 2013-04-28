#include "HiloConexion.h"

HiloConexion::HiloConexion(void){
	this->mutexCorriendo.lockEscritura(__FILE__,__LINE__);
	this->corriendo = false;	// El hilo arranca sin actividad
	this->mutexCorriendo.unlock(__FILE__,__LINE__);
}

HiloConexion::~HiloConexion(void){

}


void* HiloConexion::run(void* parametrosRun){
	
	stParametrosRun* parametros = ((stParametrosRun*)parametrosRun);
	this->rutina(parametros);

	return NULL;
}

void HiloConexion::correrConexion(stParametrosRun parametros){
	this->mutexCorriendo.lockEscritura(__FILE__,__LINE__);
	this->corriendo = true;
	this->mutexCorriendo.unlock(__FILE__,__LINE__);
	this->parametros = parametros;
	this->start(&(this->parametros)); 
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

void HiloConexion::rutina(stParametrosRun* parametros){

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

	char* cadena = NULL;
	unsigned int cantidad;
				
	// Usa el selectLectura() para no quedar bloqueado por el recibir(). Con esto solo hago recibir() sii el cliente quiere enviarme algo
	bool selectOk = pSocket->selectLectura(DELAY_HILO_CONEXION); 
	while( (this->estaActivo() == true) && (selectOk == false) ){
			selectOk = pSocket->selectLectura(DELAY_HILO_CONEXION);
	} // Este while termina si (this->estaActivo() == false) o si (selectOk == true)

	if ( (this->estaActivo() == true) && (selectOk == true) ){

		bool exito = pSocket->recibir(&cadena,cantidad); // el recibir() hace un new			
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

			// Acá entro si se produjo error.
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

	if( colaVacia == false ){ // Solo trabaja si la cola tiene datos
		pMutexColaSalida->lockLectura(__FILE__,__LINE__);
		std::string str(pColaSalida->front());
		pMutexColaSalida->unlock(__FILE__,__LINE__);

		// Usa el selectEscritura() para no quedar bloqueado por el enviar(). Con esto solo hago enviar() sii el cliente recibir lo que le mando
		bool selectOk = pSocket->selectEscritura(DELAY_HILO_CONEXION); // 500000 uSeg = 500 mSeg = 0,5 seg

		// Lo retengo hasta que haya alguna actividad
		while( (this->estaActivo() == true) && (selectOk == false) ){
				selectOk = pSocket->selectEscritura(DELAY_HILO_CONEXION);
		} // Este while termina si (this->estaActivo() == false) o si (selectOk == true)

		if ( (this->estaActivo() == true) && (selectOk == true) ){

			if ( pSocket->enviar(str.c_str(),(unsigned int)str.size())==true){  // NO envio el caracter nulo, ya que al recibir será agregado de nuevo
							
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

	}

	return void();
}

void HiloConexion::delay(void){
	std::cout << "(esIndividual == true) > Aplico delay de: 1000 milisegundos\n";
	Sleep(1000);
	return void();
}

//void* HiloConexion::run(void* parametro){
//	
//	stParametrosRun* param = ((stParametrosRun*)parametro);
//	char op = param->opcion;
//	std::list<std::string> * cola = param->pCola;
//	Mutex* mutexColaEntrada = param->pMutexCola;   // Creo esta variable en caso de usarse la cola masiva
//
//	// Chequeo si es Masivo, y si lo es, asigno la cola masiva con su mutex (Sólo va a suceder en el Servidor)
//	param->pMutexCola->lockLectura(__FILE__,__LINE__);
//	bool esIndividual = *(param->pEsIndividual);
//	param->pMutexCola->unlock(__FILE__,__LINE__);
//
//	if ( op == 'E'){		// Caso cola de (E)ntrada
//	
//		// Linea de prueba para un hilo del lado del cliente y servidor
//		if ( this->estaActivo() == false) std::cout<<" HILO ACTIVO FALSE!!!\n";
//		
//		while(this->estaActivo() == true){
//
//			if ( esIndividual == true ){ 
//				std::cout << "(esIndividual == true) > Aplico delay de: 500 milisegundos\n";
//				Sleep(500);
//			}
//
//			if ( esIndividual == false ){
//				
//				// TODO: Cambiar esto y preguntar por si es cliente o servidor, así no uso el mutex masivo
//				if ( param->pColaEntradaMasiva != NULL ){
//					cola = param->pColaEntradaMasiva;	
//				}
//				// TODO: Cambiar esto y preguntar por si es cliente o servidor, así no uso el mutex masivo
//				if ( param->pMutexMasivo != NULL ){
//
//					mutexColaEntrada = param->pMutexMasivo;
//				}
//				
//			}
//
//			if ( esIndividual == false ){	// Solo trabajará si es masivo, ya que el individual se hace directamente
//
//				char* cadena = NULL;
//				unsigned int cantidad;
//				
//				// Usa el selectLectura() para no quedar bloqueado por el recibir(). Con esto solo hago recibir() sii el cliente quiere enviarme algo
//				bool selectOk = param->pSocket->selectLectura(DELAY_HILO_CONEXION); // 500000 uSeg = 500 mSeg = 0,5 seg
//				while( (this->estaActivo() == true) && (selectOk == false) ){
//						selectOk = param->pSocket->selectLectura(DELAY_HILO_CONEXION);
//				} // Este while termina si (this->estaActivo() == false) o si (selectOk == true)
//
//				if ( (this->estaActivo() == true) && (selectOk == true) ){
//				
//					bool exito = param->pSocket->recibir(&cadena,cantidad); // el recibir() hace un new			
//					if (exito==true){
//						
//						//std::stringstream sstr;
//						//sstr<<"Hilo ID: "<< this->getId()<<" Recibo "<<cantidad<<" bytes\n";
//						//std::cout<<sstr.str();
//
//						std::string str(cadena,cantidad);
//						mutexColaEntrada->lockEscritura(__FILE__,__LINE__);
//						cola->push_back(str);
//						mutexColaEntrada->unlock(__FILE__,__LINE__);
//						delete[] cadena;  // Borro el new que hizo el recibir
//					}else{
//						
//						// Si el hilo es de un cliente masivo, reporto el ID del cliente que tuvo el error en la lista de clientes con error
//						if ( esIndividual == false && ( param->pIdMasivoConError != NULL ) ){
//							std::list<long>* clientesConError = param->pIdMasivoConError;
//							if( clientesConError != NULL ){
//								long id = param->idCliente;
//								mutexColaEntrada->lockEscritura(__FILE__,__LINE__);
//								clientesConError->push_back(id);
//								mutexColaEntrada->unlock(__FILE__,__LINE__);
//							}
//						}
//						
//						this->detenerActividad();
//					}// Fin if (exito==true){
//				}// Fin if ( (this->estaActivo() == true) && (selectOk == true) ){
//			}	// Fin if ( esIndividual == false )
//
//			// Antes de terminar el while, en cada ciclo, chequeo si es Masivo
//			param->pMutexEsIndividual->lockLectura(__FILE__,__LINE__);
//			esIndividual = *(param->pEsIndividual);
//			param->pMutexEsIndividual->unlock(__FILE__,__LINE__);
//
//		}	// Fin while(this->estaActivo() == true)
//
//	}else if( op == 'S'){	// Caso cola de (S)alida
//
//		while(this->estaActivo() == true){
//
//			if ( esIndividual == true ){ 
//				std::cout << "(esIndividual == true) > Aplico delay de: 500 milisegundos\n";
//				Sleep(500);
//			}
//
//			if ( esIndividual == false ){	// Solo trabajará si es masivo, ya que el individual se hace directamente
//
//				param->pMutexCola->lockLectura(__FILE__,__LINE__);
//				bool colaVacia = cola->empty();
//				param->pMutexCola->unlock(__FILE__,__LINE__);
//
//				if(colaVacia==false){ // Solo trabaja si la cola tiene datos
//					param->pMutexCola->lockLectura(__FILE__,__LINE__);
//					std::string str(cola->front());
//					param->pMutexCola->unlock(__FILE__,__LINE__);
//
//					// Usa el selectEscritura() para no quedar bloqueado por el enviar(). Con esto solo hago enviar() sii el cliente recibir lo que le mando
//					bool selectOk = param->pSocket->selectEscritura(DELAY_HILO_CONEXION); // 500000 uSeg = 500 mSeg = 0,5 seg
//					while( (this->estaActivo() == true) && (selectOk == false) ){
//							selectOk = param->pSocket->selectEscritura(DELAY_HILO_CONEXION);
//					} // Este while termina si (this->estaActivo() == false) o si (selectOk == true)
//
//					if ( (this->estaActivo() == true) && (selectOk == true) ){
//
//						if ( param->pSocket->enviar(str.c_str(),(unsigned int)str.size())==true){  // NO envio el caracter nulo, ya que al recibir será agregado de nuevo
//							
//							//std::stringstream sstr;
//							//sstr<<"Hilo ID: "<< this->getId()<<" Envio "<<str.size()<<" bytes\n";
//							//std::cout<<sstr.str();
//							
//							param->pMutexCola->lockEscritura(__FILE__,__LINE__);
//							cola->pop_front();
//							param->pMutexCola->unlock(__FILE__,__LINE__);
//						}else{
//							this->detenerActividad();
//						}
//
//					}// Fin if ( (this->estaActivo() == true) && (selectOk == true) ){
//				} // Fin if(colaVacia==false){
//
//			}// Fin if ( esIndividual == false )
//
//			// Antes de terminar el while, en cada ciclo, chequeo si es Masivo
//			if (this->estaActivo() == true){ 
//				param->pMutexCola->lockLectura(__FILE__,__LINE__);
//				esIndividual = *(param->pEsIndividual);
//				param->pMutexCola->unlock(__FILE__,__LINE__);
//			}
//
//		} // Fin while(this->estaActivo() == true)
//
//	} // Fin else if( op == 'S')
//
//	//std::cout << "Fin HILO " << op<<std::endl;
//	return NULL;
//}
