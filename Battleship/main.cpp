#include <iostream>
#include <vector>

#include "player.hpp"
#include "ship.hpp"
#include "tool.hpp"

void playerTurn(Player &player)
{
std:
    std::cout << "<Player Table>\n";
    printGrid(player.m_display_grid);

    int row, col;
    std::cout << "Enter the row to attack: ";
    std::cin >> row;
    std::cout << "Enter the column to attack: ";
    std::cin >> col;

    player.attack(row, col);
}

int main()
{
    // Playerオブジェクトを生成
    Player player1, player2;

    // プレイヤーの艦隊を配置
    player1.fleetPlacement();
    player2.fleetPlacement();

    // プレイヤーのグリッドを表示
    std::cout << "# --- ANSWER TABLE--- #\n\n";
    std::cout << "<Player1>\n";
    printGrid(player1.m_grid);

    std::cout << "<Player2>\n";
    printGrid(player2.m_grid);
    std::cout << "# ------------------- #\n\n";

    while (true)
    {
        playerTurn(player1);
        if (player1.isGameOver())
        {
            std::cout << "Player1 wins!\n";
            break;
        }

        playerTurn(player2);
        if (player2.isGameOver())
        {
            std::cout << "Player2 wins!\n";
            break;
        }
    }

    return 0;
}
