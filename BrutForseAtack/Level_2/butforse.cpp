#include "forse.h"
#include <iostream>
#include <vector>

std::vector<std::string> GetGuess(int val, std::string startOfReport, const int count, int* countPass)
{
    
    int p = count;
    int numb = 0;
    std::vector<std::string> strName;
    // TODO: letter frequency analysis
    const char chars[CHAR_COUNT + 1] = "abcdefghijklmnopqrstuvwxyz0123456789"; //"abcdefghijklmnopqrstuvwxyz0123456789"   36/4=9
    int i, j;
    int guessc[MAX_SIZE] = {0};     // counter
    char guess[MAX_SIZE + 1];         // chars crresponding to counter

    for (i = 1; i < MAX_SIZE; guessc[i++] = -1);   // initializing counter with -1
    for (i = 1; i <= MAX_SIZE; guess[i++] = '\0');      // initializing guess with NULL
    
    
    // change the initialisation of guess if you want the algorithm to start with a certain word/length.
    // if you want to constrain the algorithm to a certain length of password you could add a new var k, such that k < CHAR_COUNT^max_password_length
    // you could use the following code:
    // add #include <math.h> to the header file
    // and the following to the cpp file:
    //  int k = 0;
    //  while(k++ < pow(CHAR_COUNT,MAX_PASSWORD_LENGTH))
    // you would have to define MAX_PASSWORD_LENGTH as the max length passwords you want to try


    while (1)    // change here if you want to configure the max number of guesses
    {
        // increment guessc[i+1] if guessc[i] is bigger than the number of chars in the array
        i = 0;
        while (guessc[i] == CHAR_COUNT)    // check all counter elements wether theire value is bigger than the number of chars stored in CHAR_COUNT or not
        {
            guessc[i] = 0; // reset the element that is bigger than CHAR_COUNT to 0
            
            
            
            guessc[++i] += 1;             // increment the next element (index i+1)
        }

        for (j = 0; j <= i; ++j)   // change all chars that differ from the last guess (the number of chars changed is equal to the number of counter elements tested(=i))
        {
            // you could remove this if statement since it is infeasibly to bruteforce a 30 char long password in a reasonable amount of time
            // if you want the algorithm to stop after a certain length you should change the while loop at line 23 not MAX_SIZE
            // MAX_SIZE is only used to avoid accessing an index bigger than the array size!
            if (j < MAX_SIZE) // check if an element guess[j] exists
                guess[j] = chars[guessc[j]];
        }
        // output the guess to std::out

   /*
       char pass[4] = {'k','5','f','q'}; //k5fq
             if (guess[i] == pass[i]) {
                 if (guess[i + 1] == pass[i + 1]) {
                     if (guess[i + 2] == pass[i + 2]) {
                         if (guess[i + 3] == pass[i + 3]) {
                             std::cout << "perfect" << std::endl;
                             std::string strPass = std::string(guess);
                             strName.push_back(strPass);
                             printf("%s\n", guess);
                             //return strName;
 //                            throw 12;
                         }
                     }
                 }
             }
     */    
           //std::cout << numb << "  ";
          // printf("%s\n", guess);  // printf is used since it is way faster than std::cout
           numb++;
           std::string strPass = std::string(guess);
           strName.push_back(strPass);
           if (p != 0) {
               for (int y = 0; y < startOfReport.size(); y++) {
                   guess[y] = startOfReport[y];
                   }
               for (int y = 0; y < MAX_SIZE; y++) {
                   guessc[y] = *(countPass + y);
               }
               p = 0;
           }
           else {
             //  std::cout << "first iteretion" << std::endl;
           } 
           ++guessc[0];    // increment guessc at index 0 for the next run
           if (numb == val) {
               for (int y = 0; y < MAX_SIZE; y++) {
                   *(countPass+y) = guessc[y];
               }
               return strName;
           }
    }
        return strName;
}



