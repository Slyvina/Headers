// Lic:
// Units/Headers/SlyvRandom.hpp
// Slyvina - Random
// version: 22.12.18
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


/*
 * Randomizer. This has only been made more simply.
 * No .cpp code required! It's all inline. There's too little code involved here.
 */

#pragma once

#include <stdlib.h> 
#include <time.h> 

namespace Slyvina {
	namespace Units {
		class _CRandom {
		private:
			int _seed{ 0 };
		public:			
			inline void Seed(unsigned int seed = 0) {
				if (seed == 0U)
					Seed(time(NULL));
				else 
					srand(seed);
			}
			int Get(unsigned int Max) { return rand() % (Max + 1); }
			int Get(int Min, int Max) {
				auto r = Max - Min;
				if (r <= 0) return 0; // This cannot be done, folks!
				return Get(r) + Min;
			}
			_CRandom() { Seed(); }
		};

		static _CRandom Rand;
	}
}