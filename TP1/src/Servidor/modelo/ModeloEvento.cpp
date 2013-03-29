#include "ModeloEvento.h"

ModeloEvento::ModeloEvento(void){

}

ModeloEvento::~ModeloEvento(void){

}

void ModeloEvento::actualizar(class Observable* s){

	// En este punto ya se que el parámetro <s> se puede castear a ((ControladorEvento*)s)

    // Actualizo datos, por ejemplo...
	// this->tipoEvento = ((ControladorEvento*)s)->obtenerTipoEvento();
	//...completar con lo necesario

}