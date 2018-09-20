/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wallhit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amampuru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 13:54:03 by amampuru          #+#    #+#             */
/*   Updated: 2018/08/27 15:00:35 by amampuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	void	compute_pointa(t_player *fps, t_ray *ray, int x)
{
	if (ray[x].xdir == 'r' && ray[x].ydir == 'u')
	{
		ray[x].j = (int)(fps->y_pos / TILE) * (TILE) - 1;
		ray[x].i = fps->x_pos + (fps->y_pos - ray[x].j) / tan(ray[x].theta);
	}
	else if (ray[x].xdir == 'r' && ray[x].ydir == 'd')
	{
		ray[x].j = (int)(fps->y_pos / TILE) * (TILE) + TILE;
		ray[x].i = fps->x_pos - (fps->y_pos - ray[x].j) / tan(ray[x].theta);
	}
	else if (ray[x].xdir == 'l' && ray[x].ydir == 'd')
	{
		ray[x].j = (int)(fps->y_pos / TILE) * TILE + TILE;
		ray[x].i = fps->x_pos + (fps->y_pos - ray[x].j) / tan(ray[x].theta);
	}
	else if (ray[x].xdir == 'l' && ray[x].ydir == 'u')
	{
		ray[x].j = (int)(fps->y_pos / TILE) * (TILE) - 1;
		ray[x].i = fps->x_pos - (fps->y_pos - ray[x].j) / tan(ray[x].theta);
	}
}

static	void	get_horizontal_hit(t_player *fps, t_ray *ray, int x)
{
	fps->r = 0;
	ray[x].hitwall = 0;
	while (!ray[x].hitwall && ray[x].gridy >= 0 && ray[x].gridx >= 0\
			&& ray[x].gridy <= 9 && ray[x].gridx <= 31)
	{
		if (fps->map[ray[x].gridy][ray[x].gridx] == '#')
		{
			ray[x].hitwall = 1;
			break ;
		}
		else
		{
			fps->r++;
			ray[x].inew = ray[x].i + ray[x].xa * fps->r;
			ray[x].jnew = ray[x].j + ray[x].ya * fps->r;
			ray[x].gridx = (int)(ray[x].inew / TILE);
			ray[x].gridy = (int)(ray[x].jnew / TILE);
			ray[x].hx = ray[x].inew;
			ray[x].hy = ray[x].jnew;
		}
	}
}

static	int		do_rangle(t_ray *ray, int x)
{
	ray[x].theta = ray[x].rview - ray[x].rangle - ray[x].phi;
	if (ray[x].theta < 0.0f)
	{
		if (ray[x].ydir == 'u')
			ray[x].ydir = 'd';
		else if (ray[x].ydir == 'd')
			ray[x].ydir = 'u';
		ray[x].phi -= 0.1;
	}
	else if (ray[x].theta >= 1.555706)
	{
		if (ray[x].xdir == 'r')
			ray[x].xdir = 'l';
		else if (ray[x].xdir == 'l')
			ray[x].xdir = 'r';
		ray[x].phi += 0.1;
	}
	ray[x].theta = ray[x].rview - ray[x].rangle - ray[x].phi;
	return (1);
}

int				ft_hwallhit(int x, t_player *fps, t_ray *ray)
{
	do_rangle(ray, x);
	if (ray[x].xdir == 'r')
		ray[x].xa = TILE / tan(ray[x].theta);
	else if (ray[x].xdir == 'l')
		ray[x].xa = -(TILE / tan(ray[x].theta));
	if (ray[x].ydir == 'u')
		ray[x].ya = -TILE;
	else if (ray[x].ydir == 'd')
		ray[x].ya = TILE;
	compute_pointa(fps, ray, x);
	ray[x].hx = ray[x].i;
	ray[x].hy = ray[x].j;
	ray[x].gridx = (int)(ray[x].i / TILE);
	ray[x].gridy = (int)(ray[x].j / TILE);
	get_horizontal_hit(fps, ray, x);
	return (0);
}
