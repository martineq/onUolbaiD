#include "LectorDirectorios.h"

LectorDirectorios::LectorDirectorios(void){
}

LectorDirectorios::~LectorDirectorios(void){
}

// Devuelve todos los nombres de archivos encontrados en el directorio <rutaDirectorio> dado
// El formato del directorio es Ej: "c:/dir1/dirElegido" (Absoluto) ó "/dir1/dirElegido" (Relativo)
// IMPORTANTE: Sin barras al final de la ruta
std::vector<std::string> LectorDirectorios::leerDirectorio(const char* rutaDirectorio){

	// Un struct y un handle para leer los archivos
	WIN32_FIND_DATA estructuraFindData;
	HANDLE manejadorBuscar = INVALID_HANDLE_VALUE;

	// Variable que guarda todos los nombres de archivo
	std::vector<std::string> nombresDeArchivo;

	// Ruta del directorio donde se va a buscar
	std::string rutaBusqueda(rutaDirectorio);
	rutaBusqueda.append("\\*"); // Para que lea todos los archivos del directorio indicado

	// Variable para guardar la ruta del directorio completa (con la barra "\")
	std::string rutaDir(rutaDirectorio);
	rutaDir.append("/");

	// Variable para guardar la ruta completa
	std::string rutaCompleta;

	// Leo por primera vez y entro a cargar si no hubo errores
	manejadorBuscar = FindFirstFile(rutaBusqueda.c_str(), &estructuraFindData);
	if(manejadorBuscar  != INVALID_HANDLE_VALUE){

		// Agrego el primero
		if(estructuraFindData.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY){
			if( this->nombreValido(estructuraFindData.cFileName) ){
				rutaCompleta.assign(rutaDir);
				rutaCompleta.append(estructuraFindData.cFileName);
				nombresDeArchivo.push_back(rutaCompleta);
			}
		}

		while(FindNextFile(manejadorBuscar, &estructuraFindData)){

			// Agrego los demas
			if(estructuraFindData.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY){
			
				if( this->nombreValido(estructuraFindData.cFileName) ){
					rutaCompleta.assign(rutaDir);
					rutaCompleta.append(estructuraFindData.cFileName);
					nombresDeArchivo.push_back(rutaCompleta);
				}

			}

		}

		FindClose(manejadorBuscar);
	}

	return nombresDeArchivo;
}

bool LectorDirectorios::nombreValido(std::string nombre){

	if( nombre.compare(".") == 0 ){ return false;
	}else if( nombre.compare("..") == 0 ){ return false;
	}else if( nombre.compare(".svn") == 0 ){ return false;
	}else if( nombre.compare("thumbs.db") == 0 ){ return false; }

	return true;
}