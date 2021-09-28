
/*

 Project Title : Basic Example of BlockChain Technology using C(Linked List)

 Team Members :
 1)Darshan S Bharadwaj (18CS016)
 2)Chandan Rao CK (18CS015)
 3)Deepak V (18CS017)
 4)Dhanush (18CS020)


 A project on simple bloackchain techonolgy which same replicate of single linked list. It uses SHA256 encryption key which is called as hash.
 The data is stored in from of block. The block consist of two data that are:
 1)Data
 2)previous Hash
 
 A hacker cannot crack hash because it changes every 10min. Two different key is given to each user that is public and private key.
 Private key is used by user itself and its not shown to public. A public key is gievn for a user to show for whole world where anyboby can tranfer or request data from specific user.

 This technology is mainly used in cryptocurrency and other emerging stuff where more securiy is required.


 Commands To run the Code:
 1)gcc blockchain.c -lcrypto
 2)./a.out


*/

#include "stdio.h"

#include "string.h"

#include "stdlib.h"

#include "openssl/crypto.h"

#include <openssl/sha.h>

struct block {
   unsigned char prevHash[SHA256_DIGEST_LENGTH];
   int blockData;
   struct block * link;
}* head;
void addBlock(int);
void verifyChain();
void alterNthBlock(int, int);
void hackChain();
int hashCompare(unsigned char * , unsigned char * );
void hashPrinter();
unsigned char * toString(struct block);
void printBlock();
void printAllBlocks();
//SHA256(src,size,dest)
//src and dest are of type unsigned char *
void
addBlock(int data) {
   if (head == NULL) {
      head = malloc(sizeof(struct block));
      SHA256("", sizeof(""), head -> prevHash);
      head -> blockData = data;
      return;
   }
   struct block * currentBlock = head;
   while (currentBlock -> link)
      currentBlock = currentBlock -> link;
   struct block * newBlock = malloc(sizeof(struct block));
   currentBlock -> link = newBlock;
   newBlock -> blockData = data;
   SHA256(toString( * currentBlock), sizeof(currentBlock), newBlock -> prevHash);

}

void verifyChain() {
   if (head == NULL) {
      printf("BlockChain is empty! try again after adding some blocks!\n");
      return;
   }
   struct block * curr = head -> link, * prev = head;
   int count = 1;
   while (curr) {
      printf("%d\t[%d]\t", count++, curr -> blockData);
      hashPrinter(SHA256(toString( * prev), sizeof( * prev), NULL), SHA256_DIGEST_LENGTH);
      printf(" - ");
      hashPrinter(curr -> prevHash, SHA256_DIGEST_LENGTH);
      if (hashCompare(SHA256(toString( * prev), sizeof( * prev), NULL), curr -> prevHash)) {
         printf("Verified!\n");
      } else {
         printf("Verification failed");
      }
      prev = curr;
      curr = curr -> link;
   }
}

void alterNthBlock(int n, int newData) {
   struct block * curr = head;
   if (curr == NULL) {
      printf("Nth block does not exist\n");
      return;
   }
   int count = 1;
   while (count != n) {
      if (curr->link==NULL && count!=n) 
      {
         printf("Nth block does not exist!\n");
         return;
      } 
      else if (count == n) 
      	break;
      curr = curr -> link;
      count++;
   }
   printf("Before: ");
   printBlock(curr);
   curr->blockData = newData;
   printf("After :" );
   printBlock(curr);
}

void hackChain() {
   struct block * curr = head, * prev;
   if (curr == NULL) {
      printf("BlockChain is empty ! ");
      return;
   }
   while (1) {
      prev = curr;
      curr = curr -> link;
      if (curr == NULL)
         return;
      if (!hashCompare(SHA256(toString( * prev), sizeof( * prev), NULL), curr -> prevHash)) {

         hashPrinter(
            SHA256(toString( * prev), sizeof( * prev), curr -> prevHash),
            SHA256_DIGEST_LENGTH
         );
         printf(" \n ");

      }
   }
}
unsigned char * toString(struct block b) {
      unsigned char * str = malloc(sizeof(unsigned char )* sizeof(b)); 
      memcpy(str, & b, sizeof(b));
         return str;
}
      
void hashPrinter(unsigned char hash[], int length) {
         for (int i = 0; i < length; i++)
            printf("%02x", hash[i]);
   }
   int hashCompare(unsigned char * str1, unsigned char * str2) {
      for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
         if (str1[i] != str2[i])
            return 0;
      return 1;
   }
   void printBlock(struct block * b) {
      // printf("  t ",b);
      hashPrinter(b -> prevHash, sizeof(b -> prevHash));
      printf(" \t[%d] \t", b -> blockData);
      printf("%p\n", b -> link);
   }

   void printAllBlockes() {
      struct block * curr = head;
      int count = 0;
      while (curr) {
         printBlock(curr);
         curr = curr -> link;
      }
   }

   void main() {
      int c, n, r;
      
      while (1) {
      	printf("1)addBlock\n2)add n random blocks\n3)alterNthBlock\n4)printAllBlocks\n5)verifyChain\n6)hachChain\n");
         printf("\nEnter your choice: \n");
         scanf("%d", & c);
         switch (c) {
         case 1:
            printf("Enter data: ");
            scanf("%d", & n);
            addBlock(n);
            break;
         case 2:
            printf("How many blocks to enter?: ");
            scanf("%d", & n);
            for (int i = 0; i < n; i++) {
               r = rand() % (n * 10);
               printf(" Entering: %d \n ", r);
               addBlock(r);
            }
            break;
         case 3:
            printf(" Which block to alter ? : ");
            scanf("%d", & n);
            printf(" Enter value:");
            scanf("%d", & r);
            alterNthBlock(n, r);
            break;
         case 4:
            printAllBlockes();
            break;
         case 5:
            verifyChain();
            break;
         case 6:
            hackChain();
            break;
         default:
            printf(" wrong choice ! \n ");
            break;
         }
      }
   }

