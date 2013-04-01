#ifndef IMAGELOADER_H_
#define IMAGELOADER_H_
#include <SDL.h>
#include <SDL_image.h>
//#include <SDL_main.h>
#include "../../utils/SDLgfx/SDL_rotozoom.h"
#include <string>
#include "../../utils/Log/Log.h"

using namespace std;

class ImageLoader {
public:	
	static ImageLoader& getInstance();

	SDL_Surface* load_image( std::string filename );

	SDL_Surface* stretch(SDL_Surface* imagen, double Width, double Height);

	SDL_Rect createRect(double x, double y);

	SDL_Surface* levantarPantalla(double w, double h);

	bool iniciarSDL();

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
