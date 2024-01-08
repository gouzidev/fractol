#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define WIDTH 2200
#define HEIGHT 1600
#define UNIT 100 // 200 -> 1
#define MAX_ITER 10000

typedef struct s_i {
	float r;
	float i;
} 	t_c;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;



t_c sum_comp(t_c z1, t_c z2);
t_c mul_comp(t_c z1, t_c z2);
int does_blow_up(t_c z1, t_c z2);

int	key_hook(int keycode, t_vars *vars);