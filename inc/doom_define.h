/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_define.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmenant <bmenant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:05:05 by bmenant           #+#    #+#             */
/*   Updated: 2019/12/09 23:38:56 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_DEFINE_H
# define DOOM_DEFINE_H

# include "../include/SDL.h"

# define TITLE				"Doom Nukem"
# define SIDE				1384

# define BUFFER_SIZE		4096
# define SPACE				"\n\t "
# define SUCCESS			0
# define END				1
# define ERROR				-1
# define TRUE				1
# define FALSE				0
# define ON					1
# define OFF				0
# define X					0
# define Y					1

# define DELTA_MOVE_EDITOR	20

# define WHITE				0xFFFFFF
# define BLACK				0x000000
# define DARK_GREY			0x3C3C3C
# define RED				0xFF0000
# define GREEN				0x00FF00
# define BLUE				0x0000FF
# define YELLOW				0xFFFF33
# define DARK_RED			0x330000
# define DARK_GREEN			0x003300
# define DARK_BLUE			0x000033

# define NB_WALLS			1000
# define NB_SECTORS			142
# define NB_TEXTURES		42
# define NB_OBJECTS			100
# define NB_CHARACTERS		100

# define NB_SUBJECT			100
# define NB_OBSERVER		100

# define NB_NOTIFY			42
# define NB_ACTORS			6
# define NB_REACTIONS		42
# define NB_ATTRIBUTS		7
# define NB_INSTRUCTIONS	5
# define NB_REGISTERS		184

# define NB_SENTENCES		42
# define NB_CHARS			200

# define NB_THREADS			4
# define MAX_DIST			10000

# define LABEL_REG			'r'
# define VM_SIZE			200
# define INSTRUCTION_SIZE	5

# define SPEED				1.0
# define SPEED_ANGLE		0.06

# define NB_STATES			21
# define NB_AUTOMATES		3

# define MAX_WALLS			142
# define ANGLE_VISION		0.52359877559
# define FOV 				60

# define DEFAULT_CEILING	100

# define NB_LEVELS			10

# define BIN_PLAYER_AUDIO	"/usr/bin/afplay"

# define NB_LETTERS			26
# define WIDTH_FONT			7
# define HEIGHT_FONT		6
# define NB_NUMBERS			11
# define WIDTH_NUM			7
# define HEIGHT_NUM			7
# define SIZE_LINE			25
# define MARGIN				10

# define GRAV_FORCE			-10
# define JUMP_FORCE			4
# define FLY_FORCE			3

# define MIN_ALTITUDE		-10000
# define MAX_ALTITUDE		10000

# define PRECISION			1000000000
# define MAX_PIXEL		    512

#endif
