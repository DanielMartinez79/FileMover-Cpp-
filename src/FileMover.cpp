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
    struct stat folderInfo;
    std::vector <std::string> fileNames;

    if ((directory = opendir(path.c_str())) != NULL){
        while ((info = readdir(directory)) != nullptr){
            std::string fullPath = path + "/" + info->d_name;
            if (stat(fullPath.c_str(), &folderInfo) == 0 && (S_ISREG(folderInfo.st_mode)))
                fileNames.std::vector<std::string>::push_back(info->d_name);
        }
        closedir(directory);
    }
    return fileNames;
}

std::vector<std::string> FileMover::getSourceFiles(){
    return get_files(sourcePath);
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
        std::cout << "regex error" << std::endl;

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

bool FileMover::file_exists(std::string pathname){
    std::ifstream file;
    file.open(pathname);
    if (file.is_open()){
        file.close();
        return true;
    } else {
        return false;
    }
}

void FileMover::copy_matches(std::vector<std::string> matches){
    //loop through file names that matched with search words
    for (unsigned i = 0; i < matches.size(); i++){
        if (!file_exists(destinationPath + "/" + matches[i])){//if file doesnt exist in destination folder
            printf("Copying %s from %s to %s\n", matches[i].c_str(), sourcePath.c_str(), destinationPath.c_str());
            copy_file(sourcePath + "/" + matches[i], destinationPath + "/" + matches[i]);
            std::cout<< "Copying complete" << std::endl;
        } else {//if file already exists in destination folder
            printf("Error: %s already exists in %s \n", matches[i].c_str(), destinationPath.c_str());
        }
    }
}



