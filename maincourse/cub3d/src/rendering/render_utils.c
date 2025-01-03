/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:55:00 by gcrepin           #+#    #+#             */
/*   Updated: 2024/04/10 16:02:47 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"

unsigned int	ceiling_color(t_cub *data)
{
	return (data->config.ceiling_color_r << 24
		| data->config.ceiling_color_g << 16
		| data->config.ceiling_color_b << 8 | 0xFF);
}

unsigned int	floor_color(t_cub *data)
{
	return (data->config.floor_color_r << 24
		| data->config.floor_color_g << 16
		| data->config.floor_color_b << 8 | 0xFF);
}

double	pythagorean(double a, double b)
{
	return (sqrt(pow(a, 2) + pow(b, 2)));
}

unsigned int	get_pixel_color(mlx_texture_t *image, int x, int y)
{
	unsigned char	*pixel;

	pixel = &image->pixels[(y * image->width + x) * 4];
	return ((unsigned int)(pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8
		| pixel[3]));
}

double	delta_time(bool update)
{
	static double	current_time = 0;
	static double	last_time = 0;
	double			delta_time;

	if (update)
	{
		last_time = current_time;
		current_time = mlx_get_time();
		return (0);
	}
	delta_time = current_time - last_time;
	return (delta_time);
}
