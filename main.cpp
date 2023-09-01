#include <bits/stdc++.h>
#include <dirent.h>
#include <sys/stat.h>
using namespace std;
#if defined(_WIN32) || defined(_WIN64)
    string delim =  "\\";
    string path = "%userprofile%\\AppData\\Roaming\\.minecraft\\";
    string cp = "xcopy";
#elif defined(__APPLE__) && defined(__MACH__)
    string delim = "/";
    string path = "~/Library/Application\ Support/minecraft/";
    string cp = "cp";
#else
    string delim = "/";
    string path = "~/.minecraft/";
    string cp = "cp";
#endif

bool folderExists(string folderPath) {
    struct stat info;
    return stat(folderPath.c_str(), &info) == 0 && (info.st_mode & S_IFDIR);
}

int main() {
    // install forge
    try {
        system("java -jar forge.jar");
    } 
    catch (exception e) {
        cerr << "you may not java installed or you have run this program in the wrong file!" << endl;
    }

    // move all mods to the minecraft folder
    try {
        DIR *dir;
        struct dirent *entry;

        if (folderExists(path + "mods")) {
            cout << "reached!" << endl;
            system(("mkdir " + path + "mods").c_str());
        }

        if ((dir = opendir("mods")) != nullptr) {
            while ((entry = readdir(dir)) != nullptr) {
                if (entry->d_type == DT_REG) {
                    string from = "mods" + delim + entry->d_name;
                    string to = path + "mods" + delim + entry->d_name;
                    string command = cp + " " + from + " " + to;
                    system(command.c_str());
                }
            }
        }
        closedir(dir);
    } 
    catch (exception e) {
        cerr << "failed the copy!" << endl;
        cerr << e.what() << endl;
    }
}