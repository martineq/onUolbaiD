#include "ProxyModeloEntidad.h"

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
	//int tamanio = this->sizeEntidad(entidad);
	//s.addInt(tamanio);
	s.addInt(entidad.id);
	s.addString(entidad.nombreEntidad);
	//s.addBool(entidad.errorEnSocket);
	s.addBool(entidad.entidadCongelada);
	s.addBool(entidad.esJugador);
	s.addDouble(entidad.pixelSiguienteX);
	s.addDouble(entidad.pixelSiguienteY);
	s.addInt(entidad.direccion);
	s.addBool(entidad.esUltimoMovimiento);
	s.addInt(entidad.tileX);
	s.addInt(entidad.tileY);
	s.addInt(entidad.accion);	
}

int ProxyModeloEntidad::sizeEntidad(ProxyModeloEntidad::stEntidad entidad){
	int sizeID = TAM_INT;
	int sizeNombre = TAM_INT + entidad.nombreEntidad.size();
	//int sizeErrorSocket = TAM_BOOL;
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

void ProxyModeloEntidad::hidratar(Serializadora& s,ProxyModeloEntidad::stEntidad& entidad){
	int id = s.getInt();
	std::string nombre = s.getString();
	//bool errorSocket = s.getBool();
	bool congelada = s.getBool();
	bool jugador = s.getBool();
	double x = s.getDouble();
	double y = s.getDouble();
	int dir = s.getInt();
	bool ultimo = s.getBool();
	int tileX = s.getInt();
	int tileY = s.getInt();
	int accion = s.getInt();	
	
	entidad.id = id;
	entidad.nombreEntidad = nombre;
	entidad.errorEnSocket = false;
	entidad.entidadCongelada = congelada;
	entidad.esJugador = jugador;
	entidad.pixelSiguienteX = x;	
	entidad.pixelSiguienteY = y;
	entidad.direccion = dir;
	entidad.esUltimoMovimiento = ultimo;
	entidad.tileX = tileX;
	entidad.tileY = tileY;
	entidad.accion = accion;
}

// Para los que usan el proxy y quieren cargar el struct
void ProxyModeloEntidad::cargarStEntidad(ProxyModeloEntidad::stEntidad& entidad,int id,bool errorEnSocket,bool entidadCongelada,bool esJugador,std::string nombreEntidad,double pixelSiguienteX,double pixelSiguienteY,int direccion,bool esUltimoMovimiento,int tileX,int tileY,int accion){
	entidad.id = id;
	entidad.errorEnSocket = errorEnSocket;
	entidad.entidadCongelada = entidadCongelada;
	entidad.esJugador = esJugador;
	entidad.nombreEntidad = nombreEntidad;
	entidad.pixelSiguienteX = pixelSiguienteX;
	entidad.pixelSiguienteY = pixelSiguienteY;
	entidad.direccion = direccion;
	entidad.esUltimoMovimiento = esUltimoMovimiento;
	entidad.tileX = tileX;
	entidad.tileY = tileY;
	entidad.accion = accion;
}
