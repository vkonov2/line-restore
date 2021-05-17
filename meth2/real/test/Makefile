FLAGS = -O3 -ffast-math

all: test.out

test.out: test_data.o point.o
	g++ test_data.o point.o -o test.out

main.o: test_data.cpp test_functions.h
	g++ $(FLAGS) -c main.cpp
point.o: point.cpp point.h
	g++ $(FLAGS) -c point.cpp
clean:
	rm -rf *.0 test.out
