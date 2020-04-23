#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void listdir(const char *name, int level)
{
    DIR *dir;
    struct dirent *entry;
    struct stat sb;

    if (!(dir = opendir(name)))
        return;
    if (!(entry = readdir(dir)))
        return;
	

    do {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
            path[len] = 0;
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;	
	    char *file_name = entry->d_name;
	    char complete_filename[512];
	    strcpy(complete_filename, "./");
	    strcat(complete_filename, "/");
            strcat(complete_filename, file_name);	
	    stat(complete_filename, &sb);
        
            printf("%*sd:[%s] tamaño:%6lld bytes\n", level*4, "", entry->d_name, (long long)sb.st_size);
            listdir(path, level + 1);
        }
        else{
	    char *file_name = entry->d_name;
	    char complete_filename[512];
	    strcpy(complete_filename, "./");
	    strcat(complete_filename, "/");
            strcat(complete_filename, file_name);
	    stat(complete_filename, &sb);
            printf("%*sf:%s tamaño:%6lld bytes\n", level*4, "", entry->d_name, (long long)sb.st_size);
	    
	}
	
    } while (entry = readdir(dir));
    closedir(dir);
}

int main(void)
{
    listdir(".", 0);
    return 0;
}
