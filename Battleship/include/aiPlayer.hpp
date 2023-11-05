#ifndef AIPLAYER_HPP
#define AIPLAYER_HPP

#include "player.hpp"

class aiPlayer : public Player
{
public:
    aiPlayer() : Player() {}

    // 特定のセルが既に攻撃されたかどうかを確認
    bool isAttacked(int row, int col) const
    {
        return attacks_grid[row][col];
    }

    // 特定のセルが盤面の範囲内かどうかを確認
    bool isValid(int row, int col) const
    {
        return row >= 0 && row < m_grid_rows && col >= 0 && col < m_grid_cols;
    }

    // 選択したセルが戦艦だと`true`を返す
    bool check_hit(int row, int col)
    {
        return m_grid[row][col] != '~';
    }

    // 最後にヒットした位置から攻撃可能なセルを探し、その中からランダムにセルを選んで攻撃
    void logical_attack()
    {
        int row, col;
        // Check if the last hit position is valid
        if (last_hit_position.first != -1 && last_hit_position.second != -1)
        {
            // Logic to attack around the last hit position
            // TODO: Implement the logic to check around the last_hit_position
            std::vector<std::pair<int, int>> potential_target;
            std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
            for (auto &dir : directions)
            {
                int new_row = last_hit_position.first + dir.first;
                int new_col = last_hit_position.second + dir.second;
                // セルが盤面の範囲かつ未攻撃であればリストに追加
                if (isValid(new_row, new_col) && !isAttacked(new_row, new_col))
                {
                    std::cout << "Im here_0" << std::endl;

                    potential_target.push_back({new_row, new_col});
                }
                std::cout << "Im here_1" << std::endl;
            }
            if (!potential_target.empty())
            {
                int rand_index = getRandomInt(potential_target.size());
                auto target = potential_target[rand_index];
                row = target.first;  // 更新された行の値
                col = target.second; // 更新された列の値

                print_ai_selection(row, col); // 正しい行と列を表示
                Player::attack(row, col);     // 攻撃を実行

                // 攻撃結果に基づいて last_hit_position と attacks_grid を更新
                if (check_hit(row, col)) // このメソッドは攻撃後の結果を反映する必要があります
                {
                    last_hit_position = {row, col}; // ヒットした場合にのみ更新
                    std::cout << "Im here_2" << std::endl;
                }
                else
                {
                    if (!potential_target.empty())
                    {
                        last_hit_position = {row, col}; // ヒットした場合にのみ更新
                        std::cout << "Im here_3" << std::endl;
                    }
                }
            }
            std::cout << "Im here_4" << std::endl;
        }
        else
        {
            // Select a random position that has not been attacked yet
            do
            {
                row = getRandomInt(10);
                col = getRandomInt(10);
            } while (attacks_grid[row][col]); // 既に攻撃された箇所を除く `attacks_grid`は`bool`型

            print_ai_selection(row, col); // 正しい行と列を表示
            Player::attack(row, col);     // 攻撃を実行

            // 攻撃結果に基づいて last_hit_position と attacks_grid を更新
            if (check_hit(row, col)) // このメソッドは攻撃後の結果を反映する必要があります
            {
                last_hit_position = {row, col}; // ヒットした場合にのみ更新
            }
            // attacks_grid は既に攻撃されたセルを true で記録する
            attacks_grid[row][col] = true;
        }
    }

    void print_ai_selection(int row, int col)
    {
        std::cout << "AI's selection of row: " << row << std::endl;
        std::cout << "AI's selection of col: " << col << std::endl;
    }
};

#endif // AIPLAYER_HPP