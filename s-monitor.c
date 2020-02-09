#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcre.h>
#include <unistd.h>
#include <ncurses.h>

int main(int argc, char* argv[]){
  WINDOW* mainwin = initscr();
  FILE* cpuinfo = fopen("/proc/cpuinfo", "r");
  if(cpuinfo == NULL){
    printf("FATAL: couldn't open /proc/cpuinfo\n");
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
	}else {
	  mvwaddstr(mainwin, 0, 0, buffer);
	}
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
