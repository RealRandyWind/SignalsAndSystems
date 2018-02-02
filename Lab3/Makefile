ANAME ?= corr1d
CXX ?= gcc
COMPILE_FLAGS = -Wall -Wextra -g -lm -fpermissive

.PHONY: all clean

all: main-build

main-build:
	$(CXX) -o a.out $(ANAME).c ntt.c $(COMPILE_FLAGS)

clean:
	rm -f ./$(ANAME).a ./a.out ./*.o