#ifndef _caesar_h
#define _caesar_h

#include <string>

std::string ceasar_encrypt(std::string string, int shift);

std::string caesar_decrypt(std::string string, int shift);

std::string get_file_contents(const char *filename);

#endif