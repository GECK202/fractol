/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 13:16:47 by vkaron            #+#    #+#             */
/*   Updated: 2019/10/28 17:00:07 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <mlx.h>
#include <math.h>
#include <pthread.h>

typedef struct 		s_pdata
{
	unsigned int	*pixel;
	double			ci;
	double			di;
	double			dr;
	double			scale;
	int				img_w;
}					t_pdata;

typedef struct		s_param
{
	void			*mlx_p;
	void			*win_p;
	void			*img_p;
	unsigned int	*img_data;
	int				w;
	int				h;
	int				img_w;
	int				img_h;
	int				s_line;
	int				bpp;
	int				endian;
	int				bgc;
	int				event;
	int				press3;
	int				type_color;
	double			di;
	double			dr;
	int				dx;
	int				dy;
	double			scale;
	t_pdata			*tdata;
	pthread_t		*pthread;
}					t_param;

int					close_win(t_param *p);
int					key_down_event(int key, t_param *p);
int					mouse_up_event(int button, int x, int y, t_param *p);
int					mouse_move_event(int x, int y, t_param *p);
int					mouse_down_event(int button, int x, int y, t_param *p);

#endif