#include"header.h"
#include<unistd.h>
#include<sys/wait.h>
#include<vector>
#include<fcntl.h>
using namespace std;

void ioRedirection(vector<string>v){
    bool input=false;
    bool output=false;
    bool append=false;
    string inputFile;
    string outputFile;
    int i=0;
    while(1){
        if(i>=v.size()-1)break;
        if(v[i]=="<"&&i!=v.size()-1){
            inputFile=v[i+1];
            input=true;
            v.erase(v.begin()+i);
            v.erase(v.begin()+i);
            i--;
        }else if(v[i]==">"&&i!=v.size()-1){
            outputFile=v[i+1];
            output=true;
            v.erase(v.begin()+i);
            v.erase(v.begin()+i);
            i--;
        }else if(v[i]==">>"&&i!=v.size()-1){
            outputFile=v[i+1];
            output=true;
            append=true;
            v.erase(v.begin()+i);
            v.erase(v.begin()+i);
            i--;
        }
        i++;
    }
    // for(int i=0;i<v.size();i++){
    //     cout<<v[i]<<" ";
    // }cout<<endl;
    char* command[v.size()+1];
    for(int i=0;i<v.size();i++){
        //if(v[i]==">"||v[i]==">>"||v[i]=="<")continue;
        command[i]=(char*)v[i].c_str();
    }
    command[v.size()]=NULL;
    
    int in=-1;
    int out=-1;
    if(input==true){
        in=open(inputFile.c_str(),O_RDONLY);
        if(in<0){
            perror("input file does not exist");
            exit(1);
        }
    }
    if(output==true){
        if(append==true){
            out=open(outputFile.c_str(),O_WRONLY|O_CREAT|O_APPEND,0644);
        }else{
            out=open(outputFile.c_str(),O_WRONLY|O_CREAT|O_TRUNC,0644);
        }
        if(out<0){
            perror("output file does not exist");
            exit(1);
        }
    }

    pid_t pid=fork();
    if(pid==0){
        setpgid(0,0);
        if(input==true){
            dup2(in,STDIN_FILENO);
            close(in);
        }
        if(output==true){
            dup2(out,STDOUT_FILENO);
            close(out);
        }
        execvp(command[0],command);
        perror("execvp failed");
        exit(1);
    }else{
        setpgid(pid,pid); 
        foreground_pid=pid;
        int status;
        waitpid(pid, &status, WUNTRACED);
        foreground_pid=-1;
    }
    if(in!=-1)close(in);
    if(out!=-1)close(out);
}