// Lic:
// Units/Headers/SlyvArgParse.hpp
// Slyvina - Arg Parser (header)
// version: 22.12.25
// Copyright (C) 2020, 2022 Jeroen P. Broks
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


#include <vector>
#include <string>
#include <map>



namespace Slyvina {
	namespace Units {

		using namespace std;

		typedef struct {
			string myexe;
			map<string, bool> bool_flags;
			map<string, string> string_flags;
			map<string, int> int_flags;
			vector<string> arguments;
		} ParsedArg;

		typedef struct {
			map<string, string> flagtype;
			map<string, string> defaultvalue;
			map<string, bool> required;
		} FlagConfig;


		ParsedArg ParseArg(int l, char* args[], FlagConfig& CFG);
		void AddFlag_Bool(FlagConfig& CFG, string name, bool defaultvalue);
		void AddFlag_String(FlagConfig& CFG, string name, string defaultvalue, bool req = false);
		void AddFlag_Int(FlagConfig& CFG, string name, int defaultvalue, bool req = false);

		inline void AddFlag(FlagConfig& CFG, string name, bool defaultvalue) { AddFlag_Bool(CFG, name, defaultvalue); }
		inline void AddFlag(FlagConfig& CFG, string name, string defaultvalue, bool req = false) { AddFlag_String(CFG, name, defaultvalue, req); }
		inline void AddFlag(FlagConfig& CFG, string name, int defaultvalue, bool req = false) { AddFlag_Int(CFG, name, defaultvalue, req); }

		string ParseArgReport();
	}
}