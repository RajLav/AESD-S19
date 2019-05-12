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

//Declaring File Pointer
FILE *ft1,*fp;

//parent and child declarations
int from_p_to_c[10];
int from_c_to_p[10];

//Declaring structure for time (gettimeofday)
struct timespec t;
int flag = 0;
int done = 0 ;
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
    fprintf(fp,"%sThere were no acquired resources",message_temp);
    fclose(fp);
}
typedef struct
{
    char string[50];
    char string1[40];
    char string2[50];
    char string3[50];
    char string4[50];
    int string_length, status_Led;
    int x ;

}pipe_struct;
struct pipe_struct *pipe_led;
pipe_struct raj_pipe_struct2;
pipe_struct raj_pipe_struct5;
pipe_struct *raj_pipe_struct3;
pipe_struct *raj_pipe_struct6;

int main()
{
  struct sigaction action;
  memset(&action, 0, sizeof(struct sigaction));
  action.sa_handler = term;
  sigaction(SIGTERM, &action, NULL);
  pid_t fork_process_used;
    // Check the error conditions if both parent and child have less than 0 state
    if (pipe(from_p_to_c)<0 || pipe(from_c_to_p)<0 )
    {
        printf("\nError is there\n");
        return 1;
    }

    fork_process_used = fork();
    if (fork_process_used < 0)
    {
        printf("\nError is there\n");
        return 1;
    }

    else if (fork_process_used > 0)
    {

      raj_pipe_struct2.x = getpid();
      raj_pipe_struct5.x = getpid();
      char msg[50] = "\nParent says to child\n";
      char msg1[50]="\nSecond String\n";
      char msg2[50]="\nThird String\n";
      char msg3[50]="\nFourth String\n";
      char msg4[50]="\nFifth String\n";
        strcpy(raj_pipe_struct2.string,msg);
       strcpy(raj_pipe_struct2.string1,msg1);
       strcpy(raj_pipe_struct2.string2,msg2);
       strcpy(raj_pipe_struct2.string3,msg3);
       strcpy(raj_pipe_struct2.string4,msg4);
       raj_pipe_struct2.string_length = strlen(raj_pipe_struct2.string);
       raj_pipe_struct2.status_Led = on_state;
       write(from_p_to_c[1], &raj_pipe_struct2, sizeof(raj_pipe_struct2));
        ft1 = fopen("Q2.txt","a");
        clock_gettime(CLOCK_REALTIME, &t);
        fprintf(ft1, "\nPipes IPC Method and No Resources being used\n");
        fprintf(ft1,"\n[Parent]New string is : %s\n",raj_pipe_struct2.string);
        fprintf(ft1,"\n[Parent]String Length is : %d\n",raj_pipe_struct2.string_length);
        fprintf(ft1,"\n[Parent]Led State is : %d\n",raj_pipe_struct2.status_Led);
        fprintf(ft1,"\n[Parent]Second string is : %s\n",raj_pipe_struct2.string1);
        fprintf(ft1,"\n[Parent]Third string is : %s\n",raj_pipe_struct2.string2);
        fprintf(ft1,"\n[Parent]Fourth string is : %s\n",raj_pipe_struct2.string3);
        fprintf(ft1,"\n[Parent]Fifth string is : %s\n",raj_pipe_struct2.string4);
        fprintf(ft1,"\n[Parent]PID is : %d\n",raj_pipe_struct2.x);
        fprintf(ft1,"\n[Parent]PID2 is : %d\n",raj_pipe_struct2.x);
        fprintf(ft1,"\n[Parent]PID3: %d\n",raj_pipe_struct2.x);
        fprintf(ft1,"\n[Value]time stamp reading when parent sends to child: %ld \n", t.tv_nsec);
        fclose(ft1);
        wait(NULL);

 	    /************************************************************* */
      /* Part1 completed */
      /************************************************************** */

        char my_buffer[sizeof(pipe_struct)];
        read(from_c_to_p[0], my_buffer, sizeof(pipe_struct));
        raj_pipe_struct6 = (pipe_struct*)my_buffer;
        ft1 = fopen("Q2.txt","a");
        clock_gettime(CLOCK_REALTIME, &t);
        fprintf(ft1,"\n[Parent]New string is : %s\n",raj_pipe_struct6->string);
        fprintf(ft1,"\n[Parent]String Length is : %d\n",raj_pipe_struct6->string_length);
        fprintf(ft1,"\n[Parent]Led State is : %d\n",raj_pipe_struct6->status_Led);
        fprintf(ft1,"\n[Parent]Second string is : %s\n",raj_pipe_struct6->string1);
        fprintf(ft1,"\n[Parent]Third string is : %s\n",raj_pipe_struct6->string2);
        fprintf(ft1,"\n[Parent]Fourth string is : %s\n",raj_pipe_struct6->string3);
        fprintf(ft1,"\n[Parent]Fifth string is : %s\n",raj_pipe_struct6->string4);
        fprintf(ft1,"\n[Parent]PID is : %d\n",raj_pipe_struct6->x);
        fprintf(ft1,"\n[Parent]TID is : %d\n",raj_pipe_struct6->x);
        fprintf(ft1,"\n[Parent]Pthread_self: %d\n",raj_pipe_struct6->x);
        fprintf(ft1,"\n[Value]time stamp reading when parent sends to child: %ld \n", t.tv_nsec);
        fclose(ft1);



         	    /************************************************************* */
              /* Part2 completed */
              /************************************************************** */
    }
    else
    {
        char my_buffer[sizeof(pipe_struct)];
        pipe_struct *raj_pipe_struct3;
        read(from_p_to_c[0], my_buffer, sizeof(pipe_struct));
        raj_pipe_struct3 = (pipe_struct*)my_buffer;
        ft1 = fopen("Q2.txt","a");
        clock_gettime(CLOCK_REALTIME, &t);
        fprintf(ft1,"\n[Child]New string is : %s\n",raj_pipe_struct3->string);
        fprintf(ft1,"\n[Child]String Length is : %d\n",raj_pipe_struct3->string_length);
        fprintf(ft1,"\n[Child]Led State is : %d\n",raj_pipe_struct3->status_Led);
        fprintf(ft1,"\n[Child]Second string is : %s\n",raj_pipe_struct3->string1);
        fprintf(ft1,"\n[Child]Third string is : %s\n",raj_pipe_struct3->string2);
        fprintf(ft1,"\n[Child]Fourth string is : %s\n",raj_pipe_struct3->string3);
        fprintf(ft1,"\n[Child]Fifth string is : %s\n",raj_pipe_struct3->string4);
        fprintf(ft1,"\n[Child]PID is : %d\n",raj_pipe_struct3->x);
        fprintf(ft1,"\n[Child]PID2 is : %d\n",raj_pipe_struct3->x);
        fprintf(ft1,"\n[Child]PID3: %d\n",raj_pipe_struct3->x);
        fprintf(ft1,"\n[Child]time stamp reading when parent sends to child: %ld \n", t.tv_nsec);
        fclose(ft1);

        /************************************************************* */
        /* Part1 completed */
        /************************************************************** */


        char msg[] = "Message from Child";
        char msg1[50]="\nSecond String\n";
        char msg2[50]="\nThird String\n";
        char msg3[50]="\nFourth String\n";
        char msg4[50]="\nFifth String\n";

        strcpy(raj_pipe_struct5.string,msg);
        strcpy(raj_pipe_struct5.string1,msg1);
        strcpy(raj_pipe_struct5.string2,msg2);
        strcpy(raj_pipe_struct5.string3,msg3);
        strcpy(raj_pipe_struct5.string4,msg4);
        strcpy(raj_pipe_struct5.string,msg);
        raj_pipe_struct5.string_length = strlen(raj_pipe_struct5.string);
        raj_pipe_struct5.status_Led = off_state;
        raj_pipe_struct5.x = getpid();
        write(from_c_to_p[1], &raj_pipe_struct5, sizeof(raj_pipe_struct5));

        ft1 = fopen("Q2.txt","a");
        clock_gettime(CLOCK_REALTIME, &t);
        fprintf(ft1, "\nPipes IPC Method and No Resources being used\n");
        fprintf(ft1,"\n[Child]New string is : %s\n",raj_pipe_struct5.string);
        fprintf(ft1,"\n[Child]String Length is : %d\n",raj_pipe_struct5.string_length);
        fprintf(ft1,"\n[Child]Led State is : %d\n",raj_pipe_struct5.status_Led);
        fprintf(ft1,"\n[Child]Second string is : %s\n",raj_pipe_struct5.string1);
        fprintf(ft1,"\n[Child]Third string is : %s\n",raj_pipe_struct5.string2);
        fprintf(ft1,"\n[Child]Fourth string is : %s\n",raj_pipe_struct5.string3);
        fprintf(ft1,"\n[Child]Fifth string is : %s\n",raj_pipe_struct5.string4);
        fprintf(ft1,"\n[Child]PID is : %d\n",raj_pipe_struct5.x);
        fprintf(ft1,"\n[Child]PID2 is : %d\n",raj_pipe_struct5.x);
        fprintf(ft1,"\n[Child]PID3: %d\n",raj_pipe_struct5.x);
        fprintf(ft1,"\n[Child]time stamp reading when parent sends to child: %ld \n", t.tv_nsec);
        fclose(ft1);
 	      flag = 1;
        exit(0);

        /************************************************************* */
        /* Part2 completed */
        /************************************************************** */
    }
}
