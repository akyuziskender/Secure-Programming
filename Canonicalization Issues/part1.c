// İskender Akyüz
// Student ID: 150150150

#include <stdio.h>
#include <stdlib.h>

void processFile(const char *path){
	printf("Process file executes\n");
	char samplecommandtoexecute[100]={"ls -la "};
	strcat(samplecommandtoexecute, path);
	int status = system(samplecommandtoexecute);
	return;
}

int pathChecker(const char* safepath, const char *path, size_t spl) {
	size_t i = 0, pathlength = strlen(path);
	int validPath = 0, outsideSafe = 0;
	int distanceFromSafe = 0;	// the distance between where we are and the safepath
	while(i < pathlength) {
		if(*(path+i) == '/' && strncmp(path+i, safepath, spl) == 0) { // if we see a "/home" then we are in the safe zone
			outsideSafe = 0;	// we are not in the outside of safepath, so it is set to false
			distanceFromSafe = 0;
			i += (spl -1); // skipping safepath
			if(i+3 < pathlength && strncmp(path+i+1, "/..", 3) == 0) { // checking if we are going up from the safe directory
				outsideSafe = 1;	// we are in the outside safe directory, so it is set to true
				distanceFromSafe--;
				i += 3;	// skipping "/.." 
			}
		}
		else if(*(path+i) == '/' && i+1 < pathlength) {
			i++;
			if(!outsideSafe) {
				// if we inside safe directory and two dots comes after a slash, decrement distance
				if(*(path+i) == '.' && i + 1 < pathlength && *(path+i+1) == '.') {
					distanceFromSafe--;
					i++;
				}
				else // otherwise, increment distance because we are getting far from the safe directory
					distanceFromSafe++;
			}
			else {
				// if we outside directory and .. comes after a /, increase the distance
				if(*(path+i) == '.' && i + 1 < pathlength && *(path+i+1) == '.') {
					distanceFromSafe++;
					i++;
				}
				else // otherwise decrement the distance because we are getting closer to the safepath
					distanceFromSafe--;
			}
		}
		i++;
	}
	if(distanceFromSafe >= 0)	// if the distance >= 0, that means we are somewhere in the safe directory
		validPath = 1;
	else
		validPath = 0;
	return validPath;
}

void main(int argc, char *argv[]) {
	const char *safepath = "/home";
	size_t spl = strlen(safepath);
	
	char *fn = argv[1];
	
	if(pathChecker(safepath, fn, spl)){
		processFile(fn);
	}
	else {
		printf("Path specified is not valid!\n");
		return;
	}
	return;
}
