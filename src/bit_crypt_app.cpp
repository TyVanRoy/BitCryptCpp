//
//  bit_crypt_app.cpp
//  BitCrypt
//

#include <iostream>
#include <sys/stat.h>
#include "bit_crypt_app.hpp"
#include "prompt.hpp"
#include "file_manager.hpp"
#include "encryptor.hpp"
#include "history.hpp"

using namespace std;

BitCryptApp::BitCryptApp(bool _windows):windows(_windows), fManager(windows), history(windows){
    // empty constructor
}

void BitCryptApp::run(){
    // Greet user
    cout << "\n\n";
    oneway("Welcome to BitCrypt.. input 'q' at any prompt to restart");
    
    string dset[] = {"use", "about"};
    
    if(twoway("Use BitCrypt or About BitCrypt?", dset, 2)){
        doreadme();
        if(yesnoConfirm("Finished? ")){
            quit("Finished.");
        }
    }

    // Main line
    bool running = true;
    
    /*
     If any of the main methods return false:
     This means that the user attempted a restart. Restart after this.
     */
    while(running){
        
        // First step: set the mode (encrypt or decrypt)
        if(setCryptMode()){
            
            // Set the file
            if(setFile()){
                
                
                // Set the key
                if(setKey()){
                    
                    // string for user's choice confirmation.
                    string userChoiceWarning = "WARNING* Settings:\n\t-";
                    userChoiceWarning += (cryptMode == 0 ? "will: ENCRYPT\n" : "will: DECRYPT\n");
                    userChoiceWarning += ("\t-file-path: " + filePath + " (" + fManager.getFileSizeString(filePath) + ")");
                    userChoiceWarning += ("\n\t-with key: " + keyString);
                    userChoiceWarning += "\n**THE ORIGINAL FILE WILL BE OVERWRITTEN!!**\nReady to encrypt with the current settings? ";
                    
                    // Confirm. Restart on bad confirm.
                    cout << "\n\n";
                    if(yesnoConfirm(userChoiceWarning)){
                        encrypt();
                        if(!history.add(!cryptMode, filePath, keyString)){
                            oneway("!! Problem logging to history!");
                        }
                    }
                }
            }
        }
        
        if(yesnoConfirm("Finished? ")){
            running = false;
            break;
        }
        cout << "..restarting..\n\n";
    }
    
    // end run!
    quit("Finished.");
}

void BitCryptApp::doreadme(){
    cout << fManager.getReadme() << endl;
}

void BitCryptApp::encrypt(){
    char* input = fManager.getBytes(filePath);
    char* output = gencrypt(cryptMode, input, keyString, fManager.getFileSize(filePath));
    
    fManager.putBytes(filePath, output);
    
    if(!cryptMode){
        oneway("\"" + filePath + "\" was ENCRYPTED..");
    }else{
        oneway("\"" + filePath + "\" was DECRYPTED..");
    }
}

bool BitCryptApp::setKey(){
    // Get the user's choice of key
    cout << "\n";
    keyString = twoway("Enter your encryption key (no spaces!)");
    if(keyString == "q"){
        return false;
    }
    return true;
}

bool BitCryptApp::setFile(){
    cout << "\n";
    
    string desktop = fManager.getcdir();
    string choice = twoway("Please put the file you want to encrypt/decrypt on your desktop (" + desktop + ").\nWhat is the name of your file? (include the extension): ");
    
    if(choice == "q"){
        return false;
    }
    
    filePath = desktop + choice;
    
    while(!fManager.checkFile(filePath)){
        choice = twoway("File could not be read. Please try again. Make sure to put the file extension!\n ex: \"file.txt\"\n\nPlease put the file you want to encrypt/decrypt on your desktop (" + filePath + ").\nWhat is the name of your file? (include the extension): ");
        filePath = desktop + choice;
    }
    
    oneway(filePath + " (" + fManager.getFileSizeString(filePath) + ")");
    return true;
}

bool BitCryptApp::setCryptMode(){
    // Option set for crypt mode user decision
    string dset[] = {"e","d"};
    int mode;

    // User sets crypt mode
    cout << "\n";
    mode = twoway("Encrypt or decrypt?", dset, 2);
    
    // Prompt the user about their choice
    if(mode == 1){
        oneway("will decrypt..");
    }else if(mode == 0){
        oneway("will encrypt..");
    }
    
    if(mode != -1){
        cryptMode = mode;
        return true;
    }else{
        return false;
    }
}

