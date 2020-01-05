/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_functions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:25:54 by mbenjell          #+#    #+#             */
/*   Updated: 2019/12/10 00:08:53 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_FUNCTIONS_H
# define DOOM_FUNCTIONS_H

# include "doom_struct.h"

void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
size_t			ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
int				ft_strequ(const char *s1, const char *s2);
int				ft_get_nb(t_stream *s);
int				init_stream(t_stream *st, int fd);
int				ft_getchar(t_stream *s);
int				ft_getc(t_stream *s);
int				flusher(t_stream *s);
int				skip_space(t_stream *s);
int				fts_equal(t_stream *stream, char *s);
int				stream_to_buff(t_stream *s, char *buff);

void			ft_putc(t_stream *out, char c);

void			ft_putstr(t_stream *out, char *s);
void			flush_out(t_stream *out);

void			save_sentences(t_env *env);
void			save_player(t_env *env);
void			save_font(t_env *env);
void			save_content(t_env *env);
int				save_file(t_env *env);
void			write_value(int nb, t_stream *out);

int				extract_header(t_env *env);
int				extract_map(t_env *env);
int				extract_picture(t_env *env);
int				extract_code(t_env *env);
int				extract_param(t_stream *s);
int				extract_sound(t_env *env);
int				extract_font(t_env *env);
int				extract_interaction(t_env *env);
int				extract_player(t_env *env);
int				extract_text(t_env *env);
int				build_data(t_env *env);
void			verification(t_env *env);

int				get_val(t_stream *s, int min, int max);
int				max_val(int type_actor);

void			fill_character(t_env *env);
void			fill_object(t_env *env);
void			fill_wall(t_env *env, int current_sector);
void			fill_sector(t_env *env, int current_sector);
int				fill_vm(t_env *env, int type_actor, int i);

int				key_press(t_env *env);
int				key_release(t_env *env);
int				mouse_press(t_env *env);
int				mouse_release(t_env *env);
int				mouse_move(t_env *env);

int				key_e(t_env *env);
int				key_f(t_env *env);
int				key_r(t_env *env);
int				key_p(t_env *env);
int				key_escape(t_env *env);
int				key_s(t_env *env);
int				key_b(t_env *env);
int				key_n(t_env *env);
int				key_r(t_env *env);
int				key_w(t_env *env);
int				key_c(t_env *env);
int				key_up(t_env *env);
int				key_down(t_env *env);
int				key_right(t_env *env);
int				key_left(t_env *env);
int				key_space(t_env *env);
int				key_lctrl(t_env *e);
int				key_alt(t_env *env);

int				manage_editor(t_env *env);
int				manage_game(t_env *env);
void			manage_program(t_env *env);
int				manage_start(t_env *env);

int				start(t_env *env);
void			display_box(t_env *env, t_point p[4], int height, int here);
void			manage_level(t_player *p, int n);
void			reverse(unsigned int *n);
void			change_luminosity(t_sector *s);
void			options(t_env *env, int *option);
void			display_instruction_start(t_env *env);

int				pointer(t_env *env);
int				create_point(t_env *env);
int				open_polygon(t_env *env);
int				close_polygon(t_env *env);

void			draw_box(t_env *env, t_point p, int h, int w);
void			draw_toolbox(t_env *env, t_point p, int h, int w);

int				draw(t_env *env);

int				draw_player(t_env *env, int color);
int				update_view(t_env *env);

void			struct_direction(t_env *env);

int				malloc_render(t_env *env);
int				init_render(t_env *env);
int				render(t_env *env);

void			add_to_bunch1(t_env *env, t_wall i, t_wall j, int first);
void			add_to_bunch2(t_env *env, t_wall i, t_wall j, int first);
void			create_bunch(t_env *env);

void			push_bunch(t_env *env, int sector, int left_to_right);
int				first_bunch(t_env *env, int i);
int				next_bunch(t_env *env, int bunch, int i);

int				overlap(t_env *env, int i, int j);
int				closest_wall(t_env *env, int i, int j, int v);
int				test_height_sector(t_env *env, int i, int j, int vision);
int				closest_bunch1(t_env *env, int i, int j);

void			sort_bunch(t_env *env);
void			sort_bunch_inv(t_env *env);
void			display_sector(t_env *env);

void			add_portal(t_env *env, int j, int k);

void			init_fov(t_env *menv);
int				tcheck_fov(t_env *env, t_point a, t_point b);
int				is_in_range(t_env *env, t_wall i, t_wall j);
void			tcheck_hors_fov(t_env *env, t_wall *i, t_wall *j);
void			screen_x(t_env *env, t_wall *wall);

float			dist_wall(t_env *env, t_float a);
float			ft_dist(t_env *env, t_float point);
int				dist_bunch(t_env *env, int i, int j);

int				equal(t_point first, t_point sec);
int				left_to_right(t_player *p, t_point first, t_point sec);
void			first_wall(t_env *env, t_wall i);
int				next_j(t_env *env, int i, int sector);

int				same_wall(t_env *env, int sector, t_point j);
int				is_in_sector(t_env *env, int sector);
int				point_in_sector(t_env *env, int sector, t_point point);
int				in_which_sector(t_env *env);
int				which_sector(t_env *env, int i);

float			ft_angle(t_float a, t_float b);
t_float			find_portal(t_env *env, int sector[2], int *k, int *l);
void			line_cercle_inter(t_env *env, float p[2], t_float center,
																int port[2]);
float			calc_dist(t_env *env, t_float *perp, t_wall i, t_wall j);
void			port_same_xy(t_env *env, t_float perp, float dist, int port[2]);
void			new_cord(t_env *env);

void			display_cross(t_env *env);
void			look_around(t_env *env);
void			raycasting(t_env *env, t_wall a, t_wall b);
void			move_player(t_env *e);

int				init_view(t_env *env);
int				init_file(t_env *env);
void			run_game(t_env *env);
int				run_programme(t_env *env);
int				end_programme(t_env *env, char *msg);
void			del_render(t_env *env);

void			brush_color(t_env *env, int color);
void			point_to_grille(t_point *point);
void			display_grille(t_env *env, int layer);
void			draw_line(t_view *v, t_point *start, t_point *end);
void			draw_new_polygon(t_env *env, int select, int color);
void			draw_polygon(t_env *env, int select, int color);
void			draw_map(t_env *env, int color);
void			clear_layer(t_view *view, int layer);

void			display_ob(t_env *env, t_view *view, t_point pos);
void			display_char(t_env *env, t_view *view, t_point pos);
void			manage_color_obj(t_env *env, int index_obj);
void			manage_color_char(t_env *env, int index_character);

int				equal_points(t_point *p, t_point *q);

int				segment_inter(t_point a, t_point b, t_point c, t_point d);
int				segment_inter_f(t_point a, t_point b, t_float c, t_float d);
int				onsegment(t_point p, t_point q, t_point r);
int				onsegment_f(t_point p, t_float q, t_point r);
t_float			inter_position_f(t_point a, t_point b, t_float c, t_float d);
t_float			inter_position_f1(t_float a, t_float b, t_float c, t_float d);
void			smooth(t_env *env, t_uchar **dest, t_uchar *src1,
					t_uchar *src2);
void			segment(t_point a, t_point b, t_uchar *surface, t_uint color);

void			display_wall(t_env *env, t_wall *a, t_wall *b);
void			portal_handler(t_env *env, t_utils *u, t_texture *tex);
void			prepare_floor_ceiling(t_env *env, t_utils *u, int mode);
void			draw_f_main(t_env *env, t_utils *u, unsigned int *layer,
					t_texture *tx);
void			draw_c_main(t_env *env, t_utils *u, unsigned int *layer,
					t_texture *tx);
void			draw_wall(t_utils *u, unsigned int *layer, t_texture *tx);
void			draw_portal(t_env *env, t_utils *u, unsigned int *layer,
					t_texture *tx);
void			draw_floor(t_env *env, t_utils *u, unsigned int *layer,
					t_texture *tx);
void			draw_ceiling(t_env *env, t_utils *u, unsigned int *layer,
					t_texture *t);
void			prepare_dist(t_env *env, t_utils *u);

int				color_tex(unsigned char *pic, int p, float l);
void			fill(t_env *env);

void			setup_sprite(t_env *env);

void			display_walls(t_env *env);
void			display_textures(t_env *env);
void			display_obj(t_env *env);
void			display_sectors(t_env *env);
void			display_code(t_env *env, int type_actor);
void			display_reg(t_action *action);
void			display_sentence(t_env *env, char *str, t_point p,
					unsigned int color);
void			display_hud(t_env *env, t_hud *hud);
void			display_compass(t_env *env, float l);
void			display_inventory(t_env *env, int nb, int tex, float l);
unsigned int	adapt_luminosity(unsigned int hexa, float l);
void			choose_sentence(t_env *env);
void			plot(t_view *view, int x, int y);
int				inter_sector(t_env *env, t_sector *s, t_sector *z);
int				sector_correction(t_env *env, int sector);
int				connect_sector(t_env *env, int sector);
int				correct_sector(t_env *env);
int				correct_wall(t_env *env);
int				correct_polygon(t_env *env);

int				extract_object(t_env *env);
int				add_object(t_env *env);
int				draw_object(t_env *env, int color);
int				draw_character(t_env *env, int color);
void			manage_color(t_env *env, int index_wall);

int				hitbox_handler(t_env *e, int i);
t_bound_box		bound_box_creation(t_bound_box bb, t_float a, t_float b);
void			bound_box_p(t_env *e);

int				collision_handler(t_env *e);
int				collision_check(t_env *e);
int				int_check(t_env *e);
int				step_check(t_env *e, int i);
int				double_wall (t_env *e);
int				collision_point(t_env *e);

int				jump_handler(t_env *e);
int				fly_handler(t_env *e);
int				crouch_handler(t_env *e);
void			update_position(t_env *e);
void			p_movements(t_env *e, float mult, float div);
void			p_stand(t_env *e);
void			p_jump(t_env *e);
void			p_fly(t_env *e);
void			p_crouch(t_env *e);

int				read_instruction(t_env *env, int actor);
void			manage_instr(t_env *env, t_action *action, int *vm);
int				manage_op(t_env *env);
int				load_attribute(t_env *env, int type_actor, int n);
int				save_attribute(t_env *env, int type_actor, int n);
int				addition(int op1, int op2);
int				soustraction(int op1, int op2);
int				multiplication(int op1, int op2);
int				division(int op1, int op2);
int				compare(int op1, int op2);
float			pythagore2(float ab, float cd);
float			pythagore4(float a, float b, float c, float d);

void			save_character(t_env *env);

void			character_to_reg(t_env *env, int n, int type_actor);
void			object_to_reg(t_env *env, int n, int type_actor);
void			sector_to_reg(t_env *env, int n, int type_actor);
void			reg_to_character(t_env *env, int n, int type_actor);
void			reg_to_object(t_env *env, int n, int type_actor);
void			reg_to_sector(t_env *env, int n, int type_actor);
void			global_to_reg(t_env *env, int n, int type_actor);
void			reg_to_global(t_env *env, int n, int type_actor);

int				extract_asm(t_env *env, int type_actor);
int				animate_game(t_env *env);

int				play_sound(t_env *env, char *audio_file);

void			erase_bloc(t_view *v, t_point start, t_point end);

void			display_letter(t_env *env, int i, t_point point);
void			display_text(t_env *env, t_point point, char *text);

void			translate(t_point direction, t_point *p);
void			reverse_translate(t_point direction, t_point *p);
void			update_translation(t_env *env, t_point c);
void			move_sector(t_env *env);

void			draw_menu(t_env *env);

void			select_attribut(t_env *env, int before_next);
int				update_value(int *val, int sign, int min, int max);

void			aff_letter(t_env *env);
int				extract_number(t_env *env);
void			display_number(t_env *env, int i, t_point point);
void			display_value(t_env *env, t_point point, int value);

void			re_update_walls(t_env *e, int s);
void			update_character_extra(t_env *env, int sign);
void			update_character_z(t_env *env, int sign);
void			update_character(t_env *env, int sign);
void			update_animation(t_env *env, int sign);
void			update_object_extra(t_env *env, int sign);
void			update_object(t_env *env, int sign);
void			update_player(t_env *env, int sign);
void			update_sector_tex(t_env *env, int sign);
void			update_sector(t_env *env, int sign);
void			update_wall(t_env *env, int sign);
void			update_attribut(t_env *env);
void			centering(t_env *env);
void			center_editor(t_env *env);
void			navigation_editor(t_env *env);

int				listen_event(t_env *env, SDL_Event *event);
void			init_game(t_env *env);
int				refresh_screen(t_env *env);
int				filter_event(void *data, SDL_Event *event);
int				filter_keys(int k);
int				filter_pkeys(int k);

int				int_seg_seg(t_float p1, t_float p2, t_float p3, t_float p4);

int				available_memory(t_env *env, int data);
int				available_action(t_env *env, int actor);

void			check_object(t_env *env, t_hud *hud);
void			get_position(t_env *env, t_player *p);

void			init_automaton(t_env *env);
void			init_hud(t_env *env);
void			init_player(t_env *env);
void			init_fps(t_env *env);

void			test_shoot(t_env *env);

#endif
