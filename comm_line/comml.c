#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<time.h>

void h_command(){
    FILE *fptr;
    char c;

    fptr = fopen("readme.txt", "r");
    c = fgetc(fptr);
    
    // in noi dung tu readme.txt
    while (c != EOF)
        {
            printf ("%c", c); 
            c = fgetc(fptr);
        }
  
        fclose(fptr);   

}

void t_command(char **s){
    FILE *inp, *outp;
    char name[50], ch, stu_id[9];
    int j, length;
    float score;

    inp = fopen(s[1], "r");
    outp = fopen(s[2], "w");

    while (fscanf(inp, "%c", &name[0]) != EOF){
        for(j = 1; j < 20; j++){
            if(name[j - 1] == ','){
                break;
            }
            else{
                fscanf(inp, "%c", &name[j]);
            }
        }
        length = j;
        fscanf(inp, "%f", &score);
        
        for(j = 0; j < 9; j++){
            fscanf(inp, "%c", &stu_id[j]);
        }
        fscanf(inp, "%c", &ch);

        if (score > 8){
            for(j = 0; j < length; j++){
                fprintf(outp, "%c", name[j]);
            }
            fprintf(outp, " ");
            for(j = 1; j < 9; j++){
                fprintf(outp, "%c", stu_id[j]);
            }
            fprintf(outp,"\n");

        }
    }
    fclose(inp); fclose(outp);   
}

void current_time(FILE *fp){
    int hours, minutes, seconds, day, month, year;
    char cmonth[6];
    time_t now;

    time(&now);

    struct tm *local = localtime(&now);

    hours = local -> tm_hour;
    minutes = local -> tm_min;
    seconds = local -> tm_sec;

    day = local -> tm_mday;
    month = local -> tm_mon + 1;
    year = local -> tm_year + 1900;

    switch (month)
    {
    case 1:
        strcpy(cmonth,"Jan");
        break;
    case 2:
        strcpy(cmonth,"Feb");
        break;
    case 3:
        strcpy(cmonth,"Mar");
        break;
    case 4:
        strcpy(cmonth,"Apr");
        break;
    case 5:
        strcpy(cmonth,"May");
        break;
    case 6:
        strcpy(cmonth,"Jun");
        break;
    case 7:
        strcpy(cmonth,"Jul");
        break;
    case 8:
        strcpy(cmonth,"Aug");
        break;
    case 9:
        strcpy(cmonth,"Sep");
        break;
    case 10:
        strcpy(cmonth,"Oct");
        break;
    case 11:
        strcpy(cmonth,"Nov");
        break;
    case 12:
        strcpy(cmonth,"Dec");
        break;
    default:
        break;
    }
    fprintf(fp ,"Time complete is: %d-%s-%02d  %02d:%02d:%02d \n", year, cmonth, day, hours, minutes, seconds);
}
void c_command(char **s){   
    FILE *fp;
    fp = fopen ("data.log", "w");

    fprintf(fp, "Input file: %s\n", s[1]);
    fprintf(fp, "Output file: %s\n", s[2]);
    current_time(fp);
}

int main(int argc, char *argv[]){
    int i, t_mis = 0, m_mis = 0, c_mis = 0;

    if (argc == 1){
        printf("Error XX: Unrecognized command. Type “morse –h” for help");
        return 1;
    }
    
    // thuc hien lenh -h
    else if(!(strcmp(argv[1],"-h"))){
        h_command();
    }
    
    // thuc hien lenh -t
    else if(!(strcmp(argv[3],"-t"))){
        t_command(argv);
    }

    // thuc hien lenh -m
    else if(!(strcmp(argv[3],"-m"))){
        m_mis = 1;
    }

    // thuc hien lenh -c
    else if(!(strcmp(argv[3],"-c"))){
        c_command(argv);
    }

    // neu command line sai !!!
    else{
        h_command();
    }

    return 0;
}