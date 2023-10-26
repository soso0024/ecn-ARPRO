#include <iostream>
#include <vector>

#include "player.hpp"
#include "ship.hpp"
#include "utility.hpp"

int main()
{
    // Playerオブジェクトを生成
    Player player;

    // プレイヤーの艦隊を配置
    player.fleetPlacement();

    // プレイヤーのグリッドを表示
    printGrid(player.m_grid);

    while (true)
    {
        printGrid(player.m_display_grid);

        int row, col;
        std::cout << "Enter the row to attack: ";
        std::cin >> row;
        std::cout << "Enter the column to attack: ";
        std::cin >> col;

        player.attack(row, col);
    }

    return 0;
}
