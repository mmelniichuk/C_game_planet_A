#pragma once

typedef struct	s_list t_list;

struct			s_list
{
	t_list		*next;
	void		*data;	
};

void			push_back(t_list **head, void *data);
void			remove_elem(t_list **head, void *data);
int				list_size(t_list **list);
