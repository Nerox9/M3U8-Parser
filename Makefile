CC = gcc

CFLAGS  = -g -Wall
LIBS = -lcurl

EXECUTABLE = alyo
TARGET = main.c curl.c
INCLUDES = -I./include
OBJS := $(TARGET:.c=.o)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXECUTABLE) $(OBJS) $(LIBS)

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
