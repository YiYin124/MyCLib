/**
* Copyright (C) 2013 YiYin
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* version 3.0 of the License as published by the Free Software Foundation.
*/

#include <stdio.h>
#include <stdlib.h>
#include "y_list.h"

typedef struct exstruct
{
	int val;
} exstruct;

void OnIterator(int index, Element e)
{
	printf("[%d]'%d'", index, *(int *) e);
}

int EndIterator()
{
	puts("\n==== iterator result ====");
	return 1;
}

void sOnIterator(int index, Element e)
{
	printf("[%d]'%d'", index, ((exstruct *) e)->val);
}

int sEndIterator()
{
	puts("\n==== iterator result ====");
	return 1;
}

int main(void)
{
	int tmp;
	exstruct stmp;

	List *list = newList(sizeof(int));
	List *slist = newList(sizeof(exstruct));

	puts("(int)栈操作:\n入栈");
	tmp = 0;
	ListPush(list, &tmp);
	tmp = 1;
	ListPush(list, &tmp);
	tmp = 2;
	ListPush(list, &tmp);
	tmp = 3;
	ListPush(list, &tmp);
	ListIterator(list, OnIterator, EndIterator);

	puts("出栈");
	ListPop(list);
	ListPop(list);
	ListIterator(list, OnIterator, EndIterator);

	puts("");

	puts("(exstruct)栈操作:\n入栈");
	stmp.val = 00;
	ListPush(slist, &stmp);
	stmp.val = 11;
	ListPush(slist, &stmp);
	stmp.val = 22;
	ListPush(slist, &stmp);
	stmp.val = 33;
	ListPush(slist, &stmp);
	ListIterator(slist, sOnIterator, sEndIterator);

	puts("出栈");
	ListPop(slist);
	ListPop(slist);
	ListIterator(slist, sOnIterator, sEndIterator);

	system("PAUSE");
	return EXIT_SUCCESS;
}


