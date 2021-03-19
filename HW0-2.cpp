// HW00.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#include <stdio.h>
#include <iostream>
using namespace std;

void insertion_sort(int* table, int n, int i)
{
	if (i == 0)
	{
		*table = n;
	}
	else
	{
		for (int t = 0; t <= i; t++)
		{
			if (*(table + t) > n)
			{
				int temp = *(table + t);
				*(table + t) = n;
				n = temp;

			}
			else
			{
				*(table + i) = n;
			}
		}
	}
}
int delete_arr(int* table, int n, int i)
{
	int flag = 0;
	int t = 0;
	int index = 0;
//	printf("%d\n", i);
	for (t = 0; t <=i; t++)
	{
		if (*(table + flag) == n && *(table + t) != n)
		{
			*(table + flag) = *(table + t);
			for (int y = t; y < i - 1; y++)
			{
				*(table + y) = *(table + y + 1);
			}
			
			flag++;
			index++;
		}
		else if (*(table + flag) != n && *(table + t) != n)
		{
			flag++;
		}

	}
	if (*(table + (i - 1)) == n)
	{
		index++;
	}
//	printf("%d\n", index);
	return index;


}
void display(int* table, int i)
{
	for (int t = 0; t < i; t++)
	{
		printf("%d ", *(table + t));
	}
}
int main()
{
	char input;
	int enter, by, del;
	int box[1001] = { 0 };
	int i = 0;
	while (1)
	{
		printf("Input or Delete ?");
		cin >> input;
		if (input == 'i' || input == 'I')
		{
			printf("Input an integer?");
			scanf_s("%d", &enter);
			insertion_sort(&box[0], enter, i);
			i++;
			display(&box[0], i);
			printf("\n");
		}
		else if (input == 'd' || input == 'D')
		{
			printf("Delete which integer?");
			scanf_s("%d", &del);
			by = delete_arr(&box[0], del, i);
			i = i - by;
			display(&box[0], i);
			printf("\n");
		}
	}


}
