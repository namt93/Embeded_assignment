#include <fstream>
#include <string>
#include "translator.cpp"

using namespace std;

int trChar = 0, errWord = 0;     //Counter for translated characters and words.
int errChar = 0, errMorse = 0;   //Counter for error characters.

int err_textF(const char *inp) {
 
    fstream myFile;
    string line, s = "";
    int line_counter = 0, err_bool = 0;

    myFile.open(inp, ios::in);
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            line += '\n';
            line_counter ++;        //Count the number of lines in the input file.

            for (int i = 0; i < line.length(); i++) {
                line[i] = tolower(line[i]);        //Modify the input data
                s += line[i];       //Read the input data

                if (line[i] != ' ' && line[i] != '\n') {
                    for (int j = 0; j < size_of_array; j++) {
                        if (s == letter[j]) {       
                            j = size_of_array;      //The case of
                            trChar++;               //successful translation.
                        }
                        else if (j == (size_of_array - 1)) {
                            cout<<"Error AB: Unrecognize character "<<line[i]<<" on line "<<line_counter<<"\n";
                            errChar++;      
                            err_bool = 1;
                        };
                    };  
                }
                else if ((line[i] == ' ' || line[i] == '\n') && err_bool == 1) {
                    errWord++;          //Check the error
                    err_bool = 0;       //of each words.
                };

                s = "";
            };
        };

        myFile.close();
    };
};

int err_morse(const char *inp) {
    fstream myFile;
    string line, s_temp = "";
    int line_counter = 0, space_counter = 0, err_bool = 0;
    int j = 0;

    myFile.open(inp, ios::in);
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            line_counter++;
            
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '.' || line[i] == '-') {
                    s_temp += line[i];          //Read each Morse characters.
                    space_counter = 0;          
                }

                else if (line[i] == '/' || line[i] == ' ' || line[i] == '\n') {
                    if (line[i] == ' ') {
                        space_counter++;

                        if (space_counter == 2) {
                            cout<<"Error 01: Extra blankspace on line "<<line_counter<<"\n";
                            errMorse++;
                            space_counter = 0; 
                            err_bool = 1;
                        };
                    }

                    else if (line[i] == '/') {
                        space_counter = 0;
                    };

                    for (int j = 0; j < size_of_array; j++) {
                        if (s_temp.length() > 7) {
                            cout<<"Error 02: Invalid Morse code "<<s_temp<<" on line "<<line_counter<<"\n";
                            errMorse++;
                            s_temp = "";
                            j = size_of_array;
                            err_bool = 1;
                        }

                        else if (s_temp != morse[j] && j == (size_of_array - 1) ) {
                                cout<< "Error 03: Invalid Morse code "<<s_temp<<" on line "<<line_counter<<"\n";
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

        myFile.close();
    };
};
