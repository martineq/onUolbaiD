#include "FinalE.h"

FinalE::FinalE(void){

}

FinalE::~FinalE(void){

}

void FinalE::resolver(void){

	stDatos datos;

	this->leerArchivoImagen(datos);

	this->calcularHistogramas(datos);

	this->guardarArchivos(datos);

	return void();
}

void FinalE::leerArchivoImagen(stDatos &datos){

	// Archivo de entrada. Abro el archivo de entrada en modo binario.
	ESArchivoCpp entrada("./archivos/FinalE_Entrada_Origen.bmp",true,false);
	
	// Leo el byte 10: Offset de inicio de los datos.
	entrada.leerArchivo( (char*)&datos.offsetDatos , 10 , sizeof(unsigned int) );	

	// Leo el byte 18: Ancho en pixeles de la imagen.
	entrada.leerArchivo( (char*)&datos.anchoPix, 18 , sizeof(int) );					
	
	// Leo el byte 22: Alto en pixeles de la imagen.
	entrada.leerArchivo( (char*)&datos.altoPix, 22 , sizeof(int) );

	// Calculo el ancho en bytes
	unsigned int bytesPorPixel = 3;			// Un byte por cada color: (B,G,R) (Formato 24bits = 3*8)
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
	datos.origen = new unsigned char[tamanioArrayPixeles];
	entrada.leerArchivo( (char*)datos.origen , datos.offsetDatos , tamanioArrayPixeles );

	return void();
}

void FinalE::calcularHistogramas(stDatos &datos){

	// Creo e inicialo los contadores para los 3 colores
	unsigned long* contB = new unsigned long[256];
	unsigned long* contG = new unsigned long[256];
	unsigned long* contR = new unsigned long[256];
	for( int b = 0 ; b < 256 ; b++ ){
		contB[b] = 0;
		contG[b] = 0;
		contR[b] = 0;
	}

	// Cargo los valores en los contadores
	for( int i = 0 ; i < datos.cantidadFilas ; i++){

		for( int j = 0 ; j < (datos.anchoFila-datos.paddingAplicado) ; j=j+3){
			
			unsigned char valorB = datos.origen[datos.anchoFila*i + j];
			unsigned char valorG = datos.origen[datos.anchoFila*i + j + 1];
			unsigned char valorR = datos.origen[datos.anchoFila*i + j + 2];
			if( valorB!=255 && valorG!=255 && valorR!=255 ){
				contB[valorB]++;
				contG[valorG]++;
				contR[valorR]++;
			}

		}

	}

	// Hago la sumatoria de los valores encontrados
	unsigned long totalB = 0;
	unsigned long totalG = 0;
	unsigned long totalR = 0;
	for( int c = 0 ; c < 256 ; c++ ){
		totalB = totalB + contB[c];
		totalG = totalG + contG[c];
		totalR = totalR + contR[c];
	}

	// Los paso a porcentaje
	for( int d = 0 ; d < 256 ; d++ ){
		if( totalB == 0 ){contB[d] = 0;}
		else{contB[d] = (contB[d]*100) / totalB;}

		if( totalG == 0 ){contG[d] = 0;}
		else{contG[d] = (contG[d]*100) / totalG;}
		
		if( totalR == 0 ){contR[d] = 0;}
		else{contR[d] = (contR[d]*100) / totalR;}
	}


	// Hago la sumatoria de los valores encontrados, pero ahora con los porcentajes
	unsigned char totalPorcB = 0;
	unsigned char totalPorcG = 0;
	unsigned char totalPorcR = 0;
	for( int c = 0 ; c < 256 ; c++ ){
		totalPorcB = totalPorcB + contB[c];
		totalPorcG = totalPorcG + contG[c];
		totalPorcR = totalPorcR + contR[c];
	}
	unsigned char restoB = 100-totalPorcB;
	unsigned char restoG = 100-totalPorcG;
	unsigned char restoR = 100-totalPorcR;

	// Redondeo: Completo llenando de a 1% los que en total no hayan llegado al 100%. Agarro al primero que encuentre con un porcentaje !=0
	for( int c = 0 ; c < 256 ; c++ ){

		if( contB[c] != 0 && restoB != 0){
			contB[c]++;
			restoB--;
		}

		if( contG[c] != 0 && restoG != 0){
			contG[c]++;
			restoG--;
		}

		if( contR[c] != 0 && restoR != 0){
			contR[c]++;
			restoR--;
		}

	}

	//Creo e inicialo los histogramas gráficos
	int tamHisto = datos.anchoFila*datos.cantidadFilas;
	datos.histoB = new unsigned char[tamHisto];
	datos.histoG = new unsigned char[tamHisto];
	datos.histoR = new unsigned char[tamHisto];

	for( unsigned int i = 0 ; i < datos.cantidadFilas ; i++){

		for( unsigned int j = 0 ; j < (datos.anchoFila-datos.paddingAplicado) ; j=j+3){
			
			unsigned long indB = datos.anchoFila*i + j;
			unsigned long indG = datos.anchoFila*i + j + 1;
			unsigned long indR = datos.anchoFila*i + j + 2;

			unsigned char valorColor = j/3;

			// Para llenar el histograma Azul
			unsigned char cB = contB[valorColor];
			if( cB !=0 && cB >= i ) datos.histoB[indB] = valorColor;
			else datos.histoB[indB] = 0;

			datos.histoB[indG] = 0;
			datos.histoB[indR] = 0;

			// Para llenar el histograma Verde
			datos.histoG[indB] = 0;

			unsigned char cG = contG[valorColor];
			if( cG !=0 && cG >= i ) datos.histoG[indG] = valorColor;
			else datos.histoG[indG] = 0;

			datos.histoG[indR] = 0;

			// Para llenar el histograma Rojo
			datos.histoR[indB] = 0;
			datos.histoR[indG] = 0;

			unsigned char cR = contR[valorColor];
			if( cR !=0 && cR >= i  ) datos.histoR[indR] = valorColor;
			else datos.histoR[indR] = 0;

		}

	}


	return void();
}


void FinalE::guardarArchivos(stDatos &datos){

	// Archivo de entrada. Abro el archivo de entrada en modo binario.
	ESArchivoCpp entrada("./archivos/FinalE_Entrada_Origen.bmp",true,false);

	// Archivos de salida
	ESArchivoCpp salidaB("./archivos/FinalE_Histograma_Azul.bmp",false,false);
	ESArchivoCpp salidaG("./archivos/FinalE_Histograma_Verde.bmp",false,false);
	ESArchivoCpp salidaR("./archivos/FinalE_Histograma_Rojo.bmp",false,false);

	// Escribo todo el archivo original, para despues ir pisando los datos que necesito actualizar
	char* archivoCompleto = NULL;
	unsigned int tamanioArchivoCompleto = entrada.leerArchivo(&archivoCompleto);
	salidaB.escribirEnArchivo(archivoCompleto,datos.offsetDatos);
	salidaG.escribirEnArchivo(archivoCompleto,datos.offsetDatos);
	salidaR.escribirEnArchivo(archivoCompleto,datos.offsetDatos);
	if( archivoCompleto != NULL ) delete[] archivoCompleto;

	// Escribo los valores de los histogramas
	salidaB.escribirEnArchivo((char*)datos.histoB,datos.offsetDatos,datos.cantidadFilas*datos.anchoFila);
	salidaG.escribirEnArchivo((char*)datos.histoG,datos.offsetDatos,datos.cantidadFilas*datos.anchoFila);
	salidaR.escribirEnArchivo((char*)datos.histoR,datos.offsetDatos,datos.cantidadFilas*datos.anchoFila);

	return void();
}