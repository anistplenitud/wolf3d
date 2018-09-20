/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amampuru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 14:37:31 by amampuru          #+#    #+#             */
/*   Updated: 2018/08/27 14:41:30 by amampuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	int	key_down(t_player *fps, t_ray *ray)
{
	if (fps->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
	{
		fps->close_requested = 1;
		return (0);
	}
	else if (fps->event.key.keysym.scancode == SDL_SCANCODE_UP)
		fps->up = 1;
	else if (fps->event.key.keysym.scancode == SDL_SCANCODE_DOWN)
		fps->down = 1;
	else if (fps->event.key.keysym.scancode == SDL_SCANCODE_D)
	{
		ft_turnleft(fps, &ray[0]);
		return (2);
	}
	else if (fps->event.key.keysym.scancode == SDL_SCANCODE_A)
	{
		ft_turnright(fps, &ray[0]);
		return (3);
	}
	else if (fps->event.key.keysym.scancode == SDL_SCANCODE_LEFT)
		fps->left = 1;
	else if (fps->event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
		fps->right = 1;
	return (1);
}

int			ft_event(t_player *fps, t_ray *ray)
{
	if (fps->event.type == SDL_QUIT)
	{
		fps->close_requested = 1;
		return (0);
	}
	else if (fps->event.type == SDL_KEYDOWN)
		key_down(fps, ray);
	else if (fps->event.type == SDL_KEYUP)
	{
		if (fps->event.key.keysym.scancode == SDL_SCANCODE_DOWN)
			fps->down = 0;
		else if (fps->event.key.keysym.scancode == SDL_SCANCODE_UP)
			fps->up = 0;
		else if (fps->event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			fps->right = 0;
		else if (fps->event.key.keysym.scancode == SDL_SCANCODE_LEFT)
			fps->left = 0;
	}
	return (1);
}
