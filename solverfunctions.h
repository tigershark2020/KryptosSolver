#ifndef SOLVERFUNCTIONS_H
#define SOLVERFUNCTIONS_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>

class SolverFunctions
{
public:
    SolverFunctions();
    std::string FindReplaceInString(std::string subject, const std::string& search,const std::string& replace);
    std::vector<std::string> Load_Dictionary_List();
    std::string RemainingAlphabetString(std::string &keyword_one);
    std::vector<std::string> Generate_Cipher_Alphabets_From_Keywords(std::string &cipher_base_alphabet, std::string &keyword_one, std::string &keyword_two,int keyword_start_positio);
    std::string ShiftAlphaSet(std::string &cipher_base_alphabet, std::string &start_char);
    std::string Vigenere_With_Alpha_Keywords(std::string &encrypted_puzzle_part,std::string &keyword_one, std::string &keyword_two);
    std::string PrintMatrix(std::vector<std::vector<std::string> > grid_matrix);
    std::vector<std::vector<std::string> > String_To_Matrix(std::string &string_as_matrix, int width);
    std::string Matrix_To_String(std::vector<std::vector<std::string> > matrix);
    std::vector<std::vector<std::string> > RotateMatrix(std::vector<std::vector<std::string> > matrix);
    std::string Grid_Rotation_Solver(std::string &encrypted_puzzle_part);
    void SolvePuzzle();
};

#endif // SOLVERFUNCTIONS_H
