#define NAME_MAX 255

typedef struct
{
    long ino;    // inode number
    char name[NAME_MAX+1]; // name and null byte
} Dirent;

typedef struct
{
    int fd; // file descriptor
    Dirent d; // directory entry
} DIR;

DIR* opendir(char* dirname);
Dirent* readdir(DIR* dfd);
void closedir(DIR* dfd);
