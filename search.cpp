#include "header.h"
#include<iostream>
#include<dirent.h>
#include<sys/stat.h>
using namespace std;
void search(vector<string>v){
    vector<string>dir;
    //string path=pwd();
    dir.push_back(pwd());
    while(dir.size()!=0){
        string path=dir.back();
        dir.pop_back();
        DIR* directory=opendir(path.c_str());
        if(directory==NULL){
            cout<<"Error"<<endl;
            continue;
        }
        struct dirent* entry = readdir(directory);
        while(entry!=NULL){
            if(entry->d_name[0]!='.'){
                    if(v[1]==entry->d_name){
                    cout<<"True"<<endl;
                    return;
                };
                struct stat file;
                string subpath=path+"/"+entry->d_name;
                if(stat(subpath.c_str(), &file) < 0){
                    perror("stat");
                    cout << "new file path is incorrect" << endl;
                    continue;
                }
                if(S_ISDIR(file.st_mode)) {
                    dir.push_back(subpath);
                }
            }
            entry=readdir(directory);
        }
        closedir(directory);
        // for(auto i:dir){
        //     cout<<i<<endl;
        // }
    }
    
    cout<<"False"<<endl;
    
    // if(path!=pwd()&&path[0]!='/'){
    //     path=pwd()+"/"+path;
    // }
    
}