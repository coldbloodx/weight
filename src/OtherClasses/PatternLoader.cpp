#include "StdAfx.h"
#include "PatternLoader.h"

ConfParser::ConfParser(std::string filename):conf(filename)
{

}

bool ConfParser::load()
{
	bool loadFlag = xmldoc.LoadFile(conf.c_str());

	if (!loadFlag)
	{
		return false;
	}

	rootnode = xmldoc.FirstChildElement("Profile");
	TiXmlElement* pNode = rootnode;
    
    this->com1rate = rootnode->FirstChildElement("com1")->Attribute("rate");
    this->com2rate = rootnode->FirstChildElement("com2")->Attribute("rate");
    this->title = rootnode->FirstChildElement("title")->Attribute("str");
    this->powered = rootnode->FirstChildElement("powered")->Attribute("str");

	this->skipenabled = rootnode->FirstChildElement("skip")->Attribute("enabled");
	this->skiplabel = rootnode->FirstChildElement("skip")->Attribute("str");

	this->com1gap = rootnode->FirstChildElement("threshold")->Attribute("com1");
	this->com2gap = rootnode->FirstChildElement("threshold")->Attribute("com2");
	this->allgap = rootnode->FirstChildElement("threshold")->Attribute("all");
	return true;
}


bool ConfParser::save()
{
    rootnode->FirstChildElement("com1")->SetAttribute("rate", com1rate.c_str());
    rootnode->FirstChildElement("com2")->SetAttribute("rate", com2rate.c_str());
    xmldoc.SaveFile(conf.c_str());
	return true;
}
