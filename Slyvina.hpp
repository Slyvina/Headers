// Lic:
// Units/Headers/Slyvina.hpp
// Slyvina - Core Header
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


// This header file must always be accessible
// to all projects using the Slyvina libraries

// Almost ALL Slyvina projects use these
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>


#define SlyvClass(TrueClass,Class) class TrueClass; typedef std::shared_ptr<TrueClass> Class
#define XSlyvClass(TrueClass,Class) SlyvClass(TrueClass,Class); class TrueClass
// NO ';' at the end of the xSlyvClass definition. That's important, as a class creation scope needs to be able to come next.
// After SlyvClass it matters less, but better not, as it's best to do that manually in order not to spook up smart IDEs.




#pragma region platforms
#ifdef __APPLE__
	#include <TargetConditionals.h>
#endif

		#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
			#define SlyvWindows	
			#define SlyvPlat "Windows"           
			#ifdef _WIN64
				#define SlyvWin64
				#define SlyvXPlat "Windows 64"  
			#else
				#define SlyvXPlat "Windows 32"  	
				#define SlyvWin32
			#endif
		#elif defined(__APPLE__)
			#define SlyvApple
			#ifdef TARGET_IPHONE_SIMULATOR
				#define SlyvIPhoneEmulator
				#define SlyvIPhone
				#define SlyvPlat "iPhone"
				#define SlyvXPlat "iPhone Emulator"
			#elif defined(TARGET_OS_IPHONE)
				#define SlyvIPhone
				#define SlyvIPhoneReal
				#define SlyvPlat "iPhone"
				#define SlyvXPlat "iPhone"
			#elif defined(TARGET_OS_MAC)
				#define SlyvMacOS
				#define SlyvMac
				#define SlyvPlat "Mac"
				#define SlyvXPlat "Mac"
			#else
				#error "Unknown Apple platform"
			#endif
		#elif defined(__linux__)
			#define SlyvPlat "Linux"
			#define SlyvXPlat "Linux"
			#define SlyvLinux
		#elif defined(__unix__)
			#define SlyvUnix
			#define SlyvPlat "Unix"
			#define SlyvXPlat "Unix"
		#elif defined(_POSIX_VERSION)
			#define SlyvPlat "POSIX"
			#define SlyvXPlat "POSIX"
			#define SlyvPOSIX
		#else
			#error "Unknown compiler"
		#endif		

namespace Slyvina {

	typedef std::string String;

#pragma region Integer
	// Please note. This only works in x64 (LittleEndian) now. 
	// If anything changes due to other processors,
	// #ifdef should be used in detection and then coming up with 
	// new definitions are in order to make sure the definitions remain correct.
	
	typedef char Char;
	typedef unsigned char Byte;
	typedef unsigned char byte;
	typedef short int Int16;
	typedef short int int16;
	typedef unsigned short int uInt16;
	typedef unsigned short int uint16;
	
	typedef int int32;
	typedef unsigned int uint32;
	typedef int Int32;
	typedef unsigned int uInt32;
	
	typedef long long int int64;
	typedef unsigned long long int uint64;
	typedef long long int Int64;
	typedef unsigned long long int uInt64;
#pragma endregion

	inline std::string boolstring(bool k) { if (k) return "True"; else return "False"; }
	inline std::string lboolstring(bool k) { if (k) return "true"; else return "false"; }
	inline std::string uboolstring(bool k) { if (k) return "TRUE"; else return "FALSE"; }

	inline std::string Platform(bool compact = true) {
		if (compact)
			return SlyvPlat;
		else
			return SlyvXPlat;
	}

	const double PI = 3.1415926535;
	
	typedef std::shared_ptr<std::vector<String>> VecString;
	inline VecString NewVecString() { return std::make_shared<std::vector<String>>(); }

	typedef std::shared_ptr<std::map<std::string, std::string>> StringMap;
	inline StringMap NewStringMap() { return std::shared_ptr<std::map<std::string, std::string>>(new std::map<std::string,std::string>()); }
	
	// Quick creation functions!
	template<class MyType> inline MyType Nieuw() { return std::make_shared<MyType>(); }
	template<class MyType> inline std::shared_ptr<std::vector<MyType>> NewVector() { return std::make_shared<std::vector<MyType>>(); }

	inline std::string CYear(uint32 oy, uint32 yn) { if (oy > yn) return "?"; if (oy < yn) return std::to_string(oy) + "-" + std::to_string(yn); return std::to_string(yn); }
	inline std::string CYear(uint32 oy, std::string yn) { return CYear(oy, std::stoi(yn)); }
	
	template<class MyType> inline void SortVector(std::vector<MyType>* v) { std::sort(v->begin(), v->end()); }
	inline void SortVecString(VecString v) {
		if (!v) { std::cout << "SortVecString(nullptr): Cannot sort!\n\r"; return; }
		std::sort(v->begin(), v->end()); 
	}
	template<class MyType> inline bool VectorContains(std::vector<MyType>& HayStack, MyType Needle) {
		for (auto Hay : HayStack) if (Needle == Hay) return true;
		return false;
	}
	inline bool VectorContains(VecString HayStack, std::string Needle) {
		for (auto Hay : *HayStack) if (Needle == Hay) return true;
		return false;
	}
	template<class MyType> inline void VectorAddUnique(std::vector<MyType>& MyVec, MyType Value) {
		if (!VectorContains(MyVec,Value)) MyVec.push_back(Value);
	}
	inline void VectorAddUnique(VecString MyVec, std::string Value) {
		if (!VectorContains(MyVec,Value)) MyVec->push_back(Value);
	}

	inline bool VecHasString(std::vector<String>* Haystack, String Needle, bool ignorecase = true) {
		if (ignorecase)  std::transform(Needle.begin(), Needle.end(), Needle.begin(), ::toupper);
		for (auto _hay : *Haystack) {
			auto hay = _hay; if (ignorecase)  std::transform(hay.begin(), hay.end(), hay.begin(), ::toupper);
			if (hay == Needle) return true;
		}
		return false;
	}

	inline bool VecHasString(std::vector<String>HayStack, String Needle, bool ignorecase = true) { return VecHasString(&HayStack, Needle, ignorecase); }
	inline bool VecHasString(VecString HayStack, String Needle, bool ignorecase = true) { return VecHasString(HayStack.get(), Needle, ignorecase); }
}