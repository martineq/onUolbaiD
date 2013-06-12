#include "ModeloItem.h"

using namespace std;

ModeloItem::ModeloItem(const ModeloItem &modeloItem) {	
}

ModeloItem& ModeloItem::operator=(const ModeloItem &modeloItem) {
	return *this;
}

ModeloItem::ModeloItem(int alto, int ancho, int velocidad, Posicion posicion, int altoNivel, int anchoNivel, int fps, ProxyModeloEntidad* proxyEntidad, int id, string nombreEntidad, int tipoEntidad) {
	this->_activo = false;
	this->_modeloEntidad = new ModeloEntidad(alto, ancho, velocidad, posicion, altoNivel, anchoNivel, fps, proxyEntidad, id, nombreEntidad, tipoEntidad);
	this->_jugador = NULL;
	this->_listaJugadores = NULL;
	this->_listaEnemigos = NULL;
	this->_listaGolems = NULL;
}

ModeloItem::~ModeloItem() {
	delete this->_modeloEntidad;
}

bool ModeloItem::disponible() {
	return this->_jugador == NULL;
}

ModeloEntidad* ModeloItem::modeloEntidad() {
	return this->_modeloEntidad;
}

ProxyModeloEntidad::stEntidad ModeloItem::stEntidad() {
	ProxyModeloEntidad::stEntidad estado = this->_modeloEntidad->stEntidad();
	estado.vida = this->vida();
	if ((estado.nombreEntidad == STRING_BOMBA) && (this->_activo)) {
		estado.accion = 1;
		estado.esUltimoMovimiento = false;		
	}
	return estado;
}

void ModeloItem::activar() {
	this->_activo = (this->_jugador != NULL) && (this->_listaJugadores != NULL) && (this->_listaEnemigos != NULL);
}

void ModeloItem::asignarJugador(ModeloJugador* jugador) {
	this->_jugador = jugador;
	this->enviarEstado();
}

void ModeloItem::asignarListaJugadores(ListaJugadores* listaJugadores) {
	this->_listaJugadores = listaJugadores;
}

void ModeloItem::asignarListaEnemigos(ListaJugadores* listaEnemigos) {
	this->_listaEnemigos = listaEnemigos;
}

void ModeloItem::asignarListaGolems(ListaJugadores* listaGolems) {
	this->_listaGolems = listaGolems;
}

void ModeloItem::cambiarEstado() {
	bool estadoAnterior = this->_activo;

	// Si el item esta activo lo aplico y cambio el estado si se termino de aplicar lo desactivo
	if (this->_activo) {
		this->_activo = !this->aplicar(this->_jugador, this->_listaJugadores, this->_listaEnemigos, this->_listaGolems);
		if (!this->_activo)
			this->_jugador->enviarEstado();
	}

	if (this->_activo != estadoAnterior)
		this->enviarEstado();
}

void ModeloItem::enviarEstado() {
	ProxyModeloEntidad::stEntidad estado = this->stEntidad();
	estado.idJugadorDuenio = (this->_jugador == NULL) ? ID_FALSO : this->_jugador->modeloEntidad()->id();
	this->_modeloEntidad->enviarEstado(estado);
}

int ModeloItem::vida() {
	if (this->disponible() || this->_activo)
		return 1;
	else
		return 0;
}

ModeloItem* ModeloItem::crearItem(ModeloDrop::stDatoItem datoItem, ModeloDrop::stDatoGolem datosGolem, Posicion pos, ModeloDrop::stDatosDrop datosDrop){
	ModeloItem* pItem = NULL;

	std::string nombreEntidad = datoItem.nombreEntidad;
	int alto = datoItem.alto;
	int ancho = datoItem.ancho;
	int velocidad = datoItem.velocidad;
	int altoEscenario = datoItem.altoEscenario;
	int anchoEscenario = datoItem.anchoEscenario;
	int fps = datoItem.fps;

	// Creo el proxy y el ID
	ProxyModeloEntidad* pProxyEntidad = new ProxyModeloEntidad();
	pProxyEntidad->setSocketServidor(datoItem.pSocket);

	int nuevoID = Ticket::getInstance().pedirNumero();

	if ( nombreEntidad.compare(STRING_CORAZON) == 0 ){ pItem = new ModeloCorazon(alto,ancho,velocidad,pos,altoEscenario,anchoEscenario,fps,pProxyEntidad,nuevoID,nombreEntidad);
	}else if ( nombreEntidad.compare(STRING_ESCUDO) == 0 ){ pItem = new ModeloEscudo(alto,ancho,velocidad,pos,altoEscenario,anchoEscenario,fps,pProxyEntidad,nuevoID,nombreEntidad);
	}else if ( nombreEntidad.compare(STRING_ZAPATO) == 0 ){ pItem = new ModeloZapato(alto,ancho,velocidad,pos,altoEscenario,anchoEscenario,fps,pProxyEntidad,nuevoID,nombreEntidad);
	}else if ( nombreEntidad.compare(STRING_BOTELLA) == 0 ){ pItem = new ModeloBotella(alto,ancho,velocidad,pos,altoEscenario,anchoEscenario,fps,pProxyEntidad,nuevoID,nombreEntidad);
	}else if ( nombreEntidad.compare(STRING_LAMPARA) == 0 ){ pItem = new ModeloLampara(alto,ancho,velocidad,pos,altoEscenario,anchoEscenario,fps,pProxyEntidad,nuevoID,nombreEntidad);
	}else if ( nombreEntidad.compare(STRING_MAPA) == 0 ){ pItem = new ModeloMapa(alto,ancho,velocidad,pos,altoEscenario,anchoEscenario,fps,pProxyEntidad,nuevoID,nombreEntidad);
	}else if ( nombreEntidad.compare(STRING_ESPADA) == 0 ){ pItem = new ModeloEspada(alto,ancho,velocidad,pos,altoEscenario,anchoEscenario,fps,pProxyEntidad,nuevoID,nombreEntidad);
	}else if ( nombreEntidad.compare(STRING_HECHIZO_HIELO) == 0 ){ pItem = new ModeloHechizoHielo(alto,ancho,velocidad,pos,altoEscenario,anchoEscenario,fps,pProxyEntidad,nuevoID,nombreEntidad);
	}else if ( nombreEntidad.compare(STRING_BOMBA) == 0 ){ pItem = new ModeloBomba(alto,ancho,velocidad,pos,altoEscenario,anchoEscenario,fps,pProxyEntidad,nuevoID,nombreEntidad);
	}else if ( nombreEntidad.compare(STRING_GOLEM) == 0 ){
		pItem = new ModeloGolem(alto,ancho,velocidad,pos,altoEscenario,anchoEscenario,fps,pProxyEntidad,nuevoID,nombreEntidad);
		int altoGolem = datosGolem.altoGolem;
		int anchoGolem = datosGolem.anchoGolem;
		int fpsGolem = datosGolem.fpsGolem;
		int anchoEscenarioGolem = datosGolem.anchoEscenarioGolem;
		int altoEscenarioGolem = datosGolem.altoEscenarioGolem;
		((ModeloGolem*)pItem)->cargarDatos(altoGolem,anchoGolem,fpsGolem,anchoEscenarioGolem,altoEscenarioGolem,datoItem.pSocket,datosDrop);
	}else{  pItem = NULL;}	

	return pItem;
}

ModeloItem* ModeloItem::drop(ModeloDrop::stDatosDrop datos, Posicion pos){
	ModeloItem* pItem = NULL;
	int cantidadItems = datos.listaDatosItems.size();
	if( cantidadItems == 0 ) return NULL;

	// Para que siempre tire items
	int random = rand() % cantidadItems;  // Devuelve:  0, 1, 2... (cantidadItems-1)

	// Para que tenga chances de NO tirar items
	//int random = rand() % cantidadItems+1;  // Devuelve:  0, 1, 2... (cantidadItems)
	//if( random == cantidadItems ) return NULL;

	int i = 0;
	for (std::list<ModeloDrop::stDatoItem>::iterator it=datos.listaDatosItems.begin() ; it != datos.listaDatosItems.end(); it++ ){	
		if( i == random ){
			pItem = ModeloItem::crearItem((*it),datos.datosGolem,pos,datos);
			break;
		}
		i++;
	}

	return pItem;
}
