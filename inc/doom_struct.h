/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmenant <bmenant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:05:05 by bmenant           #+#    #+#             */
/*   Updated: 2019/12/09 23:41:27 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_STRUCT_H
# define DOOM_STRUCT_H

# include "doom_define.h"

typedef unsigned char		t_uchar;
typedef unsigned int		t_uint;

typedef struct s_env		t_env;
typedef int					t_pf(t_env *env);
typedef int					t_pg(int a, int b);

typedef	enum				e_player_state
{
	stand,
	jump,
	fly,
	crouch
}							t_player_state;

typedef enum				e_block
{
	file,
	header,
	level,
	player,
	map,
	picture,
	element,
	instruction,
	sound,
	font,
	number,
	data,
	text
}							t_block;

typedef enum				e_mode
{
	mode_editor,
	mode_game,
	mode_start
}							t_mode;

typedef enum				e_event
{
	silent,
	press,
	release,
	move
}							t_event;

typedef enum				e_automate
{
	parser,
	trace,
	rendu
}							t_automate;

typedef enum				e_trace
{
	cursor,
	start_point,
	paint,
	draw_on,
	draw_off,
	rubber_on
}							t_trace;

typedef enum				e_rendu
{
	choose_sector,
	r_silent,
	move_mouse
}							t_rendu;

typedef enum				e_currentbunch
{
	e_b,
	e_w,
	e_portal
}							t_currentbunch;

typedef enum				e_vis
{
	visible,
	invisible
}							t_vis;

typedef enum				e_layer
{
	editor_layer,
	render_layer,
	menu_layer,
}							t_layer;

typedef enum				e_content
{
	e_sector,
	e_wall,
	e_object,
	e_character,
	e_player,
	e_texture,
	e_all
}							t_content;

typedef enum				e_op
{
	e_add,
	e_sub,
	e_mul,
	e_div,
	e_cmp,
	e_if,
}							t_op;

typedef struct				s_point
{
	int						x;
	int						y;
}							t_point;

typedef struct				s_float
{
	float					x;
	float					y;
	float					z;
}							t_float;

typedef struct				s_stream
{
	char					*file_name;
	int						fd;
	char					buff[BUFFER_SIZE];
	int						i;
	int						nread;
}							t_stream;

typedef struct				s_texture
{
	unsigned char			picture[MAX_PIXEL * MAX_PIXEL * 4];
	int						w;
	int						h;
	float					size;
}							t_texture;

typedef struct				s_player
{
	t_float					pos;
	t_float					old_pos;
	t_float					dir;
	t_float					tmp_pos;
	t_float					tmp_dir;
	t_float					mov;
	t_float					perp;
	t_float					left;
	t_float					right;
	int						sector;
	float					cam;
	t_player_state			state;
	int						avatar;
	int						life;
	int						speed;
	int						ray;
	int						current_level;
	int						new_level;
	int						nb_levels;
	t_float					levels[NB_LEVELS];
	int						fly_mov;
	int						old_fly_mov;
	int						total_time;
	int						timer;
	int						sprint;
	int						wings;
	int						gun;
}							t_player;

typedef struct				s_view
{
	char					*layer[4];
	int						current_layer;
	int						main_layer;
	unsigned int			color;
}							t_view;

typedef struct				s_wall
{
	t_point					pos;
	int						sector;
	int						next_sector;
	int						texture;
	int						floor;
	int						ceiling;
	int						screenx;
	float					dist;
	t_float					p;
	t_point					previous_pos;
}							t_wall;

typedef struct				s_object
{
	t_point					pos;
	int						z;
	t_wall					a;
	t_wall					b;
	int						pickable;
	int						color;
	int						reaction;
	int						animated;
	int						alert;
	int						prio;
	int						nl;
	int						effect;
}							t_object;

typedef struct				s_character
{
	t_object				o;
	t_float					dir;
	int						texture[4];
	int						color;
	int						reaction;
	int						animated;
	int						dead;
}							t_character;

typedef struct				s_sentence
{
	char					str[NB_CHARS + 1];
	t_point					p;
	unsigned int			color;
	int						obj;
}							t_sentence;

typedef struct				s_utils
{
	t_wall					a;
	t_wall					b;
	t_point					old_a;
	t_point					old_b;
	float					pente;
	float					k;
	int						screenx;
	float					height;
	int						start;
	int						end;
	int						old_end;
	int						w;
	t_float					dir;
	float					inc;
	float					tex_u[3];
	float					dist[4][SIDE];
	float					lum;
	float					coeff;
	t_point					corner;
}							t_utils;

typedef struct				s_sector
{
	int						index;
	int						start_wall;
	int						num_walls;
	int						floor;
	int						ceiling;
	int						tex_f;
	int						tex_c;
	int						reaction;
	float					luminosity;
	int						light;
	int						alert;
	int						animated;
	int						count;
}							t_sector;

typedef struct				s_editor
{
	t_point					center;
	t_point					cursor;
	t_point					old_cursor;
	t_point					start_line;
	t_point					start_polygon;
	int						draw_on;
	int						select_mode;
	int						select[NB_ACTORS];
	t_point					direction;
	unsigned int			color_text;
	int						attribut_value;
	int						attribut[NB_ACTORS][NB_ATTRIBUTS];
	t_point					p;
	t_point					q;
	t_point					end;
}							t_editor;

typedef struct				s_w
{
	t_wall					w;
	int						next;
}							t_w;

typedef struct				s_bunch
{
	int						start_wall;
	int						sector;
	int						inv;
	int						inv1;
	int						next;
}							t_bunch;

typedef	struct				s_portal
{
	t_wall					i;
	t_wall					j;
	t_float					pos;
	t_float					dir;
	int						sector;
	int						next;
}							t_portal;

typedef struct				s_render
{
	t_w						*wall[2];
	t_bunch					*bunch[2];
	t_portal				*portal;
	int						p[SIDE];
	int						w[SIDE];
	int						first_bunch[2];
	int						first_portal;
	int						cur[2][3];
	t_wall					i;
	t_wall					j;
	int						sector;
	int						see;
	int						euc;
	int						port;
	int						all;
}							t_render;

typedef struct				s_col
{
	t_float					dir;
	t_float					p1;
	t_float					p2;
	t_float					p3;
	t_float					p4;
	float					a1;
	float					a2;
	float					b1;
	float					b2;
	float					x;
	float					y;
	float					l;
	float					k;
	float					sx;
	float					sy;
	int						current_wall;
}							t_col;

typedef struct				s_bound_box
{
	t_float					min;
	t_float					max;
}							t_bound_box;

typedef struct				s_fps_count
{
	int						startclock;
	int						deltaclock;
	int						current_fps;
}							t_fps_count;

typedef struct				s_option
{
	unsigned int			editor;
	unsigned int			thread;
}							t_option;

typedef struct				s_hud
{
	int						compass;
	int						timer;
	unsigned int			nb_inventory;
	int						inventory[8];
	int						bu[8];
	int						current_slot;
}							t_hud;

typedef struct				s_notify
{
	int						type;
	int						duration;
}							t_notify;

typedef struct				s_action
{
	int						type;
	int						duration;
	int						size_code;
	int						mini_vm[VM_SIZE];
	int						pc;
	int						registre[NB_REGISTERS];
}							t_action;

typedef struct				s_subject
{
	int						i;
	int						type_actor;
	int						notif;
}							t_subject;

typedef struct				s_observer
{
	int						i;
	int						type_actor;
	int						wake_up;
	int						nb_subject;
	int						reaction;
	int						subject[NB_SUBJECT];
}							t_observer;

struct						s_env
{
	char					**envp;
	char					*argv[2];
	SDL_Window				*win;
	SDL_Renderer			*render;
	SDL_Texture				*screen;
	SDL_Event				event;
	char					*file_name;
	t_stream				stream;
	t_stream				stream_out;
	t_view					view;
	t_editor				editor;
	t_sector				sector[NB_SECTORS];
	t_wall					wall[NB_WALLS];
	t_texture				texture[NB_TEXTURES];
	t_object				object[NB_OBJECTS];
	t_character				character[NB_CHARACTERS];
	t_subject				subject[NB_SUBJECT];
	t_observer				observer[NB_OBSERVER];
	t_sentence				sentence[NB_SENTENCES];
	int						nb_subject;
	int						nb_observer;
	int						nb_level;
	t_action				action[NB_ACTORS * NB_REACTIONS];
	int						card_action[NB_ACTORS];
	int						card[NB_ACTORS];
	int						current_sector;
	int						current_wall;
	int						current_texture;
	int						current_object;
	int						current_character;
	t_player				p;
	t_render				rend;
	t_bound_box				bb[NB_WALLS];
	t_bound_box				bb_player;
	t_point					mouse;
	t_pf					*pf[NB_AUTOMATES][NB_STATES];
	int						current_state[NB_AUTOMATES];
	int						activated[NB_AUTOMATES];
	int						iter_max[NB_AUTOMATES];
	t_pf					*p_controller[10];
	t_pf					*p_keys[100];
	int						keys[42];
	t_mode					mode;
	t_pf					*run_mode[3];
	t_pg					*do_op[NB_INSTRUCTIONS];
	int						listen;
	t_fps_count				fps_count;
	t_col					col;
	int						letter[NB_LETTERS * WIDTH_FONT * HEIGHT_FONT];
	int						number[NB_NUMBERS * WIDTH_NUM * HEIGHT_NUM];
	t_utils					tmp[NB_THREADS];
	pthread_t				thread[NB_THREADS];
	float					jump_force;
	float					fly_force;
	float					z_pos_base;
	int						thread_i;
	t_hud					hud;
	t_option				option;
	int						s_font;
	int						current_sentence;
	int						nb_sentence;
	int						col_recursive;
};

#endif
