// Lic:
// Units/Headers/SlyvAsk.hpp
// Ask (Header)
// version: 23.07.29
// Copyright (C) 2022, 2023 Jeroen P. Broks
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
// EndLic
#pragma once
#include <string>
#include <SlyvGINIE.hpp>
#include <SlyvQCol.hpp>
#include <SlyvConInput.hpp>

namespace Slyvina {
	namespace Units {
		extern GINIE AskGINIE;
		extern std::string AskCat;
		std::string CAsk(std::string Key, std::string Question, std::string DefaultValue = "");
		std::string Ask(std::string Cat, std::string Key, std::string Question, std::string DefaultValue = "");
		std::string CAsk(GINIE Data, std::string Key, std::string Question, std::string DefaultValue = "");
		std::string Ask(GINIE Data, std::string Cat, std::string Key, std::string Question, std::string DefaultValue = "");
		std::string Ask(UGINIE Data, std::string Cat, std::string Key, std::string Question, std::string DefaultValue = "");
		//std::string CAsk(std::shared_ptr<GINIE> Data,std::string Key, std::string Question, std::string DefaultValue = "");
		//std::string Ask(std::shared_ptr<GINIE> Data, std::string Cat, std::string Key, std::string Question, std::string DefaultValue = "");


		bool Yes(GINIE Data, std::string Cat, std::string Key, std::string Question);
		bool Yes(std::string Cat, std::string Key, std::string Question);
		//bool Yes(std::shared_ptr<GINIE> Data, std::string Cat, std::string Key, std::string Question);

		bool QuickYes(std::string Question);


		int AskInt(GINIE Data, std::string Cat, std::string Key, std::string Question, bool AllowDefault = false, int DefaultValue = 0);
		int AskInt(GINIE Data, std::string Cat, std::string Key, std::string Question, int DefaultValue);
		int AskInt(std::string Cat, std::string Key, std::string Question);
		int AskInt(std::string Cat, std::string Key, std::string Question, int DefaultValue);


		std::vector<std::string>* AskList(GINIE Data, std::string Cat, std::string Key, std::string Question,uint32 minanswers=1);
	}
}