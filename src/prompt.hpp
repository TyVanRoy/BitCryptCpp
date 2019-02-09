//
//  prompt.hpp
//  BitCrypt
//

#ifndef prompt_hpp
#define prompt_hpp

#include <stdio.h>
#include <string>

const static std::string fstr = ">>";
const static std::string critstr = "!!! * ";

// gives a string message, then asks for a yes or no from the user. Returns 0 for no yes for 1.
bool yesnoConfirm(std::string message);

// Close the program with message
void quit(std::string message);

// For one-way messages to the user
void oneway(std::string message);

/*
 For two-way messages to the user.
    Prompts the user with the message,
    attaches a string listing the options,
    then waits for the user to input a corresponding option.
 
 Returns the index of the selected option.
 Returns -1 for q (quit).
*/
int twoway(std::string message, std::string* options, int noptions);

// Sends user the string message. Returns the user's input.
std::string twoway(std::string message);

#endif /* prompt_hpp */
