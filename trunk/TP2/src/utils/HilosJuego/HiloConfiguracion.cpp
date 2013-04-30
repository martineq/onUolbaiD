#include "HiloConfiguracion.h"

HiloConfiguracion::HiloConfiguracion(void){
	this->detenerActividad();		// El hilo arranca sin actividad
	this->configuracionFinalizada = false;
	this->idCliente = -1;
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
/*
	Log::getInstance().log(1,__FILE__,__LINE__,"[SERVIDOR] Iniciando hilo de configuración para cliente : ", this->idCliente);
	this->iniciarActividad();
	// El hilo hará su tarea mientras se encuentre activo
	while(this->estaActivo()==true){

		// + El Servidor envia todos los archivos necesarios
		if( !this->enviarArchivosDeConfiguracion()){
			this->finalizarConfiguracion();
			return NULL;
		}

		Log::getInstance().log(1,__FILE__,__LINE__,"[SERVIDOR] Todos los archivos fueron enviados");

		string nivel = this->pMenu->obtenerDatosDeConexion().nivelServidor.c_str();
		Serializadora serializado;
		serializado.addString(nivel);
		std::string* source = serializado.getSerializacion();
		Log::getInstance().log(1,__FILE__,__LINE__,"[SERVIDOR] Enviamos nivel del juego", nivel);
		if (this->pServidor->enviarIndividual(source->c_str(),source->size(),this->idCliente) == false){
			this->finalizarConfiguracion();
			delete source;
			return NULL;
		} else {
			delete source;
		}

		bool eleccionFinalizada = false;
		while( eleccionFinalizada == false && this->estaActivo()){

			// recibimos el personaje elegido
			Log::getInstance().log(3,__FILE__,__LINE__,"[SERVIDOR] Esperamos eleccion de personaje por parte del cliente :");
			char* nombreElegido;
			std::string cadena;
			int longitud = 30;
			if ( !this->pServidor->recibirIndividual(&nombreElegido, longitud, this->idCliente) )  {
				this->finalizarConfiguracion(); //this->detenerActividad(); // Pincha de este lado con lo del blitsurface del cliente. Cuando estaba el detenerActividad
				Log::getInstance().log(3,__FILE__,__LINE__,"[SERVIDOR] No pudimos recibir el protagonista elegido y nos vamos");
				return NULL;
			}

			cadena.assign(nombreElegido,longitud);
			delete[] nombreElegido;

			Log::getInstance().log(3,__FILE__,__LINE__,"[SERVIDOR] Recibio personaje eligido :", cadena);

			//std::string** serializado = NULL;			
			std::string* serializado = NULL;			
			if (this->pJuego->agregarProtagonista(this->idCliente,cadena, &serializado)) {
				Log::getInstance().log(1,__FILE__,__LINE__,"[SERVIDOR] Personaje esta diponible :", cadena);
				eleccionFinalizada = true;
				this->detenerActividad();
			} else {
				Log::getInstance().log(1,__FILE__,__LINE__,"[SERVIDOR] Personaje no esta disponible :", cadena);
			}
			// envio de todos modos lo serializado, el true o false de la eleccion.
			Log::getInstance().log(1,__FILE__,__LINE__,"[SERVIDOR] Enviamos serializacion de personaje :", (*serializado));
			if (!this->pServidor->enviarIndividual((*serializado).c_str(),(*serializado).length(),this->idCliente)) {
				this->finalizarConfiguracion();
				Log::getInstance().log(1,__FILE__,__LINE__,"[SERVIDOR] Fallo el envio del personaje serializado :", (*serializado));
				if( serializado != NULL) delete serializado;
				return NULL;
			}
			// Borro lo que ya envie serializado
			if( serializado != NULL) delete serializado;
			SDL_Delay(1000);
		}

		//Verificar si el nivel ya tiene al protagonista. 
		this->pJuego->enviarEstadosIniciales(this->idCliente);
		this->pServidor->setClienteMasivo(this->idCliente);
		this->pMutexCantidadJugadores->lockEscritura(__FILE__,__LINE__);
		(*this->pCantidadJugadores) = (*this->pCantidadJugadores) + 1;
		this->pMutexCantidadJugadores->unlock(__FILE__,__LINE__);

	} // Fin while(this->estaActivo()==true)
	Log::getInstance().log(1,__FILE__,__LINE__,"[SERVIDOR] Termina hilo de configuración para cliente : ", this->idCliente);
	this->finalizarConfiguracion();
	this->detenerActividad();
	Log::getInstance().log(1,__FILE__,__LINE__,"[SERVIDOR] Estado Actividad de configuración para cliente : ", this->estaConfiguracionFinalizada());

*/
	return void();
}

// Envia al cliente todos los archivos necesarios para el funcionamiento del juego
bool HiloConfiguracion::enviarArchivosDeConfiguracion(void){
	bool retorno = true;
	LectorDirectorios lector;	// Para obtener todos los nombres de los archivos
	std::vector<std::string> listaArchivos;

	// Envio los archivos de configuracion
	Log::getInstance().log(1,__FILE__,__LINE__,"[SERVIDOR] enviando archivos de imagenes");
	
	listaArchivos = lector.leerDirectorio(DIRECTORIO_IMG);
	if( !this->enviarListaDeArchivos(listaArchivos)) {
		Log::getInstance().log(1,__FILE__,__LINE__,"[SERVIDOR] No pudo enviar todos los archivos de imagenes");
		retorno = false;
	}
	
	// Envio los archivos de imagenes
	Log::getInstance().log(1,__FILE__,__LINE__,"[SERVIDOR] enviando archivos para la configuracion");
	listaArchivos = lector.leerDirectorio(DIRECTORIO_CONFIG);
	if( this->enviarListaDeArchivos(listaArchivos) == false)  {
		Log::getInstance().log(1,__FILE__,__LINE__,"[SERVIDOR] No pudo enviar todos los archivos de configuracion");
		retorno = false;
	}

	return retorno;
}

bool HiloConfiguracion::enviarListaDeArchivos(std::vector<std::string> vector){
// TODO: Implementar
/*
	// Lista con todos las rutas de los archivos que voy a enviar
	std::list<std::string> rutaDeArchivosParaEnviar;

	// Serializo el vector de strings
	Serializadora s;
	int cantidadDeArchivos = (int)vector.size();
	s.addInt(cantidadDeArchivos);
	for ( int i=0 ; i < cantidadDeArchivos ; i++ ){
		s.addString(vector[i]);								// Los agrego al serializado
		rutaDeArchivosParaEnviar.push_back(vector[i]);		// Los agrego a la lista de archivos
	}

	// Envio el vector de strings serializado en una cadena de chars
	std::string* pStr = s.getSerializacion();
	if( this->pServidor->enviarIndividual(pStr->c_str(),pStr->size(),this->idCliente) == false ){
		delete pStr;
		return false;
	}else{
		delete pStr;
	}

	// Envio todos los archivos 
	this->pServidor->enviarArchivosIndividual(rutaDeArchivosParaEnviar,this->idCliente);
*/
	return true;
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
