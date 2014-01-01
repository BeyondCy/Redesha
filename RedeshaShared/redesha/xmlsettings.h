#pragma once

#include <fstream>
#include <string>

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

namespace Redesha
{

	class XMLSettings : public rapidxml::xml_document<>
	{
	public:
		XMLSettings(const char* fileName);
		~XMLSettings(void);

	private:
		rapidxml::file<>* xmlFile;
	};

};

