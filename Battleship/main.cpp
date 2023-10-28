#include <iostream>
#include <vector>

#include "player.hpp"
#include "ship.hpp"
#include "tool.hpp"
#include "aiPlayer.hpp"

void answerTable(Player &player)
{
    int i = 1;

    // プレイヤーのグリッドを表示
    std::cout << "# --- ANSWER TABLE--- #\n\n";
    std::cout << "<Player>" << std::endl;
    printGrid(player.m_grid);
    std::cout << "# ------------------- #\n\n";
}

void playerTurn(Player &player)
{
    int row, col;
    std::cout << "Enter the row to attack: ";
    std::cin >> row;
    std::cout << "Enter the column to attack: ";
    std::cin >> col;

    player.attack(row, col);

    std::cout << "<Player Table>\n";
    printGrid(player.m_display_grid);
}

int main()
{
    // 2人プレイ用
    // Player player1, player2;
    // player1.fleetPlacement();
    // player2.fleetPlacement();
    // answerTable(player1);
    // answerTable(player2);
    // while (true)
    // {
    //     playerTurn(player1);
    //     if (player1.isGameOver())
    //     {
    //         std::cout << "Player1 wins!\n";
    //         break;
    //     }

    //     playerTurn(player2);
    //     if (player2.isGameOver())
    //     {
    //         std::cout << "Player2 wins!\n";
    //         break;
    //     }
    // }

    // vs AI
    Player humanPlayer;
    aiPlayer aiPlayer;

    humanPlayer.fleetPlacement();
    aiPlayer.fleetPlacement();

    answerTable(humanPlayer);

    answerTable(aiPlayer);

    while (true)
    {
        playerTurn(humanPlayer);
        humanPlayer.shipHealth();
        if (humanPlayer.isGameOver())
        {
            std::cout << "Human wins!\n";
            break;
        }

        aiPlayer.attack();
        std::cout << "<Player Table>\n";
        printGrid(aiPlayer.m_display_grid);
        aiPlayer.shipHealth();
        if (aiPlayer.isGameOver())
        {
            std::cout << "AI wins!\n";
            break;
        }
    }

    return 0;
}
