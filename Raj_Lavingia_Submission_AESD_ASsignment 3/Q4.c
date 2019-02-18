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
int size_count_s1;

//Before alphabetical Seacrh
char Old_Array[60][100]={"Cat", "Dog", "Fish", "Elephant", "Cow", "Lizard", "Monkey","Lion","Tiger","Sheep","Rat","Duck","Pig","Giraffe","Zebra","Duck","Pig","Giraffe","Zebra","Sheep", "Lizard", "Monkey","Lion","Tiger","Sheep",
"Cat", "Dog", "Fish", "Elephant", "Cow","Cat", "Dog", "Fish", "Elephant", "Cow","Duck","Pig","Giraffe","Zebra","Lizard", "Monkey","Lion","Tiger","Sheep", "Monkey","Lion","Tiger","Sheep","Rat","Cat"};

//Structures Defined for set1 and set2
struct node_animal Part1_Set1;
struct node_animal Part2_Set2;

//Structures defined for Time
struct timespec begining_of_time;
struct timespec end_of_time;

struct node_animal *free_set2;
int size_count_s2,number_of_nodes_s2;

//Parameters that has to be asked from the user
int count_variable,filter;
module_param(count_variable, int , S_IRUSR | S_IWUSR);
module_param(filter, int , S_IRUSR | S_IWUSR);
char *search_name = "";
module_param(search_name, charp , S_IRUSR | S_IWUSR);
struct node_animal *tempo,*NewNode;

struct timespec difference_time;
//Animal Structure
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
	list_for_each_entry(tempo, &Part1_Set1.list, list)
	{
		if(tempo->increment >= count_variable)
			{
				NewNode = kmalloc(sizeof(*NewNode), GFP_KERNEL);
				printk(KERN_DEFAULT "Newnode %d",NewNode);
				size_count_s2 =size_count_s2+ sizeof(*NewNode);
				number_of_nodes_s2=number_of_nodes_s2+1;
				printk(KERN_DEFAULT "Set 2 %d",number_of_nodes_s2);
				strcpy(NewNode->nameofanimal , tempo->nameofanimal);
				NewNode->increment = tempo->increment;
				INIT_LIST_HEAD(&NewNode->list);
				list_add_tail(&(NewNode->list), &(Part2_Set2.list));
				printk("name of node is: %s\n", tempo->nameofanimal);
			}
	}
		printk("Sizecount_s2:%d, Number of Nodes: %d",size_count_s2,number_of_nodes_s2);
}

void search_by_name(int t)
{
	printk("printing string equal user defined : %s\n",search_name);
	list_for_each_entry(tempo, &Part1_Set1.list, list)
	{
	if(strcmp(tempo->nameofanimal,search_name)==0)
			{
				NewNode = kmalloc(sizeof(*NewNode), GFP_KERNEL);
				printk(KERN_DEFAULT "Newnode %d",NewNode);
				size_count_s2 =size_count_s2+ sizeof(*NewNode);
				number_of_nodes_s2=number_of_nodes_s2+1;
				printk(KERN_DEFAULT "Set 2 %d",number_of_nodes_s2);
				strcpy(NewNode->nameofanimal , tempo->nameofanimal);
				NewNode->increment = tempo->increment;
				INIT_LIST_HEAD(&NewNode->list);
				list_add_tail(&(NewNode->list), &(Part2_Set2.list));
				printk("Name of node is %s and its Count:%d\n", tempo->nameofanimal,tempo->increment);
			}

	}
	printk("Sizecount_s2:%d, Number of Nodes: %d",size_count_s2,number_of_nodes_s2);

}
//search by name and count function
void search_by_name_and_count(int j)
{
	printk("printing string equal user defined %s and Count:%d\n",search_name,count_variable);
	list_for_each_entry(tempo, &Part1_Set1.list, list)
	{
		if(strcmp(tempo->nameofanimal,search_name)==0 && (tempo->increment >= count_variable))
			{
				NewNode = kmalloc(sizeof(*NewNode), GFP_KERNEL);
				printk(KERN_DEFAULT "Newnode %d",NewNode);
				size_count_s2 =size_count_s2+ sizeof(*NewNode);
				number_of_nodes_s2=number_of_nodes_s2+1;
        printk(KERN_DEFAULT "Set 2 %d",number_of_nodes_s2);
				strcpy(NewNode->nameofanimal , tempo->nameofanimal);
				NewNode->increment = tempo->increment;
				INIT_LIST_HEAD(&NewNode->list);
				list_add_tail(&(NewNode->list), &(Part2_Set2.list));
				printk("Name of node is %s and its Count:%d\n", tempo->nameofanimal,tempo->increment);
			}

	}
	printk("Sizecount_s2:%d, Number of Nodes: %d",size_count_s2,number_of_nodes_s2);

}

void Make_List2(int i)
{
	list_for_each_entry(tempo, &Part1_Set1.list, list)
	{
				NewNode = kmalloc(sizeof(*NewNode), GFP_KERNEL);
				printk(KERN_DEFAULT "Newnode %d",NewNode);
				size_count_s2 =size_count_s2+ sizeof(*NewNode);
				number_of_nodes_s2=number_of_nodes_s2+1;
				printk(KERN_DEFAULT "Set 2 %d",number_of_nodes_s2);
				strcpy(NewNode->nameofanimal , tempo->nameofanimal);
				NewNode->increment = tempo->increment;
				INIT_LIST_HEAD(&NewNode->list);
				list_add_tail(&(NewNode->list), &(Part2_Set2.list));
				printk("Node name:%s Node count:%d\n", tempo->nameofanimal,tempo->increment);
	}
	printk("Sizecount_s2:%d, Number of Nodes: %d",size_count_s2,number_of_nodes_s2);

}

void Make_List1(int t)
{
	int i,existing_animal = 0;
	INIT_LIST_HEAD(&Part1_Set1.list);
//check for full array
	for(i=0; i < 50; i++)
	{
	list_for_each_entry(node_for_Set1, &Part1_Set1.list, list)
	{
		//compare if animal is equal or not if yes move to next one
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

void counter_animals(int h)
{
	//count of each animal in the sorted array and also keep on freeing the memory
	list_for_each_entry(node_for_Set1, &Part1_Set1.list, list)
	{
	printk(KERN_DEFAULT "Name of Animal - %s :Count respective : %d\n", node_for_Set1->nameofanimal,node_for_Set1->increment);
	}

}

static int __init my_init(void)
{
	//int filter;
	//For printing the time in seconds for total insmod
	getnstimeofday (&begining_of_time);

	//Printing the whole array after getting sorted alphabetically
	Alpha_Sort(50);
 	print_sorted(2);
	Make_List1(1);
	printk("Nodes for set1 %d\n",temp1_node_set1);
	counter_animals(1);

	INIT_LIST_HEAD(&Part2_Set2.list);//for_part2(1);

	printk(KERN_DEFAULT "Filter value is 1-Count, 2-Name 3-Both");
	printk(KERN_DEFAULT "Filter value is %d",filter);

	if(filter==1 && count_variable!=0 && strcmp(search_name,"")==0)
	{
		printk(KERN_DEFAULT "Inside the loop of filter 1");
		search_by_count(0);
	}
	else if (filter == 2 && count_variable==0 && strcmp(search_name,"")!=0 )
	{
		printk(KERN_DEFAULT "Inside the loop of filter 2");
		search_by_name(0);
	}
	else if (filter ==3 && count_variable!=0 && strcmp(search_name,"")!=0)
	{
		printk(KERN_DEFAULT "Inside the loop of filter 3");
		search_by_name_and_count(0);
	}
	else
	{
		printk(KERN_DEFAULT "By default State when no para given");
		Make_List2(0);
	}
	list_for_each_entry(node_for_Set2, &Part1_Set1.list, list)
	{
		kfree(node_for_Set2);
	}

	printk("Size freed after performing functions of set1 %d\n",temp1);
	list_for_each_entry(node_for_Set2, &Part2_Set2.list, list)
	{
		kfree(node_for_Set2);
	}

	getnstimeofday (&end_of_time);
	difference_time = timespec_sub(end_of_time, begining_of_time);
	printk(KERN_ALERT "Time passed %lu ns\n", difference_time.tv_nsec );
	printk("Size freed after performing functions of set2 %d\n",size_count_s2);
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
