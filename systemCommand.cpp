#include "header.h"
#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;

void systemCommand(vector<string>v){
    bool wait=true;
    if(v[v.size()-1]=="&"){
        wait=false;
        v.pop_back();
    }
    char* command[v.size()+1];
    for(int i=0;i<v.size();i++){
        command[i]=(char*)v[i].c_str();
    }
    command[v.size()]=NULL;
    pid_t pid=fork();
    if(pid==0){
        execvp(command[0],command);
        perror("execvp failed");
        exit(1);
    }
    int status;
    if(wait==true){
        waitpid(pid,&status,0);
    }else{
        cout<<pid<<endl;
    }
}