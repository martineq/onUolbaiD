#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <stdlib.h>
#include "../Constantes.h"

/* Clase encargada de generar y gestionar el Log de la aplicacion.*/

class Log{

	private: 

		std::ofstream* archLog; 
		
		/*Los constructores permanecen ocultos, para evitar que sea instanciado desde 
		 *cualquier lugar y generar multiples archivos de Log.*/
		Log();
		Log(const Log&);
		Log& operator =(const Log&);

    public:
		/*El siguiente metodo es utilizado como parte del patron Singleton para devolver una instancia del Log.
		 *Si nunca fue ejecutada la aplicacion, se creara un archivo de log y se devolvera listo para ser usado.
		 *Si ya se tiene creado el archivo y se lo solicita usar dsde otro lugar de la aplicacion, por cada 
		 *solicitud de uso (cada vez que se necesite loguear algo) no se creara un nuevo archivo sino que se 
		 *devuelve un puntero al archivo existende para continuar escribiendo en el (append) manteniendo asi,
		 * un unico Log que reuna la totalidad de mensajes sobre el juego.*/
		static Log& getInstance();

		/*Inserta en el archivo un registsro de texto.
		<nivel>		Nivel de Logueo, sirve para filtrar distintos conjuntos de logueos. 
		            Nivel 1: Release, Nivel 2: Debug Bajo, Nivel 3: Debug Alto.
					El nivel elegido incluye los niveles inferiores.
					Se pueden habilitar niveles mas altos si fuera necesario. 
		<archivo>	Nombre del archivo del cual sale el mensaje de logueo.
		<linea>		Numero de linea del archivo del cual sale el mensaje de logueo.
		<mensaje>	Breve descripcion de lo que esta sucediendo.   */
		void log(int nivel, std::string archivo, std::string linea, std::string mensaje);

		void log(int nivel, std::string archivo, int linea, std::string mensaje); 
		void log(int nivel, std::string archivo, int linea, std::string mensaje, int valor);
		void log(int nivel, std::string archivo, int linea, std::string mensaje, unsigned int valor);
		void log(int nivel, std::string archivo, int linea, std::string mensaje, double valor);
		void log(int nivel, std::string archivo, int linea, std::string mensaje, std::string valor);
		void log(int nivel, std::string archivo, int linea, std::string mensaje, long valor);

		// Otras funciones
		std::string obtenerNombreDesdeRuta(std::string rutaCompleta);
		virtual ~Log();

};

// La declaracion de la obtencion de instancia se hace en el mismo .h
inline Log& Log::getInstance(){
	static Log object;
	return object;
}

