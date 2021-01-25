#include "../inc/list.h"

#include <stdlib.h>

static t_list *new_elem(void *data)
{
	t_list *new_elem = (t_list *)malloc(sizeof(t_list));

	new_elem->data = data;
	new_elem->next = NULL;

	return (new_elem);
}

void push_back(t_list **head, void *data)
{
	t_list *tmp = *head;

	if (!tmp)
	{
		tmp = new_elem(data);
		*head = tmp;
	}
	else
	{
		while(tmp->next)
		{
			tmp = tmp->next;
		}

		tmp->next = new_elem(data);
	}
}

#include <stdio.h>

void remove_elem(t_list **head, void *data)
{
	t_list *tmp = *head;

	// printf("\nStart remove\n");
	// int num = 0;
	// while (tmp)
	// {
	// 	if (tmp->data == data)
	// 		printf("Number to remove: %d\n", num);
	// 	num++;
	// 	tmp = tmp->next;
	// }

	tmp = *head;

	if (tmp && tmp->data == data)
	{
		free(tmp->data);
		if (tmp->next)
			*head = tmp->next;
	}
	else if (tmp)
	{
		while (tmp->next)
		{
			if (tmp->next->data == data)
			{
				free(tmp->next->data);
				if (tmp->next->next)
				{
					t_list *to_remove = tmp->next;
					tmp = tmp->next->next;
					to_remove = NULL;
				}
				else
				{
					tmp->next = NULL;
				}
				break;
			}
			tmp = tmp->next;
		}
	}
}

int list_size(t_list **list)
{
	int size = 0;

	t_list *tmp = *list;

	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}

	return size;
}













