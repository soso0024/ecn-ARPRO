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
    std::cout << "<Answer Table>\n";
    printGrid(player.m_grid);

    while (true)
    {
        std::cout << "<Player Table>\n";
        printGrid(player.m_display_grid);

        int row, col;
        std::cout << "Enter the row to attack: ";
        std::cin >> row;
        std::cout << "Enter the column to attack: ";
        std::cin >> col;

        player.attack(row, col); // 攻撃を行い，　結果を判定

        // ゲームが終了したかどうかを判定
        if (player.isGameOver())
        {
            std::cout << "Congratulation, you've sunk all the ships!\n";
            break; // ゲーム終了
        }
    }

    return 0;
}
