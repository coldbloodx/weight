#include "StdAfx.h"
#include "tinyxml.h"

#ifndef _PATTERNLOADER
#define _PATTERNLOADER

class ConfParser
{
public:
	ConfParser(std::string filename);
	bool load();
	bool save();
    
    std::string gettitle(){return this->title; }
    std::string getpowered() {return this->powered; }

    std::string getcom1rate() {return this->com1rate; }
    std::string getcom2rate() {return this->com2rate; }

    void setcom1rate(std::string rate){this->com1rate = rate;}
    void setcom2rate(std::string rate){this->com2rate = rate;}

    std::string com1rate;
    std::string com2rate;
    std::string title;
    std::string powered;

private:
	std::string conf;
	TiXmlDocument xmldoc;
	TiXmlElement* rootnode;
};

#endif