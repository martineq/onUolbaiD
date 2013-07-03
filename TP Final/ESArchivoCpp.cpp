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
bool ESArchivoCpp::leerLinea(std::string& linea){
	if( std::getline(this->archivo,linea) ){
		return true;
	}else{
		linea.clear();
		return false;
	}
}

// Escribe en el archivo el tamanio pedido, desde el offset pedido
void ESArchivoCpp::escribirEnArchivo(const char* cadena, unsigned long offset, unsigned long tamanio){
	this->archivo.seekp(offset,std::ios::beg);
	this->archivo.write(cadena,tamanio);
}

// Escribe en el archivo el tamanio pedido, desde la posición que se encontraba el archivo
void ESArchivoCpp::escribirEnArchivo(const char* cadena, unsigned long tamanio){
	this->archivo.write(cadena,tamanio);
}

// Escribe en el archivo los datos contenidos en el string, desde la posición que se encontraba el archivo
void ESArchivoCpp::escribirLinea(std::string linea){
	this->archivo << linea.c_str();
}

/* ///// Resumen de manejo de archivos /////

// Creo y abro el archivo
std::fstream archivo; 
archivo.open(ruta,std::ios::in); // "std::ios::out" para salida y " | std::ios::binary " para archivos binarios

// Leo un archivo de texto con varias líneas y varios valores en cada línea separado por ","
std::string linea;
while( std::getline(archivo,linea) ){ 
	std::stringstream ssl(linea);		// Lo paso a stringstream para luego poder usar std::getline
	std::string valor;
	int indice = 1;
	int valorUno,valorDos;
	while( std::getline(ssl,valor,',') ){
		std::stringstream ssv(valor);	// Lo paso a stringstream para luego poder pasarlo a <int>, <double>, etc.
		if( indice == 1 ) ssv >> valorUno;
		if( indice == 2 ) ssv >> valorDos;
		indice++;
	}
}

// Leo un archivo binario // Con char* cadena; unsigned long offset; unsigned long tamanio;
if( this->archivo.is_open() ){
	this->archivo.seekg(offset,std::ios::beg);
	if( tamanio > 0 ) this->archivo.read(cadena,tamanio);
}

// Escribo en el archivo el tamanio pedido, desde el offset pedido. Modo binario
this->archivo.seekp(offset,std::ios::beg);
this->archivo.write(cadena,tamanio);

// Escribo en el archivo una línea en modo texto
this->archivo << linea.c_str();

// Cierro el archivo
if( this->archivo.is_open() ) archivo.close();

*/