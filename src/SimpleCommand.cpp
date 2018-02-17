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
                allsPerform(arguments[1].c_str());
            }
        } else {
            //The user supplied a different string, which should be a directory name.
            lsPerform(arguments[0].c_str());
        }
    } else if (command == "pwd") {
        //The user wants to know what the current directory they're at is.
        pwdPerform();
    } else if (command == "cd") {
        chdirPerform();
    } else if (command == "execvp") {
        execvpPerform();
    }
        //More commands here...
    else {
        //FIXME: Executables might not be recognisable and should just be run?
        cerr << "ERROR: Given command \"" << command << "\" or additional arguments not recognised.";
    }
}

/**
 * Method that prints all the files within the directory on the given path in a simple width-list. Also shows if the
 *  item is a file or another directory.
 *
 * @param const char *requestDir is the path the user has given us, that we should return the contents of.
 */
void SimpleCommand::lsPerform(const char *requestDir) {
    //FIXME?: Maybe forking has to be done for this one too?
    //dirent ** because scandir() requires this, as it expects the reference of a pointer for one of its input variables.
    struct dirent **files;
    string desiredDirName = requestDir;
    string filePath;

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
}

/**
 * Method that prints everything in the directory on the given path like "ls -al" would in Linux' command prompt.
 *  It is deliberately designed to look exactly like said OS' output.
 *
 * @param const char *requestDir is the path the user has given us, that we should return the contents of.
 */
void SimpleCommand::allsPerform(const char *requestDir) {
    //FIXME?: Maybe forking has to be done for this one too?
    //Prepare a directory variable to store the directory to read in.
    DIR *desiredDirectory;
    //Keep a dirent * to access the files within the directory one by one.
    struct dirent *files;
    //Used late to retrieve information about the current file with.
    struct stat fileStat;
    //These are needed to print the file's current owner and group later.
    struct passwd *fileOwner;
    struct group *fileGroup;

    string desiredDirName = requestDir;
    //Buffer to keep the current path to our file in later.
    char buffer[512];

    //Open the directory (if possible, otherwise it will return null) the user has given us.
    desiredDirectory = opendir(requestDir);

    cout << "[Typ&Perms]\t[Links]\t[Owner]\t[Group]\t\t[Size (Kb)]\t[Last modified]\t\t\t\t[Name]" << endl;

    //As long as there's a next file in the directory, loop through and print its information.
    while ((files = readdir(desiredDirectory)) != NULL) {
        //sprint to define the path to our file.
        sprintf(buffer, "%s/%s", requestDir, files->d_name);

        //Use the stat function (see the manual for stat) to be able to get information about the current file in the
        // given directory we're looking at.
        stat(buffer, &fileStat);

        /** Credit for this piece of code goes to TheJals on StackOverflow. **/
        // [file type]
        //Let's start with the file type
        switch (fileStat.st_mode & S_IFMT) {
            case S_IFBLK:
                printf("b");
                break;
            case S_IFCHR:
                printf("c");
                break;
            case S_IFDIR:
                printf("d");
                break; //It's a (sub)directory
            case S_IFIFO:
                printf("p");
                break; //fifo
            case S_IFLNK:
                printf("l");
                break; //Sym link
            case S_IFSOCK:
                printf("s");
                break;
                //Filetype isn't identified
            default:
                printf("-");
                break;
        }

        //[permissions]
        //Same for the permissions, we have to test the different rights
        printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
        printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
        printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
        printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
        printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
        printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
        /** End part by TheJals. **/

        //This number will show the amount of hard links from other directories to the current file. This includes
        // any currently open instances of said file.
        printf("\t\t%d", static_cast<int>(fileStat.st_nlink));

        //Get the owner of this file. This is the account on the device that has ownership of the file.
        fileOwner = getpwuid(fileStat.st_uid);
        printf("\t%s", fileOwner->pw_name);

        //Get the file group of this file. If the device has groups like "admin", these would show up, or the
        // original owner, for instance too.
        fileGroup = getgrgid(fileStat.st_gid);
        printf("\t%s", fileGroup->gr_name);

        //Print the size of the file, in kilobytes. use %*d to set a width left of the number, so we can space
        // everything in vertical columns (as bigger numbers would break this if we did not change the left width).
        printf("\t%*zd", 15, fileStat.st_size);

        //Get the date of when the file was last modified. Buffer this and make a copy into the buffer with said time.
        // Then remove the '/n' that ctime() automatically places behind it, as we do not want this.
        char dateBuf[256];
        strcpy(dateBuf, ctime(&fileStat.st_mtim.tv_sec));
        dateBuf[strlen(dateBuf) - 1] = '\0';
        //Print the last date of modification.
        printf("\t%s", dateBuf);

        //Finally, print the name of the file.
        printf("\t%s\n", files->d_name);
    }

    //And last but not least, after all files have been printed, close the directory.
    closedir(desiredDirectory);
}

/**
 * Internal helper method used by the method lsPerform(const char*) to check if the given item path points to a file
 * or a directory.
 *
 * @param const char *path is the path to the item we need to check.
 * @return 1 if the path leads to a regular file, -1 if it leads to anything else (namely, a directory).
 */
int SimpleCommand::isRegularFile(const char *path) {
    struct stat pathStat;

    //Get the information of the file at the given path location.
    stat(path, &pathStat);

    //Return if the file at the path given is a regular file (aka not a directory).
    return S_ISREG(pathStat.st_mode);
}

/**
 * Method that returns the current working directory that the console is located in.
 */
void SimpleCommand::pwdPerform() {
    cout << "Current directory: " << ::get_current_dir_name() << endl;
}

void SimpleCommand::chdirPerform() {
    const char *directory = nullptr;
    if (!arguments.empty()) {
        //Set the path.
        if (arguments.at(0)[0] == '~') {
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

    if (chdir(directory) == -1) {
        perror("cd ");
    } else {
        pwdPerform();
    }
}

void SimpleCommand::execvpPerform() {
    //Put the arguments from the vector to the char array.
    char *args[arguments.size() + 1];
    for (int i = 0; i < arguments.size(); ++i) {
        args[i] = (char *) arguments.at(i).c_str();
    }
    //Set the last argument to be a nullptr.(Required by the documentation.)
    args[arguments.size()] = nullptr;
    //Execute the program.
    if (execvp(args[0], args)) {
        perror("exec ");
    }
}