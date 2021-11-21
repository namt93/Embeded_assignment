#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

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

// in ra ngay va gio hoan thanh
void current_time(FILE *fp){
    int hours, minutes, seconds, day, month, year;
    char cmonth[6];

    time_t now;

    time(&now);

    struct tm *local = localtime(&now);

    hours = local->tm_hour;
    minutes = local->tm_min;
    seconds = local->tm_sec;

    day = local->tm_mday;
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
    clock_t t;
    t = clock();
    int i, t_mis = 0, m_mis = 0, c_mis = 0, run_if = 0;

    if (argc == 1){
        printf("Error XX: Unrecognized command. Type “morse –h” for help");
        return 1;
    }
    else if (!(strcmp(argv[argc - 1],"-h"))){
        h_command();
    }
    else if(!(strcmp(argv[argc - 1],"-t"))){
        t_command(argv);
    }
    else if(!(strcmp(argv[argc - 1],"-m"))){
        m_mis = 1;
    }
    else if(!(strcmp(argv[argc - 1],"-c"))){
        c_command(argv);
    }
    else{
        printf("Error XX: Unrecognized command. Type “morse –h” for help");
        return 1;
    }


    // switch (argv[argc - 1])
    // {
    // case "-h":
    //     h_command();
    //     break;
    // case "-t":
    //     t_command(argv);
    //     break;
    // case "-m":
    //     m_mis = 1;
    //     break;
    // case "-c":
    //     c_command();
    //     break;
    // default:
    //     printf("Something is wrong !!");
    //     break;
    // }



    // thuc hien lenh -m
    
    t = clock() - t;
    double time_taken = ((double)t) /CLOCKS_PER_SEC;

    printf("the program took %f seconds to execute \n", time_taken);

    return 0;
}