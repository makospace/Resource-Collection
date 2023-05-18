#include "apue.h"
#include <dirent.h>
#include <limits.h>
#include <fcntl.h>
 
typedef int Myfunc(const char *, const struct stat *, int);  //typedef重定义函数类型
 //Myfunc代表这样一类函数，函数名为Myfunc，函数参数为const char *, const struct stat *, int，返回值为int
static Myfunc  myfuncCompareLength, myfuncCompareContent, myfuncCompareName;
static int  myftw(char *, Myfunc *);  //myftw是这样一类函数，函数名为myftw，函数参数为char *, Myfunc *，返回值为int
static int  dopath(Myfunc *);    //dopath是这样一类函数，函数名为dopath，函数参数为Myfunc *，返回值为int

static long nlengthless4096, nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;
//定义全局变量，用于存储文件的各种属性

static long filesize, filefindcount;
static char *filebuf, *comparebuf, *inputpath, *inputfilepath, *inputfilename;
static char *getRealDir(const char *, char *);         /* 获取目录的绝对路径 */
static int getFileNamePos(const char *);          /* 获得路径中，文件名开始的位置 */
 
int
main(int argc, char *argv[])
{
    int ret;
    struct stat statbuf;  //存储文件状态
 
    if (!(argc == 2 || (argc == 4 && strcmp(argv[2], "-comp") == 0) || (argc >= 4 && strcmp(argv[2], "-name") == 0)))
        err_quit("usage:  myfind <pathname> [-comp <filename> | -name <str>…]");
    //输入参数不符合要求，报错
   
    if (lstat(argv[1], &statbuf) < 0) {
        err_quit("lstat error: %s\n", argv[1]);
    }
	//lstat函数用于获取文件的状态信息，存储在statbuf中，注意lstat不会跟踪链接符号
	//如果获取失败，报错

    if (!S_ISDIR(statbuf.st_mode)) //如果不是目录
        strcpy(argv[1], ".");   //第一个参数是要遍历的最初目录，但这里不是目录
 
    if (argc == 2) {   //实现常规功能并且统计长度不大于4096的文件
        ret = myftw(argv[1], myfuncCompareLength);  /* does it all */
 
        ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
        if (ntot == 0)
            ntot = 1;       /* avoid divide by 0; print 0 for all counts */
        printf("regular files   = %7ld, %5.2f %%\n", nreg,
            nreg*100.0/ntot);
        if (nreg == 0)
            nreg = 1;       /* nreg 也可能为 0, 后面不会再用到nreg，可以更改 */
        printf("(less than 4096 = %7ld, %5.2f %%)\n", n4096,
            n4096*100.0/nreg);
        printf("directories     = %7ld, %5.2f %%\n", ndir,
            ndir*100.0/ntot);
        printf("block special   = %7ld, %5.2f %%\n", nblk,
            nblk*100.0/ntot);
        printf("char special    = %7ld, %5.2f %%\n", nchr,
            nchr*100.0/ntot);
        printf("FIFOs           = %7ld, %5.2f %%\n", nfifo,
            nfifo*100.0/ntot);
        printf("symbolic links  = %7ld, %5.2f %%\n", nslink,
            nslink*100.0/ntot);
        printf("sockets         = %7ld, %5.2f %%\n", nsock,
            nsock*100.0/ntot);
    }
 
    /* 找出所有与指定文件有 相同内容 的文件 */
    if ( argc == 4 && strcmp(argv[2], "-comp") == 0 ) {
        /* 输入判断 */
        if (lstat(argv[3], &statbuf) < 0)
            err_quit("lstat error: %s\n", argv[3]);
        if (!S_ISREG(statbuf.st_mode))
            err_quit("that is not a regular file: %s\n", argv[3]);
 
        /* 读入文件内容 */
        int fd;
        filesize = statbuf.st_size;
 
        if ((fd = open(argv[3], O_RDONLY, FILE_MODE)) == -1)
            err_sys("can't open the file '%s'\n", argv[3]);
        if ((filebuf = (char*)malloc(sizeof(char) * filesize)) == NULL ||
            (comparebuf = (char*)malloc(sizeof(char) * filesize)) == NULL)
            err_sys("malloc error\n");
        if (read(fd, filebuf, filesize) != filesize) {
            err_sys("read error '%s'\n", argv[3]);
        }
        close(fd);
 
        /* 将起始目录转化为绝对路径 */
        /* 这样后续的遍历路径就都是绝对路径了 */
        int len;
        inputpath = path_alloc(&len);  
		//path_alloc函数是apue自带的一个函数，申请256B的内存，len返回申请内存的大小，inputpath返回申请内存的首地址
        //path_alloc返回的是一个char类型的指针
		getRealDir(argv[1], inputpath); 
       
        /* 额外的完善实现：在搜索结果中过滤掉作为比较的文件 */
        /* 既然是作为比较的文件，自身相等这是肯定的，就不该出现在结果中 */
        /* 个人理解，觉得不必要可自行删掉 inputfilepath 相关部分 */
 
        /* 首先记录 指定文件 的绝对路径，方便后边进行过滤 */
        char *inputfiledir;
        inputfiledir = path_alloc(&len);
 
        int pos;
        pos = getFileNamePos(argv[3]);
        if (pos == 0) {   /* 没有路径信息，表明是当前路径 */
            strcpy(inputfiledir, ".");
        } else {
            strncpy(inputfiledir, argv[3], pos);
        }
 
        inputfilepath = path_alloc(&len);
        getRealDir(inputfiledir, inputfilepath);
 
        /* 先获取 指定文件 所在目录的绝对路径，再加上 文件名 构成文件的绝对路径 */
        strcat(inputfilepath, argv[3]+pos);    /* argv[3]+pos 是文件名的起始处 */
 
        /* 开始查找 */
        printf("\nSame content as '%s':\n", argv[3]);
        ret = myftw(inputpath, myfuncCompareContent);
        if (filefindcount == 0) printf("Can't find any match file.\n");
        printf("\n");
    }
 
    /* 找出 指定文件名 的所有文件 */
    if ( argc >= 4 && strcmp(argv[2], "-name") == 0 ) {
        /* 将搜索目录转化为绝对路径，简化实现 */
        int len, i;
        int pos;
        inputpath = path_alloc(&len);
        inputfilename = path_alloc(&len);
        getRealDir(argv[1], inputpath);
 
        printf("\n");
        for (i = 3; i < argc; i++) {    /* 注意输入的文件名可以有多个 */
            pos = getFileNamePos(argv[i]);
            if (pos != 0)       /* 包含路径 */
                err_quit("only file name: %s", argv[i]);
 
            strncpy(inputfilename, argv[i], len);
            filefindcount = 0;
            printf("%d. Same name as '%s':\n", i-2, argv[i]);
            ret = myftw(inputpath, myfuncCompareName);
            if (filefindcount == 0) printf("Can't find any match file.\n");
            printf("\n");
        }
    }
 
    exit(ret);
}
 
//遍历目录树
#define FTW_F   1       /* file文件 */
#define FTW_D   2       /* 目录 */
#define FTW_DNR 3       /* 不能读的目录 */
#define FTW_NS  4       /* 不能查看状态的file文件 */
 
static char *fullpath;          
 
static int                  /* we return whatever func() returns */
myftw(char *pathname, Myfunc *func)
{
    int len;
    fullpath = path_alloc(&len);    /* malloc's for PATH_MAX+1 bytes */
                            /* ({Prog pathalloc}) */
    strncpy(fullpath, pathname, len);       /* protect against */
    fullpath[len-1] = 0;                /* buffer overrun */
 
    return(dopath(func));
}
 
/*
 * Descend through the hierarchy, starting at "fullpath".
 * If "fullpath" is anything other than a directory, we lstat() it,
 * call func(), and return.  For a directory, we call ourself
 * recursively for each name in the directory.
 */
static int                  /* we return whatever func() returns */
dopath(Myfunc* func)
{
    struct stat     statbuf;
    struct dirent   *dirp;
    DIR             *dp;
    int             ret;
    char            *ptr;
 
    if (lstat(fullpath, &statbuf) < 0)  /* stat error */
        return(func(fullpath, &statbuf, FTW_NS));
    if (S_ISDIR(statbuf.st_mode) == 0)  /* not a directory */
        return(func(fullpath, &statbuf, FTW_F));
 
    /*
     * It's a directory.  First call func() for the directory,
     * then process each filename in the directory.
     */
    if ((ret = func(fullpath, &statbuf, FTW_D)) != 0)
        return(ret);
 
    ptr = fullpath + strlen(fullpath);  /* point to end of fullpath */
    if (*(ptr-1) != '/') {  /* 只有当末尾不是 '/' 时，才需要加，否则会出现 '//' */
        *ptr++ = '/'; /* 保证是目录的路径以 '/' 结尾 */
        *ptr = 0;
    }
 
    if ((dp = opendir(fullpath)) == NULL)   /* can't read directory */
        return(func(fullpath, &statbuf, FTW_DNR));
 
    while ((dirp = readdir(dp)) != NULL) {
        if (strcmp(dirp->d_name, ".") == 0  ||
            strcmp(dirp->d_name, "..") == 0)
                continue;       /* ignore dot and dot-dot */
 
        strcpy(ptr, dirp->d_name);  /* append name after slash */
 
        if ((ret = dopath(func)) != 0)      /* recursive */
            break;  /* time to leave */
    }
 
    //ptr[-1] = 0;  /* erase everything from slash onwards */
 
    if (closedir(dp) < 0)
        err_ret("can't close directory %s", fullpath);
 
    return(ret);
}
 
/* 获取绝对路径，且保证目录的绝对路径以斜杠结尾 */
static char* 
getRealDir(const char *pathname, char *realpath) {
    int len;
    char *dirpath, *ptr;
 
    dirpath = path_alloc(&len);     /* 记录原来的目录 */
    if (getcwd(dirpath, len) == NULL)
        err_sys("getcwd fail\n");
 
    if (chdir(pathname) < 0)
        err_sys("can't chdir: %s\n", pathname);
    if (getcwd(realpath, len) == NULL)  /* 记录指定目录的绝对路径 */
        err_sys("getcwd fail\n");
 
    ptr = realpath + strlen(realpath);
    if (*(ptr-1) != '/') {      /* 保证目录的绝对路径以斜杠结尾 */
        *ptr++ = '/';
        *ptr = 0;
    }
 
    if (chdir(dirpath) < 0)     /* 还原状态，回到原来的目录 */
        err_sys("can't chdir: %s\n", pathname);
 
    return realpath;
}
 
/* 分离目录和文件名，返回 文件名开始 的位置，在此之前为目录，之后为文件名 */
/* 即返回最后一个 '/' (有可能没有) 的下一位置，即为文件名开始的位置 */
static int 
getFileNamePos(const char *pathname) {
    int i, pos = 0;
    for (i = strlen(pathname)-1; i >= 0; i-- ) {
        if (pathname[i] == '/') {
            pos = i;
            break;
        }
    }
    /* 有可能不包含 '/' */
    return (pos == 0) ? pos : pos + 1;
}
 
/* 遍历目录，并记录文件长度 不大于4096字节 的常规文件的百分比 */
static int
myfuncExtra(const char *pathname, const struct stat *statptr, int type)
{
    switch (type) {
    case FTW_F:
        switch (statptr->st_mode & S_IFMT) {
        case S_IFREG:
            nreg++;
            if (statptr->st_size <= 4096) n4096++;
            break;
        case S_IFBLK:   nblk++;     break;
        case S_IFCHR:   nchr++;     break;
        case S_IFIFO:   nfifo++;    break;
        case S_IFLNK:   nslink++;   break;
        case S_IFSOCK:  nsock++;    break;
        /* 题目要求不输出无关路径，所以下面的提示信息都可以删掉，我选择注释掉 */
        case S_IFDIR: ; /* 如果注释，注意这边得有一个分号 */
            // err_dump("for S_IFDIR for %s", pathname);
                    /* directories should have type = FTW_D */
        }
        break;
 
    case FTW_D:
        ndir++;
        break;
 
    case FTW_DNR:
        // err_ret("can't read directory %s", pathname);
        break;
 
    case FTW_NS:
        // err_ret("stat error for %s", pathname);
        break;
 
    default: ;
        // err_dump("unknown type %d for pathname %s", type, pathname);
    }
 
    return(0);
}
 
 
/* 找出所有与指定文件有 相同内容 的文件 */
static int
myfuncCompareContent(const char *pathname, const struct stat *statptr, int type) {
    /* 只有类型和大小都符合的普通文件，才进行内容是否相同的判断 */
    if (type == FTW_F && (statptr->st_mode & S_IFMT) == S_IFREG && statptr->st_size == filesize) {
        int fd;
        if ((fd = open(pathname, O_RDONLY, FILE_MODE)) == -1)
            // err_ret("Can't open file: %s\n", pathname);
            return (0); /* 不输出异常文件，直接返回 */
        if (read(fd, comparebuf, filesize) != filesize)
            err_sys("read error '%s'\n", pathname);
        close(fd);
 
        if (strcmp(filebuf, comparebuf) == 0) {
                /* 过滤掉作为比较的文件，这步可有可无 */
                if (strcmp(inputfilepath, pathname) != 0) {
                    filefindcount++;
                    printf("%s\n", pathname);
                }
        }
    }
 
    return (0);
}
 
/* 找出 指定文件名 的所有文件 */
static int
myfuncCompareName(const char *pathname, const struct stat *statptr, int type) {
    if (type == FTW_F) {
        int pos;
        pos = getFileNamePos(pathname);
 
        if (strcmp(inputfilename, pathname+pos) == 0) {
            filefindcount++;
            printf("%s\n", pathname);
        }
    }
 
    return (0);
}