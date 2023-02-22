src = $(wildcard *.c)
obj = $(src:.c=.o)

CFLAGS = --std=c11 -g

sim: $(obj)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f $(obj) sim

