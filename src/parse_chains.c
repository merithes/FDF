/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 19:31:46 by vboivin           #+#    #+#             */
/*   Updated: 2017/04/26 19:21:25 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hfdf.h"

static void			set_pt(t_pt *inp, int a, int b, int c)
{
	inp->x = a;
	inp->y = b;
	inp->z = c;
	inp->r = NULL;
	inp->b = NULL;
}

static t_pt			*chain_layer(int *inp, int y, t_info *toset)
{
	t_pt			*outp;
	t_pt			*scroll;
	t_pt			*prev;
	int				i;

	i = 0;
	while (inp[i] != END_F && inp[i + 1] != END_S)
	{
		prev = scroll;
		if (!(scroll = malloc(T_PT)))
			return (NULL);
		if (i == 0)
			outp = scroll;
		else
			prev->r = scroll;
		set_pt(scroll, i, y, inp[i]);
		i++;
	}
	if (toset->len < i)
		toset->len = i - 1;
	if (inp)
		free(inp);
	return (outp);
}

static void			link_chain(t_pt *inp)
{
	t_pt			*scroller_u;
	t_pt			*scroller_d;

	while (inp)
	{
		scroller_u = inp;
		scroller_d = inp->b;
		while (scroller_u)
		{
			scroller_u->b = scroller_d;
			scroller_u = scroller_u->r;
			if (scroller_d)
				scroller_d = scroller_d->r;
		}
		inp = inp->b;
	}
}

t_pt				*to_pt_list(t_list *inp, t_info *toset)
{
	t_pt			*first;
	t_pt			*layers;
	t_list			*prev;
	int				i;

	i = 0;
	prev = inp;
	if (!(first = chain_layer((int *)inp->content, 0, toset)))
		return (0);
	inp = inp->next;
	layers = first;
	while (inp && ++i)
	{
		if (!(layers->b = chain_layer((int *)inp->content, i, toset)))
			return (0);
		layers = layers->b;
		free(prev);
		prev = inp;
		inp = inp->next;
	}
	link_chain(first);
	return (first);
}
