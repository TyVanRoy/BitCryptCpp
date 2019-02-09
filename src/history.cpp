//
//  history.cpp
//  BitCrypt
//

#include "history.hpp"
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;


History::History(bool windows_):fManager(windows_){
    time_t now = time(0);
    char* dt = ctime(&now);
    dt[strlen(dt)-1] = '\0';
    
    logName = fManager.getcdir() + "BitCryptLog@" + dt + ".txt";
    cout << logName;
}

bool History::add(bool encrypt, std::string filePath, std::string key){
    fstream output;
    output.open(logName, fstream::app);
    if(output.is_open()){
        string crypt = (encrypt ? "Encrypted " : "Decrypted ");
        output << crypt + filePath + " with key: " + key << endl;
        output.close();
        return true;
    }
    
    output.close();
    return false;
}

