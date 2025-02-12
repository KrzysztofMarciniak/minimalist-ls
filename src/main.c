#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

void format_size(off_t size, char *buf, size_t buf_size) {
    snprintf(buf, buf_size, "%.2f KB", (double)size / 1024);
}

void format_permissions(mode_t mode, char *buf, size_t buf_size) {
    snprintf(buf, buf_size, "%c%c%c%c%c%c%c%c%c%c",
             S_ISDIR(mode) ? 'd' : '-',
             (mode & S_IRUSR) ? 'r' : '-',
             (mode & S_IWUSR) ? 'w' : '-',
             (mode & S_IXUSR) ? 'x' : '-',
             (mode & S_IRGRP) ? 'r' : '-',
             (mode & S_IWGRP) ? 'w' : '-',
             (mode & S_IXGRP) ? 'x' : '-',
             (mode & S_IROTH) ? 'r' : '-',
             (mode & S_IWOTH) ? 'w' : '-',
             (mode & S_IXOTH) ? 'x' : '-');
}

const char *get_owner_name(uid_t uid) {
    struct passwd *pw = getpwuid(uid);
    return (pw == NULL) ? "UNKNOWN" : pw->pw_name;
}

const char *get_group_name(gid_t gid) {
    struct group *gr = getgrgid(gid);
    return (gr == NULL) ? "UNKNOWN" : gr->gr_name;
}

void format_time(time_t rawtime, char *buf, size_t buf_size) {
    struct tm *timeinfo = localtime(&rawtime);
    strftime(buf, buf_size, "%Y-%m-%d %H:%M", timeinfo);
}

void print_file_info(const char *path) {
    struct stat file_info;
    if (stat(path, &file_info) == -1) {
        fprintf(stderr, "stat: %s: %s\n", path, strerror(errno));
        return;
    }

    char size_buf[32], permissions_buf[11], time_buf[20];
    format_size(file_info.st_size, size_buf, sizeof(size_buf));
    format_permissions(file_info.st_mode, permissions_buf, sizeof(permissions_buf));
    format_time(file_info.st_mtime, time_buf, sizeof(time_buf));

    printf("%s %-8s %-8s %10s %s %s\n",
           permissions_buf,
           get_owner_name(file_info.st_uid),
           get_group_name(file_info.st_gid),
           size_buf,
           time_buf,
           path);
}

void list_files(const char *path, int detailed) {
    DIR *dp = opendir(path);
    if (dp == NULL) {
        fprintf(stderr, "opendir: %s: %s\n", path, strerror(errno));
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dp)) != NULL) {
    
        char file_path[PATH_MAX];
        snprintf(file_path, sizeof(file_path), "%s/%s", path, entry->d_name);

        struct stat file_info;
        if (stat(file_path, &file_info) == -1) {
            fprintf(stderr, "stat: %s: %s\n", file_path, strerror(errno));
            continue;
        }

        if (detailed) {
            char size_buf[32], permissions_buf[11], time_buf[20];
            format_size(file_info.st_size, size_buf, sizeof(size_buf));
            format_permissions(file_info.st_mode, permissions_buf, sizeof(permissions_buf));
            format_time(file_info.st_mtime, time_buf, sizeof(time_buf));

            printf("%s %-8s %-8s %10s %s %s\n",
                   permissions_buf,
                   get_owner_name(file_info.st_uid),
                   get_group_name(file_info.st_gid),
                   size_buf,
                   time_buf,
                   entry->d_name);
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dp);
}

int main(int argc, char *argv[]) {
    const char *path = ".";
    int detailed = 0;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-l") == 0) {
            detailed = 1;
        } else if (argv[i][0] != '-') {
            path = argv[i];
        } else {
            fprintf(stderr, "Usage: mls [-l] [directory]\n");
            return 1;
        }
    }

    struct stat path_stat;
    if (stat(path, &path_stat) == 0) {
        if (S_ISDIR(path_stat.st_mode)) {
            list_files(path, detailed);
        } else if (S_ISREG(path_stat.st_mode)) {
            if (detailed) {
                print_file_info(path);
            } else {
                printf("%s\n", path);
            }
        } else {
            fprintf(stderr, "mls: %s: Unknown file type\n", path);
            return 1;
        }
    } else {
        fprintf(stderr, "stat: %s: %s\n", path, strerror(errno));
        return 1;
    }

    return 0;
}
