#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "../Constantes/Constantes.h"

class Serializadora{

	private:
		std::stringstream* 	stream;

	public:
		/*
		 * Instancia para serializar
		 */
		Serializadora();

		/*
		 * Instancia para deserializar.
		 */
		Serializadora(std::string stringSerializado);

		/*
		 * Agrega un int al stream.
		 */
		void addInt(int valor);

		/*
		 * Agrega un short int al stream.
		 */
		void addShortInt(short int valor);

		/*
		 * Agrega un short int al stream.
		 */
		void addDouble(double valor);

		/*
		 * Agrega un unsigned int.
		 */
		void addUnsignedInt(unsigned int valor);

		/*
		 * Agrega un bool al stream.
		 */
		void addBool(bool valor);

		/*
		 * Agrega un string al stream.
		 */
		void addString(std::string cadena);

		void addStringPointer(std::string* cadena, int size);
		/*
		 * Devuelve el resultado de la serializacion.
		 */
		std::string* getSerializacion();

		/*
		 * Devuelve un int.
		 */
		int		getInt();

		/*
		 * Obtiene un short int del stream.
		 */
		short int getShortInt();

		/*
		 * Obtiene un double del stream.
		 */
		double getDouble();

		/*
		 * Obtiene un bool del stream.
		 */
		bool getBool();

		/*
		 * Obtiene un unsigned int del stream.
		 */
		unsigned int getUnsignedInt();

		/*
		 * Devuelve un string, debe ser liberado luego de ser usado.
		 */
		std::string*	getStringPointer();

		/*
		 * Devuelve un string.
		 */
		std::string	getString();

		/*
		 * Devuelve el tamaño total de lo serializado.
		 */
		unsigned int size();

		/*
		 * Idem al constructor Serializadora(). Sirve para reusar la instancia si quiero hacer una nueva serialización
		 * Elimina el contenido anterior existente.
		 */
		void nuevaSerializacion();

		/*
		 * Idem al constructor Serializadora(string* stringSerializado). Sirve para reusar la instancia si quiero hacer una nueva hidratacion
		 * Elimina el contenido anterior existente.
		 */
		void nuevaSerializacion(std::string stringSerializado);

		virtual ~Serializadora();
		
};
