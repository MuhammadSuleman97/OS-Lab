

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


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
      
    } 
    
    else 
      token[tokenIndex++] = readChar;
    
  }
 
  free(token);
  tokens[tokenNo] = NULL ;
  return tokens;
}

char ** multi_tokenize(char * line) {
    char ** multi_tokens = (char ** ) malloc(MAX_NUM_TOKENS * sizeof(char * ));
    char * multi_token = (char * ) malloc(MAX_TOKEN_SIZE * sizeof(char));
    int i, tokenIndex = 0, tokenNo = 0;
    for (i = 0; i < strlen(line); i++) {
        char readChar = line[i];
        if (readChar == '&' || readChar == '\n') {
            if (readChar == '\n') {
                multi_token[tokenIndex++] = '\n';
                multi_token[tokenIndex] = '\0';
            }
            else if (readChar == '&') {
                multi_token[tokenIndex++] = ' ';
                multi_token[tokenIndex++] = '&';
                multi_token[tokenIndex] = '\0';
            }
            else
                multi_token[tokenIndex] = '\0';
            if (tokenIndex != 0) {
                multi_tokens[tokenNo] = (char * ) malloc(MAX_TOKEN_SIZE * sizeof(char));
                strcpy(multi_tokens[tokenNo++], multi_token);
                tokenIndex = 0;
            }
        }
        else
            multi_token[tokenIndex++] = readChar;
    }

    free(multi_token);
    multi_tokens[tokenNo] = NULL;
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
    char* filename;
    int fd;	
    int i=0;
    
	
    // Forking a child 
    pid_t PID; 
    
    PID= fork();  
  
    if (PID == -1) { 
        printf("\nUnable to fork a child !"); 
        return; 
  
       
    } 
    
    else if (PID == 0) {
    	while (tokens[++i]){
    	 
    		if(strcmp(tokens[i], ">")==0){
    			if(tokens[i+1]){ // There must be filename at "i+1" position (Only valid case)
    				fd=open(tokens[i+1], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
 	   			if (fd==-1){
 	   				printf("\nShell: could not create the file");
 	   				return;
 	   			}
 	   			dup2(fd,STDOUT_FILENO);
 	   			close(fd);
 	   			tokens[i]=NULL; //considering  the ">" sign as Null
 	   			break; 
 	   		}
 	   		
    			else if(tokens[i+2]){ // cant use space in filename
    				printf("\nShell: wrong filename");
    				return;
    			}
 	   		else
 	   			printf("\nShell: Missing filename");
 	   		}
 
    		else if(strcmp(tokens[i], "<")==0){
  			if(tokens[i+1]){ //// There must be filename at "i+1" position (Only valid case)
    				fd=open(tokens[i+1], O_RDONLY);
 	   			if (fd==-1){
 	   				printf("\nShell: could not create file");
 	   				return;
 	   			}
 	   			dup2(fd,STDIN_FILENO);
 	   			close(fd);
 	   			tokens[i]=NULL; //considering  the ">" sign as Null
 	   			break;  
    			}
    			else if(tokens[i+2]){ //cant use space in filename 
    				printf("\nShell: wrong filename");
    				return;
    			}
  
    			else
 	   			printf("\nShell: Missing filename");
 	   	}
 	}
  
        if (execvp(tokens[0], tokens) < 0) { 
            printf("\nShell: Incorrect Command"); 
        } 
        exit(0); 
        
    } else { 
        // waiting for child to terminate 
        wait(NULL);  
        return; 
    } 
}


void execution_multi(char ** tokens) { // This function executes command in background and prints PID of child

    pid_t Pid;
    Pid = fork();
    // Forking a child
    if (Pid == -1) {
        printf("\nShell: Unable to fork a child");
        return;
    }
    else if (Pid == 0) {

        if (execvp(tokens[0], tokens) < 0) {
            printf("\nShell: Incorrect command\n");
        }
        exit(0);
    }
    else { // No waiting this time for child to terminate
        printf("Pid: %d", Pid);
        return;
    }
}

 
int main(int argc, char* argv[]) {
	char  line[MAX_INPUT_SIZE];
	char  hist[MAX_INPUT_SIZE]=""; 
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
		
		
		if(line[0]=='!' && line[1]=='!' && line[2]=='\0'){
			if(hist[0]=='\0'){
				printf("No Commands in History");
				continue;
				}
			strcpy(line, hist);
			printf("%s\n", line);
		}
		
		line[strlen(line)] = '\n'; //terminate as new line comes
		strcpy(hist, line);
		
		if (line[strlen(line)-2] == '&'){ // if a command ends with &
			line[strlen(line) - 2] = '\n';
            		line[strlen(line) - 1] = '\0';
            		execution_multi(tokenize(line));
            		continue; // return shell
        
	
			
		}
		
		if (strlen(line) == 1) // if no command is entered return shell
			continue;
		multi_tokens = multi_tokenize(line); // tokenizing line based on &
		
		for(i = 0; multi_tokens[i] != NULL;i++){
			if (strlen(multi_tokens[i]) == 1)
				continue;
			else{	
			tokens = tokenize(multi_tokens[i]);
			
       		if (tokens[0][0] == 'c' && tokens[0][1] == 'd')
				chdir(tokens[1]);
				
			else if (!(strncmp(tokens[0], "exit", 4) )) {//when exit command is entered 
				//free alloted memory
				for (int j = 0; tokens[j] != NULL; j++) {
            			free(tokens[j]);
        			}
        			free(tokens);

        			for (int i = 0; multi_tokens[i] != NULL; i++) {
            			free(multi_tokens[i]);
        			}    
        			free(multi_tokens);
        			kill(0, SIGTERM);
                		exit(0);
				
			}
	
				
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
