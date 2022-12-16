// Lic:
// Units/Headers/SlyvQCol.hpp
// Slyvina - Quick Colors (header)
// version: 22.12.14
// Copyright (C) 2022 Jeroen P. Broks
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
/*
	This quick library and its header file have been designed with the thought of 
	color usage on the console in a cross-platform manner in mind. Since after all,
	most Unix based systems use ANSI for this by default, and Windows does by default
	not support ANSI (although it can be installed seperately), but its own system
	which Unix does not support. This quick little library should cover them both.

	When using the QCol object the correct driver should be chosen automatically.
*/

#pragma once
#include <string>
//#include "../Headers/QuickTypes.hpp"
#include "Slyvina.hpp"

namespace Slyvina {
	namespace Units {

		enum class qColor {
			Black,
			Blue,
			Green,
			Cyan,
			Red,
			Magenta,
			Brown,
			Grey,
			DarkGrey,
			LightBlue,
			LightGreen,
			LightCyan,
			Pink,
			LightMagenta,
			Yellow,
			White,
			LightRed = 12
		};

		//typedef void (*QColWrite)(qColor c, std::string s);
		typedef void (*QColColor)(qColor f, qColor b);
		typedef void (*QColReset)();

		extern bool qColErrorShow;

		class TmpPlateQCol;

		class TmpPlateQCol {
		public:
			uint16 DoingTab{ 20 };
			qColor Doing1{ qColor::Yellow };
			qColor Doing2{ qColor::LightCyan };
			qColor Error1{ qColor::Red };
			qColor Error2{ qColor::Yellow };
			QColReset Reset{ nullptr };
			//QColWrite Write{ nullptr };
			QColColor Color{ nullptr };
			std::string Name;
			void Doing(std::string a, std::string b, std::string ending = "\n");
			void Doing(std::string a, int b, std::string ending = "\n");
			void Write(qColor c, std::string w);
			void Error(std::string msg);
			void Warn(std::string msg);

			void Green(std::string a);
			void LGreen(std::string a);
			void Red(std::string a);
			void Pink(std::string a);
			void Dark(std::string a);
			void Yellow(std::string a);
			void Cyan(std::string a);
			void LCyan(std::string a);
			void Magenta(std::string a);

			TmpPlateQCol(QColColor c, QColReset r, std::string n);
		};

		extern TmpPlateQCol
			WinQCol,
			ANSI,
			* QCol;
	}
}