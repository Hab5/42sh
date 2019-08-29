# ---------- #
# Debug mode #
# ---------- #

DEBUG = no

# --------- #
# Directory #
# --------- #

LIBDIR = libft/
PATHLIBDIR = libft/libs/
SRCDIR = srcs/
OBJDIR = objs/
INCDIR = includes/
INCLIBDIR = libft/includes/

VPATH = objs:\
		srcs:\
		srcs/lexer:\
		srcs/lexer/dll_lex:\
		srcs/lexer/token:\
		srcs/prompt:\
		srcs/prompt/edition:\
		srcs/prompt/history:\
		srcs/prompt/history/fc:\
		srcs/prompt/multiline:\
		srcs/prompt/others:\
		srcs/prompt/selection:\
		srcs/parser:\
		srcs/parser/pre_parser:\
		srcs/parser/pre_parser/handle_quotes:\
		srcs/parser/pre_parser/simple_command:\
		srcs/parser/pre_parser/remove_space:\
		srcs/parser/pre_parser/redirect:\
		srcs/parser/pre_parser/redirect/grammar:\
		srcs/parser/ast:\
		srcs/parser/command:\
		srcs/commands:\
		srcs/job_control:\
		srcs/environnement:\
		srcs/cleaning:\
		srcs/interpreter:\
		srcs/builtins:\
		srcs/builtins/bt_jobs:\
		srcs/builtins/bt_test:\
		srcs/redirection:\
		srcs/hash_table\
		srcs/history_alias_expand:

# ------------------ #
# Compiler and flags #
# ------------------ #

CC = cc
ifeq ($(DEBUG), yes)
	CFLAGS = -Wall -Wextra
else
	CFLAGS = -Wall -Wextra -Werror
endif
CPPFLAGS = -I $(INCDIR) -I $(INCLIBDIR)
LDLIBS = -lft
LDFLAGS = -L $(PATHLIBDIR)
LFLAGS = -lncurses

# --------------- #
# Different names #
# --------------- #

NAME = 42sh

SRCS_NAMES = main.c \
			 setup_main.c \
			 lexer.c \
			 lex_check.c \
			 types.c \
			 dll_new.c \
			 dll_ins.c \
			 dll_iter.c \
			 dll_del.c \
			 token.c \
			 simple_command.c \
			 delim.c \
			 type_check.c \
			 attach.c \
			 cursortools.c \
			 dlist.c \
			 dlist_plus.c \
			 editiontools.c \
			 editline.c \
			 history.c \
			 history_file.c \
			 history_expand.c \
			 history_search.c \
			 fc_e_more.c \
			 fc_e.c \
			 fc_l_more.c \
			 fc_l.c \
			 fc_parse.c \
			 fc_print.c \
			 fc_s.c \
			 fc_tools.c \
			 history_fc.c \
			 prompt_tool.c \
			 prompt.c \
			 keyhook.c \
			 morekeyhook.c \
			 del_keyhook.c \
			 othertools.c \
			 stalkcursor.c \
			 terminit.c \
			 multiline.c \
			 heredoc.c \
			 text_selection.c \
			 copy_paste.c \
			 undo_selection.c \
			 delete_selection.c \
			 redirect.c \
			 clean_lex.c \
			 handle_great.c \
			 handle_great_and.c \
			 handle_and_great.c \
			 handle_append.c \
			 handle_less.c \
			 handle_less_and.c \
			 handle_heredoc.c \
			 handle_great_hyph.c \
			 handle_less_hyph.c \
			 rules_great.c \
			 is_a_redirect.c \
			 ast_parser.c \
			 ast_parser_tools.c \
			 tree_utils.c \
			 cmd_parser_tools.c \
			 cmd_parser.c \
			 builtin_env.c\
			 commands.c\
			 commands_pipe.c\
			 list_env.c\
			 free_env.c\
			 list_redirection.c\
			 manage_env.c\
			 manage_set.c\
			 manage_variable.c\
			 manage_file.c\
			 other_tools.c\
			 parser_var.c\
			 tools_env.c \
			 add_quote.c\
			 remove_space_token.c \
			 interpreter.c \
			 interpreter_tools.c \
			 clean_redir.c \
			 adding_token.c \
			 handle_stuff.c \
			 reading_tools.c \
			 if_checks.c \
			 if_greater.c \
			 bt_exit.c \
			 bt_echo.c\
			 add_job.c\
			 gest_process.c\
			 process.c\
			 shell_struct.c\
			 tools_job.c\
			 signaux.c\
			 bt_jobs.c\
			 parameter_expansion.c\
			 list_redirect.c\
			 redirection.c\
			 path.c\
			 add_process.c\
			 check_last.c\
			 formats_parameter_bis.c\
			 delete_redirection.c\
			 redirection_bis.c\
			 apply_parser_var.c\
			 free_job.c\
			 list_job.c\
			 test_quote.c\
			 remove_quote.c\
			 bt_alias.c\
			 bt_unalias.c\
			 hash_utils.c\
			 ht_hash_utils.c\
			 ht_hash_moreutils.c\
			 ht_hash_stillutils.c\
			 ht_hash_show.c\
			 bt_hash.c\
			 alias_replace.c\
			 alias_replace_utils.c\
			 get_options.c\
			 bt_cd.c\
			 bt_cd_utilstwo.c\
			 bt_cd_utils.c\
			 bt_cd_moreutils.c\
			 bt_cd_canonical_a.c\
			 bt_cd_canonical_b.c\
			 bt_cd_canonical_c.c\
			 process_tools.c\
			 process_pipe.c\
			 process_pipe_fd.c\
			 free_job_file.c\
			 status_process.c\
			 clean_commands.c\
			 close_redirection.c\
			 is_builtin.c\
			 parser_var_bis.c\
			 expansion_hash.c\
			 expansion_percent.c\
			 expansion_tools.c\
			 action_file.c\
			 add_set_value.c\
			 bt_export.c\
			 gest_expansion.c\
			 apply_redirection.c\
			 errors.c\
			 manage_id_job.c\
			 bt_jobs_tools.c\
			 bt_jobs_options.c\
			 bt_jobs_display.c\
			 bt_jobs_tools_bis.c\
			 search_job.c\
			 bt_fg.c\
			 bt_bg.c\
			 bt_fg_bg_tools.c\
			 history_replace.c\
			 history_replace_utils.c\
			 history_replace_moreutils.c\
			 bt_type.c \
			 bt_test.c \
			 precedence_alg.c \
			 unary_lists.c \
			 unary_primaries.c \
			 more_unary_primaries.c \
			 last_unary_primaries.c \
			 binary_primaries.c \
			 more_binary_primaries.c \
			 handle_quotes.c \
			 identify_limits.c \
			 ht_hash_moarutils.c\
			 builtins.c\
			 commands_env.c\
			 errors_d.c\
			 errors_t.c\
			 errors_q.c\
			 restore_redir_builtin.c\
			 check_path.c\
			 manage_export.c\
			 manage_set_bis.c\
			 kill.c\
			 job_running.c\
			 value_job_control.c\
			 bt_jobs_p.c\
			 assembly_command.c\
			 create_commands.c\
			 init_heredoc.c\
			 reading_input.c\
			 remove_element.c


OBJS_NAMES = $(SRCS_NAMES:.c=.o)
HEADERS_NAMES = sh21.h lexer.h parser.h env.h builtins.h job.h
LIBS_NAMES = libft.a

OBJ = $(addprefix $(OBJDIR), $(OBJS_NAMES))
HEADERS = $(addprefix $(INCDIR), $(HEADERS_NAMES))
LIBS = $(addprefix $(PATHLIBDIR), $(LIBS_NAMES))

# ----------------- #
# Command variables #
# ----------------- #

CREATE = mkdir -p
DEL = /bin/rm -rf
PRINT = printf
PHONY = all clean cleans fclean re libs cleanlibs fcleanlibs lldb norm help
REMOVE = "\r\033[K"
FUNC = "%-60b\r"

# PROGRESS BAR | Original author Cpirlot
T = $(words $(OBJ))
N = 0
C = $(words $N)$(eval N := x $N)
ECHO = "[`expr $C  '*' 100 / $T`%]"

# ----- #
# Rules #
# ----- #

all : libs $(NAME)

ifeq ($(DEBUG), yes)
	@$(PRINT) "Debug mode : on\n"
else
	@$(PRINT) "Debug mode : off\n"
endif

$(NAME) : $(LIBS) $(OBJS_NAMES)
	@$(CC) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS) $(LFLAGS) $(CFLAGS) $(CPPFLAGS)
	@$(PRINT) $(REMOVE)"Executable built\n"

libs :
	@$(MAKE) -j3 -C $(LIBDIR)

%.o : %.c $(HEADERS)
	@$(CREATE) $(OBJDIR)
	@$(CC) -o $(OBJDIR)$@ -c $< $(CFLAGS) $(CPPFLAGS)

clean : cleanlibs
	@$(DEL) $(OBJDIR)
	@$(PRINT) ".o file deleted\n"

cleans :
	@$(DEL) $(OBJDIR)
	@$(PRINT) ".o file deleted\n"

fclean : cleans fcleanlibs
	@$(DEL) $(NAME)
	@$(PRINT) "Executable destroyed\n"

cleanlibs :
	@$(MAKE) -C $(LIBDIR) clean

fcleanlibs :
	@$(MAKE) -C $(LIBDIR) fclean

lldb :
	@lldb ./$(NAME)

norm :
	@norminette ./$(NAME)

re : fclean all

help :
	@$(PRINT) "Rules available : all, clean, cleans, fclean, re, libs, cleanlibs, fcleanlibs, lldb, norm and help\n"

.PHONY : $(PHONY)
