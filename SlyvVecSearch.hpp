// Lic:
// Units/Headers/SlyvVecSearch.hpp
// Slyvina - Vector Search
// version: 23.01.17
// Copyright (C) 2022, 2023 Jeroen P. Broks
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
//#include <iostream>

#include <vector>
#include <memory>

namespace Slyvina {
	namespace Units {

		template <class MyType> inline bool VecSearch(std::vector<MyType>* HayStack, MyType Needle) {
			//for (auto N : *HayStack) 
			for (auto N : *HayStack) {
				//std::cout << "VecSearch: HayItem=" << N << "; Needle=" << Needle << "\n";
				if (N == Needle) return true;
			}
			return false;
		}

		template <class MyType> inline bool VecSearch(std::vector<MyType> HayStack, MyType Needle) { return VecSearch(&HayStack, Needle); }

		template <class MyType> inline bool VecSearch(std::shared_ptr<std::vector<MyType>> HayStack, MyType Needle) { return VecSearch(HayStack.get(), Needle); }
		template <class MyType> inline bool VecSearch(std::unique_ptr<std::vector<MyType>> HayStack, MyType Needle) { return VecSearch(HayStack.get(), Needle); }

		template <class MyType> inline MyType VecPop(std::vector<MyType>*VecToPop) { 
			if (!VecToPop->size()) return MyType{};
			MyType Ret{ (*VecToPop)[VecToPop->size() - 1] };
			VecToPop->pop_back();
			return Ret;
		}

		template <class MyType> inline MyType VecPop(std::vector<MyType> VecToPop) { return VecPop(&VecToPop); }
		template <class MyType> inline MyType VecPop(std::shared_ptr<std::vector<MyType>> VecToPop) { return VecPop(VecToPop.get()); }
		template <class MyType> inline MyType VecPop(std::unique_ptr<std::vector<MyType>> VecToPop) { return VecPop(VecToPop.get()); }

		template <class MyType> inline void VecPushUnique(std::vector<MyType>* Vec, MyType Item) { if (!VecSearch(Vec, Item)) Vec->push_back(Item); }
		template <class MyType> inline void VecPushUnique(std::vector<MyType> Vec, MyType Item) { VecPushUnique(&Vec, Item); }
		template <class MyType> inline void VecPushUnique(std::unique_ptr<std::vector<MyType>> Vec, MyType Item) { VecPushUnique(Vec.get(), Item); }
		template <class MyType> inline void VecPushUnique(std::shared_ptr<std::vector<MyType>> Vec, MyType Item) { VecPushUnique(Vec.get(), Item); }
	}
}