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

        std::vector <std::string> get_files(std::string path);
        std::string reg(std::string name);
        std::vector<std::string> search_folder(std::string keywords, std::vector<std::string> files);
        void copy_file(std::string pathname, std::string dest);
        void print_vector(std::vector<std::string> vec);
        bool file_exists(std::string filepath);
        void copy_matches(std::vector<std::string> matches);

    protected:

    private:
        std::string destinationPath;
        std::string sourcePath;
        std::string keywords;

};

#endif // FILEMOVER_H
