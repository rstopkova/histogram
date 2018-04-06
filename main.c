#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void printMenu(){
    printf("**************************************************\n");
    printf("Pokracuj stisknutim klavesy:\n");
    printf("Stlac 1) pre informacie o najcastejsom znaku\n");
    printf("Stlac 2) pre vypis, kolko je celkovo znakov\n");
    printf("Stlac ENTER) pre ukoncenie programu\n");
    printf("**************************************************\n");
}

bool get_string( char * line, int len, FILE* inputfile)
{
    if( fgets( line, len, inputfile ) == NULL ) {
        printf( "Konec souboru, koncime.\n" );
        return false;
    }

    return true;
#ifdef ECHO
    printf( "%s", line );
#endif
}

bool io_utils_get_string( char *c, int maxLen, FILE* inputfile)
{
    if( c == NULL ) {
        return false;
    }

    return get_string( c, maxLen , inputfile);
}


bool io_utils_get_char( char * c , FILE* inputfile)
{
    char line[255];

    if( get_string( line, 255, inputfile) == true ) {
        *c = line[0];
        return true;
    }

    return false;
}


int parseInput(int array[], FILE* inputfile){
    int sum = 0;
    char read;

    while (1){
        read = fgetc(inputfile);
        if(read == EOF || read == '#'){
            break;
        }
        else{
            array[(int)read] += 1;
            sum++;
        }
    }
    return sum;
}


void printArray(int array[]){
    for(int i = 0; i < 256; i++){
            printf("pozicia %d, pocet %d, znak %c \n", i,array[i], (char)i);
    }
}

int mostFrequent(int array[], int length){
    int maxnum = INT_MIN;
    int maxindex = 0;

    for(int i = 0; i < length; i++){
        if(array[i] > maxnum){
            maxnum = array[i];
            maxindex = i;
        }
    }
    if(maxnum == 0 && maxindex == 0){
        printf("Ziadne znaky neboli nacitane, prazdne pole\n");
    }
    return maxindex;
}


int main(int argc, char** argv)
{
    bool end = false;
    char loadedchar;
    int array[256] = {0};

    FILE *input = stdin;
    if(argc == 2){
        input = fopen(argv[1], "r");
    }
    if(input == NULL){
        printf( "Input soubor se nepodarilo otevrit\n" );
        return -1;
        }

    if(input == stdin){
        printf("\n");
        printf("Zadaj Sekvenciu znakov: \n");
    }
    int sum = parseInput(array, input);
    printMenu();

    fgetc(input);
    while(io_utils_get_char(&loadedchar, input)){
        switch(loadedchar){
            case '1':
            {
            int most = mostFrequent(array, 256);
            printf("Najcastejsi znak je znak \'%c\' na pozicii %d s poctom vyskytov %d\n", most, most, array[most]);
            break;
            }

            case '2':
            printf("Celkovy pocet znakov je: %d\n", sum);
            break;

            case 13:
            end = true;
            break;
        }
        if(end){
            fclose(input);
            return 0;
        }
        printMenu();
    }
    return 0;
}

