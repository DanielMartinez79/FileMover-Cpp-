#include <iostream>
#include "FileMover.h"
using namespace std;

string prompt(string prompt)
{
    string answer;
    cout << prompt << endl;
    getline(cin,  answer);
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

int main()
{
    string pathSrc = prompt("Where do I search?");
    if (verify_folder(pathSrc)){
        string pathDest = prompt("Where do I save?");
        if (verify_folder(pathDest)){
            FileMover fm(pathSrc, pathDest);
            string searchFor = prompt("What should I search for?");
            vector <string> files = fm.get_files(pathSrc);
            vector<string> matches =fm.search_folder( fm.reg(searchFor), files);
            if (!fm.file_exists(pathDest + "\\"+ matches[0])){
                fm.copy_file(pathSrc + "\\" + matches[0], pathDest+"\\"+matches[0]);
            }
        }
    }

    return 0;
}


