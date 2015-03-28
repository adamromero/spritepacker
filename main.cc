/*
This file is part of Sprite Packer

Copyright (c) 2014 Adam Romero

Sprite Packer is free software: you can redistribute
it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

Sprite Packer is distributed in the hope that it will
be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Sprite Packer.  If not,
see <http://www.gnu.org/licenses/>.
*/

#include "SpritePacker.h"

int main(int argc, char *argv[]) {
   if (argc < 3 || argc > 3) {
      std::cout << "usage: spritepacker <directory-path> <output-filename>\n";
      return 1;
   }

   if (!boost::filesystem::is_directory(argv[1])) {
      std::cout << "\"" << argv[1] << "\"" << " is not a directory\n";
      return 1;
   }

   SpritePacker packer(argv[1], argv[2]);

   if (packer.imageFilesFound()) {
      packer.packImages();
      packer.outputMergedImage();
   } else {
      std::cout << "Image files not found\n";
   }

   return 0;
}
