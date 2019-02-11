#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

FILE* file;
char* newfile = "raj.txt";
char character ='R';

void Q2_printf_file()
{
  printf("Welcome to CU boulder\n");
  file = fopen(newfile,"w");
  fprintf(file,"%c",character);
  fclose(file);
}

void Q2_memory_allocation()
{
  file = fopen(newfile,"a");
  char* memory_size = (char*)malloc(40);
  if(memory_size==NULL)
  {
   fprintf(file,"Memory not allocated\n\r");
  }	 
  printf("Enter a string:");
  scanf("%[^\n]",memory_size);
  fprintf(file,"%s",memory_size);
  fflush(file);
  fclose(file);
 
	file = fopen(newfile,"r");
	char c;
	if(c = fgetc(file))printf("character:%c\n",c);
	fgets(memory_size,40,file);
	puts(memory_size);
	fclose(file);
	free(memory_size);
	memory_size=NULL;
	printf("Freed Memory\n");

}
int main(void)
{
	
	Q2_printf_file();
	Q2_memory_allocation();

	return 0;
}
