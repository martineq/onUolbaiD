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
#define SDL_RUTA_UTIL "img/tile.png"

/************************* DIRECCIONES ***********************/
#define ACCION_NORTE "NORTE"
#define ACCION_SUR "SUR"
#define ACCION_ESTE "ESTE"
#define ACCION_OESTE "OESTE"
#define ACCION_NOROESTE "NOROESTE"
#define ACCION_NORESTE "NORESTE"
#define ACCION_SUDESTE "SUDESTE"
#define ACCION_SUDOESTE "SUDOESTE"

/************************* ACCIONES ***********************/
#define ACCION_CAMINAR "THEWALKINGDEAD"
#define ACCION_ATACAR "ATTACK"
#define ACCION_DEFENDER "SHIELD"


/*********************CONTROLES EN PANTALLA ******************/
#define DEFAULT_FONT "./src/utils/Fonts/verdana.ttf"

/**************************** YAML ***************************/

#define YAML_RUTA_ARCHIVO_JUEGO "./config/juego.yaml"
#define YAML_RUTA_ARCHIVO_CONEXION "./config/conexion.yaml"
#define YAML_RUTA_DIRECTORIO_IMG "./img/"
#define YAML_RUTA_DIRECTORIO_JUEGOS "./config/"

#define YAML_STRING_VACIO ""
#define YAML_ERROR_INT -1

#define YAML_TIPO_STRING "Cadena de caracteres"
#define YAML_TIPO_INT "Entero"

#define YAML_DEAFAULT_PANTALLA_ALTO 600
#define YAML_DEAFAULT_PANTALLA_ANCHO 800
#define YAML_DEAFAULT_VELOCIDAD_JUGADOR 200
#define YAML_DEAFAULT_MARGEN_SCROLL 20
#define YAML_DEAFAULT_NOMBRE "default"
#define YAML_DEAFAULT_IMAGEN_EXTENSION ".png"
#define YAML_DEAFAULT_RUTA_IMAGEN "default0.png"
#define YAML_DEAFAULT_ANCHO_BASE 1
#define YAML_DEAFAULT_ALTO_BASE 1
#define YAML_DEAFAULT_PIXEL_REF_X 50
#define YAML_DEAFAULT_PIXEL_REF_Y 10
#define YAML_DEAFAULT_FPS 10
#define YAML_DEAFAULT_DELAY 1
#define YAML_DEAFAULT_ALTO_NIVEL 100
#define YAML_DEAFAULT_ANCHO_NIVEL 100
#define YAML_DEAFAULT_VIDA_JUGADOR 50
#define YAML_DEAFAULT_MANA_JUGADOR 50
#define YAML_DEAFAULT_DANIO_JUGADOR 10
#define YAML_DEAFAULT_VELOCIDAD_ENEMIGO 300
#define YAML_DEAFAULT_VIDA_ENEMIGO 1
#define YAML_DEAFAULT_DANIO_ENEMIGO 1


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
#define YAML_CANTIDAD_OBLIGATORIA_DE_ANIMACIONES_PROTAGONISTA 24

/*****************************  Serializacion *****************************************/
#define TAM_BOOL sizeof(bool)
#define TAM_LONG sizeof(long)
#define TAM_LONG_LONG sizeof(long long)
#define TAM_UNSINT sizeof(unsigned int)
#define TAM_INT sizeof(int)
#define TAM_SINT sizeof (short int)
#define TAM_DBL sizeof(double)

/*****************************  Habilitación de info de Mutex *************************/
#define ESTADO_IMPRIMIR_INFO_MUTEX NO_IMPRIMIR_INFO_MUTEX  // <<< Acá hago el cambio, este es el que se toca
#define SI_IMPRIMIR_INFO_MUTEX "si"	// "si" para que imprima
#define NO_IMPRIMIR_INFO_MUTEX "no"	// "no" (o cualquier otra cosa distinto de "si") para que no imprima


/*****************************  Sockets *****************************************/
#define TAMANIO_BLOQUE 1024			// Tamaño del bloque de datos usado para envío de archivos
#define VERSION_WINSOCK_REQUERIDA 2 // Version de Winsock mínima requerida
#define ACEPTAR_TIMEOUT -2			// Código de time out al hacer el accept del servidor
#define ACEPTAR_ERROR -1			// Código de error al hacer el accept del servidor
#define PUERTO_SERVIDOR 444			// Puerto que usará el Servidor para hacer el bind
#define CLIENTE_NO_ENCONTRADO -1	// Código de identificación que indica que no se encontró un cliente
#define SELECT_OK 0					// Código de respuesta OK para el select
#define SELECT_ERROR -1				// Código de error para el select
#define SELECT_TIMEOUT -2			// Código de time out para el select
#define PERIODO_VERIFICACION_ERROR_DESCONEXION 5000	//  Valor en milisegundos. En cada periodo de tiempo se envia un paquete de prueba para comprobar el estado de la red (por si deconecta el cable)
#define SOCKETS_LOCALHOST_IP "localhost"			// IP localhost para juego single player
#define SOCKETS_LOCALHOST_PUERTO 444				// Puerto para juego single player

/*****************************  Delays *****************************************/
#define DELAY_HILO_CONEXION 1000000 // En microsegundos. 1000000 uSeg = 1 seg

/**************************** Juego ****************************/
#define ALTO_TILE 50
#define ANCHO_TILE 100
#define VELOCIDAD_SCROLL 10
#define ID_FALSO -1
#define ID_SIN_DUENIO -2
#define PERIODO_CICLO_CLIENTE 50
#define CANTIDAD_MINIMA_JUGADORES_SINGLE_PLAYER 1
#define CANTIDAD_MINIMA_JUGADORES_INICIAR_MULTI_PLAYER 2
#define CANTIDAD_MINIMA_JUGADORES_JUGAR_MULTI_PLAYER 1
#define STRING_ENEMIGO_AUTOMATICO "Enemigo_Automatico_"

// Definicion de las entidades que son Items
#define STRING_CORAZON "corazon"
#define STRING_ESCUDO "escudo"
#define STRING_ZAPATO "zapato"
#define STRING_BOTELLA "botella"
#define STRING_LAMPARA "lampara"
#define STRING_MAPA "mapa"
#define STRING_ESPADA "espada"
#define STRING_HECHIZO_HIELO "hechizo_hielo"
#define STRING_BOMBA "bomba"
#define STRING_GOLEM "golem"	// Representa en el archivo yaml al icono del item Hechizo de Golem, no al personaje con todas sus animaciones


// Tipos de Entidades que se mueven
#define TIPO_ENTIDAD_JUGADOR 1
#define TIPO_ENTIDAD_AUTOMATICO 2
#define TIPO_ENTIDAD_GOLEM 3

// Tipos de Entidades que no se mueven pero pueden desaparecer
#define TIPO_ENTIDAD_ITEM 4

// Tipos de Entidades que no se mueven ni desaparecen
#define TIPO_ENTIDAD_ESTATICO 5


// En ModeloMovimiento
#define DURACION_CALCULO_CAMINO_MINIMO 1000

// En ModeloJugador
#define RANGO_VISION 2
#define MAXIMO_ESCUDO 100
#define TIEMPO_CONGELAMIENTO 4000

// En VistaChat
#define MARGEN 20
#define ALTO_TEXTO_MENSAJES 100
#define ANCHO_TEXTO_MENSAJES 753
#define ALTO_TEXTO_INGRESADO 14
#define ANCHO_TEXTO_INGRESADO 753
#define ALTO_VENTANA 184
#define ANCHO_VENTANA 237

// En ModeloCorazon
#define VIDA_RECUPERADA 10

// En ModeloBotella
#define MAGIA_RECUPERADA 10

// En ModeloEscudo
#define ESCUDO_RECUPERADO 10

// En ModeloEspada
#define DANIO_ESPADA 10

// En ModeloHechizoHielo
#define RANGO_HECHIZO_HIELO 2

#define MAGIA_CONSUMIDA_HECHIZO_HIELO 20

// En ModeloBomba
#define DELAY_BOMBA 2000
#define DANIO_BOMBA 20
#define RANGO_BOMBA 2

// En ModeloGolem y ModeloFactory
#define ENTIDAD_GOLEM "entidad_golem"  // Representa en el archivo yaml al personaje que es un golem, no al ícono


/***************************** Fog *************************/
#define VISIBLE 2
#define CONOCIDO_NO_VISIBLE 1
#define NO_CONOCIDO 0
#define CONGELADO 1
