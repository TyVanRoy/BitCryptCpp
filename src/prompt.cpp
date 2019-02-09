//
//  prompt.cpp
//  BitCrypt
//

#include "prompt.hpp"
#include <iostream>
#include <string>

using namespace std;


bool yesnoConfirm(string message){
    string dset[] = {"yes", "no"};
    int dsetn = 2;
    
    int op = twoway(message, dset, dsetn);
    
    bool confirm = (op == 0 ? true : false);
    
    return confirm;
}

void quit(string message){
    // inform user
    oneway(message);
    oneway("quitting..");
    
    // quit
    exit(0);
}

void oneway(string message){
    // output
    cout << fstr << message << endl;
}

string twoway(string message){
    // output
    cout << fstr << message << fstr << " ";
    
    // input
    string input;
    cin >> input;
    return input;
}

int twoway(string message, string* options, int noptions){
    // simplify
    int n = noptions;
    
    while(true){
        // create string to display options
        string optionString = " (";
        for(int i = 0; i < n; i++){
            optionString += options[i];
            if(i < (n - 1)){
                optionString += ", ";
            }else{
                optionString += ", q)";
            }
        }
        
        // output
        cout << fstr << message << optionString;
        
        // input
        string input;
        cout << fstr << " ";
        cin >> input;
        
        // check/return user's decision
        for(int i = 0; i < n; i++){
            if(input == options[i]){
                return i;
            }
        }
        
        // check for quit
        if(input == "q"){
            return -1;
        }
        
        oneway("please enter a valid option..!");
    }
}

