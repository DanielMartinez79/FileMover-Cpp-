#include "utility.h"

namespace utility {

    std::string prompt(std::string prompt)
    {
        std::string answer;
        std::cout << prompt << std::endl;
        getline(std::cin,  answer);
        return answer;
    }

    bool isDir(std::string path) {
        struct stat folderInfo;

        if ( stat(path.c_str(), &folderInfo) == 0 && S_ISDIR(folderInfo.st_mode)) {
            return true;
        } else {
            return false;
        }
    }

    std::string convertToLower(std::string str){
        for (unsigned i = 0; i < str.size(); i++){
            if (str[i] > 64 && str[i] < 91) {
                str[i] += 32;
            }
        }
        return str;
    }

    std::vector<std::string> convertToLower(std::vector<std::string> vec){
        for (unsigned i = 0; i < vec.size(); i++){
            vec[i] = convertToLower(vec[i]);

        }
        return vec;
    }

    bool isFile(std::string path) {
        struct stat fileInfo;
        if ( stat(path.c_str(), &fileInfo) == 0 && S_ISREG(fileInfo.st_mode)) {
            return true;
        } else {
            return false;
        }
    }

    bool exists(std::string path){
        struct stat info;
        if (stat(path.c_str(), &info) == 0){
            return true;
        } else {
            return false;
        }
    }

    void print_vector(std::vector<std::string> vec)
    {
        for (unsigned i = 0; i < vec.size(); i++){
            std::cout << vec[i] << std::endl;
        }
    }

    std::vector <std::string> getFiles(std::string path)
    {
        DIR *directory;
        struct dirent *info;
        std::vector <std::string> fileNames;
        if ((directory = opendir(path.c_str())) != NULL){
            while ((info = readdir(directory)) != nullptr){
                std::string fullPath = path + "/" + info->d_name;
                if (utility::isFile(fullPath)){
                    fileNames.std::vector<std::string>::push_back(info->d_name);
                }

            }
        closedir(directory);

        }
        if (fileNames.size() == 0){
            std::cout << "Warning: no files in this folder" << std::endl;
        }
        return fileNames;
    }

}
