#ifndef FILEMOVER_H
#define FILEMOVER_H
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <algorithm>
#include <dirent.h>
#include <regex>

class FileMover
{
    public:
        FileMover(std::string source, std::string dest);
        virtual ~FileMover();
        std::string getDestination();
        void setDestination(std::string dest);
        std::string getSource();
        void setSource(std::string source);
        std::string reg(std::string name);
        std::vector<std::string> searchFolder(std::string keywords, std::vector<std::string> files);
        void copyFile(std::string pathname, std::string dest);
        void copyMatches(std::vector<std::string> matches);
        int moveFile(std::string filepath);
        bool checkDrives();

    protected:

    private:
        std::string destinationPath;
        std::string sourcePath;

};

#endif // FILEMOVER_H
