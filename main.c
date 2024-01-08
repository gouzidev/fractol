#include "header.h"

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(1);
	}
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void draw_lines(t_data *data)
{
	// draw the vertical line (0 -> HEIGHT)
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < HEIGHT)
	{
		my_mlx_pixel_put(data, WIDTH / 2, i, 0x00FFFFFF);
		if (i % UNIT == 0)
		{
			k = -20;
			while (k < 20)
			{
				my_mlx_pixel_put(data, WIDTH / 2  + k, i , 0x0000FFFF);
				k++;
			}
		}
		i++;
	}
	i = 0;
	// draw the horizontal line (0 -> WIDTH)
	while (i < WIDTH)
	{
		my_mlx_pixel_put(data, i, HEIGHT / 2, 0x00FFFFFF);
		if (i % UNIT == 0)
		{
			k = -20;
			while (k < 20)
			{
				my_mlx_pixel_put(data, i, HEIGHT / 2 + k, 0x0000FFFF);
				k++;
			}
		}
		i++;
	}
}

void draw_point(t_data *data, t_c p, unsigned int color)
{
	my_mlx_pixel_put(data, WIDTH / 2 + (p.r * UNIT), HEIGHT / 2 - (p.i * UNIT), color);
}

int	main(void)
{
	t_vars	vars;
	t_data data;
	t_c p;
	t_c c = {0.125, 0.125};
	t_c draw_p = {0, 0};
	char *dst;
	int x;
	int y;
	double i = 0;
	double j = 0;

	x =  WIDTH / 2;
	y =  HEIGHT / 2;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello world!");
	t_data img;
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_lines(&img);
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			p.r = i - 4;
			p.i = j - 4;
			draw_p.r = i * (WIDTH / 2) / 8;
			draw_p.i = j * (HEIGHT / 2) / 8;
			printf("[%f + %fi]\n", draw_p.r, draw_p.i);
			if (does_blow_up(p, c))
			{
				my_mlx_pixel_put(&img, draw_p.r, draw_p.i, 0x00FFFFFF);
			}
			else
			{
				my_mlx_pixel_put(&img, draw_p.r, draw_p.i, 0x00FF00FF);
			}
			j += 0.1;
		}
		i += 0.1;
	}

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	// t_c z1 = {0.125, 0.125};
	// t_c z2 = {-1, -1};
	// t_c z3 = {1, 0};
	// t_c z4 = {0, 0};
	// int res;
	// res =  does_blow_up(z1, z4);
	// printf("%d\n", res);

	// res =  does_blow_up(z2, z4);
	// printf("%d\n", res);

	// res =  does_blow_up(z3, z4);
	// printf("%d\n", res);
	// printf(" %f + %f reel    %fi  +  %fi  (imaginary) -> %f + %fi \n", z1.r , z2.r, z1.i, z2.i, mul_comp(z1, z2).r, mul_comp(z1, z2).i);
}