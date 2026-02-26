#define F_OK 0
#define F_RDLCK 0
#define F_WRLCK 0
#define F_SETLKW 0

#define O_RDONLY 0
#define O_RDWR 0
#define O_CREAT 0
#define O_TRUNC 0

#define S_IRUSR 0
#define S_IWUSR 0

struct flock {
    int l_whence, l_start, l_len, l_pid, l_type;
};
