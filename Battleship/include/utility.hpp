#ifndef UTILITY_HPP
#define UTILITY_HPP
#include <vector>
#include <iostream>
#include <random>

// 指定された最大値までのランダムな整数を返す関数
int getRandomInt(const unsigned int t_max)
{
    return rand() % (t_max + 1);
}

// グリッドを表示する関数
void printGrid(const std::vector<std::vector<char>> t_grid)
{
    // 各行についてループ
    for (unsigned int row_index = 0; row_index < t_grid.size(); row_index++)
    {
        const auto row = t_grid[row_index];

        // 各列についてループ
        for (unsigned int col_index = 0; col_index < row.size(); col_index++)
        {
            // グリッドの各要素を表示
            std::cout << row[col_index] << " ";
        }
        // 行の終わりで改行
        std::cout << "\n";
    }
    std::cout << "\n";
}

#endif // UTILITY_HPP
