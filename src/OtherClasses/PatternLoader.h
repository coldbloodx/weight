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
    
    inline std::string gettitle(){return this->title; }
    inline std::string getpowered() {return this->powered; }

    inline std::string getcom1rate() {return this->com1rate; }
    inline std::string getcom2rate() {return this->com2rate; }

    inline void setcom1rate(std::string rate){this->com1rate = rate;}
    inline void setcom2rate(std::string rate){this->com2rate = rate;}

	inline std::string getskipenabled() {return this->skipenabled;}
	inline std::string getskiplabel() {return this->skiplabel; }

	inline std::string getcom1gap() {return this->com1gap; }
	inline std::string getcom2gap() {return this->com2gap; }
	inline std::string getallgap() {return this->allgap; }

    std::string com1rate;
    std::string com2rate;
    std::string title;
    std::string powered;
	std::string skipenabled;
	std::string skiplabel;
	std::string com1gap;
	std::string com2gap;
	std::string allgap;

private:
	std::string conf;
	TiXmlDocument xmldoc;
	TiXmlElement* rootnode;
};

#endif