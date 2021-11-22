#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
int main(){
    FILE *fptr;
    char c;
    string s = "";

    fptr = fopen("readme.txt", "r");
    c = fgetc(fptr);
    
    // in noi dung tu readme.txt
    while (c != EOF)
        {
            s += c; 
            c = fgetc(fptr);
        }
  
        fclose(fptr);  
    cout << s ;
}
