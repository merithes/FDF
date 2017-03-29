/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 10:22:47 by vboivin           #+#    #+#             */
/*   Updated: 2016/12/09 12:06:25 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*outp;

	if ((outp = malloc(sizeof(*outp))) == NULL)
		return (NULL);
	if (content == NULL)
	{
		outp->content = NULL;
		outp->content_size = 0;
	}
	else
	{
		if ((outp->content = malloc(content_size)) == NULL)
		{
			free(outp->content);
			return (NULL);
		}
		ft_memcpy(outp->content, content, content_size);
		outp->content_size = content_size;
	}
	outp->next = NULL;
	return (outp);
}
