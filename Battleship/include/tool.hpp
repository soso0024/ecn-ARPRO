#ifndef TOOL_HPP
#define TOOL_HPP
#include <vector>
#include <iostream>
#include <random>

// 一度だけランダムナンバーを出すようにする
bool initialized = false;
void initializeRandom()
{
    if (!initialized)
    {
        srand(time(NULL));
        initialized = true;
    }
}

// 0 から t_max - 1 までのランダムな整数を返す関数
int getRandomInt(const int t_max)
{
    initializeRandom();
    return rand() % t_max;
}

// Grid (格子) を表示する関数
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

#endif // TOOL_HPP
