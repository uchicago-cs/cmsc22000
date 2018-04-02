# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc 
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/
LDFLAGS = -shared
RM = rm -f
TARGET_LIB = libgeometry.so
LDLIBS = -lm

SRCS = src/point.c src/polygon.c
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^ $(LDLIBS)

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean tests
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)
	make -C ./tests clean
	
tests: ${TARGET_LIB}
	make -C ./tests
	