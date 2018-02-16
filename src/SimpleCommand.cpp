#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include "SimpleCommand.h"

using namespace std;

void SimpleCommand::execute() {
	// FIXME: Your code here...

    if (command == "ls") {
        //The command given is "ls". The user wants a list of all items in this directory.
        if (arguments.empty()) {
            //No additional arguments were supplied by the user.
            lsPerform();
        } else if (arguments[0] == "-al") {
            //The user added the "-al" command to get a different output.
            allsPerform();
        } else {
            //TODO - Yoran: Allow users to give any directory name (like "Downloads" or "CLionProjects") and show the ls of that.
        }
    }
    else if (command == "pwd") {
        //The user wants to know what the current directory they're at is.
        pwdPerform();
    }
    //More commands here...
    else {
        //FIXME: Executables might not be recognisable and should just be run?
        cerr << "ERROR: Given command \"" << command << "\" or additional arguments not recognised.";
    }
}

void SimpleCommand::lsPerform() {
    //FIXME?: Maybe forking has to be done for this one too?
    struct dirent **files;
    string currentDir = get_current_dir_name();
    string filePath;

    //For convenience sake, print the current directory for the user.
    pwdPerform();

    //Set up how many items there are in the current directory.
    int count = ::scandir(get_current_dir_name(), &files, NULL, alphasort);

    if (count > 0) {
        //If there are items in this directory.
        while (count--) {
            //For every item, get their file path.
            filePath = currentDir + "/" + files[count]->d_name;

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
}

void SimpleCommand::allsPerform() {
    //FIXME?: Maybe forking has to be done for this one too?
    struct dirent **files;
    struct stat fileStat;
    string currentDir = get_current_dir_name();
    string filePath;

    //For convenience sake, print the current directory for the user.
    pwdPerform();

    //Set up how many items there are in the current directory.
    int count = ::scandir(get_current_dir_name(), &files, NULL, alphasort);

    if (count > 0) {
        //If there are items in this directory.
        while (count--) {
            //For every item, get their file path.
            filePath = currentDir + "/" + files[count]->d_name;

            stat (filePath.c_str(), &fileStat);

            char buf[256];
            strcpy(buf,ctime(&fileStat.st_ctim.tv_sec));
            buf[strlen(buf)-1]='\0';

            cout << fileStat.st_size << " \t\t" << buf << " \t\t" << files[count]->d_name << endl;
        }
    } else {
        //The directory is empty or something else went wrong.
        perror("scandir error");
    }
}

int SimpleCommand::isRegularFile(const char *path) {
    struct stat path_stat;

    //Get the information of the file at the given path location.
    stat(path, &path_stat);

    //Return if the file at the path given is a regular file (aka not a directory).
    return S_ISREG(path_stat.st_mode);
}

void SimpleCommand::pwdPerform() {
    //FIXME?: Maybe forking has to be done for this one too?
    cout << "Current directory: " << ::get_current_dir_name() << endl;
}