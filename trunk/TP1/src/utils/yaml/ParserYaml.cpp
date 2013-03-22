#include "ParserYaml.h"

ParserYaml::ParserYaml(void){

	// Inicialo this->juego
	this->juego.juegoValido = true;
	this->juego.pantalla.alto = YAML_ERROR_INT;
	this->juego.pantalla.ancho = YAML_ERROR_INT;
	this->juego.configuracion.margenScroll = YAML_ERROR_INT;
	this->juego.configuracion.velocidadPersonaje = YAML_ERROR_INT;
	this->juego.entidades.clear();
	this->juego.escenarios.clear();

}

ParserYaml::~ParserYaml(void){

}

ParserYaml::stJuego ParserYaml::cargarConfiguracionDeJuego(void){

	std::ifstream archivo(YAML_RUTA_ARCHIVO_JUEGO);
	Log::getInstance().log(1,__FILE__,__LINE__,"Configuración de juego iniciada");

	// Si pude abrir el archivo yaml, empiezo a parsear
	if(archivo.good()==true){
		try{
			YAML::Parser parser(archivo);				// Archivo YAML
			YAML::Node nodoRaiz;						// Nodo raiz del documento Yaml
			parser.GetNextDocument(nodoRaiz);			// Obtengo el nodo
			this->cargaStJuego(nodoRaiz,this->juego);	// Comienzo con la carga del juego
		}catch(YAML::Exception& e){
			this->notificarErrorLectura(YAML_TIPO_STRING,__FILE__,__LINE__,e.what(),this->juego.juegoValido);
		}
		// TODO: Acá va el this->validar(...);  que seteará <this->juego.juegoValido> en true o false seún sea el caso
		Log::getInstance().log(1,__FILE__,__LINE__,"Configuración de juego finalizada");
	}else{
		// Si no pude abrir el archivo lo reporto
		this->juego.juegoValido = false;
		Log::getInstance().log(1,__FILE__,__LINE__,(std::string)"Error al abrir el archivo YAML: "+YAML_RUTA_ARCHIVO_JUEGO);
	}

	return this->juego;
}

void ParserYaml::cargaStJuego(YAML::Node& nodoRaiz, ParserYaml::stJuego& juego){

	// Itero por todos los nodos que tenga el documento, acá hago proceso necesario para obtener los datos
	for(YAML::Iterator it=nodoRaiz.begin();it!=nodoRaiz.end();++it){
		std::string clave;
		clave = this->leerNodoYamlString(it.first());
		const YAML::Node& nodo = it.second();

		if ( clave.compare("pantalla") == 0 ){ cargaStPantalla(nodo,juego.pantalla);
		}else if ( clave.compare("configuracion") == 0 ){ cargaStConfiguracion(nodo,juego.configuracion);
		}else if ( clave.compare("entidades") == 0 ){ cargaListaEntidades(nodo,juego.entidades);
		}else if ( clave.compare("escenarios") == 0 ){ cargaListaEscenarios(nodo,juego.escenarios);
		}else{Log::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");}

		// TODO: Una vez finalizada la clase, borrar esta todas estas líneas de reporte
		Log::getInstance().log(3,__FILE__,__LINE__,"Clave <"+clave+"> Leída.");
	}

	return void();
}

void ParserYaml::cargaStPantalla(const YAML::Node& nodo, stPantalla& pantalla){

	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it){
		std::string clave;
		clave = this->leerNodoYamlString(it.first());
		if ( clave.compare("alto") == 0 ){ pantalla.alto = this->leerNodoYamlInt(it.second());
		}else if ( clave.compare("ancho") == 0 ){ pantalla.ancho = this->leerNodoYamlInt(it.second());
		}else{Log::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");}

		Log::getInstance().log(3,__FILE__,__LINE__,"Clave <"+clave+"> Leída.");
	}

	return void();
}

void ParserYaml::cargaStConfiguracion(const YAML::Node& nodo, ParserYaml::stConfiguracion& configuracion){
	
	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it){
		std::string clave;
		clave = this->leerNodoYamlString(it.first());
		if ( clave.compare("vel_personaje") == 0 ){ configuracion.velocidadPersonaje = this->leerNodoYamlInt(it.second());
		}else if ( clave.compare("margen_scroll") == 0 ){ configuracion.margenScroll = this->leerNodoYamlInt(it.second());
		}else{Log::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");}

		Log::getInstance().log(3,__FILE__,__LINE__,"Clave <"+clave+"> Leída.");
	}

	return void();
}

void ParserYaml::cargaListaEntidades(const YAML::Node& nodo, std::list <ParserYaml::stEntidad>& entidades){

	for(unsigned i=0;i<nodo.size();i++) { //El nodo es una lista, itero en esa lista
		stEntidad entidad;
		this->cargaStEntidad(nodo[i],entidad);
		entidades.push_back(entidad);
	}

	return void();
}

void ParserYaml::cargaStEntidad(const YAML::Node& nodo, ParserYaml::stEntidad& entidad){

	this->cargaDefaultStEntidad(entidad); // Cargo todos los valores por default, ya que son opcionales

	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it) {	
		std::string clave = this->leerNodoYamlString(it.first());
		if ( clave.compare("nombre") == 0 ){ entidad.nombre = this->leerNodoYamlString(it.second());
		}else if ( clave.compare("imagen") == 0 ){ entidad.imagen = this->leerNodoYamlString(it.second());
		}else if ( clave.compare("ancho_base") == 0 ){ entidad.anchoBase = this->leerNodoYamlInt(it.second());
		}else if ( clave.compare("alto_base") == 0 ){ entidad.altoBase = this->leerNodoYamlInt(it.second());
		}else if ( clave.compare("pixel_ref_x") == 0 ){ entidad.pixelReferenciaX = this->leerNodoYamlInt(it.second());
		}else if ( clave.compare("pixel_ref_y") == 0 ){ entidad.pixelReferenciaY = this->leerNodoYamlInt(it.second());
		}else if ( clave.compare("fps") == 0 ){ entidad.fps = this->leerNodoYamlInt(it.second());
		}else if ( clave.compare("delay") == 0 ){ entidad.delay = this->leerNodoYamlInt(it.second());
		}else{Log::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");}	

		Log::getInstance().log(3,__FILE__,__LINE__,"Clave <"+clave+"> Leída.");
	}

	return void();
}

void ParserYaml::cargaDefaultStEntidad(ParserYaml::stEntidad& entidad){
	entidad.nombre = YAML_DEAFAULT_NOMBRE;
	entidad.imagen = YAML_DEAFAULT_RUTA_IMAGEN;
	entidad.anchoBase = YAML_DEAFAULT_ANCHO_BASE;
	entidad.altoBase = YAML_DEAFAULT_ALTO_BASE;
	entidad.pixelReferenciaX = YAML_DEAFAULT_PIXEL_REF_X;
	entidad.pixelReferenciaY = YAML_DEAFAULT_PIXEL_REF_Y;
	entidad.fps = YAML_DEAFAULT_FPS;
	entidad.delay = YAML_DEAFAULT_DELAY;
}

void ParserYaml::cargaListaEscenarios(const YAML::Node& nodo, std::list <ParserYaml::stEscenario>& escenarios){

	for(unsigned i=0;i<nodo.size();i++) { //El nodo es una lista, itero en esa lista
		stEscenario escenario;
		this->cargaStEscenario(nodo[i],escenario);
		escenarios.push_back(escenario);
	}

	return void();
}

void ParserYaml::cargaStEscenario(const YAML::Node& nodo, ParserYaml::stEscenario& escenario){

	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it) {	
		std::string clave = this->leerNodoYamlString(it.first());
		if ( clave.compare("nombre") == 0 ){ escenario.nombre = this->leerNodoYamlString(it.second());
		}else if ( clave.compare("size_x") == 0 ){ escenario.tamanioX = this->leerNodoYamlInt(it.second());
		}else if ( clave.compare("size_y") == 0 ){ escenario.tamanioY = this->leerNodoYamlInt(it.second());
		}else if ( clave.compare("entidadesDef") == 0 ){ this->cargaListaEntidadesDefinidas(it.second(),escenario.entidadesDefinidas) ;
		}else if ( clave.compare("protagonista") == 0 ){ this->cargaStProtagonista(it.second(),escenario.protagonista);
		}else{Log::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");}

		Log::getInstance().log(3,__FILE__,__LINE__,"Clave <"+clave+"> Leída.");
	}

	return void();
}

void ParserYaml::cargaListaEntidadesDefinidas(const YAML::Node& nodo, std::list <ParserYaml::stEntidadDefinida>& entidadesDefinidas){

	for(unsigned i=0;i<nodo.size();i++) { //El nodo es una lista, itero en esa lista
		stEntidadDefinida entidadDefinida;
		this->cargaStEntidadDefinida(nodo[i],entidadDefinida);
		entidadesDefinidas.push_back(entidadDefinida);
	}

	return void();
}

void ParserYaml::cargaStEntidadDefinida(const YAML::Node& nodo, ParserYaml::stEntidadDefinida& entidadDefinida){

	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it){	
		std::string clave = this->leerNodoYamlString(it.first());
		if ( clave.compare("entidad") == 0 ){ entidadDefinida.entidad = this->leerNodoYamlString(it.second());
		}else if ( clave.compare("x") == 0 ){ entidadDefinida.x = this->leerNodoYamlInt(it.second());
		}else if ( clave.compare("y") == 0 ){ entidadDefinida.y = this->leerNodoYamlInt(it.second());
		}else{Log::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");}	

		Log::getInstance().log(3,__FILE__,__LINE__,"Clave <"+clave+"> Leída.");
	}

	return void();
}

void ParserYaml::cargaStProtagonista(const YAML::Node& nodo, ParserYaml::stProtagonista& protagonista){

	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it){
		std::string clave = this->leerNodoYamlString(it.first());
		if ( clave.compare("entidad") == 0 ){ protagonista.entidad = this->leerNodoYamlString(it.second());
		}else if ( clave.compare("x") == 0 ){ protagonista.x = this->leerNodoYamlInt(it.second());
		}else if ( clave.compare("y") == 0 ){ protagonista.y = this->leerNodoYamlInt(it.second());
		}else{Log::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");}

		Log::getInstance().log(3,__FILE__,__LINE__,"Clave <"+clave+"> Leída.");
	}

	return void();
}

// A partir de una ruta de archivo, devuelve true si el mismo se puede abrir exitosamente, false en caso contrario
bool ParserYaml::chequeoArchivo(std::string ruta){
	std::fstream archivo;
	std::string rutaRelativa(YAML_RUTA_DIRECTORIO_IMG);
	rutaRelativa.append(ruta.c_str());

	// Abro el archivo
	archivo.open( rutaRelativa.c_str() , std::ios::in | std::ios::binary);

	// Chequeo de ruta
	if ( !(archivo.is_open()) ){
		Log::getInstance().log(1,__FILE__,__LINE__,"Error de archivo. La ruta de archivo <"+rutaRelativa+"> es inválida.");
		return false;
	}

	// Cierro el archivo
	archivo.close();
	return true;
}

// Lee un nodo yaml y lo valida suponiendo que contiene un int
// Devuelve el valor validado, en caso de haber error el valor es YAML_ERROR_INT
int ParserYaml::leerNodoYamlInt(const YAML::Node& nodo){
	bool lecturaOk = true;
	int valorInt;

	// Intento leer el valor
	try{
		nodo >> valorInt;
	}catch(YAML::Exception& e){ // Capturo las excepciones del parser Yaml
		this->notificarErrorLectura(YAML_TIPO_INT,__FILE__,__LINE__,e.what(),lecturaOk);
	}

	// Devuelvo el valor validado
	if ( lecturaOk == false){
		return YAML_ERROR_INT;
	}else{
		return valorInt;
	}
}

std::string ParserYaml::leerNodoYamlString(const YAML::Node& nodo){
	bool lecturaOk = true;
	std::string valorString;

	// Intento leer el valor
	try{
		nodo >> valorString;
	}catch(YAML::Exception& e){ // Capturo las excepciones del parser Yaml
		this->notificarErrorLectura(YAML_TIPO_STRING,__FILE__,__LINE__,e.what(),lecturaOk);
	}

	if ( lecturaOk == false){
		valorString.assign(YAML_STRING_VACIO);
		return valorString;
	}else{
		return valorString;
	}
}

void ParserYaml::notificarErrorLectura(std::string tipoDato,std::string archivo, int linea, std::string msgError, bool& lecturaOk){
		std::string msg;
		msg.append("Error de sintaxis YAML. Ocurió un error al intentar leer un dato del tipo ");
		msg.append(tipoDato);
		msg.append(" . Reporte del parser ");
		msg.append(msgError);
		Log::getInstance().log(1,archivo,linea,msg);
		lecturaOk = false;
}

// TODO: Tareas:
// + Hacer la rutina de validación