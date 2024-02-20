// Lic:
// Units/Headers/SlyvDijkstra.hpp
// Dijkstra
// version: 23.11.01
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

namespace Slyvina {
	namespace Units {

		typedef bool (*DijkstraBlock)(int x, int y);
		enum class DijkstraDirectionAllow {

			/// <summary>
			/// Will only allow horizontal and vertical movement
			/// </summary>
			OnlyStraight,

			/// <summary>
			/// Will only allow diagonal movement if it's also possible to get there with only horizontal and vertical movement in 2 steps. (Prevents going through walls with the corners touching each other yet leaving both nodes free).
			/// </summary>
			DiagonalIfStraightIsPossible,

			/// <summary>
			/// Any direction can do. (I strongly recommend against this one, unless you know what you are doing)
			/// </summary>
			Everywhere
		};

		/// <summary>
		/// This class is to create a Dijkstra driver
		/// </summary>
		class Dijkstra;

		class _DijkstraRoute;
		class _DijkstraNode;

		typedef std::shared_ptr<_DijkstraRoute> DijkstraRoute;
		typedef std::shared_ptr<_DijkstraNode> DijkstraNode;

		class Dijkstra {
		private:
		public:
			DijkstraDirectionAllow DirectionAllow{ DijkstraDirectionAllow::DiagonalIfStraightIsPossible };
			DijkstraBlock Block{ nullptr };
			DijkstraRoute Route(int startx, int starty, int endx, int endy);
			bool Allow(int x, int y) { return !Block(x, y); }
			Dijkstra(DijkstraBlock _B, DijkstraDirectionAllow A = DijkstraDirectionAllow::DiagonalIfStraightIsPossible) { Block = _B; DirectionAllow = A; }
		};

		class _DijkstraRoute {
		private:
			DijkstraNode _first{ nullptr };
			//DijkstraNode _current{ nullptr };
		public:
			_DijkstraRoute() {}; // DON'T EVER USE THIS! It only exist to prevent compiler errors!
			_DijkstraRoute(DijkstraNode StartNode);
			size_t CountNodes();
			DijkstraNode First() { return _first; }
		};

		class _DijkstraNode {
		private:
			DijkstraNode _next{ nullptr };
			int _x{ 0 }, _y{ 0 };
		public:
			_DijkstraNode() {}; // DON'T EVER USE THIS! It only exist to prevent compiler errors!
			_DijkstraNode(DijkstraNode N, int __x, int __y);
			DijkstraNode Next() { return _next; }
			int x() { return _x; }
			int y() { return _y; }
		};
	}
}