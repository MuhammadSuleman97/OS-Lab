#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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


char **multi_tokenize(char *line)
{
  char **multi_tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
  char *multi_token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
  int i, tokenIndex = 0, tokenNo = 0;
  for(i =0; i < strlen(line); i++){

    char readChar = line[i];

    if (readChar == '&' || readChar == '\n'){
    	if ( readChar == '\n' ){
    		multi_token[tokenIndex++] = '\n';
    		multi_token[tokenIndex] = '\0';
    	}
    	else
      		multi_token[tokenIndex] = '\0';
      if (tokenIndex != 0){
	multi_tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
	strcpy(multi_tokens[tokenNo++], multi_token);
	tokenIndex = 0; 
      }
    } else {
      multi_token[tokenIndex++] = readChar; 
    }
  }
 
  free(multi_token);
  multi_tokens[tokenNo] = NULL ;
  return multi_tokens;
}



  
// Function to print Current Directory. 
void printDir() 
{ 
    char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); 
    printf("\nDir: %s", cwd); 
} 




  
// Function where the system command is executed 
void execution(char** tokens) 
{ 
    // Forking a child 
    pid_t PID; 
    
    PID= fork();  
  
    if (PID == -1) { 
        printf("\nUnable to fork a child !"); 
        return; 
        
    } else if (PID == 0) { 
        if (execvp(tokens[0], tokens) < 0) { 
            printf("\nUnable to execute command !"); 
        } 
        exit(0); 
        
    } else { 
        // waiting for child to terminate 
        wait(NULL);  
        return; 
    } 
}



 
int main(int argc, char* argv[]) {
	char  line[MAX_INPUT_SIZE]; 
	char **multi_tokens;           
	char  **tokens;              
	int i;

	FILE* fp;
	if(argc == 2) {
		fp = fopen(argv[1],"r");
		if(fp < 0) {
			printf("No such File !");
			return -1;
		}
	}

	while(1) {			
		/* BEGIN: TAKING INPUT */
		printDir();
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
		
		/* END: TAKING INPUT */
		
		line[strlen(line)] = '\n'; //terminate with new line
		
		if (line[strlen(line)-2] == '&'){
			printf( "pid = %d" ,getpid());
		}
		if (strlen(line) == 1)
			continue;
		multi_tokens = multi_tokenize(line);
		
		for(i = 0; multi_tokens[i] != NULL;i++){
			if (strlen(multi_tokens[i]) == 1)
				continue;
			else{	
			tokens = tokenize(multi_tokens[i]);
			
       		if (tokens[0][0] == 'c' && tokens[0][1] == 'd')
				chdir(tokens[1]);	
			else
				execution(tokens);
				
			}
			}
		
		for(int j=0;tokens[j]!=NULL;j++){
			free(tokens[j]);
		}
		free(tokens);
		
		for(i=0;multi_tokens[i]!=NULL;i++){
			free(multi_tokens[i]);
		}
		free(multi_tokens);

	}
	return 0;
}