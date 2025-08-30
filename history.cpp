#include "header.h"
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
 
void printHistory(long long number){
    vector<string>v;
    FILE *history=fopen("history.txt","r");
    if(!history){
        perror("Error in opening history");
    }
    char command[1024];
    while(fgets(command,1024,history)){
        command[strcspn(command,"\n")]=0;
        v.push_back(command);
    };
    fclose(history);
    number=number<v.size()?number:v.size();
    for(int i=0;i<number;i++){
        cout<<v[i]<<endl;
    }
}

void writeHistory(string s){ 
    if(s[0]==' ')return;
    vector<string>v;
    string path=direc.home+"/"+"history.txt";
    FILE *history=fopen(path.c_str(),"r");
    if(!history){
        perror("Error in opening history");
        return;
    }
    char command[1024];
    while(fgets(command,1024,history)){
        command[strcspn(command,"\n")]=0;
        v.push_back(command);
    };
    if(v.size()==20){
        v.pop_back();
    }
    v.insert(v.begin(),s);
    fclose(history);

    history=fopen(path.c_str(),"w");
    if(!history){
        perror("Error in opening history");
        return;
    }
    for(auto i:v){
        //cout<<i;
        fprintf(history,"%s\n",i.c_str());
    }
    fclose(history);

}

void historymain(vector<string>v){
    if(v.size()==2){
        long long number=strtoll(v[1].c_str(),NULL,10);
        printHistory(number);
        //cout<<number;
    }else{
        printHistory(10);
    }
    
}