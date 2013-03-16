#pragma once

/****************************************************************************************************/
/** Archivo de configuracion que reune todos los valores constantes que se utilizan en el proyecto **/
/****************************************************************************************************/

/**************************** Directorios ****************************/
#define DIRECTORIO_IMG "./img"
#define DIRECTORIO_CONFIG "./config"

/**************************** Juego ****************************/

/*
#define JUEGO_PANTALLA_ANCHO_MINIMO 1
#define JUEGO_PANTALLA_ALTO_MINIMO 1
#define JUEGO_PANTALLA_ANCHO_MAXIMO 1920
#define JUEGO_PANTALLA_ALTO_MAXIMO 1080
#define JUEGO_VELOCIDAD_PERSONAJE_MAXIMA 9999
#define JUEGO_PERIODO_DEFAULT 2
#define JUEGO_INT_ERROR -1
#define FRAMES_PER_SECOND 30
*/

/**************************** Log ****************************/
#define LOG_RUTA "./DI_Log.txt"
#define LOG_NIVEL LOG_NIVEL_DEBUG_ALTO  /* <<< Acá se cambia el nivel del log, se usa uno de los de abajo */
#define LOG_NIVEL_RELEASE 1		/* Nivel 1: Release, Nivel 2: Debug Bajo, Nivel 3: Debug Alto, se pueden habilitar niveles mas altos. El nivel elegido incluye los niveles inferiores*/
#define LOG_NIVEL_DEBUG_BAJO 2
#define LOG_NIVEL_DEBUG_ALTO 3

// Para setear el uso del archivo de log
#define LOG_ESCRITURA LOG_ON  // <<< Acá se setea, se puede poner LOG_OFF o LOG_ON
#define LOG_OFF 0
#define LOG_ON 1

/**************************** SDL ****************************/
// Para el ejemplo SDL
#define PANTALLA_ANCHO 640
#define PANTALLA_ALTO 480
#define TAMANIO_SPRITE 32

/**************************** YAML ***************************/

/*
#define YAML_RUTA_ARCHIVO_JUEGO "./configuracion/juego.yaml"
#define YAML_RUTA_DIRECTORIO_IMG "./img/"
#define YAML_RUTA_DIRECTORIO_JUEGOS "./config/"
#define YAML_RUTA_IMG_DEFAULT "./img/default.png"

// Para setear el uso del archivo bak
#define YAML_LECTURA_CON_BAK YAML_BAK_OFF  // <<< Acá se setea, se puede poner YAML_BAK_OFF o YAML_BAK_ON
#define YAML_BAK_OFF 0
#define YAML_BAK_ON 1
*/


/*****************************  Sockets *****************************************/
#define TAMANIO_BLOQUE 1024			// Tamaño del bloque de datos usado para envío de archivos
#define VERSION_WINSOCK_REQUERIDA 2 // Version de Winsock mínima requerida

/*****************************  Delays *****************************************/
#define DELAY_HILO_CONEXION 1000000 // En microsegundos. 1000000 uSeg = 1 seg

/*****************************  Serializacion *****************************************/
#define TAM_BOOL sizeof(bool)
#define TAM_LONG sizeof(long)
#define TAM_LONG_LONG sizeof(long long)
#define TAM_UNSINT sizeof(unsigned int)
#define TAM_INT sizeof(int)
#define TAM_SINT sizeof (short int)
#define TAM_DBL sizeof(double)

/*****************************  Tipos de Proxy *****************************************/


/*****************************  Estados del juego *****************************************/
