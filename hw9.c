// ***
// *** Do NOT modify this file
// ***

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"
#include "path.h"
#include "solver.h"

int main(int argc, char ** argv) {
	if (argc != 4) {
		fprintf(stderr, "Wrong number of command line args\n");
		fprintf(stderr, "Usage: ./hw9 [mazeFile] [pathFile]\n");
		return EXIT_FAILURE;
	}

	srand ( time(NULL) );


	makeMaze(argv[1], argv[2]);
	
	Maze * m = readMaze(argv[2]);
	
	if (m == NULL) {
		return EXIT_FAILURE;
	}

	char * path = solveMaze(m);
	
	if (writePath(argv[3], path)) {
		freeMaze(m);
		free(m);
		free(path);
		return EXIT_FAILURE;
	}

       /*
       For testing purpose ONLY: You can use the code below 
       to *read in* a path from a pathFile, and check if 
       it's a solution to the maze. This is a good way 
       to check the outputs that your solver is producing.
       To use the following code, just include the testflag
       -DCHECK_PATH in the gcc command in your Makefile
       */


	#ifdef CHECK_PATH
	freeMaze(m);
	free(m);
	free(path);

	m = readMaze(argv[2]);
	path = readPath(argv[3]);

	if (path == NULL) {
		freeMaze(m);
	 	free(m);
	 	return EXIT_FAILURE;
	}
	
	if (checkPath(m, path)) {
	 	printf("Success!\n");
	} else {
	 	printf("Failure!\n");
	}
	#endif
	
	//Clean up memory
	freeMaze(m);
	free(m);
	free(path);
	
	return EXIT_SUCCESS;

}
