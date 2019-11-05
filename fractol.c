/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:50:08 by vkaron            #+#    #+#             */
/*   Updated: 2019/11/05 23:33:43 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clear_image(t_param *param)
{
	int cell;

	cell = 0;
	while (cell < param->img_s.h * param->img_s.w)
	{
		param->img_data[cell] = param->bgc;
		++cell;
	}
}

int		draw_fractal(t_param *p)
{
	int i;

	init_thread(p);
	i = 0;
	while (i < p->img_s.h)
	{
		pthread_join(p->pthread[i], NULL);
		++i;
	}
	p->event = 0;
	return (0);
}

void	draw_info(t_param *p)
{
	mlx_string_put(p->mlx_p, p->win_p, 6, p->img_s.h - 130, 0,
	"|   use mouse:                |      use keyboard:          |");
	mlx_string_put(p->mlx_p, p->win_p, 6, p->img_s.h - 110, 0,
	"|_____________________________|_____________________________|");
	mlx_string_put(p->mlx_p, p->win_p, 6, p->img_s.h - 90, 0,
	"| -scroll to scale            | -A/Z +/-iterations          |");
	mlx_string_put(p->mlx_p, p->win_p, 6, p->img_s.h - 70, 0,
	"| -move with middle button    | -SPACE -change palette      |");
	mlx_string_put(p->mlx_p, p->win_p, 6, p->img_s.h - 50, 0,
	"| -right click to reset       | -ESC to exit                |");
	if (p->fract == JULIA)
		mlx_string_put(p->mlx_p, p->win_p, 6, p->img_s.h - 30, 0,
		"| -mouse position attribute   | -1 set mouse atrubute       |");
}

int		not_event(t_param *p)
{
	if (p->event)
	{
		clear_image(p);
		draw_fractal(p);
		mlx_put_image_to_window(p->mlx_p, p->win_p, p->img_p, 0, 0);
		draw_info(p);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_param		*p;

	if (ac == 2)
	{
		p = (t_param *)malloc(sizeof(t_param));
		if (init(p, av[1]))
		{
			mlx_mouse_hook(p->win_p, mouse_down_event, (void *)p);
			mlx_loop_hook(p->mlx_p, not_event, (void *)p);
			mlx_key_hook(p->win_p, key_down_event, (void *)p);
			mlx_hook(p->win_p, 17, 0, close_win, (void *)p);
			mlx_hook(p->win_p, 6, 0, mouse_move_event, (void *)p);
			mlx_hook(p->win_p, 5, 0, mouse_up_event, (void *)p);
			mlx_loop(p->mlx_p);
		}
		free(p);
	}
	write(1, "Usage : ./fractol [fractals]\n", 29);
	write(1, "fractals:\n-->Mandelbrot\n-->Julia\n", 33);
	write(1, "-->Space\n-->Bubbles\n-->Necklace\n", 32);
	return (0);
}
