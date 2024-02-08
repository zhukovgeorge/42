#include "fractol.h"

void	mlx_setup(t_fractol *frctl)
{
	frctl->mlx = mlx_init(WIDTH, HEIGHT, "fractol", false);
	frctl->img = mlx_new_image(frctl->mlx, WIDTH, HEIGHT);
}

void	mouse_scroll_whell(double xdelta, double ydelta, void *param)
{
	t_fractol			*frctl;

	frctl = (t_fractol *)param;
	if (xdelta == 0)
		;
	frctl->zoom = 300;
	if (ydelta > 0)
	{
		frctl->ymin *= 0.95;
		frctl->ymax *= 0.95;
		frctl->xmin *= 0.95;
		frctl->xmax *= 0.95;
		frctl->zoom *= 0.95;
	}
	frctl->zoom = 300;
	if (ydelta < 0)
	{
		frctl->ymin *= 1.05;
		frctl->ymax *= 1.05;
		frctl->xmin *= 1.05;
		frctl->xmax *= 1.05;
		frctl->zoom *= 0.8;
	}
	mandelbrot(frctl);
}

int32_t	main(int32_t argc, const char *argv[])
{
	t_fractol	*frctl = (t_fractol *)malloc(sizeof(t_fractol));
	(void) argc;
	(void) argv;

	mlx_setup(frctl);
	mandelbrot_init(frctl);
	mandelbrot(frctl);
	mlx_scroll_hook(frctl->mlx, &mouse_scroll_whell, frctl);
	mlx_loop(frctl->mlx);
	mlx_terminate(frctl->mlx);
	return (EXIT_SUCCESS);
}
