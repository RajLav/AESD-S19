#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <stdlib.h>
#include<time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h> //creating p thread
#include<time.h> //Timestamp function
#include<malloc.h> //Space
#include<unistd.h>
#define on_state  0;
#define off_state  1;
#define shared_memory_name 	"my_sm"
#define semaphore_name 		"my_semaphore"
struct timespec t;
FILE *ft1, *fp;
struct timespec t;
int done =0;
char *message_temp = "Sig kill\n";
void term(int signum)
{
    char buffer[30];
    struct timeval tv;
    time_t curtime;
    done = 1;
    printf("%s",message_temp);
    fopen("Q3.txt","a+");
    gettimeofday(&tv, NULL);
    curtime=tv.tv_sec;
    fprintf(fp,"%s%ld\n",buffer,tv.tv_usec);
    fclose(fp);
}

typedef struct
{
	char my_string[20];
	int my_string_length;
	int LED_Control;
	char string[50];
	char string1[40];
	char string2[50];
	char string3[50];
	char string4[50];
	int x ;

}data;
data data_to_sent;


int main()
{
	struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = term;
	sigaction(SIGTERM, &action, NULL);
	printf("Starting the process 2\n");
	int open_semaphore = shm_open(shared_memory_name, O_CREAT | O_RDWR, 0666);
	if(open_semaphore < 0 )
	{
		perror("Error");
		exit(1);
	}

	int sema_size = sizeof(data);

	void *shared_mem = mmap(NULL, sema_size, PROT_READ | PROT_WRITE, MAP_SHARED , open_semaphore, 0);
	if(shared_mem == (void *)-1)
	{
		perror("error");
		exit(1);
	}

	sem_t * sem = sem_open(semaphore_name, O_CREAT, 0666, 0);
	if(sem == NULL)
	{
		perror("error");
		exit(1);
	}

	sem_wait(sem);

				data data_to_received = {0};
        data *my_ptr = &data_to_received;

        memcpy(my_ptr,shared_mem, sizeof(data));

				ft1 = fopen("Q3.txt","a");
        clock_gettime(CLOCK_REALTIME, &t);
        fprintf(ft1,"\nShared Memory IPC and semphores and mutex used\n");
        fprintf(ft1,"\n[Child]New string is : %s\n",my_ptr->string);
        fprintf(ft1,"\n[Child]String Length is : %d\n",my_ptr->my_string_length);
        fprintf(ft1,"\nLed State is : %d\n",my_ptr->LED_Control);
        fprintf(ft1,"\nSecond string is : %s\n",my_ptr->string1);
        fprintf(ft1,"\nThird string is : %s\n",my_ptr->string2);
        fprintf(ft1,"\nFourth string is : %s\n",my_ptr->string3);
        fprintf(ft1,"\nFifth string is : %s\n",my_ptr->string4);
        fprintf(ft1,"\nPID is : %d\n",my_ptr->x);
        fprintf(ft1,"\nPID2 is : %d\n",my_ptr->x);
        fprintf(ft1,"\nPID3: %d\n",my_ptr->x);
        fprintf(ft1,"\n[Value]time stamp reading when parent sends to child: %ld \n", t.tv_nsec);
        fclose(ft1);

				char msg[50] = "\nChild says to Parent\n";
        char msg1[50]="\nSecond String\n";
        char msg2[50]="\nThird String\n";
        char msg3[50]="\nFourth String\n";
        char msg4[50]="\nFifth String\n";

        data data_to_sent ;
				strcpy(data_to_sent.string,msg);
				strcpy(data_to_sent.string1,msg1);
				strcpy(data_to_sent.string2,msg2);
				strcpy(data_to_sent.string3,msg3);
				strcpy(data_to_sent.string4,msg4);
				data_to_sent.my_string_length = strlen(data_to_sent.string);
				data_to_sent.LED_Control = off_state;
			  data*  my_ptr1 = &data_to_sent;
				ft1 = fopen("Q3.txt","a");
        clock_gettime(CLOCK_REALTIME, &t);
        fprintf(ft1,"\nShared Memory IPC and semphores and mutex used\n");

        fprintf(ft1,"\n[Parent]New string is : %s\n",data_to_sent.string);
        fprintf(ft1,"\n[Parent]String Length is : %d\n",data_to_sent.my_string_length);
        fprintf(ft1,"\n[Parent]Led State is : %d\n",data_to_sent.LED_Control);
        fprintf(ft1,"\n[Parent]Second string is : %s\n",data_to_sent.string1);
        fprintf(ft1,"\n[Parent]Third string is : %s\n",data_to_sent.string2);
        fprintf(ft1,"\n[Parent]Fourth string is : %s\n",data_to_sent.string3);
        fprintf(ft1,"\n[Parent]Fifth string is : %s\n",data_to_sent.string4);
        fprintf(ft1,"\n[Parent]PID is : %d\n",data_to_sent.x);
        fprintf(ft1,"\n[Parent]PID2 is : %d\n",data_to_sent.x);
        fprintf(ft1,"\n[Parent]PID3: %d\n",data_to_sent.x);
        fprintf(ft1,"\n[Value]time stamp reading when parent sends to child: %ld \n", t.tv_nsec);
        fclose(ft1);

				memcpy((char*)shared_mem, my_ptr1, sema_size);

    	sem_post(sem);

	close(open_semaphore);
  	sem_unlink(semaphore_name);
	return 0;
}
