main: main.o classifier.o sample.o
	g++ main.o classifier.o sample.o -g -o main 

main.o: main.cpp
	g++ -c -g main.cpp

classifier.o: classifier.cpp
	g++ -c -g classifier.cpp

sample.o: sample.cpp
	g++ -c -g sample.cpp

clean:
	rm *.o
