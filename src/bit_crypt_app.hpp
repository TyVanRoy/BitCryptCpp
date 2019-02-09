//
//  bit_crypt_app.hpp
//  BitCrypt
//

#ifndef bit_crypt_app_hpp
#define bit_crypt_app_hpp

#include <stdio.h>
#include <string>
#include "file_manager.hpp"
#include "history.hpp"

class BitCryptApp{
    
public:
    BitCryptApp(bool windows);
    void run();             // main logic line
    void doreadme();        // about the app
    void encrypt();         // encrypts the given file with the given key
    bool setCryptMode();    // sets the private variable cryptMode based on the user's choice. returns false if 'q' is input.
    bool setFile();         // sets the private variable filePath based on the user's choice. returns false if 'q' is input.
    bool setKey();          // sets the private varable keyString based on the user's choice. returns false if 'q' is input.
    
private:
    const bool windows;     // true if the program is running on a windows system
    
    int cryptMode;          // 0 for encrypt, 1 for decrypt
    int keyMode;            // 0 for string, 1 for file
    std::string filePath;   // string path to file
    std::string keyPath;    // string path to key file
    std::string keyString;  // string key
    
    FileManager fManager;   // FileManager for the app
    History history;        // Log
    
};

#endif /* bit_crypt_app_hpp */
