#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcre.h>
#include <unistd.h>
#include <ncurses.h>


char printStream[1024];
FILE* cpuinfo;
FILE* outfile;
WINDOW* mainwin;
//function prototypes:
void flushData();
void printToStream(const char* buffer, int option);



int main(int argc, char* argv[]){
  mainwin = initscr();
  cpuinfo = fopen("/proc/cpuinfo", "r");
  if(cpuinfo == NULL){
    printf("FATAL: couldn't open required files\n");
    exit(0);
  }
  
  noecho();
  keypad(mainwin, TRUE);
  
  char buffer[1024];
  const char* model_errorptr;
  int model_erroroffset;
  int model_ovector[30];
  const char* model_pattern = "model name	:.+|cpu MHz		:.+";
//  const char* model_pattern = "[^0-9]";
  pcre* model_re = pcre_compile(model_pattern,
			  0,
			  &model_errorptr,
 			  &model_erroroffset,
			  NULL);

  if(model_re == NULL){
    printf("FATAL: PCRE compilation 1 failed\n");
    exit(0);
  }
  
  while(1){
    while(fgets(buffer, 2048, cpuinfo) != NULL && strcmp(buffer, "\n") != 0){
      sscanf(buffer, "%[^\n]", buffer);
      int model_rc = pcre_exec(model_re,
			       NULL,
			       buffer,
			       strlen(buffer),
			       0,
			       0,
			       model_ovector,
			       30);
      if(model_rc >= 0){
        if(buffer[0] == 'c'){
	  mvwaddstr(mainwin, 1, 0, buffer);
	  printToStream(buffer, 0);
	}else {
	  mvwaddstr(mainwin, 0, 0, buffer);
	  printToStream(buffer, 1);
	}
	
        flushData();
	refresh();
      }
    }
    fclose(cpuinfo);
    cpuinfo = fopen("/proc/cpuinfo", "r");
    sleep(1);
  }
  endwin();
  return 0;
}

void flushData(){
  outfile = fopen("smonitor/info.txt", "w");
  /*  if(fwrite(printStream, 1, strlen(printStream), outfile)==0){
    printf("Failed to write to file\n");  
    }*/
  char buffer[100];
  fprintf(outfile, "%s", printStream);
  sprintf(buffer, "printed: %s", printStream);
  mvwaddstr(mainwin, 3, 0, buffer);
  fclose(outfile);
}

void printToStream(const char* buffer, int option){
  if(option == 1){
    strncpy(printStream, buffer, 1024);
  }else if(option == 0){
    strncat(printStream, buffer, 1024-strlen(printStream)); 
  }
}
