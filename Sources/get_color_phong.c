/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_phong.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 21:42:32 by mmoullec          #+#    #+#             */
/*   Updated: 2017/01/26 00:03:48 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "answers.h"

#ifdef MY_MATH_H
# undef R

# ifndef ANSWERS_H
#  define ANSWERS_H
# endif

# ifndef ANSWERS
#  define ANSWERS
#  define ANGLE_LIGHT res->angle_light
#  define INTENSITE res->intensite
#  define TEST res->test
#  define OMEGA res->omega
#  define R res->r
#  define TMP res->tmp
# endif

# ifdef OPT
#  undef OPT
#  define OPT param->e->opt

void			do_phong_calcls(t_param *param, t_object *light, \
		t_hsv *hsv, t_col_res *res)
{
	TEST = smul_v3d(VW_RAY.norm, 2 * ANGLE_LIGHT);
	R = sub_v3d(TEST, PHO_RAY.dir);
	OMEGA = cos_v3d(VW_RAY.dir, R);
}

void			get_color_phong(t_param *param, t_object *light, \
		t_hsv *hsv, t_col_res *res, double *intensite)
{
	t_object	*obj_sel;

	INTENSITE += VW_RAY.obj->mat.ambient;
	if (OPT_2)
	{
		if (ANGLE_LIGHT >= 0)
			INTENSITE += (ANGLE_LIGHT * VW_RAY.obj->mat.diffuse);
	}
	do_phong_calcls(param, light, hsv, res);
	if (OPT_3)
	{
		if (OPT_O && PHO_RAY.obj)
			INTENSITE += 0;//((VW_RAY.obj->mat.specular - 0.4) * pow(OMEGA, \
		VW_RAY.obj->mat.shine));
		else
		{
				double test = (VW_RAY.obj->mat.specular * pow(OMEGA, \
							VW_RAY.obj->mat.shine));
				if (test < 0)
					INTENSITE += 0;
				else 
					INTENSITE += test;
		}
	}
	if (OPT_O && PHO_RAY.obj)
		hsv->v = hsv->v - 0.2;
	*intensite += INTENSITE;
}

#  undef OPT
#  define OPT e->opt
# endif

void			get_color_jubarbie(t_param *param, t_object *light, \
		t_col_res *res, t_hsv *hsv)
{
	t_object	*obj_sel;

	if (ANGLE_LIGHT < 0)
	{
				hsv->v -= ANGLE_LIGHT * VW_RAY.obj->mat.diffuse;
		hsv->v = fmax(VW_RAY.obj->mat.diffuse, hsv->v);
		OPT_B ? do_shininess(param, light, hsv, res->ref) : 0;
	}
	light = light + 1 - 1;
	if (OPT_O && PHO_RAY.obj)
		hsv->v = fmax(VW_RAY.obj->mat.diffuse, hsv->v - 0.1);
	if (param->e->scene->obj_focus)
	{
		obj_sel = (t_object *)param->e->scene->obj_focus->content;
		if (VW_RAY.obj == obj_sel)
			hsv->s = 0;
	}
}

void			get_color(t_env *e, t_param *param, t_object *light, t_hsv *hsv, double *intensite)
{
	t_col_res res;

	res.intensite = 0;
	res.angle_light = cos_v3d(VW_RAY.norm, PHO_RAY.dir);
	res.ref = sub_v3d(PHO_RAY.dir, smul_v3d(VW_RAY.norm, 2.0 *
				dot_v3d(PHO_RAY.dir, VW_RAY.norm)));
	if (OPT_1)
		get_color_jubarbie(param, light, &res, hsv);
	else
		get_color_phong(param, light, hsv, &res, intensite);
}

# undef R
# define R sol.res1
#endif
