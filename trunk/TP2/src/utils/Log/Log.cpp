#include "Log.h"

Log::Log(const Log&){
	if( LOG_ESCRITURA == LOG_ON){
		this->archLog = NULL;
		this->archLog = new std::ofstream(LOG_RUTA,std::ios::app);

		if (!this->archLog){ //si no pudo abrirlo
		   std::cerr << "No se puede abrir archivo de Log." << std::endl;
		   exit(-1);
		}
	}
}

Log::Log(){
	if( LOG_ESCRITURA == LOG_ON){
		this->archLog = NULL;
		this->archLog = new std::ofstream();
		this->archLog->open(LOG_RUTA);			// Abro el archivo en modo escritura, y si no exite lo crea y lo abre
		
		 if (!this->archLog){ //si no pudo abrirlo
			std::cerr << "No se puede abrir archivo de Log("<<LOG_RUTA<<")." << std::endl;
			exit(1);
		 }

		time_t timestamp;
		time(&timestamp);
		std::string fechaHora(ctime(&timestamp),24);
		fechaHora = fechaHora.substr(11,8); 

		*(this->archLog) << "==================== TALLER DE PROGRAMACION I - CATEDRA AZCURRA, 1er Cuat. 2013 ==================== \n"  
						 << "--------------------------------------------- Diablo I --------------------------------------------- \n"
						 << "--------------------------------------------- "<< fechaHora <<" ---------------------------------------------  \n\n";
	}
}

void Log::log(int nivel, std::string archivo, int linea, std::string mensaje, std::string valor){
	if( LOG_ESCRITURA == LOG_OFF) return void();
	std::stringstream claveValor;
	claveValor << mensaje << valor;
	Log::log(nivel, archivo, linea, claveValor.str());
}

void Log::log(int nivel, std::string archivo, int linea, std::string mensaje, double valor){
	if( LOG_ESCRITURA == LOG_OFF) return void();
	std::stringstream claveValor;
	claveValor << mensaje << valor;
	Log::log(nivel, archivo, linea, claveValor.str());
}

void Log::log(int nivel, std::string archivo, int linea, std::string mensaje, long valor){
	if( LOG_ESCRITURA == LOG_OFF) return void();
	std::stringstream claveValor;
	claveValor << mensaje << valor;
	Log::log(nivel, archivo, linea, claveValor.str());
}

void Log::log(int nivel, std::string archivo, int linea, std::string mensaje, unsigned int valor){
	if( LOG_ESCRITURA == LOG_OFF) return void();
	std::stringstream claveValor;
	claveValor << mensaje << valor;
	Log::log(nivel, archivo, linea, claveValor.str());
}

void Log::log(int nivel, std::string archivo, int linea, std::string mensaje, int valor){
	if( LOG_ESCRITURA == LOG_OFF) return void();
	std::stringstream claveValor;
	claveValor << mensaje << valor;
	Log::log(nivel, archivo, linea, claveValor.str());
}

void Log::log(int nivel, std::string archivo, int linea, std::string mensaje){
	if( LOG_ESCRITURA == LOG_OFF) return void();
	std::stringstream lineaStr;
	lineaStr<<linea;
	Log::log(nivel, archivo,lineaStr.str(),mensaje );
}

// Escribe en el archivo de log el <mensaje>, 
void Log::log(int nivel, std::string archivo, std::string linea, std::string mensaje){
	if( LOG_ESCRITURA == LOG_OFF) return void();

	time_t timestamp;
	time ( &timestamp );
	std::string fechaHora(ctime(&timestamp),24);
	fechaHora = fechaHora.substr(11,8); // Me quedo solo con la hora
	
	// Le doy formato al nombre de archivo
	archivo = this->obtenerNombreDesdeRuta(archivo);

	// Acá filtro los logs que son de niveles superiores
	if (nivel <= LOG_NIVEL){
		std::string txt;

		if(LOG_NIVEL == LOG_NIVEL_RELEASE){	// Si es LOG_NIVEL_RELEASE no imprimo los nombres de los fuentes
			txt.append(fechaHora+(std::string)" --> "+mensaje+(std::string)"\n");
			this->archLog->write(txt.c_str(),txt.size());
		}else{								// Cuando no es LOG_NIVEL_RELEASE imprimo todos los datos que tengo
			txt.append(fechaHora+(std::string)" - "+archivo+(std::string)" - "+linea+(std::string)" --> "+mensaje+(std::string)"\n");
			this->archLog->write(txt.c_str(),txt.size());
		}

		this->archLog->flush();
	}

}

Log::~Log(){
	if( LOG_ESCRITURA == LOG_ON){
		if (this->archLog != NULL){
			*(this->archLog) << "\n\n\n";
			this->archLog->close();
			delete this->archLog;
		}
	}
}

std::string Log::obtenerNombreDesdeRuta(std::string rutaCompleta){
	
	std::string salida;
	int posUltimaBarra = 0;

	for ( unsigned int i=0 ; i < rutaCompleta.length() ; i++ ){
		if( rutaCompleta[i] == '/' || rutaCompleta[i] == '\\') posUltimaBarra = i;
	}

	if(  ( (int)posUltimaBarra > 0 ) && ( (int) posUltimaBarra < (int) (rutaCompleta.length()-1) )  ) salida = rutaCompleta.substr(posUltimaBarra+1);

	return salida;
}