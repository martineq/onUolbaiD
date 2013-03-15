#include "ParserYaml.h"


ParserYaml::ParserYaml(void){
	cargaJuegoDefault();
}

ParserYaml::~ParserYaml(void){

}

//////////////////////////////
// Funciones para la prueba //
//////////////////////////////

void ParserYaml::cargaVec3(const YAML::Node& nodo, Vec3& v){
	nodo[0] >> v.x;
	nodo[1] >> v.y;
	nodo[2] >> v.z;
}

void ParserYaml::cargaPower(const YAML::Node& nodo, Power& power){
	nodo["name"] >> power.name;
	nodo["damage"] >> power.damage;
	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it) {
		std::string key, value;
		it.first() >> key;
		it.second() >> value;
		std::cout << "Key: " << key << ", value: " << value << std::endl;
	}
}

void ParserYaml::cargaMonster(const YAML::Node& nodo, Monster& monster){
	nodo["name"] >> monster.name;
	cargaVec3(nodo["position"],monster.position);
	
	const YAML::Node& powers = nodo["powers"];
	for(unsigned i=0;i<powers.size();i++) {
	  Power power;
	  cargaPower(powers[i],power);
	  monster.powers.push_back(power);
	}
}

void ParserYaml::prueba(void){

	Logger::getInstance().log(3,__FILE__,__LINE__,"Prueba YAML cerrada");
	return void();
	
	//std::ifstream archivo(/*Para usar la prueba hay que usar el archivo prueba.yaml, función en desuso*/YAML_RUTA_ARCHIVO_JUEGO_DEFAULT);
  /*YAML::Parser parser(archivo);
    YAML::Node doc;
	parser.GetNextDocument(doc);

	for(unsigned i=0;i<doc.size();i++) {
	  Monster monster;
	  cargaMonster(doc[i],monster);
	  std::cout << monster.name << "\n";
	}
	
	system("pause");*/
}

/////////////////////////////
// Funciones para el juego //
/////////////////////////////

void ParserYaml::cargaStPantalla(const YAML::Node& nodo, stPantalla& pantalla){
	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it){
		std::string clave;
		clave = this->leerYamlString(it.first());
		if ( clave.compare("alto") == 0 ){ pantalla.alto = this->leerYamlInt(it.second());
		}else if ( clave.compare("ancho") == 0 ){ pantalla.ancho = this->leerYamlInt(it.second());
		}else{Logger::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");}
	}
}

void ParserYaml::cargaStParametros(const YAML::Node& nodo, stParametros& parametros){
	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it){
		std::string clave;
		clave = this->leerYamlString(it.first());
		if ( clave.compare("margen_scroll") == 0 ){ parametros.margenScroll = this->leerYamlInt(it.second());
		}else if ( clave.compare("vel_personaje") == 0 ){ parametros.velPersonaje = this->leerYamlInt(it.second());
		}else{Logger::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");}
	}
}

void ParserYaml::cargaListaSprites(const YAML::Node& nodo, std::list <std::string>& sprites){
	//El nodo es una lista
	for(unsigned i=0;i<nodo.size();i++) {
		std::string str;
		str = this->leerYamlString(nodo[i]);
		sprites.push_back(str);
	}
}

void ParserYaml::cargaListaAnimaciones(const YAML::Node& nodo, std::list <stAnimacion>& animaciones){
	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it) { // Cargo los demas datos
		stAnimacion animacion;
		animacion.nombre = this->leerYamlString(it.first()); // La clave es el nombre de la animacion
		const YAML::Node& nodoHijo = it.second();
		animacion.periodo = JUEGO_PERIODO_DEFAULT;
		for(YAML::Iterator it2=nodoHijo.begin();it2!=nodoHijo.end();++it2) { // Cargo los demas datos
			std::string clave;
			clave = this->leerYamlString(it2.first());
			if ( clave.compare("periodo") == 0 ){ animacion.periodo = this->leerYamlInt(it2.second());
			}else if ( clave.compare("sprites") == 0 ){ cargaListaSprites(it2.second(),animacion.sprites);
			}else{Logger::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");}
		}
		animaciones.push_back(animacion);
	}
}

void ParserYaml::cargaListaTiposPersonaje(const YAML::Node& nodo, std::list <stTipoPersonaje>& tiposPersonaje){
	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it) {
		stTipoPersonaje tipoPersonaje;
		tipoPersonaje.nombre = this->leerYamlString(it.first()); // La clave es el nombre del personaje
		const YAML::Node& nodoHijo = it.second();
		for(YAML::Iterator it2=nodoHijo.begin();it2!=nodoHijo.end();++it2) { // Cargo los demas datos
			std::string clave;
			clave = this->leerYamlString(it2.first());
			if ( clave.compare("alto") == 0 ){ tipoPersonaje.alto = this->leerYamlInt(it2.second());
			}else if ( clave.compare("ancho") == 0 ){ tipoPersonaje.ancho = this->leerYamlInt(it2.second());
			}else if ( clave.compare("animaciones") == 0 ){ cargaListaAnimaciones(it2.second(),tipoPersonaje.animaciones);
			}else{Logger::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");}
		}

		// Si es protagonista lo pongo al principio de la lista
		if ( tipoPersonaje.nombre.compare("protagonista")){
			tiposPersonaje.push_front(tipoPersonaje);
		}else{
			tiposPersonaje.push_back(tipoPersonaje);
		}
		
	}
}

void ParserYaml::cargaStEscalera(const YAML::Node& nodo, stEscalera& escalera){
	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it){
		std::string clave;
		clave = this->leerYamlString(it.first());
		if ( clave.compare("alto") == 0 ){ escalera.alto = this->leerYamlInt(it.second());
		}else if ( clave.compare("ancho") == 0 ){ escalera.ancho = this->leerYamlInt(it.second());
		}else if ( clave.compare("x") == 0 ){ escalera.x = this->leerYamlInt(it.second());
		}else if ( clave.compare("y") == 0 ){ escalera.y = this->leerYamlInt(it.second());
		}else if ( clave.compare("textura") == 0 ){ escalera.textura = this->leerYamlString(it.second());
		}else{Logger::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");}
	}
}

void ParserYaml::cargaStPersonaje(const YAML::Node& nodo, stPersonaje& personaje){
	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it){
		std::string clave;
		clave = this->leerYamlString(it.first());
		if ( clave.compare("tipo") == 0 ){ personaje.tipo = this->leerYamlString(it.second());
		}else if ( clave.compare("x") == 0 ){ personaje.x = this->leerYamlInt(it.second());
		}else if ( clave.compare("y") == 0 ){ personaje.y = this->leerYamlInt(it.second());
		}else{Logger::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");}
	}
}

void ParserYaml::cargaStPlataforma(const YAML::Node& nodo, stPlataforma& plataforma){
	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it){
		std::string clave;
		clave = this->leerYamlString(it.first());
		if ( clave.compare("alto") == 0 ){ plataforma.alto = this->leerYamlInt(it.second());
		}else if ( clave.compare("ancho") == 0 ){ plataforma.ancho = this->leerYamlInt(it.second());
		}else if ( clave.compare("x") == 0 ){ plataforma.x = this->leerYamlInt(it.second());
		}else if ( clave.compare("y") == 0 ){ plataforma.y = this->leerYamlInt(it.second());
		}else if ( clave.compare("textura") == 0 ){ plataforma.textura = this->leerYamlString(it.second());
		}else{Logger::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");}
	}
}

void ParserYaml::cargaListaTexturas(const YAML::Node& nodo, std::list <stTextura>& texturas){
	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it){
		stTextura textura;
		textura.nombre = this->leerYamlString(it.first());
		textura.ruta = this->leerYamlString(it.second());
		texturas.push_back(textura);
	}
}

void ParserYaml::cargaStNivel(const YAML::Node& nodo, stNivel& nivel){
	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it){
		std::string clave;
		clave = this->leerYamlString(it.first());
		if ( clave.compare("alto") == 0 ){ nivel.alto = this->leerYamlInt(it.second());
		}else if ( clave.compare("ancho") == 0 ){ nivel.ancho = this->leerYamlInt(it.second());
		}else if ( clave.compare("fondo") == 0 ){ this->fondo = this->leerYamlString(it.second());
		}else if ( clave.compare("personajes") == 0 ){
			const YAML::Node& personajes = it.second();
			for(unsigned i=0;i<personajes.size();i++){
				stPersonaje personaje;
				cargaStPersonaje(personajes[i],personaje);
				if (personaje.tipo.compare("protagonista")==0){  //Pongo al protagonista al principio de la lista
					nivel.personajes.push_front(personaje);
				}else{
					nivel.personajes.push_back(personaje);
				}
			}
		}else if ( clave.compare("plataformas") == 0 ){
			const YAML::Node& plataformas = it.second();
			for(unsigned i=0;i<plataformas.size();i++) {
				stPlataforma plataforma;
				cargaStPlataforma(plataformas[i],plataforma);
				nivel.plataformas.push_back(plataforma);
			}	
		}else if ( clave.compare("escaleras") == 0 ){
			const YAML::Node& escaleras = it.second();
			for(unsigned i=0;i<escaleras.size();i++) {
				stEscalera escalera;
				cargaStEscalera(escaleras[i],escalera);
				nivel.escaleras.push_back(escalera);
			}				
		}else{Logger::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");}
	} // Fin del For iterator
}

void ParserYaml::cargaStJuego(const YAML::Node& nodo, stJuego& juego){
	for(YAML::Iterator it=nodo.begin();it!=nodo.end();++it) {
		std::string clave;
		clave = this->leerYamlString(it.first());
		const YAML::Node& nodoHijo = it.second();
		if ( clave.compare("pantalla") == 0 ){ cargaStPantalla(nodoHijo,juego.pantalla);
		}else if ( clave.compare("parametros") == 0 ){ cargaStParametros(nodoHijo,juego.parametros);
		}else if ( clave.compare("tiposPersonaje") == 0 ){ cargaListaTiposPersonaje(nodoHijo,juego.tiposPersonaje);
		}else if ( clave.compare("texturas") == 0 ){ cargaListaTexturas(nodoHijo,juego.texturas);
		}else if ( clave.compare("nivel") == 0 ){ cargaStNivel(nodoHijo,juego.nivel);
		}else{Logger::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");}
	}
	juego.pantalla.fondo = this->fondo;
}

ParserYaml::stJuego ParserYaml::cargaJuego(void){
	std::ifstream archivo(YAML_RUTA_ARCHIVO_JUEGO);
	if(archivo.good()==true){
		try{	
			YAML::Parser parser(archivo);
			YAML::Node doc;
			parser.GetNextDocument(doc);

			for(YAML::Iterator it=doc.begin();it!=doc.end();++it) {
				std::string clave;
				clave = this->leerYamlString(it.first());
				const YAML::Node& nodo = it.second();
				if ( clave.compare("juego") == 0 ) cargaStJuego(nodo,this->juego); // Cargo el nodo Juego
				else Logger::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");
			}
		}catch(YAML::ParserException& e){
			std::string msg;
			Logger::getInstance().log(1,__FILE__,__LINE__,"Error de sintaxis en el archivo YAML. El mismo no puede ser leído. ");
			msg.append("Mensaje de error del parser YAML: ");
			msg.append(e.what());
			Logger::getInstance().log(1,__FILE__,__LINE__,msg);
			asignarJuegoDefault();
		}
/*		catch(YAML::InvalidScalar& e) {
			std::string msg;
			msg.append("Error de sintaxis YAML. Datos inválidos en el archivo YAML: ");
			msg.append(e.what());
			Logger::getInstance().log(1,__FILE__,__LINE__,msg);
			asignarJuegoDefault();
		}
		catch(YAML::Exception& e) {
			std::string msg;
			msg.append("Error de sintaxis YAML. Datos inválidos en el archivo YAML: ");
			msg.append(e.what());
			Logger::getInstance().log(1,__FILE__,__LINE__,msg);
			asignarJuegoDefault();
		}*/
		// Valido los datos
		validacionDatos();
		Logger::getInstance().log(1,__FILE__,__LINE__,"Configuración de juego finalizada");
	}else{
		Logger::getInstance().log(1,__FILE__,__LINE__,(string)"Error al abrir el archivo YAML: "+YAML_RUTA_ARCHIVO_JUEGO);
		asignarJuegoDefault();
	}
	return this->juego;
}

void ParserYaml::cargaJuegoDefault(){
	std::ifstream archivo(YAML_RUTA_ARCHIVO_JUEGO_DEFAULT);
	if(archivo.good()==true){
		try{	
			YAML::Parser parser(archivo);
			YAML::Node doc;
			parser.GetNextDocument(doc);

			for(YAML::Iterator it=doc.begin();it!=doc.end();++it) {
				std::string clave;
				clave = this->leerYamlString(it.first());
				const YAML::Node& nodo = it.second();
				if ( clave.compare("juego") == 0 ) cargaStJuego(nodo,this->bak); // Cargo el nodo Juego
				else Logger::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> descartada.");
			}
		}catch(YAML::ParserException& e){
			std::string msg;
			msg.append("Error de parseo en el juego por defecto: ");
			msg.append(e.what());
			Logger::getInstance().log(1,__FILE__,__LINE__,msg);
		}
	}else{
		Logger::getInstance().log(1,__FILE__,__LINE__,(string)"Error al abrir el archivo YAML por defecto: "+YAML_RUTA_ARCHIVO_JUEGO_DEFAULT);
	}
}

void ParserYaml::validacionDatos(){

	this->validaNivelAnchoAlto();
	this->validaPantalla();
	this->validaTiposPersonajeConParametros();
	this->validaNivelEscaleras();
	this->validaNivelPersonajes();
	this->validaNivelPlataformas();
	this->validaTexturas();

} // Fin validacionDatos

/////////////////////////////////////////////
///////////// INICIO REFACTOR ///////////////
/////////////////////////////////////////////


void ParserYaml::validaParametros(int anchoPjePpal){

	// TODO: verificar el margen vertical (para la etapa que lo requiera)

	// Chequeo el margen de scroll
	if (this->juego.parametros.margenScroll < 1 || this->juego.parametros.margenScroll > ((int)((this->juego.pantalla.ancho)/2)-(anchoPjePpal/2)-1) /*|| this->juego.parametros.margenScroll > ((int)(this->juego.pantalla.alto)/2-1)*/ ){
		Logger::getInstance().log(1,__FILE__,__LINE__,"Parametros->margenScroll fuera de rango. Se asignará el valor mínimo de margen.");
		this->juego.parametros.margenScroll = 1;
	}

	// Chequeo la velocidad del personaje
	if (this->juego.parametros.velPersonaje < 0 || this->juego.parametros.velPersonaje > JUEGO_VELOCIDAD_PERSONAJE_MAXIMA ){
		Logger::getInstance().log(1,__FILE__,__LINE__,"Parametros->velPersonaje fuera de rango. Se asignará el valor por defecto.");
		this->juego.parametros.velPersonaje = this->bak.parametros.velPersonaje;
	}

}

void ParserYaml::validaTexturas(){

	// Lista de los tipoPersonaje que se van a borrar
	list<list<stTextura>::iterator> texturasBorrar;

	// Recorro todas las texturas validando sus valores
	for (list<stTextura>::iterator it=this->juego.texturas.begin() ; it != this->juego.texturas.end(); it++ ){
		if( chequeoArchivo((*it).ruta) == false || (*it).nombre.empty()==true ){
			Logger::getInstance().log(1,__FILE__,__LINE__,"texturas tiene valores inválidos o faltantes.");
			texturasBorrar.push_back(it);
		}
	}

	// Borro las texturas inválidas
	if(texturasBorrar.empty()==false){
		Logger::getInstance().log(1,__FILE__,__LINE__,"Juego->Texturas tiene valores inválidos. Los mismos se descartarán.");
		for (list<list<stTextura>::iterator>::iterator it=texturasBorrar.begin() ; it != texturasBorrar.end(); it++ ){
			this->juego.texturas.erase(*it);
		}
	}

	// Chequeo si la lista de texturas está vacía
	if(this->juego.texturas.empty()==true){	Logger::getInstance().log(1,__FILE__,__LINE__,"Atención: Juego->Texturas texturas se encuentra vacio.");}

}

void ParserYaml::validaPantalla(){
	if (this->juego.pantalla.alto < JUEGO_PANTALLA_ALTO_MINIMO || this->juego.pantalla.alto > JUEGO_PANTALLA_ALTO_MAXIMO){
		Logger::getInstance().log(1,__FILE__,__LINE__,"Pantalla->Alto fuera de rango. Se usará valor por defecto.");
		this->juego.pantalla.alto = this->bak.pantalla.alto;
	}
	if (this->juego.pantalla.alto > this->juego.nivel.alto){
		Logger::getInstance().log(1,__FILE__,__LINE__,"Pantalla->Alto tiene un valor mayor al de Nivel. Se usará valor de Nivel.");
		this->juego.pantalla.alto = this->juego.nivel.alto;
	}
	if (this->juego.pantalla.ancho < JUEGO_PANTALLA_ANCHO_MINIMO || this->juego.pantalla.ancho > JUEGO_PANTALLA_ANCHO_MAXIMO){
		Logger::getInstance().log(1,__FILE__,__LINE__,"Pantalla->Ancho fuera de rango. Se usará valor por defecto.");
		this->juego.pantalla.ancho = this->bak.pantalla.ancho;
	}
	if (this->juego.pantalla.ancho > this->juego.nivel.ancho){
		Logger::getInstance().log(1,__FILE__,__LINE__,"Pantalla->Ancho tiene un valor mayor al de Nivel. Se usará valor de Nivel.");
		this->juego.pantalla.alto = this->juego.nivel.alto;
	}
	if (chequeoArchivo(this->juego.pantalla.fondo)==false){
		Logger::getInstance().log(1,__FILE__,__LINE__,"Pantalla->Fondo, ruta inválida. Se usará un valor por defecto.");
		this->juego.pantalla.fondo = this->bak.pantalla.fondo;
	}

}

void ParserYaml::validaTiposPersonajeConParametros(){

	// Se usa para la validación del personaje principal
	bool existeProtagonista = false;
	bool principalQuietoDerOk = false;
	bool principalQuietoIzqOk = false;
	bool principalCaminarIzqOk = false;
	bool principalCaminarDerOk = false;

	// Se usará en la validación de los márgenes
	int anchoPjePpal = 1;

	// Lista de los tipoPersonaje que se van a borrar
	list<list<stTipoPersonaje>::iterator> tipoPersonajeBorrar; 
	
	// Recorro todos los tipoPersonaje
	for (list<stTipoPersonaje>::iterator it=this->juego.tiposPersonaje.begin() ; it != this->juego.tiposPersonaje.end(); it++ ){
		
		bool tipoPersonajeOk = true; // Si == false, lo voy a descartar de mi lista de tipoPersonaje
		
		// Chequeo la validez del ancho, alto y nombre del tipoPersonaje
		if( (*it).ancho < 1 || (*it).ancho > this->juego.pantalla.ancho || (*it).alto < 1 || (*it).alto > this->juego.pantalla.alto ||
			(*it).nombre.empty()==true ){
			Logger::getInstance().log(1,__FILE__,__LINE__,"El tipoPersonaje "+ (*it).nombre +" tiene valores inválidos o faltantes.");
			tipoPersonajeOk = false;
		}

		// Chequeo si la lista de animaciones del tipoPersonaje está vacía
		if ( (*it).animaciones.empty() == true){
			Logger::getInstance().log(1,__FILE__,__LINE__,"El tipoPersonaje "+ (*it).nombre +" no tiene animaciones asignadas.");
			tipoPersonajeOk = false;
		}

		// Recorro todas las aniaciones de cierto tipoPersonaje
		for (list<stAnimacion>::iterator it2=(*it).animaciones.begin() ; it2 != (*it).animaciones.end(); it2++ ){
			
			// Chequeo la validez del nombre de la animación
			if ( (*it2).nombre.empty()==true ) {
				Logger::getInstance().log(1,__FILE__,__LINE__,"Las animaciones de el tipoPersonaje "+ (*it).nombre +" no tienen valores válidos en su nombre.");
				tipoPersonajeOk = false;
			}

			// Chequeo la validez del período de la animación
			if ( (*it2).periodo < 0 ) {
				Logger::getInstance().log(1,__FILE__,__LINE__,"Las animaciones de el tipoPersonaje "+ (*it).nombre +" no tienen valores válidos en su periodo. Se usará un valor por defecto");
				(*it2).periodo = JUEGO_PERIODO_DEFAULT;
			}

			// Chequeo si las rutas de las animaciones son válidas
			for (list<std::string>::iterator it3=(*it2).sprites.begin() ; it3 != (*it2).sprites.end(); it3++ ){
				if ( chequeoArchivo((*it3))==false){
					Logger::getInstance().log(1,__FILE__,__LINE__,"Las animaciones de el tipoPersonaje "+ (*it).nombre +" tienen rutas de archivo inválidos.");
					tipoPersonajeOk = false;
				}
			}

			// Chequeo si, siendo el protagonista, tiene las animaciones obligatorias
			if ( (*it).nombre.compare("protagonista") == 0){ 
				anchoPjePpal = (*it).ancho; // Para validar el scroll al final de la función
				if ( (*it2).nombre.compare("quietoDerecha") == 0 ){principalQuietoDerOk = true;}
				if ( (*it2).nombre.compare("quietoIzquierda") == 0 ){principalQuietoIzqOk = true;}
				if ( (*it2).nombre.compare("caminarIzquierda") == 0 ){principalCaminarIzqOk = true;}
				if ( (*it2).nombre.compare("caminarDerecha") == 0 ){principalCaminarDerOk = true;}
			}

		} // Fin del for que recorre las animaciones de un tipoPersonaje

		// Chequeo la existencia de un protagonista (con datos válidos) con las animaciones obligatorias
		if ( (*it).nombre.compare("protagonista") == 0 && tipoPersonajeOk == true){
			if ( principalQuietoDerOk == true && principalQuietoIzqOk == true && principalCaminarIzqOk == true && principalCaminarDerOk == true ){
				existeProtagonista = true;
			}else{
				existeProtagonista = false;
				tipoPersonajeOk = false;  // Descarto el protagonista por no tener las animaciones obligatorias
			}
		}

		// Si anteriormente se encontró un problema, se descarta ese tipo personaje
		if( tipoPersonajeOk == false) tipoPersonajeBorrar.push_back(it); 

	} // Fin del for que recorre los tipoPersonaje

	// En caso de tener tipoPersonaje para descartar, lo hago aquí
	if ( tipoPersonajeBorrar.empty()==false){
		Logger::getInstance().log(1,__FILE__,__LINE__,"juego->tiposPersonaje: existen tipoPersonaje inválidos. Los mismos se descartarán.");
		for (list<list<stTipoPersonaje>::iterator>::iterator it=tipoPersonajeBorrar.begin() ; it != tipoPersonajeBorrar.end(); it++ ){
			this->juego.tiposPersonaje.erase(*it);
		}
	}

	// En caso de no existir un protagonista válido, agrego uno por defecto
	if ( existeProtagonista == false ){
		Logger::getInstance().log(1,__FILE__,__LINE__,"juego->tiposPersonaje: no tiene protagonista válido. Se agregará uno por defecto.");
		anchoPjePpal = this->getStTipoPersonajeBak("protagonista").ancho;
		this->juego.tiposPersonaje.push_front(this->getStTipoPersonajeBak("protagonista"));
	}

	// Chequeo si la lista quedó vacía (o si estaba vacía desde el principio). En teoría no tendría que suceder nunca.
	if (this->juego.tiposPersonaje.empty()==true){
		Logger::getInstance().log(1,__FILE__,__LINE__,"tipospersonaje se encuentra vacio.");
		asignarJuegoDefault();	// En este caso está todo vacío. Acá SI puedo cargar todo el dafault
		return void();
	}

	// Una vez validado el protagonista, llamo al validar del margen y retorno su valor de retorno
	this->validaParametros(anchoPjePpal);
}

void ParserYaml::validaNivelAnchoAlto(){
	if (this->juego.nivel.alto < JUEGO_PANTALLA_ALTO_MINIMO){
		Logger::getInstance().log(1,__FILE__,__LINE__,"Nivel->Alto fuera de rango. Se usará valor por defecto.");
		this->juego.nivel.alto = this->bak.nivel.alto;
	}
	if (this->juego.nivel.ancho < JUEGO_PANTALLA_ANCHO_MINIMO){
		Logger::getInstance().log(1,__FILE__,__LINE__,"Nivel->Ancho fuera de rango. Se usará valor por defecto.");
		this->juego.nivel.ancho = this->bak.nivel.ancho;
	}
}

void ParserYaml::validaNivelEscaleras(){
	
	// Lista de los tipoPersonaje que se van a borrar
	list<list<stEscalera>::iterator> escalerasBorrar;

	// Recorro todas las escaleras validando sus valores (Ahora permite escaleras mas grandes que la pantalla)
	for (list<stEscalera>::iterator it=this->juego.nivel.escaleras.begin() ; it != this->juego.nivel.escaleras.end(); it++ ){
		if( (*it).x < 0 || (*it).y < 0 || (*it).x > this->juego.nivel.ancho || (*it).y > this->juego.nivel.alto ||
			(*it).ancho < 1 || (*it).alto < 1 || existeTextura((*it).textura)==false ){
			Logger::getInstance().log(1,__FILE__,__LINE__,"Nivel->Escaleras: Se detectaron valores inválidos para una escalera.");
			escalerasBorrar.push_back(it);
		}
	}

	// Borro las escaleras inválidas
	if(escalerasBorrar.empty()==false){
		Logger::getInstance().log(1,__FILE__,__LINE__,"Nivel->Escaleras tiene valores inválidos. Los mismos se descartarán.");
		for (list<list<stEscalera>::iterator>::iterator it=escalerasBorrar.begin() ; it != escalerasBorrar.end(); it++ ){
			this->juego.nivel.escaleras.erase(*it);
		}
	}

	// Acá no hago nada, es válido un nivel sin plataformas
	if(this->juego.nivel.escaleras.empty() == true){/*Logger::getInstance().log(1,__FILE__,__LINE__,"Nivel->Escaleras se encuentra vacio.");*/}

}

void ParserYaml::validaNivelPersonajes(){
	
	// Lista de los personajes que se van a borrar
	list<list<stPersonaje>::iterator> personajesBorrar;

	// Para controlar la existencia de un protagonista
	bool estaProtagonista = false;

	// Recorro todos los personajes
	for (list<stPersonaje>::iterator it=this->juego.nivel.personajes.begin() ; it != this->juego.nivel.personajes.end(); it++ ){
		if( (*it).x < 0 || (*it).y < 0 || (*it).x > this->juego.nivel.ancho || (*it).y > this->juego.nivel.alto || existeTipoPersonaje((*it).tipo)==false ){
			Logger::getInstance().log(1,__FILE__,__LINE__,"Nivel->Personajes: Se detectaron valores inválidos para un personaje.");
			personajesBorrar.push_back(it);
		}
	}

	// Borro los personajes inválidos
	if(personajesBorrar.empty()==false){
		Logger::getInstance().log(1,__FILE__,__LINE__,"Nivel->Personajes tiene valores inválidos. Los mismos se descartarán.");
		for (list<list<stPersonaje>::iterator>::iterator it=personajesBorrar.begin() ; it != personajesBorrar.end(); it++ ){
			this->juego.nivel.personajes.erase(*it);
		}
	}

	// Recorro los personajes, en busca del protagonista
	for (list<stPersonaje>::iterator it=this->juego.nivel.personajes.begin() ; it != this->juego.nivel.personajes.end(); it++ ){
		if( (*it).tipo.compare("protagonista") == 0 ) estaProtagonista = true;
	}
	
	// Si el protagonista no está en la lista, agrego uno por default
	if( estaProtagonista == false ){
		Logger::getInstance().log(1,__FILE__,__LINE__,"Nivel->personajes no tiene protagonista válido. Se agregará uno por defecto.");
		this->juego.nivel.personajes.push_front( this->getStPersonajeBak("protagonista"));
	}
	
	// En teroría esto no tendría que pasar nunca, ya que siempre hay por lo menos un protagonista
	if(this->juego.nivel.personajes.empty() == true){Logger::getInstance().log(1,__FILE__,__LINE__,"Nivel->Personajes no tiene valores válidos.");}

}

void ParserYaml::validaNivelPlataformas(){

	// Lista de los personajes que se van a borrar
	list<list<stPlataforma>::iterator> plataformasBorrar;

	// Recorro todos las plataformas validando sus valores (Ahora permite plataformas mas grandes que la pantalla)
	for (list<stPlataforma>::iterator it=this->juego.nivel.plataformas.begin() ; it != this->juego.nivel.plataformas.end(); it++ ){
		if( (*it).x < 0 || (*it).y < 0 ||  (*it).x > this->juego.nivel.ancho || (*it).y > this->juego.nivel.alto ||
			(*it).ancho < 1 || (*it).alto < 1 || existeTextura((*it).textura)==false ){
			Logger::getInstance().log(1,__FILE__,__LINE__,"Nivel->Plataformas: Se detectaron valores inválidos para una plataforma.");
			plataformasBorrar.push_back(it);
		}
	}

	// Borro las plataformas inválidas
	if(plataformasBorrar.empty()==false){
		Logger::getInstance().log(1,__FILE__,__LINE__,"Nivel->Plataformas tiene valores inválidos. Los mismos se descartarán.");
		for (list<list<stPlataforma>::iterator>::iterator it=plataformasBorrar.begin() ; it != plataformasBorrar.end(); it++ ){
			this->juego.nivel.plataformas.erase(*it);
		}
	}

	// Acá no hago nada, es válido un nivel sin plataformas
	if(this->juego.nivel.plataformas.empty() == true){/*Logger::getInstance().log(1,__FILE__,__LINE__,"Nivel->Plataformas no tiene valores válidos.");*/}

}

void ParserYaml::asignarJuegoDefault(){
	Logger::getInstance().log(1,__FILE__,__LINE__,"Se asignará el juego por defecto.");
	this->juego = this->bak;
}

// Devuelve true si el archivo se puede abrir exitosamente
bool ParserYaml::chequeoArchivo(std::string ruta){
	std::fstream archivo;
	std::string rutaRelativa(YAML_RUTA_DIRECTORIO_IMG);
	rutaRelativa.append(ruta.c_str());

	// Abro el archivo
	archivo.open( rutaRelativa.c_str() , ios::in | ios::binary);

	// Chequeo de ruta
	if ( !(archivo.is_open()) ){
		Logger::getInstance().log(1,__FILE__,__LINE__,"Error de archivo. La ruta de archivo de imagen <"+rutaRelativa+"> es inválida.");
		return false;
	}

	// Cierro el archivo
	archivo.close();
	return true;
}

// Devuelve true si la <textura> existe en el juego parseado
bool ParserYaml::existeTextura(std::string textura){
	for (list<stTextura>::iterator it=this->juego.texturas.begin() ; it != this->juego.texturas.end(); it++ ){
		if( (*it).nombre.compare(textura)==0 ) return true;
	}
	return false;
}

// Devuelve true si el <tipoPersonaje> existe en el juego parseado
bool ParserYaml::existeTipoPersonaje(std::string tipoPersonaje){
	for (list<stTipoPersonaje>::iterator it=this->juego.tiposPersonaje.begin() ; it != this->juego.tiposPersonaje.end(); it++ ){
		if( (*it).nombre.compare(tipoPersonaje)==0 ) return true;
	}
	return false;
}

// Imprime algunos valores de la estructura
void ParserYaml::imprimirValores(ParserYaml::stJuego& st){
		std::cout << "Algunos valores cargados: \n"
		<<"juego.nivel.escaleras.front().alto: "<<st.nivel.escaleras.front().alto <<"\n"
		<<"juego.pantalla.alto: "<<st.pantalla.alto <<"\n"
		<<"juego.parametros.margenScroll: "<<st.parametros.margenScroll<<"\n"
		<<"juego.texturas.back().ruta: "<<st.texturas.back().ruta <<"\n"
		<<"juego.tiposPersonaje.back().nombre: "<<st.tiposPersonaje.back().nombre <<"\n"
		<<"juego.tiposPersonaje.back().alto: "<<st.tiposPersonaje.back().alto<< endl;
}

// Obtiene un stTipoPersonaje con <nombreTipoPersonaje> del archivo bak
ParserYaml::stTipoPersonaje ParserYaml::getStTipoPersonajeBak(string nombreTipoPersonaje){
	stTipoPersonaje tipoPersonajeTemp;
	bool valorObtenido = false;
	for (list<stTipoPersonaje>::iterator it=this->bak.tiposPersonaje.begin() ; it != this->bak.tiposPersonaje.end(); it++ ){
		if( (*it).nombre.compare(nombreTipoPersonaje)==0 ){
			tipoPersonajeTemp = (*it);
			valorObtenido = true;
		}
	}
	if ( valorObtenido == false) Logger::getInstance().log(1,__FILE__,__LINE__,"¡Error!: No se pudo asignar tipoPersonaje por defecto.");
	return tipoPersonajeTemp;
}

// Obtiene un stPersonaje con <nombrePersonaje> del archivo bak
ParserYaml::stPersonaje ParserYaml::getStPersonajeBak(string nombrePersonaje){
	stPersonaje stPersonajeTemp;
	bool valorObtenido = false;
	for (list<stPersonaje>::iterator it=this->bak.nivel.personajes.begin() ; it != this->bak.nivel.personajes.end(); it++ ){
		if( (*it).tipo.compare(nombrePersonaje)==0 ){
			stPersonajeTemp = (*it);
			valorObtenido = true;
		}
	}
	if ( valorObtenido == false) Logger::getInstance().log(1,__FILE__,__LINE__,"¡Error!: No se pudo asignar personaje por defecto.");
	return stPersonajeTemp;
}

int ParserYaml::leerYamlInt(const YAML::Node& nodo){
	bool lecturaOk = true;
	int valorInt;
	try{	
		nodo >> valorInt;
	}catch(YAML::InvalidScalar& e) {
		std::string msg;
		msg.append("Error de sintaxis YAML. Se esperaba un número entero. Parser YAML: ");
		msg.append(e.what());
		Logger::getInstance().log(1,__FILE__,__LINE__,msg);
		lecturaOk = false;
	}
	catch(YAML::Exception& e) {
		std::string msg;
		msg.append("Error de sintaxis YAML. Ocurió un error al intentar leer un número entero. Parser YAML: ");
		msg.append(e.what());
		Logger::getInstance().log(1,__FILE__,__LINE__,msg);
		lecturaOk = false;
	}
	if ( lecturaOk == false){
		return JUEGO_INT_ERROR;
	}else{
		return valorInt;
	}
}

std::string ParserYaml::leerYamlString(const YAML::Node& nodo){
	bool lecturaOk = true;
	std::string valorString;
	try{
		nodo >> valorString;
	}catch(YAML::InvalidScalar& e) {
		std::string msg;
		msg.append("Error de sintaxis YAML. Se esperaba una cadena de caracteres. Parser YAML: ");
		msg.append(e.what());
		Logger::getInstance().log(1,__FILE__,__LINE__,msg);
		lecturaOk = false;
	}
	catch(YAML::Exception& e) {
		std::string msg;
		msg.append("Error de sintaxis YAML. Ocurió un error al intentar leer una cadena de caracteres. Parser YAML: ");
		msg.append(e.what());
		Logger::getInstance().log(1,__FILE__,__LINE__,msg);
		lecturaOk = false;
	}
	if ( lecturaOk == false){
		valorString.assign("");
		return valorString;
	}else{
		return valorString;
	}
}