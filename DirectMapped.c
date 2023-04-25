#include <stdio.h>

#define CACHE_SIZE 32
#define BLOCK_SIZE 4
#define SETS 8

struct cache{
int tag, LRU, data[BLOCK_SIZE], valid;
};

struct cache cache[SETS];

void createCache(){
  for(int i = 0; i < SETS; i++){
    cache[i].tag = 0;
    cache[i].LRU = 0;
  }
}

int access(int input){
  int index = (input / BLOCK_SIZE) % SETS;
  unsigned int tag = input / (SETS * BLOCK_SIZE);

  if(cache[index].tag != tag){
    // miss
    cache[index].tag = tag;
    cache[index].LRU = 0;
    return 0;
  }
  else{
    cache[index].LRU++;
    return 1;
  }
}


int main(){
  int hits, accesses;
  unsigned int input;
  int hit_rate;
  createCache();

  FILE * FILE = fopen("traces.txt", "r");

  while(fscanf(FILE, "%x", &input) != EOF){
    hits += access(input);
    accesses++;
  }

  fclose(FILE);

  hit_rate = hits / accesses;
  printf("hit rate = %d", hit_rate);
  return 0;
}