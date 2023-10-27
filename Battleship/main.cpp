#include <iostream>
#include <vector>

#include "player.hpp"
#include "ship.hpp"
#include "tool.hpp"

using namespace std;

int main()
{
    // Playerオブジェクトを生成
    Player player1;
    Player player2;

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
        std::cout << "<Player1 Table>\n";
        printGrid(player1.m_display_grid);

        int player1_row, player1_col;
        std::cout << "Enter the row to attack: ";
        std::cin >> player1_row;
        std::cout << "Enter the column to attack: ";
        std::cin >> player1_col;

        player1.attack(player1_row, player1_col); // 攻撃を行い，　結果を判定

        std::cout << "<Player2 Table>\n";
        printGrid(player2.m_display_grid);

        int player2_row, player2_col;
        std::cout << "Enter the row to attack: ";
        std::cin >> player2_row;
        std::cout << "Enter the column to attack: ";
        std::cin >> player2_col;

        player2.attack(player2_row, player2_col); // 攻撃を行い，　結果を判定

        // ゲームが終了したかどうかを判定
        if (player1.isGameOver())
        {
            std::cout << "Congratulation, you've sunk all the ships!\n";
            break; // ゲーム終了
        }

        // ゲームが終了したかどうかを判定
        if (player2.isGameOver())
        {
            std::cout << "Congratulation, you've sunk all the ships!\n";
            break; // ゲーム終了
        }
    }

    return 0;
}
