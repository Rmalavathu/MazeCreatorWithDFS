// ***
// *** You MUST modify this file
// ***

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"
#include "path.h"
#include "mazehelper.h"
#include "maze.h"

char * solveMaze(Maze * m) {
    //An obvious upper bound on the size of the solution path is the number
    //of squares in the maze + 1 (to account for the '\0'). You could make
    //this a tighter bound by accounting for how many walls there are, but
    //this approach is good enough!
	char * retval = malloc(sizeof(char) * ((m->width * m->height) + 1));

	MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
	if (!depthFirstSolve(m, mp, retval, 0)) {
		free(retval);
		return NULL;
		fprintf(stderr, "No solution found!\n");
	} else {
		printf("Solution found: %s\n", retval);
	}
	
	return retval;
}

bool depthFirstSolve(Maze * m, MazePos curpos, char * path, int step) {
	
	//Case if it reaches the end
	if(atEnd(curpos, m) == true){
		path[step] = '\0';
		return true;
	}
	//Case if it finds a bad square (obstacles/visited)
	if(!squareOK(curpos, m)) {
		return false;
	}
	//Makes current point already visited
	m -> maze[curpos.ypos][curpos.xpos].visited = true;
	char direc[4] = {NORTH, SOUTH, EAST, WEST};
	//All the possible directions to go
	MazePos pos[4] = {{.xpos = curpos.xpos, .ypos = curpos.ypos-1}, {.xpos = curpos.xpos, .ypos = curpos.ypos+1}, {.xpos = curpos.xpos+1, .ypos = curpos.ypos}, {.xpos = curpos.xpos-1, .ypos = curpos.ypos}};
	
	//Tries all four directions
	for(int i = 0; i < 4; i++){
		//If it succeeds returns those values
		if(depthFirstSolve(m, pos[i],path, step+1)){
			path[step] = direc[i];
			return true;
		}
	}

	return false;
}

