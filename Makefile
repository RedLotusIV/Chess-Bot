
NAME = chess

CFLAGS = -Wall -Wextra -g3 

CC = g++

SRC = src/main.cpp src/Board.cpp utils/utils.cpp utils/SemiLegal.cpp

OBJ = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJ)
		@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
		@$(CC) $(CFLAGS) -c $< -o $@

clean :
		@rm -rf $(OBJ)

fclean : clean
		@rm -rf $(NAME)

re : fclean all

.PHONY: all clean re fclean