#include "the_apple.h"
#include <stdio.h>

int locateworm(char* apple) {
  int i = 0;
  while(*(apple + i)) {
    if(*(apple + i) =='w') {
      return i;
    }
  }
  return 0;
}

int string_len(char* s) {
  int i = 0;
  while (*(s + i)) {
    i++;
  }
  return i;
}
int removeworm(char* apple) {
  int i = 0;
  int worm_length = 0;
  while (*(apple + i)) {
    if(*(apple + i) == 'w' || *(apple + i) == 'o' || *(apple + i) == 'r' || *(apple + i) == 'm') {
      *(apple + i) = ' ';
    }
    i++;
  }
  return i;
}

int int main(void) {
  int worm_start = locateworm(apple);
  if (worm_start) {
      printf("Worm at %i.\n", located_at);
  }
  int apple_length = string_len(apple);
  char apple_copy[apple_length + 1];

  for (int i = 0; i < apple_length + 1; i++) {
      apple_copy[i] = apple[i];
  }

  int worm_length = removeworm(new_apple);
  if (worm_length) {
      printf("%i characters removed.\n", worm_length);
      printf("Apple without worm : \n %s", apple_copy);
  } else {
      printf("Original apple has not worm...\n");
  }
  return 0;
}
/*

int removeworm(char* apple) {
    int idx = 0;
    int num_removed_chars = 0;

    // Iterate through the string
    while ( *(apple + idx) ) {

        // If any worm character is found, increment counter
        switch ( *(apple + idx) ) {
        case 'w':
            *(apple + idx) = ' ';
            num_removed_chars++;
            break;
        case 'o':
            *(apple + idx) = ' ';
            num_removed_chars++;
            break;
        case 'r':
            *(apple + idx) = ' ';
            num_removed_chars++;
            break;
        case 'm':
            *(apple + idx) = ' ';
            num_removed_chars++;
            break;
        default:
            // Any non-worm character leads here
            // If num_removed_chars is more than 1, we are after the worm and can return
            if (num_removed_chars) {
                return num_removed_chars;
            }
        }

        idx++;
    }

    return 0;
}

int main(void) {
    int located_at = locateworm(apple);
    if (located_at) {
        printf("Found worm at index %i.\n", located_at);
    }
    int apple_length = length_of_string(apple);
    char new_apple[apple_length + 1];

    for (int i = 0; i < apple_length + 1; i++) {
        new_apple[i] = apple[i];
    }

    int num_removed = removeworm(new_apple);
    if (num_removed) {
        printf("Removed worm from apple. It was %i characters long.\n", num_removed);
        printf("The apple looks like this now : \n %s", new_apple);
    } else {
        printf("No worm to remove...\n");
    }

    return 0;
}
*/
