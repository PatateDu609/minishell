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
EXEC_PATH			=	exec
ENV_PATH			=	env
EXPAND_PATH			=	expand
TERMCAP_PATH		=	termcaps

EXEC_SRCS			=	signal_handling			\
						ft_construct_path		\
						ft_check_command		\
						ft_exec					\
						ft_pipe					\
						ft_redir_utils			\
						ft_apply_redir			\
						ft_redirect				\
						error					\
						ft_builtins_dir			\
						ft_builtins_exit		\
						ft_builtins_env			\
						ft_builtins_echo		\
						ft_builtins				\
						ft_builtins_utils		\

PARSER_SRCS			=	array_utils				\
						check					\
						clear					\
						command_utils			\
						ft_parser				\
						print					\
						quotes					\
						size					\
						tokenizer				\
						utils					\
						ft_init_parsing			\
						# debug					\

ENV_SRCS			=	ft_env					\
						ft_getvar				\
						ft_env_var				\
						ft_merge_env			\

EXPAND_SRCS			=	ft_expand				\
						ft_expanded_str			\
						ft_expand_env			\
						ft_expand_backslashs	\
						ft_quote_removal		\
						clear					\
						utils					\

TERMCAP_SRCS		=	init					\
						edit_line				\
						edit_line_utils			\
						getline					\
						history					\


SRCS_BASENAME		+=	$(addprefix $(PARSER_PATH)/, $(PARSER_SRCS))
SRCS_BASENAME		+=	$(addprefix $(EXPAND_PATH)/, $(EXPAND_SRCS))
SRCS_BASENAME		+=	$(addprefix $(EXEC_PATH)/, $(EXEC_SRCS))
SRCS_BASENAME		+=	$(addprefix $(ENV_PATH)/, $(ENV_SRCS))
SRCS_BASENAME		+=	main				\
						# init_debug			\

BONUS_BASENAME		+=	$(addprefix $(TERMCAP_PATH)/, $(addsuffix _bonus, $(TERMCAP_SRCS)))
BONUS_BASENAME		+=	main_bonus

################################################################################
#                             Commands and arguments                           #
################################################################################
RM					=	@rm -f
GCC					=	@gcc
CFLAGS				=	-Wall -Wextra -Werror -g -I$(PATH_INCLUDES)
LDFLAGS				=	-L$(PATH_LIBS) -lft

# DEBUG LDFLAGS :
LDFLAGS				+=	-fsanitize=address -g -fstack-protector

################################################################################
#                         DO NOT MODIFY BELOW THIS POINT                       #
################################################################################
ifeq ($(BONUS), 1)
	CFLAGS			+=	-DBONUS
	SRCS_BASENAME	+=	$(BONUS_BASENAME)
	LDFLAGS			+=	-ltermcap
endif

SRCS_EXT			=	$(addsuffix .c, $(SRCS_BASENAME))

SRCS				=	$(addprefix $(PATH_SRCS)/, $(SRCS_EXT))
OBJS				=	$(addprefix $(PATH_OBJS)/, $(SRCS_EXT:.c=.o))

$(PATH_OBJS)/%.o:	$(PATH_SRCS)/%.c
					$(GCC) $(CFLAGS) -c $< -o $@

$(NAME):			enter_name $(PATH_LIBS) $(PATH_OBJS) $(LIBFT) enter_objs $(OBJS)
					@echo "\033[46;90;1mLinking everything\033[0m"
					$(GCC) $(OBJS) -o $(NAME) $(LDFLAGS)

$(LIBFT):			enter_libft
					@make -C $(LIBFT_PATH) -f $(LIBFT_MAKE)

$(MINILIBX):
					@make -C $(MINILIBX_PATH) -f $(MINILIBX_MAKE)

$(PATH_LIBS):
					@echo "\033[92mCreating libs folder\033[0m"
					@mkdir -p $(PATH_LIBS)

$(PATH_OBJS):
					@echo "\033[92mCreating objs folders\033[0m"
					@mkdir -p $(PATH_OBJS)/libft
					@mkdir -p $(PATH_OBJS)/$(PARSER_PATH)
					@mkdir -p $(PATH_OBJS)/$(ENV_PATH)
					@mkdir -p $(PATH_OBJS)/$(EXPAND_PATH)
					@mkdir -p $(PATH_OBJS)/$(EXEC_PATH)
					@mkdir -p $(PATH_OBJS)/$(EXEC_BUILTIN_PATH)
					@mkdir -p $(PATH_OBJS)/$(TERMCAP_PATH)

all:				$(NAME)

libft:				$(LIBFT)
					@mv $(LIBFT) $(PATH_LIBS)

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
ifeq ($(BONUS), 1)
					@echo "\033[31mMaking \033[1m$(NAME)\033[0m\033[31m with bonuses\033[0m"
else
					@echo "\033[31mMaking \033[1m$(NAME)\033[0m"
endif

enter_libft:
					@echo "\033[92mMaking libft\033[0m"

enter_objs:
					@echo "\033[92mCompiling objs\033[0m"

.PHONY:				all clean fclean re libft
