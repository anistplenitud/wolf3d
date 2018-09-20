/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amampuru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 15:51:18 by amampuru          #+#    #+#             */
/*   Updated: 2018/08/28 09:55:27 by amampuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	int		load_truck(t_player fps)
{
	SDL_Surface	*surface;
	SDL_Texture	*tex;

	surface = IMG_Load("truck.xpm");
	if (!surface)
	{
		ft_putstr("Error Creating SDL_Surface\n");
		return (-1);
	}
	tex = SDL_CreateTextureFromSurface(fps.renderer, surface);
	if (!tex)
	{
		ft_putstr("Error Creating SDL_Surface\n");
		return (-1);
	}
	SDL_FreeSurface(surface);
	SDL_RenderCopy(fps.renderer, tex, NULL, NULL);
	SDL_DestroyTexture(tex);
	return (1);
}

static	void	do_rightview(t_player *fps, t_ray *ray)
{
	fps->shift = 149;
	fps->x = 170;
	while (fps->x < 300)
	{
		fps->shift--;
		fps->x++;
		ft_hwallhit(fps->x, fps, ray);
		ft_vwallhit(fps->x, fps, ray);
		ft_drawslice(fps->x, fps, ray);
	}
}

static	void	do_leftview(t_player *fps, t_ray *ray)
{
	fps->x = 0;
	fps->shift = 0;
	while (fps->x < 150)
	{
		ft_hwallhit(fps->x, fps, ray);
		ft_vwallhit(fps->x, fps, ray);
		ft_drawslice(fps->x, fps, ray);
		fps->x++;
		fps->shift++;
	}
}

static	void	clean_up(t_player fps)
{
	SDL_RenderClear(fps.renderer);
	SDL_DestroyRenderer(fps.renderer);
	SDL_DestroyWindow(fps.window);
	SDL_Quit();
}

int				main(int ac, char **av)
{
	t_ray		ray[320];
	t_player	fps;

	if (ac >= 2 && av)
	{
		ft_putstr("No program parameters are required\n");
	}
	ft_init(&fps, &ray[0]);
	while (!fps.close_requested)
	{
		while (SDL_PollEvent(&fps.event))
			ft_event(&fps, &ray[0]);
		ft_moveplayer(&fps);
		SDL_SetRenderDrawColor(fps.renderer, 0, 0, 0, 255);
		SDL_RenderClear(fps.renderer);
		SDL_SetRenderDrawColor(fps.renderer, 0, 0, 255, 255);
		do_leftview(&fps, &ray[0]);
		do_rightview(&fps, &ray[0]);
		load_truck(fps);
		SDL_RenderPresent(fps.renderer);
	}
	clean_up(fps);
	return (0);
}
