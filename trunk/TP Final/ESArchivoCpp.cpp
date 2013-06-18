#include "ESArchivoCpp.h"

ESArchivoCpp::ESArchivoCpp(const char* ruta, bool esEntrada, bool esTexto){
	this->abrirArchivo(ruta,esEntrada,esTexto);
}

ESArchivoCpp::ESArchivoCpp(void){
}

ESArchivoCpp::~ESArchivoCpp(void){
	if( this->archivo.is_open() ) archivo.close();
}

void ESArchivoCpp::abrirArchivo(const char* ruta, bool esEntrada, bool esTexto){
	if( esEntrada == true ){
		if( esTexto == true ){
			this->archivo.open(ruta,std::ios::in);
		}else{
			this->archivo.open(ruta,std::ios::in | std::ios::binary);
		}
	}else{
		if( esTexto == true ){
			this->archivo.open(ruta,std::ios::out);
		}else{
			this->archivo.open(ruta,std::ios::out | std::ios::binary);
		}
	}
	return void();
}

// Lee el tamanio pedido, desde el offset pedido, en memoria ya instanciada
void ESArchivoCpp::leerArchivo(char* cadena, unsigned long offset, unsigned long tamanio){
	
	if( this->archivo.is_open() ){
		this->archivo.seekg(offset,std::ios::beg);
		if( tamanio > 0 ) this->archivo.read(cadena,tamanio);
	}

	return void();
}

// Lee todo el archivo en memoria instanciada por la propia función. Devuelve el tamaño total
unsigned long ESArchivoCpp::leerArchivo(char** cadena){
	unsigned long tamanio = 0;

	if( this->archivo.is_open() ){
		this->archivo.seekg(0,std::ios::end);
		tamanio = this->archivo.tellg();
		this->archivo.seekg(0,std::ios::beg);
		if( tamanio > 0 ){
			(*cadena) = new char[tamanio];
			this->archivo.read((*cadena),tamanio);
		}
	}

	return tamanio;
}

// Lee todo el archivo y lo devuelve cargado en un std::string
std::string ESArchivoCpp::leerArchivo(void){
	std::string cadenaStr;
	char* cadena;

	unsigned int tamanio = this->leerArchivo(&cadena);
	if( tamanio > 0 ){
		cadenaStr.assign(cadena,tamanio);
	}

	return cadenaStr;
}

// Escribre en el archivo el tamanio pedido, desde el offset pedido
void ESArchivoCpp::escribirEnArchivo(const char* cadena, unsigned long offset, unsigned long tamanio){
	this->archivo.seekp(offset,std::ios::beg);
	this->archivo.write(cadena,tamanio);
}

// Escribre en el archivo el tamanio pedido, desde la posición que se encontraba el archivo
void ESArchivoCpp::escribirEnArchivo(const char* cadena, unsigned long tamanio){
	this->archivo.write(cadena,tamanio);
}

// Escribre en el archivo los datos contenidos en el string, desde la posición que se encontraba el archivo
void ESArchivoCpp::escribirEnArchivo(std::string cadena){
	this->archivo << cadena.c_str();
}
