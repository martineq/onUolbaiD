#include "FinalA.h"

FinalA::FinalA(void){

}

FinalA::~FinalA(void){

}

void FinalA::resolucion(void){

	return void();
}

// Toma una imagen BMP 24-bit y le deja solo el componente verde de la misma
void FinalA::prueba(void){
	ESArchivoCpp entrada("./archivos/ruggeri_rasta.bmp",true,false); // ruggeri_rasta
	ESArchivoCpp salida("./archivos/salida.bmp",false,false);

	unsigned int tamanioArchivo = 0;
	entrada.leerArchivo( (char*)&tamanioArchivo , 2 , sizeof(unsigned int) );	// 2: Offset al tamanio de archivo, sacado del enunciado
	std::cout << "Tamanio del archivo (leido del BMP): " << tamanioArchivo << "\n";

	unsigned int offsetDatos = 0;
	entrada.leerArchivo( (char*)&offsetDatos , 10 , sizeof(unsigned int) );	// 10: Offset al offset de inicio de los datos, sacado del enunciado
	std::cout << "Offset a los datos del BMP: " << offsetDatos << "\n";

	int ancho = 0;
	entrada.leerArchivo( (char*)&ancho , 18 , sizeof(int) );		// 18: Offset al ancho en pixels de la imagen, sacado del enunciado
	std::cout << "Ancho de la imagen BMP: " << ancho << "\n";

	int alto = 0;
	entrada.leerArchivo( (char*)&alto , 22 , sizeof(int) );			// 22: Offset al alto en pixels de la imagen, sacado del enunciado
	std::cout << "Alto de la imagen BMP: " << alto << "\n";

	unsigned int anchoConPadding = (3 * ancho) + (3 * ancho)%4;		// Ojo: Cada fila está alineada con bloques de 4 bytes, si es necesario tiene padding al final de la misma
	unsigned int tamanioDatos = (alto * anchoConPadding);
	std::cout << "El tamanio de la cabecera + los datos es: " << offsetDatos + tamanioDatos << "\n";

	unsigned char* datos = new unsigned char[tamanioDatos];
	entrada.leerArchivo( (char*)datos , offsetDatos , tamanioDatos );

	// Nota: El formato de los colores es >>> (B,G,R)
	for( unsigned long i = 0; i < alto; i++){		// Azul
		unsigned int filasAnt = i * anchoConPadding;
		for( unsigned long j = 0; j < (3 * ancho); j+=3){
			unsigned short numero = 0;
			datos[filasAnt + j] = (unsigned char)numero;	// Saco la componente azul
		}
	}

	for( unsigned long i = 0; i < alto; i++){		// Verde
		unsigned int filasAnt = i * anchoConPadding;
		for( unsigned long j = 1; j < (3 * ancho); j+=3){
			unsigned short numero = 255;
			//datos[filasAnt + j] = (unsigned char)numero;  // Al verde no le hago nada
		}
	}

	for( unsigned long i = 0; i < alto; i++){		// Rojo
		unsigned int filasAnt = i * anchoConPadding;
		for( unsigned long j = 2; j < (3 * ancho); j+=3){
			unsigned short numero = 0;
			datos[filasAnt + j] = (unsigned char)numero;	// Saco la componente roja
		}
	}

	char* archivoCompleto = NULL;
	unsigned int tamanioArchivoCompleto = entrada.leerArchivo(&archivoCompleto);

	salida.escribirEnArchivo(archivoCompleto,tamanioArchivoCompleto);
	salida.escribirEnArchivo((char*)datos,offsetDatos,tamanioDatos);

	delete[] datos;
	if( archivoCompleto != NULL ) delete[] archivoCompleto;

	return void();
}
