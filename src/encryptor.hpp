//
//  encryptor.hpp
//  BitCrypt
//

#ifndef encryptor_hpp
#define encryptor_hpp

#include <stdio.h>
#include <string>

char* gencrypt(bool decrypt, char* input, std::string key, long length);

#endif /* encryptor_hpp */
