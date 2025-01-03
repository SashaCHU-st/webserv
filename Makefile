NAME = webserv
CC = c++

CFLAGS = -Wall -Wextra -Werror

SRCS = src/main.cpp \
		src/Binding_from_server.cpp \
		src/Connecting_from_client.cpp \
		src/Launching.cpp \
		src/Listen.cpp \
		src/Server.cpp \
		src/Socket.cpp \
		src/ParseConfig.cpp \
		src/Utils.cpp
		
	
		 



OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	
%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re