#include<iostream>
#include"./bloom.h"
using namespace std;

void bloom::insert(uint64_t key){
    unsigned int hash[4] = {0};
    unsigned int dest;
    MurmurHash3_x64_128(&key,sizeof(key),1,hash);
    for(int i=0;i<4;++i){
        dest=hash[i]%size;
        tmp[dest]=1;
    }
}

void bloom::get_hash4(uint64_t key,unsigned int &h1,unsigned int &h2,unsigned int &h3,unsigned int &h4){
    unsigned int hash[4] = {0};
    MurmurHash3_x64_128(&key,sizeof(key),1,hash);
    h1=hash[0]%size;
    h2=hash[1]%size;
    h3=hash[2]%size;
    h4=hash[3]%size;
}

bool bloom::find(uint64_t key){
    unsigned int hash[4] = {0};
    unsigned int dest;
    MurmurHash3_x64_128(&key,sizeof(key),1,hash);
    for(int i=0;i<4;++i){
        dest=hash[i]%size;
        if(tmp[dest]==0)return(false);
    }
    return(true);
}