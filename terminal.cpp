#include "header.h"
#include<iostream>
#include<sys/utsname.h>
#include<stdlib.h>
#include<unistd.h>
#include<pwd.h>
#include<string.h>
#include<vector>
#include<readline/readline.h>
#include<readline/history.h>
Directory direc;
using namespace std;

// void echo(vector<string>v){
//     for(int i=1;i<v.size();i++){
//         cout<<v[i]<<" ";
//     }cout<<endl;
// }

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
    read_history(".hist");
    while(1){
        string user="\033[32m"+username()+"@"+hostname()+":";
        //cout<<"\033[32m"<<username()<<"@"<<hostname()<<":";
        if(direc.home==pwd())user+="~";
        else user+=pwd();
        user+="$ \033[0m";
        //string input="";
        //cout<<"fkjsdh";
        char* input_cstr = readline(user.c_str()); 
        if(input_cstr==NULL){
            write_history(".hist");
            break;
        }
        string input(input_cstr);
        //getline(cin,input);
        size_t pos=input.find_first_not_of(" \t");
        if (pos==string::npos) continue;
        writeHistory(input);
        add_history(input_cstr);
        //if(input=="exit")break;
        //cout<<"fewlk23232";
        vector<string>c=tokenizeCommands(input);
        vector<vector<string>>commands;
        //cout<<"fewlk";
        for(auto i:c){
            vector<string>command=tokenizeTokens(i);
            commands.push_back(command);
        }
        //cout<<"dfd";
        bool exit=false;
        for(const auto &i:commands){
            bool io=false;
            bool pipe=false;
            for(auto j:i){
                if(j=="|"){
                    pipeline(i);
                    pipe=true;
                    break;
                }
            }
            if(pipe==true)continue;
            for(auto j:i){
                if(j=="<"||j==">"||j==">>"){
                    ioRedirection(i);
                    io=true;
                    break;
                }
            }
            if(io==true)continue;
            if(i[0]=="exit"){
                exit=true;
                break;
            }else if(i[0]=="echo"){
                echo(i);
            }else if(i[0]=="cd"){
                cd(i);
            }else if(i[0]=="pwd"){
                cout<<pwd()<<endl;
            }else if(i[0]=="ls"){
                lsmain(i);
            }else if(i[0]=="search"){
                search(i);
            }else if(i[0]=="history"){
                historymain(i);
            }else if(i[0]=="pinfo"){
                pinfo(i);
            }else{
                systemCommand(i);
            }
        }
        if(exit){
            write_history(".hist");
            break;
        }
        
    }
}