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

string convertToLower(string str){
    for (unsigned i = 0; i < str.size(); i++){
        if (str[i] > 64 && str[i] < 91) {
            str[i] += 32;
        }
    }
    return str;
}

vector<string> convertToLower(vector<string> vec){
    for (unsigned i = 0; i < vec.size(); i++){
        vec[i] = convertToLower(vec[i]);

    }
    return vec;
}

int main()
{
    while (true) {
    //ask user for the path of the folder they want to search
    string pathSrc = prompt("Where do I search?");
    if (verify_folder(pathSrc)){ //verify that the folder exists
        //asking user for the path to folder to save files in
        string pathDest = prompt("Where do I save?");
        if (verify_folder(pathDest)){ //verifying that the folder exists

            //creating FileMover object with the paths given by user
            FileMover fm(pathSrc, pathDest);
            //getting a vector of the files in the source path
            vector <string> files = fm.getSourceFiles();
            files = convertToLower(files);
            //asking user what words to search for in the source folder
            string searchFor = prompt("What should I search for?");
            //searching the titles of files in the search folder to match with keywords given by user
            vector<string> matches = fm.search_folder( fm.reg(searchFor), files);

            if (matches.size() > 0) {
                cout << "The following matches were found: "<< endl;
                fm.print_vector(matches);
                if (prompt("Would you like to copy these files? (y/n)").compare("y") == 0){
                    fm.copy_matches(matches);
                }
            } else {
                cout << "No matches found" << endl;
            }
        } else {
            cout << "Destination folder not found" << endl;
        }
    } else {
        cout << "Source folder not found" <<endl;
    }
    }
    return 0;
}


