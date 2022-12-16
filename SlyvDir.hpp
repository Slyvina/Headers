// Lic:
// Units/Headers/SlyvDir.hpp
// Slyvina - Directory (header)
// version: 22.12.14
// Copyright (C) 2022 Jeroen P. Broks
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

		enum class DirWant { Files, Directories, FilesAndDirectories, Tree };

		/// <summary>
		/// Is a path an actual directory?
		/// </summary>
		/// <param name="pth">Path</param>
		/// <returns>True if the path was found and actually identified as a directory</returns>
		bool IsDir(std::string pth);

		/// <summary>
		/// Is a path an actual file?
		/// </summary>
		/// <param name="pth">Path</param>
		/// <returns>True if found and identified as a file</returns>
		bool IsFile(std::string pth);

		/// <summary>
		/// Retrieve the list of files in a directory
		/// </summary>
		/// <param name="Dir"></param>
		/// <param name="Want"></param>
		/// <param name="allowhidden"></param>
		/// <param name="addprefix"></param>
		/// <returns></returns>
		VecString FileList(std::string Dir, DirWant Want = DirWant::Files, bool allowhidden = false, std::string addprefix = "");


		/// <summary>
		/// Returns the list of all files in a directory recursively
		/// </summary>
		/// <param name="dir"></param>
		/// <param name="allowhidden"></param>
		/// <returns></returns>
		VecString GetTree(std::string dir, bool allowhidden = false);

	}
}