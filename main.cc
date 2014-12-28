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
