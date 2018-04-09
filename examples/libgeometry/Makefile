# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
AR = ar 
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/
LDFLAGS = -shared
RM = rm -f
DYNAMIC_LIB = libgeometry.so
STATIC_LIB = libgeometry.a
LIBS = ${DYNAMIC_LIB} ${STATIC_LIB}
LDLIBS = -lm

SRCS = src/point.c src/polygon.c
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: ${LIBS}

$(DYNAMIC_LIB): $(OBJS)
	$(CC) -shared -o $@ $^ $(LDLIBS)

$(STATIC_LIB): $(OBJS)
	$(AR) -r -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean tests
clean:
	-${RM} ${LIBS} ${OBJS} $(SRCS:.c=.d)
	make -C ./tests clean
	make -C ./samples clean
	
tests: ${LIBS}
	make -C ./tests

samples: ${LIBS}
	make -C ./samples
