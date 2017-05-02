/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 19:31:46 by vboivin           #+#    #+#             */
/*   Updated: 2017/04/06 11:05:25 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hfdf.h"

int					check_range(t_list *inp)
{
	int				i;

	i = -1;
	while (inp)
	{
		while (((char *)inp->content)[++i] != 0)
		{
			if ((((char *)inp->content)[i] < '0' ||
						((char *)inp->content)[i] > '9') &&
							((char *)inp->content)[i] != '-' &&
								((char *)inp->content)[i] != ' ')
				return (0);
		}
		inp = inp->next;
		i = -1;
	}
	return (1);
}

static int			get_amnt(char *inp)
{
	int				i;
	int				qty;

	qty = 0;
	i = -1;
	while (inp[++i])
		if (inp[i] != ' ')
			qty++;
	return (qty + 5);
}

static int			*int_tab(char *inp, int len)
{
	int				i;
	int				iout;
	int				*outp;

	if (!(outp = malloc(sizeof(int) * (len + 5))) || !inp)
		return (NULL);
	i = 0;
	iout = 0;
	while (inp[i])
	{
		while (inp[i] == ' ')
			i++;
		outp[iout++] = ft_atoi(inp + i);
		while (inp[i] != ' ' && inp[i])
			i++;
	}
	outp[iout] = END_F;
	outp[iout + 1] = END_S;
	iout = 0;
	return (outp);
}

int					into_int(t_list *inp)
{
	char			*tmp;
	int				len;
	int				i;

	i = 0;
	tmp = NULL;
	while (inp && ++i)
	{
		if (!(len = get_amnt((char *)inp->content)))
			return (0);
		tmp = (char *)inp->content;
		inp->content = int_tab((char *)inp->content, len);
		if (tmp)
			free(tmp);
		inp = inp->next;
	}
	return (i);
}

t_info				*free_stuff(t_list *inp)
{
	t_list			*nxt;

	while (inp)
	{
		nxt = inp;
		inp = inp->next;
		if (nxt->content)
			free(nxt->content);
		if (nxt)
			free(nxt);
	}
	return (NULL);
}
