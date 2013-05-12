#pragma once

#include "VistaAnimacion.h"
#include "VistaAnimaciones.h"
#include "VistaScroll.h"
#include "../../utils/Observador/Identificable.h"
#include "../../utils/Proxy/ProxyModeloEntidad.h"	// Para usar el ProxyModeloEntidad::stEntidad

class VistaEntidad: public Identificable{

	private:		
		bool esJugador;
		bool estaCongelado;
		double x;
		double y;
		double alto;
		double ancho;
		double posicionReferenciaX;
		double posicionReferenciaY;
		double fps;
		double delay;
		double xEnPantalla;
		double yEnPantalla;
		SDL_Rect area;
		vector<string> estados;
		std::list<std::list<std::string>> listaAnimaciones;
		VistaAnimacion* animacionActual;
		VistaAnimaciones* animaciones;
		int codigoAnimacion;
		int tileX;
		int tileY;
		int tileXAnterior;
		int tileYAnterior;	
		int _id;
		bool esNecesarioRefrescar;	
		bool entraEnPantalla;

	public:
		VistaEntidad(double x,double y,double alto,double ancho,double posicionReferenciaX,double posicionReferenciaY,double fps,double delay,std::list<std::list<std::string>> listaAnimaciones,bool esJugador,int altoNivel,int anchoNivel,int id,std::string nombreEntidad);
		~VistaEntidad(void);

		void actualizar(ProxyModeloEntidad::stEntidad& entidad);
		bool verificarBordePantalla(VistaScroll* scroll);
		int id();

		// Getters
		bool getEsJugador(void);
		double getX(void);
		double getY(void);
		double getAlto(void);
		double getAncho(void);
		double getPosRefX(void);
		double getPosRefY(void);
		double getFps(void);
		double getDelay(void);
		int getTileX();
		int getTileY();
		int getTileXAnterior();
		int getTileYAnterior();
		int getCodigoAnimacion(void);
		std::list<std::list<std::string>> getListaAnimaciones(void);
		bool getEsNecesarioRefrescar(void);
		bool getEstaCongelado();
		
		// Setters
		void setXEnPantalla(double scrollX);
		void setYEnPantalla(double scrollY);
		void setEsNecesarioRefrescar(bool boolRefrescar);
		void setAnimacion(std::string estado);
		void setPosicionAnteriorEnTiles();	
		bool graficar(char visibilidad);
		void setPantalla(SDL_Surface* screen);
		void setEstaCongelado(bool estado);
};
