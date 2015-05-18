main: main.o a_star.o grid.o distance_estimators.o
	g++ main.o a_star.o grid.o distance_estimators.o -o main


main.o: main.cpp


grid.o: grid.cpp


distance_estimators.o: distance_estimators.cpp


a_star.o: a_star.cpp


main.cpp: a_star.h grid.h distance_estimators.h
	g++ -std=gnu++11 -c main.cpp


a_star.cpp: a_star.h
	g++ -std=gnu++11 -c a_star.cpp


grid.cpp: grid.h
	g++ -std=gnu++11 -c grid.cpp


distance_estimators.cpp: distance_estimators.h
	g++ -std=gnu++11 -c distance_estimators.cpp


grid.h:


a_star.h:


distance_estimators.h:


clean:
	rm *.o
