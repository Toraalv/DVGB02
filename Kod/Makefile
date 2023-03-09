src = $(wildcard *.c)
obj = $(src:.c=.o)

CFLAGS = --std=c11 -g

.PHONY: clean

sim: $(obj)
	$(CC) $(CFLAGS) -o $@ $^

post-clean:
	rm -f $(obj)

pre-clean:
	rm -f $(obj) sim