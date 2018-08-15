#include "FileMover.h"
#include "utility.h"


FileMover::FileMover(std::string source, std::string dest)
{
    destinationPath = dest;
    sourcePath = source;
}

FileMover::~FileMover()
{
    //dtor
}

std::string FileMover::getDestination()
{
    return destinationPath;
}

void FileMover::setDestination(std::string dest)
{
    destinationPath = dest;
}

std::string FileMover::getSource()
{
    return sourcePath;
}

void FileMover::setSource(std::string source)
{
    sourcePath = source;
}

std::string FileMover::reg (std::string keywords)
{
    std::regex exp("\\s");
    keywords = std::regex_replace(keywords, exp, ".?");
    return "\n*" + keywords + ".*";
}

std::vector <std::string> FileMover::search_folder(std::string keywords, std::vector<std::string> files)
{
    std::vector<std::string> matches;
    try {
        std::regex exp( keywords);
        for (unsigned i = 0; i < files.size(); i++) {
            if (std::regex_search(files[i], exp, std::regex_constants::match_default)){
                matches.push_back(files[i]);
            }
        }
    } catch (std::regex_error e){
        std::cout << "regex error" << std::endl;

    }
    return matches;
}

void FileMover::copy_file(std::string pathSrc, std::string pathDest)
{
    //Opening the source file at the end to get file size
    std::ifstream srcFile;
    srcFile.open(pathSrc, std::ios::binary | std::ios::ate);

    //Opening the destination file
    std::ofstream destFile;
    destFile.open(pathDest, std::ios::binary);

    if (srcFile.is_open()) {
        long long file_size = srcFile.tellg();//getting file size
        srcFile.seekg(0, std::ios::beg);//moving put to start of file
        int buff_size = 1024 * 1024;
        char * buff = new char[buff_size];//1 MB buffer
        long long total = 0;//counter used to keep track of progress
        if (file_size > buff_size) {
            while (total < file_size) {
                srcFile.read(buff, buff_size);//write to buffer
                destFile.write(buff, buff_size);//read from buffer
                total += buff_size;//increment the progress of file copying
            //std::cout << ((float)total/(float)file_size) * 100;
            //std::cout << "\r";
            }
        } else {
            srcFile.read(buff, file_size);
            destFile.write(buff, file_size);
        }
    }
    srcFile.close();
    destFile.close();

}

void FileMover::copy_matches(std::vector<std::string> matches)
{
    //loop through file names that matched with search words
    for (unsigned i = 0; i < matches.size(); i++){
        if (!utility::exists(this->getDestination() + "/" + matches[i])){//if file doesnt exist in destination folder
            if (checkDrives()) {
                printf("Moving %s from %s to %s\n", matches[i].c_str(), this->getSource().c_str(), this->getDestination().c_str());
                move_file(matches[i]);
                std::cout << "Move complete" << std::endl;
            } else {
                printf("Copying %s from %s to %s\n", matches[i].c_str(), this->getSource().c_str(), this->getDestination().c_str());
                copy_file(this->getSource() + "/" + matches[i], this->getDestination() + "/" + matches[i]);
                std::cout<< "Copying complete" << std::endl;
            }
        } else {//if file already exists in destination folder
            printf("Error: %s already exists in %s \n", matches[i].c_str(), this->getDestination().c_str());
        }
    }
}

int FileMover::move_file(std::string filename)
{
    std::string src = this->getSource() + "/" + filename;
    std::string dst = this->getDestination() + "/" + filename;

    return rename(src.c_str(), dst.c_str());

}

/*This method checks if the destination and source folder are on the same device
If so, it returns true. Otherwise it returns false */
bool FileMover::checkDrives(){

    struct stat srcInfo, destInfo;

    stat(this->getDestination().c_str(), &destInfo);
    stat(this->getSource().c_str(), &srcInfo);
    return (srcInfo.st_dev == destInfo.st_dev);


}


