/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawslice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amampuru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 13:36:39 by amampuru          #+#    #+#             */
/*   Updated: 2018/08/28 10:08:09 by amampuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	void	drawceiling(t_player *fps, int ch, int x)
{
	int y;

	y = 0;
	while (y < ch)
	{
		SDL_SetRenderDrawColor(fps->renderer, 135, 206, 250, 255);
		SDL_RenderDrawPoint(fps->renderer, x, y);
		y++;
	}
}

static	void	drawfloor(t_player *fps, int ch, int x, float wh)
{
	int y;

	y = WINDOW_HEIGHT;
	while (y > ch + (int)(wh))
	{
		SDL_SetRenderDrawColor(fps->renderer, 73, 56, 41, 255);
		SDL_RenderDrawPoint(fps->renderer, x, y);
		y--;
	}
}

static	void	ud_color(t_player *fps, t_ray *ray, int x)
{
	if (ray[x].ydir == 'u')
		SDL_SetRenderDrawColor(fps->renderer, 150, 0, 0, 255);
	else
		SDL_SetRenderDrawColor(fps->renderer, 130, 130, 0, 255);
}

static	void	rl_color(t_player *fps, t_ray *ray, int x)
{
	if (ray[x].xdir == 'r')
		SDL_SetRenderDrawColor(fps->renderer, 0, 255, 0, 255);
	else
		SDL_SetRenderDrawColor(fps->renderer, 50, 40, 80, 255);
}

int				ft_drawslice(int x, t_player *fps, t_ray *ray)
{
	ray[x].dh = fabs(fps->x_pos - ray[x].hx) / cos(ray[x].theta);
	ray[x].dv = fabs(fps->x_pos - ray[x].vx) / cos(ray[x].theta);
	if (ray[x].dh < ray[x].dv)
	{
		ray[x].distancetowall = ray[x].dh * cos(ray[x].inpov);
		ud_color(fps, ray, x);
	}
	else
	{
		ray[x].distancetowall = ray[x].dv * cos(ray[x].inpov);
		rl_color(fps, ray, x);
	}
	ray[x].wallheight = TILE / ray[x].distancetowall * 255;
	ray[x].ch = 100 - (ray[x].wallheight / 2);
	fps->y = ray[x].ch;
	while (fps->y < 200 - ray[x].ch)
	{
		SDL_RenderDrawPoint(fps->renderer, x, fps->y);
		fps->y++;
	}
	drawceiling(fps, ray[x].ch, x);
	drawfloor(fps, ray[x].ch, x, ray[x].wallheight);
	return (1);
}
