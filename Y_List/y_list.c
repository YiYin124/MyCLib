/**
* Copyright (C) 2013 YiYin
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* version 3.0 of the License as published by the Free Software Foundation.
*/

#include <stdlib.h>
#include "y_list.h"

static int ElementClone(Element *dest, Element src, int len)
{
	void *tmp;
	if ((*dest = malloc(len)) == NULL )
		return -1; // 未申请到内存
	tmp = *dest;
	do
	{
		*(char *) tmp = *(char *) src;
		tmp++;
		src++;
	} while (len--);
	return 1;
}

List *newList(const int size)
{
	List *list;
	if ((list = (List *) malloc(sizeof(List))) == NULL )
		return NULL ; // 未申请到内存
	list->node = NULL;
	list->size = size;
	list->length = 0;
	return list;
}

int ListIterator(const List *src, const IterFunc iterator,
		const IterEndFunc endIterator)
{
	int index = 0;
	ListNode *node = src->node;
	while (node != NULL )
	{
		iterator(index, node->e);
		node = node->next;
		index++;
	}
	return endIterator();
}

int ListAddFirst(List *dest, const Element e)
{
	if (dest->node == NULL )
	{
		if ((dest->node = (ListNode *) malloc(sizeof(ListNode))) == NULL )
			return -1; // 未申请到内存

		if (ElementClone(&(dest->node->e), e, dest->size) == -1)
			return -1; // 未申请到内存

		dest->node->prev = NULL;
		dest->node->next = NULL;
		dest->length++;
		return 1;
	}

	if ((dest->node->prev = (ListNode *) malloc(sizeof(ListNode))) == NULL )
		return -1; // 未申请到内存

	if (ElementClone(&(dest->node->prev->e), e, dest->size) == -1)
		return -1; // 未申请到内存

	dest->node->prev->prev = NULL;
	dest->node->prev->next = dest->node;
	dest->node = dest->node->prev;
	dest->length++;
	return 1;
}

int ListAddLast(List *dest, const Element e)
{
	ListNode *node = dest->node;

	if (dest->node == NULL )
	{
		if ((dest->node = (ListNode *) malloc(sizeof(ListNode))) == NULL )
			return -1; // 未申请到内存

		if (ElementClone(&(dest->node->e), e, dest->size) == -1)
			return -1; // 未申请到内存

		dest->node->prev = NULL;
		dest->node->next = NULL;
		dest->length++;
		return 1;
	}

	while (1)
	{
		if (node->next == NULL )
			break;
		else
			node = node->next;
	}

	if ((node->next = (ListNode *) malloc(sizeof(ListNode))) == NULL )
		return -1; // 未申请到内存

	if (ElementClone(&(node->next->e), e, dest->size) == -1)
		return -1; // 未申请到内存

	node->next->prev = node;
	node->next->next = NULL;
	dest->length++;
	return 1;
}

int ListAdd(List *dest, int index, const Element e)
{
	ListNode *node = dest->node;
	ListNode *addNode;

	if (index < 0 || index > dest->length)
		return -1; // 插入地址超出范围
	else if (index == 0)
		return ListAddFirst(dest, e);
	else if (index == dest->length)
		return ListAddLast(dest, e);

	while (index--)
	{
		node = node->next;
	}

	if ((addNode = (ListNode *) malloc(sizeof(ListNode))) == NULL )
		return -1; // 未申请到内存

	if (ElementClone(&(addNode->e), e, dest->size) == -1)
		return -1; // 未申请到内存

	addNode->next = node;
	addNode->prev = node->prev;
	node->prev->next = addNode;
	node->prev = addNode;
	dest->length++;
	return 1;
}

int ListRemoveFirst(List *dest)
{
	ListNode *node = dest->node;

	if (dest->node == NULL )
		return -1; // 此表为空

	dest->node = node->next;

	if (dest->node != NULL )
		dest->node->prev = node->prev;

	free(node->e);
	free(node);
	dest->length--;
	return 1;
}

int ListRemoveLast(List *dest)
{
	ListNode *node = dest->node;

	if (dest->node == NULL )
		return -1; // 此表为空

	while (1)
	{
		if (node->next == NULL )
			break;
		else
			node = node->next;
	}

	if (node->prev == NULL )
		dest->node = NULL;
	else
		node->prev->next = NULL;

	free(node->e);
	free(node);
	dest->length--;
	return 1;
}

int ListRemove(List *dest, int index)
{
	ListNode *node = dest->node;

	if (node == NULL || index < 0 || index >= dest->length)
		return -1; // 删除地址超出范围 或 空表
	else if (index == 0)
		return ListRemoveFirst(dest);
	else if (index == dest->length - 1)
		return ListRemoveLast(dest);

	while (index--)
	{
		node = node->next;
	}

	node->prev->next = node->next;
	node->next->prev = node->prev;

	free(node->e);
	free(node);
	dest->length--;
	return 1;
}

int ListSetFirst(List *dest, const Element e)
{
	Element tmp;
	if (dest->node == NULL )
		return -1; // 此表为空

	tmp = dest->node->e;
	if (ElementClone(&(dest->node->e), e, dest->size) == -1)
		return -1; // 未申请到内存

	free(tmp);
	return 1;
}

int ListSetLast(List *dest, const Element e)
{
	ListNode *node = dest->node;
	Element tmp;
	if (dest->node == NULL )
		return -1; // 此表为空

	while (1)
	{
		if (node->next == NULL )
			break;
		else
			node = node->next;
	}

	tmp = node->e;
	if (ElementClone(&(node->e), e, dest->size) == -1)
		return -1; // 未申请到内存

	free(tmp);
	return 1;
}

int ListSet(List *dest, int index, const Element e)
{
	ListNode *node = dest->node;
	Element tmp;

	if (node == NULL || index < 0 || index >= dest->length)
		return -1; // 设置地址超出范围 或 空表

	while (index--)
	{
		node = node->next;
	}

	tmp = node->e;
	if (ElementClone(&(node->e), e, dest->size) == -1)
		return -1; // 未申请到内存

	free(tmp);
	return 1;
}

Element ListGetFirst(const List *src)
{
	if (src->node == NULL )
		return NULL ; // 此表为空
	return src->node->e;
}

Element ListGetLast(const List *src)
{
	ListNode *node = src->node;

	if (src->node == NULL )
		return NULL ; // 此表为空

	while (1)
	{
		if (node->next == NULL )
			break;
		else
			node = node->next;
	}

	return node->e;
}

Element ListGet(const List *src, int index)
{
	ListNode *node = src->node;

	if (node == NULL || index < 0 || index >= src->length)
		return NULL ; // 设置地址超出范围 或 空表

	while (index--)
	{
		node = node->next;
	}

	return node->e;
}

Element ListPop(List *dest)
{
	Element tmp = ListGetFirst(dest);
	ListRemoveFirst(dest);
	return tmp;
}

int ListClone(List **dest, const List *src)
{
	int i = 0;
	if ((*dest = newList(src->size)) == NULL )
		return -1; // 创建副本失败

	for (i = 0; i < src->length; i++)
	{
		if (ListAdd(*dest, i, ListGet(src, i)) == -1)
			return -1; // 添加元素失败
	}
	return 1;
}

void ListClear(List *dest)
{
	while (dest->length)
		ListRemoveFirst(dest);
	free(dest);
}

int ListLink(List *dest, const List *src)
{
	int i = 0;

	if (dest->size != src->size)
		return -1; // 容器大小不同不能连接

	for (i = 0; i < src->length; i++)
	{
		if (ListAddLast(dest, ListGet(src, i)) == -1)
			return -1; // 添加元素失败
	}
	return 1;
}
