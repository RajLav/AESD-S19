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

#define queue_name 		"/my_queue"
#define queue_size		8

struct timespec t;
FILE *ft1,*fp;
char *message_temp = "Sig kill\n";
int done = 0;


void term(int signum)
{
    char buffer[30];
    struct timeval tv;

    time_t curtime;
    done = 1;
    printf("%s",message_temp);
    fopen("Q4.txt","a+");
    gettimeofday(&tv, NULL);
    curtime=tv.tv_sec;
    fprintf(fp,"%s%ld\n",buffer,tv.tv_usec);
    fprintf(fp,"%sno acquired resources",message_temp);
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
data data_to_receive;
int main()
{
  struct sigaction action;
  memset(&action, 0, sizeof(struct sigaction));
  action.sa_handler = term;
  sigaction(SIGTERM, &action, NULL);
	mqd_t myqueue;

	struct mq_attr myqueue_attr;
	myqueue_attr.mq_maxmsg = queue_size;
	myqueue_attr.mq_msgsize = sizeof(data);

	myqueue = mq_open(queue_name, O_CREAT | O_RDWR, 0666, &myqueue_attr);		//open queue

	if(myqueue == (mqd_t)-1)
	{
		perror("error");
		exit(1);
	}

      char msg[50] = "\nParent says to child\n";
      char msg1[50]="\nSecond String\n";
      char msg2[50]="\nThird String\n";
      char msg3[50]="\nFourth String\n";
      char msg4[50]="\nFifth String\n";
      data_to_sent.x = getpid();
      strcpy(data_to_sent.string,msg);
      strcpy(data_to_sent.string1,msg1);
      strcpy(data_to_sent.string2,msg2);
      strcpy(data_to_sent.string3,msg3);
      strcpy(data_to_sent.string4,msg4);
      data_to_sent.my_string_length = strlen(data_to_sent.string);
      data_to_sent.LED_Control =off_state;
      data *my_ptr = &data_to_sent;
      ft1 = fopen("Q4.txt","a");
      clock_gettime(CLOCK_REALTIME, &t);
    	fprintf(ft1,"\nPosix Queue and no resources used\n");
      fprintf(ft1,"\n[Parent]New string is : %s\n",my_ptr->string);
      fprintf(ft1,"\n[Parent]String Length is : %d\n",my_ptr->my_string_length);
      fprintf(ft1,"\n[Parent]Led State is : %d\n",my_ptr->LED_Control);
      fprintf(ft1,"\n[Parent]Second string is : %s\n",my_ptr->string1);
      fprintf(ft1,"\n[Parent]Third string is : %s\n",my_ptr->string2);
      fprintf(ft1,"\n[Parent]Fourth string is : %s\n",my_ptr->string3);
      fprintf(ft1,"\n[Parent]Fifth string is : %s\n",my_ptr->string4);
      fprintf(ft1,"\n[Parent]PID is : %d\n",my_ptr->x);
      fprintf(ft1,"\n[Parent]PID2 is : %d\n",my_ptr->x);
      fprintf(ft1,"\n[Parent]PID3: %d\n",my_ptr->x);
      fprintf(ft1,"\n[Value]time stamp reading when parent sends to child: %ld \n", t.tv_nsec);
      fclose(ft1);


	int ret = mq_send(myqueue,&data_to_sent, sizeof(data_to_sent),0);
	if(ret == -1)
	{
		perror("error");
		exit(1);
	}
	ret = mq_receive(myqueue, &data_to_receive, sizeof(data_to_receive), 0);
	if(ret == -1)
	{
		perror(" error");
		exit(1);
	}
  data* my_ptr1 = &data_to_receive;
  ft1 = fopen("Q4.txt","a");
  clock_gettime(CLOCK_REALTIME, &t);

	fprintf(ft1,"\nPosix Queue and no resources used\n");
  fprintf(ft1,"\n[Child]New string is : %s\n",my_ptr1->string);
  fprintf(ft1,"\n[Child]String Length is : %d\n",my_ptr1->my_string_length);
  fprintf(ft1,"\nLed State is : %d\n",my_ptr1->LED_Control);
  fprintf(ft1,"\nSecond string is : %s\n",my_ptr1->string1);
  fprintf(ft1,"\nThird string is : %s\n",my_ptr1->string2);
  fprintf(ft1,"\nFourth string is : %s\n",my_ptr1->string3);
  fprintf(ft1,"\nFifth string is : %s\n",my_ptr1->string4);
  fprintf(ft1,"\nPID is : %d\n",my_ptr1->x);
  fprintf(ft1,"\nPID2 is : %d\n",my_ptr1->x);
  fprintf(ft1,"\nPID3: %d\n",my_ptr1->x);
  fprintf(ft1,"\n[Value]time stamp reading when parent sends to child: %ld \n", t.tv_nsec);
  fclose(ft1);
	mq_close(myqueue);
	mq_unlink(queue_name);
	return 0;
}
