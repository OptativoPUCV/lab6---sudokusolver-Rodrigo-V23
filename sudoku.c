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
  us filas[9][10] = {0};
  us columnas[9][10] = {0};
  us sub_matriz[9][10] = {0};

  for(us i = 0 ; i < 9 ; i++)
  {
    for(us j = 0 ; j < 9 ; j++)
    {
      us valor = n -> sudo[i][j];
      if(valor == 0) continue;

      if(filas[i][valor] == 1) return 0;
      filas[i][valor] = 1;

      if(columnas[j][valor] == 1) return 0;
      columnas[j][valor] = 1;

      us sub_matriz_ind = (i / 3) * 3 + (j / 3);

      if(sub_matriz[sub_matriz_ind][valor] == 1) return 0;
      sub_matriz[sub_matriz_ind][valor] = 1;
    }
  }
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
          if(is_valid(nodo_adj))
          {
            pushBack(lista, nodo_adj); 
          }
          else
          {
            free(nodo_adj);
          }
        }
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
Node* DFS(Node* n, int* cont) {
    Stack* stack = createStack();
    push(stack, n);

    while (!is_empty(stack)) {
        Node* current = top(stack);

        // Verifica si el estado actual es final (solución)
        if (is_final(current)) {
            return current; // Se encontró una solución
        }

        // Obtiene los nodos adyacentes válidos
        List* adj_nodes = get_adj_nodes(current);
        
        // Verifica si hay nodos adyacentes válidos
        if (!is_empty(adj_nodes)) {
            // Obtiene el primer nodo adyacente
            Node* next_node = front(adj_nodes);
            popFront(adj_nodes);

            // Agrega el primer nodo adyacente al stack
            push(stack, next_node);
        } else {
            // Si no hay nodos adyacentes válidos, elimina el nodo actual del stack
            pop(stack);
        }

        // Libera la memoria de la lista de nodos adyacentes
        clean(adj_nodes);
        free(adj_nodes);

        // Libera la memoria del nodo actual
        free(current);

        (*cont)++; // Incrementa el contador de iteraciones
    }

    return NULL; // No se encontró una solución
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