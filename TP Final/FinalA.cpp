#include "FinalA.h"

FinalA::FinalA(void){

}

FinalA::~FinalA(void){

}

// Consideraciones: 
// + El formato de colores por pixel es (B,G,R)
// + Cuando el enunciado dice "offset 3 bytes", se refiere al 3er byte o sea a realizar un offset de 2 desde el inicio
// + Las l�neas de pixeles comienzan desde abajo, yendo de izquierda a derecha
// + Las l�neas siempre tienen una longitud total m�ltiplo de 4 bytes...
//   ...o sea que si es necesario cada l�nea puede tener un padding de 0, 1, 2 o 3 bytes al final de cada l�nea
void FinalA::resolver(void){

	// Ac� cargo los datos del archivo de entrada
	stDatos datos;
	datos.arrayPixeles = NULL;
	datos.arrayPixelesDuplicados = NULL;
	datos.arrayPixelesTransparentados = NULL;

	// Obtengo todos los datos necesarios para procesar la imagen
	this->leerArchivo(datos);

	// Duplico el tama�o de la imagen
	this->duplicarTamanioImagen(datos);

	// Guardo todo lo calculado en la salida
	this->guardarArchivo(datos);

	// Borro lo que instanci�
	if( datos.arrayPixeles != NULL ) delete[] datos.arrayPixeles;
	if( datos.arrayPixelesDuplicados != NULL ) delete[] datos.arrayPixelesDuplicados ;
	if( datos.arrayPixelesTransparentados != NULL ) delete[] datos.arrayPixelesTransparentados ;

	return void();
}

void FinalA::leerArchivo(stDatos &datos){

	// Archivo de entrada. Abro el archivo de entrada en modo binario.
	ESArchivoCpp entrada("./archivos/FinalA_Entrada.bmp",true,false);
	
	// Leo el byte 2: Tama�o del archivo.
	entrada.leerArchivo( (char*)&datos.tamanioArchivo , 2 , sizeof(unsigned int) );	
	
	// Leo el byte 10: Offset de inicio de los datos.
	entrada.leerArchivo( (char*)&datos.offsetDatos , 10 , sizeof(unsigned int) );	

	// Leo el byte 18: Ancho en pixeles de la imagen.
	entrada.leerArchivo( (char*)&datos.anchoPix, 18 , sizeof(int) );					
	
	// Leo el byte 22: Alto en pixeles de la imagen.
	entrada.leerArchivo( (char*)&datos.altoPix, 22 , sizeof(int) );

	// Calculo el alto y ancho real, incluyendo los bytes de padding. Valores en bytes.
	unsigned int bytesPorPixel = 3;			// Un byte por cada color: (B,G,R)
	unsigned int alineacion = 4;			// Alineaci�n en bytes
	unsigned int anchoEnBytesSinPadding = ( datos.anchoPix * bytesPorPixel);
	unsigned int paddingPorLinea = ( ( alineacion - (anchoEnBytesSinPadding % alineacion) ) % alineacion );
	unsigned int anchoEnBytesConPadding = anchoEnBytesSinPadding + paddingPorLinea;

	// Guardo los valores calculados
	datos.bytesPorPixel = bytesPorPixel;
	datos.anchoFila = anchoEnBytesConPadding;
	datos.cantidadFilas = datos.altoPix;
	datos.paddingAplicado = paddingPorLinea;

	// Guardo los datos de todos los pixeles
	unsigned int tamanioArrayPixeles = ( datos.anchoFila * datos.cantidadFilas );
	datos.arrayPixeles = new unsigned char[tamanioArrayPixeles];
	entrada.leerArchivo( (char*)datos.arrayPixeles , datos.offsetDatos , tamanioArrayPixeles );

	return void();
}

void FinalA::duplicarTamanioImagen(stDatos &datos){

	// Preparo el array doble
	unsigned int filasDoble = datos.cantidadFilas * 2;
	unsigned int anchoDobleSinPadding = (datos.anchoFila - datos.paddingAplicado) * 2;
	unsigned int alineacion = 4;		// Alineaci�n en bytes
	unsigned int paddingPorLineaDoble = ( ( alineacion - (anchoDobleSinPadding % alineacion) ) % alineacion );
	unsigned int anchoDoble = anchoDobleSinPadding + paddingPorLineaDoble;
	
	// Guardo el dato para otras funciones.
	datos.anchoFilaDoble = anchoDoble;

	// Preparo el array doble
	unsigned int tamanioArrayPixelesDuplicados = ( anchoDoble * filasDoble );
	datos.arrayPixelesDuplicados = new unsigned char[tamanioArrayPixelesDuplicados];

	// Lleno el array doble con los valores duplicados. Recorro el array original.
	for( unsigned int i = 0 ; i < datos.cantidadFilas ; i++ ){  // Recorre todas las filas
		for( unsigned int j = 0 ; j < (datos.anchoFila-datos.paddingAplicado) ; j++ ){  // Recorre todos los bytes de cada fila, sin pasar por los bytes de padding

			// Calculo las posiciones y filas que debo acceder para guardar los datos duplicados en el otro array
			unsigned int pos1 = ( (2*j) - (j % datos.bytesPorPixel) );	// Calculo la ubicaci�n del pixel
			unsigned int pos2 = pos1 + datos.bytesPorPixel;				// Calculo la ubicaci�n de la copia del pixel
			unsigned int fila1 = (datos.anchoFilaDoble) * (i*2);		// Calculo la ubicaci�n de la fila
			unsigned int fila2 = (datos.anchoFilaDoble) * (i*2+1);		// Calculo la ubicaci�n de la copia de la fila

			// Una fila con el valor duplicado
			unsigned char valor = datos.arrayPixeles[(i*datos.anchoFila)+j];
			datos.arrayPixelesDuplicados[fila1+pos1] = valor;
			datos.arrayPixelesDuplicados[fila1+pos2] = valor;

			// Una copia de la fila anterior
			datos.arrayPixelesDuplicados[fila2+pos1] = valor;
			datos.arrayPixelesDuplicados[fila2+pos2] = valor;

		}
	}

	return void();
}

void FinalA::calcularColorTransparente(stDatos &datos){
	// TODO: En construcci�n
	return void();
}

void FinalA::reemplazarColorTransparente(stDatos &datos){
	// TODO: En construcci�n
	return void();
}

void FinalA::guardarArchivo(stDatos &datos){

	// Archivo de entrada. Abro el archivo de entrada en modo binario.
	ESArchivoCpp entrada("./archivos/FinalA_Entrada.bmp",true,false);

	// Archivo de salida
	ESArchivoCpp salida("./archivos/FinalA_Salida.bmp",false,false);

	// Escribo todo el archivo original, para despues ir pisando los datos que necesito actualizar
	char* archivoCompleto = NULL;
	unsigned int tamanioArchivoCompleto = entrada.leerArchivo(&archivoCompleto);
	salida.escribirEnArchivo(archivoCompleto,datos.offsetDatos);
	if( archivoCompleto != NULL ) delete[] archivoCompleto;

	// Escribo el byte 2: Tama�o del archivo.
	unsigned int tamanioArrayDuplicado = (datos.cantidadFilas * 2) * ( datos.anchoFilaDoble );
	unsigned int tamanioArchivo = datos.offsetDatos + tamanioArrayDuplicado;
	salida.escribirEnArchivo((char*)&tamanioArchivo,2, sizeof(unsigned int));

	// Escribo el byte 18: Ancho en pixeles de la imagen.
	int anchoEnPixeles = datos.anchoPix * 2;
	salida.escribirEnArchivo( (char*)&anchoEnPixeles , 18 , sizeof(int) );					
	
	// Escribo el byte 22: Alto en pixeles de la imagen.
	int altoEnPixeles = datos.altoPix * 2;
	salida.escribirEnArchivo( (char*)&altoEnPixeles , 22 , sizeof(int) );

	// Escribo los nuevos valores del array duplicado
	salida.escribirEnArchivo((char*)datos.arrayPixelesDuplicados,datos.offsetDatos,tamanioArrayDuplicado);

	return void();
}

// Toma una imagen BMP 24-bit y le deja solo el componente verde de la misma
void FinalA::pruebaPintaVerde(void){
	ESArchivoCpp entrada("./archivos/ruggeri_rasta.bmp",true,false);
	ESArchivoCpp salida("./archivos/FinalA_Salida.bmp",false,false);

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

	unsigned int anchoConPadding = (3 * ancho) + ( 4 - ((3 * ancho)%4) ) % 4;	// Ojo: Cada fila est� alineada con bloques de 4 bytes, si es necesario tiene padding al final de la misma
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
