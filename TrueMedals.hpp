// Lic:
// **********************************************
// 
// Medals/TrueMedals.hpp
// (c) Jeroen Broks, 2021, 2023, All Rights Reserved.
// 
// This file contains material that is related
// to a storyline that is which is strictly
// copyrighted to Jeroen Broks.
// 
// This file may only be used in an unmodified
// form with an unmodified version of the
// software this file belongs to.
// 
// You may use this file for your study to see
// how I solved certain things in the creation
// of this project to see if you find valuable
// leads for the creation of your own.
// 
// Mostly this file comes along with a project
// that is for most part released under an
// open source license and that means that if
// you use that code with this file removed
// from it, you can use it under that license.
// Please check out the other files to find out
// which license applies.
// This file comes 'as-is' and in no possible
// way the author can be held responsible of
// any form of damages that may occur due to
// the usage of this file
// 
// 
// **********************************************
// 
// version: 23.12.24
// EndLic
#pragma once

#undef Medal_Debug
#undef CrashBankPanic

//#define site "tricky1975.github.io/Medals/Medals.ini"
//#define site "google.com"

//#include <GetHTTP.hpp>
#include <SlyvGINIE.hpp>
#include <SlyvSTOI.hpp>
#include <SlyvDirry.hpp>
#include <SlyvStream.hpp>
#include <SlyvString.hpp>
#include <SlyvMD5.hpp>
#include <SlyvTime.hpp>

#include <jcr6_core.hpp>
#include <JCR6_Write.hpp>

#include <iostream>

using namespace std;
using namespace Slyvina;
using namespace Units;
using namespace JCR6;

#ifdef CrashBankPanic
void ___BankPanic(string e) { throw runtime_error("\7MEDAL RUNTIME ERROR IN BANKING: "+e); }
#endif

namespace Slyvina {
	namespace Medals {

		typedef struct Medal {
			string Game;
			string Tag;
			string Achieved;
		} Medal;

		//typedef shared_ptr<GINIE> MGINIE; // No longer needed

		// Laziness! 
#define MGINIE GINIE
		// (No idea why the typedef definitions refuse to work properly)
	//#define MGINIE shared_ptr<GINIE>

		//static map<Medal, string> GotMedals;
		static vector<Medal> GotMedals;
		//static MGINIE MedalData;
		//static string CheckFile; //{ Dirry("$AppSupport$/Medals.JBC") };
#define CheckFile Dirry("$AppSupport$/Medals.JBC")

		MGINIE _Parse(string src) {
			//auto r{ make_shared<GINIE>() };
			//r->Parse(src);
			auto r{ ParseGINIE(src) };
			return r;
		}

		class _CMData;
		typedef shared_ptr<_CMData> CMData;
		//#define CMData shared_ptr<_CMData> 

		class _CMData {
		public:
			MGINIE Data{ nullptr };
			string src;
			void Parse() { Data = _Parse(src); }
			void Parse(string _src) { src = _src; Parse(); }
			int Version() { return ToInt(Data->Value("Sys", "Version")); }
			bool Valid() { return Upper(Data->Value("Sys", "Complete")) == "TRUE"; }

			static map<string, CMData> Register;
			static CMData Create(string src, string Tag) {
				auto ret{ make_shared<_CMData>() };
				ret->Parse(src);
				Register[Upper(Tag)] = ret;
#ifdef Medal_Debug
				cout << "Registered " << src.size() << " bytes of source into " << Upper(Tag) << ".\n";
#endif
				return ret;
			}
			static CMData Latest() {
				static auto base{ Create("[sys]\nversion=0\ncomplete=false\n","Start") };
				auto ret{ base };
				for (auto a : Register) {
#ifdef Medal_Debug
					cout << "Get Latest>> " << a.first << " >> Valid: " << a.second->Valid() << "; Version: " << a.second->Version() << endl;
#endif
					if (a.second->Valid() && a.second->Version() > ret->Version()) ret = a.second;
				}
				return ret;
			}

		};
		map<string, CMData> _CMData::Register{};

		MGINIE MedalData(bool force = false) {
			static bool first = true;
			static MGINIE r;
			if (force || first) {
#ifdef Medal_Debug
				cout << "MedalData wanted! Version: " << _CMData::Latest()->Version() << endl;
#endif
				//return _CMData::Latest()->Data; 
				r = _CMData::Latest()->Data;
				first = false;
			}
			return r;
		}

		/*
		static string LatestGENIE;
		static string InternetGENIE;
		static string JCR6GENIE;
		static string ConfigGENIE;
		*/


		static void LoadGotMedals(bool onlynew = true) {
			static bool donebefore{ false };
			if (onlynew && donebefore) return;
			donebefore = true;
			GotMedals.clear();
			if (!FileExists(CheckFile)) return;
			auto lJ{ JCR6_Dir(CheckFile) };
			//auto M5{ lJ->GetString("Check_MD5") };
			auto BT{ lJ->B("Medals") };
#ifdef CrashBankPanic
			BT->Panic = ___BankPanic;
#endif
			//auto FM{ BT->BufAsString() + "\n\n" + CheckFile };
			if (false) { //if (md5(FM) != M5) {
				//#ifdef Medal_Debug
							//cout << "Str4Hash: " << FM << endl;
							//cout << "Hash mismatch: " << md5(FM) << "!=" << M5 << endl; // debug only!
				//#endif
				return;
			}
			unsigned char tag{ 0 };
			do {				
				tag = BT->ReadByte();				
				switch (tag) {
				case 255:
					break;
				case 1:
				{
					/// BT->ReadByte(); BT->ReadByte(); BT->ReadByte(); // Fix?
#ifdef Medal_Debug
					cout << "Pos " << BT->Position() << "/" << BT->Size() << "\n";
#endif
					Medal M{ BT->ReadString(),BT->ReadString(),BT->ReadString() };
#ifdef Medal_Debug
					cout << M.Game << "." << M.Tag << " = " << M.Achieved << endl;
#endif
					GotMedals.push_back(M);
				}
				break;
				default:
#ifdef Medal_Debug
					cout << "Medal: Unknown tag: " << tag << endl;
#endif
					return;
				}
			} while (tag != 255);
			bool Ok{ false };
			if (lJ->EntryExists("SCORE") && lJ->EntryExists("SCOREHASH")) {
				auto src{ lJ->GetString("SCORE") };
				auto hsh{ lJ->GetString("SCOREHASH") };
				CMData D;
				//if (md5(src) == hsh) {
				if (true) { // Something wrong?
					D = _CMData::Create(src, "CONF");
					Ok = D->Valid();
#ifdef Medal_Debug
				} else {
					cout << "Score table from home. Hash mismatch>> " << hsh << "!=" << md5(src) << endl;
#endif
				}
			}
			if (!Ok) {
				_CMData::Create("[sys]\nVersion=0\nComplete=false\n", "CONF");
			}
		}

		static void SaveGotMedals() {
			auto sdir{ ExtractDir(CheckFile) };
			if (!DirectoryExists(sdir)) MakeDir(sdir);
			JT_Create sJ{ CreateJCR6(CheckFile,_Storage) };//{ CheckFile,_Storage };
			auto BT{ sJ->NewEntry("Medals", _Storage) };
			for (auto it : GotMedals) {
				BT->WriteByte((byte)1);
				BT->Write(it.Game);
				BT->Write(it.Tag);
				BT->Write(it.Achieved);
#ifdef Medal_Debug
				cout << "Got: " << it.Game << "." << it.Tag << ">" << it.Achieved << endl;
#endif

			}
			BT->Write((unsigned char)255);
			auto s4hash{ BT->BufAsString() };
#ifdef Medal_Debug
			cout << "For hasing: " << s4hash;
#endif // Medal_Debug

			BT->Close();
			sJ->AddString(md5(s4hash + "\n\n" + CheckFile), "Check_MD5", _Storage);
			sJ->AddString(_CMData::Latest()->src, "Score", _Storage);
			sJ->AddString(md5(_CMData::Latest()->src), "ScoreHash", _Storage);
			sJ->Close();
#ifdef Medal_Debug
			cout << "Data saved to: " << CheckFile << "; Storage: " << _Storage << endl;
			cout << "JCR Reported: " << (Last()->Error) << endl;
#endif
		}
/*
		void LoadFromInternet() {
			auto Data{ GetHTTP(site) };
#ifdef Medal_Debug
			cout << "<Data site=\"" << site << "\" error=\"" << HTTP_GetError() << "\">\n" << Data << "\n</Data>\n";
#endif
			//MedalData()->Parse(Data);
			_CMData::Create(Data, "INTERNET");
		}
//*/

		void LoadFromNothing() {
			_CMData::Create("[Sys]\nVersion=0\ncomplete=false", "NOTHING");
		}


		int MedalValue(const char* game, const char* medal) {
			//cout << "MEDALDATA." << game << "." << medal << " = \"" << MedalData()->Value(game, medal) << "\"\n"; // debug only!
			return ToInt(MedalData()->Value(game, medal));
		}

		int FullScore() {
			int Total{ 0 };
			LoadGotMedals();
			for (auto M : GotMedals) if (M.Achieved.size()) {
				//cout << "MEDALCOUNT: " << Total << " >> " << M.Game << "::" << M.Tag << " >> " << MedalValue(M.Game.c_str(), M.Tag.c_str()) << endl; // DEBUG ONLY!!
				Total += MedalValue(M.Game.c_str(), M.Tag.c_str());
			}
			return Total;
		}

		int MaxScore() {
			int Total{ 0 };
			auto Cats{ MedalData()->Categories() };
			for (auto C : *Cats) {
				auto Vals{ MedalData()->Values(C) };
				for (auto M : *Vals) Total += MedalValue(C.c_str(), M.c_str());
			}
			return Total;
		}

		int ScorePercent() {
			long double
				S{ (long double)FullScore() },
				M{ (long double)MaxScore() };
			return floor((S / M) * 100);
		}


		bool GotMedal(const char* game, const char* medal) {
			for (auto M : GotMedals) if (M.Game == game && M.Tag == medal) return true;
			return false;
		}

		void Award(const char* game, const char* medal) {
			LoadGotMedals();
			//Medal ID{ game,medal };
			if (GotMedal(game, medal)) {
#ifdef Medal_Debug
				cout << "Award " << game << "." << medal << " ignored. Already awarded\n";
#endif // 

				return;
			}
			//GotMedals[ID] = CurrentDate() + "; " + CurrentTime();
			Medal M{ game, medal,CurrentDate() + "; " + CurrentTime() };
			GotMedals.push_back(M);
			SaveGotMedals();
		}

		bool Awarded(const char* game, const char* medal) {
			LoadGotMedals();
#ifdef Medal_Debug
			cout << "Checking awarded <" << game << "," << medal << "> -> " << GotMedal(game, medal) << endl;
#endif
			return GotMedal(game, medal);
		}


		void LoadFromJCR6(JT_Dir main, std::string medalfile) {
			_CMData::Create(main->GetString(medalfile), "Project");
		}

		bool Active() { return true; }

	}
}