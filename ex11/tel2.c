#include <stdio.h>
#include <string.h>

#define MAXLEN 100
#define N      100

struct entry {
  int number;
  char name[MAXLEN];
};
typedef struct entry Entry;

int read_entries (Entry* e[]);

int main ()
{
  Entry* telephones[N];
  int n;
  
  n = read_entries (telephones);
  return 0;
}

int read_entries (Entry* e[])
{
  FILE* fp;
  int i;
  char line[MAXLEN];
  char* name;
  char* number;
  
  fp = fopen ("telephone.in", "r");
  for (i = 0; fgets(line, MAXLEN, fp) != NULL; i++) {
    //fputs (line, stdout);
    name = strtok (line, "|");
    number = strtok (NULL, "|");
    printf ("%s,%s\n", name, number);
  }
  fclose(fp);
  return i;
}
