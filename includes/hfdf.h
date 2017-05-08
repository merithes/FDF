/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 14:46:20 by vboivin           #+#    #+#             */
/*   Updated: 2017/04/26 20:35:13 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HFDF_H
# define HFDF_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>

/*
** WINDOW PROPERTIES
*/
# define TITLE "title goes there"
# define WIDTH 800
# define HEIGHT 400
# define TOP_SP HEIGHT -HEIGHT_M

/*
** COLORS
*/
# define WHITE 0xFFFFFF
# define LI_RED 0xFE3333

# define BLUU 255
# define REDD 0xFE0000
# define GRNN 0x00FE00
# define YELO 0xFEFE00

# define BLUE 0x4040FE
# define CYAN 0x00d5d8
# define ORAN 0xFE8800

# define YEL_D 0X333300

/*
** OTHERS[DATA]
*/
# define XA 0
# define YA 1
# define XB 2
# define YB 3

# define X 0
# define Y 1
# define Z 2

# define MLXID 0
# define WINID 1

# define END_F 1471471473
# define END_S -1791791794

# define T_PT sizeof(t_pt)
# define T_SEG sizeof(t_seg)
# define COS(angleDegrees) ((cos((angleDegrees) * M_PI / 180)))
# define SIN(angleDegrees) ((sin((angleDegrees) * M_PI / 180)))
# define RX(pt, a) (pt * (COS(a) - SIN(a)))
# define RY(pt, a) (pt * (SIN(a) + COS(a)))
# define PYTH(a, b) (sqrt(a * a + b * b))
# define ABS(a) (sqrt (a * a))

/*
** OTHERS[Preferences]
*/
# define HEIGHT_M 300
# define TOP_M HEIGHT - HEIGHT_M
# define MENU_COLOR LI_RED
# define WALP_COLOR 0x000033 

# define GRIDCOL CYAN + 1

# define D_P 20
# define D(a) (a * D_P)
# define MARGIN_TOP HEIGHT/2
# define MARGIN_LEF WIDTH/2
# define Z_CO 0

# define ROTX 0
# define ROTY 0
# define ROTZ 0

# define Z_DIFF 1
# define ANG_DIFF 5
# define MAR_DIFF 10
# define ZOOM_DIFF 1

/*
** TYPEDEF(s)
*/

typedef struct		s_pt
{
	int				x;
	int				y;
	int				z;
	int				pos[2];
	struct s_pt		*r;
	struct s_pt		*b;
}					t_pt;

typedef struct		s_seg
{
	int	xa;
	int	ya;
	int	za;
	int	xb;
	int	yb;
	int	zb;
}					t_seg;

typedef struct		s_info
{
	int				margin_t;
	int				margin_l;
	int				z_coef;
	int				rotx;
	int				roty;
	int				rotz;
	void			*mid;
	void			*wid;
	struct s_pt		*first_pt;
	int				len;
	int				height;
	int				zoom;
	int				detail;
}					t_info;


/*
** PROTOTYPES
*/
int					ft_drawline(void *p[2], t_seg *seg, int color);
void				set_coords(int inp[4], int xa, int ya, int xb, int yb);
int					rekt_angle(void *p[2], int coords[4], int color);
int					set_menu(t_info *inf);
t_info				*get_map(int fildes, void *pointers[2]);
void				exits(int exnu);
int					remem(int inp_fd, int boo);
t_pt				*transfo(t_list *inp);
int					check_range(t_list *inp);
int					into_int(t_list *inp);
t_info				*free_stuff(t_list *inp);
t_pt				*to_pt_list(t_list *inp, t_info *toset);
void				draw_grid(t_info *inp, int color);
void				put_word(void *p[2], int x, int y, char *inp);

#endif
