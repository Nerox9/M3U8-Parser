CC = gcc

CFLAGS  = -g -Wall
LIBS = -lcurl
DEFS = 
SRCDIR = src
OBJDIR = obj

EXECUTABLE = alyo

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o,$(SRCS))
INCLUDES = -I./include
	
%.o:
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFS) -c $(@:$(OBJDIR)/%.o=$(SRCDIR)/%.c) -o $@

all: $(EXECUTABLE)
	
debug: DEFS=-DDEBUG

debug: all
	
$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXECUTABLE) $(OBJS) $(LIBS)

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
