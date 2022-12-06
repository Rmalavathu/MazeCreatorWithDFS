CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
TESTFLAGS = -DCHECK_PATH
GCC = gcc $(CFLAGS)
EXEC = hw9
OBJS =  hw9.o maze.o mazehelper.o path.o solver.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

$(EXEC): $(OBJS) solver.h
	$(GCC) $(OBJS) -o $(EXEC) 

test: $(EXEC)
	./$(EXEC) testcases/maze1 mazes/maze1 output1
	./$(EXEC) testcases/maze2 mazes/maze2 output2
	./$(EXEC) testcases/maze3 mazes/maze3 output3

memory: $(EXEC)
	$(VALGRIND) --log-file=log1 ./$(EXEC) testcases/maze1 mazes/maze1 output1
	$(VALGRIND) --log-file=log2 ./$(EXEC) testcases/maze2 mazes/maze2 output2
	$(VALGRIND) --log-file=log3 ./$(EXEC) testcases/maze3 mazes/maze3 output3

%.o : %.c
	$(GCC) -c $< 

clean:
	rm -f hw9.o maze.o mazehelper.o path.o solver.o
	rm -f $(EXEC)
	rm -f id? name? log?
	rm -f output*