// Lic:
// Wen_State.hpp
// Wendicka - State (header)
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

// C++
#include <memory>

// Slyvina
#include <SlyvBank.hpp>
#include <SlyvStream.hpp>
#include <SlyvString.hpp>


// Wendicka
#include "Wendicka.hpp"
#include "Wen_TypeDefs.hpp"
#include "Wen_Panic.hpp"

// JCR6 (Keep commented. It's supposed to be optional, but I needed to be able to check my code right)
// #include <JCR6_Core.hpp>

namespace Slyvina {

	namespace Wendicka {
		


		class _WState {
		private:
			static uint32 _UnNamedCount;
			static std::string _StateName;
			bool _runbefore{ false }; // In order to create bytecode, the script may not yet have been run before!
			std::map<std::string, bool> _cb{ {"INGORECASE",true} };
			std::map<std::string, int> _ci{ {"__VERSION",VNum} };
			std::map<std::string, std::string> _cs{};
		public:
			/// <summary>
			/// When set to 'true' warnings could be visible on screen. Handy for compiler tools, but in run-time not recommended. Default value is 'false'.
			/// </summary>
			static bool AllowPublicWarning;

			/// <summary>
			/// Returns the name of the state. If none was given upon creation the generated one will be returned
			/// </summary>
			/// <returns>State name</returns>
			inline std::string StateName() { return _StateName; }

			/// <summary>
			/// Here you can define your custom function in case an error is thrown
			/// </summary>
			Wen_Panic StatePanic{ nullptr };

		private:
			inline void _Panic(std::string err) { Panic(this, StatePanic, err); }
			std::map <std::string, _WChunk> _Chunks{};
			std::vector<_WChunk> _InitChunks{};
			std::unique_ptr<_WCall> FirstCall{ nullptr };
			_WCall* _CurrentCall{ nullptr };
		public:
			inline _WCall* CurrentCall() { return _CurrentCall; }

			/// <summary>
			/// Adds bytecode to the state
			/// </summary>
			/// <param name="code"></param>
			/// <param name="CName">Name of code (handy for debugging)</param>
			void AddCode(Units::Bank code,std::string CName="");

			/// <summary>
			/// Traceback
			/// </summary>
			/// <returns>Traceback data</returns>
			std::string TraceBack();

			_WState(std::string _SN);

			void SetConfig(std::string k, bool v);
			void SetConfig(std::string k, int v);
			void SetConfig(std::string k, std::string v);

			bool CFGBool(std::string k);
			int CFGInt(std::string k);
			std::string CFGString(std::string k);

			std::vector<std::string> CFGFieldsBool();
			std::vector<std::string> CFGFieldsInt();
			std::vector<std::string> CFGFieldsString();

			bool HasChunk(std::string k);
			inline void ClearChunks() { _Chunks.clear(); _InitChunks.clear(); }

			_WChunk* NewChunk(std::string k, bool overwrite = false);
			_WChunk* NewInit();
			
			void Register(std::string ChunkName, Wen_API API, bool force = false);
			void Register(std::map<std::string, Wen_API>* lib, std::string prefix = "", bool force = false);
			inline void Register(std::map<std::string, Wen_API > lib, std::string prefix = "", bool force = false) { Register(&lib, prefix, force); }
			inline void Register(std::unique_ptr<std::map<std::string, Wen_API >> lib, std::string prefix = "", bool force = false) { Register(lib.get(), prefix, force); }
			inline void Register(std::shared_ptr<std::map<std::string, Wen_API >> lib, std::string prefix = "", bool force = false) { Register(lib.get(), prefix, force); }

			inline size_t InitCount() { return _InitChunks.size(); }
			inline _WChunk* Init(size_t idx) { return &_InitChunks[idx]; }

			std::vector<std::string> ChunkNames();
			_WChunk* Chunk(std::string Name);
			
		};		

		class _WChunk {
		private:
			_WState* _Parent{ nullptr };
		public:
			ChunkType Type{ ChunkType::Regular };
			Wen_API API{ nullptr };
			_WChunk() {}; // trouble preventer
			_WChunk(_WState* ouwe);
			inline _WState* Parent() { return _Parent; }
			std::vector<_WInstruction> Instructions;
			_WInstruction* NewInstruction();
		};

		inline WState CreateState(std::string SN = "") { return std::shared_ptr<_WState>(new _WState(SN)); }
		inline UWState CreateUniqueState(std::string SN = "") { return std::unique_ptr<_WState>(new _WState(SN)); }

		inline WState CreateState(Units::Bank Code, std::string SN = "") {
			auto r{ CreateState(SN) };
			if (r) r->AddCode(Code, SN+" main code");
		}
		inline UWState CreateUniqueState(Units::Bank Code, std::string SN = "") {
			auto r{ new _WState(SN) };
			if (r) r->AddCode(Code, SN + " main code");
			return std::unique_ptr <_WState>(r);
		}

		WState LoadState(std::string File, std::string SN = "");
		UWState LoadUniqueState(std::string File, std::string SN = "");

		class _WInstruction {
		private:
			_WChunk* _Parent{ nullptr };
		public:
			_WInstruction() {}; // Only needed to prevent compiler crap!
			_WInstruction(_WChunk* Ouwe);
			_WChunk* Parent() { return _Parent; }
			_WState* State() { return _Parent->Parent(); }
			WIns Command{ WIns::Unknown };
			std::vector<_WIParam> Params{};
			//_WIParam NewParams(uint32 n);
			std::string srcfile{ "" };
			size_t srcline{ 0 };
		};

		class _WIParam {
		private:
			_WInstruction* _ParIns{ nullptr };
			_WIParam* _ParPar{ nullptr };
		public:
			_WIPIdx Index{ nullptr };
			inline _WIParam* NextIndex() { if (Index) return Index.get(); else return nullptr; }
			inline _WIParam* ParentParameter() { return _ParPar; }
			inline _WInstruction* ParentInstruction() { return _ParIns; }
			inline _WIParam() {} // Must exist
			inline _WIParam(_WInstruction* IOuwe, _WIParam* POuwe = nullptr) { _ParIns = IOuwe; _ParPar = POuwe; }
			std::string rawstringvalue{ "" };
			int64 rawintvalue{ 0 };
			double rawnumvalue{ 0 };
			WParamType Type{ WParamType::Nothing };
		};

		class _WCall {
		private:
			_WCall* Parent{ nullptr };
			std::unique_ptr<_WCall> Kid{ nullptr };
		public:
		};

#ifdef Slyvina_JCR6_Core_Present
		inline WState LoadState(JCR6::JT_Dir JCRMain, std::string entry, std::string SN = "") {
			if (!JCRMain) { Panic("Null received for main"); return nullptr; }
			auto buf{ JCRMain->B(entry) };
			if (JCR6::Last()->Error) { Panic(JCR6::Last()->ErrorMessage + " (" + JCR6::Last()->MainFile + "::" + JCR6::Last()->Entry + ")"); return nullptr; }
			if (!buf) { Panic("Loading entry '" + entry + "' for Wendicka code failed"); return nullptr; }
			if (!SN.size()) SN = entry;
			return CreateState(buf, SN);
		}
		
		inline WState LoadState(std::string JCRMain, std::string entry, std::string SN = "") {
			auto J{ JCR6::JCR6_Dir(JCRMain) };
			if (JCR6::Last()->Error) { Panic(JCR6::Last()->ErrorMessage); return nullptr; }
			if (!J) { Panic("Loading JCR6 file " + JCRMain + " failed"); return nullptr; }
			return LoadState(J, entry, SN);
		}
#endif

	}



}