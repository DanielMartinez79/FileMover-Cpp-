#include "utility.h"

namespace utility {

    std::string prompt(std::string prompt)
    {
        std::string answer;
        std::cout << prompt << std::endl;
        getline(std::cin,  answer);
        return answer;
    }

    bool verify_folder(std::string path) {
        struct stat folderInfo;

        if ( stat(path.c_str(), &folderInfo) != 0) {
            return false;
        } else if ( S_ISDIR(folderInfo.st_mode)){
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

}
