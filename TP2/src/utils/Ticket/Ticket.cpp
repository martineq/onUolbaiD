#include "Ticket.h"

long Ticket::contador = 0;

Ticket::Ticket(void){

}

Ticket::~Ticket(void){

}

int Ticket::pedirNumero(void){
	int numero = (int)InterlockedIncrement(&(this->contador));
	return numero;
}
