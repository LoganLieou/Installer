#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
    string delim =  "\\";
    string path = "%userprofile%\\AppData\\Roaming\\.minecraft\\";
    string cp = "xcopy";
#elif defined(__APPLE__) && defined(__MACH__)
    std::string delim = "/";
    std::string path = "~/Library/Application\\ Support/minecraft/";
    std::string cp = "cp";
#else
    string delim = "/";
    string path = "~/.minecraft/";
    string cp = "cp";
#endif

bool folderExists(std::string folderPath) 
{
    struct stat info;
    return stat(folderPath.c_str(), &info) == 0 && (info.st_mode & S_IFDIR);
}

int main(void)
{
    system("java -jar forge.jar");

    DIR *dir;
    struct dirent *entry;

    if (folderExists(path + "mods"))
    {
        system("mods");
    }

    if ((dir = opendir("mods")) != NULL) 
    {
        while ((entry = readdir(dir)) != NULL) 
        {
            if (entry->d_type == DT_REG) 
            {
                std::string to = "";
                std::string from = "";
                std::string command = to + " " + from;
                system(command.c_str());
            }
        }
    }
    closedir(dir);

    return 0;
}
