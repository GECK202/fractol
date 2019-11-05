/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 22:03:46 by vkaron            #+#    #+#             */
/*   Updated: 2019/11/05 22:04:55 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	check_card(double x, double y)
{
	double	p;
	double	fi;
	double	pc;
	double	x2;

	x2 = x - 0.25;
	p = x2 * x2 + y * y;
	fi = atan2(y, x2);
	x2 = (0.5 - 0.5 * cos(fi));
	pc = x2 * x2;
	if (p <= pc)
		return (1);
	return (0);
}

void		*calc_mandel(void *thread_arg)
{
	t_pdata	*tdata;
	t_comp	z;
	t_comp	c;
	int		r;

	tdata = (t_pdata*)thread_arg;
	c.i = tdata->ci;
	r = 0;
	while (r < tdata->img_s.w)
	{
		c.r = ((double)(r - tdata->d.r)) / tdata->scale;
		if (check_card(c.r, tdata->ci))
			tdata->pixel[r] = 0;
		else
		{
			z.i = 0;
			z.r = 0;
			iteration_j(tdata, z, c, r);
		}
		++r;
	}
	return (0);
}
