//
//  RLEscript.c
//  This program takes in a mode, encrypt or decrypt.
//  It then uses the run-length encoding algorigthm to compress the file given.
//  It's complexity should be O(n).
//  Created by Raymond Ho on 3/13/14.

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct node node;

//  LinkedList data structure to hold characters.
struct node {
    char character;
    int count;
    node *link;
};

//  Create a new node
node *createNode(char data, int count) {
    //  Malloc space for new character
    node *tmp = (node*)malloc(sizeof (node));
    assert(tmp != NULL);
    //  Assign character to tmp
    tmp->character = data;
    tmp->count = count;
    tmp->link = NULL;
    
    return tmp;
}

//  Free the LinkedList
void freeList(node *head) {
    
    while (head != NULL) {
        node *old = head;
        head = head->link;
        free(old);
    }
}

//  This function encodes a given file.
void encode(FILE *file) {
    
    //  Create a linked list.
    node *head = NULL;
    node *curr = head;
    
    char buffer[1000];
    char data;
    
    //  Read in the file.
    for (int i = 0; fscanf(file, "%c", &data) == 1; i++)
        buffer[i] = data;
    
    int counter = 1;
    //  Iterate the buffer
    for (int i = 0; i < strlen(buffer); i++) {
        while (buffer[i] == buffer[i + 1]) {
            //  i++ skips going to the next one
            //  counter++ adds to counter
            i++; counter++;
        }
        //  Create a new node to add to linkedlist
        node *tmp = createNode(buffer[i], counter);
        //  Add new node to linkedlist
        if (head == NULL) head = tmp;
        else curr->link = tmp;
        curr = tmp;
        counter = 1;
        
    }
    printf("Input: %s\nOutput: ", buffer);
    //  Print the linked list!
    for (node *curr = head; curr != NULL; curr = curr->link) {
        if (curr->count == 1) printf("%c", curr->character);
        else printf("{%d}%c", curr->count, curr->character);
    }
    
    //  Free memory
    freeList(head);
}

//  This function decodes a given file.
void decode(FILE *file) {
    
    char buffer[1000];
    char data;
    
    //  Read in the file.
    for (int i = 0; fscanf(file, "%c", &data) == 1; i++)
        buffer[i] = data;
    
    printf("Input: %s\nOutput: ", buffer);
    
    char countString[50];
    int counter = 0;
    
    //  Iterate the buffer
    for (int i = 0; i < strlen(buffer); i++) {
        //  Read input between bracket.
        if (buffer[i] == '{') {
            for(int j = 0; buffer[i+1] != '}'; j++) {
                //  Add character (number) to the string
                countString[j] = buffer[i+1];
                //  Set the last character to null for termination
                countString[j+1] = '\0';
                i++;
            }
            //  When the last matching bracket is found
            if (buffer[i+1] == '}') {
                i += 2;
                //  Convert the string into an int
                counter = atoi(countString);
                //  Print recursively
                for (; counter > 0; counter--)
                    printf("%c", buffer[i]);
            }
        }
        //  If no bracket found, print normally.
        else {
            printf("%c", buffer[i]);
            counter = 0;
        }
    }
}
int main(int argc, char * argv[]) {
    
    //  Not using argc
    (void)argc;
    
    //  Variables to determine which mode to run.
    bool doEncode = false;
    bool doDecode = false;
    
    //  Checks first argument to detect mode.
    //  If nothing detected, exit.
    
    if (argv[1] == NULL) {
        printf("No mode detected, try '-e' or '-d'\n");
        printf("When using decode mode, the count should be inside brackets.\n");
        printf("For example: '{3}w' will give 'www'\n");
        return 1;
    }
    if (strcmp(argv[1], "-e") == 0) {
        printf("Encoding method detected.\n");
        doEncode = true;
    }
    else if (strcmp(argv[1], "-d") == 0) {
        printf("Decoding method detected.\n");
        doDecode = true;
    }
    
    if (argv[2] == NULL) {
        printf("No file found!\n");
        return 1;
    }
    //  Store the filename.
    char *filename = argv[2];
    
    //  Open the file given to read.
    FILE *file = fopen(filename, "r");
    
    //  Decides which mode
    if (doEncode) encode(file);
    else if(doDecode) decode(file);
    
    //  Closes the file when finished.
    fclose(file);
    
    return 0;
}
