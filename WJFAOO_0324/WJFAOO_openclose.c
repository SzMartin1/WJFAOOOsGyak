#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <locale.h>


int main()
{
    int fd,ret;
    char buf[32];
    buf[0]=0;

    //O-RDONLY  -  O_RDWR - O_WRONLY --- ezekbõl valamelyik ötelezõ
    //O_APPEND  - minden WRITE után a végére pozícionál
    //O_CREAT   - Létrehozás
    //O_TRUNC

    fd=open("WJFAOO.txt",O_RDWR);

    if(fd==-1)
    {
        perror("open() hiba!");
        exit(-1);
    }
    ret=read(fd,buf,32); //ret: mennyit sikerult olvasni
    printf("read() olvasott %d byteot, ami a következõ:%s\n",ret,buf);

    ret=lseek(fd,0,SEEK_SET);//SEEK_CUR, SEEK_END - ret : hova állt be ténylegesen
    printf("lseek() mondja : %d\n",ret);

    ret=write(fd,buf,6); // ret: mennyit ír ki valójában

    printf("write() mondja : %d\n",ret);

    close(fd);
    return 0;
}
