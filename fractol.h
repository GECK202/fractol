/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 13:16:47 by vkaron            #+#    #+#             */
/*   Updated: 2019/11/05 23:23:58 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define MANDELBROT 1
# define JULIA 2
# define SPACE 3
# define BUBBLES 4
# define NECKLACE 5

# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <math.h>
# include <pthread.h>

typedef struct		s_comp
{
	double			i;
	double			r;
}					t_comp;

typedef struct		s_size
{
	int				w;
	int				h;
}					t_size;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_pdata
{
	unsigned int	*pixel;
	double			ci;
	t_comp			d;
	double			scale;
	t_size			img_s;
	int				type_color;
	double			zi;
	double			zr;
	int				i;
	int				fract;
	double			posx;
	double			posy;
	int				depth;
	int				m_param;
}					t_pdata;

typedef struct		s_param
{
	void			*mlx_p;
	void			*win_p;
	void			*img_p;
	unsigned int	*img_data;
	int				w;
	int				h;
	t_size			img_s;
	int				s_line;
	int				bpp;
	int				endian;
	int				bgc;
	int				event;
	int				press3;
	int				type_color;
	t_comp			d;
	int				dx;
	int				dy;
	double			posx;
	double			posy;
	double			scale;
	int				fract;
	int				depth;
	int				m_param;
	t_pdata			*tdata;
	pthread_t		*pthread;
}					t_param;

int					close_win(t_param *p);
int					key_down_event(int key, t_param *p);
int					mouse_up_event(int button, int x, int y, t_param *p);
int					mouse_move_event(int x, int y, t_param *p);
int					mouse_down_event(int button, int x, int y, t_param *p);
unsigned int		set_color(int k, int color_type);
void				iteration_j(t_pdata *tdata, t_comp z, t_comp c, int r);
void				*calc_mandel(void *thread_arg);
void				*calc_fract(void *thread_arg);
void				init_thread(t_param *p);
int					init(t_param *p, char *file);
void				init_thread(t_param *p);
void				reset_param(t_param *p);

#endif
