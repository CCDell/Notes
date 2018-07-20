#include "inter.h"



int main(int argc, char * argv[]){
  const static int sigils = 4;
  const static char * sigil[] = {"-s", "-t", "-p", "-h"};
  const static char * help =
    "This is a note-taking program.\n-s is the Subject, -t is the Title, -p is the place this note was found (for example, found on twitter). Only -p is optional";

  if (argc == 1){ // This program needs input prefixed with a sigil (above) to work.
    throw("error, main: Not enough arguments");
  }
  else if(strcmp(argv[1], sigil[3]) == 0){ // If the help sigil is inputed give them help
    throw(help);
  }

  char * subj = getPromptStr(sigil[0], sigil, sigils, argv, argc);
  char * title = getPromptStr(sigil[1], sigil, sigils, argv, argc);
  char * place = getPromptStr(sigil[2], sigil, sigils, argv, argc);

  if(subj == NULL || title == NULL || place == NULL)
    throw("error, main: please enter a subject, title, and place");

  FILE * file = fopen(NOTES_FILENAME, "a");

  fprintf(file,"%s\n", __DATE__);
  fprintf(file, "%s, ", subj);
  fprintf(file, "%s. ", title);
  fprintf(file, "%s.\n", place);

  fclose(file);
  
  return 0;
}

// Checks to see if prompt is in args[]. Ensures that the prompt preceedes an argument as opposed to a second
// prompt (in const char * prompts[]).
char * getPromptStr(const char * prompt, const char * prompts[], const int promptLen, char * args[], int argc){
  short loc = 0;
  short promptCount = 0;
  
  for(int i = 0; i < argc; ++i){
    if(strcmp(args[i], prompt) == 0){
      loc = i;
      ++promptCount;
    }
  }
  if (promptCount == 0) return NULL;

  if (1 < promptCount){
    throw("error, getPromptStr: too many instances of the prompt\n");
  }
  if(argc-1 <= loc){
    throw("error, getPromptStr: no command after the prompt\n");
  }
  if(inStrArray(prompts,args[loc+1],promptLen)){
    throw("error, getPromptStr: next string is a prompt\n");
  }
  return args[loc+1];
}

short inStrArray(const char * arr[], char * val, int arrlen){
  for(int i = 0; i < arrlen; ++i){
    if(strcmp(arr[i], val)==0)
      return 1;
  }
  return 0;
}

/*
  note -s Books -t easat of eden -p twitter
*/
