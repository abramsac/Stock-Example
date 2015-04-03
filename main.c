//
//  main.c
//  Assignment6
//
//  Created by Alex Abrams on 4/18/14.
//  Copyright (c) 2014 Alex Abrams. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GenericNode.h"

typedef struct stock{
	char * stockSymbol;
	float closingSharePrice;
	float openingSharePrice;
	int numberOfShares;
	float (* getPrice) (void * S);
	float (*getTotalDollarAmount)(void* S);
	float (*getPercentChange)(void* S);
	char * (* toString)(void* S);
}stock_t;

stock_t * newStock(char *name, float closingSharePrice, float openingSharePrice, int numberOfShares, float (*getPrice)(void * S), float (*getTotalDollarAmount)(void * S), float (*getPercentChange)(void * S), char * (*toString)(void * S));

float getPrice(void * S);
float getTotalDollarAmount(void * S);
float getPercentChange(void * S);
char * toString(void * S);
int menu();
void searchClosingPrice(stock_t * stock, float b);
void searchPercentChange(stock_t * stock, float b);
void stockList(stock_t * stock);
node_t * readIn();
void deleter(node_t * node);

node_t * stocks = NULL;

int main(){
    stocks = readIn();
    float b = 0;
    int a = 0;
    while (a != 4){
        node_t * temp = NULL;
        temp = stocks;
        a = menu();
        if (a == 1){
            printf("Enter closing price. (Float)\n");
            scanf("%f", &b);
            while (temp != NULL){
                searchClosingPrice(temp->item, b);
                temp = temp->next;
            }

        }
        if (a == 2){
            printf("Enter percent change. (Float)\n"); //In decimal form such as .10, not 10%
            scanf("%f", &b);
            while (temp != NULL){
                searchPercentChange(temp->item, b);
                temp = temp->next;
            }

        }
        if (a == 3){
            while (temp != NULL){
                printf("%s\n",((stock_t *)temp->item)->stockSymbol);
                temp = temp->next;
            }

        }
        if(0 < a > 4){
            printf("Command not recognized...");
        }
    }
    deleter(stocks);
    return 0;
}

stock_t * newStock(char *name, float closingSharePrice, float openingSharePrice, int numberOfShares, float (*getPrice)(void * S), float (*getTotalDollarAmount)(void * S), float (*getPercentChange)(void * S), char * (*toString)(void * S)){
    
    stock_t * stock;
    
    stock = malloc(sizeof(*stock));
    stock->stockSymbol = (char*)malloc(sizeof(char)*20);
    int i = 0;
    char * temp = name;
    while(*temp != '\0'){
        *((stock->stockSymbol) + i) = *temp;
        temp = temp + 1;
        i++;
    }
    stock->closingSharePrice = closingSharePrice;
    stock->openingSharePrice = openingSharePrice;
    stock->numberOfShares = numberOfShares;
    stock->getPrice = getPrice;
    stock->getTotalDollarAmount = getTotalDollarAmount;
    stock->getPercentChange = getPercentChange;
    stock->toString = toString;
    return stock;
    
}

int menu(){
    int a;
	puts("Welcome to fun with stocks!!!");
	puts("Please choose from the following choices: ");
    puts("1. Search/print stock with closing price > some amount");
    puts("2. Search/print stock with % change > some amount");
    puts("3. List all the stocks using toString");
    puts("4. Quit and leave");
    scanf("%d", &a);
    return	a;
}
         
void searchClosingPrice(stock_t * stock, float b){
    if (stock->closingSharePrice > b){
        printf("%s\n", stock->toString(stock));
    }
    return;
}
         
void searchPercentChange(stock_t * stock, float b){
    if (stock->getPercentChange(stock) > b){
        printf("%s\n", stock->toString(stock));
    }
    return;
}
         
void stockList(stock_t * stock){
    printf("%s\n", stock->toString(stock));
    return;
}
         
float getPrice(void * S){
    stock_t * stock = (stock_t *) S;
    return stock->closingSharePrice;
}

float getTotalDollarAmount(void * S){
    stock_t * stock = (stock_t *) S;
    return stock->numberOfShares * stock->closingSharePrice;
}

float getPercentChange(void * S){
    stock_t * stock = (stock_t *) S;
    float x = (stock->closingSharePrice - stock->openingSharePrice)/stock->openingSharePrice;
    return x;
}

char * toString(void * S){
    stock_t * stock = (stock_t *) S;
    return stock->stockSymbol;
}

node_t * readIn(){
    
    FILE *inf = fopen("/Users/alexabrams/Downloads/stocks", "r"); //opens a file for READING
    char buffer[80];
    char *name, *opening,*closing, *shares; //need these since you read data in as a char string then convert to float or int
    float opens, closes;
    int numshares;
        
    if (inf == NULL){
        puts("no file you idiot");
        exit(1);
    }

    node_t * head = (node_t *)malloc(sizeof(node_t));
        
    int count = 0;
        
    while (1) {
        fgets(buffer, 80, inf); //reads in at most 80 char from a line
        if (feof(inf)) //this checks to see if the special EOF was read
            break;     //if so, break out of while and continue with your main
        name = (char *) malloc(sizeof(char)*20);
        opening = (char *) malloc(sizeof(char)*20);
        closing = (char *) malloc(sizeof(char)*20);
        shares = (char *) malloc(sizeof(char)*20);
            
        name = strtok(buffer, " ");//get first token up to space
        opening = strtok(NULL, " ");  //get next token up to space
        closing = strtok(NULL, " ");  //get next token up to space
        shares = strtok(NULL, "\n"); //get next token up to \n
            
        opens = atof(opening);
        closes = atof(closing);
        numshares = atoi(shares);
        printf("line: %s %f %f %i\n",name,opens,closes,numshares);
            count++;
        //now you need to insert the square into a node of the generic link list
        stock_t * stock = (stock_t *)malloc(sizeof(stock_t));
        stock = newStock(name, opens, closes, numshares, getPrice, getTotalDollarAmount, getPercentChange, toString);
        node_t * node = (node_t *)malloc(sizeof(node));
        (node->item) = (stock_t *) stock;
        insertAtEnd(node, head);
        printf("%s\n", ((stock_t *)node->item)->stockSymbol);
        
        }
        
        fclose(inf);  //Closes a file.
        printf("%d new records were read\n", count);
        //Hpefully, at this point, the data is nicely stored in the generic link list
    return head;
}

void deleter(node_t * node){
    node_t * next = node->next;
    while (next != NULL){
        free(node);
        node = next;
        next = node->next;
    }
}










