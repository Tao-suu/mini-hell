/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:24:18 by picheval          #+#    #+#             */
/*   Updated: 2025/11/16 22:32:02 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lstmap_create_new_content(t_list *elem, void **new_content,
	void *(*f)(void *))
{
	*new_content = NULL;
	if (elem->content)
	{
		*new_content = f(elem->content);
		if (!*new_content)
			return (0);
	}
	return (1);
}	

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*new;
	void	*new_content;

	if (!f || !del || !lst)
		return (NULL);
	ret = NULL;
	while (lst)
	{
		if (!ft_lstmap_create_new_content(lst, &new_content, f))
		{
			ft_lstclear(&ret, del);
			return (NULL);
		}
		new = ft_lstnew(new_content);
		if (!new)
		{
			del(new_content);
			ft_lstclear(&ret, del);
			return (NULL);
		}
		ft_lstadd_back(&ret, new);
		lst = lst->next;
	}
	return (ret);
}
