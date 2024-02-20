// Lic:
// head/june19_textfield.hpp
// June 19 - Textfield (header)
// version: 23.05.11
// Copyright (C) 2020, 2021, 2023 Jeroen P. Broks
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


#include "june19_core.hpp"

namespace Slyvina {
	namespace June19 {

		// Creates a text field. When you don't set the "height" paramater, the textfield will automatically adjust the height based on the chosen font.
		j19gadget* CreateTextfield(int x, int y, int w, j19gadget* ouwe, std::string defaultvalue = "");
		// Creates a text field.
		j19gadget* CreateTextfield(int x, int y, int w, int h, j19gadget* ouwe, std::string defaultvalue = "");
	}
}