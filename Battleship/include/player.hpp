#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <cstdlib>
#include <ctime>

#include "utility.hpp"
#include "ship.hpp"

// 0 から t_max - 1 までのランダムな整数を返す関数
int getRandomInterval(const int t_max)
{
    srand(time(NULL));
    return rand() % t_max;
}

struct Player
{
    // 定数：ゲーム盤のサイズ
    const unsigned int m_grid_cols{10};
    const unsigned int m_grid_rows{10};

    // ゲーム盤：2次元ベクトル
    std::vector<std::vector<char>> m_grid;

    // 艦隊：Ship オブジェクトのベクトル
    std::vector<Ship> m_fleet;

    // コンストラクタ：プレイヤーのゲーム盤と艦隊を初期化する
    Player()
    {
        // ゲーム盤を '~'（水面）で初期化
        std::vector<char> row(m_grid_cols, '~');
        for (unsigned int it = 0; it < m_grid_rows; it++)
        {
            m_grid.push_back(row);
        }

        // 艦隊に各種艦船を追加
        m_fleet.push_back(Ship('D', 3)); // 駆逐艦
        m_fleet.push_back(Ship('C', 4)); // 巡洋艦
        m_fleet.push_back(Ship('M', 1)); // 掃海艇
    }

    // 艦隊をランダムな位置に配置する関数
    void fleetPlacement()
    {
        for (Ship ship : m_fleet)
        {
            bool placed = false;
            while (!placed)
            {
                // ランダムな位置を選ぶ
                int row_index = getRandomInterval(m_grid_rows);
                int col_index = getRandomInterval(m_grid_cols - ship.m_size);

                // 艦船が重ならずに配置できるかチェック
                bool canPlace = true;
                for (int it = 0; it < ship.m_size; it++)
                {
                    if (m_grid[row_index][col_index + it] != '~')
                    {
                        canPlace = false;
                        break;
                    }
                }

                // 重ならない場合、艦船を配置
                if (canPlace)
                {
                    for (int it = 0; it < ship.m_size; it++)
                    {
                        m_grid[row_index][col_index + it] = ship.m_ID;
                    }
                    placed = true;
                }
            }
        }
    }
};

#endif // PLAYER_HPP
