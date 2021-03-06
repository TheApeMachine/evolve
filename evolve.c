#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <editline/readline.h>
#include <editline/history.h>
#include <regex.h>

#define MAX_ERROR_MSG 0x1000

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

  struct id_token  {char* sym;};
  struct op_token  {char* sym;};
  struct num_token {int   sym;};
  struct newline   {char* sym;};

  regex_t r;
  const char * id_tokens;
  id_tokens = "echo|quit";

  compile_regex (&r, id_tokens);
  match_regex (&r, in);
  regfree (&r);

  return 0;
}

int compile_regex(regex_t* r, const char* id_tokens) {
  int status = regcomp(r, id_tokens, REG_EXTENDED|REG_NEWLINE);
  if(status != 0) {
    char error_message[MAX_ERROR_MSG];
    regerror(status, r, error_message, MAX_ERROR_MSG);
    printf("Regex error compiling '%s\n'", id_tokens, error_message);
    return 1;
  }

  return 0;
 }

 int match_regex (regex_t * r, const char * to_match)
 {
     /* "P" is a pointer into the string which points to the end of the
        previous match. */
     const char * p = to_match;
     /* "N_matches" is the maximum number of matches allowed. */
     const int n_matches = 10;
     /* "M" contains the matches found. */
     regmatch_t m[n_matches];

     while (1) {
         int i = 0;
         int nomatch = regexec (r, p, n_matches, m, 0);
         if (nomatch) {
             printf ("No more matches.\n");
             return nomatch;
         }
         for (i = 0; i < n_matches; i++) {
             int start;
             int finish;
             if (m[i].rm_so == -1) {
                 break;
             }
             start = m[i].rm_so + (p - to_match);
             finish = m[i].rm_eo + (p - to_match);
             if (i == 0) {
                 printf ("$& is ");
             }
             else {
                 printf ("$%d is ", i);
             }
             printf ("'%.*s' (bytes %d:%d)\n", (finish - start),
                     to_match + start, start, finish);
         }
         p += m[0].rm_eo;
     }
     return 0;
 }
