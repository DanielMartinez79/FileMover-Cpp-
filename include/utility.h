#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include <dirent.h>
namespace utility {
    std::string prompt(std::string prompt);
    std::string convertToLower(std::string str);
    std::vector<std::string> convertToLower(std::vector<std::string> vec);
    bool isFile(std::string path);
    bool isDir(std::string path);
    bool exists(std::string path);
    void printVector(std::vector<std::string> vec);
    std::vector <std::string> getFiles(std::string path);

}

#endif // UTILITY_H_INCLUDED
