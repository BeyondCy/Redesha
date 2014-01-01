#include "xmlsettings.h"


using namespace Redesha;

XMLSettings::XMLSettings(const char* fileName)
{
	this->xmlFile = new rapidxml::file<>(fileName);
	this->parse<0>(this->xmlFile->data());
}


XMLSettings::~XMLSettings(void)
{
	delete this->xmlFile;
}