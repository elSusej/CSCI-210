#include "types.h"

extern struct NODE* root;
extern struct NODE* cwd;

//make directory
void mkdir(char pathName[]){

    if (strlen(pathName) == 0 || strcmp(pathName, "/") == 0) {
        printf("MKDIR ERROR: no path provided\n");
        return;
    }

    char baseName[64];
    char dirName[256];
    char pathCopy[256];

    strncpy(pathCopy,pathName, sizeof(pathCopy) -1);
    pathCopy[sizeof(pathCopy) - 1] = '\0';

    struct NODE* parent = splitPath(pathCopy, baseName, dirName);
    
    if (parent == NULL) {
        return;
    }

    //check if directory already exists:
    struct NODE* currentDir = parent->childPtr;
    while (currentDir != NULL) {
        if ((strcmp(currentDir->name,baseName) == 0) && (currentDir->fileType == 'D')) {
            printf("MKDIR ERROR: directory %s already exists\n", currentDir->name);
            return;
        }

        currentDir = currentDir->siblingPtr;
    }

    struct NODE* newDir = (struct NODE*)malloc(sizeof(struct NODE));
    strncpy(newDir->name, baseName, sizeof(newDir->name) - 1);
    newDir->name[sizeof(newDir->name) - 1] = '\0';
    newDir->fileType = 'D';
    newDir->childPtr = NULL;
    newDir->siblingPtr = NULL;
    newDir->parentPtr = parent;

    if (parent->childPtr == NULL) {
        parent->childPtr = newDir;
    }
    else {
        currentDir = parent->childPtr;
        while (currentDir->siblingPtr != NULL) {
            currentDir = currentDir->siblingPtr;
        }
        currentDir->siblingPtr = newDir;
    }

    printf("MKDIR SUCCESS: node %s successfully created\n", newDir->name);
    return; //
}

//handles tokenizing and absolute/relative pathing options

struct NODE* splitPath(char* pathName, char* baseName, char* dirName){

    int len = strlen(pathName);
    struct NODE* currentDir;
    
    if (pathName[0] == '/') {
        currentDir = root;
    }
    else {
        currentDir = cwd;
    }

    if (strcmp(pathName, "/") == 0) { //handles case where path name is simply /
            strcpy(dirName,"/");
            strcpy(baseName,"");
            return root;
    }

    char* lastSlash = strrchr(pathName, '/');
    if (lastSlash) {
        strncpy(dirName, pathName, lastSlash - pathName);
        dirName[lastSlash - pathName] = '\0'; // Null terminate dirName
        strcpy(baseName, lastSlash + 1); // Base name is after the last slash
    } else {
        strcpy(dirName, ""); // No directory name, base name is the full path
        strcpy(baseName, pathName);
    }

    //what follows is to find ptr

    char dirToken[255];
    strncpy(dirToken,dirName,sizeof(dirToken) - 1);
    dirToken[sizeof(dirToken) - 1] = '\0';

    char* token  = strtok(dirToken, "/");
    while (token != NULL) {
        int found = 0;
        struct NODE* child = currentDir->childPtr;

        while (child != NULL) {
            if ((strcmp(child->name, token) == 0) && (child->fileType == 'D')) {
                found = 1;
                currentDir = child;
                break;
            }
            child = child->siblingPtr;
        }

        if (!found) {
            printf("ERROR: directory %s does not exist\n", token);
            return NULL;
        }

        token = strtok(NULL, "/"); //NULL tells strtok to continue from where it left off previously
    }
    
    
    return currentDir;
}
