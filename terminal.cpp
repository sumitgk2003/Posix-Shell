#include "header.h"
#include<iostream>
#include<sys/utsname.h>
#include<stdlib.h>
#include<unistd.h>
#include<pwd.h>
#include<string.h>
#include<vector>


using namespace std;

void echo(vector<string>v){
    for(int i=1;i<v.size();i++){
        cout<<v[i]<<" ";
    }cout<<endl;
}

// string pwd(){
//     char cwd[1000];
//     getcwd(cwd,1000);
//     return cwd;
// }

string username(){
    uid_t uid=getuid();
    struct passwd *pw=getpwuid(uid);
    return pw->pw_name;
}

string hostname(){
    char hostName[100];
    gethostname(hostName,100);
    return hostName;
}

vector<string> tokenizeTokens(string command){
    vector<string>v;
    char* com=strdup(command.c_str());
    char* token=strtok(com," \t");
    while(token!=NULL){
        v.push_back(token);
        token=strtok(NULL," \t");
    }
    return v;
}

vector<string> tokenizeCommands(string input){
    vector<string>commands;
    char* in=strdup(input.c_str());
    char* command=strtok(in,";");
    while(command!=NULL){
        commands.push_back(command);
        command=strtok(NULL,";");
    }
    return commands;
}



int main(){
    while(1){
        cout<<username()<<"@"<<hostname()<<":~"<<"$ ";
        string input;
        getline(cin,input);
        vector<string>c=tokenizeCommands(input);
        vector<vector<string>>commands;
        for(auto i:c){
            vector<string>command=tokenizeTokens(i);
            commands.push_back(command);
        }
        if(input=="exit")break;

        for(auto i:commands){
            if(i[0]=="echo"){
                echo(i);
            }else if(i[0]=="cd"){

            }else if(i[0]=="pwd"){
                cout<<pwd()<<endl;
            }else if(i[0]=="ls"){
                lsmain(i);
            }
        }
        
    }
}