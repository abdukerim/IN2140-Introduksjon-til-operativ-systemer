#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char *vowelshift(char* s, char c){
  int i, len = strlen(s) + 1;
  char *newString = malloc(sizeof(char)*len);
  for (i = 0; i < len; i++) {
    if(s[i] == 'a' || s[i]  == 'e' || s[i] == 'o'
      || s[i] == 'i' || s[i] == 'u') {
        newString[i] = c;
      }
      else {
        newString[i] = s[i];
      }
    }
    return newString;
}

int main(int argc, char *argv[]){

  char *result = vowelshift(argv[1],*argv[2]);
  printf("%s\n", result);
  free(result);
  return 0;
}
