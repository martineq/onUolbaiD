#include "Hilo.h"

Hilo::Hilo(){
	this->id = Ticket::getInstance().pedirNumero();
}

int Hilo::getId(void){
    return (int)this->id;
}

int Hilo::start(void* arg) {

	stParametro* p = new stParametro();
	p->punteroThis = (void*)this;
	p->parametro = arg;

	//std::cout << "Comienza el hilo de ID: " << this->id << std::endl;

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
		std::cerr << "Error al cerrar hilo.\n";
	}
	//std::cout << "Cierra el hilo de ID: " << this->id << std::endl;
	return retorno;
}

Hilo::~Hilo() {

}

