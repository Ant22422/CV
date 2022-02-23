#pragma once
#include <vector>
#include <iostream>
#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <stdio.h>

#define MAX_SIZE 4         // only used to avoid errors
// do not use MAX_SIZE to constrain the algorithm to a certain password length. use the while loop in bruteforce.cpp
#define CHAR_COUNT 36 //36       // size of the charset you want to use (number of possible chars for the password)

std::vector<std::string> GetGuess(int val, std::string startOfReport, const int count, int* countPass);

#endif // BRUTEFORCE_H
