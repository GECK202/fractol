/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:12:14 by vkaron            #+#    #+#             */
/*   Updated: 2019/11/05 22:30:23 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_color	set_grad_color(int k)
{
	double	grad;
	t_color	col;

	grad = k * M_PI / 180.0;
	col.r = floor(fabs(sin(grad + M_PI / 50)) * 255);
	col.g = floor(fabs(sin(grad + M_PI / 10)) * 255);
	col.b = floor(fabs(sin(grad + M_PI / 5)) * 255);
	return (col);
}

static t_color	set_gray_color(int k)
{
	t_color	col;

	col.r = (k * 9) % 255;
	col.g = (k * 9) % 255;
	col.b = (k * 9) % 255;
	return (col);
}

unsigned int	set_color(int k, int color_type)
{
	t_color			col;
	unsigned int	color;

	color = 0;
	if (color_type < 2)
		col = set_grad_color(k);
	if (color_type > 1)
		col = set_gray_color(k);
	if (color_type > 7)
		col.r = 255;
	else if (color_type > 5)
		col.g = 255;
	else if (color_type > 3)
		col.b = 255;
	color = (col.r << 16) + (col.g << 8) + col.b;
	if (color_type % 2)
		color = 0xffffff - color;
	return (color);
}
