/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 19:32:18 by vboivin           #+#    #+#             */
/*   Updated: 2017/03/30 12:01:07 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hFdF.h"

int				set_menu(void *p[2])
{
	int			coords[4];

	coords[XA] = 0;
	coords[YA] = TOP_M;
	coords[XB] = WIDTH;
	coords[YB] = HEIGHT;
	rekt_angle(p, coords, BACKG_COLOR);
	return (0);
}
