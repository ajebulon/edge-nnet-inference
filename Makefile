CC = gcc

CFLAGS += -ggdb3 -std=gnu99
LDFLAGS += -lm

PROGS = main
TESTS = activation_test layer_test read_test

main: main.o network.o layer.o activation.o initialization.o
	$(CC) $(CFLAGS) -Wall -Werror $^ -o $@ $(LDFLAGS)

activation_test: activation_test.o activation.o
	$(CC) $(CFLAGS) -Wall -Werror $^ -o $@ $(LDFLAGS)

layer_test: layer_test.o layer.o activation.o initialization.o 
	$(CC) $(CFLAGS) -Wall -Werror $^ -o $@ $(LDFLAGS)

.PHONY: tests
tests: $(TESTS)

.PHONY: clean
clean:
	rm -rf $(PROGS)
	rm -rf $(TESTS)
	rm -rf *.o
	rm -rf valgrind-out.txt