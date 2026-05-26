#include <stdio.h>

void swap_strings(char **a, char **b) {
  char *tmp = *a;
  *a = *b;
  *b = tmp;
}

int main() {
  char *s1 = "Hello";
  char *s2 = "Goodbye";

  printf("Before: s1 = %s, s2 = %s\n", s1, s2);
  swap_strings(&s1, &s2);
  printf("After:  s1 = %s, s2 = %s\n", s1, s2);

  char *s3 = "foo";
  char *s4 = "bar";

  printf("Before: s3 = %s, s4 = %s\n", s3, s4);
  swap_strings(&s3, &s4);
  printf("After:  s3 = %s, s4 = %s\n", s3, s4);

  return 0;
}


/*output:
Before: s1 = Hello, s2 = Goodbye
After:  s1 = Goodbye, s2 = Hello
Before: s3 = foo, s4 = bar
After:  s3 = bar, s4 = foo*/