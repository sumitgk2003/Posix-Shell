#include<string.h>
#include<iostream>
#include<vector>

using namespace std;

void echo(vector<string>v){
    for(int i=1;i<v.size();i++){
        cout<<v[i]<<" ";
    }cout<<endl;
}