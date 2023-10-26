#ifndef UTILITY_HPP
#define UTILITY_HPP
#include <vector>
#include <iostream>
#include <random>

int getRandomInt(const unsigned int t_max){
    return rand() % (t_max + 1);
}

void printGrid(const std::vector<std::vector<char>> t_grid)
{
    for (unsigned int row_index = 0; row_index < t_grid.size(); row_index++)
    {
        const auto row = t_grid[row_index];

        for (unsigned int col_index = 0; col_index < row.size(); col_index++)
        {
            std::cout << row[col_index] << " ";
        }
        std::cout << "\n";
    }
}

#endif // UTILITY_HPP