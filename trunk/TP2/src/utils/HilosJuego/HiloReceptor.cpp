#include "HiloReceptor.h"

HiloReceptor::HiloReceptor(void){
	this->detenerActividad();		// El hilo arranca sin actividad
	this->clientesEnConfiguracion.clear();
}

HiloReceptor::~HiloReceptor(void){
	// Cerramos todos los hilos (se hayan terminado de configurar o no) porque su hilo padre está por destruirse. Ver si cierra bien
	int cantidadHilos = this->clientesEnConfiguracion.size();
	for(int i = 0 ; i < cantidadHilos ; i++){
		this->clientesEnConfiguracion[i]->detenerActividad();
		this->cerrarHiloConfiguracion(this->clientesEnConfiguracion[i]->getId());
	}
}

void* HiloReceptor::run(void* parametrosRun){
	HiloConfiguracion::stParametrosConfiguracion* parametros = ((HiloConfiguracion::stParametrosConfiguracion*)parametrosRun);
	this->rutina(parametros);
	return NULL;
}

// Acá activo el hilo y hago el start
void HiloReceptor::correrRecepcion(HiloConfiguracion::stParametrosConfiguracion parametrosRun){
	this->mutexCorriendo.lockEscritura(__FILE__,__LINE__);
	this->corriendo = true;
	this->mutexCorriendo.unlock(__FILE__,__LINE__);
	this->parametrosRun = parametrosRun;
	this->start(&(this->parametrosRun)); 
	return void();
}

void HiloReceptor::rutina(HiloConfiguracion::stParametrosConfiguracion* parametrosEntrada){

	SocketServidor* pServidor = (SocketServidor*)parametrosEntrada->pServidor;
	std::cout << "Aceptando clientes..."  << std::endl;

	// El hilo hará su tarea mientras se encuentre activo
	while(this->estaActivo()==true){		
		long idCliente;
		HiloConfiguracion* pHiloConfig;
		
		// Agrego un Cliente nuevo, y por ende un nuevo HiloConfiguracion. Inmediatamente después, inicio ese hilo
		idCliente = pServidor->aceptarCliente();
		if ( idCliente != ACEPTAR_TIMEOUT && idCliente != ACEPTAR_ERROR ){
			std::cout << "Cliente aceptado."  << std::endl;
			pHiloConfig = new HiloConfiguracion();
			parametrosEntrada->idCliente = idCliente;
			pHiloConfig->correrConfiguracion(*parametrosEntrada);
			this->clientesEnConfiguracion.push_back(pHiloConfig);
		}else{
			if( idCliente == ACEPTAR_ERROR ){
				Log::getInstance().log(1,__FILE__,__LINE__,"[SERVIDOR] Error al acerptar cliente!!!");
				this->detenerActividad();
			}
			if( idCliente == ACEPTAR_TIMEOUT ){
				// Si hubo time out, no pasa nada, vuelvo a probar para ver si alguien quiere conectarse
				// Entro otra vez al while
			}
		}

		// Cierro los hilos que terminaron
		// Acá guardaré los índices del vector de hilos que hayan finalizado
		std::vector<int> idDeHilosParaCerrar;

		// Chequeo el estado de los hilos. Si alguno termino su tarea, guardo su indice en el vector para luego cerrarlo
		for( int i = 0 ; i < this->clientesEnConfiguracion.size() ; i++){
			if( this->clientesEnConfiguracion[i]->estaConfiguracionFinalizada() == true ){
				idDeHilosParaCerrar.push_back(this->clientesEnConfiguracion[i]->getId());
			}
		}

		// A partir de los valores que guarde en el vector de indices, cierro los hilos que terminaron
		for( int i = 0 ; i < idDeHilosParaCerrar.size() ; i++){
			this->cerrarHiloConfiguracion(idDeHilosParaCerrar[i]);
		}

		// Delay de tiempo para que no quede dando vueltas tan rápido.
		Temporizador::getInstance().crearDelay(1000);
	}

	// Cerramos todos los hilos que terminaron de configurarse, justo después del último for, dentro del último ciclo while
	int cantidadHilos = this->clientesEnConfiguracion.size();
	for(int i = 0 ; i < cantidadHilos ; i++){
		if( this->clientesEnConfiguracion[i]->estaConfiguracionFinalizada() == true ){
			this->cerrarHiloConfiguracion(this->clientesEnConfiguracion[i]->getId());
		}
	}

	this->detenerActividad();

	return void();
}

// Cierra y elimina el HiloConfiguracion indicado con <idVectorHiloConfiguracion>
// Nota: Si el hilo existe, entonces necesariamente se inició (con start)
void HiloReceptor::cerrarHiloConfiguracion(int idVectorHiloConfiguracion){

	int indice = -1;

	// Obtengo la posición en la que se encuentra actualmente el ID que estoy buscando
	for( int i = 0 ; i < this->clientesEnConfiguracion.size() ; i++){
		if( this->clientesEnConfiguracion[i]->getId() == idVectorHiloConfiguracion ){
			indice = i;
		}
	}
	if( indice == -1 ) return void(); // Si no encontró ese hilo termino acá mismo

	// Detengo la actividad de el hilo para poder hacer el join
	this->clientesEnConfiguracion[indice]->detenerActividad();

	// Hago el join
	this->clientesEnConfiguracion[indice]->join();

	// Borro el elemento del vector, su instanciación y su puntero en el vector
	delete this->clientesEnConfiguracion[indice];
	this->clientesEnConfiguracion.erase(this->clientesEnConfiguracion.begin()+indice);

	return void();
}

void HiloReceptor::detenerActividad(void){
	this->mutexCorriendo.lockEscritura(__FILE__,__LINE__);
	this->corriendo = false;
	this->mutexCorriendo.unlock(__FILE__,__LINE__);
	return void();
}

bool HiloReceptor::estaActivo(void){
	bool resultado;
	this->mutexCorriendo.lockLectura(__FILE__,__LINE__);
	resultado = this->corriendo;
	this->mutexCorriendo.unlock(__FILE__,__LINE__);
	return resultado;
}
