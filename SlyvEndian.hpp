// Lic:
// Units/Headers/SlyvEndian.hpp
// Slyvina - Endian Handler (header)
// version: 23.03.06
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
#include "Slyvina.hpp"

namespace Slyvina {
	namespace Units {

		enum class Endian { Ignore, Little, Big };

		union __AllNum {
			char ch;
			byte bt;
			int16 i16;
			uint16 ui16;
			int32 i32;
			uint32 ui32;
			int64 i64;
			uint64 ui64;
			char check[16];
		};

		inline bool IsLittleEndian() {
			__AllNum A; 
			A.i16 = 1;
			return A.check[0];
		}
		inline bool IsBigEndian() { return !IsLittleEndian(); }

		inline __AllNum __Swap(__AllNum O, size_t L) {
			__AllNum T{};
			for (byte i = 0; i < L; ++i) T.check[(L - 1) - i] = O.check[i];
			return T;
		}

		

#define SlyvConv(type,fld) \
		inline type FromLittle(type v) { \
			if (IsLittleEndian()) return v; else {\
				__AllNum O; O.fld=v;\
				__AllNum T = __Swap(O,sizeof(type));\
				return T.fld;\
			}\
		}\
		\
		inline type FromBig(type v) { \
			if (IsBigEndian()) return v; else {\
				__AllNum O; O.fld=v;\
				__AllNum T = __Swap(O,sizeof(type));\
				return T.fld;\
			}\
		}\
	inline type ToLittle(type v) { \
			if (IsLittleEndian()) return v; else {\
				__AllNum O; O.fld=v;\
				__AllNum T = __Swap(O,sizeof(type));\
				return T.fld;\
			}\
		}\
		\
		inline type ToBig(type v) { \
			if (IsBigEndian()) return v; else {\
				__AllNum O; O.fld=v;\
				__AllNum T = __Swap(O,sizeof(type));\
				return T.fld;\
			}\
		}


		SlyvConv(int16, i16);
		SlyvConv(uint16, ui16);
		SlyvConv(int32, i32);
		SlyvConv(uint32, ui32);
		SlyvConv(int64, i64);
		SlyvConv(uint64, ui64);


		inline byte Char2Byte(char c) {
			__AllNum r; r.ch = c;
			return r.bt;
		}
#undef SlyvConv

	}
}