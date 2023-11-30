#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n" 
#define MAX_COMMAND_SIZE 255  
#define MAX_NUM_ARGUMENTS 10    
int history_filled = 0;

int main()
{
    char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );
    int pidIterator=0;
    int pidBox [15];    
    char * history[15];
    int history_index = 0;
    int histIterator=0;
    for( histIterator=0;histIterator<15;histIterator++)
    {
        history[histIterator] = (char* ) malloc (sizeof(char) * 255);
    }
    int numCommand=0;
    while( 1 )
    {
        printf ("msh> ");
        while( !fgets (cmd_str, MAX_COMMAND_SIZE, stdin) );
        if(cmd_str[0]=='!')
        {
            int newNum = atoi(&cmd_str[1]);
            cmd_str = history[newNum];
        }
        strncpy(history[history_index++], cmd_str, 255);
        if(history_index>14)
        {
            history_index = 0;
            history_filled = 1;
        }
        char *token[MAX_NUM_ARGUMENTS];
        int token_count = 0;
        char *argument_ptr;                                         
        char *newCommandString;
        char *working_str  = strdup( cmd_str ); 
        char *working_root = working_str;
        while ( ( (argument_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) && 
                (token_count<MAX_NUM_ARGUMENTS))
        {
            token[token_count] = strndup( argument_ptr, MAX_COMMAND_SIZE );
            if( strlen( token[token_count] ) == 0 )
            {
                token[token_count] = NULL;
            }
            token_count++;
        }
        if(( cmd_str[0]==' ')|| (cmd_str[0] == '\n') ) continue;
        int ret;
        if(strcmp(token[0],"cd")==0)
        {
            ret = chdir( token[1] );  
        }
        else if(strcmp(token[0],"quit")==0)
        {
            exit(0); 
        }
        else if(strcmp(token[0],"exit")==0)
        {
            exit(0);
        }
        else if(strcmp(token[0],"showpids")==0)
        {
            int j=0;
            while(pidBox[j]!=0)
            {
                printf("%d: %d\n",j,pidBox[j]);
                j++;
            }
        }
        else if(strcmp(token[0],"history")==0)
        {  
            int f=0;
            int histIndex = history_index;
            if(history_filled == 0)
            {
                for(f=0;f<histIndex;f++)
                {
                    printf("%d: %s",f,history[f]);    
                }
            }
            else
            { 
                for(f=0;f<15;f++)
                {
                    printf("%d: %s",f,history[f]);                              
                }
            }
        } 
        else
        {
            int token_index  = 0;
            pid_t pid = fork( );  
            if( pid == 0 )
            {
                char *arguments[4];
                arguments[0] = ( char * ) malloc( strlen( token[token_index] ) );
                arguments[1] = ( char * ) malloc( strlen( "-l" ) );
                strncpy( arguments[0], token[token_index], strlen( token[token_index] ) );
                strncpy( arguments[1], "-1", strlen( "-1" ) );
                arguments[2] = NULL;
                int ret2 = execvp( token[0], &token[0] ); 
                if( ret2 == -1 )
                {
                    printf("%s: Command not found.\n", token[token_index]);
                    exit(0);
                }
                if( ret == -1)
                {
                    printf("there is no directory\n");
                }
            }
            else 
            {
                int status;
                wait( & status );
                if( pidIterator>14) pidIterator = 0;
                pidBox[pidIterator] = pid;
                pidIterator++;
            } 
        } 
        free( working_root );
    }
    return 0;
}