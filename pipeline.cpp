#include"header.h"
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;

void pipeline(vector<string>v){
    vector<vector<string>>parts;
    vector<string>v1;
    for(auto i:v){
        if(i=="|"){
            parts.push_back(v1);
            v1.clear();
            continue;
        }
        v1.push_back(i);
    }
    parts.push_back(v1);
    // for(auto i:parts){
    //     for(auto j:i){
    //         cout<<j<<" ";
    //     }cout<<endl;
    // }

    int n=parts.size();
    int pipes[n-1][2];
    for(int i=0;i<n-1;i++){
        pipe(pipes[i]);
    }
    for(int i=0;i<n;i++){
        if(fork()==0){
                bool input=false;
                bool output=false;
                bool append=false;
                string inputFile;
                string outputFile;
                int j=0;
                while(1){
                    if(j>=parts[i].size()-1)break;
                    if(parts[i][j]=="<"&&j!=parts[i].size()-1){
                        inputFile=parts[i][j+1];
                        input=true;
                        parts[i].erase(parts[i].begin()+j);
                        parts[i].erase(parts[i].begin()+j);
                        j--;
                    }else if(parts[i][j]==">"&&j!=parts[i].size()-1){
                        outputFile=parts[i][j+1];
                        output=true;
                        parts[i].erase(parts[i].begin()+j);
                        parts[i].erase(parts[i].begin()+j);
                        j--;
                    }else if(parts[i][j]==">>"&&j!=parts[i].size()-1){
                        outputFile=parts[i][j+1];
                        output=true;
                        append=true;
                        parts[i].erase(parts[i].begin()+j);
                        parts[i].erase(parts[i].begin()+j);
                        j--;
                    }
                    j++;
                }
                // for(int j=0;j<parts[i].size();j++){
                //     cout<<parts[i][j]<<" ";
                // }cout<<endl;

                // char* command[parts[i].size()+1];
                // for(int j=0;j<parts[i].size();j++){
                //     //if(v[i]==">"||v[i]==">>"||v[i]=="<")continue;
                //     command[j]=(char*)parts[i][j].c_str();
                // }
                // command[parts[i].size()]=NULL;
                
                if(input&&i==0){
                int in=open(inputFile.c_str(),O_RDONLY);
                    if(in<0){ 
                        perror("input file"); 
                        exit(1); 
                    }
                    dup2(in,STDIN_FILENO);
                    close(in);
                }else if(i!=0){
                    dup2(pipes[i-1][0], STDIN_FILENO);
                }
                if(output&&i==n-1) {
                    int out;
                    if(append){
                        out=open(outputFile.c_str(),O_WRONLY| O_CREAT|O_APPEND,0644);
                    }else{
                        out=open(outputFile.c_str(),O_WRONLY|O_CREAT|O_TRUNC,0644);
                    }
                    if(out<0){ 
                        perror("output file"); 
                        exit(1); 
                    }
                    dup2(out, STDOUT_FILENO);
                    close(out);
                }else if(i!=n-1) {
                    dup2(pipes[i][1],STDOUT_FILENO);
                }
                
                for(int j=0;j<n-1;j++){
                    close(pipes[j][0]);
                    close(pipes[j][1]);
                }
        
                char* command[parts[i].size()+1];
                for(int j=0;j<parts[i].size();j++){
                    command[j]=(char*)parts[i][j].c_str();
                }
                command[parts[i].size()]=NULL;
                execvp(command[0],command);
                perror("execvp failed");
                exit(1);
                //exit(0);
            
        }
    }
    for(int i=0;i<n-1;i++){
            close(pipes[i][0]);
            close(pipes[i][1]);
        }
    for(int i=0;i<n;i++){
        wait(NULL);
    }
}