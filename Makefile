NAME = chess

CXX = g++
CXXFLAGS = -Wall -Wextra -g3
LDFLAGS = -lSDL2

SRC = src/main.cpp src/Board.cpp utils/utils.cpp utils/SemiLegal.cpp src/WindowManagment.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean re fclean