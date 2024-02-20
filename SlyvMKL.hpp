// Lic:
// Units/Headers/SlyvMKL.hpp
// MKL for Slyvina (header)
// version: 23.06.23
// Copyright (C) 2023 Jeroen P. Broks
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

#include <Slyvina.hpp>
#include <SlyvString.hpp>
#include <algorithm>
#include <iostream>

// This line must be present in any of the source files when using MKL as long as it's only found ONCE in an entire project. The same file as were int main() is found could be a good idea.
#define MKL_Init std::map<std::string, Slyvina::Units::TMKL> Slyvina::Units::MKL_Register{Slyvina::Units::_MKL_Init()};

namespace Slyvina {
	namespace Units {
		class TMKL {
		public:
			uint32 Day{ 0 }, Month{ 0 }, Year{ 0 };
			std::string Src{ "" }, Lic{ "" };
			inline int32 SYear(bool m100=false) {
				if (m100) return Year % 100;
				if (Year < 2000 || Year>2099)
					throw std::exception("SYear only works in a year from 2000 till 2099");
				return Year - 2000;
			}

			inline std::string uVersion() {
				char ret[12];
				//std::cout << "DEBUG:\t" << SYear() << "\t" << Month << "\t" << Day << "\n";
				sprintf_s(ret, "%02d.%02d.%02d", SYear(true), Month, Day);
				return ret;
			}

			inline uint32 Num() { return Day + (Month * 100) + (Year * 10000); }

		};

		extern std::map<std::string, TMKL> MKL_Register;

		inline void MKL_Version(std::string File, uint32 d, uint32 m, uint32 y,bool no2000=false) {
			if (y < 100 && (!no2000)) y += 2000;
			MKL_Register[File].Day = d;
			MKL_Register[File].Month = m;
			MKL_Register[File].Year = y;
			MKL_Register[File].Src = File;
		}

		inline void MKL_Version(std::string File, std::string Ver) {
			try {
				auto
					_y{ Ver.substr(0,2) },
					_m{ Ver.substr(3,2) },
					_d{ Ver.substr(6,2) };
				auto
					y{ std::stoi(_y) },
					m{ std::stoi(_m) },
					d{ std::stoi(_d) };
				MKL_Version(File, y, m, d);
			} catch (std::exception err) {
				printf("\7\x1b[31m;ERROR:\x1b[0m; MKL_Version(\"%s\",\"%s\"): %s\n", File.c_str(), Ver.c_str(), err.what());
			}
		}

		inline void MKL_VersionP(std::string File, std::string DTE) {
			static std::map<std::string, uint32> months{ {"JAN",1},{"FEB",2},{"MAR",3},{"APR",4},{"MAY",5},{"JUN",6},{"JUL",7},{"AUG",8},{"SEP",9},{"OCT",10},{"NOV",11},{"DEC",12} };
			std::transform(DTE.begin(), DTE.end(), DTE.begin(), ::toupper);
			DTE = StReplace(DTE,"  ", " ");
			std::string DTEA[3]{ "","","" };
			{
				byte idx{ 0 };
				for (byte i = 0; i < DTE.size() && idx < 3; i++) { if (DTE[i] == 32u) idx++; else DTEA[idx] += DTE[i]; }
				//std::cout << DTEA[0] << "\t" << DTEA[1] << "\t" << DTEA[2] << "\n";
				if (months.count(DTEA[0])) MKL_Version(File,std::stoi(DTEA[1]), months[DTEA[0]], std::stoi(DTEA[2]));
				else if (months.count(DTEA[1])) MKL_Version(File, std::stoi(DTEA[0]), months[DTEA[1]], std::stoi(DTEA[2]));
				else printf("\7\x1b[31m;ERROR:\x1b[0m; MKL_VersionP(\"%s\",\"%s\"): Parse failure\n", File.c_str(), DTE.c_str() );
			}
		}

		inline void MKL_Lic(std::string File, std::string L) { MKL_Register[File].Lic = L; }

		inline std::string ShowAll(int tab,bool Lic=true) {
			std::string ret{ "" };
			for (auto r : MKL_Register) {
				auto rec{ &r.second };
				std::string l = rec->Src.substr(0,tab-1)+" ";
				while (l.size() < tab) l += "."; l += " ";
				l += rec->uVersion();
				if (Lic) l += rec->Lic;
				ret += l + "\n";
			}
		}
		
		inline std::string ShowAll(bool Lic = true) {
			uint32 tab = 40;
			for (auto r : MKL_Register) tab = std::max(tab, (uint32)r.second.Src.size() + 1);
			return ShowAll(tab, Lic);
		}

		inline std::string Newest() {
			uint32 b{ 0 };
			std::string rec{ "" };
			for (auto r : MKL_Register) {
				if (b < r.second.Num()) {
					b = r.second.Num();
					rec = r.second.uVersion();
				}
			}
			return rec;
		}

		inline std::map<std::string, Slyvina::Units::TMKL> _MKL_Init() {
			return std::map<std::string, Slyvina::Units::TMKL>();
		}
	}

}