#include<stdio.h>
#include<fcntl.h>
#include<sys/times.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<errno.h>
#include<stdarg.h>

int main(int argc,char* argv[])
{
    //参数检查
    if(argc<2||argc>3){
        printf("argv error: ./timewrite<f1 f2 or ./timewrite f1 sync < f2");
    }    
    if(argc==3 && strcmp(argv[2],"sync")!=0){
        printf("argv[2] error: ./timewrite f1 sync<f2");
    }

    int fd;

    //打开文件
    if(argc==2) //异步打开文件
    {
        if((fd=open(argv[1],O_RDWR|O_CREAT,0777))<0){
            printf("can't open");
            exit(0);
        }
    }else //同步打开文件
        {
             if((fd=open(argv[1],O_RDWR|O_CREAT|O_TRUNC|O_SYNC,0777))<0){
                printf("can't open");
                exit(0);
             }  
        }
   

    //获取文件长度
    long int length;
    if((length = lseek(STDIN_FILENO,0,SEEK_END))<0){
        printf("lseek error");
        exit(0);
    }

    //开辟文件长度大小的缓冲区
    char * buff;
    buff = (char*)malloc(sizeof(char)*length);

    //设置文件偏移量为开头
    if(lseek(STDIN_FILENO,0,SEEK_SET)==-1){
        printf("lseek error");
        exit(0);
    }

    //把文件读入到buff中
    if(read(STDIN_FILENO,buff,length)<0){
        printf("read error");
        exit(0);
    }

    //返回每秒时钟的滴答数
    int ticks = sysconf(_SC_CLK_TCK);
    
    //写文件，并计算效率
    clock_t clockstart,clockend;
    struct tms tmsStart,tmsEnd;
    int buffsize;
    for(buffsize=1024;buffsize<=131072;buffsize *= 2){
 
         printf("\n\nBuffsize:%d\n",buffsize);

         //每次写入前,定位到文件头
        if(lseek(fd,0,SEEK_SET)==-1) printf("lseek error");

        clockstart = times(&tmsStart);

        int count = length/buffsize;  //写入次数
        for(int i=0;i<count;i++){
            if(write(fd,buff+i*buffsize,buffsize)!=buffsize){
                printf("write error");
                exit(0);
            }
        }

        int remain = length - buffsize*count;  //剩余内容
        //写入剩余内容
        if(remain){
            if(write(fd,buff+count*buffsize,remain)!=remain){
                printf("write error");
                exit(0);
            }
            count++;
        }

        clockend = times(&tmsEnd);

        printf("clock used = %d\n",clockend-clockstart);
        printf("tms_utime = %d\n",tmsEnd.tms_utime-tmsStart.tms_utime);
        printf("tms_stime = %d\n",tmsEnd.tms_stime-tmsStart.tms_stime);
        printf("tms_cutime = %d\n",tmsEnd.tms_cutime-tmsStart.tms_cutime);
        printf("tms_cstime = %d\n",tmsEnd.tms_cstime-tmsStart.tms_cstime);
    }
    return 0;
}

