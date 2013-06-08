#include "ModeloItem.h"

ModeloGolem::ModeloGolem(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, std::string nombreEntidad)
	: ModeloItem(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad, TIPO_ITEM_GOLEM) {

}

ModeloGolem::~ModeloGolem() {

}

bool ModeloGolem::aplicar(ModeloJugador* jugador, ListaJugadores* listaJugadores, ListaJugadores* listaEnemigos, ListaJugadores* listaGolems) {
	
	// Cargo los datos que necesito del jugador que invoca el golem
	this->idDuenio = jugador->modeloEntidad()->id();
	this->velocidad =  jugador->modeloEntidad()->velocidad();
	this->danio = (jugador->danioAtaque() / 2);			// El golem tendrá menos daño de ataque que su creador
	this->vida= (jugador->vida() / 2);
	this->pos = jugador->posicionGolem();
	
	ModeloJugador* golem = this->crearGolem();
	listaGolems->agregarJugador(golem);
	jugador->asignarGolem(golem);
	golem->consumirVida(this->vida);
	
	return true;
}

// Lo usa el ModeloFactory para cargar los datos necesarios para la creación del golem
void ModeloGolem::cargarDatos(int idGolem, int alto, int ancho, int fps, int anchoEscenario, int altoEscenario, void* pSocketServidor){

	this->idGolem = idGolem;
	this->alto = alto;
	this->ancho = ancho;
	this->fps = fps;
	this->anchoEscenario = anchoEscenario;
	this->altoEscenario = altoEscenario;
	this->pSocketServidor = pSocketServidor;
	this->nombreEntidad.assign(ENTIDAD_GOLEM);
	this->mana = 0;

	return void();
}

ModeloJugador* ModeloGolem::crearGolem(){

	// Creo el proxy para este enemigo
	ProxyModeloEntidad* pProxyEntidad = new ProxyModeloEntidad();
	pProxyEntidad->setSocketServidor(pSocketServidor);

	// Creo el enemigo (es un ModeloJugador) y lo agrego al nivel
	ModeloJugador* pGolem = new ModeloJugador(alto,ancho,velocidad,pos,altoEscenario,anchoEscenario,fps,pProxyEntidad,idGolem,nombreEntidad,"",this->vida,mana,danio,idDuenio,TIPO_ENTIDAD_GOLEM,true);

	return pGolem;
}
