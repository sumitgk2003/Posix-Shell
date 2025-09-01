#ifndef HEADER_H
#define HEADER_H

#include<string>
#include<vector>
#include<iostream>
using namespace std;

void lsmain(vector<string>v);
string pwd();
void search(vector<string>v);
void echo(vector<string>v);
void cd(vector<string>v);
class Directory{
    public:
    string current=pwd();
    string prev=pwd();
    string home=pwd();
};
extern Directory direc;
void systemCommand(vector<string>v);
void historymain(vector<string>v);
void writeHistory(string s);
void ioRedirection(vector<string>v);
#endif