// Lic:
// Units/Headers/SlyvString.hpp
// Slyvina - Quick String Handler (header)
// version: 24.02.18
// Copyright (C) 2022, 2023, 2024 Jeroen P. Broks
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
#include <Slyvina.hpp>

namespace Slyvina {
	namespace Units {

		/// <summary>
		/// Portion of a std::string
		/// </summary>
		/// <param name="str"></param>
		/// <param name="start"></param>
		/// <param name="length"></param>
		/// <returns></returns>
		std::string Mid(std::string str, unsigned int start, unsigned int length);

		std::string Mid(std::string str, unsigned int start, unsigned int length, std::string newstring);


		inline std::string Left(std::string str, unsigned int length) { return Mid(str, 1, length); }
		inline std::string Right(std::string str, unsigned int length) {
			if (length > (unsigned int)str.size()) return str;
			return Mid(str, ((unsigned int)str.size() - length) + 1, length);
		}
		//std::string right(std::string str, size_t length) { return right(str, (unsigned int)length); }


		inline bool Prefixed(std::string str, std::string prefix) { return Left(str, (unsigned int)prefix.size()) == prefix; }
		inline bool Suffixed(std::string str, std::string suffix) { return Right(str, (unsigned int)suffix.size()) == suffix; }

		/// <summary>
		/// Find last occurance of a character in a std::string
		/// </summary>
		/// <param name="str"></param>
		/// <param name="ch"></param>
		/// <returns>The index number of the last occurance or -1 when the character has not been found at all</returns>
		int FindLast(std::string str, char ch);

		int FindLast(std::string haystack, std::string needle);

		inline int FindFirst(std::string str, char ch) {
			for (int i = 0; i < str.size(); i++)
				if (str[i] == ch) return i;
			return -1;
		}

		inline int FindFirst(std::string str, std::string Needle) {			
				for (int i = 0; i+Needle.size()<str.size() && i < str.size(); i++)
					if (Mid(str,i,(unsigned int)Needle.size()) == Needle) return i;
				return -1;			
		}

		/// <summary>
		/// Replace something in a std::string
		/// </summary>
		/// <param name="mystr"></param>
		/// <param name="ori"></param>
		/// <param name="subst"></param>
		/// <returns></returns>
		std::string ChReplace(std::string mystr, char ori, char subst); // I don't know, but when the Slyvina definition the linker goes lying about the situation. That is why I sometimes HATE C and C++.

		std::string StReplace(std::string mystr, std::string ori, std::string subst);

		std::string CSReplace(std::string mystr, char ori, std::string subst);



		std::string ExtractDir(std::string file);

		std::string StripDir(std::string file);

		std::string StripExt(std::string file);

		inline std::string StripAll(std::string file) { return StripDir(StripExt(file)); }

		VecString Split(std::string str, char spltchar);

		VecString Split(std::string str, char spltchar, int max);


		VecString StringToLines(std::string str);

		std::string Trim(std::string str);

		inline void Trans2Upper(std::string& str) { std::transform(str.begin(), str.end(), str.begin(), ::toupper); }

		inline void Trans2Lower(std::string& str) { std::transform(str.begin(), str.end(), str.begin(), ::tolower); }


		inline std::string Upper(std::string str) {
			std::string ret = str;
			Trans2Upper(ret);
			return ret;
		}

		inline std::string Lower(std::string str) {
			std::string ret = str;
			Trans2Lower(ret);
			return ret;
		}

		/*
		std::string bsdec(const char* str) {
			std::string ret = "";
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
		std::string bsdec(std::string str) { return bsdec(str.c_str()); }
		*/


		inline std::string Hex(int num) {
			char H[10];
			sprintf_s(H, "%08X", num);
			return std::string(H);
		}

		inline std::string StringJoin(std::string lnk, std::vector<std::string> strs) {
			std::string ret{ "" };
			for (std::string s : strs) {
				if (ret.size()) ret += lnk;
				ret += s;
			}
			return ret;
		}

		long long FindString(std::string Needle, std::string HayStack);


		std::string ExtractExt(std::string file);

		inline std::string Vec2Str(std::vector<char> input) {
			std::string s(input.begin(), input.end());
			return s;
		}


		/// <summary>
		/// A quicker way for sprintf. Having to go trough all the trouble creating a c-string, and converting that into a C++ string class and blah blah blah was getting on my nerves!
		/// </summary>
		/// <param name="fmt">C format string</param>
		/// <param name="">The values to be parsed in</param>
		/// <returns>The Formatted string</returns>
		std::string TrSPrintF(const char* fmt, ...);

		std::wstring ToWString(const std::string& s);
		std::string FromWString(std::wstring ws);

		std::string Repeat(std::string s, uint64 times);
	}
}