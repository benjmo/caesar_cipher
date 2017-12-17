#ifndef _caesar_h
#define _caesar_h

#include <string>
#include <vector>

std::string ceasar_encrypt(std::string string, int shift);

std::string caesar_decrypt(std::string string, int shift);

std::vector<std::pair<int, int>> caesar_hack(std::string string, std::vector<std::string> &decrypted);

bool sortDescThenAsc(const std::pair<int, int> &a, const std::pair<int, int> &b);

std::string get_file_contents(const char *filename);

#endif