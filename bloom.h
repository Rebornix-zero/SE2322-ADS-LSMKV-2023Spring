#ifndef BLOOM
#define BLOOM
#include<iostream>
#include"./MurmurHash3.h"
using namespace std;

//
class bloom{
    private:
    unsigned int size;
    char* tmp;

    public:
    bloom(unsigned int kb=10){ 
        size=1024*kb; 
        tmp=new char[size]{0}; 
    }
    ~bloom(){ delete []tmp; }
    void clear(){ for(int i=0;i<size;++i)tmp[i]=0; }
    void print(){ for(int i=0;i<size;++i)cout<<(char)(tmp[i]+'0'); }
    void insert(uint64_t key);
    bool find(uint64_t key);
    const char* get_list(){return tmp;}
    void get_hash4(uint64_t key,unsigned int &h1,unsigned int &h2,unsigned int &h3,unsigned int &h4);
};


#endif