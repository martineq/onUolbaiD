#include "Hilo.h"

long Hilo::contador = 0;

Hilo::Hilo(){
	this->id = (int)InterlockedIncrement(&(this->contador));  // Genera un ID
}

int Hilo::getId(void){
    return (this->id);
}

int Hilo::start(void* arg) {

	stParametro* p = new stParametro();
	p->punteroThis = (void*)this;
	p->parametro = arg;

	int error = pthread_create(&this->thread, NULL, rutina, (void*)p);
	return error;
}

void* Hilo::rutina(void* parametro) {

	Hilo *hilo = (Hilo*)((stParametro*)parametro)->punteroThis;
	hilo->run(((stParametro*)parametro)->parametro);

	delete parametro;

	return NULL;
}

void* Hilo::join() {

	void *retorno;
	if ( pthread_join(thread, &retorno) != 0 ){
		std::cout << "Error al cerrar hilo.\n";
	}
	return retorno;

}

Hilo::~Hilo() {

}