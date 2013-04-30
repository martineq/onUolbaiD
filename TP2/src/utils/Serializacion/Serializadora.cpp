#include "Serializadora.h"

Serializadora::Serializadora() {
	stream = new stringstream();
}

Serializadora::Serializadora(string *stringSerializado)
{
	stream = new stringstream(*stringSerializado);
}

void Serializadora::addInt(int valor)
{
	stream->write((char*)&valor,TAM_INT);
}

void Serializadora::addDouble(double valor)
{
	stream->write((char*)&valor,TAM_DBL);
}

void Serializadora::addBool(bool valor)
{
	stream->write((char*)&valor,TAM_BOOL);
}

void Serializadora::addString(string cadena)
{
	int size = cadena.size();
	addInt(size);
	stream->write((char*)cadena.c_str(),size);
}


void Serializadora::addStringPointer(string* cadena,int size)
{
	addInt(size);
	stream->write(cadena->c_str(),size);
}

string *Serializadora::getSerializacion()
{
	return new string(stream->str());
}

int Serializadora::getInt()
{
	int valor;
	stream->read((char*)&valor,TAM_INT);
	return valor;
}

bool Serializadora::getBool()
{
	bool valor;
	stream->read((char*)&valor,TAM_BOOL);
	return valor;
}


string *Serializadora::getStringPointer()
{
	int size = getInt();
	char* aux = new char[size];
	stream->read(aux,size);
	stringstream abc;
	abc.write(aux,size);
	string* cadena = new string(abc.str());
	delete[] aux;
	return cadena;
}

string Serializadora::getString()
{
	int size = getInt();
	char* aux = new char[size];
	stream->read(aux,size);
	stringstream abc;
	abc.write(aux,size);
	delete[] aux;
	return abc.str();
}

void Serializadora::addShortInt(short int valor)
{
	stream->write((char*)&valor,TAM_SINT);
}

short int Serializadora::getShortInt()
{
	short int valor;
	stream->read((char*)&valor,TAM_SINT);
	return valor;
}

double Serializadora::getDouble()
{
	double valor;
	stream->read((char*)&valor,TAM_DBL);
	return valor;
}

void Serializadora::addUnsignedInt(unsigned int valor)
{
	stream->write((char*)&valor,sizeof(unsigned int));
}

unsigned int Serializadora::getUnsignedInt()
{
	unsigned int valor;
	stream->read((char*)&valor,sizeof(unsigned int));
	return valor;
}

Serializadora::~Serializadora() {
	delete stream;
}


