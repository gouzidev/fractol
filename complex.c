#include "header.h"

t_c sum_comp(t_c z1, t_c z2)
{
	t_c res;
	res.r = z1.r + z2.r;
	res.i = z1.i + z2.i;
	return res;
}

t_c mul_comp(t_c z1, t_c z2)
{
	t_c res;
	float a, b, c, d;
	// z1 = 4 - 4i
	// z2 = 1 + i
	// 4 * 1    +   4 * i   - 4i * 1       - 4i * 1i
	a = (z1.r * z2.r); // real
	b = (z1.r * z2.i); // imaginary
	c = (z1.i * z2.r); // imaginary
	d = (z1.i * z2.i); // real
	d *= -1;
	res.i = b + c;
	res.r = a + d;
	return res;
}

int out_of_range(t_c z)
{
	if ((z.r > 0 && z.r > MAX_ITER) || (z.i > 0 && z.i > MAX_ITER))
		return 1;
	if ((z.r < 0 && z.r < -MAX_ITER) || (z.i < 0 && z.i < -MAX_ITER))
		return 1;
	return 0;
}



int does_blow_up(t_c z0, t_c c)
{
	t_c zn;
	int i = 0;
	int is_out_of_range;

	is_out_of_range = 0;
	while (i < 100)
	{
		is_out_of_range = out_of_range(z0);
		if (is_out_of_range)
			return (1);
		zn = sum_comp(mul_comp(z0, z0), c);
		// printf("ITER[%d] -> [%f + %fi]\n",i, zn.r, zn.i);
		z0 = zn;
		i++;
	}
	return 0;
	// Z(n+1) = Z(n) + c
}