CC = gcc

CFLAGS += -ggdb3 -std=gnu99
LDFLAGS += -lm

PROGS = main
TESTS = activation-test forward-test

main: main.o
	$(CC) $(CFLAGS) -Wall -Werror $^ -o $@ $(LDFLAGS)

activation-test: activation_test.o activation.o
	$(CC) $(CFLAGS) -Wall -Werror $^ -o $@ $(LDFLAGS)

forward-test: forward_test.o activation.o initialization.o
	$(CC) $(CFLAGS) -Wall -Werror $^ -o $@ $(LDFLAGS)

.PHONY: tests
tests: $(TESTS)

.PHONY: clean
clean:
	rm -rf $(PROGS)
	rm -rf $(TESTS)
	rm -rf *.o
	rm -rf valgrind-out.txt