// Lic:
// Units/Headers/SlyvSTOI.hpp
// Slyvina - Alternate STOI (header)
// version: 22.12.15
// Copyright (C) 2021, 2022 Jeroen P. Broks
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
#include <string>

namespace Slyvina {
	namespace Units {
        /// <summary>
       /// Contains the last error that occurred during a string to integer conversion. When there were no errors, this variable contains an empty string.
       /// </summary>
        extern std::string STOI_Error;

        /// <summary>
        /// Converts a string to integer. Unlike std::stoi no error will be thrown if something goes wrong. STOI_Error will contain an error if something goes wrong, though.
        /// </summary>
        /// <param name="s">The string</param>
        /// <returns>The integer generated. (0 if something goes wrong. Check STOI_Error if that happens).</returns>
        int ToInt(std::string s);
        unsigned int ToUInt(std::string s);
	}
}