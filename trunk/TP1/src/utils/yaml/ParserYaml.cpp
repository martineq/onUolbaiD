#include "ParserYaml.h"


ParserYaml::ParserYaml(void){
}

ParserYaml::~ParserYaml(void){
}


int ParserYaml::cargaJuego(void){
	std::ifstream archivo(YAML_RUTA_ARCHIVO_JUEGO);
	Log::getInstance().log(1,__FILE__,__LINE__,"Configuración de juego iniciada");
	if(archivo.good()==true){
		YAML::Parser parser(archivo);
		YAML::Node doc;
		parser.GetNextDocument(doc);

		for(YAML::Iterator it=doc.begin();it!=doc.end();++it) {
			std::string clave;
			clave = this->leerYamlString(it.first());
			const YAML::Node& nodo = it.second();
			Log::getInstance().log(1,__FILE__,__LINE__,"Clave <"+clave+"> Leída.");
		}

		Log::getInstance().log(1,__FILE__,__LINE__,"Configuración de juego finalizada");
	}else{
		Log::getInstance().log(1,__FILE__,__LINE__,(std::string)"Error al abrir el archivo YAML: "+YAML_RUTA_ARCHIVO_JUEGO);
	}
	return 0;
}


// Devuelve true si el archivo se puede abrir exitosamente
bool ParserYaml::chequeoArchivo(std::string ruta){
	std::fstream archivo;
	std::string rutaRelativa(YAML_RUTA_DIRECTORIO_IMG);
	rutaRelativa.append(ruta.c_str());

	// Abro el archivo
	archivo.open( rutaRelativa.c_str() , std::ios::in | std::ios::binary);

	// Chequeo de ruta
	if ( !(archivo.is_open()) ){
		Log::getInstance().log(1,__FILE__,__LINE__,"Error de archivo. La ruta de archivo de imagen <"+rutaRelativa+"> es inválida.");
		return false;
	}

	// Cierro el archivo
	archivo.close();
	return true;
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
		Log::getInstance().log(1,__FILE__,__LINE__,msg);
		lecturaOk = false;
	}
	catch(YAML::Exception& e) {
		std::string msg;
		msg.append("Error de sintaxis YAML. Ocurió un error al intentar leer un número entero. Parser YAML: ");
		msg.append(e.what());
		Log::getInstance().log(1,__FILE__,__LINE__,msg);
		lecturaOk = false;
	}
	if ( lecturaOk == false){
		return -1;
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
		Log::getInstance().log(1,__FILE__,__LINE__,msg);
		lecturaOk = false;
	}
	catch(YAML::Exception& e) {
		std::string msg;
		msg.append("Error de sintaxis YAML. Ocurió un error al intentar leer una cadena de caracteres. Parser YAML: ");
		msg.append(e.what());
		Log::getInstance().log(1,__FILE__,__LINE__,msg);
		lecturaOk = false;
	}
	if ( lecturaOk == false){
		valorString.assign("");
		return valorString;
	}else{
		return valorString;
	}
}