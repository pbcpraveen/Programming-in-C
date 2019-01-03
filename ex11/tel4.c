 #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>

  #define MAXLEN 100
  #define N      100

  struct entry {
    int number;
    char name[MAXLEN];
  };
  typedef struct entry Entry;

  int read_entries (Entry* e[]);
  Entry* get_node (char* name, char* number);
  void print_entries (Entry* e[], int n);
  int write_entries (Entry* e[], int n);
  void print_entry(Entry* e[],int p);
  int search_number(int p,Entry* e[],int n);
  int insert(Entry p,Entry* e[],int* n);
  int delete(int p,Entry* e[],int* n);

  int main ()
  {
    Entry* telephones[N];
    int n;
    char line[MAXLEN];
    char choice;
    char name[MAXLEN];
    int number,res;
    n = read_entries (telephones);
   // print_entries(telephones,n);
    while (1)
      {
        printf ("? ");
        fgets (line, MAXLEN, stdin);
        choice = line[0];
        switch (choice)
          {
          case 's':
            sscanf (line+1, "%d", &number);
            int pos=search_number(number,telephones,n);
            if(pos<n)
               print_entry(telephones,pos);
            else
               printf("No such record\n");
            break;
          case 'i':
            sscanf (line+1, "%d%s", &number, name);
            Entry p;
            p.number=number;
            strcpy(p.name,name);
            res= insert(p,telephones,&n);
            if(res==0)
                 printf("Record already exists\n");
            break;
          case 'd':
            sscanf (line+1, "%d", &number);
            res=delete(number,telephones,&n);
            break;
          case 'q':
            write_entries(telephones, n);
            print_entries(telephones,n);
            return 0;
      default:
        printf("Invalid choice\n");
          }
  }
  return 0;
  }
  void print_entry(Entry* e[],int p)
  {
    printf("%s\t %d\n",e[p]->name,e[p]->number);
  }
  void print_entries (Entry* e[], int n)
  {
    for (int i = 0; i < n; i++)
      printf ("%d,%s,%d\n", i, e[i]->name, e[i]->number);
  }

  int read_entries (Entry* e[])
  {
    FILE* fp;
    int i;
    char line[MAXLEN];
    char* name;
    char* number;
    
    fp = fopen ("telephone.in", "r");
    for (i = 0; fgets(line, MAXLEN, fp) != NULL; i++)
      {
        name = strtok (line, "|");
        number = strtok (NULL, "|");
        e[i] = get_node (name, number);
      }
    fclose(fp);
    return i;
  }

  Entry* get_node (char* name, char* number)
  {
    Entry* t = (Entry*) malloc (sizeof(Entry));
    strcpy(t->name, name);
    t->number = atoi(number);
    return t;
  }

  int write_entries (Entry* e[], int n)
  {
    int i;
    FILE* fp;
    
    fp = fopen ("telephone.in", "w");
    for (i = 0; i < n; i++)
      fprintf(fp, "|%s|%d|\n", e[i]->name, e[i]->number);
    fclose (fp);
  }
  int search_number(int p,Entry* e[],int n)
  {
    for(int i=0;i<n;i++)
      {
        if(e[i]->number==p)
          {
            return i;
          }
      }
    return n;
  }
  int insert(Entry p,Entry* e[],int* n)
    {
      int pos=search_number(p.number,e,*n);
      if(pos==*n)
        {
          e[*n]=(Entry*)malloc(sizeof(Entry));
          e[pos]->number=p.number;
          strcpy(e[pos]->name,p.name);
          (*n)++;
          return 1;
        }
      return 0;
    }
   int delete(int p,Entry* e[],int* n)
      {
        int pos=search_number(p,e,*n);
        if(pos<(*n))
          {
            for(int i=pos;i<(*n)-1;i++)
              {
                e[i]=e[i+1];
              }
            (*n)--;
            return 1;
          }
        return 0;
      }
