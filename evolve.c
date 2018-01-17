#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <editline/readline.h>
#include <editline/history.h>

int main(int argc, char** argv) {
  puts("evolve v0.1b\n");
  puts("Press Ctrl+c to Exit\n");

  while(1) {
    char* in = readline("evol>");
    add_history(in);
    parse(in);
    free(in);
  }

  return 0;
}

int parse(char* in) {
  int l = strlen(in);

  for(int i=0; i<l; i++) {
    if(in[i] == 32) {
      printf("\n");
    }
    else {
      printf("%c\n", in[i]);
    }
  }
  return 0;
}
