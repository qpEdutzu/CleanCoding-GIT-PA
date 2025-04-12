#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Graph {
    int vertexCount;
    int* visited;
    struct Node** adjacencyList;
} Graph;

typedef struct Stack {
    int top;
    int capacity;
    int* array;
} Stack;

Node* createNode(int value) {
    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph* graph, int source, int destination) {
    if (source >= graph->vertexCount || destination >= graph->vertexCount) return;
    Node* newNode = createNode(destination);
    if (newNode == NULL) return;
    newNode->next = graph->adjacencyList[source];
    graph->adjacencyList[source] = newNode;

    newNode = createNode(source);
    if (newNode == NULL) return;
    newNode->next = graph->adjacencyList[destination];
    graph->adjacencyList[destination] = newNode;
}

Graph* createGraph(int vertexCount) {
    Graph* graph = malloc(sizeof(Graph));
    if (graph == NULL) return NULL;
    graph->vertexCount = vertexCount;
    graph->visited = malloc(vertexCount * sizeof(int));
    graph->adjacencyList = malloc(vertexCount * sizeof(Node*));
    if (graph->visited == NULL || graph->adjacencyList == NULL) {
        free(graph->visited);
        free(graph->adjacencyList);
        free(graph);
        return NULL;
    }
    for (int i = 0; i < vertexCount; i++) {
        graph->adjacencyList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

Stack* createStack(int capacity) {
    Stack* stack = malloc(sizeof(Stack));
    if (stack == NULL) return NULL;
    stack->array = malloc(capacity * sizeof(int));
    if (stack->array == NULL) {
        free(stack);
        return NULL;
    }
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push(Stack* stack, int value) {
    if (stack->top < stack->capacity - 1) {
        stack->top++;
        stack->array[stack->top] = value;
    }
}

void DFS(Graph* graph, Stack* stack, int vertexNumber, int target, int* found) {
    if (vertexNumber >= graph->vertexCount) return;
    if (vertexNumber == target) {
        *found = 1;
        return;
    }
    graph->visited[vertexNumber] = 1;
    push(stack, vertexNumber);
    Node* current = graph->adjacencyList[vertexNumber];
    while (current != NULL) {
        int connectedVertex = current->data;
        if (connectedVertex < graph->vertexCount && graph->visited[connectedVertex] == 0) {
            DFS(graph, stack, connectedVertex, target, found);
        }
        current = current->next;
    }
}

void insertEdges(Graph* graph, int edgeCount, int vertexCount) {
    printf("Add %d edges (from 1 to %d, enter as space-separated pairs, e.g., 1 2)\n", edgeCount, vertexCount);
    for (int i = 0; i < edgeCount; i++) {
        int source, destination;
        if (scanf("%d %d", &source, &destination) != 2) {
            printf("Invalid input format. Use space-separated numbers.\n");
            break;
        }
        source--;
        destination--;
        if (source >= 0 && source < vertexCount && destination >= 0 && destination < vertexCount) {
            addEdge(graph, source, destination);
        } else {
            printf("Invalid vertex numbers. Must be between 0 and %d.\n", vertexCount - 1);
        }
    }
}

void wipe(Graph* graph, int vertexCount) {
    for (int i = 0; i < vertexCount; i++) {
        graph->visited[i] = 0;
    }
}

int canReach(Graph* graph, int vertexCount, Stack* stack, int vertex1, int vertex2) {
    int found = 0;
    DFS(graph, stack, vertex1, vertex2, &found);
    wipe(graph, vertexCount);
    return found;
}

int main() {
    int vertexCount, edgeCount;

    printf("How many vertices does the graph have? ");
    scanf("%d", &vertexCount);

    printf("How many edges does the graph have? ");
    scanf("%d", &edgeCount);

    Graph* graph = createGraph(vertexCount);
    if (graph == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    Stack* stack = createStack(2 * vertexCount);
    if (stack == NULL) {
        printf("Stack creation failed\n");
        free(graph->visited);
        free(graph->adjacencyList);
        free(graph);
        return 1;
    }

    insertEdges(graph, edgeCount, vertexCount);

    int vertex1, vertex2;
    printf("Enter first vertex (0 to %d): ", vertexCount - 1);
    scanf("%d", &vertex1);
    printf("Enter second vertex (0 to %d): ", vertexCount - 1);
    scanf("%d", &vertex2);

    int result = canReach(graph, vertexCount, stack, vertex1, vertex2);
    printf("There is a direct or indirect path between %d and %d: %s\n", vertex1, vertex2, result ? "Yes" : "No");

    free(stack->array);
    free(stack);
    for (int i = 0; i < vertexCount; i++) {
        Node* current = graph->adjacencyList[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->visited);
    free(graph->adjacencyList);
    free(graph);

    return 0;
}