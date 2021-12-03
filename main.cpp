#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fstream>

#include "error.cpp"

void text_morseFILE(const char* inp, const char* outp){
    fstream myFile;
    myFile.open(inp, ios::in);
    string line;
    string s = "";
    string s_res;

    if (myFile.is_open()) {
        while (getline(myFile , line))
            s += line + '\n';       //Add '\n' to every lines.

        s.resize(s.length() - 1);   //Delete the last '\n'.
        s_res = letter_to_morse(s);     //Start encryption.

        myFile.close();
    };

    myFile.open(outp, ios::out);
    if (myFile.is_open()) {
        myFile<< s_res;     //Print encrypted data to the output file.

        myFile.close();
    };
 };

void morse_textFILE(const char *inp, const char *outp){
    fstream myFile;
    myFile.open(inp, ios::in);
    string line;
    string s = "";
    string s_res;

    if (myFile.is_open()) {
        while (getline(myFile , line)) {
            s += line + '\n';       //Add '\n' for every lines.
        };

        s.resize(s.length() - 1);       //Delete the last '\n'.
        s_res = morse_to_letter(s);     //Start decryption.

        myFile.close();
    };

    myFile.open(outp, ios::out);
    if (myFile.is_open()) {
        myFile<< s_res;     //Print decrypted data to the output file.

        myFile.close();
    }
 }


/* Local variables store date and time values 
as a number */
int year, month, day, 
hours, minutes, seconds;

/* A local variable detect error 
in the command line */ 
int error = 0, errText = 0;

/* Local variables store the name of 
input and output file without extension */
char new_inp[50], new_outp[50];

clock_t t;
double time_taken;
/* Perform -h command */
void h_command() {
    FILE *fptr;
    char c;

    /* Open readme file for reading */
    fptr = fopen("readme.txt", "r");
    c = fgetc(fptr);
    
    /* Print the content from readme.txt file */
    while (c != EOF) {
            printf ("%c", c); 
            c = fgetc(fptr);
        };
  
        fclose(fptr);
};

/* Perform -t command */
void t_command(char **s){
    const char *inp, *outp;
    FILE *fp;
    char ans;
    int ansn = 1;
    fp = fopen(s[1], "r");
    t = clock();
 
    inp = s[1];
    outp = s[2];

    if (fopen(s[1],"r") == NULL) {
        printf("Error XX: %s could not be opened\n", s[1]);
        error = 1;
    }

    else {
        if (fopen(s[2], "r") != NULL) {
            printf("Warning: %s already exists.",
            " Do you wish to overwrite (y, n)? ", s[2]);
            ans = getchar();
            ansn = 0;
            if (ans == 'y') {
                ansn = 1;
            }

            else {
                error = 1;
            };
        }

        if (ansn == 1) {
            text_morseFILE(inp, outp);
            err_textF(inp);
        };
    };

    fclose(fp);

    t = clock() - t;
    time_taken = ((double) t)/CLOCKS_PER_SEC;
};

/* Perform -m command */
void m_command(char **s){
    const char *inp, *outp;
    // FILE *fp;
    char ans;
    int ansn = 1;
    // fp = fopen(s[1], "r");
    t = clock();
 
    inp = s[1];
    outp = s[2];

    if (fopen(s[1],"r") == NULL) {
        printf("Error XX: %s could not be opened\n", s[1]);
        error = 1;
    }

    else {
        if (fopen(s[2], "r") != NULL) {
            printf("Warning: %s already exists.",
            " Do you wish to overwrite (y, n)? ", s[2]);
            ans = getchar();
            ansn = 0;
            if (ans == 'y')
                ansn = 1;
            else 
                error = 1;
        }

        if (ansn == 1) {
            morse_textFILE(inp, outp);
            err_morse(inp);
        }
    }

    // fclose(fp);
    
    t = clock() - t;
    time_taken = ((double) t)/CLOCKS_PER_SEC;
}

// print out date and time
char cmonth[6];
void current_time(FILE *fp){
    /* time_t is arithmetic time type */
    time_t now;

    /* time() returns the current time of
    the system as a time_t value */
    time(&now);

    /* Localtime converts a time_t value to calendar time */
    struct tm *local = localtime(&now);

    hours = local->tm_hour;             /* Get hours (0 - 23)   */
    minutes = local->tm_min;            /* Get minutes (0 - 59) */
    seconds = local->tm_sec;            /* Get seconds (0 - 59) */

    day = local->tm_mday;               /* Get day (1 to 31)    */
    month = local -> tm_mon + 1;        /* Get month (0 to 11)  */
    year = local -> tm_year + 1900;     /* Get year since 1900  */

    /* Convert month 
    from number to word */ 
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

    /* Print out date and time */
    fprintf(fp ,"Time complete is: %d-%s-%02d  %02d:%02d:%02d \n",
    year, cmonth, day, hours, minutes, seconds);
}

/* Remove file extension of
input and output */
void rm_extension(char *s, char *s1){
    int i, j = 0;
    char extension[2] = ".";
    int siz = strlen(s);
    int siz1 = strlen(s1);
    
    /* Return new_inp as
    the input file name without file extension */
    for (int i = 0; i < siz; i++) {
        if (strstr(&s[i],extension) == &s[i])
            break;
        else
            new_inp[j++] = s[i];
        
    }
    new_inp[j] = '\0';
    j = 0;
    
    /* Return new_outp as the name of
    the output file without file extension */
    for (int i = 0; i < siz1; i++) {
        if(strstr(&s1[i],extension) == &s1[i])
            break;
        else
            new_outp[j++] = s1[i];
        
    }
}

/* Rename log file of -c flag */
void rename_log(char **s){
    
    char old_name[] = "data.log";
    
    /* Variables store values in the char type */
    char cyear[10], cmonth[10], cday[10], 
    chours[10], cminutes[10], cseconds[10];

    /* Convert int to char */
    itoa(year, cyear, 10);
    itoa(month, cmonth, 10);
    itoa(day, cday, 10);
    itoa(hours, chours, 10);
    itoa(minutes, cminutes, 10);
    itoa(seconds, cseconds, 10);

    /* Remove extension of 
    the input and output name */
    rm_extension(s[1], s[2]);

    /* Combine components of 
    the log file name */
    strcat(new_inp, "_");
    strcat(new_inp, new_outp);
    strcat(new_inp, "_");
    strcat(new_inp, cyear);
    strcat(new_inp, cmonth);
    strcat(new_inp, cday);
    strcat(new_inp, "_");
    strcat(new_inp, chours);
    strcat(new_inp, cminutes);
    strcat(new_inp, cseconds);
    strcat(new_inp, ".log");

    /* Change the log file name */
    rename(old_name, new_inp);
}

/* Perform -c command */
void c_command(char **s) { 
    /* fp is a pointer of the log file */
    /* finp is a pointer of the input file */
    FILE *fp, *finp;
    
    /* m_mis decides to perform m_command */
    /* pre_space detect a word */
    int m_mis = 1, pre_space = 1;
    
    /* Counter for character and word */
    int char_count = 0, word_count = 0;
    char c;

    finp = fopen(s[1], "r");
    c = fgetc(finp);
    
    /* Detect if input file is a morse file or not */
    while (c != EOF) {
        if (c != '.' 
        && c != '/' && c != '-' 
        && c != ' ' && c != '\n')
            m_mis = 0;

        c = fgetc(finp);
    }

    /* Perform m_command */
    if (m_mis == 1) {
        m_command(s);

        finp = fopen(s[1], "r");

        /* Count character and word */
        do {
            c = fgetc(finp);

            if (c == ' ' || c == '\n') 
                pre_space = 1;
            if ((c == '.' || c == '-') && pre_space == 1) {
                char_count++;
                pre_space = 0;
            }
            else if (c == '/' || c == '\n' || c == EOF) 
                word_count++;
        } 
        while (c != EOF);
    }
    
    /* Perform t_command */
    else {
        t_command(s);

        finp = fopen(s[1], "r");
        c = fgetc(finp);

        /* Count character and word */
        while (c != EOF) {
            if (c != ' ' && c != '\n')
                char_count++;
            
            for (int i = 0; i < size_of_array; i++) {
                string temp = "";
                temp += c;
                if (pre_space == 1 && temp == letter[i]) {
                    word_count++;
                    pre_space = 0;
                }

                if (c == ' ' || c == '\n') 
                    pre_space = 1;
                temp = "";
            }
            c = fgetc(finp);
        }
    }

    if (error == 1) 
        return;

    /* The initial log file of -c flag */
    fp = fopen ("data.log", "w");

    fprintf(fp, "Input file: %s\n", s[1]);  /* Get the input file name */
    fprintf(fp, "Output file: %s\n", s[2]); /* Get the output file name */
    
    /* Print date and time to data.log file */
    current_time(fp);  

    /* Print statistics */
    fprintf(fp, "Duration [seconds]: %f\n", time_taken);

    if (m_mis == 0) {
        fprintf(fp, "Word count in input file: %d\n", word_count);
        fprintf(fp, "Word converted: %d\n", word_count - errWord);
        fprintf(fp, "Word with errors: %d\n", errWord);
        
        fprintf(fp, "Total number of characters: %d\n", char_count);
        fprintf(fp, "Number of characters have been converted: %d\n", char_count - errChar);
        fprintf(fp, "Number of characters are NOT converted: %d\n", errChar);
    }

    else {
        fprintf(fp, "Word count in output file: %d\n", word_count);
        fprintf(fp, "Word converted: %d\n", word_count - errWord);
        fprintf(fp, "Word with errors: %d\n", errWord);

        fprintf(fp, "Total number of characters: %d\n", char_count);
        fprintf(fp, "Number of characters have been converted: %d\n", char_count - errMorse);
        fprintf(fp, "Number of characters are NOT converted: %d\n", errMorse);
    }

    fclose(fp);
    fclose(finp);
    
    /* Rename data.log file */
    rename_log(s);
}

/* Perform the command line
or detect errors in the command line */
void option_error(int n, char **s){
    int i = 0, t_exist = 0, same_com = 0;

    /* Check "-t" and "-m" are 
    in the same command or not */
    for (i = 0; i < n; i++){
            if(!strcmp(s[i], "-t")){
                t_exist = 1;
            }
        }
        for (i = 0; i < n; i++){
            if(!strcmp(s[i], "-m") && t_exist == 1){
                same_com = 1;
                break;
            }
        }
    
    /* Error: Unrecognized command. */
    if (n == 1){
        printf("Error 02: Unrecognized command.",
        " Type “morse –h” for help \n");
        return;
    }

    /* perform -h flag */
    else if (n == 2 && !(strcmp(s[n - 1],"-h")))
        h_command();
    
    else if(n > 2 && !(strcmp(s[n - 1], "-h")))
        printf("Type “./main –h” for help");
    

    else if (n == 3 && (strcmp(s[n - 1], "-c")
    && strcmp(s[n - 1], "-m")
    && strcmp(s[n - 1], "-t")))
        c_command(s);
    

    /* Error: missing arguments */
    else if(n < 4 && (!strcmp(s[n - 1], "-t"))){
        printf("Error 05: Missing arguments.",
        " Type “./main –h” for help \n");
        printf("Correct syntax: “./main <inputfile> <outpufile> -t”");
        
    }
    else if (n < 4 && (!strcmp(s[n - 1], "-m"))){
        printf("Error 05: Missing arguments.",
        " Type “./main –h” for help \n");
        printf("Correct syntax: “./main <inputfile> <outpufile> -m”");
    }
    else if (n < 4 && (!strcmp(s[n - 1], "-c"))){
        printf("Error 05: Missing arguments.",
        " Type “./main –h” for help \n");
        printf("Correct syntax: “./main <inputfile> <outpufile> -c”");
    }


    /* Error 03: more than 4 arguments */
    else if(n > 4){
        printf("Error 03: Too many arguments.",
        " Type “./main –h” for help"); 
        return;
    }

    /* Error 04: "-t" and "-m" are in the same command */
    else if(same_com == 1)
        printf("Error 04: “-t”, “-m” in the same command.",
        " Type “./main –h” for help \n");

    /* perform -t flag */
    else if(!(strcmp(s[3],"-t")))
        t_command(s);
    

    /* perform -m flag */
    else if(!(strcmp(s[3],"-m")))
        m_command(s);
    

    /* perform -c flag */
    else if(!(strcmp(s[3],"-c")))
        c_command(s);
    
    
    /* Error 01: Unknown command */ 
    else if(n == 4 
    && ((strcmp(s[3],"-t"))
    ||(strcmp(s[3],"-m"))
    ||(strcmp(s[3],"-c")))){
        printf("Error 01: Unknown command.",
        " Type “./main –h” for help");
        return;
    }

    else{
        printf("Type “./main –h” for help\n");
        return;
    }
}

int main(int argc, char *argv[]){
    /* Peform the command line or
    detect errors in the command line */
    option_error(argc, argv);

    return 0;

}