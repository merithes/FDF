/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 14:46:20 by vboivin           #+#    #+#             */
/*   Updated: 2017/03/29 10:52:47 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HFDF_H
# define HFDF_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>

/*			WINDOW PROPERTIES		*/
# define	TITLE	"title goes there"
# define	WIDTH	1920
# define	HEIGHT	1080
# define	TOP_SP	HEIGHT -HEIGHT_M

/*			COLORS					*/
# define	WHITE	0xFFFFFF
# define	ORANGE	0xFF8800

/*			OTHERS[DATA]			*/
# define	XA		0
# define	YA		1
# define	XB		2
# define	YB		3

# define	MLXID	0
# define	WINID	1
# define	PICID	2

/*			OTHERS[Preferences]		*/
# define	HEIGHT_M	300
# define	BACKG_COLOR ORANGE

/*			TYPEDEF(s)				*/

typedef struct		s_map
{
}					t_map;

/*			PROTOTYPES				*/
int			ft_drawline(void *p[2], int line[4], int color);
int			ft_rekt_angle(void *p[2], int coords[4], int color);
int			set_menu(void *p[2]);
int			dispall(void *p[2]);
void		exits(int exnu);
t_map		*stock_em(char *filename);

#endif
