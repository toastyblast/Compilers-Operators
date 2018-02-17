#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include <pwd.h>
#include <grp.h>
#include "SimpleCommand.h"

using namespace std;

void SimpleCommand::execute() {
	// FIXME: Your code here...

    if (command == "ls") {
        //The command given is "ls". The user wants a list of all items in this directory.
        if (arguments.empty()) {
            //No additional arguments were supplied by the user, so return them the ls of the current directory.
            lsPerform(get_current_dir_name());
        } else if (arguments[0] == "-al") {
            //The user added the "-al" command to get a different form of output.
            if (arguments.size() == 1) {
                //This means the user wants the ls -al for the current directory they're in.
                allsPerform(get_current_dir_name());
            } else {
                //This means the user also supplied a second argument, which should be the directory they want to see.
                //TODO - Yoran: Allow users to give any directory name (like "Downloads" or "../CLionProjects") and if it can be found using the route they gave, show the ls -al of that.
                allsPerform(arguments[1].c_str());
            }
        } else {
            //The user supplied a different string, which should be a directory name.
            lsPerform(arguments[0].c_str());
        }
    }
    else if (command == "pwd") {
        //The user wants to know what the current directory they're at is.
        pwdPerform();
    }
    else if (command == "cd") {
        chdirPerform();
    }
    else if (command == "execvp") {
        execvpPerform();
    }
    //More commands here...
    else {
        //FIXME: Executables might not be recognisable and should just be run?
        cerr << "ERROR: Given command \"" << command << "\" or additional arguments not recognised.";
    }
}

void SimpleCommand::lsPerform(const char *requestDir) {
    //FIXME?: Maybe forking has to be done for this one too?
    DIR *desiredDirectory;
    struct dirent **files;
    string desiredDirName = requestDir;
    string filePath;

    if (desiredDirName != get_current_dir_name()) {
        //This means the user gave a specific directory to ls.
        desiredDirectory = opendir(requestDir);
    }

    //Set up how many items there are in the given directory.
    int count = ::scandir(requestDir, &files, NULL, alphasort);

    if (count > 0) {
        //If there are items in this directory.
        while (count--) {
            //For every item, get their file path.
            filePath = desiredDirName + "/" + files[count]->d_name;

            if (isRegularFile(filePath.c_str())) {
                //If the item is a file, print it in such a way.
                cout << "[File] " << files[count]->d_name << "\t\t";
            } else {
                //Otherwise, it's a directory, for readability and as a little extra, we let the user know this.
                cout << "[Dir] " << files[count]->d_name << "\t\t";
            }
        }
    } else {
        //The directory is empty or something else went wrong.
        perror("scandir error");
    }

    cout << endl;
    closedir(desiredDirectory);
}

void SimpleCommand::allsPerform(const char *requestDir) {
    //FIXME?: Maybe forking has to be done for this one too?
    DIR *desiredDirectory;
    struct dirent *files;
    struct stat fileStat;
    struct passwd *fileOwner;
    struct group *fileGroup;
    string desiredDirName = requestDir;
    string filePath;
    char buffer[512];

    if (desiredDirName != get_current_dir_name()) {
        //This means the user gave a specific directory to ls.
        desiredDirectory = opendir(requestDir);
    } else {
        desiredDirectory = opendir(get_current_dir_name());
    }

    while ((files = readdir(desiredDirectory)) != NULL) {
        sprintf(buffer, "%s/%s", requestDir, files->d_name);

        stat(buffer, &fileStat);

        //...

        printf("\t%d ", fileStat.st_nlink);

        fileOwner = getpwuid(fileStat.st_uid);
        printf("\t%s ", fileOwner->pw_name);

        fileGroup = getgrgid(fileStat.st_gid);
        printf("\t%s ", fileGroup->gr_name);

        printf("\t%*zd", 15, fileStat.st_size);

        char dateBuf[256];
        strcpy(dateBuf, ctime(&fileStat.st_mtim.tv_sec));
        dateBuf[strlen(dateBuf)-1]='\0';
        printf("\t%s", dateBuf);

        printf("\t%s\n", files->d_name);
    }

    //Set up how many items there are in the current directory.
//    int count = ::scandir(requestDir, &files, NULL, alphasort);
//
//    if (count > 0) {
//        //If there are items in this directory.
//        while (count--) {
//            //For every item, get their file path.
//            filePath = desiredDirName + "/" + files[count]->d_name;
//
//            stat (filePath.c_str(), &fileStat);
//
//            char buf[512];
//            strcpy(buf,ctime(&fileStat.st_ctim.tv_sec));
//            buf[strlen(buf)-1]='\0';
//
//            cout << fileStat.st_size << " \t\t" << buf << " \t\t" << files[count]->d_name << endl;
//        }
//    } else {
//        //The directory is empty or something else went wrong.
//        perror("scandir error");
//    }

    closedir(desiredDirectory);
}

int SimpleCommand::isRegularFile(const char *path) {
    struct stat path_stat;

    //Get the information of the file at the given path location.
    stat(path, &path_stat);

    //Return if the file at the path given is a regular file (aka not a directory).
    return S_ISREG(path_stat.st_mode);
}

void SimpleCommand::pwdPerform() {
    cout << "Current directory: " << ::get_current_dir_name() << endl;
}

void SimpleCommand::chdirPerform() {
    const char *directory = nullptr;
    if (!arguments.empty()){
        //Set the path.
        if(arguments.at(0)[0] == '~'){
            //If the argument is "~", the user is returned to the home directory.
            struct passwd *pw = getpwuid(getuid());
            directory = pw->pw_dir;
        } else {
            string path = arguments.at(0);
            directory = path.c_str();
        }
    } else {
        //If no path is specified a.k.a only "cd" is written. The user is returned to the home directory.
        struct passwd *pw = getpwuid(getuid());
        directory = pw->pw_dir;
    }

    if (chdir(directory) == -1){
        perror("cd ");
    } else {
        pwdPerform();
    }
}

void SimpleCommand::execvpPerform() {
    //Put the arguments from the vector to the char array.
    char* args[arguments.size()+1];
    for (int i=0; i<arguments.size(); ++i) {
        args[i] = (char *) arguments.at(i).c_str();
    }
    //Set the last argument to be a nullptr.(Required by the documentation.)
        args[arguments.size()] = nullptr;
    //Execute the program.
    if(execvp(args[0], args)){
        perror("exec ");
    }
}