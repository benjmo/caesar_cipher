/*
 *
 */
#include "caesar.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cerrno>
#include <set>
#include <vector>

int main(int argc, char *argv[]) {
   if (argc == 1) {
      int n;
      std::cout << "Would you like to encrypt or decrypt text?\n" <<
                   "1. Encrypt (default)\n" <<
                   "2. Decrypt\n" <<
                   "Please enter 1 or 2: ";
      std::cin >> n;

      if (n != 1 && n != 2) {
         std::cout << "Invalid response, quitting.\n";
      }
   } else if (((std::string(argv[1]) == "encrypt" || std::string(argv[1]) == "e") ||
               (std::string(argv[1]) == "decrypt" || std::string(argv[1]) == "d")) && 
                argc == 4) {
      auto input = get_file_contents(argv[2]);
      std::cout << input << "\n";

      int key;
      try {
         key = std::stoi(argv[3]);
      } catch (std::exception const &e) {
         std::cout << "Invalid arguments.\n";
         return 0;
      }

      if (std::string(argv[1]) == "encrypt" || std::string(argv[1]) == "e") {
         auto cipher = ceasar_encrypt(input, key);
         std::cout << cipher << "\n";
      } else {
         auto text = caesar_decrypt(input, key);
         std::cout << text << "\n";
      }
   } else if ((std::string(argv[1]) == "decrypt" || std::string(argv[1]) == "d") &&
              argc == 3) {

      // Decrypt brute force

      auto input = get_file_contents(argv[2]);
      std::cout << input << "\n";

      auto decrypted = std::vector<std::string>();
      for (int i = 0; i < 26; ++i) {
         decrypted.push_back(caesar_decrypt(input, i));
      }

      for (auto &text : decrypted) {
         std::cout << text << "\n";
      }
   }

//   std::cout << n;

   return 0;
}

std::string ceasar_encrypt(std::string string, int key) {
   for (auto &c : string) {
      if (c >= 'A' && c <= 'Z') {
         c = ((c + key - 'A') % 26) + 'A';
      } else if (c >= 'a' && c <= 'z') {
         c = ((c + key - 'a') % 26) + 'a';
      }
   }
   return string;
}

std::string caesar_decrypt(std::string string, int key) {
   auto shift = 26 - key;
   return ceasar_encrypt(string, shift);   
}

std::string get_file_contents(const char *filename) {
   std::ifstream in(filename, std::ios::in | std::ios::binary);
   if (in) {
      std::string contents;
      in.seekg(0, std::ios::end);
      contents.resize(in.tellg());
      in.seekg(0, std::ios::beg);
      in.read(&contents[0], contents.size());
      in.close();
      return(contents);
   }
   throw(errno);
}