#include "Serializadora.h"

Serializadora::Serializadora() {
	stream = new std::stringstream();
}

Serializadora::Serializadora(std::string stringSerializado)
{
	stream = new std::stringstream(stringSerializado);
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

void Serializadora::addString(std::string cadena)
{
	int size = cadena.size();
	addInt(size);
	stream->write((char*)cadena.c_str(),size);
}

void Serializadora::addStringPointer(std::string* cadena,int size)
{
	addInt(size);
	stream->write(cadena->c_str(),size);
}

std::string *Serializadora::getSerializacion()
{
	return new std::string(stream->str());
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

std::string *Serializadora::getStringPointer()
{
	int size = getInt();
	char* aux = new char[size];
	stream->read(aux,size);
	std::stringstream abc;
	abc.write(aux,size);
	std::string* cadena = new std::string(abc.str());
	delete[] aux;
	return cadena;
}

std::string Serializadora::getString()
{
	int size = getInt();
	char* aux = new char[size];
	stream->read(aux,size);
	std::stringstream abc;
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

unsigned int Serializadora::size(){
	std::string str = this->stream->str();
	unsigned int tamanio = str.size();
	return tamanio;
}

void Serializadora::nuevaSerializacion(){
	this->stream->str(std::string());		// Le inicialo con un string vacio
	this->stream->clear();					// Seteo la bandera de eof
}

void Serializadora::nuevaSerializacion(std::string stringSerializado){
	this->stream->str(stringSerializado);	// Piso lo que habia antes con el nuevo serializado
}

Serializadora::~Serializadora() {
	delete this->stream;
}
