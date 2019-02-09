//
//  main.cpp
//  BitCrypt
//

#include <iostream>
#include <string>
#include "bit_crypt_app.hpp"
#include "file_manager.hpp"
#include "prompt.hpp"
#include "encryptor.hpp"

int main() {
    /*
     Determine the system OS for the app initialization.
     Windows or not windows
     */
    bool windows_;
    std::string osName = getOSName();
    
    if(osName == win32os || osName == win64os){
        windows_ = true;
    }else{
        windows_ = false;
    }
        
    // Create & run a BitCryptApp.
    BitCryptApp app(windows_);
    app.run();
    
    return 0;
}
