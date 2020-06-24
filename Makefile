# compiler
CC  = gcc
# compile option
CFLAGS = -Wall -O2 -Werror -g3
# execute file
TARGET  = bin/othello
# source
SRCS    = *.c
HEADER = *.h

# object file
OBJS    = $(SRCS:.c=.o)

# include path
INCDIR  = 

# libruary path
LIBDIR  = 

# lib file
LIBS    = 

# linker and make target
$(TARGET): $(OBJS)
	mkdir -p bin
	$(CC) -o $@ $^ $(LIBDIR) $(LIBS)

# generate objfile
$(OBJS): $(SRCS) $(HEADER) Makefile
	$(CC) $(CFLAGS) $(INCDIR) -c $(SRCS)

# make all is clean and make
all: clean $(OBJS) $(TARGET)
# rm file which is not need  
clean:
	-rm -f $(OBJS) $(TARGET) *.~