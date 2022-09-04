#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_char(char ch) {
  int ascii_value = (int) ch;
  if(ascii_value >= 97 && ascii_value <= 122) {
    return ascii_value - 96;
  }
  else if(ascii_value >= 65 && ascii_value <= 90) {
    return ascii_value - 64;
  }
  else if(ascii_value == 32) {
    return 0;
  }
  else {
    return -1;
  }
}

int stringsum(char* s) {
  int sum = 0;
  int c_v = 0;
  while (*s) {
    c_v = is_char(*s);
    if(c_v == -1) {
      return -1;
    }
    sum += is_char(*s);
    s++;
  }
  return sum;
}
int locate_first(char* s, char c) {
  int i = 0;
  while(*(s +i)) {
    if(*(s +i) == c) {
      return i;
    }
    i++;
  }
  return 0;
}
int locate_last(char* s,char c) {
  for (int i = strlen(s) - 1; i > 0; i--) {
    if(s[i] == c) {
      return i;
    }
  }
  return 0;
}

int distance_between(char* s, char c) {
  int first_ch = locate_first(s,c);
  int last_ch = locate_last(s,c);
  if(first_ch == 0) {
    return -1;
  }
  else if(last_ch == first_ch) {
    return 0;
  }
  else {
    return last_ch - first_ch;
  }
}


char *string_between(char *s, char c) {
  int distance = distance_between(s,c);
  int first_one = locate_first(s,c);
  if(distance == -1) {
    return NULL;
  }
  if(distance == 0) {
    return malloc(0);
  }
  char *new_string = malloc(sizeof(char) * distance + 1);
  strncpy(new_string, s + first_one + 1,distance - 1);

  new_string[distance - 1] = '\0';
  return new_string;
}

void stringsum2(char *s, int *res) {
  *res = stringsum(s);
}
