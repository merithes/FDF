/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 19:31:46 by vboivin           #+#    #+#             */
/*   Updated: 2017/04/05 15:37:04 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hfdf.h"

static int			check_range(t_list *inp)
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
	outp[iout + 1] = END_F;
	outp[iout + 2] = END_S;
	return (outp);
}

static int			into_int(t_list *inp)
{
	int				i;
	int				len;

	i = 0;
	while (inp)
	{
		if (!(len = get_amnt((char *)inp->content)))
			return (0);
		inp->content = int_tab((char *)inp->content, len);
		inp = inp->next;
	}
	return (1);
}

t_pt				*transfo(t_list *inp)
{
	if (check_range(inp) != 1 || into_int(inp) != 1)
		return (NULL);
	int i = 0;
	while (inp)
	{
		while (((int *)inp->content)[i + 1] != END_F && ((int *)inp->content)[i + 2] != END_S)
			printf("%d ", ((int *)inp->content)[i++]);
		printf("\n");
		i = 0;
		inp = inp->next;
	}
	return (NULL);
}
