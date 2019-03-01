/*Name :- Raj Lavingia
Date :- 2/28/19
Assignment 4
Question 1
*/

//Declaring Variables
#include <string.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <malloc.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
int var1 = 0;
char new_string[50];

FILE *ft1; //File pointer declared for opening and closign of file
int set_value = 0;
//Variables declared for time stamps
struct timespec time_for_measurement;
struct timeval time_for_measurement_current;

int x,y,z; //pid,ppid
uint16_t count[26], i, temp_count;
char temp2, temo1;

//Structure which is passed in the function
struct string_thread
{
  char *string;
  int numofthreads;
  char *stringlength;
};
struct string_thread *pointer_task; //pointer declared for taking argument and storing
struct string_thread struct_new;
void *function1(void *Para_Passed)
{
  long int c1 = syscall(SYS_gettid);
  long int c2 = pthread_self();
	static FILE *ft1 = 0;
	static FILE *ft12;
  if(ft12<0)
  {
    printf("\nNot open file\n");
  }
	ft12 = fopen(((struct string_thread *)Para_Passed)->string, "a");
	gettimeofday(&time_for_measurement_current, NULL);
	fprintf(ft12, "\n thread 1 starting time is %lu.%lu \n", time_for_measurement_current.tv_sec, time_for_measurement_current.tv_usec);
	fprintf(ft12, "Linux ID : %lu Posix ID : %lu",c1,c2);
  ft1 = fopen("gdb.txt","r");
  int a;
  for(i = 0x61, a = 0; a < 26; i ++, a ++) count[a] = (i);
  while(1)
  	{
  		temp2 = fgetc(ft1);
  		if(feof(ft1))	break;
  		for(i = 0; i < 26; i ++)
  		{
  			temo1 = count[i] & 0x00FF;
  			if((temp2 == temo1) || (temp2 == (temo1 - 32)))
  			{
  				if(((count[i] & 0xFF00)>>8) < 0xFF)	count[i] += (1<<8);
  			}
  		}
  	}

  	for(i = 0; i < 26; i ++)
  	{
  		temo1 = count[i] & 0x00FF;
  		temp_count = (count[i] & 0xFF00) >> 8;
	        if(temp_count < 100)
	        {
  		    fprintf(ft12, "\nCharacter: %c Count: %d\n", temo1, temp_count);
      		}
  	}

	gettimeofday(&time_for_measurement_current, NULL);
	fprintf(ft12, "\nThread 1 over at time %lu.%lu and process is completed \n", time_for_measurement_current.tv_sec, time_for_measurement_current.tv_usec);
	fclose(ft12);
	fclose(ft1);
	pthread_exit(0);
}

void extra_function_address(int parameter)
{
  static FILE *ft1, *ft12;
  if(parameter == SIGVTALRM)
      {
      //  printf("\n sigvtalrm\n");
        char *cpu_cat_process = "cat /proc/stat | head -n 2";
        FILE *ft12 = popen(cpu_cat_process, "r");
        if(ft12<0)
        {
          printf("\n Error is there\n");
        }
          ft1 = fopen(new_string, "a");
            if(ft1)
          {
            gettimeofday(&time_for_measurement_current, NULL);
            fprintf(ft1, "\nCPU %lu.%lu \n", time_for_measurement_current.tv_sec, time_for_measurement_current.tv_usec);
              while(!feof(ft12))
            {
              char temp_char;
              temp_char = fgetc(ft12);
              fprintf(ft1, "%c", temp_char);
            }
          }
          fclose(ft1);
        }


      else if(parameter == SIGUSR1 || parameter == SIGUSR2)
      {
        if(parameter == SIGUSR1)
        {
          printf("\n Killed by USer1\n");
        }
        else
        {
          printf("\n Killed by USer2\n");
        }

        printf("\n inside user kill function by user 1 or 2\n");
        ft12 = fopen(new_string, "a");
        if(ft12<0)
        {
          printf("\n Error is there\n");
        }
        else
        {
	  if(parameter == SIGUSR1)
        {
          fprintf(ft12,"\n Killed by USer1\n");
        }
        else
        {
          fprintf(ft12,"\n Killed by USer2\n");
        }
          printf("\nFile is opened\n");
          gettimeofday(&time_for_measurement_current, NULL);
          fprintf(ft12, "\n Thread 2 is over at time %lu.%lu\n", time_for_measurement_current.tv_sec, time_for_measurement_current.tv_usec);
          fclose(ft12);
        }
      var1 = 1;
      }
}

void *thread_two(void *Para_Passed)
{
  static FILE *ft1, *ft12;
  struct sigaction sig_action_raj;
  struct itimerval sig_action_raj_timer;
  long int d = syscall(SYS_gettid);
  long int d1 = pthread_self();
	ft1 = fopen(((struct string_thread *)Para_Passed)->string, "a");
	if(ft1<0)
  {
    printf("\nFile pointer not passed successfully\n");
  }
	printf("\nThread2 id %ld", d);
	gettimeofday(&time_for_measurement_current, NULL);
	fprintf(ft1, "\nThread2 Started at %lu.%lu\n", time_for_measurement_current.tv_sec, time_for_measurement_current.tv_usec);
	fprintf(ft1, "Linux Thread: %ld,  Posix thread ID: %lu", d, d1);
	fclose(ft1);
	bzero(&sig_action_raj, sizeof (sig_action_raj));
	sig_action_raj.sa_handler = &extra_function_address;
	sig_action_raj_timer.it_interval.tv_sec = 0;
	sig_action_raj_timer.it_interval.tv_usec = 100000;
	sig_action_raj_timer.it_value.tv_sec = 0;
	sig_action_raj_timer.it_value.tv_usec = 100000;
	sigaction (SIGVTALRM, &sig_action_raj, NULL);
	sigaction (SIGUSR1, &sig_action_raj, NULL);
	sigaction (SIGUSR2, &sig_action_raj, NULL);
	setitimer (ITIMER_VIRTUAL, &sig_action_raj_timer, NULL);

while(var1 == 0)
{
  ;
}
pthread_exit(NULL);


}

int main(int argc, char **argv)
{
  //Pthreads declared here
  pthread_t pika1, pika2;
  int x1 = getpid();
  int x2 = getppid();
  pointer_task = (struct string_thread *) malloc (sizeof(struct string_thread));
	if(pointer_task<0)
  {
    printf("\nStructure pointer not passed\n");
  }

  printf("\nelse continue with the following process\n");
  pointer_task->string = argv[1];
  printf("\nFile name which will be made is %s\n",pointer_task->string);
  strcpy(new_string, pointer_task->string);
  //strcpy (struct_new.string, new_string);
  struct_new.string = new_string;
  printf("\nPID:%d PPID: %d\n",x1, x2);
  clock_gettime(CLOCK_REALTIME, &time_for_measurement); //for getting real time clock
	ft1 = fopen(new_string, "w+");
	if(ft1<0)
  {
    printf("\nStructure pointer not passed\n");
  }
  printf("\nelse continue with the following process\n");
  gettimeofday(&time_for_measurement_current, NULL);
	fprintf(ft1, "\nMain Thread Created and the time is  %lu.%lu\n", time_for_measurement_current.tv_sec, time_for_measurement_current.tv_usec);
	fclose(ft1);
  //pthread creation
  pthread_create(&pika1, NULL, function1, (void *)pointer_task);
	pthread_create(&pika2, NULL, thread_two, (void *)pointer_task);
  //Joining p threads
	pthread_join(pika1, NULL);
	pthread_join(pika2, NULL);
  //New string by user is opened again here
	ft1 = fopen(new_string, "a");
	if(ft1<0)
    {
      printf("\nStructure pointer not passed\n");
    }
	gettimeofday(&time_for_measurement_current, NULL);
  fprintf(ft1, "\n Master threading is exited now: %lu.%lu\n", time_for_measurement_current.tv_sec,time_for_measurement_current.tv_usec);
	fclose(ft1);

}
