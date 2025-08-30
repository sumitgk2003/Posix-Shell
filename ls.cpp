#include "header.h"
#include<vector>
#include<string>
#include<iostream>
#include<dirent.h>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>
#include<ctime>
using namespace std;


void details(struct stat stat){
    if (S_ISREG(stat.st_mode)) cout << "-";
    else if (S_ISDIR(stat.st_mode)) cout << "d";
    else if (S_ISLNK(stat.st_mode)) cout << "l";
    if(stat.st_mode & S_IRUSR)cout<<"r";
    else cout<<"-";
    if(stat.st_mode & S_IWUSR)cout<<"w";
    else cout<<"-";
    if(stat.st_mode & S_IXUSR)cout<<"x";
    else cout<<"-";
    if(stat.st_mode & S_IRGRP)cout<<"r";
    else cout<<"-";
    if(stat.st_mode & S_IWGRP)cout<<"w";
    else cout<<"-";
    if(stat.st_mode & S_IXGRP)cout<<"x";
    else cout<<"-";
    if(stat.st_mode & S_IROTH)cout<<"r";
    else cout<<"-";
    if(stat.st_mode & S_IWOTH)cout<<"w";
    else cout<<"-";
    if(stat.st_mode & S_IXOTH)cout<<"x";
    else cout<<"-";
    cout<<" "<<stat.st_nlink;
    struct passwd *pw=getpwuid(stat.st_uid);
    struct group  *gr=getgrgid(stat.st_gid);
    cout<<" "<<pw->pw_name;
    cout<<" "<<gr->gr_name;
    cout<<" "<<stat.st_size;
    char time[80];
    struct tm* t = localtime(&stat.st_mtime);
    strftime(time,sizeof(time),"%b %d %H:%M",t);
    cout<<" "<<time;
}

void lsa(string path){
    struct stat file;
    if(stat(path.c_str(), &file) < 0){
        perror("stat");
        cout << "new file path is incorrect" << endl;
        return;
    }
    if(S_ISREG(file.st_mode)) {
        cout<<path<<endl;
        return;
    }
    if(path!=pwd()&&path[0]!='/'){
        path=pwd()+"/"+path;
    }
    DIR* directory=opendir(path.c_str());
    if(directory==NULL){
        cout<<"Error"<<endl;
        return;
    }
    struct dirent* entry = readdir(directory);
    while(entry!=NULL){
        cout<<entry->d_name<<endl;
        entry=readdir(directory);
    }
    closedir(directory);
}

void lsl(string path){
    struct stat file;
    if(stat(path.c_str(), &file) < 0){
        perror("stat");
        cout << "new file path is incorrect" << endl;
        return;
    }
    if(S_ISREG(file.st_mode)) {
        details(file);
        cout<<" "<<path;
        cout<<endl;
        return;
    }
    if(path!=pwd()&&path[0]!='/'){
        path=pwd()+"/"+path;
    }
    DIR* directory=opendir(path.c_str());
    if(directory==NULL){
        cout<<"Error"<<endl;
        return;
    }
    struct dirent* entry = readdir(directory);
    while(entry!=NULL){
        if(entry->d_name[0]!='.'){
            struct stat file;
            string filepath;
            filepath=path+"/"+entry->d_name;
            if(stat(filepath.c_str(),&file)<0){
                perror("stat");
                cout<<"new file path is incorrect"<<endl;
            };
            details(file);
            cout<<" "<<entry->d_name;
            cout<<endl;
        }
        entry=readdir(directory);
    }
    closedir(directory);
}
void lsal(string path){
    struct stat file;
    if(stat(path.c_str(), &file) < 0){
        perror("stat");
        cout << "new file path is incorrect" << endl;
        return;
    }
    if(S_ISREG(file.st_mode)) {
        details(file);
        cout<<" "<<path;
        cout<<endl;
        return;
    }
    if(path!=pwd()&&path[0]!='/'){
        path=pwd()+"/"+path;
    }
    DIR* directory=opendir(path.c_str());
    if(directory==NULL){
        cout<<"Error"<<endl;
        return;
    }
    struct dirent* entry = readdir(directory);
    while(entry!=NULL){
            struct stat file;
            string filepath;
            filepath=path+"/"+entry->d_name;
            if(stat(filepath.c_str(),&file)<0){
                perror("stat");
                cout<<"new file path is incorrect"<<endl;
            };
            details(file);
            cout<<" "<<entry->d_name;
            cout<<endl;
        entry=readdir(directory);
    }
    closedir(directory);
}

void ls(string path){
    struct stat file;
    if(stat(path.c_str(), &file) < 0){
        perror("stat");
        cout << "new file path is incorrect" << endl;
        return;
    }
    if(S_ISREG(file.st_mode)) {
        cout<<path<<endl;
        return;
    }
    if(path!=pwd()&&path[0]!='/'){
        path=pwd()+"/"+path;
    }
    //cout<<"Path is "<<path<<endl;
    DIR* directory=opendir(path.c_str());
    if(directory==NULL){
        cout<<"Error";
        return;
    }
    struct dirent* entry = readdir(directory);
    while(entry!=NULL){
        if(entry->d_name[0]!='.'){
            cout<<entry->d_name<<endl;
        }
        entry=readdir(directory);
    }
    closedir(directory);
}

void lsmain(vector<string>v){
    bool l=false;
    bool a=false;
    vector<string>files;
    for(int i=1;i<v.size();i++){
        if(v[i]=="-l")l=true;
        else if(v[i]=="-a")a=true;
        else if(v[i]=="-al"||v[i]=="-la"){
            a=true;
            l=true;
        }else if(v[i]=="~"){
            files.push_back("/home/sumit/Desktop/AOS-2");
        }else{
            files.push_back(v[i]);
        }
    }
    if(files.size()==0){
        files.push_back(pwd());
    }
    //cout<<files.size()<<endl;
    for(auto i:files){
        if(l==true && a==true){
            //cout<<"lsal"<<endl;
            lsal(i);
        }else if(l==true){
            //cout<<"lsl"<<endl;
            lsl(i);
        }else if(a==true){
            //cout<<"lsa"<<endl;
            lsa(i);  
        }else{
            //cout<<"ls"<<endl;
            ls(i);
        }   
    }
       
}