/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 19:32:18 by vboivin           #+#    #+#             */
/*   Updated: 2017/03/29 21:21:42 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hFdF.h"

int				set_menu(void *p[2])
{
	int			coords[4];

	set_coords(coords, 0, HEIGHT - HEIGHT_M, WIDTH, HEIGHT);
	rekt_angle(p, coords, ORANGE);
	return(0);
}
