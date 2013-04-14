#include "./VistaLoop.h"

VistaLoop::VistaLoop(void){
	this->pantalla = NULL;
	this->fondo = NULL;
}

void VistaLoop::setPantalla(SDL_Surface *pantalla){
	this->pantalla = pantalla;
}

bool VistaLoop::loop(VistaNivel& vistaNivel){
	if( this->dibujarEntidades(vistaNivel) == false) return false;

	return true;
}

// Levanta el fondo y la pantalla
bool VistaLoop::levantarFondo(double altoNivel, double anchoNivel){

	this->fondo = ImageLoader::getInstance().load_image(SDL_RUTA_FONDO);	
	if( this->fondo == NULL ) return false;
	
	this->fondo = ImageLoader::getInstance().stretch(this->fondo,anchoNivel,altoNivel);
	if( this->fondo == NULL ) return false;

	return true;
}

bool VistaLoop::dibujarEntidades(VistaNivel& vistaNivel){
	// Cargo el fondo
	// TODO: Ver estas lineas
	SDL_Rect rcFondo = ImageLoader::getInstance().createRect(0,0);
	SDL_Rect rc = ImageLoader::getInstance().createRect(vistaNivel.getScroll()->getX(),vistaNivel.getScroll()->getY());
	if( SDL_BlitSurface(this->fondo, &rc, this->pantalla, &rcFondo) != 0 ) return false;

	list<VistaEntidad*> listaDeEntidades = vistaNivel.getListaEntidades();	
	list<VistaEntidad*>::iterator it = listaDeEntidades.begin();
	while (it != listaDeEntidades.end()){
		VistaEntidad* unaEntidad = *it;
		//Es necesario actualizar o porque cambio de posicion o porque se actualizo el scroll
		
		if ( (vistaNivel.getScroll()->getEsNecesarioRefrescar() == true ) ){
			unaEntidad->verificarBordePantalla(vistaNivel.getScroll());
			vistaNivel.getScroll()->setEsNecesarioRefrescar(false);
		}

		unaEntidad->setPantalla(this->pantalla);
		if( unaEntidad->graficar() == false ) return false;
		it++;
	}

	if ( (vistaNivel.getScroll()->getEsNecesarioRefrescar() == true ) ){	
		vistaNivel.getScroll()->setEsNecesarioRefrescar(false);
	}

	ImageLoader::getInstance().refrescarPantalla(this->pantalla);

	return true;
}

VistaLoop::~VistaLoop(void){
	if( this->pantalla != NULL ) SDL_FreeSurface(this->pantalla);
	if( this->fondo != NULL ) SDL_FreeSurface(this->fondo);	
	ImageLoader::getInstance().cerrarSDL();	
}
