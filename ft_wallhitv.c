/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wallhitv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amampuru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 12:35:06 by amampuru          #+#    #+#             */
/*   Updated: 2018/08/27 15:05:20 by amampuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	void	compute_pointd(t_player *fps, t_ray *ray, int x)
{
	if (ray[x].xdir == 'r' && ray[x].ydir == 'u')
	{
		ray[x].i = (int)(fps->x_pos / TILE) * (TILE) + TILE;
		ray[x].j = fps->y_pos + (fps->x_pos - ray[x].i) * tan(ray[x].theta);
	}
	else if (ray[x].xdir == 'r' && ray[x].ydir == 'd')
	{
		ray[x].i = (int)(fps->x_pos / TILE) * (TILE) + TILE;
		ray[x].j = fps->y_pos - (fps->x_pos - ray[x].i) * tan(ray[x].theta);
	}
	else if (ray[x].xdir == 'l' && ray[x].ydir == 'd')
	{
		ray[x].i = (int)(fps->x_pos / TILE) * TILE - 1;
		ray[x].j = fps->y_pos + (fps->x_pos - ray[x].i) * tan(ray[x].theta);
	}
	else if (ray[x].xdir == 'l' && ray[x].ydir == 'u')
	{
		ray[x].i = (int)(fps->x_pos / TILE) * TILE - 1;
		ray[x].j = fps->y_pos - (fps->x_pos - ray[x].i) * tan(ray[x].theta);
	}
}

static	void	get_vertical_hit(t_player *fps, t_ray *ray, int x)
{
	while (!ray[x].hitwall && ray[x].gridy >= 0 && ray[x].gridx >= 0 &&\
			ray[x].gridx <= 31 && ray[x].gridy <= 9)
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
			ray[x].vx = ray[x].inew;
			ray[x].vy = ray[x].jnew;
		}
	}
}

int				ft_vwallhit(int x, t_player *fps, t_ray *ray)
{
	fps->r = 0;
	ray[x].hitwall = 0;
	if (ray[x].ydir == 'u')
		ray[x].ya = -TILE * tan(ray[x].theta);
	else if (ray[x].ydir == 'd')
		ray[x].ya = TILE * tan(ray[x].theta);
	if (ray[x].xdir == 'r')
		ray[x].xa = TILE;
	else if (ray[x].xdir == 'l')
		ray[x].xa = -TILE;
	compute_pointd(fps, ray, x);
	ray[x].vx = ray[x].i;
	ray[x].vy = ray[fps->x].j;
	ray[x].gridx = (int)(ray[x].i / TILE);
	ray[x].gridy = (int)(ray[x].j / TILE);
	get_vertical_hit(fps, ray, x);
	return (1);
}
