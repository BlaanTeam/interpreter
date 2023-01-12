
NAME = interpreter

CC = c++

CFLAGS = -Wall -Wextra -std=c++11 -ggdb


SRC = interpreter.cpp  parser.cpp ast.cpp exception.cpp global_utils.cpp 

HEADER =  interpreter.hpp  parser.hpp ast.hpp exception.hpp global_utils.hpp 

OBJ = $(SRC:%.cpp=%.o)

all: $(NAME)


run:
	@./$(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $(NAME) -lreadline -fsanitize=address



%.o: %.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -vf $(OBJ)

fclean:	clean
	rm -vf $(NAME)

re: fclean all