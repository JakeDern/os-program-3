CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = 537make
SCAN_BUILD_DIR = scan-build-out

all: main.o FileChecker.o Graph.o LinkedList.o ListIterator.o Target.o FileParser.o ProgramBuilder.o
	$(CC) -o $(EXE) main.o FileChecker.o Graph.o LinkedList.o ListIterator.o Target.o FileParser.o ProgramBuilder.o

main.o: main.c 
	$(CC) $(WARNING_FLAGS) -c main.c 

FileChecker.o: ./modules/FileChecker.c ./interfaces/FileChecker.h
	$(CC) $(WARNING_FLAGS) -c ./modules/FileChecker.c 

Graph.o: ./types/graph/Graph.c ./types/graph/Graph.h
	$(CC) $(WARNING_FLAGS) -c ./types/graph/Graph.c

ListIterator.o:  ./types/linked_list/ListIterator.c ./types/linked_list/ListIterator.h
	$(CC) $(WARNING_FLAGS) -c ./types/linked_list/ListIterator.c 
	
LinkedList.o:	./types/linked_list/LinkedList.c ./types/linked_list/LinkedList.h
	$(CC) $(WARNING_FLAGS) -c ./types/linked_list/LinkedList.c 

Target.o:  ./types/target/Target.c ./types/target/Target.h
	$(CC) $(WARNING_FLAGS) -c ./types/target/Target.c 

FileParser.o: ./modules/FileParser.c ./interfaces/FileParser.h
	$(CC) $(WARNING_FLAGS) -c ./modules/FileParser.c

ProgramBuilder.o: ./modules/ProgramBuilder.c ./interfaces/ProgramBuilder.h
	$(CC) $(WARNING_FLAGS) -c ./modules/ProgramBuilder.c 

clean:
	rm $(EXE) *.o

#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html 
