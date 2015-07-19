#include "..\StdAfx.h"
#include "..\ExternClasses\header\tinyxml.h"

#ifndef _PATTERNLOADER
#define _PATTERNLOADER
struct Color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

struct ConfigPattern
{
	char patternID;
	std::string com1;
	std::string com2;
	Color bgColor;
	Color textColor;
	Color buttonColor;
};

class PatternLoader
{
public:
	PatternLoader(std::string fileName);
	bool loadPattern(std::string patternName);
	bool savePattern();
	ConfigPattern pattern;
private:
	std::string loadBaudRate(std::string& nodeName);
	bool setBaudRate( std::string& portName, std::string& baudRate);
	Color loadColorPattern(std::string& nodeName);
	bool setColorPattern();
	std::string profileName;
	TiXmlDocument xmlDoc;
	TiXmlElement* rootNode;
};

#endif