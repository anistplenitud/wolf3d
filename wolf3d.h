/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amampuru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 12:15:32 by amampuru          #+#    #+#             */
/*   Updated: 2018/08/28 08:41:10 by amampuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "SDL.h"
# include "SDL_image.h"
# include "libft/libft.h"
# include <math.h>

typedef struct		s_player
{
	int				xdir;
	int				ydir;
	float			rview;
	float			pov;
	float			rangle;
	float			x_pos;
	float			y_pos;
	int				up;
	int				down;
	int				left;
	int				right;
	float			turn;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	Uint32			render_flags;
	SDL_Event		event;
	int				x;
	int				y;
	int				shift;
	int				r;
	char			*map[10];
	int				close_requested;
}					t_player;

typedef struct		s_ray
{
	float		theta;
	float		pov;
	float		phi;
	float		inpov;
	float		rview;
	float		rangle;
	char		xdir;
	char		ydir;
	int			quadrant;
	int			fromq;
	int			xa;
	int			ya;
	float		hx;
	float		hy;
	float		vx;
	float		vy;
	float		wallheight;
	float		dv;
	float		dh;
	float		distancetowall;
	int			hitwall;
	int			ch;
	float		i;
	float		j;
	float		inew;
	float		jnew;
	int			gridx;
	int			gridy;
}					t_ray;

void				ft_dosv(double x1, double y1, double x2, double y2,\
		SDL_Renderer *r);
void				ft_dos(double x1, double y1, double x2, double y2,\
		SDL_Renderer *r);
int					ft_init(t_player *fps_ptr, t_ray *ray);
int					ft_hwallhit(int x, t_player *fps, t_ray *ray);
int					ft_vwallhit(int x, t_player *fps, t_ray *ray);
int					ft_drawslice(int x, t_player *fps, t_ray *ray);
int					ft_turnleft(t_player *fps, t_ray *ray);
int					ft_turnright(t_player *fps, t_ray *ray);
int					ft_event(t_player *fps, t_ray *ray);
int					ft_moveplayer(t_player *fps);
# define WINDOW_WIDTH (300)
# define WINDOW_HEIGHT (480)
# define SPEED (1)
# define TILE (64)
#endif
