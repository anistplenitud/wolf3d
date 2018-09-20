/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amampuru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 13:31:04 by amampuru          #+#    #+#             */
/*   Updated: 2018/08/28 09:36:51 by amampuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	void	fps_motion_init(t_player *fps)
{
	fps->up = 0;
	fps->down = 0;
	fps->left = 0;
	fps->right = 0;
	fps->close_requested = 0;
	fps->rangle = 0;
	fps->rview = M_PI / 2;
	fps->turn = (M_PI / 6) / 60 + 0.001;
	fps->x_pos = 96;
	fps->y_pos = 224;
	fps->xdir = 'r';
	fps->ydir = 'u';
}

static	int		fps_sdl_init(t_player *fps)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL2 Couldn't Initialize.\n");
		return (0);
	}
	fps->window = NULL;
	fps->window = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,\
		SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (!fps->window)
	{
		ft_putstr("SDL2 Couldn't Create Window\n");
		return (0);
	}
	fps->render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	fps->renderer = SDL_CreateRenderer(fps->window, -1, 0);
	if (!fps->renderer)
	{
		ft_putstr("Couldn't Create SDL2 Rendering tool\n");
		return (0);
	}
	SDL_SetRenderDrawColor(fps->renderer, 0, 0, 0, 0);
	return (1);
}

static	void	fps_left_init(t_player *fps, t_ray *ray)
{
	int x;
	int shift;

	x = 0;
	shift = 0;
	while (x < 160)
	{
		ray[x].phi = M_PI / 6 - shift * M_PI / 6 / 160 + 0.001;
		ray[x].theta = M_PI / 2 - ray[x].phi;
		ray[x].rview = fps->rview;
		ray[x].pov = ray[x].rview - fps->rangle;
		ray[x].xdir = 'l';
		ray[x].ydir = 'u';
		ray[x].hitwall = 0;
		ray[x].inpov = ray[x].phi;
		ray[x].rangle = fps->rangle;
		shift++;
		x++;
	}
}

static	void	fps_right_init(t_player *fps, t_ray *ray)
{
	int x;
	int shift;

	x = 160;
	shift = 159;
	while (x < 320)
	{
		ray[x].phi = M_PI / 6 - shift * M_PI / 6 / 160 + 0.001;
		ray[x].rview = fps->rview;
		ray[x].theta = ray[x].rview - ray[x].rangle - ray[x].phi;
		ray[x].pov = ray[x].rview - fps->rangle;
		ray[x].xdir = 'r';
		ray[x].ydir = 'u';
		ray[x].hitwall = 0;
		ray[x].inpov = -ray[x].phi;
		ray[x].rangle = fps->rangle;
		shift--;
		x++;
	}
}

int				ft_init(t_player *fps, t_ray *ray)
{
	fps->map[0] = "################################";
	fps->map[1] = "#..#...#.......................#";
	fps->map[2] = "#..#...#...#...................#";
	fps->map[3] = "#............#.................#";
	fps->map[4] = "#.............#................#";
	fps->map[5] = "#..............................#";
	fps->map[6] = "#..............................#";
	fps->map[7] = "#..............................#";
	fps->map[8] = "#..............................#";
	fps->map[9] = "################################";
	if (fps_sdl_init(fps) == 0)
		return (0);
	fps_motion_init(fps);
	fps_left_init(fps, ray);
	fps_right_init(fps, ray);
	return (1);
}
