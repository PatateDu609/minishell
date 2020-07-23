################################################################################
#                               Name of the output                             #
################################################################################
NAME				=	minishell

################################################################################
#                          Paths of sources and objects                        #
################################################################################
PATH_INCLUDES		=	include
PATH_SRCS			=	srcs
PATH_OBJS			=	objs
PATH_LIBS			=	libs

################################################################################
#                                 Libft's infos                                #
################################################################################
LIBFT_PATH			=	libft
LIBFT_MAKE			=	Makefile
LIBFT				=	$(PATH_LIBS)/libft.a

################################################################################
#                              Name of sources files                           #
################################################################################
PARSER_PATH			=	parser

PARSER_SRCS			=	ft_parser			\
						ft_parser_utils		\

PARSER_BONUS_SRCS	=	ft_parser_utils		\

SRCS_BASENAME		+=	$(addprefix $(PARSER_PATH)/, $(PARSER_SRCS))
SRCS_BASENAME		+=	main

ifeq ($(BONUS), 1)
	BONUS_BASE_NAME	+=	$(addsuffix _bonus, $(PARSER_BONUS_SRCS))
	SRCS_BASENAME	+=	$(addprefix $(PARSER_PATH)/, $(BONUS_BASE_NAME))
endif

################################################################################
#                             Commands and arguments                           #
################################################################################
RM					=	@rm -f
GCC					=	@gcc
CFLAGS				=	-Wall -Wextra -Werror -g -I$(PATH_INCLUDES)
LDFLAGS				=	-L$(PATH_LIBS) -lft

# DEBUG LDFLAGS :
# LDFLAGS				+=	-fsanitize=address -g -fstack-protector

################################################################################
#                         DO NOT MODIFY BELOW THIS POINT                       #
################################################################################
SRCS_EXT			=	$(addsuffix .c, $(SRCS_BASENAME))

SRCS				=	$(addprefix $(PATH_SRCS)/, $(SRCS_EXT))
OBJS				=	$(addprefix $(PATH_OBJS)/, $(SRCS_EXT:.c=.o))

OS					=	$(shell uname -o)
ifeq ($(OS), GNU/Linux)
	CFLAGS			+=	-DLINUX
	# LDFLAGS			+=	-fsanitize=leak
endif

ifeq ($(BONUS), 1)
	CFLAGS			+= -DBONUS
endif

$(PATH_OBJS)/%.o:	$(PATH_SRCS)/%.c
					$(GCC) $(CFLAGS) -c $< -o $@

$(NAME):			enter_name $(PATH_LIBS) $(PATH_OBJS) $(LIBFT) enter_objs $(OBJS)
					@echo "\e[46;90;1mLinking everything\e[0m"
					$(GCC) $(OBJS)  -o $(NAME) $(LDFLAGS)

$(LIBFT):			enter_libft
					@make -C $(LIBFT_PATH) -f $(LIBFT_MAKE)

$(MINILIBX):
					@make -C $(MINILIBX_PATH) -f $(MINILIBX_MAKE)

$(PATH_LIBS):
					@echo "\e[92mCreating libs folder\e[0m"
					@mkdir -p $(PATH_LIBS)

$(PATH_OBJS):
					@echo "\e[92mCreating objs folders\e[0m"
					@mkdir -p $(PATH_OBJS)/libft
					@mkdir -p $(PATH_OBJS)/$(PARSER_PATH)

all:				$(NAME)

libft:				$(LIBFT)

re:					fclean all

bonus:				fclean $(PATH_OBJS_BONUS)
					@make BONUS=1

.PHONY:				all clean fclean re libft

libft:				$(LIBFT)

clean:
					$(RM) $(OBJS)
					@make -C $(LIBFT_PATH) -f $(LIBFT_MAKE) clean

fclean:				clean
					$(RM) -r $(PATH_OBJS) $(PATH_LIBS)
					@make -C $(LIBFT_PATH) -f $(LIBFT_MAKE) fclean

enter_name:
					@echo -n "\e[31mMaking \e[1m$(NAME)\e[0m"
ifeq ($(BONUS), 1)
					@echo -n "\e[31m with bonuses\e[0m"
endif
					@echo ""

enter_libft:
					@echo "\e[92mMaking libft\e[0m"

enter_objs:
					@echo "\e[92mCompiling objs\e[0m"

.PHONY:				all clean fclean re libft
