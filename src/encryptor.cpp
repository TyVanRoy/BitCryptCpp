//
//  encryptor.cpp
//  BitCrypt
//

#include "encryptor.hpp"
#include "prompt.hpp"
#include <iostream>
#include <fstream>
#include <sys/stat.h>

using namespace std;

char* gencrypt(bool decrypt, char* input, string key, long length){
    char* output = input;   // clone
    
    for(int i = 0; i < length; i++){
        if(decrypt){
            output[i] += key[i % key.length()];
        }else{
            output[i] -= key[i % key.length()];
        }
    }
    
    return output;
}

