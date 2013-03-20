#include "ParserYaml.h"


ParserYaml::ParserYaml(void){

}

ParserYaml::~ParserYaml(void){

}


int ParserYaml::cargaJuego(void){

	std::ifstream archivo(YAML_RUTA_ARCHIVO_JUEGO);
	Log::getInstance().log(1,__FILE__,__LINE__,"Configuración de juego iniciada");

	// Si pude abrir el archivo yaml, empiezo a parsear
	if(archivo.good()==true){

		YAML::Parser parser(archivo);	// Archivo YAML
		YAML::Node doc;					// Nodo para el primer elemento
		parser.GetNextDocument(doc);	// Obtengo el nodo

		// Itero por todos los nodos que tenga el documento, acá hago proceso necesario para obtener los datos
		for(YAML::Iterator it=doc.begin();it!=doc.end();++it) {
			std::string clave;
			clave = this->leerNodoYamlString(it.first());
			const YAML::Node& nodo = it.second();
			Log::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> Leída."); // Por ahora el proceso es solo imprimir que es lo que leí
		}

		Log::getInstance().log(1,__FILE__,__LINE__,"Configuración de juego finalizada");
	}else{
		// Si no pude abrir el archivo lo reporto
		Log::getInstance().log(1,__FILE__,__LINE__,(std::string)"Error al abrir el archivo YAML: "+YAML_RUTA_ARCHIVO_JUEGO);
	}

	return 0;
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
		this->notificarErrorLectura("entero",e.what(),lecturaOk);
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
		this->notificarErrorLectura("cadena de caracteres",e.what(),lecturaOk);
	}
	
	if ( lecturaOk == false){
		valorString.assign("");
		return valorString;
	}else{
		return valorString;
	}
}

void ParserYaml::notificarErrorLectura(std::string tipoDato, std::string msgError, bool& lecturaOk){
		std::string msg;
		msg.append("Error de sintaxis YAML. Ocurió un error al intentar leer un dato del tipo ");
		msg.append(tipoDato);
		msg.append(" . Reporte del parser YAML: ");
		msg.append(msgError);
		Log::getInstance().log(1,__FILE__,__LINE__,msg);
		lecturaOk = false;
}