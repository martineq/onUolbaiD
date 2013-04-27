#include "VistaAnimacionRepository.h"

VistaAnimacionRepository::VistaAnimacionRepository(void)
{
}

VistaAnimacionRepository::VistaAnimacionRepository(const VistaAnimacionRepository&){
}

VistaAnimacion* VistaAnimacionRepository::getAnimacion(std::string nombreAnimacion){
	map<std::string, VistaAnimacion* >::iterator it = this->animaciones.find(nombreAnimacion);
	VistaAnimacion* animacion = NULL;
	if (it != this->animaciones.end()) {
		animacion = (*it).second;
	}
	return animacion;
}

VistaAnimacion* VistaAnimacionRepository::agregarAnimacion(std::string nombreAnimacion, list<std::string> sprites, int periodo, double ancho, double alto, int fps, bool automatica){
	VistaAnimacion* animacion = this->getAnimacion(nombreAnimacion);
	if (animacion == NULL){
		animacion = new VistaAnimacion(sprites, periodo, ancho, alto,automatica, fps);
		this->animaciones.insert(std::make_pair(nombreAnimacion, animacion));				
	}
	return animacion;
}

VistaAnimacionRepository::~VistaAnimacionRepository(void)
{
	map<std::string, VistaAnimacion* >::iterator it;
	for (it=this->animaciones.begin();it!=this->animaciones.end();it++) {
		VistaAnimacion* animacion = (*it).second;
		if (animacion != NULL){
			delete animacion;
			(*it).second = NULL;
			 //delete animacion;
		}
	}

}
