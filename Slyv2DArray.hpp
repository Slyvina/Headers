// Lic:
// Units/Headers/Slyv2DArray.hpp
// Slyvina 2D array
// version: 23.06.23
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
#include <stdio.h>
#include <memory>

//#include <minmax.h>
#include <algorithm>

namespace Slyvina {
	namespace Units {

		struct len2d { int d1, d2; };

		//typedef void* Panic2D(const char* msg);

		/// <summary>
		/// Class that allows to use 2 dimensional arrays rather easily.
		/// </summary>
		/// <typeparam name="mytype"></typeparam>
		template <class mytype> class Array2D {
		private:
			mytype* _array{ nullptr };
			//std::shared_ptr<mytype[]>_array{ nullptr };
			int	_Dim1, _Dim2;
			bool _autoclean;
			bool _panicked{ false };

		public:

			/// <summary>
			/// Defines a 2D array. Please note if you do it this way in stead of using the DIM method (creating a shared pointer) you will need to dispose the data manuwally with the Dispose() method.
			/// </summary>
			/// <param name="d1">Dimension 1</param>
			/// <param name="d2">Dimension 2</param>
			Array2D(int d1, int d2);

			Array2D();

			~Array2D();

			/// <summary>
			/// Defines a value
			/// </summary>
			/// <param name="d1">Dimension 1</param>
			/// <param name="d2">Dimension 2</param>
			/// <param name="value">The actual value</param>
			void Value(int d1, int d2, mytype value);

			/// <summary>
			/// Retrieves a value
			/// </summary>
			/// <param name="d1">1st dimension</param>
			/// <param name="d2">2nd dimension</param>
			/// <returns></returns>
			mytype Value(int d1, int d2);

			void SetAll(mytype v);

			/// <summary>
			/// Creates a shared pointer. Please note when using this you don't need to dispose the data after use. This will then be done automatically.
			/// </summary>
			/// <param name="D1">1st dimension</param>
			/// <param name="D2">2nd dimension</param>
			/// <returns></returns>
			static std::shared_ptr<Array2D<mytype>> Dim(int D1, int D2);

			/// <summary>
			/// Creates a unique pointer. Please note when using this you don't need to dispose the data after use. This will then be done automatically.
			/// </summary>
			/// <param name="D1">1st dimension</param>
			/// <param name="D2">2nd dimension</param>
			/// <returns></returns>

			static std::unique_ptr<Array2D<mytype>> DimU(int D1, int D2);


			/// <summary>
			/// Tries to redo the actual max of dimensions. I recommend against using this routine (it can slow down and not be fully stable), but it's there.
			/// </summary>
			/// <param name="D1">1st dimension</param>
			/// <param name="D2">2nd dimension</param>
			void ReDim(int D1, int D2, bool keepdata = false);

			/// <summary>
			/// Disposes array. If you created a shared pointer with the Dim function, you won't need to do this.
			/// </summary>
			void Dispose();

			/// <summary>
			/// Converts the 2 dimensions into the true index. Only needed for debugging this class itself and used within the class.
			/// </summary>
			/// <param name="d1">1st dimension</param>
			/// <param name="d2">2nd dimension</param>
			/// <returns>The true index</returns>
			int idx(int d1, int d2);

			/// <summary>
			/// </summary>
			/// <returns>Returns a scruct with d1 and d2 as fields, containing the two lengths</returns>
			len2d length();
		};

		template<class mytype> inline Array2D<mytype>::Array2D(int d1, int d2) {
			//_array = std::make_shared<mytype[]>(new mytype[d1 * d2]);
			_array = new mytype[d1 * d2];
			_Dim1 = d1;
			_Dim2 = d2;
		}

		template<class mytype> inline Array2D<mytype>::Array2D() {
			//_array = std::make_shared<mytype[]>( new mytype[100]);
			_array = new mytype[100];
			_Dim1 = 10;
			_Dim2 = 10;
		}

		template<class mytype> inline Array2D<mytype>::~Array2D() {
			if (_autoclean) Dispose();
		}

		template<class mytype> inline void Array2D<mytype>::Value(int d1, int d2, mytype value) {
			_panicked = false;
			auto i{ idx(d1,d2) };
			if (!_panicked) _array[i] = value;
		}

		template<class mytype> inline mytype Array2D<mytype>::Value(int d1, int d2) {
			return _array[idx(d1, d2)];
		}

		template<class mytype> inline void Array2D<mytype>::SetAll(mytype v) {
			auto mx{ _Dim1 * _Dim2 };
			for (auto i = 0; i < mx; i++) _array[i] = v;
		}

		template<class mytype> inline std::shared_ptr<Array2D<mytype>> Array2D<mytype>::Dim(int D1, int D2) {
			auto ret{ std::make_shared<Array2D<mytype>>(D1,D2) };
			ret->_autoclean = true;
			return ret;
		}

		template<class mytype> inline std::unique_ptr<Array2D<mytype>> Array2D<mytype>::DimU(int D1, int D2) {
			auto ret{ new Array2D<mytype>>(D1,D2) };
			ret->_autoclean = true;
			return std::unique_ptr<Array2D<mytype>>(ret);			
		}

		template<class mytype> inline void Array2D<mytype>::ReDim(int D1, int D2, bool keepdata) {
			auto newarray{ new mytype[D1 * D2] };
			//std::shared_ptr<mytype[]> newarray ( new mytype[D1 * D2] );
			if (keepdata) {
				for (int i2 = 0; i2 < D2; ++i2) for (int i1 = 0; i1 < D1; ++i1) {
					if (i1 < std::min(D1, _Dim1) && i2 < std::min(D2, _Dim2))
						newarray[i1 + (i2 * D1)] = _array[idx(i1, i2)];
				}
			}
			//if (_array) {
			//delete[] _array;
			//} else { std::cout << "WARNING! Redim, but old array was null pointed!\n"; }
			_Dim1 = D1;
			_Dim2 = D2;
			_array = newarray;
		}

		template<class mytype> inline void Array2D<mytype>::Dispose() {
			if (_array)
				delete[] _array;
			_array = nullptr;
		}

		template<class mytype> inline int Array2D<mytype>::idx(int d1, int d2) {
			//if (Panic && (d1 < 0 || d2 < 0 || d1 >= Dim1 || d2 >= Dim2)) {
			//	char err[200];
			//	sprintf_s(err, "2D Array index out of bounds [%d,%d] (dim %d,%d)", d1, d2, Dim1, Dim2);
			//	Panic(err);
			//}
			return d1 + (d2 * _Dim1);
		}
		template<class mytype> 	inline len2d Array2D<mytype>::length() { len2d r{ _Dim1, _Dim2 }; return r; }

	}
}