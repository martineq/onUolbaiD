#pragma once

#include "VistaAnimacion.h"
#include "VistaAnimaciones.h"
#include "VistaScroll.h"
#include "VistaMusica.h"
#include "../../utils/Observador/Identificable.h"
#include "../../utils/Proxy/ProxyModeloEntidad.h"

class VistaEntidad: public Identificable{

	private:		
		bool esJugador;
		bool esMiJugador;
		bool estaCongelado;
		bool esNecesarioRefrescar;
		bool tieneMapa;
		bool esUltimoMovimiento;
		bool sufrioDanio;
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
		std::string nombreEntidad;
		std::string nombreJugador;
		VistaAnimacion* animacionActual;
		VistaAnimaciones* animaciones;
		int codigoAnimacion;
		int tileX;
		int tileY;
		int tileXAnterior;
		int tileYAnterior;	
		int _id;
		int vida;
		int rangoVision;	

		void actualizarEventosSonido(std::string entidad, bool sufrioDanio, bool murio);

	public:
		VistaEntidad(double x,double y,double alto,double ancho,double posicionReferenciaX,double posicionReferenciaY,int rangoVisible,double fps,double delay,std::list<std::list<std::string>> listaAnimaciones,bool esJugador,int altoNivel,int anchoNivel,int id,std::string nombreEntidad,bool estaCongelado,int estado,std::string nombreJugador);
		~VistaEntidad(void);

		void actualizar(ProxyModeloEntidad::stEntidad& entidad);
		bool verificarBordePantalla(VistaScroll* scroll);
		int id();

		// Getters		
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
		int getRangoVision();		
		bool getEsNecesarioRefrescar(void);		
		bool getEsUltimoMovimiento();
		bool getEstaCongelado();
		bool getTieneMapa();
		bool getEsJugador(void);
		bool getEstaVivo();
		bool getSufrioDanio();
		std::string getNombreEntidad();
		std::string getNombreJugador();
		std::list<std::list<std::string>> getListaAnimaciones(void);	

		// Setters
		void setXEnPantalla(double scrollX);
		void setYEnPantalla(double scrollY);
		void setEsNecesarioRefrescar(bool boolRefrescar);
		void setAnimacion(std::string estado);
		void setPosicionAnteriorEnTiles();			
		void setPantalla(SDL_Surface* screen);
		void setEstaCongelado(bool estado);
		void setEsMiJugador(bool valor);
		bool graficar(char visibilidad);

};
