main: main.o GMM.o Gaussian.o Sample.o
	g++ main.o GMM.o Gaussian.o Sample.o -o main

main.o: main.cpp
	g++ main.cpp -o main.o

GMM.o: GMM.cpp
	g++ GMM.cpp -o GMM.o

Gaussian.o: Gaussian.cpp
	g++ Gaussian.cpp -o Gaussian.o

Sample.o: Sample.cpp
	g++ Sample.cpp -o Sample.o
