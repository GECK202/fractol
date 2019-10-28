#include "fractol.h"
 
#define DEPTH 1000

int		check_card(double x, double y)
{
	double p;
	double fi;
	double pc;
	double x2;

	x2 = x - 0.25;
	p = x2 * x2 + y * y;
	fi = atan2(y, x2);
	x2 = (0.5 - 0.5 * cos(fi));
	pc = x2 * x2;
	if (p <= pc)
		return (1);
	return (0);
}

void	*calc_mand(void *thread_arg)
{
	t_pdata *tdata;
	double zi, zr, cr, tmp;
	int r, k;
	int rd,gn,bl;
	unsigned int color;
	double grad;

	tdata = (t_pdata*)thread_arg;
	for(r = 0; r < tdata->img_w; r++)
	{
		cr = ((double)(r - tdata->dr)) / tdata->scale;
		if (check_card(cr, tdata->ci))
			color = 0xff00;
		else
		{
			zi = zr = 0.0;
			for(k = 0; k < DEPTH; k++)
			{
				tmp = zr*zr - zi*zi + cr;
				zi = 2*zr*zi + tdata->ci;
				zr = tmp;
				if (zr*zr + zi*zi > 4)
					break;
			}
			if (k < DEPTH) 
			{
				grad = k * M_PI / 180.0;
				rd=floor(fabs(sin(grad+M_PI/50))*255);
				gn=floor(fabs(sin(grad+M_PI/10))*255);
				bl=floor(fabs(sin(grad+M_PI/5))*255);
				color = (rd << 16) + (gn << 8) + bl;
				if (tdata->type_color == 1 && !(k % 2))
					color = 0xffffff - color;
			}
			else
				color = 0;
		}
		tdata->pixel[r] = color;
	}
	return (0);
}

void		init_thread(t_param *p)
{
	int i;

	for(i = 0; i < p->img_h; i++)
	{
		p->tdata[i].pixel = &(p->img_data[i * p->img_w]);
		p->tdata[i].ci = ((double)(i - p->di)) / p->scale;
		p->tdata[i].dr = p->dr;
		p->tdata[i].di = p->di;
		p->tdata[i].scale = p->scale;
		p->tdata[i].img_w = p->img_w;
		p->tdata[i].type_color = p->type_color;
		pthread_create(&(p->pthread[i]), NULL, calc_mand, &(p->tdata[i]));
	}
}

int draw_m(t_param *p) 
{ 
	int i;

	init_thread(p);
	for(i = 0; i < p->img_h; i++)
	{
		pthread_join(p->pthread[i], NULL);
	}
	p->event = 0;
	return (0);
}

void	clear_image(t_param *param)
{
	int cell;

	cell = 0;
	while (cell < param->img_h * param->img_w)
	{
		param->img_data[cell] = param->bgc;
		++cell;
	}
}

int			not_event(t_param *p)
{
	if (p->event)
	{
		clear_image(p);
		draw_m(p);
		mlx_put_image_to_window(p->mlx_p, p->win_p, p->img_p, 0, 0);
	}
	return (0);
}

int			init_param(t_param *p, char *file)
{
	p->w = 1600;
	p->h = 1200;
	p->s_line = 400;
	p->bpp = 32;
	p->endian = 1;
	p->img_w = p->w;
	p->img_h = p->h;
	p->mlx_p = mlx_init();
	p->win_p = mlx_new_window(p->mlx_p, p->w, p->h, file);
	p->img_p = mlx_new_image(p->mlx_p, p->img_w, p->img_h);
	p->img_data = (unsigned int *)mlx_get_data_addr(p->img_p, &(p->bpp),
					&(p->s_line), &(p->endian));
	p->bgc = 0;
	p->event = 1;
	p->press3 = 0;
	p->type_color = 0;
	p->dx = 0;
	p->dy = 0;
	p->scale = 200.0; 
	p->di = p->img_h / 2;
 	p->dr = p->img_w / 2;
	p->tdata = (t_pdata*)malloc(p->img_h * sizeof(t_pdata));
	p->pthread = (pthread_t*)malloc(p->img_h * sizeof(pthread_t));
	return (1);
}

int			main(int ac, char **av)
{
	t_param	*p;

	if (ac == 2)
	{
		p = (t_param *)malloc(sizeof(t_param));
		if (init_param(p, av[1]))
		{
			mlx_mouse_hook(p->win_p, mouse_down_event, (void *)p);
			mlx_loop_hook(p->mlx_p, not_event, (void *)p);
			mlx_key_hook(p->win_p, key_down_event, (void *)p);
			mlx_hook(p->win_p, 17, 0, close_win, (void *)p);
			mlx_hook(p->win_p, 6, 0, mouse_move_event, (void *)p);
			mlx_hook(p->win_p, 5, 0, mouse_up_event, (void *)p);
			mlx_loop(p->mlx_p);
			return (0);
		}
	}
	write(1, "Usage : ./fractol {type_of_fractal}\n", 36);
	return (0);
}