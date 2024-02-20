// Lic:
// Wen_TypeDefs.hpp
// Wendicka - Type definitions
// version: 23.05.30
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
#include <memory>
#include <string>

namespace Slyvina {
	namespace Wendicka {
		const uint32
			VNum{ 1 },
			Min{ 1 }; // Minimal version the oldest script must be set up in.

		enum class WValue { Null, Integer, String, Table, Object, Chunk, Number };
		enum class WParamType { Nothing, Error, Command, GenWord, String, Int, Number, SuperGlobal, Global, Local, Label, Index };

		class _WState; typedef std::unique_ptr<_WState> UWState; typedef std::shared_ptr<_WState> WState;
		class _WChunk;
		class _WInstruction;
		class _WIParam; typedef std::unique_ptr<_WIParam> _WIPIdx;
		class _WCall;
		//typedef _WIParam* WIParamArray;
		typedef void (*Wen_Panic)(_WState*, std::string);

		enum ChunkType { Regular, API };
		typedef void (*Wen_API)(_WState*);


		enum class WIns {
			Unknown = 0xffffff,
			WhiteLine = 0xfffffe, // Should not live in actual code, but in the compiler it can be handy
			Special = 0xfffffd, // Should not live in actual code, but in the compiler it can be handy
			Label = 0xfffffc, // Should not live in actual code, but in the compiler it can be handy

			End = 0,
			Call,
			LetCall,

			Jmp,
			JmpTrue,
			JmpFalse,
			Chk,
			IsEqual,
			IsGreater,
			IsLess,
			Done,
			Let,
			Inc,
			Dec,
			Null, // Will set 'nul' to variants, tables or pointerbased variables
			LetSum, LetMul, LetSub, LetDiv, LetMod,

			DV, // Declare variable
			Class, DF,

			Chunk, Method, Init,

			SourceLine, SourceFile,

			Return
		};

	}
}