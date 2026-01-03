/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:51:28 by picheval          #+#    #+#             */
/*   Updated: 2025/11/16 22:29:53 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cursor;

	if (!lst || !*lst)
	{	
		if (lst)
			*lst = new;
		return ;
	}
	cursor = *lst;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = new;
}
