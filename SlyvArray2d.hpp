// Lic:
// Units/Headers/SlyvArray2d.hpp
// 2D Array
// version: 24.02.18
// Copyright (C) 2024 Jeroen P. Broks
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
#include <memory>
#include <stdexcept>


namespace Slyvina {
	namespace Units {
		typedef void(*FunctionArray2DPanic)(std::string what);

		template <class MyType> class __Array2D {
		private:
			MyType* _TrueArray{ nullptr };
			size_t m1, m2;
			void _Panic(std::string what) { throw std::runtime_error(what); }
			void Paniek(std::string what);
			void _Assert(bool cond, std::string what) { if (!cond) Paniek(what); }
		public:
			FunctionArray2DPanic Panic{nullptr};
			__Array2D(size_t d1, size_t d2);
			~__Array2D();
			MyType& V(size_t d1, size_t d2);
			inline void All(MyType v) {
				size_t m = m1 * m2;
				for (size_t i = 0; i < m; i++) _TrueArray[i] = v;
			}
		};

		template<class MyType> inline void __Array2D<MyType>::Paniek(std::string what) {
			if (Panic) Panic(what); else _Panic(what);
		}

		template<class MyType> inline __Array2D<MyType>::__Array2D(size_t d1, size_t d2) {
			_TrueArray = new MyType[d1 * d2];
			m1 = d1;
			m2 = d2;
		}

		template<class MyType> inline __Array2D<MyType>::~__Array2D() {
			delete[] _TrueArray;
		}

		template<class MyType> inline MyType& __Array2D<MyType>::V(size_t d1, size_t d2) {
			if (!(d1 < m1 && d2 < m2)) {
				char err[250];
				sprintf_s(err, "2D Index out of bounds (%d,%d) / (%d,%d)", d1, d2, m1, m2);
				Paniek(err);
			}
			return _TrueArray[d1 + (d2 * m1)];
		}

		template <class MyType> inline std::shared_ptr<__Array2D<MyType>> Dim2D(size_t d1,size_t d2) {
			auto ret{ new __Array2D<MyType>(d1,d2) };
			return std::shared_ptr<__Array2D<MyType>>(ret);
		}

		template <class MyType> inline std::shared_ptr<__Array2D<MyType>> Dim2D(size_t d1, size_t d2,MyType DVal) {
			auto ret{ new __Array2D<MyType>(d1,d2) };
			ret->All(DVal);
			return std::shared_ptr<__Array2D<MyType>>(ret);
		}

		template <class MyType> inline std::unique_ptr<__Array2D<MyType>> Dim2DU(size_t d1, size_t d2) {
			auto ret{ new __Array2D<MyType>(d1,d2) };
			return std::unique_ptr<__Array2D<MyType>>(ret);
		}

		template <class MyType> inline std::unique_ptr<__Array2D<MyType>> Dim2DU(size_t d1, size_t d2, MyType DVal) {
			auto ret{ new __Array2D<MyType>(d1,d2) };
			ret->All(DVal);
			return std::unique_ptr<__Array2D<MyType>>(ret);
		}

	}
}