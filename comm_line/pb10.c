#include <stdio.h> 
#include <string.h>

int main(int argc, char* argv[]){
    FILE *inp, *outp;
    char name[50], ch, stu_id[9];
    int j, length;
    float score;

    // inp = fopen("C:\\Users\\Tran Nhat Nam\\Desktop\\student.csv", "r");
    // outp = fopen("C:\\Users\\Tran Nhat Nam\\code\\C-C++\\week05\\homework\\ee3491.csv", "w");

    // char dir[] = "";
    // strcat(dir, argv[1]);

    inp = fopen(&argv[1],"r");
    outp = fopen(&argv[2],"w");
    
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
    return 0;
}