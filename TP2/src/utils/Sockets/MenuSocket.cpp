#include "MenuSocket.h"

MenuSocket::MenuSocket(void){
	this->serv = NULL;
	this->cli = NULL;
}

MenuSocket::~MenuSocket(void){
	if (this->serv != NULL) delete this->serv;
	if (this->cli != NULL) delete this->cli;
}

std::string MenuSocket::menuVisual(){
	std::string opc;
	while ( opc.compare("s") != 0 && opc.compare("c") != 0){
		std::cout << "Ingrese \"s\" para iniciar servidor o \"c\" para iniciar cliente" << std::endl;
		getline (std::cin,opc);
		std::cout << "Ingreso: "<< opc << std::endl;
	}
	return opc;
}

void MenuSocket::cicloConfigServidor(int cantClientes,bool clientesSonIndividuales){
	std::cout << "Ingrese el puerto elegido para el servidor (Enter para 444)" << std::endl;
	std::string entradaTexto;
	getline (std::cin,entradaTexto);
	if (entradaTexto.empty()==true) entradaTexto.assign("444");
	std::cout << "Ingreso: |"<<entradaTexto <<"| "<< std::endl;
	std::stringstream str(entradaTexto);
	int puerto;
	str >> puerto;

	if (this->serv->inciarServidor(puerto)==false){
		std::cout << "Error al iniciar el servidor. Se cerrara el programa" << std::endl;
		system("pause");
		exit(-2);
	}

	int cantidadDeClientes=cantClientes;
	std::cout << "Se recibirán "<< cantidadDeClientes << " clientes, modo de envio masivo"<< std::endl;

	for(int i = 0; i<cantidadDeClientes; i++){ 
		
		bool seguir = true;
		while(seguir==true){
			long idCliente = this->serv->aceptarCliente();
			if ( idCliente != ACEPTAR_TIMEOUT && idCliente != ACEPTAR_ERROR ){
				this->ids.push_back(idCliente);
				if (clientesSonIndividuales == false){
					this->serv->setClienteMasivo(idCliente);
					std::cout << "Seteo cliente " << idCliente << " masivo" << std::endl;
				}
				seguir = false;
			}else{
				if( idCliente == ACEPTAR_ERROR ){
					std::cout << "Error al acerptar cliente!!!" << std::endl;
				}
				if( idCliente == ACEPTAR_TIMEOUT ){
					// Si hubo time out, no pasa nada, vuelvo a probar para ver si alguien quiere conectarse
					// Entro otra vez al while
				}
			}
		}


	}
/*
	if (this->serv->enviarMasivo("Hola! Este es un mensaje del servidor",sizeof("Hola! Este es un mensaje del servidor"))==false){
		std::cout << "Error al enviar desde el servidor. Se cerrara el programa" << std::endl;
		system("pause");
		exit(-2);
	}
*/

}

void MenuSocket::cicloConfigCliente(bool clientesEsIndividual){
	std::cout << "Ingrese el puerto donde se encuentra el servidor (Enter para 444)" << std::endl;
	std::string entradaTexto;
	getline (std::cin,entradaTexto);
	if (entradaTexto.empty()==true) entradaTexto.assign("444");
	std::cout << "Ingreso: |"<<entradaTexto <<"| "<< std::endl;
	std::stringstream str(entradaTexto);
	int puerto;
	str >> puerto;
	std::cout << "Ingrese el host al cual desea conectarse (Enter para \"localhost\")" << std::endl;
	entradaTexto.clear();
	getline (std::cin,entradaTexto);
	if (entradaTexto.empty()==true) entradaTexto.assign("localhost");
	std::cout << "Ingreso: |"<<entradaTexto.c_str() <<"| "<< std::endl;

	if (this->cli->iniciarCliente(entradaTexto.c_str(),puerto)==false){
		std::cout << "Error al iniciar cliente. Se cerrara el programa" << std::endl;
		system("pause");
		exit(-2);
	}else{
		if(clientesEsIndividual == true){
			this->cli->setEnvioDirecto();
		}else{
			this->cli->setEnvioIndirecto();
		}
	}

}

void MenuSocket::cicloJuegoServidor(){

	std::cout << "Se recibirán mensajes hasta recibir \"EOF\" o hasta que se cierre el cliente. " << std::endl;
	bool seguir = true;
	std::string str;
	int tamanio;
	
	while ( seguir == true ){

		seguir = this->serv->recibirMasivo(str);	// El recibirMasivo hace un new
	
		if ( seguir == true ){
			
			if ( str.size() > 0){

				if ( str.compare("EOF") == 0 ){	seguir = false;	}
				
				std::cout << "Mensaje recibido ( "<< str.size() <<" bytes): " << str << std::endl;
				
				if ( seguir == true){
					str.append("Alguien dijo: ");
					Serializadora s;
					s.addString(str);
					seguir = this->serv->enviarMasivo(s);
				}
				
			}

		}else{

			std::cout << "Error al recibir. Se cerrara el programa" << std::endl;
			system("pause");
			exit(-2);

		}
		
	}
	std::cout << "El Servidor se cerrara..."<< std::endl;
	system("pause");

}

void MenuSocket::cicloJuegoCliente(){
	bool seguir = true;
	std::string entradaTexto;
	std::string cadenaRecibida;

	while ( seguir == true ){
		std::cout << "Mensaje a enviar > ";
		getline (std::cin,entradaTexto);

		if (entradaTexto.compare("EOF")==0) seguir = false;

		Serializadora s;
		s.addString(entradaTexto);
		seguir = this->cli->enviar(s);

		if ( seguir == true){

			std::cout <<"Mensaje devueltos :\n";
			seguir = this->cli->recibir(cadenaRecibida);
			std::cout <<"Tamanio: "<< cadenaRecibida.size() <<" Mensaje devueltos: \n";

			while (seguir == true && cadenaRecibida.size() > 0 ){ 	
				std::cout << "( "<< cadenaRecibida.size() <<" bytes): " << cadenaRecibida << std::endl;
				seguir = this->cli->recibir(cadenaRecibida);
			}

		}
		std::cout << "Cliente corriendo" << std::endl;
	}
	std::cout << "El cliente se cerrara..."<< std::endl;
	system("pause");
}

void MenuSocket::prueba(void){

	std::string opc = this->menuVisual();

	if ( opc.compare("s") == 0){
		this->serv = new SocketServidor;
		this->cicloConfigServidor(1,false);
		//this->cicloArchivoServidor();
		//this->cicloArchivoServidor2();
		//this->cicloArchivoServidor3();
		this->cicloJuegoServidor();
		system("pause");
	}

	if ( opc.compare("c") == 0){
		this->cli = new SocketCliente;
		this->cicloConfigCliente(false);
		//this->cicloArchivoCliente();
		//this->cicloArchivoCliente2();
		//this->cicloArchivoCliente3();
		this->cicloJuegoCliente();
		system("pause");
	}

}


void MenuSocket::cicloArchivoServidor(){

	std::string ruta("Cartilla_Cpp.pdf");
	std::list<std::string> rutasDeArchivos;
	rutasDeArchivos.push_back(ruta);
	if (this->serv->enviarArchivosIndividual(rutasDeArchivos,this->ids.front())==false){
		std::cout << "Error al enviar archivos desde el servidor. Se cerrara el programa" << std::endl;
		system("pause");
		exit(-2);
	}

	std::cout << "termine de mandar el archivo" << std::endl;
	//system("pause");

}


void MenuSocket::cicloArchivoCliente(){

	std::cout << "Empezare a recibir el archivo" << std::endl;
	//system("pause");

	std::string ruta("Cartilla_Cpp_Recibida.pdf");
	std::list<std::string> rutasDeArchivos;
	rutasDeArchivos.push_back(ruta);
	if (this->cli->recibirArchivo(ruta.c_str()) == false){
		std::cout << "Error al recibir archivos desde el servidor. Se cerrara el programa" << std::endl;
		system("pause");
		exit(-2);
	}

}


bool MenuSocket::cicloArchivoServidor2(){

	LectorDirectorios lector;	// Para obtener todos los nombres de los archivos
	std::vector<std::string> listaArchivos;

	// Envio los archivos de configuracion
	Log::getInstance().log(1,__FILE__,__LINE__,"[SERVIDOR] enviando archivos de imagenes");
	listaArchivos = lector.leerDirectorio(DIRECTORIO_IMG);

	// Serializo el vector de strings
	Serializadora s;
	int cantidadDeArchivos = (int)listaArchivos.size();
	s.addInt(cantidadDeArchivos);
	std::cout<<"Cantidad de archivos: "<<cantidadDeArchivos<<std::endl;
	for ( int i=0 ; i < cantidadDeArchivos ; i++ ){
		std::cout<<"Agrego: "<<listaArchivos[i]<<std::endl;
		s.addString(listaArchivos[i]);
	}

	// Envio el vector de strings serializado en una cadena de chars
	std::string* pStr = s.getSerializacion();
	std::cout<<"Envio una cadena de "<<pStr->size()<<" bytes al id: "<<this->ids.front()<<std::endl;
	
	if( this->serv->enviarIndividual(s,this->ids.front()) == false ){
		delete pStr;
		std::cout<<"enviarIndividual == false\n";
		return false;
	}else{
		delete pStr;
		std::cout<<"enviarIndividual == true\n";
	}


	return true;
}

bool MenuSocket::cicloArchivoCliente2(){

	std::string cadena;

	// Recibo el vector de strings serializado en una cadena de chars
	if( this->cli->recibir(cadena) == false ) return false;
	std::cout<<"tamanioRecibido: "<<cadena.size()<<std::endl;
	if( cadena.size() > 0 ){

	}else{
		// "Error al obtener archivos"
		return false;
	}

	// Hidrato el vector de strings y recibo cada archivo
	int cantidadDeArchivos = 0;
	std::cout<<"tamanioCadena: "<<cadena.size()<<std::endl;
	Serializadora s(&cadena);
	cantidadDeArchivos = s.getInt();
	std::cout<<"Cantidad de archivos: "<<cantidadDeArchivos<<std::endl;
	for ( int i=0 ; i < cantidadDeArchivos ; i++ ){
		std::string rutaDestino(s.getString());
		std::cout<<"Recibo: "<<rutaDestino<<std::endl;
	}
	system("pause");
	return true;
}


bool MenuSocket::cicloArchivoServidor3(){

	LectorDirectorios lector;	// Para obtener todos los nombres de los archivos
	std::vector<std::string> listaArchivos;
	std::list<std::string> listaArch;

	// Envio los archivos de configuracion
	Log::getInstance().log(1,__FILE__,__LINE__,"[SERVIDOR] enviando archivos de imagenes");
	listaArchivos = lector.leerDirectorio(DIRECTORIO_IMG);

	// Serializo el vector de strings
	Serializadora s;
	int cantidadDeArchivos = (int)listaArchivos.size();
	s.addInt(cantidadDeArchivos);
	std::cout<<"Cantidad de archivos: "<<cantidadDeArchivos<<std::endl;
	for ( int i=0 ; i < cantidadDeArchivos ; i++ ){
		std::cout<<"Agrego: "<<listaArchivos[i]<<std::endl;
		s.addString(listaArchivos[i]);
		listaArch.push_back(listaArchivos[i]);
	}

	// Envio el vector de strings serializado en una cadena de chars
	std::string* pStr = s.getSerializacion();
	std::cout<<"Envio una cadena de "<<pStr->size()<<" bytes al id: "<<this->ids.front()<<std::endl;

	if( this->serv->enviarIndividual(s,this->ids.front()) == false ){
		delete pStr;
		std::cout<<"enviarIndividual == false\n";
		return false;
	}else{
		delete pStr;
		std::cout<<"enviarIndividual == true\n";
	}

	if (this->serv->enviarArchivosIndividual(listaArch,this->ids.front())==false){
		std::cout << "Error al enviar archivos desde el servidor. Se cerrara el programa" << std::endl;
		system("pause");
		exit(-2);
	}

	std::cout << "termine de mandar el archivo" << std::endl;
	system("pause");
	return true;
}

bool MenuSocket::cicloArchivoCliente3(){

	std::string cadena;

	// Recibo el vector de strings serializado en una cadena de chars
	if( this->cli->recibir(cadena) == false ) return false;
	std::cout<<"tamanioRecibido: "<<cadena.size()<<std::endl;
	if( cadena.size() > 0 ){

	}else{
		// "Error al obtener archivos"
		return false;
	}

	// Hidrato el vector de strings y recibo cada archivo
	int cantidadDeArchivos = 0;
	std::cout<<"tamanioCadena: "<<cadena.size()<<std::endl;
	Serializadora s(&cadena);
	cantidadDeArchivos = s.getInt();
	std::cout<<"Cantidad de archivos: "<<cantidadDeArchivos<<std::endl;
	for ( int i=0 ; i < cantidadDeArchivos ; i++ ){
		std::string rutaDestino(s.getString());
		rutaDestino.append(".RECIBIDO");
		std::cout<<"Recibo: "<<rutaDestino<<std::endl;
		if (this->cli->recibirArchivo(rutaDestino.c_str()) == false){
			std::cout << "Error al recibir archivos desde el servidor. Se cerrara el programa" << std::endl;
			system("pause");
			exit(-2);
		}
		std::cout<<"Recibido: "<<rutaDestino<<std::endl;
	}

	system("pause");
	return true;
}

