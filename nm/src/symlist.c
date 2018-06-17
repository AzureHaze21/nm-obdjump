/*
** EPITECH PROJECT, 2018
** 
** File description:
** 
*/

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "nm.h"

void free_symlist(t_sym *head)
{
	t_sym *p = NULL;

	while (head)
	{
		p = head;
		head = p->next;
		free(p);
	}
}

void swap_syms(t_sym **head)
{
	char *tmp;

	if (!head || !(*head))
		return;
	if (!((*head)->next))
		return;
	(*head)->addr ^= (*head)->next->addr;
	(*head)->next->addr ^= (*head)->addr;
	(*head)->addr ^= (*head)->next->addr;
	(*head)->type ^= (*head)->next->type;
	(*head)->next->type ^= (*head)->type;
	(*head)->type ^= (*head)->next->type;
	tmp = (*head)->name;
	(*head)->name = (*head)->next->name;
	(*head)->next->name = tmp;
}

void push_sym(t_sym **head,
	      unsigned addr,
	      unsigned char type,
	      char *name)
{
	t_sym *p;
	t_sym *curr;

	if(!head || !name)
		return;
	if (!(p = malloc(sizeof(t_sym))))
		return;
	p->addr = addr;
	p->type = type;
	p->name = name;
	p->next = NULL;
	if (!(*head))
	{
		*head = p;
		return;
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = p;
}

static int symcmp(const void *a, const void *b) 
{ 
	char *s1 = ((t_sym*)a)->name;
	char *s2 = ((t_sym*)b)->name;
	int	ret;
	int i = 0;
	int j = 0;

	while (strchr("@_.", s1[i])) i++;
	while (strchr("@_.", s2[j])) j++;
	if (!strcmp(&s1[i], &s2[j]))
		return (strlen(s1) > strlen(s2) ? 1 : -1);
	while (*s1 && *s2) {
		s1 += strchr("@_.", *s1) ? 1 : 0;
		s2 += strchr("@_.", *s2) ? 1 : 0;
		if (*s1 && *s2 &&
		    (!strchr("@_.", *s1) && !strchr("@_.", *s2))) {
			ret =  TO_LOWER(*s1) - TO_LOWER(*s2);
			if (ret)
				return (ret);
			s1++;
			s2++;
			if (!(*s1) && *s2)
				return (-1);
			else if (*s1 && !(*s2))
				return (1);
		}
	}
	return (0);
} 

void print_symbols(t_sym *a, size_t n)
{
	size_t i = 0;

	while (i < n)
	{
		while (i < n)
		{
			if (a[i].addr || (a[i].type == 'T'))
				printf("%016x", a[i].addr);
			else
				printf("%16c", 0x20);
			printf(" %c", a[i].type);
			printf(" %s\n", a[i].name);
			i++;
		}
	}
}

void print_symbols32(t_sym *a, size_t n)
{
	size_t i = 0;

	while (i < n)
	{
		while (i < n)
		{
			if (a[i].addr || (a[i].type == 'T'))
				printf("%08x", a[i].addr);
			else
				printf("%8c", 0x20);
			printf(" %c", a[i].type);
			printf(" %s\n", a[i].name);
			i++;
		}
	}
}

void sort_symlist(t_sym **head, int arch)
{
	t_sym *curr;
	int i = 0;
	int n;

	if (!head || !(*head))
		return;
	curr = *head;
	while (curr)
	{
		++i;
		curr = curr->next;
	}
	if (i == 1)
		return;
	t_sym *symbols = malloc((i) * sizeof(t_sym));
	n = i;
	i = -1;
	curr = *head;
	while (curr)
	{
		memcpy(&symbols[++i], curr, sizeof(t_sym));
		curr = curr->next;
	}
	qsort(symbols, n, sizeof(t_sym), &symcmp);
	if (arch == 0)
		print_symbols(symbols, n);
	else
		print_symbols32(symbols, n);
	free(symbols);
}
