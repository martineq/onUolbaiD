#include "ProxyEntidad.h"

ProxyEntidad::ProxyEntidad()
{
}


ProxyEntidad::ProxyEntidad(ModeloEntidad* entidad){
	this->tipoProxy = PROXY_ENTIDAD;	
	this->id = entidad->id();
	this->nombre = "PROTAGONISTA"; //Acá tendría que tener el nombre de la entidad, por ej "agua"
	this->x = entidad->pixelActual().x;
	this->y = entidad->pixelActual().y;
	this->tileX = entidad->posicionActual().x;
	this->tileY = entidad->posicionActual().y;
	this->esJugador = true; //Tendría que tener el modelo si corresponde o no a jugador
	this->codigoDireccion = entidad->direccion();
	this->codigoAccion = entidad->accion();
}

string* ProxyEntidad::serialize(){
	string* retorno;
	Serializadora * serializadora = new Serializadora();
	serializadora->addString(this->tipoProxy);
	serializadora->addInt(this->id);
	serializadora->addString(this->nombre);
	serializadora->addDouble(this->x);
	serializadora->addDouble(this->y);
	serializadora->addInt(this->tileX);
	serializadora->addInt(this->tileY);
	serializadora->addBool(this->esJugador);
	serializadora->addInt(this->codigoDireccion);
	serializadora->addInt(this->codigoAccion);	
	retorno = serializadora->getSerializacion();
	this->actualizado = false;
	delete serializadora;
	return retorno;
	
}

bool ProxyEntidad::hydrate(string* source){
	Serializadora * serializadora = new Serializadora(source);
	string tipo = serializadora->getString();
	int id = serializadora->getInt();
	if ((this->tipoProxy == tipo) && (this->id) == (id)){
		this->nombre = serializadora->getString();
		this->x = serializadora->getDouble();
		this->y = serializadora->getDouble();
		this->tileX = serializadora->getInt();
		this->tileY = serializadora->getInt();
		this->esJugador = serializadora->getBool();
		this->codigoDireccion = serializadora->getInt();
		this->codigoAccion = serializadora->getInt();
		delete serializadora;
		return true;
	}
	delete serializadora;
	return false;
}


void ProxyEntidad::actualizar(Observable* s){
	//this->setPosicionAnteriorEnTiles();
	this->x = ((ModeloEntidad*)s)->pixelSiguiente().x;
	this->y = ((ModeloEntidad*)s)->pixelSiguiente().y;
	this->tileX = ((ModeloEntidad*)s)->posicionSiguiente().x;
	this->tileY = ((ModeloEntidad*)s)->posicionSiguiente().y;	
	this->codigoDireccion = ((ModeloEntidad*)s)->direccion();
	this->codigoAccion = ((ModeloEntidad*)s)->accion();
	this->actualizado = true;
}

ProxyEntidad::~ProxyEntidad(void)
{
}
