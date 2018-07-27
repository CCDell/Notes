#include "inter.h"



int main(int argc, char * argv[]){
  const static int sigils = 4;
  const static char * sigil[] = {"-s", "-t", "-p", "-h"};
  const static char * help =
    "This is a note-taking program.\n-s is the Subject, -t is the Title, -p is the place this note was found (for example, found on twitter). 'look' as the first argument will open your current notes.";
  char * info[] = {NULL, NULL, NULL};
  FILE * file;

  if (argc == 1){ // This program needs input prefixed with a sigil (above) to work.
    throw("error, main: Not enough arguments");
  }
  else if(strcmp(argv[1], sigil[3]) == 0){ // If the help sigil is inputed give them help
    throw(help);
  }
  else if(strcmp(argv[1], "look") == 0 ){
    system("emacs ~/Desktop/notes");
    exit(0);
  }
  
  file = fopen(NOTES_FILENAME, "a");

  fprintf(file,"%s, %s\n", __DATE__, __TIME__);
  for(int i = 0; i < NOTES_INFO_LEN; ++i){
    info[i] = calloc(NOTES_MAXSTR, sizeof(char));
    memset(info[i], '\0', NOTES_MAXSTR);
    
    getPromptStr(sigil[i], sigil, sigils, argv, argc, info[i]);
    
    fprintf(file, "%s. ", info[i]);
  }

  fprintf(file,"\n");
  
  for(int i =0; i < NOTES_INFO_LEN; ++i)
    free(info[i]);
  fclose(file);
  
  return 0;
}

// Checks to see if prompt is in args[]. Ensures that the prompt preceedes an argument as opposed to a second
// prompt (in const char * prompts[]).
void getPromptStr(const char * prompt, const char * prompts[], const int promptLen,
		  char * args[], int argc, char * ret){
  short loc = 0;
  short promptCount = 0;
  char temp[NOTES_MAXSTR] = {'\0'};
  memset(temp, '\0', NOTES_MAXSTR);
  
  for(int i = 0; i < argc; ++i){
    if(strcmp(args[i], prompt) == 0){
      loc = i;
      ++promptCount;
    }
  }
  if (promptCount == 0)
    throw("error, getPromptStr: not all prompts present");

  if (1 < promptCount){
    throw("error, getPromptStr: too many instances of the prompt\n");
  }
  if(argc-1 <= loc){
    throw("error, getPromptStr: no command after the prompt\n");
  }
  if(inStrArray(prompts,args[loc+1],promptLen)){
    throw("error, getPromptStr: next string is a prompt\n");
  }
  
  for(int i = 0; loc + i + 1 < argc && !inStrArray(prompts, args[loc+i+1],promptLen) ; ++i){
    
    char space[2] = {' ', '\0'};
    strcat(ret, space);
    strcat(ret, args[loc+i+1]);
  }
}

short inStrArray(const char * arr[], char * val, int arrlen){
  for(int i = 0; i < arrlen; ++i){
    if(strcmp(arr[i], val)==0)
      return 1;
  }
  return 0;
}

