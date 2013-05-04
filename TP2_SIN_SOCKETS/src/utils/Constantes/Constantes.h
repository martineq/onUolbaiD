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
#define SDL_RUTA_FONDO "./img/nivel.bmp"
#define SDL_IMAGEN_DEFAULT "./img/default.png"
#define SDL_RUTA_UTIL "img/tile8bits.bmp"
#define BIKINI "./img/bikini.bmp"

/************************* DIRECCIONES ***********************/
#define ACCION_NORTE "NORTE"
#define ACCION_SUR "SUR"
#define ACCION_ESTE "ESTE"
#define ACCION_OESTE "OESTE"
#define ACCION_NOROESTE "NOROESTE"
#define ACCION_NORESTE "NORESTE"
#define ACCION_SUDESTE "SUDESTE"
#define ACCION_SUDOESTE "SUDOESTE"
//#define vector<string> vector
/************************* ACCIONES ***********************/
#define ACCION_CAMINAR "THEWALKINGDEAD"
#define ACCION_ATACAR "ATTACK"
#define ACCION_DEFENDER "SHIELD"

/*********************CONTROLES EN PANTALLA ******************/
#define DEFAULT_FONT "./src/utils/Fonts/verdana.ttf"

/**************************** YAML ***************************/

#define YAML_RUTA_ARCHIVO_JUEGO "./config/juego.yaml"
#define YAML_RUTA_DIRECTORIO_IMG "./img/"
#define YAML_RUTA_DIRECTORIO_JUEGOS "./config/"

#define YAML_STRING_VACIO ""
#define YAML_ERROR_INT -1

#define YAML_TIPO_STRING "Cadena de caracteres"
#define YAML_TIPO_INT "Entero"

#define YAML_DEAFAULT_PANTALLA_ALTO 600
#define YAML_DEAFAULT_PANTALLA_ANCHO 800
#define YAML_DEAFAULT_VEL_PERSONAJE 100
#define YAML_DEAFAULT_MARGEN_SCROLL 20
#define YAML_DEAFAULT_NOMBRE "default"
#define YAML_DEAFAULT_RUTA_IMAGEN "default.png"
#define YAML_DEAFAULT_ANCHO_BASE 1
#define YAML_DEAFAULT_ALTO_BASE 1
#define YAML_DEAFAULT_PIXEL_REF_X 0
#define YAML_DEAFAULT_PIXEL_REF_Y 0
#define YAML_DEAFAULT_FPS 15
#define YAML_DEAFAULT_DELAY 1
#define YAML_DEAFAULT_ALTO_NIVEL 100
#define YAML_DEAFAULT_ANCHO_NIVEL 100

#define YAML_PANTALLA_ALTO_TOPE_MINIMO 1
#define YAML_PANTALLA_ALTO_TOPE_MAXIMO 1080
#define YAML_PANTALLA_ANCHO_TOPE_MINIMO 1
#define YAML_PANTALLA_ANCHO_TOPE_MAXIMO 1920
#define YAML_VELOCIDAD_PERSONAJE_TOPE_MINIMO 0
#define YAML_VELOCIDAD_PERSONAJE_TOPE_MAXIMO 5000
#define YAML_MARGEN_SCROLL_TOPE_MINIMO 1
#define YAML_PERSONAJE_LONGITUD_MAXIMA 50
#define YAML_FPS_TOPE_MAXIMO 99
#define YAML_DELAY_TOPE_MAXIMO 99
#define YAML_CANTIDAD_OBLIGATORIA_DE_ANIMACIONES_PROTAGONISTA 8


/**************************** Tamanio serializacion ****************************/
#define TAM_BOOL sizeof(bool)
#define TAM_LONG sizeof(long)
#define TAM_LONG_LONG sizeof(long long)
#define TAM_UNSINT sizeof(unsigned int)
#define TAM_INT sizeof(int)
#define TAM_SINT sizeof (short int)
#define TAM_DBL sizeof(double)

/**************************** Tipos de Proxy ***********************************/
#define PROXY_ENTIDAD "entidad"
#define PROXY_JUEGO "juego"
#define PROXY_CONTROLADOR "controlador"

/*****************************  Habilitación de info de Mutex *************************/
#define ESTADO_IMPRIMIR_INFO_MUTEX NO_IMPRIMIR_INFO_MUTEX  // <<< Acá hago el cambio, este es el que se toca
#define SI_IMPRIMIR_INFO_MUTEX "si"	// "si" para que imprima
#define NO_IMPRIMIR_INFO_MUTEX "no"	// "no" (o cualquier otra cosa distinto de "si") para que no imprima


/*****************************  Sockets *****************************************/
#define TAMANIO_BLOQUE 1024			// Tamaño del bloque de datos usado para envío de archivos
#define VERSION_WINSOCK_REQUERIDA 2 // Version de Winsock mínima requerida

/*****************************  Delays *****************************************/
#define DELAY_HILO_CONEXION 1000000 // En microsegundos. 1000000 uSeg = 1 seg
#define DELAY_ACCIONES_PERSONAJE 2000 // En milesimas (valor temporal hasta que lo discutamos)

/**************************** Juego ****************************/
#define ALTO_TILE 50
#define ANCHO_TILE 100
#define VELOCIDAD_SCROLL 5

/***************************** Fog *************************/
#define ZONA_VISIBLE 5
#define VISIBLE 2
#define CONOCIDO_NO_VISIBLE 1
#define NO_CONOCIDO 0

