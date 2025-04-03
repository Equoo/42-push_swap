# Variables
DEBUG = 0
NAME = push_swap
STATE_FILE := .state.tmp
CC = cc
NORMIGNORE =

DIR_OBJ = obj/
SRC_DIR = src/
INC_DIR = headers/
LIBFT_DIR = libft/
LIBFT_LIB = libft/libft.a

# Compiler and linker flags
EXTRAFLAGS = -O3
CFLAGS = -Wall -Wextra -Werror -MMD -D $(shell echo "$(NAME)" | tr '[:lower:]' '[:upper:]')=1 -I $(INC_DIR) -I $(LIBFT_DIR)headers
LIBS = -L$(LIBFT_DIR) -lft

# Sources
SRCS = main.c \
		ft_error.c \
		quicksort.c \
		sort_ten.c \
		stack/operate_for.c \
		stack/operate.c \
		stack/push.c \
		stack/rotate.c \
		stack/swap.c \

# Object files and dependencies
OBJS = $(patsubst %.c,$(DIR_OBJ)%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)
-include $(DEPS)

# Colors for output
GREEN  := \033[1;32m
BLUE   := \033[1;34m
YELLOW := \033[1;33m
RED    := \033[1;31m
RESET  := \033[0m

# Default rule
.DEFAULT_GOAL = all

.PHONY: clean_cmd
clean_cmd:
	@clear

# Targets
.PHONY: all
all: clean_cmd check_git_submodules banner libft check_build
	@$(MAKE) -j$(shell nproc) --no-print-directory EXTRAFLAGS="$(EXTRAFLAGS)" $(NAME)
	@STATE=$$(cat $(STATE_FILE) 2>/dev/null || echo 0); \
	if [ $$STATE -eq 1 ]; then \
		echo -e "$(BLUE)[✓] Everything is up to date! No need to rebuild.$(RESET)"; \
	else \
		echo -e "$(YELLOW)=====================================$(RESET)"; \
		echo -e "$(GREEN)[✓] Build completed!$(RESET)"; \
	fi

# Check if recompilation is needed
.PHONY: check_build
check_build:
	@if [ -f $(NAME) ] && \
		! find $(SRC_DIR) -type f -name '*.c' -newer $(NAME) | grep -q . && \
		! find $(INC_DIR) -type f -name '*.h' -newer $(NAME) | grep -q . && \
		! [ Makefile -nt $(NAME) ] && \
		! [ -z "$(wildcard $(OBJS)/$(NAME))/" ]; then \
		echo "1" > $(STATE_FILE); \
	else \
		echo -e "$(YELLOW)[Building MiniTalk]$(RESET)"; \
		echo "0" > $(STATE_FILE); \
	fi

.PHONY: debug
debug: EXTRAFLAGS = -O0 -g3 -DDEBUG=1
debug: LIBFTTARGET = debug
debug: DEBUG = 1
debug: all
	touch .d

.PHONY: bonus
bonus: SRCS = $(SRCS_BONUS)
bonus: BONUS = 1
bonus: all
	touch .b

%/:
	@mkdir -p $@

$(DIR_OBJ)%.o: $(SRC_DIR)%.c Makefile
	@echo -e "\t$(YELLOW)Compiling $(NAME) $*.c$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(EXTRAFLAGS) -c $< -o $@

.PHONY: libft
libft:
	@$(MAKE) --no-print-directory -s -C $(LIBFT_DIR) $(LIBFTTARGET)

$(NAME): $(LIBFT_LIB) Makefile $(OBJS)
	@echo -e "$(BLUE)[Linking]$(RESET) $@"
	$(CC) $(CFLAGS) $(EXTRAFLAGS) -o $@ $(filter %.o, $^) $(LIBS)
	@echo -e "$(GREEN)[✓] Successfully built: $@$(RESET)"

.PHONY: clean
clean:
	@echo -e "$(RED)[Cleaning]$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@rm -rf $(DIR_OBJ)
	@rm -f $(STATE_FILE)
	@rm -f .d .b
	@echo -e "$(GREEN)[✓] Cleaned all object files!$(RESET)"

.PHONY: fclean
fclean: clean
	@echo -e "$(RED)[Full Clean]$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo -e "$(GREEN)[✓] Fully cleaned everything!$(RESET)"

re: fclean all

.PHONY: banner
banner:
	@echo -e "$(YELLOW)=====================================$(RESET)"
	@echo -e "$(BLUE)             norminette            $(RESET)"
#	@norminette | grep -v -E "OK\!|$(NORMIGNORE)"; true
	@echo -e "$(YELLOW)=====================================$(RESET)"

# Git Submodule Check
.PHONY: check_git_submodules
check_git_submodules:
	@if [ -f .gitmodules ]; then \
		echo -e "$(YELLOW)[Git] Checking submodules...$(RESET)"; \
		if [ -z "$$(git submodule status --recursive | grep '^-')" ]; then \
			echo -e "$(GREEN)[✓] Submodules are up to date.$(RESET)"; \
		else \
			echo -e "$(BLUE)[Git] Initializing and updating submodules...$(RESET)"; \
			git submodule update --init --recursive; \
			echo -e "$(GREEN)[✓] Submodules updated.$(RESET)"; \
		fi \
	else \
		echo -e "$(GREEN)[✓] No submodules found, skipping.$(RESET)"; \
	fi
