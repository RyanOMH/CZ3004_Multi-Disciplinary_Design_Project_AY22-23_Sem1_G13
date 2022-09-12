#include "Q.h"
#include <stdlib.h>

void queue_init(Queue *q){
	q->ll.head = NULL;
	q->ll.size = 0;
	q->ll.tail = NULL;
}

int enqueue(Queue *q, Cmd item){
   return insertNode(&(q->ll), q->ll.size, item);
}

Cmd dequeue(Queue *q){
   Cmd item;
   item = ((q->ll).head)->item;
   removeNode(&(q->ll), 0);
   return item;
}

int isEmptyQueue(Queue *q){
   if ((q->ll).size == 0)
      return 1;
   return 0;
}

ListNode * findNode(LinkedList *ll, int index){

   ListNode *temp;

   if (ll == NULL || index < 0 || index >= ll->size)
      return NULL;

   temp = ll->head;

   if (temp == NULL || index < 0)
      return NULL;

   while (index > 0){
      temp = temp->next;
      if (temp == NULL)
         return NULL;
      index--;
   }

   return temp;
}

int insertNode(LinkedList *ll, int index, Cmd value){

   ListNode *pre, *cur;

   ListNode *node = malloc(sizeof(ListNode));
   node->item.MAGNITUDE = value.MAGNITUDE;
   node->item.MOTOR_DIR = value.MOTOR_DIR;
   node->item.SERVO_DIR = value.SERVO_DIR;

   if (ll == NULL || index < 0 || index > ll->size + 1)
      return -1;

   // If empty list or inserting first node, need to update head pointer
   if (ll->head == NULL || index == 0){
      cur = ll->head;
      ll->head = node;
      ll->tail = ll->head;
      ll->head->next = cur;
      ll->size++;
      return 0;
   }

   // Inserting as new last node
   if (index == ll->size){
      pre = ll->tail;
      cur = pre->next; //NULL
      pre->next = node;
      ll->tail = pre->next;
      pre->next->next = cur;
      ll->size++;
      return 0;
   }

   // Find the nodes before and at the target position
   // Create a new node and reconnect the links
   if ((pre = findNode(ll, index-1)) != NULL){
      cur = pre->next;
      pre->next = node;

      if (index == ll->size)
         ll->tail = pre->next;

      pre->next->next = cur;
      ll->size++;
      return 0;
   }

   return -1;
}

int removeNode(LinkedList *ll, int index){

   ListNode *pre, *cur;

   // Highest index we can remove is size-1
   if (ll == NULL || index < 0 || index >= ll->size)
      return -1;

   // If removing first node, need to update head pointer
   if (index == 0){
      cur = ll->head->next;
      free(ll->head);
      ll->head = cur;
      ll->size--;

      if (ll->size == 0)
         ll->tail = 0;

      return 0;
   }

   // Find the nodes before and after the target position
   // Free the target node and reconnect the links
   if ((pre = findNode(ll, index-1)) != NULL){

      // Removing the last node, update the tail pointer
      if (index == ll->size - 1){
         ll->tail = pre;
         free(pre->next);
         pre->next = NULL;
      }
      else{
         cur = pre->next->next;
         free(pre->next);
         pre->next = cur;
      }
      ll->size--;
      return 0;
   }

   return -1;
}
