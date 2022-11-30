assignment4: main.o KB.o 
	g++ main.o KB.o  -o assignment4

KB.o: KB.cpp KB.h
	g++ -c KB.cpp

main.o: main.cpp KB.h 
	g++ -c main.cpp
clean:
	rm *.o assignment4

