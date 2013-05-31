#pragma once

// ************************************************************************************* //
// Esta clase no pertenece al proyecto. Es sólo para correr pruebas de distintas clases. //
// Sirve para poner ese código acá en vez de dejarlo mezclado con el código del proyecto //
// ************************************************************************************* //

#include <SDL.h>
#include <SDL_mixer.h>
#include "../Constantes/Constantes.h"
#include "../Log/log.h"
#include "../yaml/ParserYaml.h"
#include "../../Servidor/modelo/ModeloEntidad.h"
#include "./HiloDePrueba.h"
#include "../../Cliente/vista/VistaAnimacion.h"
#include "../../Cliente/vista/VistaAnimaciones.h"
#include "../../Cliente/vista/VistaEntidad.h"
#include "../SDLgfx/SDL_gfxPrimitives.h"
#include "../../Cliente/vista/VistaChat.h"
#include "../../Cliente/controlador/DetectorEventos.h"
#include "../LectorDirectorios/LectorDirectorios.h"
#include "../Proxy/ProxyControladorEvento.h"

class Pruebas{

	private:

		void dibujarTriangulos(SDL_Surface* pantalla, int alto,int ancho,
				int supAIni,int supAFin,int supBIni,int supBFin,int derAIni,int derAFin,int derBIni,int derBFin,
				int infAIni,int infAFin,int infBIni,int infBFin,int izqAIni,int izqAFin,int izqBIni,int izqBFin,
				int rojo, int verde, int azul,int alfa);

	public:

		Pruebas(void);
		~Pruebas(void);
		void PruebaMusica();
		void PruebaSdl(void);
		void PruebaYAML(void);
		void PruebaModeloEntidad(void);
		void PruebaHilos(void);
		void PruebaAnimacion(void);
		void PruebaSockets(void);
		void PruebaServidorChat();
		void PruebaClienteChat();
};