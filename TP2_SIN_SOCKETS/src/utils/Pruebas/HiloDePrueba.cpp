#include "HiloDePrueba.h"

HiloDePrueba::HiloDePrueba(void){

}

HiloDePrueba::~HiloDePrueba(void){

}

void* HiloDePrueba::run(void* parametro){

	for(unsigned int i=0;i<10;i++){
		std::stringstream ss;
		ss<<"Soy el hilo con ID: "<< this->getId() <<" Emito el valor: "<< i <<std::endl;
		std::cout<<ss.str();
	}

	return NULL;
}
