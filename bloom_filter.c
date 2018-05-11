#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _Bit{
    unsigned int bit : 1;
} Bit;

// hash function pointer
typedef unsigned int (*hashfunc_p)(const char*);

//Bloom Filter
typedef struct _BloomFilters{
    int filter_size;
    int num_hashfunc;
    Bit *FilterArray;
    hashfunc_p *funcs; //function pointer array for hash functions
} BloomFilters;

//Hash functions
unsigned int Hash1 (const char *Key){
    int HashVal=0;
    for(;*Key !='\0';Key ++)
        HashVal += *Key + 31;
    return HashVal;
 } 
unsigned int Hash2 (const char *Key){  
    int HashVal=0;
    for(;*Key !='\0';Key ++)   
        HashVal += *Key * 31;
    return HashVal;
 } 
unsigned int Hash3 (const char *Key){  int HashVal=0;
  for(;*Key !='\0';Key ++)
      HashVal += (*Key + 31) *11;
  return HashVal;
 } 
unsigned int Hash4 (const char *Key){  int HashVal=0;
  for(;*Key !='\0';Key ++) 
      HashVal = (HashVal >> 5 ) + *Key++;
  return HashVal;
 } 
unsigned int Hash5 (const char *Key){  int HashVal=0;
  for(;*Key !='\0';Key ++)
      HashVal = (HashVal << 5 ) + *Key++;
  return HashVal;
 } 
unsigned int Hash6 (const char *Key){  int HashVal=0;
  for(;*Key !='\0';Key ++)
      HashVal = (HashVal << 5 ) + (HashVal >> 5 ) + *Key++ ;
  return HashVal;
 } 
unsigned int Hash7 (const char *Key){  int HashVal=0;
  for(;*Key !='\0';Key ++)
      HashVal += (*Key * 11) +31;
  return HashVal;
 } 
unsigned int Hash8 (const char *Key){  int HashVal=0;
  for(;*Key !='\0';Key ++)
      HashVal = ((HashVal << 5 ) + (HashVal >> 5 )) *11 + *Key++ ;
  return HashVal;
 } 
unsigned int Hash9 (const char *Key){  int HashVal=0;
  for(;*Key !='\0';Key ++)   
      HashVal = (HashVal >> 5 )*11 + *Key++;
  return HashVal;
 } 
unsigned int Hash10 (const char *Key){  int HashVal=0;
  for(;*Key !='\0';Key ++)
      HashVal = (HashVal << 5 ) *11 + *Key++;
  return HashVal;
 } 

// Bloom filter functions
BloomFilters *CreateBloomFilter(int s, int b, int k){
    BloomFilters *filter = (BloomFilters *)(malloc(sizeof(BloomFilters)));
    filter->filter_size = s*b;
    filter->num_hashfunc = k;
    filter->FilterArray = (Bit *)(malloc(sizeof(Bit)*s));
    filter->funcs= (hashfunc_p *)(malloc(sizeof(hashfunc_p)*(filter->num_hashfunc)));
    filter->funcs[0] = Hash1;
    filter->funcs[1] = Hash2;
    filter->funcs[2] = Hash3;
    filter->funcs[3] = Hash4;
    filter->funcs[4] = Hash5;
    filter->funcs[5] = Hash6;
    filter->funcs[6] = Hash7;
    filter->funcs[7] = Hash8;
    filter->funcs[8] = Hash9;
    filter->funcs[9] = Hash10;
    printf("b = %d \t k = %d\n", b, k);
    return filter;
}

void insert(BloomFilters *B, char *key){
    printf("%s\n",key);
    int hashval = B->funcs[0](key);
    for(int i=0;i<B->num_hashfunc;i++){
        int num = B->funcs[i](key);
        B->FilterArray[num].bit = 1;
    }
    printf("%d",hashval);
}

void lookup(BloomFilters *B, char *key){
   }

int hash(BloomFilters *B, unsigned int key){
//hash1~hash10 함수들 값이 bit array 개수보다 큼 --> bit array index로 바꾸는 함수 (?)
//
//
}
int main(int argc, const char *argv[])
{
    int s = 7; //from user input
    int e = 0.01;
    int b = 9 ;//2.88/log(2); //왜 9??  
    int k = 0.693 * b;
    char *text = "data";
    BloomFilters *filter = CreateBloomFilter(s,b,k);
    insert(filter, text);
    return 0;
}
