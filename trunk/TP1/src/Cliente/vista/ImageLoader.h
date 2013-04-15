#ifndef IMAGELOADER_H_
#define IMAGELOADER_H_

const int SCREEN_BPP = 32;

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <sstream>
#include "../../utils/Log/Log.h"
#include "../../utils/SDLgfx/SDL_rotozoom.h"
using namespace std;

class ImageLoader {
public:	
	static ImageLoader& getInstance();

	// carga una imagen, devuelve un sdl_surface que hay que destruir despues.
	SDL_Surface* load_image( std::string filename );

	// ajusta el tamaño de la imagen
	SDL_Surface* stretch(SDL_Surface* imagen, double Width, double Height);

	// devuelve un sdl_rect donde le digamos
	SDL_Rect createRect(double x, double y);

	//devuelve la pantalla
	SDL_Surface* levantarPantalla(double w, double h);

	void blanquearPantalla (SDL_Surface*);

	void rotar(int grados,string idImage, string newPosition);

	void refrescarPantalla(SDL_Surface* screen);

	bool iniciarSDL();

	void cerrarSDL();

	virtual ~ImageLoader();

private:
	ImageLoader();
	ImageLoader(const ImageLoader&);
	ImageLoader& operator =(const ImageLoader&);		

};

inline ImageLoader& ImageLoader::getInstance(){
   static ImageLoader object;
   return object;
}

#endif /* IMAGELOADER_H_ */
