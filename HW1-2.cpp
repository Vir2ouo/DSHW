#include <iostream>
#include <stdio.h>
using namespace std;

struct node {
	int data;
	struct node* next;
};
struct node* head, * rear;

void create_single_list(void)
{
	head = (struct node*)malloc(sizeof(struct node));
	rear = (struct node*)malloc(sizeof(struct node));
	head->next = NULL;
	rear->next = NULL;
}

int empty(void)
{
	if (head->next == NULL)
		return 1;
	else
		return 0;
}
void insertNode(int number)
{
	struct node* new_node,*prev_node, *this_node;
	new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = number;
	new_node->next = NULL;

	if (empty())
	{
		head->next = new_node;
		rear-> next = new_node;
		
	}
	else
	{
		this_node = head->next;
		if (number < this_node->data)  //插入到串列前端
		{
			head->next = new_node;
			new_node->next = this_node;
		}
		else
		{
			while (this_node->next != NULL) //插入到串列中間
			{
				prev_node = this_node;
				this_node = this_node->next;
				if (number < this_node->data)
				{
					prev_node->next = new_node;
					new_node->next = this_node;
					return;
				}
			}
			this_node->next = new_node; //插入到串列尾端
			rear->next = new_node;
		}
	}

}

void delete_node(int number)
{
	struct node* this_node, * prev_node, * temp_node;
	prev_node = head;
	this_node = head->next;
	while (this_node->next != NULL)  //不是最後一 個節點時
	{
		if (number == this_node->data)
		{
			temp_node = this_node;
			prev_node->next = this_node->next;
			this_node = this_node->next;
			free(temp_node);
		}
		else
		{
			prev_node = this_node;
			this_node=this_node->next;
		}
	}
	if (number == this_node->data) //檢查最後一個節點
	{
		temp_node = this_node;
		prev_node->next = NULL;
		rear->next = prev_node;
		free(temp_node);
	}
}


void printList(void)
{
	struct node* this_node;
	if (!empty())
	{
		this_node = head->next;
		while (this_node->next != NULL)
		{
			printf("%d ", this_node->data);
			this_node = this_node->next;
		}
		printf("%d\n", this_node->data);
	}
	
}
int main()
{
	char input;
	int t = 0;
	int number;

	create_single_list();
	while (1)
	{
		printf("Input or Delete ?");
		cin >> input;
		cout << endl;
		if (input == 'i' || input == 'I')
		{
			printf("Input an integer?");
			cin >> number;
			insertNode(number);
			printList();
			cout << endl;
			
		}
		else if (input == 'd' || input == 'D')
		{
			printf("Input an integer?");
			cin >> number;
			delete_node(number);
			printList();
		}
	}
}


