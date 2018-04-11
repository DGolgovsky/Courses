#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define RESULT "result.out"


void exec_pipe(char*** cmds, int size, int index) {
	if (index == size - 1) {
		FILE *result = fopen(RESULT, "w");
		dup2(fileno(result), STDOUT_FILENO);
		fclose(result);
		execvp(cmds[index][0], cmds[index]);
		return;
	}

	int pfd[2];
    pipe(pfd);

    pid_t pid;
    if (pid = fork()) {
        dup2(pfd[1], STDOUT_FILENO);
		close(pfd[0]);
		close(pfd[1]);
        execvp(cmds[index][0], cmds[index]);
		return;
    }

	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	close(pfd[1]);
	
	exec_pipe(cmds, size, ++index);
}


int main(int argc, char **argv) {
    char *line = NULL;
    size_t size;
    getline(&line, &size, stdin);
/////////////////////////////////
    int pipes = 0;
    char *s = line;
    while (*s++) {
        if (*s == '|') pipes++;
    }
    char ***cmds;
    cmds = malloc(sizeof(char**) * (pipes + 1));
/////////////////////////////////
    s = line;
    int numWords = 0;
    int isWord = 0;
    int index = 0;
    while (*s) {
        if (*s == '|') {
            cmds[index++] = malloc(sizeof(char*) * (numWords + 1));
            numWords = 0;
            s++;
            continue;
        }
        if (isspace(*s)) {
            if (isWord) isWord = 0;
        } else {
            if (!isWord) {
                numWords++;
                isWord = 1;
            }
        }
        s++;
    }
    cmds[index] = malloc(sizeof(char*) * (numWords + 1));
////////////////////////////////
    s = line;
    int pIndex = 0;
    int wIndex = 0;
    char *start = 0;
    isWord = 0;
    while (*s) {
        if (*s == '|') {
            cmds[pIndex][wIndex] = 0;
            pIndex++;
            wIndex = 0;
            s++;
            continue;
        }
        if (isspace(*s)) {
            if (isWord) {
                isWord = 0;
                cmds[pIndex][wIndex] = malloc(s - start + 1);
                memcpy(cmds[pIndex][wIndex], start, s - start);
                cmds[pIndex][wIndex][s - start] = 0;
                cmds[pIndex][++wIndex] = 0;
            }
        } else {
            if (!isWord) {
                isWord = 1;
                start = s;
            }
        }
        s++;
    }

    exec_pipe(cmds, pipes+1, 0);
}
