CC = gcc

CFLAGS += -ggdb3 -std=gnu99
LDFLAGS += -lm

PROGS = benchmark
TESTS = activation_test layer_test network_test

benchmark: benchmark.o network.o layer.o activation.o initialization.o
	$(CC) $(CFLAGS) -Wall -Werror $^ -o $@ $(LDFLAGS)

network_test: network_test.o network.o layer.o activation.o initialization.o
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