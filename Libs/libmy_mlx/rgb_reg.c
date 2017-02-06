/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_reg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 14:16:14 by mmoullec          #+#    #+#             */
/*   Updated: 2017/02/05 17:18:47 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_mlx.h"

void		rgb_reg(t_rgb *r)
{
	if (r->r > 255)
		r->r = 255;
	if (r->g > 255)
		r->g = 255;
	if (r->b > 255)
		r->b = 255;
}

void		rgb_reg_min(t_rgb *r)
{
	if (r->r < 0)
		r->r = 0;
	if (r->g < 0)
		r->g = 0;
	if (r->b < 0)
		r->b = 0;
}
