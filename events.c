/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:44:48 by vkaron            #+#    #+#             */
/*   Updated: 2019/10/28 17:27:34 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		close_win(t_param *p)
{
	mlx_destroy_window(p->mlx_p, p->win_p);
	free(p->pthread);
	free(p->tdata);
	free(p);
	exit(0);
}

int		key_down_event(int key, t_param *p)
{
	if (key == 49)
	{
		++(p->type_color);
		if (p->type_color == 2)
			p->type_color = 0;
	}
	if (key == 53)
		close_win(p);
	p->event = 1;
	return (0);
}

int		mouse_up_event(int button, int x, int y, t_param *p)
{
	if (button == 3 && x && y)
	{
		p->press3 = 0;
		p->dx = 0;
		p->dy = 0;
	}
	return (0);
}

int		mouse_move_event(int x, int y, t_param *p)
{
	if (p->press3 == 1)
	{
		p->di += (y - p->dy);
		p->dr += (x - p->dx);
		p->dy = y;
		p->dx = x;
		p->event = 1;
	}
	return (0);
}

int		mouse_down_event(int button, int x, int y, t_param *p)
{
	double kx;
	double ky;

	kx = 0;
	ky = 0;
	if ((button == 5) || (button == 4))
	{
		ky = ((double)(y - p->di)) / p->scale;
		kx = ((double)(x - p->dr)) / p->scale;
		if (button == 5)
			p->scale /= 1.1;
		else
			p->scale *= 1.1;
		p->di = (double)y - ky * p->scale;
		p->dr = (double)x - kx * p->scale;
		p->event = 1;
	}
	else if (button == 3 && !p->press3)
	{
		p->press3 = 1;
		p->dx = x;
		p->dy = y;
	}
	return (0);
}
