#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include "Serializadora.h"

class Serializable {

	public:
		virtual std::string* serialize() = 0;
		virtual int getSize() = 0;
		virtual bool hydrate(std::string* source) = 0;
		virtual ~Serializable(){};

};