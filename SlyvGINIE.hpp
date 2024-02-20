// Lic:
// Units/Headers/SlyvGINIE.hpp
// Slyvina - GINIE
// version: 24.02.18
// Copyright (C) 2022, 2023, 2024 Jeroen P. Broks
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
#include <SlyvStream.hpp>
#include <SlyvString.hpp>
#include <SlyvVecSearch.hpp>
#include <SlyvSTOI.hpp>
#include <string>
#include <algorithm>


#undef GINIE_DEBUG

/*

GINIE = GINIE is not INI either.
The name was a play on GINI (GINI is not INI) and is actually a completely revised workout. 
The name is to be pronounced as "GENIE".

GINIE is in most ways compatible with base config files in .ini form, whoever there are a few differences
- GINIE is case insensitive, so upper and lower case won't matter in the config keys
- GINIE also supports its own listing system


Now unlike most of my libraries were I recommend to only use either the share_ptr or unique_ptr variants, GINIE should be safe to use Raw_GENIE, but I ain't a fan of that.
*/



namespace Slyvina {
	namespace Units {

		enum class GINIE_Read { Source, File };

		class RawGINIE;

		typedef std::shared_ptr<RawGINIE> GINIE;
		typedef std::unique_ptr<RawGINIE> UGINIE;

		class RawGINIE {
		private:		
			std::map<std::string, std::map<std::string, std::string>> _Values{};		
			std::map<std::string, std::map<std::string, std::vector<std::string>>> _Lists{};
			inline static void S2U(std::string& str) { if (!str.size()) str = "NAMELESS"; std::transform(str.begin(), str.end(), str.begin(), ::toupper); }
		public:

			std::string AutoSave{ "" }; // When you put a file name into this, GINIE will save all modifications automatically to it once they are made.
			std::string AutoSaveHeader{ "" }; // Wehn set a comment header will be added to automatically saved files.

			inline void Clear() {
				_Values.clear();
				_Lists.clear();
			}

			inline std::string UnParse(std::string Header = "") {
				std::string ret{ "" };
				if (Header.size()) {
					ret += "# ";
					for (size_t i = 0; i < Header.size(); ++i) {
						switch (Header[i]) {
						case '\r': break; // remove these fitly <CR> characters from my source! I don't want them. I don't need them.
						case '\n': ret += "\n# "; break;
						default: ret += Header[i]; break;
						}
					}
					ret += "\n\n";
				}
				std::map<std::string, bool>CatDone{};
				for (auto& cat : _Values) {
					CatDone[cat.first] = true;
					ret += "["; ret += cat.first; ret += "]\n";
					for (auto& val : cat.second) { ret += val.first + "=" + val.second+"\n"; }
					if (_Lists.count(cat.first)) for (auto& lst : _Lists[cat.first]) {
						ret += "*list:" + lst.first + "\n";
						for (auto item : lst.second) { ret += "\t" + item + "\n"; }
						ret += "*end\n";
					}
				}
				for (auto& cat : _Lists) {
					if ((!CatDone.count(cat.first) || (!CatDone[cat.first]))) {
						ret += "["; ret += cat.first; ret += "]\n";
						for (auto& lst : cat.second) {
							ret += "*list:" + lst.first + "\n";
							for (auto item : lst.second) { ret += "\t" + item + "\n"; }
							ret += "*end\n";
						}
					}
				}
				return ret;
			}


			inline void SaveSource(std::string File, std::string Header = "") { SaveString(File, UnParse(Header)); }

			/// <summary>
			/// Define a value
			/// </summary>
			/// <param name="cat"></param>
			/// <param name="key"></param>
			/// <param name="value"></param>
			inline void Value(std::string cat, std::string key, std::string value) {
				S2U(cat); S2U(key); value = Trim(value);
				if ((!_Values.count(cat)) && value == "") return;
				if ((!_Values[cat].count(key)) && value == "") return;
				if (_Values[cat][key] == value) return;
				if (value == "") _Values[cat].erase(key);
				_Values[cat][key] = value;
				if (AutoSave.size()) SaveSource(AutoSave, AutoSaveHeader);
			}

			inline void Value(std::string cat, std::string key, int64 value) {
				Value(cat, key, std::to_string(value));
			}
			inline void Value(std::string cat, std::string key, int32 value) {
				Value(cat, key, std::to_string(value));
			}

			/// <summary>
			/// Get a value
			/// </summary>
			/// <param name="cat"></param>
			/// <param name="key"></param>
			/// <returns>The value</returns>
			inline std::string Value(std::string cat, std::string key) {
				if (!this) {
					std::cout << "\x7\x1b[31mERROR!\x1b[0m <NULLGINIE>->Value(\"" << cat << "\", \"" << key << "\"): Trying to get a value from NULL!\n";
					return "";
				}
				S2U(cat); S2U(key);
				if (!_Values.count(cat)) return "";
				if (!_Values[cat].count(key)) return "";
				return Trim(_Values[cat][key]); 
			}

			//inline std::string operator[](std::string cat, std::string key) { return Value(cat, key); }

			/// <summary>
			/// Gets a value and tries to parse it into an integer
			/// </summary>
			/// <param name="cat"></param>
			/// <param name="key"></param>
			/// <returns>Integer value. Returns 0 if failed</returns>
			inline int IntValue(std::string cat, std::string key) {
				return ToInt(Value(cat, key));
			}

			inline bool BoolValue(std::string cat, std::string key) {
				auto V = Upper(Value(cat, key));
				return (V == "TRUE" || V == "YES");
			}

			inline void BoolValue(std::string cat, std::string key,bool V) {
				Value(cat, key, boolstring(V));
			}

			/// <summary>
			/// Does a value exist?
			/// </summary>
			/// <param name="cat"></param>
			/// <param name="key"></param>
			/// <returns></returns>
			inline bool HasValue(std::string cat, std::string key) {
				Trans2Upper(cat);
				Trans2Upper(key);
				if (!_Values.count(cat)) return false;
				return _Values[cat].count(key);
			}

			inline bool HasCat(std::string cat) {
				Trans2Upper(cat);
				return _Values.count(cat) || _Lists.count(cat);
			}

			/// <summary>
			/// Will define a value, but only if it doesn't already exist!
			/// </summary>
			/// <param name="cat"></param>
			/// <param name="key"></param>
			/// <param name="value"></param>
			inline std::string NewValue(std::string cat, std::string key, std::string value) {
				if (!HasValue(cat, key)) Value(cat, key, value);
				return Value(cat, key);
			}

			inline int NewValue(std::string cat, std::string key, int value) {
				NewValue(cat, key, std::to_string(value));
				return IntValue(cat, key);
			}

			inline VecString Values(std::string cat){
				auto ret{ NewVecString() };
				Trans2Upper(cat);
				if (_Values.count(cat)) {
					for (auto k : _Values[cat]) ret->push_back(k.first);
				}
				return ret;
			}

			/// <summary>
			/// Add to a list (if the list doesn't yet exist, it will be created)
			/// </summary>
			/// <param name="cat"></param>
			/// <param name="key"></param>
			/// <param name="value"></param>
			/// <param name="unique"></param>
			inline void Add(std::string cat, std::string key, std::string value, bool sort=false, bool unique = false) {
				S2U(cat); S2U(key);
				if (value == "") return;
				if (unique) {
					for (auto k : _Lists[cat][key]) if (k == value) return;
				}
				_Lists[cat][key].push_back(value);
				if (sort) 
					std::sort(_Lists[cat][key].begin(), _Lists[cat][key].end());
				if (AutoSave.size()) SaveSource(AutoSave, AutoSaveHeader);
			}

			inline void AddNew(std::string cat, std::string key, std::string value, bool sort=false) { Add(cat, key, value, sort, true); }

			inline void Remove(std::string cat, std::string key, std::string value, int times = -1,bool ignorecase=false) {
				S2U(cat); S2U(key);
				auto V = NewVecString();
				bool match{ false };
				bool removals{ false };
				for (auto chkv : _Lists[cat][key]) {
					if (ignorecase)
						match = Upper(chkv) == Upper(value);
					else
						match = chkv == value;
					removals = removals || match;
					if (!match) V->push_back(chkv);
					times = std::max(-1, --times);
					if (times == 0) break;
				}
				if (removals) {
					_Lists[cat][key] = *V;
					if (AutoSave.size()) SaveSource(AutoSave, AutoSaveHeader);
				}
			}

			/// <summary>
			/// Pointer to the list with these settings. Best is to only use this for reading purposes and not for writing. At least not when you set the AutoSave variable.
			/// </summary>
			/// <param name="cat"></param>
			/// <param name="key"></param>
			/// <returns>Pointer to the list in question</returns>
			inline std::vector<std::string>* List(std::string cat, std::string key) {
				S2U(cat); S2U(key);
				return &_Lists[cat][key];
			}

			inline size_t ListCount(std::string cat, std::string key) {
				S2U(cat); S2U(key);
				if (!_Lists.count(cat)) return 0;
				if (!_Lists[cat].count(key)) return 0;
				return _Lists[cat][key].size();
			}

			/// <summary>
			/// Creates a list unless it already exists. (If you set the 'force' parameter to true a new list will be created anyway).
			/// </summary>
			inline void NewList(std::string cat, std::string key, bool force = false) {
				S2U(cat); S2U(key);
				if (_Lists[cat].count(key) && (!force)) return;
				_Lists[cat][key] = std::vector<std::string>();
				if (AutoSave.size()) SaveSource(AutoSave, AutoSaveHeader);
			}

			inline bool HasList(std::string cat, std::string key) {
				S2U(cat); S2U(key);
				//std::cout << "?> cat:" << cat << _Lists.count(cat) << std::endl; // debug only!
				if (!_Lists.count(cat)) return false;
				//std::cout << "?>" << _Lists[cat].count(key) << std::endl; // debug only!
				return _Lists[cat].count(key);
			}

			/// <summary>
			/// Parses a source so it can be processed.
			/// </summary>
			/// <param name="source">Source code to be parsed and processed</param>
			/// <param name="merge">If set to true the content will be merged with the existing data. If set to false, the existing data will be disposed</param>
			inline void Parse(std::string source, bool merge = false) {
				if (!this) std::cout << "WARNING! Trying to parse into a null-GINIE!\n";
				if (!merge) { _Values.clear(); _Lists.clear(); }
				auto src{ Split(StReplace(source,"\r",""),'\n') };
				std::string cat{ "" };
				std::string list{ "" };
				for (size_t i = 0; i < src->size(); ++i) {
					auto linenum{ i + 1 };
					auto line{ Trim((*src)[i]) };
#ifdef GINIE_DEBUG
					std::cout << "Paring line " << linenum << "/" << src->size() << ": " << line << std::endl;
#endif
					if ((!line.size()) || (line[0] == '#' && list == "")) {
#ifdef GINIE_DEBUG
						std::cout << "Whiteline or comment! Must ignore\n";
#endif
						// Do NOTHING at all. Whitelines and comments are to be ignored!
					} else if (list.size()) {
						if (Upper(line) == "*END")
							list = "";
						else
							Add(cat, list, line);
					} else if (line[0] == '[' && line[line.size() - 1] == ']') {
						cat = Mid(line, 2, (unsigned int)line.size() - 2);
					} else if (Prefixed(Upper(line), "*LIST:")) {
						if (!cat.size()) { std::cout << "GINIE ERROR! Categoryless list started in line " << linenum << "\n"; return; }
						list = line.substr(6);
						if (!list.size()) { std::cout << "GINIE ERROR! Namelist list in line " << linenum << "\n"; return; }
					} else {
						if (!cat.size()) { std::cout << "GINIE ERROR! Categoryless value definition in line " << linenum << "\nLine:" << line << "\n"; return; }
						auto p = FindFirst(line, '=');
						if (p < 0) { std::cout << "GINIE ERROR! Syntax error in line " << linenum << "\n"; return; }
						auto k{ Trim(line.substr(0,p)) };
						auto v{ Trim(line.substr(p + 1)) };
						Value(cat, k, v);
					}
				}
			}

			/// <summary>
			/// Read a file and parse it.
			/// </summary>
			/// <param name="f">File</param>
			/// <param name="merge">If set to true the content will be merged with the existing data. If set to false, the existing data will be disposed</param>
			void FromFile(std::string f, bool merge = false) {
				if (!FileExists(f)) { std::cout << "GINIE ERROR! File not found! (" << f << ")\n"; return; }
				if (!this) std::cout << "GINIE ERROR! Trying to parse into null! Expect an exception to be thrown!\n";
				Parse(FLoadString(f), merge);
			}

			VecString Categories() {
				auto Ret{ NewVecString() };
				for (auto l : _Values) Ret->push_back(l.first);
				for (auto l : _Lists) Ret->push_back(l.first);
				SortVecString(Ret);
				return Ret;
			}

			inline RawGINIE() {};
			inline RawGINIE(GINIE_Read r, std::string src, std::string autosv = "", std::string autosvh = "") {
				switch (r) {
				case GINIE_Read::Source: Parse(src); break;
				case GINIE_Read::File: FromFile(src); break;
				default: std::cout << "GINIE ERROR! Unknown readup tag!\n"; return;
				}
				AutoSave = autosv;
				AutoSaveHeader = autosvh;
			}
		};

		/// <summary>
		/// Loads a GINIE file, parses it and returns it as a shared pointer.
		/// </summary>
		/// <param name="src"></param>
		/// <param name="autosv"></param>
		/// <param name="autosvh"></param>
		/// <returns></returns>
		inline GINIE LoadGINIE(std::string src, std::string autosv = "", std::string autosvh = "") { return std::make_shared<RawGINIE>(GINIE_Read::File, src, autosv, autosvh); }

		/// <summary>
		/// Loads a GINIE file (creates it if it doesn't yet exist), parses it and returns it as a shared pointer.
		/// </summary>
		/// <param name="src"></param>
		/// <param name="autosv"></param>
		/// <param name="autosvh"></param>
		///  <returns></returns>
		inline GINIE LoadOptGINIE(std::string src, std::string autosv = "", std::string autosvh = "") {
			if (!FileExists(src)) {
				auto d{ ExtractDir(src) };
				if (!DirectoryExists(d)) MakeDir(d);
				SaveString(src, "# Creating new GINIE: " + src);
			}
			return LoadGINIE(src, autosv, autosvh);
		}

		/// <summary>
		/// Loads a GINIE file, parses it and returns it as a unique pointer.
		/// </summary>
		///  <param name="src"></param>
		/// <param name="autosv"></param>
		/// <param name="autosvh"></param>
		/// <returns></returns>
		inline UGINIE LoadUGINIE(std::string src, std::string autosv = "", std::string autosvh = "") { return std::make_unique<RawGINIE>(GINIE_Read::File, src, autosv, autosvh); }

		/// <summary>
		/// Parses a GINIE source and returns it as a shared pointer
		/// </summary>
		/// <param name="src"></param>
		/// <param name="autosv"></param>
		/// <param name="autosvh"></param>
		/// <returns></returns>
		inline GINIE ParseGINIE(std::string src, std::string autosv = "", std::string autosvh = "") { return std::make_shared<RawGINIE>(GINIE_Read::Source, src, autosv, autosvh); }

		/// <summary>
		/// Parses a GINIE source and returns it as a unique pointer
		/// </summary>
		/// <param name="src"></param>
		/// <param name="autosv"></param>
		/// <param name="autosvh"></param>
		/// <returns></returns>
		inline UGINIE ParseUGINIE(std::string src, std::string autosv = "", std::string autosvh = "") { return std::make_unique<RawGINIE>(GINIE_Read::Source, src, autosv, autosvh); }

	}
}