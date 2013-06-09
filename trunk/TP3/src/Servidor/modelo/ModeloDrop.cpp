#include "ModeloDrop.h"

ModeloDrop::ModeloDrop(ModeloDrop::stDatosDrop datos){
	this->datos = datos;
}

ModeloDrop::~ModeloDrop(void){

}

ModeloItem* ModeloDrop::drop(Posicion pos){
	ModeloItem* pItem = NULL;
	int cantidadItems = this->datos.listaDatosItems.size();
	if( cantidadItems = 0 ) return NULL;

	int random = rand() % cantidadItems;  // Devuelve:  0, 1, 2... (cantidadItems-1)

	int i = 0;
	for (std::list<ModeloDrop::stDatoItem>::iterator it=this->datos.listaDatosItems.begin() ; it != this->datos.listaDatosItems.end(); it++ ){	
		if( i = random ){
			pItem = this->crearItem((*it),pos);
			break;
		}
		i++;
	}

	return pItem;
}

ModeloItem* ModeloDrop::crearItem(ModeloDrop::stDatoItem datoItem, Posicion pos){
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
		int nuevoIDGolem = Ticket::getInstance().pedirNumero();
		int altoGolem = datos.datosGolem.altoGolem;
		int anchoGolem = datos.datosGolem.anchoGolem;
		int fpsGolem = datos.datosGolem.fpsGolem;
		int anchoEscenarioGolem = datos.datosGolem.anchoEscenarioGolem;
		int altoEscenarioGolem = datos.datosGolem.altoEscenarioGolem;
		((ModeloGolem*)pItem)->cargarDatos(nuevoIDGolem,altoGolem,anchoGolem,fpsGolem,anchoEscenarioGolem,altoEscenarioGolem,datoItem.pSocket);
	}else{  pItem = NULL;}	


	return pItem;
}
