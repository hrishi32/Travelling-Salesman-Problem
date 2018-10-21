all: tsp

tsp: tsp.o
	g++ tsp.o -o tsp

tsp.o: simAnnealing.cpp
	g++ simAnnealing.cpp -c -o tsp.o

clean:
	rm -r *o tsp