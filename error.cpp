#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "translator.cpp"

using namespace std;

int trChar = 0, errWord = 0;        /* Counter for translated characters and words. */
int errChar = 0, errMorse = 0;      /* Counter for error characters. */
string line1 = "";                  /* Get unrecognized characters. */
int line_num[200];
int w_length[200];                  /* Get the length of unrecognized morse codes. */
int numl = 0;

void err_textF(const char *inp, int n) {

    fstream myFile, myFile1;
    string line, s;
    int line_counter = 0, err_bool = 0;

    myFile.open(inp, ios::in);
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            line_counter ++;        //Count the number of lines in the input file.
            line += '\n';       //Add '\n' to the end of every lines
            for (int i = 0; i < line.length(); i++) {
                line[i] = tolower(line[i]);        //Modify the input data
                s += line[i];       //Read the input data

                if (line[i] != ' ' && line[i] != '\n') {        //Start detecting error if line[i] is not a seperator
                    for (int j = 0; j < size_of_array; j++) {
                        if (s == letter[j]) {       //Check if "s" does exist in the "letter" array
                            j = size_of_array;      //The case of
                            trChar++;               //successful translation.
                        }
                        else if (j == (size_of_array - 1)) {        //The case of "s" not being in the "letter" array
                            cout<<"Error T1: Unrecognize character "<<line[i]<<" on line "<<line_counter<<".\n";
                            line1 += line[i];
                            line_num[numl++] = line_counter;
                            errChar++;      
                            err_bool = 1;       //The word has error(s)
                        }
                    }
                }
                else if ((line[i] == ' ' || line[i] == '\n') && err_bool == 1) {        //Check if the word has error or not
                    errWord++;          //If err_bool = 1
                    err_bool = 0;       //then the word has error(s)
                };
                s = "";
            }
        }
        myFile.close();
    }
}

int line_counter;
int extBlank[2000]; /* Counter for the number of extra blanks */
void err_morse(const char *inp) {
    fstream myFile;
    string line, s_temp = "";
    int space_counter = 0, err_bool = 0, space_bool = 0;
    int j = 0, numlf = 0;

    myFile.open(inp, ios::in);
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            line_counter++;
            line += '\n';
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '.' || line[i] == '-') {         //Append line[i] to s_temp if it's not a seperator
                    s_temp += line[i];          //Read each Morse characters.
                    space_counter = 0;          
                }

                else if (line[i] == '/' || line[i] == ' ' || line[i] == '\n') {     //Start checking error
                    if (line[i] == ' ') {
                        space_counter++;

                        if (space_counter == 2) {       //The case of having 2 ' ' between each characters
                            space_bool ++;
                            extBlank[line_counter]++;
                            errMorse++;
                            space_counter = 0; 
                            err_bool = 1;
                        };
                    }

                    else if (line[i] == '/') {
                        space_counter = 0;
                    };

                    for (int j = 0; j < size_of_array; j++) {
                        if (s_temp.length() > 7) {      //The case of word's length being larger than 7
                            cout<<"Error M2: Invalid Morse code "<<s_temp<<" on line "<<line_counter<<".\n";
                            line1 += s_temp;
                            line_num[numl++] = line_counter;
                            w_length[numlf++] = s_temp.length();
                            errMorse++;
                            s_temp = "";
                            j = size_of_array;
                            err_bool = 1;
                        }

                        else if (s_temp != morse[j] && j == (size_of_array - 1) ) {     //The case of s_temp not being in the "morse" array 
                                cout<< "Error M3: Invalid Morse code "<<s_temp<<" on line "<<line_counter<<".\n";
                                line1 += s_temp;
                                line_num[numl++] = line_counter;
                                w_length[numlf++] = s_temp.length();
                                errMorse++;
                                s_temp = "";
                                err_bool = 1;
                        }
                    
                        else if (s_temp == morse[j] || s_temp == "") {
                            s_temp = "";            //Successful translation.
                            j = size_of_array;
                        };
                    };

                    if ((line[i] == '/' || line[i] == '\n') && err_bool == 1) {
                        errWord++;          //Check for error words.
                        err_bool = 0;
                    };
                };
            };
            s_temp = "";
        };

        /* Print out the Error M1 to the screen. */
        for (int i = 0; i < line_counter + 1; i++){
                if (extBlank[i] > 0)
                    cout<<"Error M1: "<< extBlank[i] <<" extra blankspaces on line "<<i<<".\n"; 
            }
        myFile.close();
    };
};
