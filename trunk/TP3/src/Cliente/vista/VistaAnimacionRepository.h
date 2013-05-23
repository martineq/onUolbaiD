#pragma once

#include <map>
#include "VistaAnimacion.h"

class VistaAnimacionRepository
{
public:
	static VistaAnimacionRepository& getInstance();	
	VistaAnimacion* getAnimacion(std::string nombreAnimacion);
	VistaAnimacion* agregarAnimacion(std::string nombreAnimacion, list<std::string> sprites, int periodo, double ancho, double alto, int fps, bool automatica);
	virtual ~VistaAnimacionRepository(void);
private:
	VistaAnimacionRepository(void);
	VistaAnimacionRepository(const VistaAnimacionRepository&);
	VistaAnimacionRepository& operator =(const VistaAnimacionRepository&);
	map<std::string, VistaAnimacion* > animaciones;	
};

inline VistaAnimacionRepository& VistaAnimacionRepository::getInstance(){
   static VistaAnimacionRepository object;
   return object;
}