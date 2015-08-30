#include "StdAfx.h"
#include "PatternLoader.h"

PatternLoader::PatternLoader(std::string fileName):profileName(fileName)
{

}

bool PatternLoader::loadPattern(std::string patternName)
{
	bool loadFlag = xmlDoc.LoadFile("config.xml");

	if (!loadFlag)
	{
		return false;
	}

	rootNode = xmlDoc.FirstChildElement("Profile")->FirstChildElement(patternName.c_str());
	TiXmlElement* pNode = rootNode;

	pattern.patternID = 0;

	while(pNode)
	{
		pattern.com1 = loadBaudRate(std::string("Com1"));
		pattern.com2 = loadBaudRate(std::string("Com2"));

		pattern.bgColor = loadColorPattern(std::string("BackgroundColor"));
		pattern.textColor = loadColorPattern(std::string("TextColor"));
		pattern.buttonColor = loadColorPattern(std::string("ButtonColor"));

		pNode = pNode->NextSiblingElement();
	}

	return true;
}

Color PatternLoader::loadColorPattern(std::string& nodeName )
{
	Color tempColor = {0};
	TiXmlNode* xmlNode = rootNode->FirstChildElement(nodeName.c_str());
	TiXmlElement* xmlElement = xmlNode->FirstChildElement("red");
	tempColor.r = atoi(xmlElement->FirstChild()->Value());
	xmlElement = xmlNode->FirstChildElement("green");
	tempColor.g = atoi(xmlElement->FirstChild()->Value());
	xmlElement = xmlNode->FirstChildElement("blue");
	tempColor.b = atoi(xmlElement->FirstChild()->Value());
	return tempColor;
}

std::string PatternLoader::loadBaudRate(std::string& nodeName)
{
	std::string temp;
	std::string ratesArray[4] = {"1200","2400","4800","9600"};
	std::vector<std::string> rates(ratesArray, ratesArray+4);
	TiXmlNode* xmlNode = rootNode->FirstChildElement(nodeName.c_str());
	TiXmlElement* xmlElement = xmlNode->FirstChildElement("BaudRate");
	temp= xmlElement->FirstChild()->Value();
	std::vector<std::string>::iterator it = std::find(rates.begin(), rates.end(), temp);
	if (!temp.empty() && it != rates.end())
	{
		return temp;
	}
	temp = "2400";
	return temp;
}

bool PatternLoader::savePattern()
{
	setBaudRate(std::string("Com1"), pattern.com1);
	setBaudRate(std::string("Com2"), pattern.com2);
	setColorPattern();
	xmlDoc.SaveFile();
	return true;
}

bool PatternLoader::setBaudRate( std::string& portName, std::string& baudRate )
{
	TiXmlNode* xmlNode = rootNode->FirstChildElement(portName.c_str());
	TiXmlElement* xmlElement = xmlNode->FirstChildElement("BaudRate");
	xmlElement->FirstChild()->SetValue(baudRate.c_str());
	return true;
}

bool PatternLoader::setColorPattern()
{
	return true;
}