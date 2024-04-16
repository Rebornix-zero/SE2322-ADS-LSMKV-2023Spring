#include"./LevelCache.h"


/*
 *struct LevelCache::levelcache function
*/
void LevelCache::levelcache::inserttable(TableCache* obj){
    ++nownum;
    if(this->mode==Tiering){
        data.push_back(*obj);
    }else{
        if(data.empty()){ data.push_back(*obj); return;}
        if(data.begin()->minkey>obj->maxkey){ data.push_front(*obj);return; } 
        if( prev(data.end()) ->maxkey<obj->minkey){ data.push_back(*obj);return; }
        list<TableCache>::iterator it=data.begin(),itnext=next(it);
        while(itnext!=data.end()){
            if(it->maxkey<obj->minkey&&itnext->minkey>obj->maxkey){
                data.insert(itnext,*obj);
                return;
            }
            ++it;
            ++itnext;
        }
    }
}

void LevelCache::levelcache::removetable(string delname){
    if(nownum==0)return;
    for(list<TableCache>::iterator it=data.begin();it!=data.end();++it){
        if(it->name==delname){
            data.erase(it);
            --nownum;
            return;
        }
    }
    return;
}

void LevelCache::levelcache::clear(){
    nownum=0;
    data.clear();
}



/*
 *class LevelCache function
*/
void LevelCache::restart(){
    cache_list.clear();
    filestamps.clear();
    levelcache tmp(0,Tiering);
    cache_list.push_back(tmp);
    filestamps.push_back(0);
    size=1;
}

void LevelCache::addLevlevel(){
    levelcache tmp(size);
    cache_list.push_back(tmp);
    filestamps.push_back(0);
    ++size;
}

void LevelCache::inserttable(TableCache* obj,uint64_t level){
    while(size<level+1){ addLevlevel(); }
    cache_list[level].inserttable(obj);
    ++filestamps[level];                //renew filestamp
}

void LevelCache::removetable(string delname,uint64_t level){
    while(size<level+1){ return; }
    cache_list[level].removetable(delname);
}