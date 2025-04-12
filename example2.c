/*parcurgerge  graf cu DFS/BFS*/

//Scuze acceptate

#include <stdlib.h>

#include <stdio.h>
typedef struct Node
    {
        int vertex;
        struct Node *next;
} Node;

typedef struct Graph
    {
         int numVertices;
         Node **adjLists;
    }
Graph;

/// utils

    Node *create_node(int vertex)
    {
        Node *newNode = malloc(sizeof(Node));

        newNode->vertex = vertex;
        newNode->next = NULL;
        return newNode;
    }

    Graph *create_graph(int numVertices)
    {
        int i;
        Graph *graph = malloc(sizeof(Graph));

        graph->numVertices = numVertices;
        graph->adjLists = malloc(numVertices * sizeof(Node *));

        for (int i = 0; i < numVertices; i++)
        {
            graph->adjLists[i] = NULL;
        }

        return graph;
}

void add_edge(Graph *graph, int src, int dest)
    {
        Node *newNode = create_node(dest);

        newNode->next = graph->adjLists[src];
        graph->adjLists[src] = newNode;
        newNode = create_node(src);
        newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void print_graph(Graph *graph)
    {
          int i;
          for (i = 0; i < graph->numVertices; i++)
            {
                Node *temp = graph->adjLists[i];

                printf("Nod %d: ", i);

                while (temp)
                  {
                      printf("%d ", temp->vertex);

                      temp = temp->next;
                  }

                  printf("NULL\n");
                }
            }

    int has_direct_path(Graph *graph, int src, int dest)
    {
      Node *temp = graph->adjLists[src];

      while (temp)
        {
            if (temp->vertex == dest)
            {
              return 1;
            }
            temp = temp->next;
        }
        return 0;
}
    int main()
    {
          int numVertices, numEdges, i, src, dest, restaurantA, restaurantB;

          printf("Numarul de restaurante(noduri): ");
          scanf("%d", &numVertices);

          printf("numarul de leegaturi directe(muchii):");
          scanf("%d", &numEdges);

          Graph *graph = create_graph(numVertices);

          printf("Introduceti cele %d muchii (ex: 0 1 pentru muchie intre 0 si 1):\n", numEdges);
          for (i = 0; i < numEdges; i++)
            {
            scanf("%d %d", &src, &dest);

            add_edge(graph, src, dest);
            }

           printf("Verificare drum direct intre restaurantele:\n");
           printf("Restaurant A: ");
           scanf("%d", &restaurantA);
           printf("Restaurant B: ");
           scanf("%d", &restaurantB);

           if (has_direct_path(graph, restaurantA, restaurantB))
             {
                 printf("Exista drum direct intre %d si %d.\n", restaurantA, restaurantB);
             }
             else
             {
               printf("Nu exista drum direct intre %d si %d.\n", restaurantA, restaurantB);
             }

             return 0;
}