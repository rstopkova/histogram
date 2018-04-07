#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <stdbool.h>

typedef enum{MOSTFREQUENT, LEASTFREQUENT, SUM, AVERAGE, PRINTALL, ENDPROGRAM}Function_t;

void printMenu(){
    printf("**************************************************\n");
    printf("Pokracuj stisknutim klavesy:\n");
    printf("Stlac 1) pre informacie o najcastejsom abecednom znaku\n");
    printf("Stlac 2) pre informacie o najmenej castom abecednom znaku\n");
    printf("Stlac 3) pre vypis, kolko je celkovo abecednych znakov\n");
    printf("Stlac 4) pre informaciu o priemernej pocetnosti abecednych znakov\n");
    printf("Stlac 5) pre vypis pocetnosti kazdeho abecedneho znaku\n");
    printf("Stlac ENTER) pre ukoncenie programu\n");
    printf("**************************************************\n");
}

void parseInput(int array[], int length, FILE* inputfile){

    for(int i = 0; i < length; i++){
        array[i] = 0;
    }

    char read;

    if(inputfile == stdin){
        printf("Zadaj Sekvenciu znakov: \n");
    }

    while (1){
        read = fgetc(inputfile);
        if(read == EOF || read == '#'){
            break;
        }
        else{
            if(isalpha(read)){
                array[(int)read] += 1;
            }
        }
    }
}


void printArray(int array[], int length){
    for(int i = 0; i < length; i++){
        if(isalpha(i)){
            printf("Znak '%c' ... Pocet vyskytov = %d\n", (char)i, array[i]);
        }
    }
}


float averageCount(int array[], int length){
    float sum = 0;
    int countalpha = 0;

    for(int i = 0; i < length; i++){
        if(isalpha(i)){
            sum += array[i];
            countalpha++;
        }
    }
    return sum / countalpha;
}

int mostFrequent(int array[], int length){
    int maxnum = INT_MIN;
    int maxindex = 0;

    for(int i = 0; i < length; i++){
        if(isalpha(i)){
            if(array[i] > maxnum){
                maxnum = array[i];
                maxindex = i;
            }
        }
    }
    return maxindex;
}

int leastFrequent(int array[], int length){
    int minnum = INT_MAX;
    int minindex = 0;

    for(int i = 0; i < length; i++){
        if(isalpha(i)){
            if(array[i] < minnum){
                minnum = array[i];
                minindex = i;
            }
        }
    }
    return minindex;
}

int charTotal(int array[], int length){
    int sum = 0;
    for(int i = 0; i < length; i++){
        if(isalpha(i)){
            sum += array[i];
        }
    }
    return sum;
}

Function_t functionChoice(){
    printMenu();
    char znak;

    while(1){
        znak = getche();
        printf("\n");
        if (znak == '1'){
            return MOSTFREQUENT;
        }
        else if(znak == '2'){
            return LEASTFREQUENT;
        }
        else if(znak == '3'){
            return SUM;
        }
        else if(znak == '4'){
            return AVERAGE;
        }
        else if(znak == '5'){
            return PRINTALL;
        }
        else if(znak == 13){
            return ENDPROGRAM;
        }
        else{
            printf("Nevalidny vstup, zadaj 1, 2, 3, 4, 5, alebo Enter \n");
        }
    }
}


int main(int argc, char** argv)
{
    Function_t function;
    int array[256];
    const int length = 256;
    int sum, most, least;
    float average;

    FILE *input = stdin;
    if(argc == 2){
        input = fopen(argv[1], "r");
    }
    if(input == NULL){
        printf( "Input soubor se nepodarilo otevrit\n" );
        return -1;
        }

    parseInput(array, length, input);
    sum = charTotal(array, length);

    while(1){
        function = functionChoice();
        switch(function){
            case MOSTFREQUENT:
            most = mostFrequent(array, length);
            printf("Najcastejsi znak je znak \'%c\' s poctom vyskytov %d\n", most, array[most]);
            break;

            case LEASTFREQUENT:
            least = leastFrequent(array, length);
            printf("Najmenej casty znak je znak \'%c\' s poctom vyskytov %d\n", least, array[least]);
            break;

            case SUM:
            printf("Celkovy pocet znakov je: %d\n", sum);
            break;

            case AVERAGE:
            average = averageCount(array, length);
            printf("Priemerny pocet vyskytov znaku je %.3f\n", average);
            break;

            case PRINTALL:
            printArray(array, length);
            break;

            case ENDPROGRAM:
            break;

        }
        if(function == ENDPROGRAM){
            break;
        }
    }
    fclose(input);
    return 0;
}

