#include <stdio.h>

#define CACHE_SIZE 16
#define BLOCK_SIZE 4
#define SETS 2

typedef struct cache{
int tag, LRU, data, valid;
}Cache;

Cache cache[CACHE_SIZE][SETS];
int tagged[CACHE_SIZE][SETS];

int Least_recently_used(int num_set){
  int counter = 0;

  if(cache[set][1].valid == 0){
    counter = 1;
  }
  else if(cache[set][0].valid == 0){
    counter = 0;
  }
  else if(cache[set][1].LRU > cache[set][0].LRU){
    counter = 0;
  }
  else{
    counter = 1;
  }
}


void createCache(){
  for(int i = 0; i < SETS; i++){
    for(int j = 0; j < i; i++){
      cache[i][j].tag = 0;
      cache[i][j].LRU = 0;
    }
  }
}


int associative(int input){
  int set = (input / BLOCK_SIZE) % CACHE_SIZE;
  int tag_value = input / (CACHE_SIZE * BLOCK_SIZE);

  if(tagged[set][1] == tag_value && cache[set][0].valid){
    cache[set][1].LRU = 0;
    return 1;
  }else if(tagged[set][0] == tag_value && cache[set][0].valid){
    cache[set][0].LRU = 0;
    return 1;
  }else{
    // miss case
    int LRU = Least_recently_used(set);
    cache[set][LRU].valid = 1;
    cache[set][LRU].data = input;
    tagged[set][LRU] = tag_val
    return 0;
  }
}




int main(){
  int hits, accesses;
  unsigned int input;
  int hit_rate;
  createCache();

  FILE * FILE = fopen("traces.txt", "r");

  while(fscanf(FILE, "%x", &input) != EOF){
    hits += associative(input);
    accesses++;
  }

  fclose(FILE);

  hit_rate = hits / accesses;
  printf("hit rate = %d", hit_rate);
  return 0;
}