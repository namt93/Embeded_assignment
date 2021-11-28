#include <fstream>
#include <string>
#include "test.cpp"

using namespace std;

void err_text(const char *inp) {
    fstream myFile;
    string line, s = "";
    int line_counter = 0;

    myFile.open(inp, ios::in);
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            line_counter ++;
            for (int i = 0; i < line.length(); i++) {
                line[i] = tolower(line[i]);
                s += line[i];

                if (line[i] != ' ' && line[i] != '\n') {
                    for (int j = 0; j < size_of_array; j++) {
                        if (s == letter[j]) {
                            j = size_of_array;
                        }
                        else if (j == (size_of_array - 1)) {
                            cout<<"Error AB: Unrecognize character "<<line[i]<<" on line "<<line_counter<<"\n";
                        };
                    };
                };
                s = "";
            };
        };

        myFile.close();
    };
};

void err_morse(const char *inp) {
    fstream myFile;
    string line, s_temp = "";
    int line_counter = 0, space_counter = 0, j = 0;

    myFile.open(inp, ios::in);
    if (myFile.is_open()) {
        while (getline(myFile, line)) {

            line_counter++;

            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '.' || line[i] == '-') {
                    s_temp += line[i];
                    space_counter = 0;
                }
                else if (line[i] == '/' || line[i] == ' ' || line[i] == '\n') {
                    if (line[i] == ' ') {
                        space_counter++;
                        if (space_counter == 2) {
                            cout<<"Error AB: Extra blankspace on line "<<line_counter<<"\n";
                            space_counter = 0; 
                        };
                    }
                    else if (line[i] == '/') {
                        space_counter = 0;
                    };

                    for (int j = 0; j < size_of_array; j++) {
                        if (s_temp.length() > 7) {
                            cout<<"Error AB: Invalid Morse code "<<s_temp<<" on line "<<line_counter<<"\n";
                            s_temp = "";
                            j = size_of_array;
                        }

                        else if (s_temp != morse[j] && j == (size_of_array - 1) ) {
                                cout<< "Error AB: Invalid Morse code "<<s_temp<<" on line "<<line_counter<<"\n";
                                s_temp = "";
                        }
                    
                        else if (s_temp == morse[j] || s_temp == "") {
                            s_temp = "";
                            j = size_of_array;
                        };
                    };
                };
            };
        };
        myFile.close();
    };
};