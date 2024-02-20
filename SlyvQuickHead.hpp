// Lic:
// Units/Headers/SlyvQuickHead.hpp
// Slyvina Quick Head (header)
// version: 23.06.23
// Copyright (C) Slyvina Quick Head (header), 2023 Jeroen P. Broks
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
#include "Slyvina.hpp"
#include "SlyvString.hpp"
#include "SlyvMKL.hpp"
#include "SlyvQCol.hpp"

namespace Slyvina {
	namespace Units {
		inline void QuickHeader(std::string Name, uint32 year = 0, std::string Lic = "General Public License 3", std::string Author = "Jeroen P. Broks") {
			if (!year) year = std::stoi(Right(__DATE__, 4));
			QCol->LGreen(Name + "\n\n");;
			QCol->Doing("Coded by", Author);
			QCol->Doing("Version", Newest());
			QCol->Magenta(TrSPrintF("(c) Copyright %s %s, %s\n",Author.c_str(), CYear(year, Right(__DATE__, 4)).c_str(),Lic.c_str()));
			QCol->Reset(); std::cout << std::endl;
		}
	}
}