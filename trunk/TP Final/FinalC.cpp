#include "FinalC.h"

FinalC::FinalC(void){

}

FinalC::~FinalC(void){

}

void FinalC::resolver(void){

	stDatos datos;

	// Leo el archivo de Rectangulos
	this->leerArchivoDispersores(datos);

	// Leo el archivo de Circulos
	this->leerArchivoTejos(datos);

	// Calculo las colisiones
	this->procesarChoques(datos);

	return void();
}

void FinalC::leerArchivoDispersores(stDatos &datos){
	ESArchivoCpp entrada("./archivos/FinalC_Entrada_Dispersores.txt",true,true);
	std::string linea;
	while( entrada.leerLinea(linea) ){
		std::stringstream ssl(linea);
		std::string valor;
		int indice = 1;
		stRec disp;	// Supongo que todos los datos vienen validados y formateados. por ej. nunca falta un valor, o tiene un tipo erróneo
		while( std::getline(ssl,valor,',') ){
			std::stringstream ssv(valor);
			if( indice == 1 ) disp.id.assign(ssv.str());
			if( indice == 2 ) ssv >> disp.x;
			if( indice == 3 ) ssv >> disp.y;
			if( indice == 4 ) ssv >> disp.alto;
			if( indice == 5 ) ssv >> disp.ancho;
			indice++;
		}
		datos.dispersores.push_back(disp);
	}
	
	return void();
}

void FinalC::leerArchivoTejos(stDatos &datos){
	ESArchivoCpp entrada("./archivos/FinalC_Entrada_Tejos.txt",true,true);
	std::string linea;
	while( entrada.leerLinea(linea) ){
		std::stringstream ssl(linea);
		std::string valor;
		int indice = 1;
		stCir disp;	// Supongo que todos los datos vienen validados y formateados. por ej. nunca falta un valor, o tiene un tipo erróneo
		while( std::getline(ssl,valor,',') ){
			std::stringstream ssv(valor);
			if( indice == 1 ) disp.id.assign(ssv.str());
			if( indice == 2 ) ssv >> disp.x;
			if( indice == 3 ) ssv >> disp.y;
			if( indice == 4 ) ssv >> disp.r;
			indice++;
		}
		datos.tejos.push_back(disp);
	}
	return void();
}

void FinalC::procesarChoques(stDatos &datos){

	std::list<stResultado> resultados;

	// Itero sobre los tejos
	for( std::list<stCir>::iterator itTejo = datos.tejos.begin() ; itTejo != datos.tejos.end() ; itTejo++ ){
		
		// Lo comaparo contra cada uno de los dispersores
		for( std::list<stRec>::iterator itDispersor = datos.dispersores.begin() ; itDispersor != datos.dispersores.end() ; itDispersor++ ){

			// Calculo el rango de intersección en la coordenada "y"
			double sup, inf;
			double tejoSup = (*itTejo).r + (*itTejo).y;
			double tejoInf = (*itTejo).r - (*itTejo).y;
			double dispSup = (*itDispersor).y + (*itDispersor).alto;
			double dispInf = (*itDispersor).y;

			// Miro se se van a chocar
			bool hayInterseccion = ( (tejoInf>dispSup) || (tejoSup<dispInf) ) == false;  // Hay interseccion si no sucede que el tejo pasa por arriba o por abajo

			if( hayInterseccion ){

				// Calculo el rango donde chocarian
				if( tejoSup > dispSup ){ sup = dispSup;
				}else{ sup = tejoSup; }

				if( tejoInf > dispInf ){ inf = tejoInf;
				}else{ inf = dispInf; }

				// Calculo el punto de contacto donde se va a producir el choque
				double contactoX, contactoY;
				if( (inf <= (*itTejo).y) && ((*itTejo).y <= sup) ){	// Si está el centro ya se que choca allí
					contactoX = (*itTejo).x + (*itTejo).r;
					contactoY = (*itTejo).y;
				}else{

					// Calculo el "Y" según el rango de intersección
					if( (inf > (*itTejo).y) ){	// Si no está el centro y toca por arriba, chocará con el "Y" mas bajo
						contactoY = inf;
					}
					if( ((*itTejo).y > sup) ){	// Si no está el centro y toca por abajo, chocará con el "Y" mas alto
						contactoY = sup;
					}

					// Calculo el "contactoX" según el "contactoY" obtenido recién, usando pitágoras
					double r = (*itTejo).r;				// Radio
					double y = (*itTejo).y - contactoY; // Distancia al radio en el eje "y"
					double x = sqrt( (r*r)-(y*y) );		// Distancia al radio en el eje "x"
					contactoX = (*itTejo).x + x;
				}

				// Una vez que tengo el punto con el que chocaria el tejo, calculo la distancia respecto del dispersor
				// Siempre y cuando el punto que choca el tejo se encuentre a la izquierda del borde izquierdo del dispersor
				if( contactoX < (*itDispersor).x ){
					stResultado res;
					res.idTejo.assign((*itTejo).id);
					res.idDispersor.assign((*itDispersor).id);
					res.distancia = (*itDispersor).x - contactoX;
					
					bool agregarNuevoValor = true;
					for( std::list<stResultado>::iterator it = resultados.begin() ; it!=resultados.end() ; it++){

						if( res.idTejo.compare( (*it).idTejo ) == 0 && res.idDispersor.compare( (*it).idDispersor ) == 0 ){
							if( res.distancia < (*it).distancia ){	// Si la distancia es mas corta, choca primero con este. Reemplazo los datos
								(*it).idTejo = res.idTejo;
								(*it).idDispersor = res.idDispersor;
								(*it).distancia = res.distancia;
								agregarNuevoValor = false;
							}else{									// Si la distancia es mas grande, no va a chocar con este. Lo descarto
								agregarNuevoValor = false;
							}
						} 

					}
					
					// Si era una colisión completamente nueva, la agrego a la lista
					if( agregarNuevoValor == true ) resultados.push_back(res);
				}
				
			}
			
		}

	}

	std::cout << "Resultados:\n";
	for( std::list<stResultado>::iterator it = resultados.begin() ; it!=resultados.end() ; it++){
		std::cout << " > ID Tejo:" << (*it).idTejo << "  ID Dispersor:" << (*it).idDispersor << "  Distancia:" << (*it).distancia << std::endl;
	}

	return void();
}
