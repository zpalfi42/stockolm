NAME        = stockolm

#--------------- DIRS ---------------#

INCLUDE_DIR    = include
SRC_DIR        = src
OBJS_DIR    = objs

#--------------- FILES ---------------#

INC                = -I $(INCLUDE_DIR)

SRC                = stockolm.c \

OBJ                = $(addprefix $(OBJS_DIR)/,$(SRC:.c=.o))


#--------------- COMPILATION ---------------#

CC            = gcc
CFLAGS        = -g $(INC)
CPPFLAGS	  = -I/home/linuxbrew/.linuxbrew/opt/openssl@1.1/include/openssl
LDFLAGS		  = -L/home/linuxbrew/.linuxbrew/opt/openssl@1.1/lib -lssl -lcrypto

#--------------- RULES ---------------#

objs/%.o:src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) -c $(CFLAGS) -o $@ $^
	@echo "Compiling $^"

all:    $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "Built $(NAME)"

clean:
	@rm -rf $(OBJS_DIR)

fclean:
	@rm -f $(NAME)

re:    fclean all
