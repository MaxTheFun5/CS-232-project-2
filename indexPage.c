/* File: indexPage.c */
/* Author: Britton Wolfe */
/* Date: September 3rd, 2010 */

/* This program indexes a web page, printing out the counts of words on that page */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* TODO: structure definitions */

struct trieNode{
  struct trieNode* children[26];
  int occurances;
};




/* NOTE: int return values can be used to indicate errors (typically non-zero)
   or success (typically zero return value) */

/* TODO: change this return type */
void indexPage(const char* url);

int addWordOccurrence(const char* word, const int wordLength,
		       /* TODO: other parameters you need */
           struct trieNode* node
          );

void printTrieContents(/* TODO: any parameters you need */ struct  trieNode* root, char buffer[],
   int depth//start at zero
);

int freeTrieMemory(/* TODO: any parameters you need */ struct  trieNode* root
    );

int getText(const char* srcAddr, char* buffer, const int bufSize);

int main(int argc, char** argv){
  /* TODO: write the (simple) main function

  /* argv[1] will be the URL to index, if argc > 1 */

  return 0;
}

/* TODO: define the functions corresponding to the above prototypes */

/* TODO: change this return type */
void indexPage(const char* url)
{}

//NOTE: This function assumes the Trie is already initialized
int addWordOccurrence(const char* word, const int wordLength,
		       /* TODO: other parameters you need */ struct trieNode* node)
{
  if(node == NULL){
    return -1;
  }

  for(int i = 0; i < wordLength; i++){
    //subract 'a' to get the ASCII value of the character, 'a' = 0, etc. This formats the trie in a 
    //consistant, alphabetical  manner.
    int index = word[i]-'a';
    if(node->children[index] == NULL){

      //Allocates the next node
      node->children[index] = malloc(sizeof(struct trieNode));
      if(node->children[index] == NULL){
        prinf("COULD NOt ALLOCATE MEMORY");
      }

      //Sets the next node's word occurances to zero
      node->children[index]->occurances = 0;

      //Allocates the next nodes array of children
      for(int j =0; j < 26; j++){
        node->children[index]->children[j] = NULL;
      }
    }
    node = node->children[index];
  }
  node->occurances++;
  return node->occurances;
}

void printTrieContents(/* TODO: any parameters you need */ struct trieNode*root, char buffer[], int depth)
{
  if(root == NULL){
    return;
  }

  if(root->occurances > 0){
      buffer[depth] = '\0';
      printf("%s: %d\n", buffer, root->occurances);
  }

  for(int i = 0; i < 26; i++){
    //Higher i means the buffer receievs the corresponding ASCII character via character arithmetic
    buffer[depth] = i+'a';

    //Depth is used to keep track of the position in the current word
    printTrieContents(root->children[i], buffer, depth+1);
  }
  
}

int freeTrieMemory(/* TODO: any parameters you need */struct trieNode* root)
{
  if(root == NULL){
    return;
  }
  for(int i = 0; i < 26; i++){
    freeTrieMemory(root->children[i]);
  }
  free(root);
}

/* You should not need to modify this function */
int getText(const char* srcAddr, char* buffer, const int bufSize){
  FILE *pipe;
  int bytesRead;

  snprintf(buffer, bufSize, "curl -s \"%s\" | python3 getText.py", srcAddr);

  pipe = popen(buffer, "r");
  if(pipe == NULL){
    fprintf(stderr, "ERROR: could not open the pipe for command %s\n",
	    buffer);
    return 0;
  }

  bytesRead = fread(buffer, sizeof(char), bufSize-1, pipe);
  buffer[bytesRead] = '\0';

  pclose(pipe);

  return bytesRead;
}
