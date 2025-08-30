#include "header.h"
#include<iostream>
#include<unistd.h>
#include<string.h>
#include<vector>
using namespace std;

void cd(vector<string>v){
    if(v.size()>2){
        cout<<"Too many arguments"<<endl;
        return;
    }
    if(v.size()==1){
        chdir(direc.home.c_str());
        direc.prev=direc.current;
        direc.current=direc.home;
        return;
    }
    if(v[1]=="~"){
        chdir(direc.home.c_str());
        direc.prev=direc.current;
        direc.current=direc.home;
        return;
    }
    if(v[1]=="-"){
        chdir(direc.prev.c_str());
        swap(direc.current,direc.prev);
        return;
    }
    string path;
    if(v[1][0]!='/'){
        path=pwd()+"/"+v[1];
    }else{
        path=v[1];
    }
    if(chdir(path.c_str())!=0){
        perror("cd failed");
    }else{
        direc.prev=direc.current;
        direc.current=path;
    }
}