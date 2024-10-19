#include <stdio.h>
#include <stdlib.h>

struct queue{
  char* myQueue;
  int cur_size;
  int max_size;
  int cur_point;
};

typedef struct queue Queue;

void trigger(char* pointer, Queue* queue);

void push(char val, Queue* queue);
char pop(Queue* queue);
void resetData(Queue* queue);
int notFinished(Queue* queue);

int main(int argc, char** argv){
    FILE* file;
    char op;
    char* MemBlock = (char*)malloc(30000);
    char* pointer = MemBlock;  
    Queue First;
    First.myQueue = (char*)malloc(1000);
    First.max_size = 1000;
    First.cur_point = 0;
    First.cur_size = 0;
    Queue* FirstPoint = &First;
    

    file = fopen(argv[1], "r");
    if (file == NULL) {
      printf("Error in opening file");
      return 1;
    }
    while(1) {
      op = fgetc(file);
      if (op == EOF)
        break;
      push(op, FirstPoint);
    }
    fclose(file);
    trigger(pointer, FirstPoint);
    free(First.myQueue);
    free(MemBlock);
}

void trigger(char* pointer, Queue* queue){
  Queue* QueueSec;
  QueueSec = malloc(sizeof(*QueueSec));
  QueueSec->myQueue = (char*)malloc(1000);
  QueueSec->max_size = 1000;
  QueueSec->cur_point = 0;
  QueueSec->cur_size = 0;
  int trackFlag = 0;
  queue->cur_point = 0;
  while (!notFinished(queue)){
    char op = pop(queue);
    if (trackFlag == 1){
      push(op, QueueSec);
    }
    switch (op){
        case '>':
          pointer+=1;
          break; 
        case '<':
          pointer-=1;
          break; 
        case '+':
          *pointer+=1;
          break; 
        case '-':
          *pointer-=1;
          break; 
        case ']':
          QueueSec->cur_size--;
          trackFlag = 0;
          while (*pointer != 0){
            trigger(pointer, QueueSec);
          }
          resetData(QueueSec);
          break; 
        case '[':
          trackFlag = 1;
          break; 
        case ',':
          scanf(" %c", pointer);
          break; 
        case '.':
          printf("%c", *pointer);
          break; 
        default:
          break;
      }
    
  }
  free(QueueSec->myQueue);
  free(QueueSec);
}
int notFinished(Queue* queue){
  return (queue->cur_size == queue->cur_point);
}


void push(char val, Queue* queue){
  queue->myQueue[queue->cur_size] = val;
  queue->cur_size++;
  if (queue->cur_size == queue->max_size){
    char* temp = (char*)malloc(queue->max_size*2);
    for (int i = 0; i < queue->cur_size; i++){
      temp[i] = queue->myQueue[i];
    }
    free(queue->myQueue);
    queue->myQueue = temp;
    queue->max_size *= 2;
  }
}

char pop(Queue* queue){
  return queue->myQueue[queue->cur_point++];
}
void resetData(Queue* queue){
  queue->cur_point = 0;
  queue->cur_size = 0;
}
