useDijkstra.exe: useDijkstra.o graph.o hash.o heap.o
	g++ -o useDijkstra.exe useDijkstra.o graph.o hash.o heap.o

useDijkstra.o: useDijkstra.cpp graph.h
	g++ -c useDijkstra.cpp

dijkstra.o: graph.cpp graph.h hash.h heap.h
	g++ -c graph.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

debug:
	g++ -g -o useDijkstraDebug.exe useDijkstra.cpp graph.cpp hash.cpp heap.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
