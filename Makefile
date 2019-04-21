CC=gcc
OPT=-Wall

HEADDIR=headers
SRCDIR=src
TESTSDIR=tests

cmd_test: cmd_test.o utils_block.o utils_stripe.o utils_virtual_disk.o
	$(CC) -o $@ $(OPT)

%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(OPT)

clean:
	rm -rf *.o *.exe *.stackdump
