#include "header.h"
#include<iostream>
#include<string.h>
#include <unistd.h>
#include<limits.h>
using namespace std;

string pwd(){
    char cwd[1000];
    getcwd(cwd,1000);
    return cwd;
}