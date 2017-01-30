/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 08:30:59 by jubarbie          #+#    #+#             */
/*   Updated: 2017/01/30 18:04:47 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Initialize light ray parameters
** This function is called for every pixel of the calculated image
*/

static void	init_light_ray(t_param *param, t_object *light)
{
	t_v3d	tmp;

	PHO_RAY.pos = light->pos;
	tmp = sub_v3d(VW_RAY.inter, PHO_RAY.pos);
	PHO_RAY.dist = length_v3d(tmp);
	PHO_RAY.dir = unit_v3d(tmp);
	PHO_RAY.obj = NULL;
}

/*
** Perform the shininess
*/

void		do_shininess(t_param *param, t_object *light, t_hsv *hsv, t_v3d ref)
{
	int		color;
	double	angle_ref;

	if (VW_RAY.obj->mat.shine > 0.0)
	{
		angle_ref = cos_v3d(ref, VW_RAY.dir);
		if (angle_ref <= -0.95)
		{
			color = hsv_to_rgb(hsv->h, hsv->s, hsv->v);
			color = add_color(color, light->color, ((-0.95 - angle_ref) / 0.05)
					* VW_RAY.obj->mat.shine);
			rgb_to_hsv(color, &hsv->h, &hsv->s, &hsv->v);
		}
	}
}

/*
** Perform lights
*/

t_rgb		modify_color(t_v3d inter, double coef, double diffuse);
t_rgb		color_damier(t_v3d inter);

void		apply_light(t_env *e, t_param *param)
{
	t_list		*lst_light;
	t_list		*lst_obj;
	t_object	*obj;
	t_hsv		hsv;
	double		vm;
	double		intensite;
//	double			cc = 0;
	intensite = 0;
	t_rgb rgb;

	if (VW_RAY.obj->pro && modify_color_for_tex(VW_RAY.obj->pro, \
					sub_v3d(VW_RAY.inter, VW_RAY.obj->pos), &rgb))
		hsv = my_rgb_to_hsv(rgb);
				//	hsv = my_rgb_to_hsv(color_damier(sub_v3d(VW_RAY.inter, VW_RAY.obj->pos)));
	else
		rgb_to_hsv(VW_RAY.obj->color, &hsv.h, &hsv.s, &hsv.v);
	vm = hsv.v;
	if (!OPT_1)
		hsv.v = VW_RAY.obj->mat.diffuse;
	lst_light = e->scene->light;
	while (lst_light)
	{
		lst_obj = e->scene->obj;
		init_light_ray(param, (t_object *)lst_light->content);
		while (lst_obj)
		{
			obj = (t_object *)lst_obj->content;
			if (obj != VW_RAY.obj)
				(*(e->obj_fct_obj[obj->type]))(obj, &PHO_RAY, &SOL);
			lst_obj = lst_obj->next;
		}
		get_color(obj->type, e, param, (t_object *)lst_light->content, &hsv, &intensite);
		lst_light = lst_light->next;
	}
	if (!OPT_1)
		COLOR = hsv_to_rgb(hsv.h, hsv.s, LUMI + (hsv.v * vm));
	else
	{
		rgb = my_hsv_to_rgb(hsv);
		rgb_s_mult(&rgb, intensite);
		rgb_reg(&rgb);
		hsv = my_rgb_to_hsv(rgb);
		COLOR = hsv_to_rgb(hsv.h, hsv.s, LUMI + (hsv.v * vm));
	}
}
