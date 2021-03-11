CFLAGS = -Wall -fopenmp -lm

EXE_NAME = pi.out
SRC=$(wildcard *.c)

NUMBER_OF_THREADS = 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16

all: $(EXE_NAME) tests

$(EXE_NAME): $(SRC) 
	gcc -o $(EXE_NAME) $^ $(CFLAGS)

test: $(SRC)
	./$(EXE_NAME) 6 12345678

tests: $(SRC)
	$(foreach var,$(NUMBER_OF_THREADS),./$(EXE_NAME) $(var) 12345678;)

clean: 
	rm $(EXE_NAME)

.PHONY: clean test tests