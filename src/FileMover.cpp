#include "FileMover.h"


FileMover::FileMover(std::string source, std::string dest)
{
    destinationPath = dest;
    sourcePath = source;
}

FileMover::~FileMover()
{
    //dtor
}

std::string FileMover::getDestination(){
    return destinationPath;
}

void FileMover::setDestination(std::string dest){
    destinationPath = dest;
}

std::string FileMover::getSource(){
    return sourcePath;
}

void FileMover::setSource(std::string source){
    sourcePath = source;
}

std::string FileMover::reg (std::string keywords){
    std::regex exp("\\s");
    keywords = std::regex_replace(keywords, exp, ".?");
    return "\n*" + keywords + ".*";
}

std::vector <std::string> FileMover::get_files(std::string path) {
    DIR *directory;
    struct dirent *info;
    std::vector <std::string> fileNames;
    if ((directory = opendir(path.c_str())) != NULL){
        while ((info = readdir(directory)) != nullptr){
            fileNames.std::vector<std::string>::push_back(info->d_name);
        }
        closedir(directory);
    }
    return fileNames;
}

void FileMover::print_vector(std::vector<std::string> vec){
    for (unsigned i = 0; i < vec.size(); i++){
        std::cout << vec[i] << std::endl;
    }
}

std::vector <std::string> FileMover::search_folder(std::string keywords, std::vector<std::string> files){
    std::vector<std::string> matches;

    try {
        std::regex exp( keywords);
        for (unsigned i = 0; i < files.size(); i++) {
            if (std::regex_search(files[i], exp, std::regex_constants::match_default)){
                matches.push_back(files[i]);
            }
        }
    } catch (std::regex_error e){
        std::cout << "error" << std::endl;

    }
    return matches;
}

void FileMover::copy_file(std::string pathSrc, std::string pathDest){
    //Opening the source file at the end to get file size
    std::ifstream srcFile;
    srcFile.open(pathSrc, std::ios::binary | std::ios::ate);

    //Opening the destination file
    std::ofstream destFile;
    destFile.open(pathDest, std::ios::binary);

    if (srcFile.is_open()) {
        long long file_size = srcFile.tellg();
        srcFile.seekg(0, std::ios::beg);
        int buff_size = 1024 * 1024;
        char * buff = new char[buff_size];
        long long total = 0;
        std::cout<<"Please wait"<<std::endl;
        while (total < file_size) {
            srcFile.read(buff, buff_size);
            destFile.write(buff, buff_size);
            total += buff_size;
            //std::cout << ((float)total/(float)file_size) * 100;
            //std::cout << "\r";
        }
    }
    srcFile.close();
    destFile.close();

}

bool FileMover::file_exists(std::string pathname){
    std::ifstream file;
    file.open(pathname);
    return file.is_open();
}

void FileMover::copy_matches(std::vector<std::string> matches){
    for (unsigned i = 0; i < matches.size(); i++){
    }
}

