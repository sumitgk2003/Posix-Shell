#include"header.h"
#include<iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;
void pinfo(vector<string>v){
    int pid;
    if(v.size()==1){
        pid=getpid();
    }else{
        pid=strtoll(v[1].c_str(),0,10);
    }
    
    string spath="/proc/"+to_string(pid)+"/stat";
    int stat=open(spath.c_str(),O_RDONLY);
    if(stat==-1){
        perror("Process not Found");
        return;
    }
    char statData[5000];
    int bytesRead=read(stat,statData,4999);
    close(stat);
    statData[bytesRead]='\0';
    //cout<<statData;
    string statt=statData;
    vector<string>statFile=tokenizeTokens(statt);
    // for(auto i:statFile){
    //     cout<<i<<endl;
    // }
    cout<<"Process Status: "<<statFile[2];
    if(strtoll(statFile[4].c_str(),0,10)==tcgetpgrp(STDIN_FILENO))cout<<"+";
    cout<<endl;
    cout<<"Virtual Memory: "<<statFile[22]<<endl;
    
    char exepath[5000];
    string epath="/proc/"+to_string(pid)+"/exe";
    int exe=readlink(epath.c_str(),exepath,4999);
    if(exe!=-1){
        exepath[exe]='\0';
    }else{
        perror("exe file not found");
        return;
    }
    cout<<"Executable Path: "<<exepath<<endl;
}