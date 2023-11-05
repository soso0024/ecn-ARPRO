#include <iostream>
#include <vector>

#include "player.hpp"
#include "ship.hpp"
#include "tool.hpp"
#include "aiPlayer.hpp"

void answerTable(Player &player)
{
    // プレイヤーのグリッドを表示
    std::cout << "# --- ANSWER TABLE--- #\n\n";
    std::cout << "<Ship Table>" << std::endl;
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

    std::cout << "<Ship Table>\n";
    printGrid(player.m_display_grid);
    player.printShipHealth();
}

void aiTurn(aiPlayer &player)
{
    player.logical_attack();
    std::cout << "<Ship Table>\n";
    printGrid(player.m_display_grid);
    player.printShipHealth();
}

void withPlayer(Player player1, Player player2)
{
    // 2人プレイ用
    player1.fleetPlacement();
    player2.fleetPlacement();

    answerTable(player1);
    answerTable(player2);

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
}

void withAI(Player humanPlayer, aiPlayer aiPlayer)
{
    humanPlayer.fleetPlacement();
    aiPlayer.fleetPlacement();

    answerTable(humanPlayer);
    answerTable(aiPlayer);

    while (true)
    {
        playerTurn(humanPlayer);

        if (humanPlayer.isGameOver())
        {
            std::cout << "Human wins!\n";
            break;
        }

        aiTurn(aiPlayer);

        if (aiPlayer.isGameOver())
        {
            std::cout << "AI wins!\n";
            break;
        }
    }
}

int selectGameMode()
{
    int mode;
    std::cout << "Select Game Mode:" << std::endl;
    std::cout << "1. Play with another player" << std::endl;
    std::cout << "2. Play with AI" << std::endl
              << "Your choice: ";
    std::cin >> mode;

    // エラーハンドリング: 無効な選択肢が入力された場合
    while (mode != 1 && mode != 2)
    {
        std::cout << "Invalid selection. Please select again: \n";
        std::cin >> mode;
    }

    return mode;
}

int main()
{
    int gameMode = selectGameMode();

    if (gameMode == 1)
    {
        Player player1;
        Player player2;

        withPlayer(player1, player2);
    }
    else if (gameMode == 2)
    {
        // vs AI
        Player humanPlayer;
        aiPlayer aiPlayer;

        withAI(humanPlayer, aiPlayer);
    }

    return 0;
}
