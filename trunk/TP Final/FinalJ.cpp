#include "FinalJ.h"

FinalJ::FinalJ(void){

}

FinalJ::~FinalJ(void){

}

void FinalJ::resolver(){
	stDatos datos;
	datos.tam = 100;

	this->leerArchivos(datos);

	this->procesar(datos);

	this->listar(datos);

}

void FinalJ::leerArchivos(stDatos& datos){
	std::fstream aEnem;
	std::fstream aPje;

	std::string ruta("./archivos/FinalJ_Entrada_enem.txt"); 
	aEnem.open(ruta.c_str(),std::ios::in);
	ruta.assign("./archivos/FinalJ_Entrada_pjes.txt");
	aPje.open(ruta.c_str(),std::ios::in);

	std::string linea;
	while( std::getline(aEnem,linea)){
		std::stringstream ssl(linea);
		stEnem enem;
		std::string dato;
		int ind = 1;
		while( std::getline(ssl,dato,',')){
			std::stringstream ssv(dato);
			if( ind == 1) ssv >> enem.x;
			if( ind == 2) ssv >> enem.y;
			if( ind == 3) ssv >> enem.atq;
			ind++;
		}
		datos.enemigos.push_back(enem);
	}

	while( std::getline(aPje,linea)){
		std::stringstream ssl(linea);
		stPje pje;
		std::string dato;
		int ind = 1;
		while( std::getline(ssl,dato,',')){
			std::stringstream ssv(dato);
			if( ind == 1) pje.id.assign(ssv.str());
			if( ind == 2) ssv >> pje.x;
			if( ind == 3) ssv >> pje.y;
			if( ind == 4) ssv >> pje.energia;
			ind++;
		}
		pje.ciclos = 0;
		pje.recorrido = 0;
		pje.gano = false;
		pje.murio = false;
		datos.pDisponibles.push_back(pje);
	}

	aEnem.close();
	aPje.close();

}

void FinalJ::procesar(stDatos& datos){

	bool sigueJuego = true;
	
	while( sigueJuego == true ){
	
		// Los jugadores suman otro ciclo jugado
		for( std::list<stPje>::iterator it= datos.pDisponibles.begin() ; it!=datos.pDisponibles.end() ;it++){
			if( (*it).gano == false && (*it).murio == false){
				(*it).ciclos = (*it).ciclos + 1;
			}

		}

		// Los enemigos atacan en 8 direcciones
		for( std::list<stEnem>::iterator it= datos.enemigos.begin() ; it!=datos.enemigos.end() ;it++){
			this->atacar(datos, (*it).x+1, (*it).y+1,(*it).atq);
			this->atacar(datos, (*it).x+1, (*it).y,(*it).atq);
			this->atacar(datos, (*it).x+1, (*it).y-1,(*it).atq);
			this->atacar(datos, (*it).x, (*it).y-1,(*it).atq);

			this->atacar(datos, (*it).x-1, (*it).y-1,(*it).atq);
			this->atacar(datos, (*it).x-1, (*it).y,(*it).atq);
			this->atacar(datos, (*it).x-1, (*it).y+1,(*it).atq);
			this->atacar(datos, (*it).x, (*it).y+1,(*it).atq);
		}

		// Los personajes avanzan, si alguien llegó al final lo pongo en ganador
		for( std::list<stPje>::iterator it= datos.pDisponibles.begin() ; it!=datos.pDisponibles.end() ;it++){
			if( (*it).gano == false && (*it).murio == false){

				bool hayEnemigo = false;
				for( std::list<stEnem>::iterator it2= datos.enemigos.begin() ; it2!=datos.enemigos.end() ;it2++){
					if( (*it).x+1 == (*it2).x && (*it).y == (*it2).y ) hayEnemigo = true;
				}

				if( hayEnemigo == false ){
					(*it).x = (*it).x + 1;
					(*it).recorrido = (*it).recorrido + 1;
				}

				if( (*it).x > datos.tam ) (*it).gano = true;

			}
		}

		// Verifico si sigue el juego
		sigueJuego = false;
		for( std::list<stPje>::iterator it= datos.pDisponibles.begin() ; it!=datos.pDisponibles.end() ;it++){
			if( (*it).gano == false && (*it).murio == false ){
				
				sigueJuego = true;

			}
		}
	
	}


}

// Los enemigos atacan en 8 direcciones, si alguien murio lo paso al listado de muerto
void FinalJ::atacar(stDatos& datos, int x, int y, double atq){
	
	// Verifico rango del mapa
	if( x>0 && y>0 && x<=datos.tam &&  x<=datos.tam){
	
		for( std::list<stPje>::iterator it= datos.pDisponibles.begin() ; it!=datos.pDisponibles.end() ;it++){
			
			if( (*it).gano == false && (*it).murio == false){
				
				if( (*it).x == x && (*it).y == y ){
				
					(*it).energia = (*it).energia - atq;
			
				}

				if( (*it).energia <= 0 ) (*it).murio = true;
			}
			
		}

	}

}

// Muestro a los que mueren
void FinalJ::listar(stDatos& datos){

	// Ordeno
	datos.pDisponibles.sort();

	std::cout << "Personajes que perdieron: " << std::endl;
	for( std::list<stPje>::iterator it= datos.pDisponibles.begin() ; it!=datos.pDisponibles.end() ;it++){
		if( (*it).gano == false && (*it).murio == true ){
			std::cout << "Id: " << (*it).id << " Ciclos: " << (*it).ciclos << " Recorrido: " << (*it).recorrido << std::endl;
		}
	}

}