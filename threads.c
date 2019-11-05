/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 21:35:29 by vkaron            #+#    #+#             */
/*   Updated: 2019/11/05 23:30:37 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	set_fract_param(t_param *p)
{
	if (p->fract == SPACE)
	{
		p->scale = 32215350185.300587;
		p->d.i = -3032071848.304810;
		p->d.r = -9577036288.647171;
		p->posx = 0.1075;
		p->posy = 0.88;
		p->type_color = 1;
		p->depth = 150;
	}
	else if (p->fract == BUBBLES)
	{
		p->posx = 0.4;
		p->posy = -1.0;
	}
	else if (p->fract == NECKLACE)
	{
		p->posx = -0.19;
		p->posy = -0.93;
		p->type_color = 2;
	}
}

void		reset_param(t_param *p)
{
	p->bgc = 0;
	p->event = 1;
	p->press3 = 0;
	p->type_color = 0;
	if (p->fract == JULIA)
		p->type_color = 9;
	p->dx = 0;
	p->dy = 0;
	p->scale = 400.0;
	p->d.i = p->img_s.h / 2;
	p->d.r = p->img_s.w / 2;
	p->posx = -0.4;
	p->posy = -0.67;
	p->depth = 100;
	p->m_param = 0;
	set_fract_param(p);
}

void		init_thread(t_param *p)
{
	int i;

	i = 0;
	while (i < p->img_s.h)
	{
		p->tdata[i].pixel = &(p->img_data[i * p->img_s.w]);
		p->tdata[i].ci = ((double)(i - p->d.i)) / p->scale;
		p->tdata[i].d.r = p->d.r;
		p->tdata[i].d.i = p->d.i;
		p->tdata[i].scale = p->scale;
		p->tdata[i].img_s.w = p->img_s.w;
		p->tdata[i].img_s.h = p->img_s.h;
		p->tdata[i].type_color = p->type_color;
		p->tdata[i].i = i;
		p->tdata[i].posx = p->posx;
		p->tdata[i].posy = p->posy;
		p->tdata[i].fract = p->fract;
		p->tdata[i].depth = p->depth;
		p->tdata[i].m_param = p->m_param;
		if (p->fract == MANDELBROT)
			pthread_create(&(p->pthread[i]), NULL, calc_mandel, &(p->tdata[i]));
		else
			pthread_create(&(p->pthread[i]), NULL, calc_fract, &(p->tdata[i]));
		++i;
	}
}
