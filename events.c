/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:44:48 by vkaron            #+#    #+#             */
/*   Updated: 2019/11/05 23:21:44 by vkaron           ###   ########.fr       */
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
	if (key == 53)
		close_win(p);
	else if (key == 49)
	{
		++p->type_color;
		if (p->type_color == 10)
			p->type_color = 0;
	}
	else if (key == 0)
		p->depth += 50;
	else if (key == 6 && (p->depth > 50))
	{
		p->depth -= 50;
	}
	else if (key == 18)
	{
		if (p->m_param == 0)
			p->m_param = 1;
		else
			p->m_param = 0;
	}
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
	if (button == 2)
		reset_param(p);
	return (0);
}

int		mouse_move_event(int x, int y, t_param *p)
{
	if (p->press3 == 1)
	{
		p->d.i += (y - p->dy);
		p->d.r += (x - p->dx);
		p->dy = y;
		p->dx = x;
		p->event = 1;
	}
	if (p->fract == JULIA && p->m_param)
	{
		p->posx = (x - p->d.r) / p->scale;
		p->posy = (y - p->d.r) / p->scale;
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
		ky = ((double)(y - p->d.i)) / p->scale;
		kx = ((double)(x - p->d.r)) / p->scale;
		if (button == 5)
			p->scale /= 1.1;
		else
			p->scale *= 1.1;
		p->d.i = (double)y - ky * p->scale;
		p->d.r = (double)x - kx * p->scale;
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
