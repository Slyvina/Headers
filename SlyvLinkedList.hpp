// Lic:
// Units/Headers/SlyvLinkedList.hpp
// Linked List
// version: 23.07.28
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


#include "Slyvina.hpp"

namespace Slyvina {
	namespace Units {

		template <class MyClass> class TList;
		template <class MyClass> class TLink {
		public:
			TList<MyClass>* Parent{ nullptr };
			TLink<MyClass>* Prev{ nullptr };
			TLink<MyClass>* Next{ nullptr };
			//std::unique_ptr<MyClass> Obj{ nullptr };
			bool unique{ false };
			MyClass* Obj{ nullptr };
			std::unique_ptr<MyClass> Move(bool unlink = true);
			inline void UnLink();
		};

		const byte tlist_fchannels{ 16 };
		template <class MyClass> class TList {
			bool AutoKill{ false };
			bool _unique{ true };
			TLink<MyClass>* fchan[tlist_fchannels];
		public:
			TList<MyClass>();
			TLink<MyClass>* _First{ nullptr }; // Don't adress directly!
			TLink<MyClass>* _Last{ nullptr }; // Don't adress directly!
			TLink<MyClass>* FirstLink(byte channel = 0);
			TLink<MyClass>* NextLink(byte channel = 0);
			MyClass* First(byte channel = 0);
			MyClass* Next(byte channel = 0);

			static TList<MyClass> Create() { return TList<MyClass>(); }
			static std::unique_ptr<TList> CreateUnique(bool unique = true) { auto r = new TList<MyClass>(); r->AutoKill = true; r->_unique = unique;  return std::unique_ptr<TList<MyClass>>(r); }
			static std::shared_ptr<TList> CreateShared(bool unique = true) { auto r = new TList<MyClass>(); r->AutoKill = true; r->_unique = unique; return std::shared_ptr<TList<MyClass>>(r); }
			void Clear() { while (_First) _First->UnLink(); }
			void AddLast(MyClass* O, bool unique);
			void AddLast(MyClass* O) { AddLast(O, _unique); }
			void operator+=(MyClass* O) { AddLast(O); }
			TLink<MyClass>* Link(uint64 idx);
			MyClass* Value(uint64 idx);
			MyClass* operator[](uint64 idx) { return Value(idx); }
			void Delete(uint64 idx);
			uint64 Size();
			~TList<MyClass>();
		};

		template<class MyClass>	inline TList<MyClass>::TList() {
			for (byte i = 0; i < tlist_fchannels; i++) fchan[i] = nullptr;
		}

		template<class MyClass>	inline TLink<MyClass>* Slyvina::Units::TList<MyClass>::FirstLink(byte channel) {
			auto ret{ _First };
			fchan[channel] = nullptr;
			if (ret) {
				fchan[channel] = ret->Next;
			} else { return nullptr; }
			return ret;
		}

		template<class MyClass>	inline TLink<MyClass>* Slyvina::Units::TList<MyClass>::NextLink(byte channel) {
			if (!fchan[channel]) return nullptr;
			auto ret{ fchan[channel] };
			fchan[channel]= fchan[channel]->Next;
			return ret;
		}

		template<class MyClass>	inline MyClass* Slyvina::Units::TList<MyClass>::First(byte channel) {
			auto FL{ FirstLink(channel) };
			if (FL) return FL->Obj; else return nullptr;
		}

		template<class MyClass>	inline MyClass* Slyvina::Units::TList<MyClass>::Next(byte channel) {
			auto FL{ NextLink(channel) };
			if (FL) return FL->Obj; else return nullptr;
		}


		template<class MyClass> inline std::unique_ptr<MyClass> TLink<MyClass>::Move(bool unlink) {
			unique = false;
			return std::unique_ptr<MyClass>(Obj);
			if (unlink) UnLink();
		}

		template<class MyClass>	inline void TLink<MyClass>::UnLink() {
			if (!Parent) throw std::exception("Parentless link");
			if (Prev) Prev->Next = Next; else Parent->_First = Next;
			if (Next) Next->Prev = Prev; else Parent->_Last = Prev;
			if (unique) delete Obj;
			delete this;
		}

		template<class MyClass>	inline void TList<MyClass>::AddLast(MyClass* O,bool unique) {
			auto L{ new TLink<MyClass>() };
			L->Parent = this;
			L->Prev = _Last;
			L->unique = unique;
			if (_Last) _Last->Next = L;
			if (!_First) _First = L;
			_Last = L;
			//L->Obj = std::unique_ptr<MyClass>(O);
			L->Obj = O;
			//std::cout << "unique:" << unique << "\n"; // debug
		}

		template<class MyClass> inline TLink<MyClass>* TList<MyClass>::Link(uint64 idx) {
			auto L = _First;
			while (L && idx) { idx--; L = L->Next; }
			return L;
		}

		template<class MyClass> inline MyClass* TList<MyClass>::Value(uint64 idx) {
			auto L{ Link(idx) };
			if (L) return L->Obj; 
			return nullptr;
		}

		template<class MyClass>	inline void TList<MyClass>::Delete(uint64 idx) {
			auto L{ Link(idx) };
			if (L) L->UnLink(); 
		}

		template<class MyClass> inline uint64 TList<MyClass>::Size() {
			uint64 r{ 0u };
			for (auto L = _First; L; L = L->Next) r++;
			return r;
		}

		template<class MyClass> inline TList<MyClass>::~TList() {
			if (AutoKill) Clear();
		}

		

	}
}