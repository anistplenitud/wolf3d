/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moveplayer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amampuru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 14:24:59 by amampuru          #+#    #+#             */
/*   Updated: 2018/08/27 14:58:21 by amampuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	ft_moveplayer(t_player *fps)
{
	fps->pov = fps->rview - fps->rangle;
	if (fps->up && !fps->down)
	{
		fps->x_pos += cos(fps->pov) * SPEED;
		fps->y_pos -= sin(fps->pov) * SPEED;
	}
	if (fps->down && !fps->up)
	{
		fps->x_pos -= cos(fps->pov) * SPEED;
		fps->y_pos += sin(fps->pov) * SPEED;
	}
	if (fps->left && !fps->right)
		fps->x_pos -= SPEED;
	if (fps->right && !fps->left)
		fps->x_pos += SPEED;
	if (fps->x_pos <= 0)
		fps->x_pos = 0;
	if (fps->y_pos <= 0)
		fps->y_pos = 0;
	if (fps->x_pos >= TILE * 32)
		fps->x_pos = TILE * 32;
	if (fps->y_pos >= 10 * TILE)
		fps->y_pos = 10 * TILE;
	return (0);
}
