//
//  GenericNode.h
//  Assignment6
//
//  Created by Alex Abrams on 4/18/14.
//  Copyright (c) 2014 Alex Abrams. All rights reserved.
//

typedef struct node{
	void * item;
	struct node * next;
    struct node * prev;
}node_t;

void insertAtEnd(node_t * node, node_t * header);
void * insertAtIndex(node_t * header, int index, node_t * node);
void deleteNodeNumber(node_t * header, int index);
