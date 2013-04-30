#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include "../Constantes/Constantes.h"

using std::string;
using std::stringstream;
using std::cout;
using std::endl;

class Serializadora{

	private:
		stringstream*	stream;

	public:
		/*
		 * Instancia para serializar
		 */
		Serializadora();

		/*
		 * Instancia para deserializar.
		 */
		Serializadora(string* stringSerializado);

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
		void addString(string cadena);

		void addStringPointer(string* cadena, int size);
		/*
		 * Devuelve el resultado de la serializacion.
		 */
		string* getSerializacion();

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
		string*	getStringPointer();

		/*
		 * Devuelve un string.
		 */
		string	getString();

		virtual ~Serializadora();
		
};
