CC = gcc

CFLAGS  = -g -Wall
LIBS = -lcurl
DEFS = 

EXECUTABLE = alyo
TARGET = main.c curl.c parser.c url.c list.c hls.c
INCLUDES = -I./include
OBJS := $(TARGET:.c=.o)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFS) -c $< -o $@

all: $(EXECUTABLE)

debug: DEFS=-DDEBUG

debug: all

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXECUTABLE) $(OBJS) $(LIBS)

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
