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

  #define on_state  1;
  #define off_state  0;

  struct timespec t;
  FILE *ft1,*fp;
	int done =0;
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
  data data_to_be_sent;
	data data_to_be_received;

  char *message_temp = "Sig kill\n";
  void term(int signum)
  {
      char buffer[30];
      struct timeval tv;
      time_t curtime;
      done = 1;
      printf("%s",message_temp);
      fopen("Q5.txt","a+");
      gettimeofday(&tv, NULL);
      curtime=tv.tv_sec;
      fprintf(fp,"%s%ld\n",buffer,tv.tv_usec);
      fprintf(fp,"%s no acquired resources",message_temp);
      fclose(fp);
  }

	void main(int argc, char *argv[])
	{
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);
		int sock;
		struct sockaddr_in server;
		char buff[1024];
		struct hostent *hp;
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if(sock < 0)
		{
			perror("failed");
			exit(1);
		}
		server.sin_family = AF_INET;
		hp = gethostbyname(argv[1]);
		if(hp == 0)
		{
			perror("failed");
			exit(1);
		}
		memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
		server.sin_port = htons(5005);

		if(connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
		{
			perror("failes");
			exit(1);
		}

      char msg[50] = "\nParent says to child\n";
      char msg1[50]="\nSecond String\n";
      char msg2[50]="\nThird String\n";
      char msg3[50]="\nFourth String\n";
      char msg4[50]="\nFifth String\n";
      data_to_be_sent.x = getpid();
      strcpy(data_to_be_sent.string,msg);
      strcpy(data_to_be_sent.string1,msg1);
      strcpy(data_to_be_sent.string2,msg2);
      strcpy(data_to_be_sent.string3,msg3);
      strcpy(data_to_be_sent.string4,msg4);
      data_to_be_sent.my_string_length = strlen(data_to_be_sent.string);
      data_to_be_sent.LED_Control = off_state;
      data *my_ptr = &data_to_be_sent;
      ft1 = fopen("Q5.txt","a");
      clock_gettime(CLOCK_REALTIME, &t);
			fprintf(ft1,"\nSocket used and no resources used\n");
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

		if(send(sock, &data_to_be_sent, sizeof(data), 0) < 0)
		{
			perror("failed");
			exit(1);
		}


		int temp_buffer_receive = read(sock,&data_to_be_received,sizeof(data));
	   if (temp_buffer_receive < 0)
		{
	        	perror("failed");
						exit(1);
		}
    data* my_ptr1 = &data_to_be_received;
    ft1 = fopen("Q5.txt","a");
    clock_gettime(CLOCK_REALTIME, &t);
		fprintf(ft1,"\nSocket used and no resources used\n");
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
		close(sock);
	}
