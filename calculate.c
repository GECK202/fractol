/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:17:55 by vkaron            #+#    #+#             */
/*   Updated: 2019/11/05 22:27:44 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		iteration_j(t_pdata *tdata, t_comp z, t_comp c, int r)
{
	int		k;
	t_comp	tmp;

	k = 0;
	while (k < tdata->depth)
	{
		tmp.i = z.i;
		tmp.r = z.r;
		z.r = tmp.r * tmp.r - tmp.i * tmp.i + c.r;
		z.i = 2 * tmp.r * tmp.i + c.i;
		if ((z.r * z.r + z.i * z.i) > 4)
			break ;
		++k;
	}
	if (k < tdata->depth)
		tdata->pixel[r] = set_color(k, tdata->type_color);
	else
		tdata->pixel[r] = 0;
}

static void	iteration_b(t_pdata *tdata, t_comp z, t_comp c, int r)
{
	int		k;
	t_comp	tmp;

	k = 0;
	while (k < tdata->depth)
	{
		tmp.i = z.i;
		tmp.r = z.r;
		z.r = cos(tmp.r) * cosh(tmp.i);
		z.i = sin(tmp.r) * sinh(tmp.i);
		tmp.r = (c.r * z.r + c.i * z.i) / (z.r * z.r + z.i * z.i);
		tmp.i = (c.r * z.i - c.i * z.r) / (z.r * z.r + z.i * z.i);
		z.r = tmp.r * tmp.r - tmp.i * tmp.i;
		z.i = tmp.r * tmp.i + tmp.i * tmp.r;
		if ((z.r * z.r + z.i * z.i) > 10)
			break ;
		++k;
	}
	if (k < tdata->depth)
		tdata->pixel[r] = set_color(k, tdata->type_color);
	else
		tdata->pixel[r] = 0;
}

static void	iteration_s(t_pdata *tdata, t_comp z, t_comp c, int r)
{
	int		k;
	t_comp	tmp;
	t_comp	tmp2;

	k = 0;
	while (k < tdata->depth)
	{
		tmp2.i = z.i;
		tmp2.r = z.r;
		tmp.i = tmp2.r * tmp2.r - tmp2.i * tmp2.i;
		tmp.r = 2 * tmp2.r * tmp2.i;
		tmp2.i = tmp.r * tmp.r - tmp.i * tmp.i;
		tmp2.r = 2 * tmp.r * tmp.i;
		z.r = tmp2.r * tmp2.r - tmp2.i * tmp2.i + c.r;
		z.i = 2 * tmp2.r * tmp2.i + c.i;
		if ((z.r * z.r + z.i * z.i) > 4)
			break ;
		++k;
	}
	if (k < tdata->depth)
		tdata->pixel[r] = set_color(k, tdata->type_color);
	else
		tdata->pixel[r] = 0;
}

void		*calc_fract(void *thread_arg)
{
	t_pdata *td;
	t_comp	c;
	t_comp	z;
	int		r;

	td = (t_pdata*)thread_arg;
	r = 0;
	while (r < td->img_s.w)
	{
		c.r = td->posy;
		c.i = td->posx;
		z.r = ((double)td->img_s.w / td->img_s.h) * (r - td->img_s.w * 0.5) /
			(0.001 * td->scale * td->img_s.w) - ((td->d.r - td->img_s.w /
			2.0) / td->scale);
		z.i = ((double)td->i - td->img_s.h * 0.5) / (0.001 * td->scale *
			td->img_s.h) - ((td->d.i - td->img_s.h / 2.0) / td->scale);
		if (td->fract == JULIA)
			iteration_j(td, z, c, r);
		else if (td->fract == SPACE)
			iteration_s(td, z, c, r);
		else if (td->fract >= BUBBLES)
			iteration_b(td, z, c, r);
		++r;
	}
	return (0);
}
