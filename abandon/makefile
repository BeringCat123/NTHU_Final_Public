CC = gcc
OBJS = main.o
OBJS_NAME = main
OBJS_NAME_DEBUG = main_debug
INCLUDE_PATHS = 
LIBRARY_PATHS =
COMPILER_FLAGS = -o
LINKER_FLAGS =

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(OBJS_NAME)

*.o: *.c
	$(CC) -c $*.c -o $@

.PHONY: clean
clean:
	del *.o