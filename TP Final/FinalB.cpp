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
	//this->leerArchivoDatos(datos);	// TODO: Habilitar cuando se implemente

	// Pinto las areas indicadas
	//this->pintarAreas(datos);			// TODO: Habilitar cuando se implemente

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
	unsigned int anchoPix;
	entrada.leerArchivo( (char*)&anchoPix, 18 , sizeof(int) );					
	
	// Leo el byte 22: Alto en pixeles de la imagen.
	unsigned int altoPix;
	entrada.leerArchivo( (char*)&altoPix, 22 , sizeof(int) );

	// Calculo el ancho en bytes
	unsigned int bytesPorPixel = 3;			// Un byte por cada color: (B,G,R)
	unsigned int alineacion = 4;			// Alineación en bytes
	unsigned int anchoEnBytesSinPadding = ( anchoPix * bytesPorPixel);
	unsigned int paddingPorLinea = ( ( alineacion - (anchoEnBytesSinPadding % alineacion) ) % alineacion );
	unsigned int anchoEnBytesConPadding = anchoEnBytesSinPadding + paddingPorLinea;

	// Guardo los valores calculados
	datos.anchoFila = anchoEnBytesConPadding;
	datos.paddingAplicado = paddingPorLinea;
	datos.cantidadFilas = altoPix;

	// Guardo los datos de todos los pixeles
	unsigned int tamanioArrayPixeles = ( datos.anchoFila * datos.cantidadFilas );
	datos.arrayPixeles = new unsigned char[tamanioArrayPixeles];
	entrada.leerArchivo( (char*)datos.arrayPixeles , datos.offsetDatos , tamanioArrayPixeles );

	return void();
}

void FinalB::leerArchivoDatos(stDatos &datos){

	return void();
}

void FinalB::pintarAreas(stDatos &datos){

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
