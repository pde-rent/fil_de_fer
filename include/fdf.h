/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-rent <pde-rent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 14:34:31 by pde-rent          #+#    #+#             */
/*   Updated: 2018/03/02 15:46:42 by pde-rent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <mlx.h>
# include "../libft/libft.h"
# include "colors.h"
# include "keymap.h"

# define IS_INT(X) 		if (!X) return (0);
# define IS_CHAR(X) 	if (!X) return (NULL);
# define IS_VOID(X)		if (!X) return ;
# define MX				env->grid->matrix
# define SCREEN_WIDTH	2560
# define SCREEN_HEIGHT	1440
# define ROT_X			env->view->rot_x
# define ROT_Y			env->view->rot_y
# define ROT_Z			env->view->rot_z
# define POS_X			env->view->pos_x
# define POS_Y			env->view->pos_y
# define REL_X(X)		(X->x - env->view->mid_x)
# define REL_Y(X)		(X->y - env->view->mid_y)
# define X_OFFSET		env->grid->x_offset
# define Y_OFFSET		env->grid->y_offset
# define BUFF_SIZE		1000

typedef struct  s_point
{
	int     x;
	int     y;
	int     z;
	int		d;
	int     clr;
}               t_point;

typedef	struct	s_vect
{
	t_point *a;
	t_point *b;
}				t_vect;

typedef struct	s_grid
{
	int		nb_x;
	int		nb_y;
	int		x_offset;
	int		y_offset;
	int		x_spacing;
	int		y_spacing;
	int		z_mult;
	int		zx_spacing;
	int		zy_spacing;
	int		max;
	int		min;
	int		**matrix;
}			t_grid;

typedef struct	s_view
{
	int		depth;
	int		zoom;
	int		pos_x;
	int		pos_y;
	int		rot_x;
	int		rot_y;
	int		rot_z;
	int		mid_x;
	int		mid_y;
	int		last_dir;
	int		background;
	int8_t	trail_lvl;	
}				t_view;

typedef	struct	s_env
{
	//t_point	*ptest;
	t_grid	*grid;
	t_view	*view;
	void	*mlx;
	void	*win;
	void	*img;
	char	*win_title;
	char	*file_name;
	int8_t	display_ui;
	int8_t	display_state;
	int8_t	trail;
	int		stroke_cnt;
	int     width;
	int     height;
	int     pct_scale;
	int		clr1;
	int		clr2;
	int		*imgtab;
	int		bpp;
	int		sl;
	int		endian;
}				t_env;

typedef int MOVE(t_env *env);
MOVE	move_up, move_down, move_right, move_left;
MOVE	zoom_in, zoom_out; 
MOVE	inc_depth, dec_depth;

typedef int ROT(t_env *env, int dir);
ROT		rot_x, rot_y, rot_z;

void	draw_line(t_env *env, t_point *a, t_point *b);
void    draw_circle(t_env *env, t_point *mid, float pct_radius);
void	win_refresh(t_env *env);
void	ppoint(t_env *env, t_point *pt);
void	ppixel(t_env *env, int *tab, int x, int y, int clr);
void	print_ui(t_env *env);
void    put_ui(t_env *env, int row, int col, int clr, char *str);
char	*raw_str(char *file_name);
int     rgb_to_hex(int R, int G, int B);
int     set_opacity(int clr, int8_t lvl);
int     gradient(t_env *env, t_point *a, t_point *b, int y, int x);
int     tab_init(t_env *env, char *str);
int		grid_init(t_env *env);
int		view_init(t_view *view);
int		change_back_color(t_env *env);
int		change_front_color(t_env *env);
int		dyna_key_hook(t_env *env);
int		loop_key_hook(t_env *env);
int		key_recognition(int key_code, t_env *env);
int		mouse_recognition(int key_code, int pos_x, int pos_y, t_env *env);
int		sketch(t_env *env);
int		first_trail(t_env *env);
int		map_matrix(t_env *env);
int		check_av(int ac, char **av);
int		put_err(int errno);
int		check_map(char *str);
int		reinit(t_env *env);
int     deinit(t_env *env);
t_env	*env_init(void);
t_point	*pt_init(void);
t_vect  *vectorize(t_point *a, t_point *b);

#endif