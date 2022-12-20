#pragma once
#include <string>
#include <SlyvGINIE.hpp>
#include <SlyvQCol.hpp>
#include <SlyvConInput.hpp>

namespace Slyvina {
namespace Units{
	extern GINIE AskGINIE;
	extern std::string AskCat;
	std::string CAsk(std::string Key, std::string Question, std::string DefaultValue = "");
	std::string Ask(std::string Cat, std::string Key, std::string Question, std::string DefaultValue = "");
	std::string CAsk(GINIE Data, std::string Key, std::string Question, std::string DefaultValue = "");
	std::string Ask(GINIE Data, std::string Cat, std::string Key, std::string Question, std::string DefaultValue = "");
	//std::string CAsk(std::shared_ptr<GINIE> Data,std::string Key, std::string Question, std::string DefaultValue = "");
	//std::string Ask(std::shared_ptr<GINIE> Data, std::string Cat, std::string Key, std::string Question, std::string DefaultValue = "");


	bool Yes(GINIE Data, std::string Cat, std::string Key, std::string Question);
	//bool Yes(std::shared_ptr<GINIE> Data, std::string Cat, std::string Key, std::string Question);


	int AskInt(GINIE Data, std::string Cat, std::string Key, std::string Question, bool AllowDefault=false, int DefaultValue=0);
	int AskInt(GINIE Data, std::string Cat, std::string Key, std::string Question, int DefaultValue);
	int AskInt(std::string Cat, std::string Key, std::string Question);
	int AskInt(std::string Cat, std::string Key, std::string Question, int DefaultValue);

}
}
