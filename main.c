#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <stdbool.h>

typedef enum{MOSTFREQUENT, LEASTFREQUENT, SUM, AVERAGE, PRINTALL, NEWINPUT, ENDPROGRAM}Function_t;

void printMenu(){
    printf("**************************************************\n");
    printf("Pokracuj stisknutim klavesy:\n");
    printf("Stlac 1) pre informacie o najcastejsom abecednom znaku\n");
    printf("Stlac 2) pre informacie o najmenej castych abecednych znakoch\n");
    printf("Stlac 3) pre vypis, kolko je celkovo abecednych znakov\n");
    printf("Stlac 4) pre informaciu o priemernej pocetnosti abecednych znakov\n");
    printf("Stlac 5) pre vypis pocetnosti kazdeho abecedneho znaku\n");
    printf("Stlac SPACEBAR) pre zadanie novych dat z konzole\n");
    printf("Stlac ENTER) pre ukoncenie programu\n");
    printf("**************************************************\n");
}

/*!
 * \brief Načíta vstup z input streamu a rozparsuje ho do pripraveného poľa
 * \param array[] Pole kam má byť vstup po spracovaní uložený
 * \param length dĺžka poľa, konštantná hodnota (256)
 * \param inputfile input stream (závisí na parametroch príkazovej riadky, s ktorými bol program spustený)
 */
void parseInput(int array[], int length, FILE* inputfile){

    for(int i = 0; i < length; i++){
        array[i] = 0;
    }

    char read;

    if(inputfile == stdin){
        printf("Zadaj Sekvenciu znakov: \n");
    }

    do{
        read = fgetc(inputfile);
        if(isalpha(read)){
            array[(int)read] += 1;
        }
    }while(read != EOF && read != '#');
}

/*!
 * \brief Načíta vstup z input streamu a rozparsuje ho do pripraveného poľa
 * \param array[] Pole kam má byť vstup po spracovaní uložený
 * \param length dĺžka poľa, konštantná hodnota (256)
 */
void printArray(int array[], int length){
    for(int i = 0; i < length; i++){
        if(isalpha(i)){
            printf("Znak '%c' ... Pocet vyskytov = %d\n", (char)i, array[i]);
        }
    }
}

/*!
 * \brief Vypočíta priemerný počet znakov z textu
 * \param array[] Pole kam má byť počet po spracovaní uložený
 * \param length dĺžka poľa, konštantná hodnota (256)
 * \return float average - priemerný počet výskytov abecedného znaku
 */
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
/*!
 * \brief Vyhľadá znak s najvačším počtom výskytov
 * \param array[] Pole kam má byť počet po spracovaní uložený
 * \param length dĺžka poľa, konštantná hodnota (256)
 */
void mostFrequent(int array[], int length){
    int maxnum = INT_MIN;

    for(int i = 0; i < length; i++){
        if(isalpha(i)){
            if(array[i] > maxnum){
                maxnum = array[i];
            }
        }
    }
    printf("Najvyssi pocet vyskytov nejakeho znaku: %d\n", maxnum);
    printf("Tento pocet vyskytov maju znaky:\n");

    for(int j = 0; j < length; j++){
        if(isalpha(j)){
            if(array[j] == maxnum){
                printf("%c ", (char)j);
            }
        }
    }
}
/*!
 * \brief Vyhľadá znak s najmenším počtom výskytov
 * \param array[] Pole kam má byť počet po spracovaní uložený
 * \param length dĺžka poľa, konštantná hodnota (256)
 */
void leastFrequent(int array[], int length){
    int minnum = INT_MAX;

    for(int i = 0; i < length; i++){
        if(isalpha(i)){
            if(array[i] < minnum){
                minnum = array[i];
            }
        }
    }
    printf("Najnizsi pocet vyskytov nejakeho znaku: %d\n", minnum);
    printf("Tento pocet vyskytov maju znaky:\n");

    for(int j = 0; j < length; j++){
        if(isalpha(j)){
            if(array[j] == minnum){
                printf("%c ", (char)j);
            }
        }
    }
}
/*!
 * \brief Spočíta celkový počet znakov použitých v textovom súbore
 * \param array[] Pole kam má byť počet po spracovaní uložený
 * \param length dĺžka poľa, konštantná hodnota (256)
 * \return sum - celkový počet znakov vyskytujúcich sa v textovom súbore
 */
int charTotal(int array[], int length){
    int sum = 0;
    for(int i = 0; i < length; i++){
        if(isalpha(i)){
            sum += array[i];
        }
    }
    return sum;
}

/*!
 * \brief Vypíše menu a realizuje voľbu funkcie pomocou uživateľského vstupu z terminálu
 * \return Vracia zvolenú funkciu (realizované uživateľom definovaným výčtovým typom Function_t, viď. vyššie)
 */

Function_t functionChoice(){
    printMenu();
    char znak;

    while(1){
        printf("Vasa volba: ");
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
        else if(znak == 32){
            return NEWINPUT;
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
    int sum;
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
            mostFrequent(array, length);
            printf("\n");
            break;

            case LEASTFREQUENT:
            leastFrequent(array, length);
            printf("\n");
            break;

            case SUM:
            printf("Celkovy pocet znakov je: %d\n", sum);
            break;

            case AVERAGE:
            average = averageCount(array, length);
            printf("Priemerny pocet vyskytov znaku je %.3f\n", average);
            break;

            case NEWINPUT:
            if(input != stdin){
                input = stdin;
            }
            parseInput(array, length, input);
            sum = charTotal(array, length);
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

