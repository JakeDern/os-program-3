CC = gcc
CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = 537make
SCAN_BUILD_DIR = scan-build-out

all: main.o FileChecker.o Graph.o LinkedList.o ListIterator.o Target.o
	$(CC) -o $(EXE) main.o FileChecker.o Graph.o LinkedList.o ListIterator.o Target.o 

main.o: main.c 
	$(CC) $(WARNING_FLAGS) -c main.c 

FileChecker.o:  
	$(CC) $(WARNING_FLAGS) -c ./modules/FileChecker.c 

Graph.o: 
	$(CC) $(WARNING_FLAGS) -c ./types/graph/Graph.c

LinkedList.o:
	$(CC) $(WARNING_FLAGS) -c ./types/linked_list/LinkedList.c 

ListIterator.o:  
	$(CC) $(WARNING_FLAGS) -c ./types/linked_list/ListIterator.c 

Target.o:  
	$(CC) $(WARNING_FLAGS) -c ./types/target/Target.c 

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
