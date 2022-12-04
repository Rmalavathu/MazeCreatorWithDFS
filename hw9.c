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

	bool solvable; //Boolean to check if maze is solvable
	solvable = false;
	Maze * m;
	char * path;
	srand ( time(NULL) );


	while(!solvable){
		makeMaze(argv[1], argv[2]); //Calls make maze
		
		m = readMaze(argv[2]);
		
		if (m == NULL) {
			return EXIT_FAILURE;
		}

		path = solveMaze(m);
		
		if (writePath(argv[3], path)) {
			freeMaze(m);
			free(m);
			free(path);
			return EXIT_FAILURE;
		}

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
		solvable = checkPath(m, path); //calls check path
		if (solvable) {
			printf("Success!\n");
			return EXIT_SUCCESS;
		} else {
			printf("Failure!\n");
		}
		
		//Clean up memory

		freeMaze(m);
		free(m);
		free(path);

	}

}
