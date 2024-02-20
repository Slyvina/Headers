// Lic:
// Units/Headers/DieParse.hpp
// Die Parse
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

namespace Slyvina {
	namespace Units {
		byte D2();
		byte D4();
		byte D6();
		byte D8();
		byte D10(bool zero = true);
		byte D12();
		byte D20();
		byte D30();
		byte D100(bool zero = true);


		// Quick and Dirty Parse! It's not fast or anything, but it works, and that's what matters.
		extern byte QDMax;
		std::string QDParse(std::string p);
	}
}