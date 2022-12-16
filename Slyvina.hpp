// Lic:
// Units/Headers/Slyvina.hpp
// Slyvina - Core Header
// version: 22.12.15
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


// This header file must always be accessible
// to all projects using the Slyvina libraries

// Almost ALL Slyvina projects use these
#include <memory>
#include <string>
#include <iostream>
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
			#ifdef _WIN64
				#define SlyvWin64
			#else
				#define SlyvWin32
			#endif
		#elif defined(__APPLE__)
			#define SlyvApple
			#ifdef TARGET_IPHONE_SIMULATOR
				#define SlyvIPhoneEmulator
				#define SlyvIPhone
			#elif defined(TARGET_OS_IPHONE)
				#define SlyvIPhone
				#define SlyvIPhoneReal
		    #elif defined(TARGET_OS_MAC)
				#define SlyvMacOS
				#define SlyvMac
			#else
				#error "Unknown Apple platform"
			#endif
		#elif defined(__linux__)
			#define SlyvLinux
		#elif defined(__unix__)
			#define SlyvUnix
		#elif defined(_POSIX_VERSION)
			#define SlyvPOSIX
		#else
		#   error "Unknown compiler"
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

	const double PI = 3.1415926535;
	
	typedef std::shared_ptr<std::vector<String>> VecString;
	inline VecString NewVecString() { return std::make_shared<std::vector<String>>(); }

	typedef std::shared_ptr<std::map<std::string, std::string>> StringMap;
	inline StringMap NewStringMap() { return std::make_shared<std::map<std::string, std::string>>(); }
	
	// Quick creation functions!
	template<class MyType> inline MyType Nieuw() { return std::make_shared<MyType>(); }
	template<class MyType> inline std::shared_ptr<std::vector<MyType>> NewVector() { return std::make_shared<std::vector<MyType>>(); }
	
}