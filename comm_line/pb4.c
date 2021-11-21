#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int frequency(char c){
    return (c == ' '||c == '\t');
}

void replace(char* s, char* word){
    char neww[100];
    int i = 0, j = 0;
    int sizw = strlen(word);
    for(i = 0; i < sizw; i++){
        neww[i]  = '*';
    }
    neww[sizw] = '\0';
    int len = strlen(s);
    char* res = (char *) malloc(len + 1);
    for(i = 0; s[i] != '\0'; ){
        if (strstr(&s[i], word) == &s[i] && i == 0){
            strcpy(&res[j], neww);
            i += sizw;
            j += sizw; 
        }
        else if (strstr(&s[i], word) == &s[i] && s[i - 1] == ' '){
            strcpy(&res[j], neww);
            i += sizw;
            j += sizw;           
        }
        else{
            res[j++] = s[i++];
        }
    }
    // puts(neww);
    res[j] = '\0';
    puts(res);
}

int main(){
    char st_input[1000], re_st[100];
    int siz_w, siz_pa;
    printf("Enter a string: \n");
    fgets(st_input, 999, stdin);
    printf("Enter the word you want to replace: \n");
    fgets(re_st, 99, stdin);
    siz_w = strlen(re_st);
    siz_pa = strlen(st_input);
    if(siz_w > 0){
        re_st[siz_w - 1]= '\0';
    }
    if(siz_pa > 0){
        st_input[siz_pa - 1]= '\0';
    }
    replace(st_input, re_st);

    return 0;
}