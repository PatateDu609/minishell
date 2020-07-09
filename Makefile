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

PARSER_SRCS			=	ft_parser	\

SRCS_BASENAME		+=	$(addprefix $(PARSER_PATH)/, $(PARSER_SRCS))
SRCS_BASENAME		+=	main

################################################################################
#                             Commands and arguments                           #
################################################################################
RM					=	rm -f
GCC					=	gcc
CFLAGS				=	-Wall -Wextra -Werror -g -I$(PATH_INCLUDES) -ltermcap
LDFLAGS				=	-L$(PATH_LIBS) -lft

# DEBUG LDFLAGS :
LDFLAGS				+=	-fsanitize=address -g -fstack-protector

################################################################################
#                         DO NOT MODIFY BELOW THIS POINT                       #
################################################################################
SRCS_EXT			=	$(addsuffix .c, $(SRCS_BASENAME))

SRCS				=	$(addprefix $(PATH_SRCS)/, $(SRCS_EXT))
OBJS				=	$(addprefix $(PATH_OBJS)/, $(SRCS_EXT:.c=.o))

OS					=	$(shell uname -o)
ifeq ($(OS), GNU/Linux)
	CFLAGS			+=	-DLINUX
	LDFLAGS			+=	-fsanitize=leak
endif


$(PATH_OBJS)/%.o:	$(PATH_SRCS)/%.c
					$(GCC) $(CFLAGS) -c $< -o $@

$(NAME):			$(PATH_LIBS) $(PATH_OBJS) $(OBJS) $(LIBFT)
					$(GCC) $(OBJS)  -o $(NAME) $(LDFLAGS)

$(LIBFT):
					make -C $(LIBFT_PATH) -f $(LIBFT_MAKE)

$(MINILIBX):
					make -C $(MINILIBX_PATH) -f $(MINILIBX_MAKE)

$(PATH_LIBS):
					mkdir -p $(PATH_LIBS)

$(PATH_OBJS):
					mkdir -p $(PATH_OBJS)/libft
					mkdir -p $(PATH_OBJS)/$(PARSER_PATH)

all:				$(NAME)

libft:				$(LIBFT)

clean:
					$(RM) $(OBJS)
					make -C $(LIBFT_PATH) -f $(LIBFT_MAKE) clean

fclean:				clean
					make -C $(LIBFT_PATH) -f $(LIBFT_MAKE) fclean

re:					fclean all

.PHONY:				all clean fclean re libft

libft:				$(LIBFT)

clean:
					$(RM) $(OBJS)
					make -C $(LIBFT_PATH) -f $(LIBFT_MAKE) clean

fclean:				clean
					$(RM) -r $(PATH_OBJS)
					make -C $(LIBFT_PATH) -f $(LIBFT_MAKE) fclean

re:					fclean all

.PHONY:				all clean fclean re libft
