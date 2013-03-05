/**
* Copyright (C) 2013 YiYin
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* version 3.0 of the License as published by the Free Software Foundation.
*/

#ifndef Y_LIST_H_
#define Y_LIST_H_

typedef void * Element;

typedef struct ListNode
{
	Element e; 				/* data block */
	struct ListNode *prev; 	/* prev node */
	struct ListNode *next; 	/* next node */
} ListNode;

typedef struct List
{
	int size; 				/* element size */
	int length; 			/* list lengih */
	struct ListNode *node; 	/* header */
} List;

typedef void (*IterFunc)(int index, Element e);
typedef int (*IterEndFunc)();

List *newList(const int size);
int ListAddFirst(List *dest, const Element e);
int ListAddLast(List *dest, const Element e);
int ListAdd(List *dest, int index, const Element e);

int ListRemoveFirst(List *dest);
int ListRemoveLast(List *dest);
int ListRemove(List *dest, int index);

int ListSetFirst(List *dest, const Element e);
int ListSetLast(List *dest, const Element e);
int ListSet(List *dest, int index, const Element e);

Element ListGetFirst(const List *src);
Element ListGetLast(const List *src);
Element ListGet(const List *src, int index);

#define ListPush(dest, e) ListAddFirst(dest, e)
Element ListPop(List *dest);

int ListIterator(const List *src, const IterFunc iterator,
		const IterEndFunc endIterator);
int ListClone(List **dest, const List *src);
void ListClear(List *dest);
int ListLink(List *dest, const List *src);

#endif /* Y_LIST_H_ */
