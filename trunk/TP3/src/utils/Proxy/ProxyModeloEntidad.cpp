#include "ProxyModeloEntidad.h"

using namespace std;

ProxyModeloEntidad::ProxyModeloEntidad(void){
	this->pCliente = NULL;
	this->pServidor = NULL;
}

ProxyModeloEntidad::~ProxyModeloEntidad(void){

}

void ProxyModeloEntidad::setSocketCliente(SocketCliente* pCliente){
	this->pCliente = pCliente;
}

void ProxyModeloEntidad::setSocketServidor(SocketServidor* pServidor){
	this->pServidor = pServidor;
}

// Idem enviarEntidad() pero para enviar a un cliente en particular
// Nota: Este método está creado para ser usado en el hilo de configuración, desde el ModeloFactory.
// El cliente debe estar seteado en Individual para que funcione. 
bool ProxyModeloEntidad::enviarEntidadIndividual(ProxyModeloEntidad::stEntidad entidad,int id){
	Serializadora s;
	this->serializar(s,entidad);
	return this->pServidor->enviarIndividual(s,id);
	//return true;
}

// Idem enviarEntidad() pero para recibir directo
// Nota: Este método está creado para ser usado desde el VistaFactory.
// El cliente debe estar seteado en Individual para que funcione. 
// OJO: Acá se da por supuesto que el cliente se encuentra en modo directo ("EnvioDirecto")
bool ProxyModeloEntidad::recibirEntidadIndividual(ProxyModeloEntidad::stEntidad& entidad){
	
	this->recibirEntidad(entidad);

	if( entidad.errorEnSocket == true){
		return false;
	}else{
		return true;
	}

}	

// Envío la entidad a través del socket
// Devuelve true lo pudo enviar exitosamente. Devuelve false si hubo error al enviar.
// Nota: Después se deberá verificar quien tuvo el error y eliminarlo, en cada loop
bool ProxyModeloEntidad::enviarEntidad(ProxyModeloEntidad::stEntidad entidad){
	Serializadora s;
	this->serializar(s,entidad);
	return this->pServidor->enviarMasivo(s);
}

// Devuelve true si sacó datos de la cola de sockets. Devuelve false la cola estaba vacía
// Para ver si hubo errores al recibir del socket debo ver ProxyModeloEntidad::stEntidad.errorEnSocket, y ver si es true
bool ProxyModeloEntidad::recibirEntidad(ProxyModeloEntidad::stEntidad& entidad){
	// Este método tiene que hacerse cargo de poner en true o false el valor errorEnSocket
	Serializadora s;
	if (this->pCliente->recibir(s)){
		if (s.size() > 0){
			this->hidratar(s,entidad);
		}else{
			entidad.errorEnSocket = false;
			return false;			
		}
	}
	else{
		entidad.errorEnSocket = true;
	}
	return true;
}


void ProxyModeloEntidad::serializar(Serializadora& s,ProxyModeloEntidad::stEntidad& entidad){
	// ModeloEntidad
	s.addInt(entidad.id);
	s.addString(entidad.nombreEntidad);
	s.addBool(entidad.esJugador);
	s.addInt(entidad.posicionX);
	s.addInt(entidad.posicionY);
	s.addDouble(entidad.pixelX);
	s.addDouble(entidad.pixelY);
	s.addBool(entidad.esUltimoMovimiento);

	// ModeloJugador
	s.addString(entidad.nombreJugador);
	s.addInt(entidad.escudo);
	s.addBool(entidad.estaCongelado);
	s.addInt(entidad.magia);
	s.addInt(entidad.vida);
	s.addInt(entidad.rangoVision);
	s.addInt(entidad.idRemitente);
	s.addString(entidad.mensaje);

	s.addInt(entidad.accion);
}

void ProxyModeloEntidad::hidratar(Serializadora& s,ProxyModeloEntidad::stEntidad& entidad){			
	// ModeloEntidad
	entidad.id = s.getInt();
	entidad.nombreEntidad = s.getString();
	entidad.esJugador = s.getBool();
	entidad.posicionX = s.getInt();
	entidad.posicionY = s.getInt();
	entidad.pixelX = s.getDouble();
	entidad.pixelY = s.getDouble();
	entidad.esUltimoMovimiento = s.getBool();

	// ModeloJugador
	entidad.nombreJugador = s.getString();
	entidad.escudo = s.getInt();
	entidad.estaCongelado = s.getBool();
	entidad.magia = s.getInt();
	entidad.vida = s.getInt();
	entidad.rangoVision = s.getInt();
	entidad.idRemitente = s.getInt();
	entidad.mensaje = s.getString();

	entidad.accion = s.getInt();
}

int ProxyModeloEntidad::sizeEntidad(ProxyModeloEntidad::stEntidad entidad){
	int sizeID = TAM_INT;
	int sizeNombre = TAM_INT + entidad.nombreEntidad.size();
	int sizeEntidadCongelada = TAM_BOOL;
	int sizeEsJugador = TAM_BOOL;
	int sizePixelSiguienteX = TAM_DBL;
	int sizePixelSiguienteY = TAM_DBL;
	int sizeDireccion = TAM_INT;
	int sizeUltimoMovimiento = TAM_DBL;
	int sizeTileX = TAM_INT;
	int sizeTileY = TAM_INT;
	int sizeAccion = TAM_INT;
	return (sizeID+sizeNombre+sizeEntidadCongelada+sizeEsJugador+sizePixelSiguienteX+sizePixelSiguienteY+sizeDireccion+sizeUltimoMovimiento+sizeTileX+sizeTileY+sizeAccion);
}

void ProxyModeloEntidad::cargarMatriz(ProxyModeloEntidad::stEntidad& entidad,std::string matriz){
	entidad.actualizacionMapa = matriz;
}

bool ProxyModeloEntidad::enviarMatriz(std::string matrix,int id){
	Serializadora s;
	s.addString(matrix);
	return this->pServidor->enviarIndividual(s,id);
}

bool ProxyModeloEntidad::recibirMatrix(std::string& matrix){
	Serializadora s;
	if (this->pCliente->recibir(s)){
		if (s.size() > 0){
			matrix = s.getString();
		}else{
			return false;			
		}
	}
	else{
		return false;
	}
	return true;

}
