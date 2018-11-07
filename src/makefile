
all:main.o FileChecker.o Graph.o LinkedList.o ListIterator.o Target.o FileParser.o ProgramBuilder.o
	gcc -o 537make main.o FileChecker.o Graph.o LinkedList.o ListIterator.o Target.o FileParser.o ProgramBuilder.o

main.o: main.c 
	gcc -Wall -Wextra -c main.c 

FileChecker.o: ./modules/FileChecker.c ./interfaces/FileChecker.h
	gcc -Wall -Wextra -c ./modules/FileChecker.c 

Graph.o: ./types/graph/Graph.c ./types/graph/Graph.h
	gcc -Wall -Wextra -c ./types/graph/Graph.c

ListIterator.o: ./types/linked_list/ListIterator.c ./types/linked_list/ListIterator.h
	gcc -Wall -Wextra -c ./types/linked_list/ListIterator.c 

LinkedList.o: ./types/linked_list/LinkedList.c  ./types/linked_list/LinkedList.h
	gcc -Wall -Wextra -c ./types/linked_list/LinkedList.c 

Target.o:  ./types/target/Target.c ./types/target/Target.h
	gcc -Wall -Wextra -c ./types/target/Target.c 

FileParser.o: ./modules/FileParser.c ./interfaces/FileParser.h
	gcc -Wall -Wextra -c ./modules/FileParser.c

ProgramBuilder.o: ./modules/ProgramBuilder.c ./interfaces/ProgramBuilder.h
	gcc -Wall -Wextra -c ./modules/ProgramBuilder.c 

clean:
	rm *.o
