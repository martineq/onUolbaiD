#include "ImageLoader.h"

ImageLoader::ImageLoader() {

}

ImageLoader::ImageLoader(const ImageLoader&){
}

SDL_Surface *ImageLoader::load_image( std::string filename )
{
	//The image that's loaded
	SDL_Surface* loadedImage = NULL;
	map<std::string, SDL_Surface* >::iterator it = this->surfaces.find(filename);
	if (it != this->surfaces.end()) {
		loadedImage = (*it).second;
	}

	if (loadedImage == NULL){

		//The optimized surface that will be used
		SDL_Surface* optimizedImage = NULL;
	
		//Load the image
		loadedImage = IMG_Load( filename.c_str() );

		//If the image loaded
		if( loadedImage == NULL ){
			Log::getInstance().log(1,__FILE__,__LINE__,"No se cargará la siguiente imagen:");
			Log::getInstance().log(1,__FILE__,__LINE__,filename);
			loadedImage = IMG_Load( SDL_IMAGEN_DEFAULT );
		}

		//Create an optimized surface
		optimizedImage = SDL_DisplayFormat( loadedImage );

		//Free the old surface
		SDL_FreeSurface( loadedImage );

		//If the surface was optimized
		if( optimizedImage != NULL )
		{
			//Color key surface
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0xFF, 0xFF, 0xFF ) );
			this->surfaces.insert(std::make_pair(filename,optimizedImage));
			//Return the optimized surface
			return optimizedImage;
		}else{
			return NULL;
		}
	}
	return loadedImage;
}

SDL_Surface* ImageLoader::stretch(SDL_Surface *surface, double width, double height)
{	
	double escalaAncho = width / surface->w;
	double escalaAlto = height / surface->h;
	SDL_Surface * zoomed = zoomSurface (surface,escalaAncho,escalaAlto,1);
	SDL_Surface * retornar = NULL;

	retornar = SDL_DisplayFormat( zoomed );
	if( retornar == NULL ) return NULL;

	SDL_FreeSurface(zoomed);

	if( SDL_SetColorKey(retornar, SDL_SRCCOLORKEY, SDL_MapRGB( retornar->format, 0xFF, 0xFF, 0xFF )) != 0 ) return NULL ;
	
	return retornar;
}

SDL_Rect ImageLoader::createRect(double x, double y){
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	return rect;
}

void ImageLoader::blanquearPantalla (SDL_Surface* pantalla) {
	SDL_FillRect(pantalla, NULL, 0x000000);
}

void ImageLoader::rotar(int grados,string idImage, string newPosition){
	unsigned int position = idImage.find("_");
	unsigned int posExtension = idImage.size()-4;
	SDL_Surface* img = IMG_Load(idImage.c_str());

	string newIDImage;  
	newIDImage = idImage.substr(0,position); //newIDImage dara como resultado nombreOriginal+_"+angulo+extension
	newIDImage += "_";
	newIDImage += newPosition;
	newIDImage += idImage.substr(posExtension-1,5);
    SDL_Surface* rot = rotozoomSurface( img, grados, 1.0, 0 );
	SDL_SaveBMP(rot,newIDImage.c_str());
	SDL_FreeSurface(img);
	SDL_FreeSurface(rot);
}

bool ImageLoader::iniciarSDL(){
	//inicia SDL
	bool ok = true;
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		Log::getInstance().log(1,__FILE__,__LINE__,"SDL no se pudo iniciar");
		ok = false;
	}

	//inicia la TTF
	TTF_Init();
	SDL_EnableUNICODE(SDL_ENABLE);

	return ok;
}

void ImageLoader::cerrarSDL(){
	SDL_EnableUNICODE(SDL_DISABLE);
	SDL_Quit();
	TTF_Quit();
}


SDL_Surface* ImageLoader::levantarPantalla(double w, double h){
	SDL_Surface* screen = SDL_SetVideoMode( w, h, SCREEN_BPP, SDL_SWSURFACE );
	SDL_WM_SetCaption( "..:: Diablo III ::..", NULL );	
	return screen;
}

void ImageLoader::refrescarPantalla(SDL_Surface* screen){
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

ImageLoader::~ImageLoader() {

}
