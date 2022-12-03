CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
TESTFLAGS = -DCHECK_PATH
GCC = gcc $(CFLAGS) $(TESTFLAGS)
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
	$(VALGRIND) --log-file=log1 ./$(EXEC) testcases/maze1 output1
	$(VALGRIND) --log-file=log2 ./$(EXEC) testcases/maze2 output2
	$(VALGRIND) --log-file=log3 ./$(EXEC) testcases/maze3 output3
	$(VALGRIND) --log-file=log4 ./$(EXEC) testcases/maze4 output4
	$(VALGRIND) --log-file=log5 ./$(EXEC) testcases/maze5 output5



%.o : %.c
	$(GCC) -c $< 

clean:
	rm -f hw9.o maze.o mazehelper.o path.o solver.o
	rm -f $(EXEC)
	rm -f id? name? log?
	rm -f output*