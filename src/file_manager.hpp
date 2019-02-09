//
//  file_manager.hpp
//  BitCrypt
//

#ifndef file_manager_hpp
#define file_manager_hpp

#include <stdio.h>
#include <string>

const static char* win32os = "Windows 32-bit";
const static char* win64os = "Windows 64-bit";
const static char* unixos = "Unix";
const static char* macos = "Mac OSX";
const static char* linuxos = "Linux";
const static char* otheros = "Other";
const static char* desktop = "Desktop";
const static char* README = "./readme.txt";

// for determining the name of the system OS
std::string getOSName();

class FileManager{
    
public:
    FileManager(bool _windows);
    long getFileSize(std::string filePath);                 // get size of file in bytes in long form
    std::string getFileSizeString(std::string filePath);    // gets the size of the file in giga/mega/kilo/bytes put into a string format
    std::string getcdir();                                  // gets the 'current' directory.
    std::string getReadme();                                // gets the "readme"
    char* getBytes(std::string filePath);                   // extracts data from a file as an array of bytes.
    int putBytes(std::string filePath, char* input);        // writes an array of bytes to the given file. returns 0 if successfull.
    bool checkFile(std::string filePath);                   // checks if the file located at filePath is valid.

private:
    const bool windows;     // OS. windows if true, unix if not.
    const char* homedir;    // home directory
    std::string cdir;       // current directory: operating directory.
    std::string fdiv;       // file-path divider
    
};

#endif /* file_manager_hpp */
