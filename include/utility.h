#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <algorithm>
namespace utility {
    std::string prompt(std::string prompt);
    bool verify_folder(std::string path);
    std::string convertToLower(std::string str);
    std::vector<std::string> convertToLower(std::vector<std::string> vec);


}

#endif // UTILITY_H_INCLUDED
