#pragma once

#include "./VistaNivel.h"
#include "../../utils/yaml/ParserYaml.h"

class VistaFactory{

	public:
		VistaFactory(void);
		~VistaFactory(void);

		bool crearVistaNivel(VistaNivel& vistaNivel);
};
