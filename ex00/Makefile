NAME     := megaphone
LIB_NAME := lib$(NAME).a

# Default flag
CFLAGS := -Werror -Wall -Wextra -std=c++98

# Debug flag
CFLAGS += -ggdb -fsanitize=leak

# Include directory
INCLUDE_DIR :=

# Command
CPP    := c++
RM    := rm -rf
CP    := cp -r
MKDIR := mkdir -p
AR    := ar rc
MAKE  := make

# Source files
# SRCS := $(shell find . -name "*.cpp" -type f | sort)
MAIN := megaphone.cpp

# Object directory
OBJS_DIR := objs

# Create Object directory
# $(shell find . -type d -exec mkdir -p $(OBJS_DIR)/{} \;)

# Object files
OBJS_NO_MAIN := $(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJS_MAIN    := $(MAIN:%.c=$(OBJS_DIR)/%.o)
OBJS         := $(OBJS_NO_MAIN) $(OBJS_MAIN)

SRCS_COUNT   := $(words $(SRCS) $(MAIN))
PROGRESS     := 0
BAR_LENGTH   := $(shell echo $$(($$COLUMNS / 3)))

.PHONY:
	all clean fclean re library

$(OBJS_DIR)/%.o: %.c
	@$(CPP) $(CFLAGS) $(INCLUDE_DIR) -c $< -o $@
	@$(eval PROGRESS=$(shell echo $$(($(PROGRESS) + 1))))
	@PERCENTAGE=$$(($(PROGRESS) * 100 / $(SRCS_COUNT))) ; \
	BAR=$$(($(BAR_LENGTH) * $$PERCENTAGE / 100)) ; \
	SPACES=$$(($(BAR_LENGTH) - $$BAR)) ; \
	printf "\r\033[K" ; \
	printf "Progress: [" ; \
	for i in $$(seq 1 $$BAR); do printf "="; done ; \
	printf ">" ; \
	for i in $$(seq 1 $$SPACES); do printf " "; done ; \
	printf "] $$PERCENTAGE%% ($@)"
	@if [ $(PROGRESS) -eq $(SRCS_COUNT) ]; then \
		echo ""; \
	fi

all: $(NAME)

# library:
# 	$(AR) $(LIB_NAME) $(OBJS_NO_MAIN) $(LIBRARIES)

$(NAME): $(OBJS)
	$(CPP) $(CFLAGS) $(INCLUDE_DIR) -o $(NAME) $(OBJS_MAIN)

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
