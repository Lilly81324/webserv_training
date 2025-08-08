NAME = snooper

CXX = c++
CFLAGS = -Wall -Wextra -Werror

SRC = main.cpp Snooper.cpp
OBJ = $(SRC:%.cpp=%.o)

all: $(NAME)

$(NAME): clean
	$(CXX) $(CFLAGS) $(SRC) -o $@

run: $(NAME)
	./$(NAME)

clean:
	rm -f $(NAME)

.PHONY = all clean re
