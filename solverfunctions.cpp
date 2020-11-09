#include "solverfunctions.h"

SolverFunctions::SolverFunctions()
{

}

std::string SolverFunctions::FindReplaceInString(std::string subject, const std::string& search,const std::string& replace)
{
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}

std::vector<std::string> SolverFunctions::Load_Dictionary_List()
{
        std::ifstream dictionaryFile;
        std::string line;
        std::vector<std::string> dictionary_vector;

        dictionaryFile.open("/usr/share/dict/words");

        while(getline(dictionaryFile, line))
        {
            dictionary_vector.push_back(line);
        }

        dictionaryFile.close();

        return dictionary_vector;
}

std::string SolverFunctions::RemainingAlphabetString(std::string &keyword_one)
{
    std::string standard_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string remaining_characters;

    for(int i = 0; i < standard_alphabet.length(); i++)
    {
        bool in_alpha_set = false;
           for(int j = 0; j < keyword_one.length(); j++)
           {
               if(standard_alphabet.substr(i,1) == keyword_one.substr(j,1))
               {
                   in_alpha_set = true;
               }
           }

           if(in_alpha_set == false)
           {
               remaining_characters = remaining_characters + standard_alphabet.substr(i,1);
           }
    }

    return remaining_characters;
}

std::string SolverFunctions::ShiftAlphaSet(std::string &cipher_base_alphabet, std::string &start_char)
{
    int cipher_alphabet_size = cipher_base_alphabet.size();
    std::string new_alpha_set;
    int start_position;

    for(int i = 0; i < cipher_base_alphabet.length(); i++)
    {
        if(start_char == cipher_base_alphabet.substr(i,1))
        {
            start_position = i;
        }
    }

    new_alpha_set = cipher_base_alphabet.substr(start_position,cipher_alphabet_size-start_position) + cipher_base_alphabet.substr(0,start_position);

    return new_alpha_set;
}

std::vector<std::string> SolverFunctions::Generate_Cipher_Alphabets_From_Keywords(std::string &cipher_base_alphabet, std::string &keyword_one, std::string &keyword_two, int keyword_start_position)
{

        std::vector<std::string> cipher_alphabet_vector;

        std::string keyword_one_start_char = keyword_one.substr(keyword_start_position,1);

        int standard_alphabet_size = cipher_base_alphabet.size();
        int keyword_one_size = keyword_one.length();

        for(int i= 0; i < keyword_two.length(); i++)
        {
            int new_alpha_start_position;
            for(int j = 0; j < cipher_base_alphabet.length(); j++)
            {
                if(keyword_two.substr(i,1) == cipher_base_alphabet.substr(j,1))
                {
                    new_alpha_start_position = j;
                }
            }

            std::string new_alpha_start_char = cipher_base_alphabet.substr(new_alpha_start_position,1);
            std::string cipher_keyset = ShiftAlphaSet(cipher_base_alphabet,new_alpha_start_char);

            cipher_alphabet_vector.push_back(cipher_keyset);
        }

        return cipher_alphabet_vector;
}

std::string SolverFunctions::Vigenere_With_Alpha_Keywords(std::string &encrypted_puzzle_part,std::string &keyword_one, std::string &keyword_two)
{
    int keyword_starting_position = 0;
    int keyword_two_length = keyword_two.length();

    std::string standard_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::string remaining_alphabet_characters = RemainingAlphabetString(keyword_one);
    std::string cipher_base_alphabet = keyword_one + remaining_alphabet_characters;
    std::string decrypted_string;

    std::cout << "Keyword One:\t" << keyword_one << std::endl << "Keyword Two:\t" << keyword_two << std::endl << std::endl;
    std::vector<std::string> cipher_alphabet_vector = Generate_Cipher_Alphabets_From_Keywords(cipher_base_alphabet, keyword_one, keyword_two, keyword_starting_position);

    int vector_index = 0;
    for(int i = 0; i < encrypted_puzzle_part.length(); i++)
    {
        vector_index = (vector_index < keyword_two_length) ? vector_index : 0;
        for(int j = 0; j < cipher_alphabet_vector[vector_index].length(); j++)
        {
            if(encrypted_puzzle_part.substr(i,1) == cipher_alphabet_vector[vector_index].substr(j,1))
            {
                decrypted_string = decrypted_string + cipher_base_alphabet.substr(j,1);
            }
        }
        vector_index++;
    }

    return decrypted_string;
}

std::vector<std::vector<std::string> > SolverFunctions::String_To_Matrix(std::string &string_as_matrix, int width)
{
    std::vector<std::vector<std::string> > new_matrix;
    std::vector<std::string> new_matrix_row;
    int new_matrix_row_counter = 0;

    for(int i = 0; i < string_as_matrix.length(); i++)
    {
        new_matrix_row.push_back(string_as_matrix.substr(i,1));
        new_matrix_row_counter++;
        if(new_matrix_row_counter == width)
        {
            new_matrix.push_back(new_matrix_row);
            new_matrix_row.clear();
            new_matrix_row_counter = 0;
        }
    }

    return new_matrix;
}

std::string SolverFunctions::Matrix_To_String(std::vector<std::vector<std::string> > matrix)
{
    std::string matrix_as_string;

    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix[i].size(); j++)
        {
            matrix_as_string = matrix_as_string + matrix[i][j];
        }
    }

    return matrix_as_string;
}

std::vector<std::vector<std::string> > SolverFunctions::RotateMatrix(std::vector<std::vector<std::string> > matrix)
{
    std::vector<std::vector<std::string> > rotated_matrix;
    std::vector<std::string> row_array;

    for(int j = 0; j < matrix[0].size(); j++)
    {
        for(int i = 0; i < matrix.size(); i++)
        {
            row_array.push_back(matrix[matrix.size() - i -1][j]);
        }
        rotated_matrix.push_back(row_array);
        row_array.clear();
    }

    return rotated_matrix;
}

std::string SolverFunctions::PrintMatrix(std::vector<std::vector<std::string> > grid_matrix)
{
    std::string matrix_string;

    for(int j = 0; j < grid_matrix.size(); j++)
    {
        for (int k = 0; k < grid_matrix[j].size(); k++)
        {
           std::cout << grid_matrix[j][k];
           matrix_string = matrix_string + grid_matrix[j][k];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return matrix_string;

}

std::string SolverFunctions::Grid_Rotation_Solver(std::string &encrypted_puzzle_part)
{
    int grid_width = 25;

    std::vector<std::vector<std::string> > grid_matrix;
    std::string row_string;
    std::vector<std::string> row_array;

    int column_counter = 0;

    for(int i = 0; i < encrypted_puzzle_part.length(); i++)
    {
        row_array.push_back(encrypted_puzzle_part.substr(i,1));
        column_counter++;
        if((column_counter == grid_width - 1) || (i == encrypted_puzzle_part.size()-1))
        {
            column_counter = 0;
            grid_matrix.push_back(row_array);
            row_array.clear();
        }
    }

    // PrintMatrix(grid_matrix);

    std::vector<std::vector<std::string> > rotated_matrix = RotateMatrix(grid_matrix);
    // PrintMatrix(rotated_matrix);

    std::string matrix_string = Matrix_To_String(rotated_matrix);
    std::vector<std::vector<std::string> > new_matrix = String_To_Matrix(matrix_string,8);
    new_matrix = RotateMatrix(new_matrix);
    std::string solution = PrintMatrix(new_matrix);

    return solution;
}

void SolverFunctions::SolvePuzzle()
{
        // std::vector<std::string> dictionary_vector = Load_Dictionary_List();

        /*
        for(int i = 0; i < dictionary_vector.size(); i++)
        {
            std::cout << dictionary_vector[i] << std::endl;
        }
        */
        std::string part_one_keyword_one = "KRYPTOS";
        std::string part_one_keyword_two = "PALIMPSEST";
        std::string encrypted_part_one = "EMUFPHZLRFAXYUSDJKZLDKRNSHGNFIVJYQTQUXQBQVYUVLLTREVJYQTMKYRDMFD";

        std::string part_one_decrypted = Vigenere_With_Alpha_Keywords(encrypted_part_one,part_one_keyword_one,part_one_keyword_two);
        part_one_decrypted = FindReplaceInString(part_one_decrypted,"?","");

        std::cout << "Part One Length:\t" << encrypted_part_one.length() << std::endl;
        std::cout << "Part One:\t" << encrypted_part_one << std::endl;

        std::cout << part_one_decrypted << std::endl << std::endl;

        std::string part_two_keyword_one = "KRYPTOS";
        std::string part_two_keyword_two = "ABSCISSA";
        std::string encrypted_part_two = "VFPJUDEEHZWETZYVGWHKKQETGFQJNCEGGWHKK?DQMCPFQZDQMMIAGPFXHQRLGTIMVMZJANQLVKQEDAGDVFRPJUNGEUNAQZGZLECGYUXUEENJTBJLBQCRTBJDFHRRYIZETKZEMVDUFKSJHKFWHKUWQLSZFTIHHDDDUVH?DWKBFUFPWNTDFIYCUQZEREEVLDKFEZMOQQJLTTUGSYQPFEUNLAVIDXFLGGTEZ?FKZBSFDQVGOGIPUFXHHDRKFFHQNTGPUAECNUVPDJMQCLQUMUNEDFQELZZVRRGKFFVOEEXBDMVPNFQXEZLGREDNQFMPNZGLFLPMRJQYALMGNUVPDXVKPDQUMEBEDMHDAFMJGZNUPLGEWJLLAETG";
        encrypted_part_two = FindReplaceInString(encrypted_part_two,"?","");


        std::string part_two_decrypted = Vigenere_With_Alpha_Keywords(encrypted_part_two,part_two_keyword_one,part_two_keyword_two);

        std::cout << "Part Two Length:\t" << encrypted_part_two.length() << std::endl;
        std::cout << "Part Two:\t" << encrypted_part_two << std::endl;
        std::cout << part_two_decrypted << std::endl << std::endl;

        std::string encrypted_part_three = "ENDYAHROHNLSRHEOCPTEOIBIDYSHNAIACHTNREYULDSLLSLLNOHSNOSMRWXMNETPRNGATIHNRARPESLNNELEBLPIIACAEWMTWNDITEENRAHCTENEUDRETNHAEOETFOLSEDTIWENHAEIOYTEYQHEENCTAYCREIFTBRSPAMHNEWENATAMATEGYEERLBTEEFOASFIOTUETUAEOTOARMAEERTNRTIBSEDDNIAAHTTMSTEWPIEROAGRIEWFEBAECTDDHILCEIHSITEGOEAOSDDRYDLORITRKLMLEHAGTDHARDPNEOHMGFMFEUHEECDMRIPFEIMEHNLSSTTRTVDOHW?";
        encrypted_part_three = FindReplaceInString(encrypted_part_three,"?","");

        std::cout << "Part Three Length:\t" << encrypted_part_three.length() << std::endl;
        std::cout << "Part Three:\t" << encrypted_part_three << std::endl;

        std::string part_three_decrypted = Grid_Rotation_Solver(encrypted_part_three);

        std::cout << part_three_decrypted << std::endl << std::endl;

        std::string encrypted_part_four = "OBKRUOXOGHULBSOLIFBBWFLRVQQPRNGKSSOTWTQSJQSSEKZZWATJKLUDIAWINFBNYPVTTMZFPKWGDKZXTJCDIGKUHUAUEKCAR";
        std::string aligned_part_four = "                                                               BERLINCLOCK                       ";
        encrypted_part_four = FindReplaceInString(encrypted_part_four,"?","");

        std::cout << "Part Four Length:\t" << encrypted_part_four.length() << std::endl;
        std::cout << "Part Four:\t" << encrypted_part_four << std::endl;

        std::cout << "Part Four:\t" << aligned_part_four << std::endl;

}
