#ifndef JL 
#define JL

#include<iostream>
using namespace std;
#include<vector>
#include<time.h>

class JumpList{
    private:
    //部分数据成员定义
    enum Jnodemode{Head,Data,Tail};
    struct Jnode{
        Jnode* after;
        Jnode* below;
        Jnodemode mode;
        pair<uint64_t, std::string> data;
        Jnode(pair<uint64_t, std::string>da,Jnodemode mo,Jnode* af=NULL,Jnode* be=NULL){
            data=da;
            mode=mo;
            after=af;
            below=be;
        }
        Jnode(Jnodemode mo){
            after=NULL;
            below=NULL;
            mode=mo;
        }
    };
    //数据成员实例
    double p;
    int max_h,height;               //vector[0]对应height为1，vector[height-1]对应最高层
    vector<Jnode*> datalist;

    void creat_newlist(){  
        Jnode* tmp=new Jnode(Head); 
        tmp->after=new Jnode(Tail);
        datalist.push_back(tmp);
        if(datalist.size()>=2){tmp->below=datalist[height-1];}
        ++height;
    }
    void clear_all(){
        Jnode* obj;
        Jnode* tmp;
        for(int i=0;i<height;++i){
            obj=datalist[i];
            while(obj!=NULL){
                tmp=obj;
                obj=obj->after;
                delete tmp;
            }
        }
        height=0;
        datalist.clear();
        creat_newlist();
    }
    Jnode* findJnode(uint64_t key);
    void print_tower(uint64_t key);
    void renew(Jnode* tmp,string data);
    void newinsert(pair<uint64_t, std::string> data);
    //insert_tower函数，在hei层中插入数据data，并返回该新建结点指针
    Jnode* insert_tower(int hei,pair<uint64_t, std::string> data);

    public:

    JumpList(double in_p=0.25,int max=20){ 
        p=in_p; 
        max_h=max; 
        height=0;
        creat_newlist();
    }
    ~JumpList(){clear_all();}
    void clear(){ clear_all();}
    string find(uint64_t key);
    void insert(pair<uint64_t, std::string> data);
    void print();
    void del(uint64_t key);
    vector<pair<uint64_t, std::string>*>* getallKV();
};


#endif 