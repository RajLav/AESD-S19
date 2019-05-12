





/*****************************************************************************************
Referenced from: 
1. https://www.theurbanpenguin.com/using-a-simple-c-program-to-explain-the-suid-permission/
2. https://www.includehelp.com/c-programs/system-date-time-linux.aspx
3. https://www.unixmen.com/add-cron-jobs-linux-unix/
*****************************************************************************************/
#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/types.h>
#include <time.h>

#include <stdlib.h>

FILE* fp;
int i=0,j=0,index1=1,n;
int array[256]={0};
int size=256;
int ret_array[256]={0};




int main(void)
{    
    printf("Input Values:\n");
    while(index1<257)
    {
        n = rand() % 600 + 1;
        array[index1-1]=n;
        printf("%d,",array[index1]);
	++index1;

    }
    printf("\n");

    long int status=syscall(398,array,size,ret_array);
    printf("Sorted array:\n");
    for(i=0;i<256;++i)
    {
        printf("%d,",ret_array[i]);
    }
    
    fp = fopen("log.txt","a+");
   int real = getuid();
     int euid = geteuid();
    time_t T= time(NULL);
    struct  tm tm = *localtime(&T);

    fprintf(fp,"UID=: %d/\n", real);
    fprintf(fp,"EFFECTIVE-UID =: %d\n", euid);
    fprintf(fp,"Date: %02d/%02d/%04d\n",tm.tm_mon+1,tm.tm_mday,tm.tm_year+1900);
    fprintf(fp,"Time: %02d:%02d:%02d\n",tm.tm_hour, tm.tm_min, tm.tm_sec);
    fprintf(fp,"Array:\n");
    for(i=0;i<256;++i)
    {
        fprintf(fp,"%d\n",array[i]);
    }
    fprintf(fp,"Sorted Array:\n");
    for(i=0;i<256;++i)
    {
        fprintf(fp,"%d\n",ret_array[i]);
    }
    fclose(fp);
}
