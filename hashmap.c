#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    long pos = hash(key, map->capacity);
    Pair *array = createPair(key, value);
    if (map->buckets[pos] == NULL || map->buckets[pos]->key == NULL){
        map->buckets[pos] = array;
        map->size++;
        map->current = pos;
        return;
    }
    if (strcmp(map->buckets[pos]->key, key) == 0){
        map->buckets[pos]->value = value;
        free(array);
        map->current = pos;
        return;
    }
    for (long i = 1 ; i < map->capacity ; i++){
        long k = hash(pos + 1, map->capacity); 
        if (map->buckets[k] == NULL || map->buckets[k]->key == NULL){
            map->buckets[k] = array;
            map->size++;
            map->current = k;
            return;
        }
        if (strcmp(map->buckets[k]->key, key) == 0){
            map->buckets[k]->value = value;
            free(array);
            map->current = k;
            return;
        }
    }
    free(array);
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap *Map = (HashMap *)malloc(sizeof(HashMap));
    Map->buckets = (Pair **)malloc(sizeof(Pair *)* capacity);
    for (long i = 0 ; i < capacity ; i++){
        Map->buckets[i] = NULL;
    }

    Map->size = 0;
    Map->capacity = capacity;
    Map->current = -1;

    return Map;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
