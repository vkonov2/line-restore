FLAGS = -O3 -ffast-math

all: proec.out

proec.out: main.o point.o time_now.o solve.o get_data.o line_solve.o line_res.o eigen.o yakobi.o vect.o check.o rm.o
	g++ main.o point.o time_now.o solve.o get_data.o line_solve.o line_res.o eigen.o yakobi.o vect.o check.o rm.o -o proec.out

main.o: main.cpp functions.h
	g++ $(FLAGS) -c main.cpp
point.o: point.cpp point.h
	g++ $(FLAGS) -c point.cpp
time_now.o: time_now.cpp functions.h
	g++ $(FLAGS) -c time_now.cpp
solve.o: solve.cpp functions.h
	g++ $(FLAGS) -c solve.cpp
get_data.o: get_data.cpp functions.h
	g++ $(FLAGS) -c get_data.cpp
line_solve.o: line_solve.cpp functions.h
	g++ $(FLAGS) -c line_solve.cpp
line_res.o: line_res.cpp functions.h
	g++ $(FLAGS) -c line_res.cpp
eigen.o: eigen.cpp functions.h
	g++ $(FLAGS) -c eigen.cpp
yakobi.o: yakobi.cpp functions.h
	g++ $(FLAGS) -c yakobi.cpp	
vect.o: vect.cpp functions.h
	g++ $(FLAGS) -c vect.cpp
check.o: check.cpp functions.h
	g++ $(FLAGS) -c check.cpp	
rm.o: rm.cpp functions.h
	g++ $(FLAGS) -c rm.cpp	
clean:
	rm -f *.o proec.out
