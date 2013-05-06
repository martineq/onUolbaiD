#include "HiloConfiguracion.h"

HiloConfiguracion::HiloConfiguracion(void){
	this->detenerActividad();		// El hilo arranca sin actividad
	this->configuracionFinalizada = false;
}

HiloConfiguracion::~HiloConfiguracion(void){

}

void* HiloConfiguracion::run(void* parametrosRun){
	stParametrosConfiguracion* parametros = ((stParametrosConfiguracion*)parametrosRun);
	this->rutina(parametros);
	return NULL;
}

// Acá activo el hilo y hago el start
void HiloConfiguracion::correrConfiguracion(stParametrosConfiguracion parametrosRun){
	this->mutexCorriendo.lockEscritura(__FILE__,__LINE__);
	this->corriendo = true;
	this->mutexCorriendo.unlock(__FILE__,__LINE__);
	this->parametrosRun = parametrosRun;
	this->start(&(this->parametrosRun)); 
	return void();
}

// + Se encarga se enviar y recibir datos y archivos al cliente a través del Servidor, para dejar listo al jugador para entrar al ciclo de juego. Una vez hecha su tarea el hilo finaliza
void HiloConfiguracion::rutina(stParametrosConfiguracion* parametrosConfiguracion){

	int id;
	SocketServidor* pServidor;
	ModeloFactory* pModeloFactory; 
	void* pModeloNivel;

	// Preparo los parámetros a usar
	if( this->estaActivo() == true ){
		id = parametrosConfiguracion->idCliente;
		pServidor = (SocketServidor*)parametrosConfiguracion->pServidor;
		pModeloFactory = parametrosConfiguracion->pModeloFactory; 
		pModeloNivel = parametrosConfiguracion->pModeloNivel;
	}else{
		return void();
	}

	// Corro la configuración del cliente desde el ModeloFactory
	if( this->estaActivo() == true ){
		if( pModeloFactory->rutinaAgregarNuevoCliente(pModeloNivel,pServidor,id) == false ){
				this->finalizarConfiguracion();	
				Log::getInstance().log(1,__FILE__,__LINE__,"Error: No se pudo configurar el cliente. ");
				return void();
			}
	}else{
		this->finalizarConfiguracion();
		return void();
	}

	// Doy por terminada la configuración para avisar que luego se cierre este hilo
	this->finalizarConfiguracion();
	return void();
}

void HiloConfiguracion::detenerActividad(void){
	this->mutexCorriendo.lockEscritura(__FILE__,__LINE__);
	this->corriendo = false;
	this->mutexCorriendo.unlock(__FILE__,__LINE__);
	return void();
}

bool HiloConfiguracion::estaActivo(void){
	bool resultado;
	this->mutexCorriendo.lockLectura(__FILE__,__LINE__);
	resultado = this->corriendo;
	this->mutexCorriendo.unlock(__FILE__,__LINE__);
	return resultado;
}

void HiloConfiguracion::finalizarConfiguracion(void){
	this->mutexConfiguracionFinalizada.lockEscritura(__FILE__,__LINE__);
	this->configuracionFinalizada = true;
	this->mutexConfiguracionFinalizada.unlock(__FILE__,__LINE__);
	return void();
}

bool HiloConfiguracion::estaConfiguracionFinalizada(void){
	bool resultado;
	this->mutexConfiguracionFinalizada.lockLectura(__FILE__,__LINE__);
	resultado = this->configuracionFinalizada;
	this->mutexConfiguracionFinalizada.unlock(__FILE__,__LINE__);
	return resultado;
}
