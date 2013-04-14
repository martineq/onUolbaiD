#include "./VistaLoop.h"

VistaLoop::VistaLoop(void){
	this->pantalla = NULL;
	this->fondo = NULL;
}

void VistaLoop::setPantalla(SDL_Surface *pantalla){
	this->pantalla = pantalla;
}

bool VistaLoop::loop(VistaNivel& vistaNivel){
	this->dibujarEntidades(vistaNivel);

	return true;	// TODO: Implementar este return
}

//levanta el fondo y la pantalla
bool VistaLoop::levantarFondo(double altoNivel, double anchoNivel){

	this->fondo = ImageLoader::getInstance().load_image(SDL_RUTA_FONDO);	
	this->fondo = ImageLoader::getInstance().stretch(this->fondo,anchoNivel,altoNivel);

	return true; // TODO: Implementar el return del método
}

void VistaLoop::dibujarEntidades(VistaNivel& vistaNivel){
	// Cargo el fondo
	// TODO: Ver estas lineas
	SDL_Rect rcFondo = ImageLoader::getInstance().createRect(0,0);
	SDL_Rect rc = ImageLoader::getInstance().createRect(vistaNivel.getScroll()->getX(),vistaNivel.getScroll()->getY());
	SDL_BlitSurface(this->fondo, &rc, this->pantalla, &rcFondo);

	list<VistaEntidad*> listaDeEntidades = vistaNivel.getListaEntidades();	
	list<VistaEntidad*>::iterator it = listaDeEntidades.begin();
	while (it != listaDeEntidades.end()){
		VistaEntidad* unaEntidad = *it;
		//Es necesario actualizar o porque cambio de posicion o porque se actualizo el scroll
		
		if ( (vistaNivel.getScroll()->getEsNecesarioRefrescar() == true ) ){
			unaEntidad->setXEnPantalla(vistaNivel.getScroll()->getX());
			unaEntidad->setYEnPantalla(vistaNivel.getScroll()->getY());
			vistaNivel.getScroll()->setEsNecesarioRefrescar(false);
		}

		if ( (unaEntidad->getEsNecesarioRefrescar() == true) ){
			unaEntidad->setXEnPantalla(unaEntidad->getX());
			unaEntidad->setYEnPantalla(unaEntidad->getY());
			unaEntidad->setEsNecesarioRefrescar(false);			
		}
		
		//Si no cambio de posicion ni se movió el scroll igual grafica.
		unaEntidad->setPantalla(this->pantalla);
		unaEntidad->graficar();
		it++;
	}
	ImageLoader::getInstance().refrescarPantalla(this->pantalla);
}

VistaLoop::~VistaLoop(void){
	if( this->pantalla != NULL ) SDL_FreeSurface(this->pantalla);
	if( this->fondo != NULL ) SDL_FreeSurface(this->fondo);	
	ImageLoader::getInstance().cerrarSDL();	
}
