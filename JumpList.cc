
#include"JumpList.h"

void JumpList::print_tower(uint64_t key){
     Jnode* tmp=findJnode(key);
     do{
        cout<<"("<<key<<":"<<tmp->data.second+") ";
        tmp=tmp->below;
     }while(tmp!=NULL);
     cout<<'\n';
}

JumpList::Jnode* JumpList::findJnode(uint64_t key){
     Jnode* tmp=datalist[height-1];
     while(tmp!=NULL){
        if(tmp->data.first==key&&tmp->mode!=Head)return(tmp);
        if(tmp->after->mode==Tail||tmp->after->data.first>key){tmp=tmp->below;}
        else{tmp=tmp->after;}
    }
    return(NULL);
}

void JumpList::newinsert(pair<uint64_t, std::string> data){
    
    int hei=1;      //设置插入高度，起始为1层
    Jnode* prenode=NULL;    //竖向插入的前一个节点指针
    Jnode* nownode;         //竖向插入的当前节点指针
    while(true){
        if(hei>max_h)return;            //若待插入层数高于最大层，则不能继续插入，返回
        if(hei>height)creat_newlist();  //若待插入层数高于现有层数，先新建一高层
        nownode=insert_tower(hei,data); //insert_tower函数，在hei层中插入数据data，并返回该新建结点指针
        if(nownode==NULL){cout<<"already insert!"<<endl;return;}    //若重复则返回NULL
        nownode->below=prenode;         //将新建节点的below连接
        prenode=nownode;                //更新prenode
        ++hei;                          //待插入层高+1

        double tmp= (double)(rand()%10000) /(double)10000;  //随机插入原则实现
        if(tmp>p)return;
    }
}

void JumpList::print(){
    Jnode* tmp=datalist[0]->after;
    while(tmp->mode!=Tail){
        print_tower(tmp->data.first);
        tmp=tmp->after;
    }
}

string JumpList::find(uint64_t key){      
    Jnode* tmp=datalist[height-1];  
    while(tmp!=NULL){              
        if(tmp->data.first==key && tmp->mode!=Head)return(tmp->data.second);            
        if(tmp->after->mode==Tail||tmp->after->data.first>key){tmp=tmp->below;} 
        else{tmp=tmp->after;}                    
    }
    return("");                          
}

void JumpList::renew(Jnode* tmp,string data){
    while(tmp!=NULL){
        tmp->data.second=data;
        tmp=tmp->below;
    }
}

void JumpList::insert(pair<uint64_t, std::string> data){
    Jnode* tmp=findJnode(data.first);
    if(tmp==NULL){
        newinsert(data);
    }else{
        renew(tmp,data.second);
    }
}

JumpList::Jnode* JumpList::insert_tower(int hei,pair<uint64_t, std::string> data){
    Jnode* tmp=datalist[hei-1];
    Jnode* tmpaf=tmp->after;
    while(tmpaf->data.first<=data.first && tmpaf->mode!=Tail){ tmp=tmpaf;tmpaf=tmp->after; }
    if( tmp->data.first==data.first && tmp->mode!=Head )return(NULL);
    tmp->after=new Jnode(data,Data,tmpaf,NULL);
    return(tmp->after);
}

vector<pair<uint64_t, std::string>*>* JumpList::getallKV(){
    vector<pair<uint64_t, std::string>*>* tmp=new vector<pair<uint64_t, std::string>*>();
    Jnode* node=datalist[0];
    while(node->mode!=Tail){
        tmp->push_back(&(node->data));
        node=node->after;
    }
    return tmp;
}

void JumpList::del(uint64_t key){
    Jnode* tmp=findJnode(key);
    if(tmp==NULL)return;
    int i=0;
    while(tmp!=NULL){
        ++i;
        tmp=tmp->below;
    }
    Jnode* tmpbefore=datalist[i-1];
    while(tmpbefore!=NULL){
        while(tmpbefore->after->data.first!=key){tmpbefore=tmpbefore->after;}
        tmp=tmpbefore->after;
        tmpbefore->after=tmp->after;
        delete tmp;
        tmpbefore=tmpbefore->below;
    }
}