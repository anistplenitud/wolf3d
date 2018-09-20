/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_turnright.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amampuru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 13:57:56 by amampuru          #+#    #+#             */
/*   Updated: 2018/08/27 14:56:29 by amampuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	ft_turnright(t_player *fps, t_ray *ray)
{
	fps->rangle -= fps->turn;
	fps->x = 0;
	while (fps->x < 320)
	{
		if (ray[fps->x].ydir == fps->ydir && ray[fps->x].xdir == fps->xdir)
			ray[fps->x].rangle -= fps->turn;
		else if (ray[fps->x].ydir == 'd' && ray[fps->x].xdir == 'l')
			ray[fps->x].rangle -= fps->turn;
		else
			ray[fps->x].rangle += fps->turn;
		fps->x++;
	}
	return (1);
}
