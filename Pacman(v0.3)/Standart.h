#pragma once

#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<cstdlib>
#include<ctime>


int** allocateMatrix(unsigned, unsigned);

void deleteMatrix(int** );

void Error(std::string message);


int Random(int number, int );