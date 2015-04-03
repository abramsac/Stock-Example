//
//  GenericNode.c
//  Assignment6
//
//  Created by Alex Abrams on 4/18/14.
//  Copyright (c) 2014 Alex Abrams. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "GenericNode.h"

void insertAtEnd(node_t * node, node_t * header){
    node_t * temp = header;
    if (header->item == NULL){
        header->item = node->item;
        return;
    }
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = node;
    return;
}

void * insertAtIndex(node_t * header, int index, node_t * node){
    node_t * temp = header;
    int i = 0;
    
    if (index == 0){
        node->next = header;
        header->prev = node;
        header = node;
        return header;
    }
    while (i < index - 1){
        temp = temp->next;
    }
    node_t * nxt = temp->next;
    nxt->prev = node;
    node->next = nxt;
    temp->next = node;
    node->prev = temp;
    return header;
}

void deleteNodeNumber(node_t * header, int index){
    node_t * temp = header;
    int i = 0;
    while(i < index){
        temp = temp->next;
    }
    (temp->prev)->next = temp->next;
    (temp->next)->prev = temp->prev;
    free(temp);
    
}


