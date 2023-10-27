#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <cstdlib>
#include <ctime>

#include "tool.hpp"
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

    // 表示用ゲーム盤：2次元ベクトル
    std::vector<std::vector<char>> m_display_grid;

    // 艦隊：Ship オブジェクトのベクトル
    // m_fleet はC++の std::vector コンテナによって管理されている. これはリストに似たデータ構造をしている
    std::vector<Ship> m_fleet;

    // コンストラクタ：プレイヤーのゲーム盤と艦隊を初期化する
    Player()
    {
        // ゲーム盤を '~'（水面）で初期化
        std::vector<char> row(m_grid_cols, '~');
        for (unsigned int it = 0; it < m_grid_rows; it++)
        {
            m_grid.push_back(row);
            m_display_grid.push_back(row);
        }

        // 艦隊に各種艦船を追加
        m_fleet.push_back(Ship('M', 2, 2));
        m_fleet.push_back(Ship('S', 3, 3));
        m_fleet.push_back(Ship('D', 3, 3));
        m_fleet.push_back(Ship('C', 4, 4));
        m_fleet.push_back(Ship('A', 5, 5));
    }

    bool checkForFreeCells(const int row_index, const int col_index, const Ship ship)
    {

        for (int it = 0; it < ship.m_size; it++)
        {
            if (m_grid[row_index][col_index + it] != '~')
            {
                return false;
            }
        }

        return true;
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

                // 重ならない場合、艦船を配置
                if (checkForFreeCells(row_index, col_index, ship))
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

    void attack(int row, int col)
    {
        // すでに攻撃された場所かチェック
        // ToDo 数字以外が入力されたときの対処（無限ループにならないようにする）
        if (m_display_grid[row][col] != '~')
        {
            std::cout << "You have already attacked this position. Choose another one.\n";

            // 同じ箇所を攻撃した場合，下の処理を行わず，mainのwhileに戻る
            return;
        }

        // 戦艦が存在するか確認
        if (m_grid[row][col] != '~')
        {
            if (m_grid[row][col] == 'D')
            {
                std::cout << "Hit! It's 'D'ship!\n\n";
                m_display_grid[row][col] = 'D'; // 命中した箇所を 'D' に更新
            }
            if (m_grid[row][col] == 'C')
            {
                std::cout << "Hit! It's 'C'ship!\n\n";
                m_display_grid[row][col] = 'C'; // 命中した箇所を 'C' に更新
            }
            if (m_grid[row][col] == 'M')
            {
                std::cout << "Hit! It's 'M'ship!\n\n";
                m_display_grid[row][col] = 'M'; // 命中した箇所を 'M' に更新
            }

            // 艦船の耐久度を減らす
            for (Ship &ship : m_fleet)
            {
                if (ship.m_ID == m_grid[row][col]) // 1. プレイヤーの艦隊（m_fleet）内のすべての艦船に対してループを回す
                {                                  // 2. 現在の艦船（ship）のIDが、攻撃された座標（row, col）に存在する艦船のIDと一致するか確認
                    ship.m_health--;               // 3. 一致する場合、その艦船の耐久度（m_health）を1減らす
                    break;                         // 4. 耐久度を減らした後は、ループを抜ける（他の艦船は影響を受けない）
                }
            }
            /*
            & シンボルは参照（reference）を示す。したがって、Ship &ship は Ship 型のオブジェクトへの参照を意味する

            ＜参照を使う理由＞
            効率: オブジェクトのコピーを避けることで、メモリと時間を節約できます。
            変更の反映: 参照を通じてオブジェクトを変更すると、その変更は元のオブジェクトにも反映されます。

            参照（&）を使うと、ship は m_fleet の各要素への参照となります。
            この場合、ループ内で ship を通じて行った変更（例えば、艦船の耐久度を減らす）は、m_fleet に直接反映されます。

            shipだけだと，　_fleet の各要素は ship という新しい変数にコピーされます。
            このコピーに対する変更は m_fleet に反映されません。
            */
        }
        else
        {
            std::cout << "Miss.\n\n";
            m_display_grid[row][col] = 'X';
        }
    }

    // ゲームが終了したかどうかを判定する関数
    bool isGameOver()
    {
        for (const Ship &ship : m_fleet)
        {
            if (ship.m_health > 0)
            {
                return false; // まだ沈んでいない艦船が存在する
            }
        }
        return true; // 全ての艦船が沈んでいる
    }
};

#endif // PLAYER_HPP
