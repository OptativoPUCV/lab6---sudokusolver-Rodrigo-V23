#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef unsigned short us;

typedef struct
{
   int sudo[9][9];
}Node;

Node* createNode()
{
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}
Node* copy(Node* n)
{
  Node* new=(Node*) malloc(sizeof(Node));
  *new = *n;
  return new;
}
Node* read_file (char* file_name)
{
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++)
  {
   for(j=0;j<9;j++)
   {
    if(!fscanf (file, "%d", &n->sudo[i][j]))
    {
      printf("failed to read data!");
    } 
   }
  }

  fclose (file);
  return n;
}
void print_node(Node* n)
{
  int i,j;
  for(i=0;i<9;i++)
  {
    for(j=0;j<9;j++)
    {
      printf("%d ", n->sudo[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}
int is_valid(Node* n)
{
  
  return 1;
}
List* get_adj_nodes(Node* n)
{
  List * lista = createList();

  for(us i = 0 ; i < 9 ; i++)
  {
    for(us j = 0 ; j < 9 ; j++)
    {
      if(n -> sudo[i][j] == 0)
      {
        for(us k = 1 ; k <= 9 ; k++)
        {
          Node * nodo_adj = copy(n);
          nodo_adj -> sudo[i][j] = k;
          pushBack(lista, nodo_adj);
        }
        return lista;
      }
    }
  }
  return lista;
}
int is_final(Node* n)
{
  for(us i = 0 ; i < 9 ; i++)
  {
    for(us j = 0 ; j < 9 ; j++)
    {
      if(n -> sudo[i][j] == 0)
      {
        return 0;
      }
    } 
  }
  return 1;
}
Node* DFS(Node* initial, int* cont)
{
  Stack * lista_stack = createList();
  push(lista_stack, n);

  while(!is_empty(lista_stack))
  {
    Node * current = (Node*) top(lista_stack);
    pop(lista_stack);

    if(is_final(current))
    {
      (cont++);
      return current;
    }
    List * nodos_adj = get_adj_nodes(current);
    Node * nodo_adj = (Node *) front(nodos_adj);

    while(nodo_adj != NULL);
    {
      push(lista_stack, nodo_adj);
      nodo_adj = (Node*) next(nodos_adj);
    }
    free(current);
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/