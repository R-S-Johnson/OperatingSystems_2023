#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

/* Splits the string by space and returns the array of tokens
*
*/
char **tokenize(char *line)
{
  char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
  char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
  int i, tokenIndex = 0, tokenNo = 0;

  for(i =0; i < strlen(line); i++){

    char readChar = line[i];

    if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
      token[tokenIndex] = '\0';
      if (tokenIndex != 0){
	tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
	strcpy(tokens[tokenNo++], token);
	tokenIndex = 0; 
      }
    } else {
      token[tokenIndex++] = readChar;
    }
  }
 
  free(token);
  tokens[tokenNo] = NULL ;
  return tokens;
}

void binCom(char **command) {
	// cd command
	if (strcmp(command[0], "cd") == 0) {
		if (chdir(command[1]) != 0) {
			printf("Shell: Incorrect command\n");
		}
	}

	// /usr/bin/ commands
	else if (execvp(command[0], command) == -1) {
		printf("Shell: Incorrect command\n");
	}
}


int main(int argc, char* argv[]) {
	char  line[MAX_INPUT_SIZE];            
	char  **tokens;              
	int i;
	int tokensSize = 0;
	int backGnd[64];
	int backGndSize = 0;


	FILE* fp;
	if(argc == 2) {
		fp = fopen(argv[1],"r");
		if(fp < 0) {
			printf("File doesn't exists.");
			return -1;
		}
	}

	while(1) {			
		/* BEGIN: TAKING INPUT */
		bzero(line, sizeof(line));
		if(argc == 2) { // batch mode
			if(fgets(line, sizeof(line), fp) == NULL) { // file reading finished
				break;	
			}
			line[strlen(line) - 1] = '\0';
		} else { // interactive mode
			printf("$ ");
			scanf("%[^\n]", line);
			getchar();
		}
		// printf("Command entered: %s (remove this debug output later)\n", line);
		/* END: TAKING INPUT */
		printf("input taken\n");


		// Check for done background processes
		int tmp;
		if(waitpid(-1, &tmp, WNOHANG) > 0) {
			printf("Shell: Background process finished\n");
		}
		printf("checked for bckgnd process\n");

        // Check empty input
        if (line == "\n") {
			for(i=0;tokens[i]!=NULL;i++){
				free(tokens[i]);
			}
			free(tokens);
			continue;
        }
		printf("not empty input\n");

		line[strlen(line)] = '\n'; //terminate with new line
		tokens = tokenize(line);

		tokensSize = 0;
		while (tokens[tokensSize] != NULL) {
			tokensSize++;
		}
		printf("format done\n");

		// background process
		// printf("%d\n", strcmp(tokens[tokensSize-2], "&"));
		printf("# of tokens: %d\n", tokensSize);	
		if (tokensSize > 1 && !strcmp(tokens[tokensSize-1], "&")) {
			printf("bckgnd process selected\n");
			int pid = fork();
			if (pid == 0) {
				// Child
				tokens[tokensSize-1] = NULL;
				binCom(tokens);
			}
			else {
				backGnd[backGndSize] = pid;
				backGndSize++;
			}
		}

       // basic bin command
	   else if (fork() == 0) {
			// Child
			binCom(tokens);
	   }
	   else {
			// Parent
			wait(NULL);
	   }
	   printf("round complete\n");

		// for(i=0;tokens[i]!=NULL;i++){
		// 	printf("found token %s (remove this debug output later)\n", tokens[i]);
		// }
       
		// Freeing the allocated memory	
		for(i=0;tokens[i]!=NULL;i++){
			free(tokens[i]);
		}
		free(tokens);

	}
	return 0;
}