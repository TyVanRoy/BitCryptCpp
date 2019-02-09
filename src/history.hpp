//
//  history.hpp
//  BitCrypt
//

#ifndef history_hpp
#define history_hpp

#include <stdio.h>
#include <string>
#include "file_manager.hpp"

class History{

public:
    // creates the new log on the user's desktop
    History(bool _windows);
    
    // adds to the history log
    bool add(bool encrypt, std::string filePath, std::string key);
    
private:
    FileManager fManager;   // local file manager
    std::string logName;    // name of the log

};

#endif /* history_hpp */
