// Lic:
// Units/Headers/SlyvConInput.hpp
// Slyvina - Console Input
// version: 22.12.16
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
#include <Slyvina.hpp>


/// <summary>
/// Quickly reads input from the console and return it as a tring
/// </summary>
/// <param name="Question">You can pop a question on the screen if you like</param>
/// <returns></returns>
inline std::string ReadLine(std::string Question="") {
	std::cout << Question;
	std::string str;
	std::getline(std::cin, str);
	return str;
}

/// <summary>
/// Similar to ReadLine(), however, this one has been adapted to easy work with pure C-strings, in other words, char arrays.
/// </summary>
/// <param name="ret"></param>
/// <param name="Question"></param>
inline void CReadLine(char* ret, const char* Question) {
	if (!sizeof(ret)) return;
	auto _ret{ ReadLine(Question) };
	strcpy_s(ret, _ret.size(), _ret.c_str());
}