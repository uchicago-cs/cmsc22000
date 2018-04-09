# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc 
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/
DYN_LDFLAGS = -L../ -Wl,-rpath,.
STC_LDFLAGS = -L../
RM = rm -f
LDLIBS = -lgeometry

SRCS = polygon.c
OBJS = $(SRCS:.c=.o)
BINS = polygon-sample polygon-sample-static

.PHONY: all
all: ${BINS}

polygon.o: polygon.c

polygon-sample: polygon.o
	$(CC) $(DYN_LDFLAGS) $^ -o$@ $(LDLIBS) 

polygon-sample-static: polygon.o
	$(CC) $(STC_LDFLAGS) $^ -o$@ -l:libgeometry.a -lm


.PHONY: clean
clean:
	-${RM} ${OBJS} ${BINS}
