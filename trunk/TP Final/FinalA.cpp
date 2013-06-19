#include "FinalA.h"

FinalA::FinalA(void){

}

FinalA::~FinalA(void){

}

// Consideraciones: 
// + El formato de colores por pixel es (B,G,R)
// + Cuando el enunciado dice "offset 3 bytes", se refiere al 3er byte o sea a realizar un offset de 2 desde el inicio
// + Las líneas de pixeles comienzan desde abajo, yendo de izquierda a derecha
// + Las líneas siempre tienen una longitud total múltiplo de 4 bytes...
//   ...o sea que si es necesario cada línea puede tener un padding de 0, 1, 2 o 3 bytes al final de cada línea
void FinalA::resolver(void){

	// Acá cargo los datos necesarios para trabajar
	stDatos datos;
	datos.arrayPixeles = NULL;
	datos.arrayPixelesDuplicados = NULL;

	// Obtengo todos los datos necesarios para procesar la imagen
	this->leerArchivo(datos);

	// Duplico el tamaño de la imagen
	this->duplicarTamanioImagen(datos);

	// Calculo el color de transparencia
	this->calcularColorTransparente(datos);

	// Aplico el color de transparencia
	this->reemplazarColorTransparente(datos);

	// Guardo todo lo calculado en la salida
	this->guardarArchivo(datos);

	// Borro lo que instancié
	if( datos.arrayPixeles != NULL ) delete[] datos.arrayPixeles;
	if( datos.arrayPixelesDuplicados != NULL ) delete[] datos.arrayPixelesDuplicados ;

	return void();
}

void FinalA::leerArchivo(stDatos &datos){

	// Archivo de entrada. Abro el archivo de entrada en modo binario.
	ESArchivoCpp entrada("./archivos/FinalA_Entrada.bmp",true,false);
	
	// Leo el byte 2: Tamaño del archivo.
	entrada.leerArchivo( (char*)&datos.tamanioArchivo , 2 , sizeof(unsigned int) );	
	
	// Leo el byte 10: Offset de inicio de los datos.
	entrada.leerArchivo( (char*)&datos.offsetDatos , 10 , sizeof(unsigned int) );	

	// Leo el byte 18: Ancho en pixeles de la imagen.
	entrada.leerArchivo( (char*)&datos.anchoPix, 18 , sizeof(int) );					
	
	// Leo el byte 22: Alto en pixeles de la imagen.
	entrada.leerArchivo( (char*)&datos.altoPix, 22 , sizeof(int) );

	// Calculo el alto y ancho real, incluyendo los bytes de padding. Valores en bytes.
	unsigned int bytesPorPixel = 3;			// Un byte por cada color: (B,G,R)
	unsigned int alineacion = 4;			// Alineación en bytes
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
	unsigned int alineacion = 4;		// Alineación en bytes
	unsigned int paddingPorLineaDoble = ( ( alineacion - (anchoDobleSinPadding % alineacion) ) % alineacion );
	unsigned int anchoDoble = anchoDobleSinPadding + paddingPorLineaDoble;
	
	// Guardo el dato para otras funciones.
	datos.anchoFilaDoble = anchoDoble;
	datos.paddingAplicadoDoble = paddingPorLineaDoble;

	// Preparo el array doble
	unsigned int tamanioArrayPixelesDuplicados = ( anchoDoble * filasDoble );
	datos.arrayPixelesDuplicados = new unsigned char[tamanioArrayPixelesDuplicados];

	// Lleno el array doble con los valores duplicados. Recorro el array original.
	for( unsigned int i = 0 ; i < datos.cantidadFilas ; i++ ){  // Recorre todas las filas
		for( unsigned int j = 0 ; j < (datos.anchoFila-datos.paddingAplicado) ; j++ ){  // Recorre todos los bytes de cada fila, sin pasar por los bytes de padding

			// Calculo las posiciones y filas que debo acceder para guardar los datos duplicados en el otro array
			unsigned int pos1 = ( (2*j) - (j % datos.bytesPorPixel) );	// Calculo la ubicación del pixel
			unsigned int pos2 = pos1 + datos.bytesPorPixel;				// Calculo la ubicación de la copia del pixel
			unsigned int fila1 = (datos.anchoFilaDoble) * (i*2);		// Calculo la ubicación de la fila
			unsigned int fila2 = (datos.anchoFilaDoble) * (i*2+1);		// Calculo la ubicación de la copia de la fila

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

	unsigned long tamanioContador = 256*256*256;
	unsigned int* contador = new unsigned int[tamanioContador];	// Creo una matriz 3D (aplanada en 1D) para contabilizar las apariciones de cada color
	for( unsigned long i=0 ; i < tamanioContador ; i++ ){ contador[i] = 0; } // Inicialo todo en cero 

	for( unsigned int i = 0 ; i < (datos.cantidadFilas*2) ; i++ ){  // Recorre todas las filas
		for( unsigned int j = 0 ; j < (datos.anchoFilaDoble-datos.paddingAplicadoDoble) ; j+=3 ){  // Recorre todos los bytes de cada fila, sin pasar por los bytes de padding
			unsigned int posB = (datos.anchoFilaDoble) * i + j;
			unsigned int posG = (datos.anchoFilaDoble) * i + j + 1;
			unsigned int posR = (datos.anchoFilaDoble) * i + j + 2;
			unsigned char b = datos.arrayPixelesDuplicados[posB];
			unsigned char g = datos.arrayPixelesDuplicados[posG];
			unsigned char r = datos.arrayPixelesDuplicados[posR];

			// Busco la posición correspondiente al color e incremento su contador en uno
			unsigned long posicionContador = (256)*(256)*(b) + (256)*(g) + (1)*(r);
			unsigned int valor = contador[posicionContador];
			valor++;
			contador[posicionContador] = valor;
		}
	}

	// Me quedo con el color que apareció mas veces. En cantidad igualada, busco el mas cercano al (255,255,255) calculando la norma
	unsigned int cantidadActual = 0;
	datos.fondoB = 0;
	datos.fondoG = 0;
	datos.fondoR = 0;

	for( unsigned long b=0 ; b < 256 ; b++ ){
		for( unsigned long g=0 ; g < 256 ; g++ ){
			for( unsigned long r=0 ; r < 256 ; r++ ){

				unsigned long pos = (256)*(256)*(b) + (256)*(g) + (1)*(r);
				unsigned int valorObtenido = contador[pos];

				if( cantidadActual == valorObtenido ){
					unsigned long normaValorObtenido = ( b*b + g*g + r*r );
					unsigned long normaActual = (datos.fondoB*datos.fondoB + datos.fondoG*datos.fondoG + datos.fondoR*datos.fondoR);
					if( normaValorObtenido > normaActual ){
						datos.fondoB = b;
						datos.fondoG = g;
						datos.fondoR = r;
					}
				}else{
					if( cantidadActual < valorObtenido ){
						datos.fondoB = b;
						datos.fondoG = g;
						datos.fondoR = r;
						cantidadActual = valorObtenido;
					}
				}

			}
		}
	}

	return void();
}

void FinalA::reemplazarColorTransparente(stDatos &datos){
	
	for( unsigned int i = 0 ; i < (datos.cantidadFilas*2) ; i++ ){  // Recorre todas las filas
		for( unsigned int j = 0 ; j < (datos.anchoFilaDoble-datos.paddingAplicadoDoble) ; j+=3 ){  // Recorre todos los bytes de cada fila, sin pasar por los bytes de padding
			unsigned int posB = (datos.anchoFilaDoble) * i + j;
			unsigned int posG = (datos.anchoFilaDoble) * i + j + 1;
			unsigned int posR = (datos.anchoFilaDoble) * i + j + 2;
			unsigned char b = datos.arrayPixelesDuplicados[posB];
			unsigned char g = datos.arrayPixelesDuplicados[posG];
			unsigned char r = datos.arrayPixelesDuplicados[posR];

			// Si me encuentro con el color de transparencia lo reemplazo por el correspondiente (128,255,255) o (0,0,0)
			unsigned int largoZona = 64;									// Largo en pixeles
			unsigned int largoEnBytes = largoZona * datos.bytesPorPixel;	// Largo en bytes
			if( (b == datos.fondoB) && (g == datos.fondoG) && (r == datos.fondoR) ){

				if( (j % largoEnBytes*2) < largoEnBytes ){
					if( (i % largoZona*2) < largoZona ){	
						datos.arrayPixelesDuplicados[posB] = 128;
						datos.arrayPixelesDuplicados[posG] = 255;
						datos.arrayPixelesDuplicados[posR] = 255;
					}else{
						datos.arrayPixelesDuplicados[posB] = 0;
						datos.arrayPixelesDuplicados[posG] = 0;
						datos.arrayPixelesDuplicados[posR] = 0;
					}
				}else{
					if( (i % largoZona*2) < largoZona ){	
						datos.arrayPixelesDuplicados[posB] = 0;
						datos.arrayPixelesDuplicados[posG] = 0;
						datos.arrayPixelesDuplicados[posR] = 0;
					}else{
						datos.arrayPixelesDuplicados[posB] = 128;
						datos.arrayPixelesDuplicados[posG] = 255;
						datos.arrayPixelesDuplicados[posR] = 255;					
					}
				}

			}

		}
	}

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

	// Escribo el byte 2: Tamaño del archivo.
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

	unsigned int anchoConPadding = (3 * ancho) + ( 4 - ((3 * ancho)%4) ) % 4;	// Ojo: Cada fila está alineada con bloques de 4 bytes, si es necesario tiene padding al final de la misma
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

void FinalA::pruebaSortYFind(void){

	struct stDato{

		std::string str;
		int x;

		// Defino el operador "<" para ser usado por el std::sort()
		bool operator<(const stDato &otro) const {
			return ( (*this).x < otro.x );
		}

		// Defino el operador "==" para ser usado por el std::find()
		bool operator==(const stDato &otro) const {
			return ( (*this).x == otro.x );
		}

	};

	std::vector<stDato> v;
	stDato d;
	d.x = 32; v.push_back(d);
	d.x = 71; v.push_back(d);
	d.x = 12; v.push_back(d);
	d.x = 45; v.push_back(d);
	d.x = 26; v.push_back(d);
	d.x = 80; v.push_back(d);
	d.x = 53; v.push_back(d);
	d.x = 33; v.push_back(d);

	// Ordeno los stDato
	std::sort(v.begin(),v.end());

	std::cout << "Valores ordenados: ";
	for (std::vector<stDato>::iterator it=v.begin(); it!=v.end(); ++it){
		std::cout << ' ' << (*it).x;
	}
	std::cout << std::endl;

	std::cout << "Busco el stDato con valor x=34... ";
	d.x = 34;
	std::vector<stDato>::iterator it = std::find(v.begin(),v.end(),d);
	if( it == v.end()  ) std::cout << "no se encuentra\n";
	else{	std::cout << "encontrado el valor: " << (*it).x << std::endl; }

	std::cout << "Busco el stDato con valor x=33... ";
	d.x = 33;
	it = std::find(v.begin(),v.end(),d);
	if( it == v.end()  ) std::cout << "no se encuentra\n";
	else{	std::cout << "encontrado el valor: " << (*it).x << std::endl; }

	return void();
}

void FinalA::pruebaMap(void){
	
	struct stColor{

		unsigned int b;
		unsigned int g;
		unsigned int r;

		// Defino el operador "<" para ser usado por el std::map
		bool operator<(const stColor &otro) const {
			if( b < otro.b ){	
				return true;	// (2,x,x)vs(3,x,x)
			}else{
				if( b > otro.b ){	
					return false;	// (3,x,x)vs(2,x,x)
				}else{
					if( g < otro.g ){	
						return true;	// (3,2,x)vs(3,3,x)
					}else{
						if( g > otro.g ){	
							return false;		// (3,3,x)vs(3,2,x)
						}else{
							if( r < otro.r ){	
								return true;	// (3,3,2)vs(3,3,3)
							}else{
								return false;  // (3,3,3)vs(3,3,3) o (3,3,3)vs(3,3,2)
							}
						}

					}

				}

			}

		}

	};

	std::map<stColor,int> cc;
	stColor color;
	color.b = 255; color.g = 255; color.r = 32; cc.insert(std::make_pair(color,1));
	color.b = 255; color.g = 255; color.r = 71; cc.insert(std::make_pair(color,1));
	color.b = 255; color.g = 255; color.r = 12; cc.insert(std::make_pair(color,1));
	color.b = 255; color.g = 255; color.r = 45; cc.insert(std::make_pair(color,1));
	color.b = 255; color.g = 255; color.r = 26; cc.insert(std::make_pair(color,1));
	color.b = 255; color.g = 255; color.r = 80; cc.insert(std::make_pair(color,1));
	color.b = 255; color.g = 255; color.r = 53; cc.insert(std::make_pair(color,1));
	color.b = 255; color.g = 255; color.r = 33; cc.insert(std::make_pair(color,1));


	std::cout << "Valores ordenados: ";
	for (std::map<stColor,int>::iterator it=cc.begin(); it!=cc.end(); ++it){
		std::cout << ' ' << (*it).first.r;
	}
	std::cout << std::endl;

	std::cout << "Busco el stDato con valor (255,255,34)... ";
	color.b = 255; color.g = 255; color.r = 34;
	std::map<stColor,int>::iterator it = cc.find(color);
	if( it == cc.end()  ) std::cout << "no se encuentra\n";
	else{	std::cout << "encontrado el valor: " << (*it).first.r << std::endl; }

	std::cout << "Busco el stDato con valor (255,255,33)... ";
	color.b = 255; color.g = 255; color.r = 33;
	it = cc.find(color);
	if( it == cc.end()  ) std::cout << "no se encuentra\n";
	else{	std::cout << "encontrado el valor: " << (*it).first.r << std::endl; }

	return void();
}
