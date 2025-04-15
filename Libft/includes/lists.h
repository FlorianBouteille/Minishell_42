/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csolari <csolari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:51:55 by csolari           #+#    #+#             */
/*   Updated: 2025/02/21 11:25:41 by csolari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

typedef struct s_pslist
{
	int				value;
	struct s_pslist	*next;
}					t_pslist;

int			ft_ps_lstsize(t_pslist *lst);
int			ft_ps_lstmax(t_pslist **stack);
int			ft_ps_lstmin(t_pslist **stack);
int			ft_ps_index(t_pslist **stack, int value);
int			ft_firstsup(t_pslist **stack, int value);
int			ft_firstinf(t_pslist **stack, int value);
void		ft_ps_lstadd_back(t_pslist **lst, t_pslist *new);
void		ft_ps_lstfree(t_pslist **lst);
void		ft_print_list(t_pslist **lst, char c);
void		ft_ps_lstadd_front(t_pslist **stack, t_pslist *new);
t_pslist	*ft_ps_lstnew(int content);
t_pslist	*ft_ps_lstlast(t_pslist *lst);
t_pslist	*ft_ps_lstpenultimate(t_pslist *lst);

typedef struct s_value
{
	int	median;
	int	len;
	int	*cpy_tab;
}		t_value;

#endif