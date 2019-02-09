//
//  file_manager.cpp
//  BitCrypt
//

#include "file_manager.hpp"
#include "prompt.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>

using namespace std;

FileManager::FileManager(bool _windows):windows(_windows){
    // assign the appropriate file-path divider for OS
    if(windows){
        fdiv = "\\";
    }else{
        fdiv = "/";
    }
    
    // assigns appropriate home directory for OS
    homedir = "";
    if(windows){
        char* userprofile = getenv("USERPROFILE");
//        char* homedrive = getenv("HOMEDRIVE");
//        char* homepath = getenv("HOMEPATH");
        homedir = userprofile;
    }else{
        if ((homedir = getenv("HOME")) == NULL) {
            homedir = getpwuid(getuid())->pw_dir;
        }
    }
    
    // set current directory to homedir
    cdir = (homedir + fdiv + desktop + fdiv);
}

string FileManager::getReadme(){
    string readme = "";
    string line = "";
    
    fstream file;
    file.open(README);
    if(file.is_open()){
        while(getline(file, line)){
            readme += line + "\n";
            line = "";
        }
    }else{
        quit("File Error !");
    }
    
    file.close();

    return readme;
}

bool FileManager::checkFile(string filePath){
    fstream file;               // test file
    file.open(filePath);        // open the file
    
    // is file open?
    if(file.is_open())
        return true;
    
    // file is not open
    return false;
}

string FileManager::getcdir(){
    return this->cdir;
}

string FileManager::getFileSizeString(string filePath){
    string output = "";
    long total = getFileSize(filePath);
    
    long gigs = total / (1000000000);
    if(gigs != 0){
        total -= (gigs * (1000000000));
        output += to_string(gigs) + " gigabytes, ";
    }
    
    long megs = total / (1000000);
    if(megs != 0){
        total -= (megs * (1000000));
        output += to_string(megs) + " megabytes, ";
    }
    
    long kils = total / (1000);
    if(kils != 0){
        total -= (kils * (1000));
        output += to_string(kils) + " kylobytes, and ";
    }
    
    output += to_string(total) + " bytes.";
    return output;
}

long FileManager::getFileSize(string filePath){
    long n = 0;
    
    struct stat results;
    if (stat((filePath.c_str()), &results) == 0){
        n = results.st_size;
    }else{
        quit("File Error !");
    }
    
    return n;
}

int FileManager::putBytes(string filePath, char* input){
    const char* outName = filePath.c_str();         // output file name
    long fileSizeInBytes = getFileSize(filePath);   // file size
    
    // Write to file
    ofstream outFile(outName, ios::binary|ios::out);
    if(outFile.is_open()){
        outFile.write(input, fileSizeInBytes);
    }else{
        quit("File Error !");
    }
    outFile.close();
    
    return 0;
}

char* FileManager::getBytes(string filePath){
    const char* inName = filePath.c_str();          // extra
    long fileSizeInBytes = getFileSize(filePath);   // file size
    char* input = new char[fileSizeInBytes];       // stores input
    
    // Read in file
    ifstream inFile(inName, ios::binary|ios::in);
    if(inFile.is_open()){
        inFile.read(input, fileSizeInBytes);
    }else{
        quit("File error !");
    }
    inFile.close();
    
    return input;
}

string getOSName(){
    #ifdef _WIN32
        return win32os;
    #elif _WIN64
        return win64os;
    #elif __unix || __unix__
        return unixos;
    #elif __APPLE__ || __MACH__
        return macos;
    #elif __linux__
        return linuxos;
    #else
        return otheros;
    #endif
}
