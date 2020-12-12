CC = gcc

CFLAGS  = -g -Wall
LDFLAGS = -lcurl

EXECUTABLE = alyo
TARGET = main.c curl.c
INCLUDES = -I./include
OBJS := $(TARGET:.c=.o)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) -o $(EXECUTABLE) $(OBJS) 

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
