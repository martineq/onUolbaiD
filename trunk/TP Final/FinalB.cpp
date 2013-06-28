#include "FinalB.h"

FinalB::FinalB(void){

}

FinalB::~FinalB(void){

}

// Consideraciones: 
// + 
void FinalB::resolver(void){

	// Acá cargo los datos necesarios para trabajar
	stDatos datos;
	datos.arrayPixeles = NULL;

	// Obtengo todos la información del archivo de imagen
	this->leerArchivoImagen(datos);

	// Obtengo todos la información del archivo de datos
	this->leerArchivoDatos(datos);

	// Pinto las areas indicadas
	this->pintarAreas(datos);

	// Guardo todo lo calculado en la salida
	this->guardarArchivo(datos);

	// Borro lo que instancié
	if( datos.arrayPixeles != NULL ) delete[] datos.arrayPixeles;

	return void();
}

void FinalB::leerArchivoImagen(stDatos &datos){

	// Archivo de entrada. Abro el archivo de entrada en modo binario.
	ESArchivoCpp entrada("./archivos/FinalB_Entrada_Imagen.bmp",true,false);
	
	// Leo el byte 10: Offset de inicio de los datos.
	entrada.leerArchivo( (char*)&datos.offsetDatos , 10 , sizeof(unsigned int) );	

	// Leo el byte 18: Ancho en pixeles de la imagen.
	entrada.leerArchivo( (char*)&datos.anchoPix, 18 , sizeof(int) );					
	
	// Leo el byte 22: Alto en pixeles de la imagen.
	entrada.leerArchivo( (char*)&datos.altoPix, 22 , sizeof(int) );

	// Calculo el ancho en bytes
	unsigned int bytesPorPixel = 3;			// Un byte por cada color: (B,G,R)
	unsigned int alineacion = 4;			// Alineación en bytes
	unsigned int anchoEnBytesSinPadding = ( datos.anchoPix * bytesPorPixel);
	unsigned int paddingPorLinea = ( ( alineacion - (anchoEnBytesSinPadding % alineacion) ) % alineacion );
	unsigned int anchoEnBytesConPadding = anchoEnBytesSinPadding + paddingPorLinea;

	// Guardo los valores calculados
	datos.anchoFila = anchoEnBytesConPadding;
	datos.paddingAplicado = paddingPorLinea;
	datos.cantidadFilas = datos.altoPix;

	// Guardo los datos de todos los pixeles
	unsigned int tamanioArrayPixeles = ( datos.anchoFila * datos.cantidadFilas );
	datos.arrayPixeles = new unsigned char[tamanioArrayPixeles];
	entrada.leerArchivo( (char*)datos.arrayPixeles , datos.offsetDatos , tamanioArrayPixeles );

	return void();
}

void FinalB::leerArchivoDatos(stDatos &datos){

	// Archivo de entrada. Abro el archivo de entrada en modo texto.
	ESArchivoCpp entrada("./archivos/FinalB_Entrada_Datos.txt",true,true);
	std::string linea;
	while( entrada.leerLinea(linea) == true ){
		stPunto punto;
		std::stringstream ss(linea);
		std::string atomo;
		int posicion = 0;
		while( std::getline(ss,atomo,',') ){	
			std::stringstream temp(atomo);
			int num;
			temp >> num;
			if( posicion == 0 ) punto.x = num;
			if( posicion == 1 ) punto.y = num;
			if( posicion == 2 ) punto.r = num;
			if( posicion == 3 ) punto.g = num;
			if( posicion == 4 ) punto.b = num;
			posicion++;
		}
		datos.puntos.push_back(punto);
	}

	return void();
}

void FinalB::pintarAreas(stDatos &datos){
	
	for( std::vector<stPunto>::iterator it = datos.puntos.begin() ; it !=  datos.puntos.end() ; it++ ){
		bool* pintado = new bool[datos.altoPix*datos.anchoPix];
		for( unsigned long i=0 ; i<datos.altoPix*datos.anchoPix; i++) pintado[i]=false;

		stPunto puntoReemplazo = (*it);
		stColor colorBusco;
		unsigned int posB = (datos.anchoFila) * (puntoReemplazo.y) + ( 3 * (puntoReemplazo.x) );
		colorBusco.b = datos.arrayPixeles[posB];
		colorBusco.g = datos.arrayPixeles[posB+1];
		colorBusco.r = datos.arrayPixeles[posB+2];

		this->pintar(datos,puntoReemplazo,colorBusco,pintado);

		delete[] pintado;
	}


	return void();
}

void FinalB::pintar(stDatos &datos, stPunto pReemp, stColor c, bool* pintado){

	std::stack<stPunto> pila;
	pila.push(pReemp);

	while( pila.empty() == false ){

		stPunto punto = pila.top();
		pila.pop();
		long x = punto.x;
		long y = punto.y;

		// Chequeo que no se haya pintado antes
		if( pintado[datos.anchoPix*y + x] == true ) continue;

		// Marco que este pixel ya fue revisado
		pintado[datos.anchoPix*y + x] = true;

		// Chequeo que sea el color que busco, pinto y expando a los 4 costados
		unsigned int posB = (datos.anchoFila) * y + ( 3 * x);
		if( c.b == datos.arrayPixeles[posB] && c.g == datos.arrayPixeles[posB+1] && c.r == datos.arrayPixeles[posB+2] ){
			datos.arrayPixeles[posB] = punto.b;
			datos.arrayPixeles[posB+1] = punto.g;
			datos.arrayPixeles[posB+2] = punto.r;

			// Izquierda
			punto.x = x-1;
			punto.y = y;
			if( (punto.x >= 0) && (pintado[datos.anchoPix*punto.y + punto.x] == false)  ) pila.push(punto);

			// Derecha
			punto.x = x+1;
			punto.y = y;
			if( (punto.x < datos.anchoPix) && (pintado[datos.anchoPix*punto.y + punto.x] == false) ) pila.push(punto);

			// Arriba
			punto.x = x;
			punto.y = y+1;
			if( (punto.y < datos.altoPix) && (pintado[datos.anchoPix*punto.y + punto.x] == false) ) pila.push(punto);

			// Abajo
			punto.x = x;
			punto.y = y-1;
			if( (punto.y >= 0) && (pintado[datos.anchoPix*punto.y + punto.x] == false) ) pila.push(punto);

			// Avanzo por las diagonales
			// Inferior Izquierda
			punto.x = x-1;
			punto.y = y-1;
			if( (punto.x >= 0) && (punto.y >= 0) && (pintado[datos.anchoPix*punto.y + punto.x] == false)  ) pila.push(punto);

			// Inferior Derecha
			punto.x = x+1;
			punto.y = y-1;
			if( (punto.x < datos.anchoPix) && (punto.y >= 0) && (pintado[datos.anchoPix*punto.y + punto.x] == false) ) pila.push(punto);
 
			// Superior Izquierda
			punto.x = x-1;
			punto.y = y+1;
			if( (punto.x >= 0) && (punto.y < datos.altoPix) && (pintado[datos.anchoPix*punto.y + punto.x] == false) ) pila.push(punto);

			// Superior Derecha
			punto.x = x+1;
			punto.y = y+1;
			if( (punto.x < datos.anchoPix) && (punto.y < datos.altoPix) && (pintado[datos.anchoPix*punto.y + punto.x] == false) ) pila.push(punto);

		}

	}

	return void();
}

void FinalB::guardarArchivo(stDatos &datos){

	// Archivo de entrada. Abro el archivo de entrada en modo binario.
	ESArchivoCpp entrada("./archivos/FinalB_Entrada_Imagen.bmp",true,false);

	// Archivo de salida
	ESArchivoCpp salida("./archivos/FinalB_Salida.bmp",false,false);

	// Escribo la cabecera del archivo original, para despues ir agregando los datos nuevos
	char* archivoCompleto = NULL;
	unsigned int tamanioArchivoCompleto = entrada.leerArchivo(&archivoCompleto);
	salida.escribirEnArchivo(archivoCompleto,datos.offsetDatos);
	if( archivoCompleto != NULL ) delete[] archivoCompleto;

	// Escribo los nuevos valores del array
	unsigned int tamanioArray = datos.anchoFila * datos.cantidadFilas;
	salida.escribirEnArchivo((char*)datos.arrayPixeles,datos.offsetDatos,tamanioArray);

	return void();
}
