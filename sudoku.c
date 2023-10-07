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
Node* DFS(Node* initial, int* cont) {
    Stack* stack = createStack();
    push(stack, initial);

    // Utilizar un conjunto para rastrear los estados visitados
    // Esto evita agregar nodos duplicados a la pila
    // Puedes implementar un conjunto personalizado o utilizar una biblioteca de conjuntos
    // Aquí se supone un conjunto simple basado en una matriz booleana
    int visited[9][9] = {{0}};

    while (!is_empty(stack)) {
        Node* current = top(stack);
        pop(stack);
        (*cont)++;

        if (is_final(current)) {
            // Se encontró una solución
            return current;
        }

        // Obtener nodos adyacentes válidos y agregarlos a la pila
        List* adj_nodes = get_adj_nodes(current);
        Node* adj_node = first(adj_nodes);
        while (adj_node) {
            // Verificar si el estado ya fue visitado
            int row = 0, col = 0;
            // Calcular las coordenadas de la casilla modificada en adj_node
            // (deberías implementar esta parte de acuerdo a tu estructura de datos)
            if (!visited[row][col]) {
                push(stack, adj_node);
                visited[row][col] = 1; // Marcar el estado como visitado
            } else {
                // Liberar la memoria del nodo adyacente duplicado
                free(adj_node);
            }
            adj_node = next(adj_nodes);
        }

        // Liberar memoria del nodo actual
        free(current);
    }

    // No se encontró una solución
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