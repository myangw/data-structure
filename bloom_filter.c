#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
unsigned int Hash3 (const char *Key){  
    int HashVal=0;
    for(;*Key !='\0';Key ++)
        HashVal += (*Key + 31) *11;
    return HashVal;
} 
unsigned int Hash4 (const char *Key){  
    int HashVal=0;
    for(;*Key !='\0';Key ++) 
        HashVal = (HashVal >> 5 ) + *Key++;
    return HashVal;
} 
unsigned int Hash5 (const char *Key){  
    int HashVal=0;
    for(;*Key !='\0';Key ++)
        HashVal = (HashVal << 5 ) + *Key++;
    return HashVal;
} 
unsigned int Hash6 (const char *Key){  
    int HashVal=0;
    for(;*Key !='\0';Key ++)
        HashVal = (HashVal << 5 ) + (HashVal >> 5 ) + *Key++ ;
    return HashVal;
} 
unsigned int Hash7 (const char *Key){  
    int HashVal=0;
    for(;*Key !='\0';Key ++)
        HashVal += (*Key * 11) +31;
    return HashVal;
} 
unsigned int Hash8 (const char *Key){  
    int HashVal=0;
    for(;*Key !='\0';Key ++)
        HashVal = ((HashVal << 5 ) + (HashVal >> 5 )) *11 + *Key++ ;
    return HashVal;
} 
unsigned int Hash9 (const char *Key){  
    int HashVal=0;
    for(;*Key !='\0';Key ++)   
        HashVal = (HashVal >> 5 )*11 + *Key++;
    return HashVal;
} 
unsigned int Hash10 (const char *Key){  
    int HashVal=0;
    for(;*Key !='\0';Key ++)
        HashVal = (HashVal << 5 ) *11 + *Key++;
    return HashVal;
} 

// Bloom filter functions
BloomFilters *CreateBloomFilter(int s, int b, int k){
    BloomFilters *filter = (BloomFilters *)(malloc(sizeof(BloomFilters)));
    filter->filter_size = s*b;
    filter->num_hashfunc = k;
    filter->FilterArray = (Bit *)(malloc(sizeof(Bit)* filter->filter_size));
    filter->funcs= (hashfunc_p *)(malloc(sizeof(hashfunc_p)*k));
    filter->funcs[0] = Hash1;
    filter->funcs[1] = Hash2;
    filter->funcs[2] = Hash3;
    filter->funcs[3] = Hash4;
    filter->funcs[4] = Hash5;
    filter->funcs[5] = Hash6;
    //filter->funcs[6] = Hash7;
    //filter->funcs[7] = Hash8;
    //filter->funcs[8] = Hash9;
    //filter->funcs[9] = Hash10;
    printf("b = %d \t k = %d\n", b, k);
    return filter;
}

//hash1~10 --> bit array index 안의 범위로 바꾸어 리턴.
int hash(BloomFilters *B, unsigned int num, char *word){
    return B->funcs[num](word) % B->filter_size;
}

void insert(BloomFilters *B, char *word){
    printf("%s\n",word);
    for(int i=0;i<B->num_hashfunc;i++){
        int num = hash(B, i, word);
        B->FilterArray[num].bit = 1;
        printf("a[%d] = 1\n", num);
    }
}

void lookup(BloomFilters *B, char *key){
    int count = 0;
    for(int i=0;i<B->num_hashfunc;i++){
        int num = hash(B, i, key);
        if(B->FilterArray[num].bit == 1){
            count++;
        }
    }
    if(count == B->num_hashfunc){
        printf("%s = true\n",key);
    }else{
        printf("%s = false\n",key);
    }
}

int main(int argc, const char *argv[])
{
    if(argc == 2){
        FILE *fp = fopen(argv[1], "r");
        if(fp){
            char buf[20];
            int count = 0;
            int s = 0;
            BloomFilters *filter;
            while(fgets(buf, sizeof(buf), fp)){
                if(count == 0){
                    s = buf[0] - 48;
                    int e = 0.01;
                    int b = 1.44 * log(100) / log(2);
                    int k = 0.693 * b;
                    filter = CreateBloomFilter(s,b,k);
                    count++;
                }else if(count < s+1){
                    buf[strlen(buf) - 1] = '\0';
                    insert(filter, buf);
                    count++;
                }else{
                    buf[strlen(buf) - 1] = '\0';
                    lookup(filter, buf);
                }
            }
        }else{
            printf("file open error. \n");
        }
    }else{
        printf("Please execute with an input file.\n");
    }
    return 0;
}
