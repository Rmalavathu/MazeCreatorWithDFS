CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
TESTFLAGS = -DCHECK_PATH
GCC = gcc $(CFLAGS)
EXEC = hw9
OBJS =  hw9.o maze.o mazehelper.o path.o solver.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

$(EXEC): $(OBJS) solver.h
	$(GCC) $(OBJS) -o $(EXEC) 

test: $(EXEC)
	./$(EXEC) testcases/maze1 path_out1
	./$(EXEC) testcases/maze2 path_out2
	./$(EXEC) testcases/maze3 path_out3
	./$(EXEC) testcases/maze4 path_out4
	./$(EXEC) testcases/maze5 path_out5

memory: $(EXEC)
	$(VALGRIND) --log-file=log1 ./$(EXEC) testcases/maze1 path_out1
	$(VALGRIND) --log-file=log2 ./$(EXEC) testcases/maze2 path_out2
	$(VALGRIND) --log-file=log3 ./$(EXEC) testcases/maze3 path_out3
	$(VALGRIND) --log-file=log4 ./$(EXEC) testcases/maze4 path_out4
	$(VALGRIND) --log-file=log5 ./$(EXEC) testcases/maze5 path_out5



%.o : %.c
	$(GCC) -c $< 

clean:
	rm -f main.o shuffle.o
	rm -f $(EXEC)
	rm -f id? name? log?
	rm -f output*