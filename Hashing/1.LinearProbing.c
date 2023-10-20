#include<stdio.h>
#include<stdlib.h>

typedef struct hashTable{
    int size;
    int *table;
}hashmap;

hashmap* init(int size){
    hashmap* _new = (hashmap*)malloc(sizeof(hashmap));
    _new->size = size;
    _new->table = (int*)malloc(sizeof(int)*size);

    for(int i = 0; i < size; i++){
        _new->table[i] = -1;        // assuming -1 is not a part of dataset
    }
    return _new;
}

void insert(hashmap* _hashmap, int _key){
    int _index = _key % _hashmap->size;

    while(_hashmap->table[_index] != -1){
        _index = (_index + 1) % _hashmap->size;

        if(_index == _key % _hashmap->size){
            printf("Hashtable is full\n");
            return;
        }
    }

    _hashmap->table[_index] = _key;
    printf("Key inserted at %d index.\n",_index);
    return;
}

int find(hashmap* _hashmap, int _key){
    int _index = _key % _hashmap->size;
    int _original_index = _index;

    while(_hashmap->table[_index] != _key){
        _index = (_index + 1) % _hashmap->size;

        if(_hashmap->table[_index] == -1 || _index == _original_index){
            printf("Key not found.\n");
            return -1;
        }
    }
    printf("Key found at index %d.\n",_index);
    return _index;
}

int main(){
    int size;
    printf("Enter the size of Hashtable: ");
    scanf("%d",&size);
    hashmap* hash_map = init(size);
    
    insert(hash_map,12);    
    insert(hash_map,22);
    insert(hash_map,32);
   

    find(hash_map,22);   
    return 0;
}
