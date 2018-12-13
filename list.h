//
//  list.h
//  somefuck
//
//  Created by Дмитрий Маслюков on 11/12/2018.
//  Copyright © 2018 Дмитрий Маслюков. All rights reserved.
//

#ifndef list_h
#define list_h
#include<stdlib.h>
enum order {ASC=1, DESC=-1};
template <typename obj>
class List{
private:
    obj*Objects;
    int __mem_res;
    int length;
    void Rloc(){
        Objects = (obj*)realloc(Objects,(__mem_res)*sizeof(obj));
    }
public:
    typedef int(*ordrel)(obj,obj);
    typedef int(*eqrel)(obj,obj);
    typedef int(*sigma)(int);
    
    int Length(){
        return length;
    }
    
    List(int n = 1){
        length = 0;
        __mem_res = n;
        Objects = (obj*)malloc(n*sizeof(obj));
    }
    ~List(){
        free(Objects);
    }
    
    List &operator=(List &l){
        __mem_res = l.length;
        Rloc();
        length = l.length;
        for(int i = 0; i<length; i++)
            Objects[i] = l[i];
        return *this;
    }
    
    obj &operator[] (int n) {
        if (n<0)
            n = length -n;
        if(n<length)
            return Objects[n];
        else
            throw("Index out of bounds");
    }
    
    int Find(obj O, eqrel F=[](obj a, obj b)->int{return a ==b;}){
        for(int i = 0;i<length;i++)
            if(F(Objects[i],O)==1)
                return i;
        return -1;
    }
    
    List Reshuffle(sigma s){ //sigma must be biective
        List<obj> list = List<obj>(length);
        list = *this;
        for(int i = 0; i<length; i++)
            list[s(i)] = Objects[i];
        return list;
    }
    
    void Append(obj O){
        if(length==__mem_res){
             __mem_res<<=1;
            Rloc();
           
        }
        Objects[length] = O;
        length++;
    }
    
    void Remove(int i){
        if (i<0 || i >=length)
            throw "Out of bounds";
        else{
            for(int j = i+1;j<length;j++)
                Objects[j-1] = Objects[j];
            length--;
            if(length<=__mem_res>>1){
                __mem_res >>=1;
                Rloc();
                
            }
        }
           
    }
    
    void _memory(){
        __mem_res = length;
        Rloc();
        
    }
    
    
    void Sort(ordrel f){
        int j,k,i;
        obj buf;
        for(k = length/2; k > 0; k /=2)
            for(i = k; i < length; i++)
            {
                buf = Objects[i];
                for(j = i; j>=k; j-=k)
                {
                    if(f(buf,Objects[j-k])==0)
                        Objects[j] = Objects[j-k];
                    else
                        break;
                }
                Objects[j] = buf;
            }
        

    }
    
   
    
    
};




#endif /* list_h */
