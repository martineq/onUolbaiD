#pragma once

/****************************************************************************************************/
/** Archivo de configuracion que reune todos los valores constantes que se utilizan en el proyecto **/
/****************************************************************************************************/

/**************************** Directorios ****************************/
#define DIRECTORIO_IMG "./img"
#define DIRECTORIO_CONFIG "./config"

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
#define SDL_RUTA_SPRITE "./img/sprite.bmp"
#define SDL_RUTA_PASTO "./img/pasto.bmp"

/**************************** YAML ***************************/

#define YAML_RUTA_ARCHIVO_JUEGO "./config/juego.yaml"
#define YAML_RUTA_DIRECTORIO_IMG "./img/"
#define YAML_RUTA_DIRECTORIO_JUEGOS "./config/"
#define YAML_RUTA_IMG_DEFAULT "./img/default.png"
#define YAML_ERROR_INT -1

/*****************************  Sockets *****************************************/
#define TAMANIO_BLOQUE 1024			// Tamaño del bloque de datos usado para envío de archivos
#define VERSION_WINSOCK_REQUERIDA 2 // Version de Winsock mínima requerida

/*****************************  Delays *****************************************/
#define DELAY_HILO_CONEXION 1000000 // En microsegundos. 1000000 uSeg = 1 seg

/**************************** Juego ****************************/
