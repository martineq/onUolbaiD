#include "ParserYaml.h"

ParserYaml::ParserYaml(){

	// Inicialo this->juego
	this->juego.juegoValido = true;
	this->juego.pantalla.alto = YAML_ERROR_INT;
	this->juego.pantalla.ancho = YAML_ERROR_INT;
	this->juego.configuracion.margenScroll = YAML_ERROR_INT;
	this->juego.configuracion.velocidadPersonaje = YAML_ERROR_INT;
	this->juego.entidades.clear();
	this->juego.escenarios.clear();

	// Indico que no se leyó el archivo YAML
	this->archivoYaLeido = false;

}

ParserYaml::~ParserYaml(void){

}


///////////////////////
/// Carga de datos  ///
///////////////////////

ParserYaml::stJuego ParserYaml::cargarConfiguracionDeJuego(void){

	if( this->archivoYaLeido == true ) return this->juego; // Para poder leer los datos varias veces

	std::ifstream archivo(YAML_RUTA_ARCHIVO_JUEGO);	// Abro el archivo
	Log::getInstance().log(1,__FILE__,__LINE__,"Configuración de juego iniciada");

	if(archivo.good()==true){						// Si pude abrir el archivo yaml, empiezo a parsear
		try{
			YAML::Parser parser(archivo);				// Parser YAML
			YAML::Node nodoRaiz;						// Creo un nodo raiz del documento Yaml
			parser.GetNextDocument(nodoRaiz);			// Obtengo el nodo raiz
			this->cargaStJuego(nodoRaiz,this->juego);	// Comienzo con la carga del juego
		}catch(YAML::Exception& e){
			this->notificarErrorLectura(YAML_TIPO_STRING,__FILE__,__LINE__,e.what(),this->juego.juegoValido);
		}

		this->validacionDeDatos();
		Log::getInstance().log(1,__FILE__,__LINE__,"Configuración de juego finalizada");
	}else{
		// Si no pude abrir el archivo lo reporto
		this->juego.juegoValido = false;
		Log::getInstance().log(1,__FILE__,__LINE__,(std::string)"Error al abrir el archivo YAML: "+YAML_RUTA_ARCHIVO_JUEGO);
	}

	// TODO: Luego borrar este if
	if( this->juego.juegoValido == true){
		Log::getInstance().log(1,__FILE__,__LINE__,"Se obtuvo una configuración de juego válida");
	}else{
		Log::getInstance().log(1,__FILE__,__LINE__,"NO se pudo obtener una configuración de juego válida");
	}

	this->archivoYaLeido = true;
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
		//Log::getInstance().log(3,__FILE__,__LINE__,"Clave <"+clave+"> Leída.");
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

		//Log::getInstance().log(3,__FILE__,__LINE__,"Clave <"+clave+"> Leída.");
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

		//Log::getInstance().log(3,__FILE__,__LINE__,"Clave <"+clave+"> Leída.");
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
		}else if ( clave.compare("imagen") == 0 ){ std::string rutaImagen(YAML_RUTA_DIRECTORIO_IMG); rutaImagen.append(this->leerNodoYamlString(it.second())); entidad.imagen = rutaImagen;
		}else if ( clave.compare("ancho_base") == 0 ){ entidad.anchoBase = this->leerNodoYamlInt(it.second());
		}else if ( clave.compare("alto_base") == 0 ){ entidad.altoBase = this->leerNodoYamlInt(it.second());
		}else if ( clave.compare("pixel_ref_x") == 0 ){ entidad.pixelReferenciaX = this->leerNodoYamlInt(it.second());
		}else if ( clave.compare("pixel_ref_y") == 0 ){ entidad.pixelReferenciaY = this->leerNodoYamlInt(it.second());
		}else if ( clave.compare("fps") == 0 ){ entidad.fps = this->leerNodoYamlInt(it.second());
		}else if ( clave.compare("delay") == 0 ){ entidad.delay = this->leerNodoYamlInt(it.second());
		}else{Log::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");}	

		//Log::getInstance().log(3,__FILE__,__LINE__,"Clave <"+clave+"> Leída.");
	}

	return void();
}

void ParserYaml::cargaDefaultStEntidad(ParserYaml::stEntidad& entidad){
	std::string rutaImagen(YAML_RUTA_DIRECTORIO_IMG);
	rutaImagen.append(YAML_DEAFAULT_RUTA_IMAGEN);
	entidad.imagen = rutaImagen;
	entidad.nombre = YAML_DEAFAULT_NOMBRE;
	entidad.anchoBase = YAML_DEAFAULT_ANCHO_BASE;
	entidad.altoBase = YAML_DEAFAULT_ALTO_BASE;
	entidad.pixelReferenciaX = YAML_DEAFAULT_PIXEL_REF_X;
	entidad.pixelReferenciaY = YAML_DEAFAULT_PIXEL_REF_Y;
	entidad.fps = YAML_DEAFAULT_FPS;
	entidad.delay = YAML_DEAFAULT_DELAY;
}

void ParserYaml::cargaListaEscenarios(const YAML::Node& nodo, std::list <ParserYaml::stEscenario>& escenarios){

	for(unsigned i=0;i<nodo.size();i++) { // El nodo es una lista, itero en esa lista
		stEscenario escenario;
		this->cargaDefaultStEscenario(escenario);
		this->cargaStEscenario(nodo[i],escenario);
		escenarios.push_back(escenario);
	}

	return void();
}

void ParserYaml::cargaDefaultStEscenario(ParserYaml::stEscenario& escenario){
	escenario.nombre = YAML_STRING_VACIO;
	escenario.tamanioX = YAML_ERROR_INT;
	escenario.tamanioY = YAML_ERROR_INT;
	escenario.entidadesDefinidas.clear();
	escenario.protagonistas.clear();
}

void ParserYaml::cargaStEscenario(const YAML::Node& nodo, ParserYaml::stEscenario& escenario){

	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it) {	
		std::string clave = this->leerNodoYamlString(it.first());
		if ( clave.compare("nombre") == 0 ){ escenario.nombre = this->leerNodoYamlString(it.second());
		}else if ( clave.compare("size_x") == 0 ){ escenario.tamanioX = this->leerNodoYamlInt(it.second());
		}else if ( clave.compare("size_y") == 0 ){ escenario.tamanioY = this->leerNodoYamlInt(it.second());
		}else if ( clave.compare("entidadesDef") == 0 ){ this->cargaListaEntidadesDefinidas(it.second(),escenario.entidadesDefinidas) ;
		}else if ( clave.compare("protagonista") == 0 ){ this->cargaListaProtagonistas(it.second(),escenario.protagonistas);
		}else{Log::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");}

		//Log::getInstance().log(3,__FILE__,__LINE__,"Clave <"+clave+"> Leída.");
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

		//Log::getInstance().log(3,__FILE__,__LINE__,"Clave <"+clave+"> Leída.");
	}

	return void();
}

void ParserYaml::cargaListaProtagonistas(const YAML::Node& nodo, std::list <ParserYaml::stProtagonista>& protagonistas){

	for(unsigned i=0;i<nodo.size();i++) { //El nodo es una lista, itero en esa lista
		
		stProtagonista protagonista;

		for(YAML::Iterator it=nodo[i].begin();it!=nodo[i].end();++it){
			
			std::string clave = this->leerNodoYamlString(it.first());
			if ( clave.compare("entidad") == 0 ){ protagonista.entidad = this->leerNodoYamlString(it.second());
			}else if ( clave.compare("x") == 0 ){ protagonista.x = this->leerNodoYamlInt(it.second());
			}else if ( clave.compare("y") == 0 ){ protagonista.y = this->leerNodoYamlInt(it.second());
			}else{Log::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");}

			//Log::getInstance().log(3,__FILE__,__LINE__,"Clave <"+clave+"> Leída.");
		}

		// Agrego el protagonista a la lista
		protagonistas.push_back(protagonista);
	}

	return void();
}


///////////////////////////
/// Validación de datos ///
///////////////////////////

void ParserYaml::validacionDeDatos(){

	this->validaPantalla();
	this->validaConfiguracion();
	this->validaEntidades();
	this->validaEscenarios();

	return void();
}

void ParserYaml::validaPantalla(void){

	if (this->juego.pantalla.alto < YAML_PANTALLA_ALTO_TOPE_MINIMO || this->juego.pantalla.alto > YAML_PANTALLA_ALTO_TOPE_MAXIMO){
		Log::getInstance().log(1,__FILE__,__LINE__,"Pantalla->Alto fuera de rango. Se usará valor por defecto.");
		this->juego.pantalla.alto = YAML_DEAFAULT_PANTALLA_ALTO;
	}

	if (this->juego.pantalla.ancho < YAML_PANTALLA_ANCHO_TOPE_MINIMO || this->juego.pantalla.ancho > YAML_PANTALLA_ANCHO_TOPE_MAXIMO){
		Log::getInstance().log(1,__FILE__,__LINE__,"Pantalla->Ancho fuera de rango. Se usará valor por defecto.");
		this->juego.pantalla.ancho = YAML_DEAFAULT_PANTALLA_ANCHO;
	}

	return void();
}

void ParserYaml::validaConfiguracion(void){

	// Chequeo la velocidad del personaje
	if (this->juego.configuracion.velocidadPersonaje < YAML_VELOCIDAD_PERSONAJE_TOPE_MINIMO || this->juego.configuracion.velocidadPersonaje > YAML_VELOCIDAD_PERSONAJE_TOPE_MAXIMO ){
		Log::getInstance().log(1,__FILE__,__LINE__,"configuracion->vel_personaje fuera de rango. Se asignará el valor por defecto.");
		this->juego.configuracion.velocidadPersonaje = YAML_DEAFAULT_VEL_PERSONAJE;
	}

	// Chequeo el margen de scroll
	if (this->juego.configuracion.margenScroll < YAML_MARGEN_SCROLL_TOPE_MINIMO || this->juego.configuracion.margenScroll > ((int)((this->juego.pantalla.ancho)/2)-(YAML_PERSONAJE_LONGITUD_MAXIMA/2)-1) || this->juego.configuracion.margenScroll > ( (int) ( (this->juego.pantalla.alto)/2)-(YAML_PERSONAJE_LONGITUD_MAXIMA/2)-1 ) ){
		Log::getInstance().log(1,__FILE__,__LINE__,"configuracion->margen_scroll fuera de rango. Se asignará el valor de margen por defecto.");
		this->juego.configuracion.margenScroll = YAML_DEAFAULT_MARGEN_SCROLL;
	}

	return void();
}

void ParserYaml::validaEntidades(void){

	// Lista de las entidades que se van a borrar, en caso de presentar errores
	std::list<std::list<stEntidad>::iterator> tipoEntidadABorrar; 

	this->validaRecorrerListaEntidades(tipoEntidadABorrar);
	this->validaDescartarEntidades(tipoEntidadABorrar);
	this->validaListaEntidadesVacia();

	return void();
}


void ParserYaml::validaRecorrerListaEntidades(std::list<std::list<ParserYaml::stEntidad>::iterator>& tipoEntidadABorrar){

	for (std::list<stEntidad>::iterator it=this->juego.entidades.begin() ; it != this->juego.entidades.end(); it++ ){

		bool entidadOk = true; // Luego, Si (entidadOk == false), la voy a descartar de mi lista de entidades
		
		// Chequeo la validez del ancho, alto, nombre la entidad y los pixel_ref
		if( (*it).anchoBase < 1 || (*it).anchoBase > this->juego.pantalla.ancho || (*it).altoBase < 1 || (*it).altoBase > this->juego.pantalla.alto ||
			(*it).nombre.empty()==true || (*it).pixelReferenciaX > this->juego.pantalla.ancho || (*it).pixelReferenciaY > this->juego.pantalla.alto ||
			(*it).pixelReferenciaX < 0 || (*it).pixelReferenciaY < 0){
			Log::getInstance().log(1,__FILE__,__LINE__,"La entidad "+ (*it).nombre +" tiene valores inválidos o faltantes.");
			entidadOk = false;
		}

		// Chequeo la validez de fps
		if( (*it).fps < 0 || (*it).fps > YAML_FPS_TOPE_MAXIMO ){
			Log::getInstance().log(1,__FILE__,__LINE__,"La entidad "+ (*it).nombre +" tiene el valor fps fuera del rango permitido.");
			entidadOk = false;
		}

		// Chequeo la validez de delay
		if( (*it).delay < 0 || (*it).fps > YAML_DELAY_TOPE_MAXIMO ){
			Log::getInstance().log(1,__FILE__,__LINE__,"La entidad "+ (*it).nombre +" tiene el valor delay fuera del rango permitido.");
			entidadOk = false;
		}

		// Chequeo la validez de la ruta de la imagen // TODO: Ver si hay que agregar funcionalidad para una lista de animaciones
		if( chequeoArchivo((*it).imagen) == false ){
			Log::getInstance().log(1,__FILE__,__LINE__,"La entidad "+ (*it).nombre +" tiene una ruta de imagen inválida.");
			entidadOk = false;
		}

		// Chequeo que no sea una entidad repetida, entro solo si los demás datos son válidos
		if( entidadOk == true){
			if( this->validaEsEntidadRepetida(it,tipoEntidadABorrar) == true ){ entidadOk = false; }
		}

		// Si anteriormente se encontró un problema, se descarta ese tipo personaje
		if( entidadOk == false) tipoEntidadABorrar.push_back(it); 

	}
	return void();
}

bool ParserYaml::validaEsEntidadRepetida(std::list<stEntidad>::iterator iterador, std::list<std::list<stEntidad>::iterator>& tipoEntidadABorrar){

	unsigned int repeticiones = 0;

	for (std::list<stEntidad>::iterator it=this->juego.entidades.begin() ; it != this->juego.entidades.end(); it++ ){	
		if( (*it).nombre.compare((*iterador).nombre) == 0 ){
			repeticiones++;
		}
	}

	if( repeticiones < 2){	// No está repetido
		return false;
	}else{					// Si está repetido
		int repeticionesSobrantes = ( this->validaCantidadVecesEnEntidadABorrar(iterador,tipoEntidadABorrar) );
		if ( repeticionesSobrantes < (repeticiones-1) ){  // Y si todavia la cantidad de veces que lo voy a borrar es menor a repeticiones-1
			Log::getInstance().log(1,__FILE__,__LINE__,"La entidad "+ (*iterador).nombre +" se encuentra repetida.");
			return true;
		}else{
			return false;
		}
	}
}

int ParserYaml::validaCantidadVecesEnEntidadABorrar(std::list<stEntidad>::iterator iteradorBuscado, std::list<std::list<stEntidad>::iterator>& tipoEntidadABorrar){

	int vecesRepetidas = 0;

	for (std::list<std::list<stEntidad>::iterator>::iterator it=tipoEntidadABorrar.begin() ; it != tipoEntidadABorrar.end(); it++ ){	
		if( (*(*it)).nombre.compare( (*iteradorBuscado).nombre) == 0 ) vecesRepetidas++;
	}

	return vecesRepetidas;
}

bool ParserYaml::validaListaAnimaciones(std::list<std::string> listaAnimaciones){

	bool animacionesOk = true;

// TODO: Ver si se usará esto para el chequeo de las animaciones

		// Chequeo si la lista de animaciones está vacía
/*		if ( (*it).animaciones.empty() == true){
			Log::getInstance().log(1,__FILE__,__LINE__,"La entidad "+ (*it).nombre +" no tiene animaciones asignadas.");
			animacionesOk = false;
		}

		// Recorro todas las aniaciones 
		for (std::list<stAnimacion>::iterator it=(*it).animaciones.begin() ; it != (*it).animaciones.end(); it++ ){
			
			// Chequeo la validez del nombre de la animación
			if ( (*it).nombre.empty()==true ) {
				Log::getInstance().log(1,__FILE__,__LINE__,"Las animaciones de la entidad "+ (*it).nombre +" no tienen valores válidos en su nombre.");
				animacionesOk = false;
			}

			// Chequeo la validez del período de la animación
			if ( (*it).periodo < 0 ) {
				Log::getInstance().log(1,__FILE__,__LINE__,"Las animaciones de la entidad "+ (*it).nombre +" no tienen valores válidos en su periodo. Se usará un valor por defecto");
				(*it).periodo = JUEGO_PERIODO_DEFAULT;
			}

			// Chequeo si las rutas de las animaciones son válidas
			for (std::list<std::string>::iterator it3=(*it).sprites.begin() ; it3 != (*it).sprites.end(); it3++ ){
				if ( chequeoArchivo((*it3))==false){
					Log::getInstance().log(1,__FILE__,__LINE__,"Las animaciones de la entidad "+ (*it).nombre +" tienen rutas de archivo inválidos.");
					animacionesOk = false;
				}
			}

		} 
*/
	return animacionesOk;
}

void ParserYaml::validaDescartarEntidades(std::list<std::list<ParserYaml::stEntidad>::iterator>& tipoEntidadABorrar){

	// En caso de tener un entidad para descartar, lo hago aquí
	if ( tipoEntidadABorrar.empty() == false ){
		Log::getInstance().log(1,__FILE__,__LINE__,"entidades: existen entidades inválidas. Las mismas se descartarán.");
		for (std::list<std::list<stEntidad>::iterator>::iterator it=tipoEntidadABorrar.begin() ; it != tipoEntidadABorrar.end(); it++ ){
			this->juego.entidades.erase(*it);
		}
	}
	return void();
}

void ParserYaml::validaListaEntidadesVacia(void){

	// Chequeo si la lista quedó vacía (o si estaba vacía desde el principio).
	if (this->juego.entidades.empty() == true){
		Log::getInstance().log(1,__FILE__,__LINE__,"no existen entidades disponibles.");
		this->juego.juegoValido = false;
	}
	return void();
}

void ParserYaml::validaEscenarios(void){

	// Lista de los escenarios que se van a borrar, en caso de presentar errores
	std::list<std::list<ParserYaml::stEscenario>::iterator> tipoEscenarioABorrar; 

	this->validaRecorrerListaEscenarios(tipoEscenarioABorrar);
	this->validaDescartarEscenarios(tipoEscenarioABorrar);
	this->validaListaEscenariosVacia();

	return void();
}

void ParserYaml::validaRecorrerListaEscenarios(std::list<std::list<ParserYaml::stEscenario>::iterator>& tipoEscenarioABorrar){

	for (std::list<stEscenario>::iterator it=this->juego.escenarios.begin() ; it != this->juego.escenarios.end(); it++ ){

		bool escenarioOk = true; // Luego, Si (escenarioOk == false), lo voy a descartar de mi lista de entidades

		// Chequeo la validez de tamanioX, tamanioY y del nombre 
		if( (*it).tamanioX < 1 || (*it).tamanioY < 1 || (*it).nombre.compare(YAML_STRING_VACIO) == 0 ){
			Log::getInstance().log(1,__FILE__,__LINE__,"La entidad "+ (*it).nombre +" tiene valores inválidos o faltantes.");
			escenarioOk = false;
		}

		this->validaListaEntidadesDefinidas((*it).entidadesDefinidas,(*it).nombre,(*it).tamanioX,(*it).tamanioY );

		if( this->validaListaProtagonistas((*it).protagonistas,(*it).nombre,(*it).tamanioX,(*it).tamanioY) == false){
			escenarioOk = false;
		}

		// Si anteriormente se encontró un problema, se descarta ese tipo personaje
		if( escenarioOk == false) tipoEscenarioABorrar.push_back(it); 
	}
	return void();
}

void ParserYaml::validaListaEntidadesDefinidas(std::list <ParserYaml::stEntidadDefinida>& entidadesDefinidas, std::string nombreEscenario, int tamanioX, int tamanioY){

	// Lista de las entidades que se van a borrar, en caso de presentar errores
	std::list<std::list<ParserYaml::stEntidadDefinida>::iterator> tipoEntidadDefinidaABorrar; 
	bool entidadDefinidaOk = true;

	// Recorro todas las entidades definidas 
	for (std::list<stEntidadDefinida>::iterator it=entidadesDefinidas.begin() ; it != entidadesDefinidas.end(); it++ ){
		
		// Chequeo la validez del nombre de la entidad definida
		if ( (*it).entidad.compare(YAML_STRING_VACIO) == 0 ) {
			Log::getInstance().log(1,__FILE__,__LINE__,"Una entidad definida del escenario "+ nombreEscenario +" no tiene un valor válido en su campo <entidad>.");
			entidadDefinidaOk = false;
		}

		// Valido <x> e <y>
		if ( (*it).x < 0 || (*it).y < 0 || (*it).x > tamanioX || (*it).y > tamanioY ) {
			Log::getInstance().log(1,__FILE__,__LINE__,"Los valores de x e y del escenario "+ nombreEscenario +", entidad "+ (*it).entidad +" no tienen valores válidos.");
			entidadDefinidaOk = false;
		}

		// Valido la existencia de la entidad
		if( this->validaExisteEntidad((*it).entidad) == false ) entidadDefinidaOk = false;

		// Agrego la entidad definida con errores
		if( entidadDefinidaOk == false) tipoEntidadDefinidaABorrar.push_back(it); 
	} 

	// Borro las entidades definidas con errores
	if ( tipoEntidadDefinidaABorrar.empty() == false ){
		Log::getInstance().log(1,__FILE__,__LINE__,"escenarios->entidadesDef: existen entidades definidas inválidas para el escenario "+ nombreEscenario +". Las mismas se descartarán.");
		for (std::list<std::list<stEntidadDefinida>::iterator>::iterator it=tipoEntidadDefinidaABorrar.begin() ; it != tipoEntidadDefinidaABorrar.end(); it++ ){
			entidadesDefinidas.erase(*it);
		}
	}

}

bool ParserYaml::validaExisteEntidad(std::string entidad){
	for (std::list<ParserYaml::stEntidad>::iterator it=this->juego.entidades.begin() ; it != this->juego.entidades.end(); it++ ){
		if( (*it).nombre.compare(entidad) == 0 ) return true;
	}
	Log::getInstance().log(1,__FILE__,__LINE__,"La entidad requerida <"+ entidad +"> no existe.");
	return false;
}

bool ParserYaml::validaListaProtagonistas(std::list <ParserYaml::stProtagonista>& protagonistas,std::string nombreEscenario, int tamanioX, int tamanioY){
	
	// Lista de los protagonistas que se van a borrar, en caso de presentar errores
	std::list<std::list<ParserYaml::stProtagonista>::iterator> tipoProtagonistaABorrar; 
	bool protagonistaOk = true;

	// Recorro todas los protagonistas 
	for (std::list<stProtagonista>::iterator it=protagonistas.begin() ; it != protagonistas.end(); it++ ){
		
		// Chequeo la validez del nombre del protagonista
		if ( (*it).entidad.compare(YAML_STRING_VACIO) == 0 ) {
			Log::getInstance().log(1,__FILE__,__LINE__,"Un protagonista del escenario "+ nombreEscenario +" no tiene un valor válido en su campo <entidad>.");
			protagonistaOk = false;
		}

		// Valido <x> e <y>
		if ( (*it).x < 0 || (*it).y < 0 || (*it).x > tamanioX || (*it).y > tamanioY ) {
			Log::getInstance().log(1,__FILE__,__LINE__,"Los valores de x e y del protagonista con escenario "+ nombreEscenario +", entidad "+ (*it).entidad +" no tienen valores válidos.");
			protagonistaOk = false;
		}

		// Valido la existencia de la entidad
		if( this->validaExisteEntidad((*it).entidad) == false ) protagonistaOk = false;

		// Agrego la entidad definida con errores
		if( protagonistaOk == false) tipoProtagonistaABorrar.push_back(it); 
	} 

	// Borro las entidades definidas con errores
	if ( tipoProtagonistaABorrar.empty() == false ){
		Log::getInstance().log(1,__FILE__,__LINE__,"escenarios->protagonista: existen protagonistas definidos inválidos para el escenario "+ nombreEscenario +". Los mismos se descartarán.");
		for (std::list<std::list<stProtagonista>::iterator>::iterator it=tipoProtagonistaABorrar.begin() ; it != tipoProtagonistaABorrar.end(); it++ ){
			protagonistas.erase(*it);
		}
	}

	if ( protagonistas.empty() == true ){
		Log::getInstance().log(1,__FILE__,__LINE__,"Luego de la validación, la lista de personajes del escenario "+ nombreEscenario +" ha quedado vacía.");
		return false;
	}else{
		return true;
	}

}

void ParserYaml::validaDescartarEscenarios(std::list<std::list<ParserYaml::stEscenario>::iterator>& tipoEscenarioABorrar){

	// En caso de tener un escenario para descartar, lo hago aquí
	if ( tipoEscenarioABorrar.empty() == false ){
		Log::getInstance().log(1,__FILE__,__LINE__,"escenarios: existen escenarios inválidos. Los mismos se descartarán.");
		for (std::list<std::list<stEscenario>::iterator>::iterator it=tipoEscenarioABorrar.begin() ; it != tipoEscenarioABorrar.end(); it++ ){
			this->juego.escenarios.erase(*it);
		}
	}
	return void();
}

void ParserYaml::validaListaEscenariosVacia(void){
	// Chequeo si la lista quedó vacía (o si estaba vacía desde el principio).
	if (this->juego.escenarios.empty() == true){
		Log::getInstance().log(1,__FILE__,__LINE__,"no existen escenarios disponibles.");
		this->juego.juegoValido = false;
	}
	return void();
}


////////////////////////////
/// Funciones auxiliares ///
////////////////////////////

// A partir de una ruta de archivo, devuelve true si el mismo se puede abrir exitosamente, false en caso contrario
bool ParserYaml::chequeoArchivo(std::string rutaArchivo){
	std::fstream archivo;

	// Abro el archivo
	archivo.open( rutaArchivo.c_str() , std::ios::in | std::ios::binary);

	// Chequeo de ruta
	if ( !(archivo.is_open()) ){
		Log::getInstance().log(1,__FILE__,__LINE__,"Error de archivo. La ruta de archivo <"+rutaArchivo+"> es inválida.");
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
// + Verificar que la rutina de validación cubre todos los casos
