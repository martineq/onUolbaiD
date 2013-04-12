#include "./VistaLoop.h"

VistaLoop::VistaLoop(void){
	
}

void VistaLoop::setPantalla(SDL_Surface *pantalla){
	this->pantalla = pantalla;
}

bool VistaLoop::loop(VistaNivel& vistaNivel){
	this->dibujarPantalla(vistaNivel);

	return true;	// TODO: Implementar este return
}

//levanta el fondo y la pantalla
bool VistaLoop::levantarPantalla(int altoPantalla, int anchoPantalla){

	this->fondo = ImageLoader::getInstance().load_image(SDL_RUTA_FONDO);	

	return true; // TODO: Implementar el return del método
}

void VistaLoop::dibujarPantalla(VistaNivel& vistaNivel){
	// Cargo el fondo
	// TODO: Ver estas lineas
	SDL_Rect rcFondo = ImageLoader::getInstance().createRect(0,0);
	SDL_BlitSurface(this->fondo, NULL, this->pantalla, &rcFondo);

	list<VistaEntidad*> listaDeEntidades = vistaNivel.getListaEntidades();	
	list<VistaEntidad*>::iterator it = listaDeEntidades.begin();
	while (it != listaDeEntidades.end()){
		VistaEntidad* unaEntidad = *it;
		//Es necesario actualizar o porque cambio de posicion o porque se actualizo el scroll
		if ( (vistaNivel.getScroll()->getEsNecesarioRefrescar() == true ) || (unaEntidad->getEsNecesarioRefrescar() == true) ){
			unaEntidad->setXEnPantalla(vistaNivel.getScroll()->getX());
			unaEntidad->setYEnPantalla(vistaNivel.getScroll()->getY());
			unaEntidad->setEsNecesarioRefrescar(false);
			vistaNivel.getScroll()->setEsNecesarioRefrescar(false);
		}
		unaEntidad->setPantalla(this->pantalla);
		unaEntidad->graficar();
		it++;
	}
	ImageLoader::getInstance().refrescarPantalla(this->pantalla);
}

VistaLoop::~VistaLoop(void){
	SDL_FreeSurface(this->pantalla);
	SDL_FreeSurface(this->fondo);	
	ImageLoader::getInstance().cerrarSDL();	
}