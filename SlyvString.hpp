// Lic:
// Units/Headers/SlyvString.hpp
// Slyvina - Quick String Handler (header)
// version: 22.12.09
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
#pragma once
#include <algorithm>
#include<Slyvina.hpp>

namespace Slyvina {
	namespace Units {

		/// <summary>
		/// Portion of a string
		/// </summary>
		/// <param name="str"></param>
		/// <param name="start"></param>
		/// <param name="length"></param>
		/// <returns></returns>
		String Mid(String str, unsigned int start, unsigned int length);

		String Mid(String str, unsigned int start, unsigned int length, String newstring);


		inline String Left(String str, unsigned int length) { return Mid(str, 1, length); }
		inline String Right(String str, unsigned int length) {
			if (length > str.size()) return str;
			return Mid(str, (str.size() - length) + 1, length);
		}
		//string right(string str, size_t length) { return right(str, (unsigned int)length); }


		inline bool Prefixed(String str, String prefix) { return Left(str, prefix.size()) == prefix; }
		inline bool Suffixed(String str, String suffix) { return Right(str, suffix.size()) == suffix; }

		/// <summary>
		/// Find last occurance of a character in a string
		/// </summary>
		/// <param name="str"></param>
		/// <param name="ch"></param>
		/// <returns>The index number of the last occurance or -1 when the character has not been found at all</returns>
		int FindLast(String str, char ch);

		int FindLast(String haystack, String needle);

		inline int FindFirst(String str, char ch) {
			for (int i = 0; i < str.size(); i++)
				if (str[i] == ch) return i;
			return -1;
		}

		inline int FindFirst(String str, String Needle) {			
				for (int i = 0; i+Needle.size()<str.size() && i < str.size(); i++)
					if (Mid(str,i,Needle.size()) == Needle) return i;
				return -1;			
		}

		/// <summary>
		/// Replace something in a string
		/// </summary>
		/// <param name="mystr"></param>
		/// <param name="ori"></param>
		/// <param name="subst"></param>
		/// <returns></returns>
		String TReplace(String mystr, char ori, char subst);

		String TReplace(String mystr, String ori, String subst);

		String TReplace(String mystr, char ori, String subst);



		std::string ExtractDir(std::string file);

		std::string StripDir(std::string file);

		String StripExt(String file);

		inline String StripAll(String file) { return StripDir(StripExt(file)); }

		VecString Split(String str, char spltchar);

		VecString Split(String str, char spltchar, int max);


		VecString StringToLines(String str);

		String Trim(String str);

		inline void Trans2Upper(String& str) { std::transform(str.begin(), str.end(), str.begin(), ::toupper); }

		inline void Trans2Lower(String& str) { std::transform(str.begin(), str.end(), str.begin(), ::tolower); }


		inline String Upper(String str) {
			String ret = str;
			Trans2Upper(ret);
			return ret;
		}

		inline String Lower(std::string str) {
			String ret = str;
			Trans2Lower(ret);
			return ret;
		}

		/*
		string bsdec(const char* str) {
			string ret = "";
			for (int i = 0; str[i]; i++) {
				auto c = str[i];
				if (c == ' ' || (c >= 'a' && c <= 'z') || (c >= '0' && c <= ':') || (c >= 'A' && c <= 'Z'))
					ret += c;
				else {
					char fme[10];
					sprintf_s(fme, 6, "\\%03d", c);
					ret += fme;
				}
			}
			return ret;
		}
		string bsdec(string str) { return bsdec(str.c_str()); }
		*/


		inline std::string Hex(int num) {
			char H[10];
			sprintf_s(H, "%08X", num);
			return std::string(H);
		}

		inline std::string StringJoin(std::string lnk, std::vector<std::string> strs) {
			String ret{ "" };
			for (auto s : strs) {
				if (ret.size()) ret += lnk;
				ret += s;
			}
			return ret;
		}

		long long FindString(std::string Needle, std::string HayStack);


		String ExtractExt(std::string file);

		inline String Vec2Str(std::vector<char> input) {
			String s(input.begin(), input.end());
			return s;
		}


		
		String TrSPrintF(const char* fmt, ...);
	}
}