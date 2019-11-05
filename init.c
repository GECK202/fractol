/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:53:04 by vkaron            #+#    #+#             */
/*   Updated: 2019/11/05 23:42:44 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_img(t_param *p)
{
	p->s_line = 400;
	p->bpp = 32;
	p->endian = 1;
	p->img_s.w = p->w;
	p->img_s.h = p->h;
	p->img_p = mlx_new_image(p->mlx_p, p->img_s.w, p->img_s.h);
	p->img_data = (unsigned int *)mlx_get_data_addr(p->img_p, &(p->bpp),
					&(p->s_line), &(p->endian));
}

static int	init_param(t_param *p)
{
	reset_param(p);
	if (!(p->tdata = (t_pdata*)malloc(p->img_s.h * sizeof(t_pdata))))
		return (0);
	if (!(p->pthread = (pthread_t*)malloc(p->img_s.h * sizeof(pthread_t))))
	{
		free(p->tdata);
		return (0);
	}
	return (1);
}

static int	compare_name(char *file, const char *name)
{
	while (*file || *name)
	{
		if (*file != *name)
			return (0);
		++file;
		++name;
	}
	return (1);
}

static int	check_name(char *file)
{
	const char	*n1 = "Mandelbrot";
	const char	*n2 = "Julia";
	const char	*n3 = "Space";
	const char	*n4 = "Bubbles";
	const char	*n5 = "Necklace";

	if (compare_name(file, n1))
		return (MANDELBROT);
	else if (compare_name(file, n2))
		return (JULIA);
	else if (compare_name(file, n3))
		return (SPACE);
	else if (compare_name(file, n4))
		return (BUBBLES);
	else if (compare_name(file, n5))
		return (NECKLACE);
	return (0);
}

int			init(t_param *p, char *file)
{
	p->w = 1600;
	p->h = 1200;
	p->mlx_p = mlx_init();
	if (!(p->fract = check_name(file)))
		return (0);
	p->win_p = mlx_new_window(p->mlx_p, p->w, p->h, file);
	init_img(p);
	return (init_param(p));
}
