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
int is_valid(Node* n) {
    int rows[9][10] = {0}; // Para comprobar filas (inicializado con ceros)
    int cols[9][10] = {0}; // Para comprobar columnas (inicializado con ceros)
    int subgrids[9][10] = {0}; // Para comprobar submatrices de 3x3 (inicializado con ceros)

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int num = n->sudo[i][j];
            if (num == 0) continue; // Casilla vacía

            // Verifica si el número ya se ha encontrado en la fila
            if (rows[i][num] == 1) return 0;
            rows[i][num] = 1;

            // Verifica si el número ya se ha encontrado en la columna
            if (cols[j][num] == 1) return 0;
            cols[j][num] = 1;

            // Calcula el índice de la submatriz de 3x3
            int subgrid_index = (i / 3) * 3 + (j / 3);

            // Verifica si el número ya se ha encontrado en la submatriz
            if (subgrids[subgrid_index][num] == 1) return 0;
            subgrids[subgrid_index][num] = 1;
        }
    }

    return 1; // Si no se encontraron duplicados, el nodo es válido
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