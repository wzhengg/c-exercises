SRCS = main.c kv.c list.c
TARG = kv
CC   = gcc
OPTS = -O -Wall -std=c99

OBJS = $(SRCS:.c=.o)

$(TARG): $(OBJS)
	$(CC) -o $(TARG) $(OBJS)

%.o: %.c
	$(CC) $(OPTS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(TARG)
