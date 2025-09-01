#include"header.h"
#include<unistd.h>
#include<sys/wait.h>
#include<vector>
#include<fcntl.h>
#include<unistd.h>
using namespace std;

void ioRedirection(vector<string>v){
    bool input=false;
    bool output=false;
    bool append=false;
    string inputFile;
    string outputFile;
    for(int i=0;i<v.size();i++){
        if(v[i]=="<"&&i!=v.size()-1){
            inputFile=v[i+1];
            input=true;
            v.erase(v.begin()+i);
            v.erase(v.begin()+i+1);
        }else if(v[i]==">"&&i!=v.size()-1){
            outputFile=v[i+1];
            output=true;
            v.erase(v.begin()+i);
            v.erase(v.begin()+i+1);
        }else if(v[i]==">>"&&i!=v.size()-1){
            outputFile=v[i+1];
            output=true;
            append=true;
            v.erase(v.begin()+i);
            v.erase(v.begin()+i+1);
        }
    }
    char* command[v.size()+1];
    for(int i=0;i<v.size();i++){
        //if(v[i]==">"||v[i]==">>"||v[i]=="<")continue;
        command[i]=(char*)v[i].c_str();
    }
    command[v.size()]=NULL;
    
    int in,out;
    if(input==true){
        in=open(inputFile.c_str(),O_RDONLY);
        if(in<0){
            perror("input file does not exist");
        }
    }
    if(output==true){
        if(append==true){
            out=open(outputFile.c_str(),O_WRONLY|O_CREAT|O_APPEND);
        }else{
            out=open(outputFile.c_str(),O_WRONLY|O_CREAT|O_TRUNC);
        }
        if(out<0){
            perror("output file does not exist");
        }
    }

    pid_t pid=fork();
    if(pid==0){
        if(input==true){
            dup2(in,STDIN_FILENO);
        }
        if(output==true){
            dup2(out,STDOUT_FILENO);
        }
        execvp(command[0],command);
        perror("execvp failed");
        exit(1);
    }else{
        wait(NULL);
    }
}