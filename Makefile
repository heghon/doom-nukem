# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/23 16:23:08 by mbenjell          #+#    #+#              #
#    Updated: 2019/12/10 16:40:20 by sseneca          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =			doom.c \
				init.c \
				run.c \
				event.c \
				view.c \
				data.c \
				framing.c \
				tools_editor.c \
				extract_picture.c \
				extract_header.c \
				extract_map.c \
				extract_object.c \
				extract_instruction.c \
				extract_sound.c \
				extract_player.c \
				extract_text.c \
				model.c \
				controller.c \
				draw.c \
				editor.c \
				manager.c \
				manage_mode.c \
				manage_sdl.c \
				libft_write.c \
				libft_number.c \
				libft_stream.c \
				libft_mem.c \
				libft_str.c \
				player.c \
				save_content.c \
				sector.c \
				portal.c \
				object.c \
				add_object.c \
				character.c \
				vision.c \
				manage_instruction.c \
				extract_asm.c \
				operation.c \
				attribut.c \
				register.c \
				register_global.c \
				register_character.c \
				animation.c \
				error.c \
				sound.c \
				font.c \
				number.c \
				translation.c \
				change_sector_attributs.c \
				change_attribut.c \
				update_value.c \
				tools_menu.c \
				menu.c \
				key_efrp.c \
				key_xbn.c \
				key_arrow.c \
				tools_structure.c \
				gameplay.c \
				collision_check.c \
				intersection_check.c \
				collision_handler.c \
				hitbox_handler.c \
				double_wall.c \
				jump_handler.c \
				intersection.c \
				intersection_float.c \
				render.c \
				init_render.c \
				create_bunch.c \
				manip_bunch.c \
				sort_bunch.c \
				sort_bunch_inv.c \
				closest_bunch.c \
				closest_wall.c \
				display_render.c \
				create_portal.c \
				tcheck_fov.c \
				change_screenx.c \
				in_sector.c \
				tools_render.c \
				dist.c \
				n_euclid.c \
				tools_n_euclid.c \
				tools_display.c \
				display_core.c \
				display.c \
				display2.c \
				hud.c \
				compass.c \
				inventory.c \
				setup_sprite.c \
				start.c \
				start_options.c \
				tools_start.c \
				shoot.c \
				pick_object.c \
				verification.c \
				update_position.c \
				p_stand.c \
				p_jump.c \
				p_fly.c \
				p_crouch.c \
				int_check.c \
				choose_sentence.c

GREEN =			\033[0;32m
BLUE =			\033[1;34m
YELLOW =		\033[1;33m
WHITE =			\033[1;37m
OK =			$(GREEN)-OK-$(WHITE)

CC =			gcc
NAME =			doom-nukem

LOGIN = 		`whoami`

SRC_FILE =		./src/
OBJ_FILE =		./obj/

OBJ =			$(SRC:.c=.o)

SRCS =			$(addprefix $(SRC_FILE),$(SRC))
OBJS =			$(addprefix $(OBJ_FILE),$(OBJ))

LFLAGS =		`sdl2-config --libs --cflags`
FLAGS =			-Wall -Wextra -Werror
OFLAGS =		-O3
IFLAGS =		-I ./inc/
CFLAGS =		-g3 -fsanitize=address
LIBFLAGS =		-lm -pthread

RM =			/bin/rm -f

COMPILE =		$(CC) $(OFLAGS) $(INC)

.PHONY:			all clean fclean re


all : $(NAME)

$(OBJ_FILE)%.o : $(SRC_FILE)%.c
	@mkdir $(OBJ_FILE) 2> /dev/null || true
	@$(CC) -c $(FLAGS) $(OFLAGS) -o $@ $<
	@echo "$@\r				$(OK)"

$(NAME) : $(OBJS)
	@$(CC) $(FLAGS) $(OFLAGS) $(OBJS) -o $(NAME) $(LFLAGS) $(LIBFLAGS)
	@echo "$(BLUE)-$(NAME)-\r				$(OK)"

clean :
	@rm -Rf $(OBJ_FILE)
	@echo "$(BLUE)-clean-\r				$(OK)"

fclean : clean
	@rm -f audio.mp3
	@rm -f saved_map.doom
	@rm -f $(NAME)
	@echo "$(BLUE)-fclean-\r				$(OK)"

re	: fclean all
