/*
 *
 */
#include "caesar.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cerrno>
#include <set>
#include <vector>
#include <utility>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <map>

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
      // encrypt or decrypt via args
      // format: ./caesar encrypt|decrypt|e|d <filename> <key>
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
      auto decrypted = std::vector<std::string>();
      auto decryptedSorted = caesar_hack(input, decrypted);
      int maxMatchingWords = decryptedSorted[0].first;
      int totalWords = 1;
      for (unsigned int i = 0; i < input.length(); ++i) {
         if (isblank(input[i])) {
            ++totalWords;
         }
      }

      for (auto pair : decryptedSorted) {
         if (maxMatchingWords != 0 && pair.first != maxMatchingWords) {
            break;
         }

         std::cout << "=== Key: " << pair.second << " Words matched: " << 
                      pair.first << "/" << totalWords << " ===\n";
         std::cout << decrypted[pair.second] << "\n"; 
      }

      std::cout << "The best match(es) are shown. Show all? (Y/N)\n";
      char response;
      std::cin >> response;
      if (response == 'Y' || response == 'y') {
         for (auto pair : decryptedSorted) {
            std::cout << "=== Key: " << pair.second << " Words matched: " << 
                         pair.first << "/" << totalWords << " ===\n";
            std::cout << decrypted[pair.second] << "\n"; 
         }         
      }
   }

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

std::vector<std::pair<int, int>> caesar_hack(std::string string, 
                                             std::vector<std::string> &decrypted) {
   // generate 26 sets of texts based on 0-25 key
   for (int i = 0; i < 26; ++i) {
      decrypted.push_back(caesar_decrypt(string, i));
   }

   // generate a set of english words in dictionary
   auto dictionary = std::unordered_set<std::string>();
   std::ifstream infile("words.txt");
   std::string line;
   while (std::getline(infile, line)) {
      dictionary.insert(line);
   }
   
   // check if words are in dictionary
   // and insert into vector pairs<numWords, index>
   // numWords is the first element to take advantage of std::sort
   auto decryptedCounted = std::vector<std::pair<int, int>>();
   int index = 0;
   for (auto string : decrypted) {
      std::istringstream iss(string);
      std::string word;
      int numWords = 0;
      while (iss >> word) {
         std::transform(word.begin(), word.end(), word.begin(), ::tolower);
         if (dictionary.find(word) != dictionary.end()) {
            ++numWords;
         }
      }
      decryptedCounted.push_back(std::pair<int, int>(numWords, index));
      ++index;
   }

   std::sort(decryptedCounted.begin(), decryptedCounted.end(), sortDescThenAsc);
   return decryptedCounted;
}

bool sortDescThenAsc(const std::pair<int, int> &a, const std::pair<int, int> &b) {
   if (a.first == b.first) {
      return a.second < b.second;
   }
   return a.first > b.first;
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