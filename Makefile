SERVER = server.out
CLIENT = client.out
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SFILES = server.c
CFILES = client.c
all : server client

server :
	$(CC) $(CFLAGS)  $(SFILES) -o $(SERVER)

client :
	$(CC) $(CFLAGS)  $(CFILES) -o $(CLIENT)

clean :
	rm -f $(SERVER)
	rm -f $(CLIENT)

fclean : clean
	rm -f $(SERVER) $(CLIENT)
re : clean all

.PHONY : clean all re
