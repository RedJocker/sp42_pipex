#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maurodri <maurodri@student.42sp...>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 20:20:04 by maurodri          #+#    #+#              #
#    Updated: 2024/04/24 09:05:03 by maurodri         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME := pipex
LIBFT_DIR := ./lib/libftx
LIBFT := $(LIBFT_DIR)/libft.a
FILES := main.c

BONUS_FILES := main_bonus.c 

OBJ_DIR := ./obj/
MANDATORY_OBJS := $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(FILES)))
BONUS_OBJS := $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(BONUS_FILES)))
DEP_FLAGS := -MP -MD
INCLUDES := -I./ -I$(LIBMLX_DIR)/include -I$(LIBFT_DIR)/includes
VPATH := ./ ./mandatory ./bonus
CFLAGS := -g3 -Wall -Wextra # -fsanitize=address -Werror 
CC := cc

ifdef WITH_BONUS
	INCLUDES := -I./bonus -I$(LIBMLX_DIR)/include -I$(LIBFT_DIR)/includes
	CLEAR := $(MANDATORY_OBJS) $(patsubst %.o, %.d, $(MANDATORY_OBJS))
	OBJS := $(BONUS_OBJS)
	ETAGS_BASE := ./bonus
	DEP_FILES := $(patsubst %.o, %.d, $(OBJS))
else
	INCLUDES := -I./mandatory -I$(LIBMLX_DIR)/include -I$(LIBFT_DIR)/includes
	CLEAR := $(BONUS_OBJS) $(patsubst %.o, %.d, $(BONUS_OBJS))
	OBJS := $(MANDATORY_OBJS)
	ETAGS_BASE := ./mandatory
endif

all: $(NAME)

$(NAME): $(OBJS) $(LIBMLX) $(LIBFT)
	rm -f $(CLEAR)
	$(CC) $(CFLAGS) $^ $(INCLUDES) -o $@
	etags $$(find $(ETAGS_BASE) -name '*.[ch]') $$(find $(LIBFT_DIR) -name '*.[ch]') --include '~/glibc/TAGS'

$(OBJS): $(OBJ_DIR)%.o : %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEP_FLAGS) -o $@ -c $< $(INCLUDES) 

$(OBJ_DIR):
	@mkdir -p $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

.PHONY: all clean fclean re bonus

bonus:
	$(MAKE) WITH_BONUS=1

clean:
	rm -fr $(OBJ_DIR) **/*~ *~ **/.#*
	$(MAKE) -C $(LIBMLX_DIR)/build clean
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEP_FILES)
