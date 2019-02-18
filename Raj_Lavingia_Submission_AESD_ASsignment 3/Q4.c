/*Name :- Raj Lavingia
Date :- 02.17.2019
*/

//Libraries defined for modules and macros used in the code
#include <linux/module.h>
#include <linux/kernel.h>	
#include <linux/init.h>		
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/timer.h> //For displaying time in kernel 

MODULE_DESCRIPTION("Animals Kernel Functions");
MODULE_AUTHOR("Raj Lavingia");
MODULE_LICENSE("GPL");

//Declaration of variables for Set1 and Set2
int temp1 = 0,temp2 = 0;
int temp1_node_set1=0,temp2_node_set2=0;

char New_Array[60][100]; //After alphabetical seacrh
char minStr[10];
char temp[20];

int i,existing_animal = 0;
struct node_animal *sorted_node_set1, *node_for_Set1; //comparison of nodes and adding and subtracting them and also incrementing the count
struct node_animal *sorted_node_set2, *node_for_Set2;

//Before alphabetical Seacrh
char Old_Array[60][100]={"Cat", "Dog", "Fish", "Elephant", "Cow", "Lizard", "Monkey","Lion","Tiger","Sheep","Rat","Duck","Pig","Giraffe","Zebra","Duck","Pig","Giraffe","Zebra","Sheep", "Lizard", "Monkey","Lion","Tiger","Sheep",
"Cat", "Dog", "Fish", "Elephant", "Cow","Cat", "Dog", "Fish", "Elephant", "Cow","Duck","Pig","Giraffe","Zebra","Lizard", "Monkey","Lion","Tiger","Sheep", "Monkey","Lion","Tiger","Sheep","Rat","Cat"};

//Structures Defined for set1 and set2
struct node_animal Part1_Set1;
struct node_animal part2_set2;

//Structures defined for Time
struct timespec begining_of_time;
struct timespec end_of_time;

struct node_animal *free_set2;

int count_variable;
module_param(count_variable, int , S_IRUSR | S_IWUSR);
char *search_name = "";
module_param(search_name, charp , S_IRUSR | S_IWUSR);
struct node_animal *temp9;

struct timespec difference_time;

typedef struct node_animal
{
	char nameofanimal[30];
	unsigned int increment;
	struct list_head list; 
};

//Sorting of alphabetical array , Reference:- GeekfoeGeeks.com
void Alpha_Sort(int n)
{
	int i,j;
	for (i = 0; i < 50; i++)
	{
		int min_idx = i;
		strcpy(minStr, Old_Array[i]);
		for (j = i+1; j < 50; j++)
		{
			if (strcmp(minStr, Old_Array[j]) > 0)
			{
				strcpy(minStr, Old_Array[j]);
				min_idx = j;
			}
		}
		if (min_idx != i)
		{
			strcpy(temp,Old_Array[i]); 
			strcpy(Old_Array[i], Old_Array[min_idx]);
			strcpy(Old_Array[min_idx], temp);
		}
	}
	
}

//Printing the sorted alphabetical array
void print_sorted(int k)
{
	int i;
	for(i=0;i<50;i++)
	{
		strcpy(New_Array[i],Old_Array[i]);
		printk(KERN_DEFAULT "New array are : %s\n",New_Array[i]);
	}
}

//search by count function
void search_by_count(int g)
{
	printk("printing count equal user defined :%d\n",count_variable);
	
	list_for_each_entry(temp9, &part2_set2.list, list)
	{
		if(count_variable <= temp9->increment)
		{
			printk(KERN_INFO "Animal name: %s\n", temp9->nameofanimal);
		}
	}
	
}

//search by name function
void search_by_name(int t)
{
	printk("printing string equal user defined : %s\n",search_name);
	list_for_each_entry(temp9, &part2_set2.list, list)
	{
		if(strcmp(temp9->nameofanimal,search_name)==0)
		{
			printk(KERN_INFO "Animal name: %s\n==>Animal Count:%d", temp9->nameofanimal,temp9->increment);
		}
		
	}
	
}
//search by name and count function
void search_by_name_and_count(int j)
{
	printk("printing string equal user defined  %s and Count:%d\n",search_name,count_variable);
	list_for_each_entry(temp9, &part2_set2.list, list)
	{
		if(strcmp(temp9->nameofanimal,search_name)==0 && (count_variable <= temp9->increment))
		{
			printk(KERN_INFO "Animal name: %s\n==>Animal Count:%d", temp9->nameofanimal,temp9->increment);
		}
		
	}
}
void count_node_remove(int t)
{
	int i,existing_animal = 0;
	INIT_LIST_HEAD(&Part1_Set1.list);
	
	for(i=0; i < 50; i++)
	{
		list_for_each_entry(node_for_Set1, &Part1_Set1.list, list)
		{
			if( strcmp(node_for_Set1->nameofanimal, New_Array[i]) == 0 )
			{
				node_for_Set1->increment++; //increment the array numnber if the 2 animals are same , if same then dont add the new node.
				printk(KERN_DEFAULT "Animal which exists %s count: %d \n", node_for_Set1->nameofanimal, node_for_Set1->increment);
				existing_animal = 1;
				printk(KERN_DEFAULT "Inside the loop\n\r");
				break;
			}
		}
		if(existing_animal == 0)
		{
			printk(KERN_DEFAULT "Inside the loop2\n\r");
			
			sorted_node_set1 = kmalloc(sizeof(*sorted_node_set1), GFP_KERNEL); ///memory
			printk(KERN_DEFAULT "Memory size of buffer\n",sorted_node_set1);
			int k1 = sizeof(*sorted_node_set1);//sorted_node_set1;			
			
			temp1=temp1+k1;//memory assigned
			printk("Size occupied by Set1: %d\n",temp1);
			
			temp1_node_set1=temp1_node_set1+1; //nodes displayed
			
			strcpy(sorted_node_set1->nameofanimal, New_Array[i]);//New array copied
			printk(KERN_DEFAULT "Compared String: %s",sorted_node_set1->nameofanimal);
			
			sorted_node_set1->increment = 1;
			
			INIT_LIST_HEAD(&sorted_node_set1->list);
			list_add_tail(&(sorted_node_set1->list), &(Part1_Set1.list));
			
			
		}
		
		existing_animal = 0;	
		
	}
}

void for_part2(int r)
{
	int i,existing_animal = 0;
	INIT_LIST_HEAD(&part2_set2.list);

	for(i=0; i < 50; ++i)
	{
		list_for_each_entry(node_for_Set2, &part2_set2.list, list)
		{
			if( strcmp(node_for_Set2->nameofanimal, New_Array[i]) == 0 )
			{
				node_for_Set2->increment++; //increment the array numnber if the 2 animals are same , if same then dont add the new node.
				printk(KERN_DEFAULT "Animal which exists %s count: %d \n", node_for_Set2->nameofanimal, node_for_Set2->increment);
				existing_animal = 1;
				printk(KERN_DEFAULT "Inside the loop of set2\n\r");
				break;
			}
			
				
		}
		if(existing_animal == 0)
		{
			printk(KERN_DEFAULT "Inside the loop2\n\r");
			
			sorted_node_set2 = kmalloc(sizeof(*sorted_node_set2), GFP_KERNEL); ///memory
			printk(KERN_DEFAULT "Memory size of buffer\n",sorted_node_set2);
			int k2 = sizeof(*sorted_node_set2);//sorted_node_set1;
			
			temp2=temp2+k2;//memory assigned
			printk("Size occupied by Set1: %d\n",temp1);
			
			temp2_node_set2=temp2_node_set2+1; //nodes displayed
			
			strcpy(sorted_node_set2->nameofanimal, New_Array[i]);//New array copied
			printk(KERN_DEFAULT "Compared String: %s",sorted_node_set2->nameofanimal);
			
			sorted_node_set2->increment = 1;
			
			INIT_LIST_HEAD(&sorted_node_set2->list);
			list_add_tail(&(sorted_node_set2->list), &(part2_set2.list));
			
			
		}
		
		existing_animal = 0;
		
			
	}
}



void counter_animals(int h)
{
	//count of each animal in the sorted array and also keep on freeing the memory
	list_for_each_entry(node_for_Set1, &Part1_Set1.list, list)
	{
		printk(KERN_DEFAULT "Name of Animal - %s :Count respective : %d\n", node_for_Set1->nameofanimal,node_for_Set1->increment);
		kfree(node_for_Set1);
	}
	
}

static int __init my_init(void)
{
	//For printing the time in seconds for total insmod
	getnstimeofday (&begining_of_time);

	//Printing the whole array after getting sorted alphabetically
	Alpha_Sort(50);
    print_sorted(2);
	count_node_remove(1);
	printk("Nodes for set1 %d\n",temp1_node_set1);
	counter_animals(1);
	printk("Memory Freed by Set 1 %d\n",temp1);
	for_part2(1);
	//functions called for filtering purposes
	search_by_count(1);
	search_by_name(3);
	search_by_name_and_count(2);
	
	list_for_each_entry(node_for_Set2, &part2_set2.list, list)
	{
		printk(KERN_INFO "%s--%d\n", node_for_Set2->nameofanimal,node_for_Set2->increment);
		kfree(free_set2);
	}
	
	list_for_each_entry(node_for_Set2, &part2_set2.list, list)
	{
		printk(KERN_INFO "Animal name: %s - count: %d\n", node_for_Set2->nameofanimal, node_for_Set2->increment);
	}		

	getnstimeofday (&end_of_time);
	difference_time = timespec_sub(end_of_time, begining_of_time); 
	printk(KERN_ALERT "Time passed %luns\n", difference_time.tv_nsec );
	printk("Size freed after performing fucntions of set2  %d\n",temp2);

	return 0; 

}


static void __exit my_exit(void)
{
	
	getnstimeofday (&begining_of_time);
	getnstimeofday (&end_of_time);
	difference_time = timespec_sub(end_of_time, begining_of_time); 
	printk(KERN_ALERT "Time elapsed: %luns\n", difference_time.tv_nsec );

}

module_init(my_init);
module_exit(my_exit);
