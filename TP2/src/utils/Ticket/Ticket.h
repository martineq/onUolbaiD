#pragma once

#include <winsock.h>  // Para usar InterlockedIncrement()

class Ticket{

	private: 
		Ticket(void);
		Ticket(const Ticket&);
		Ticket& operator =(const Ticket&);
		static long contador;
	
	public:
		static Ticket& getInstance();
		int pedirNumero(void);
		virtual ~Ticket(void);
};

inline Ticket& Ticket::getInstance(){
	static Ticket objecto;
	return objecto;
}