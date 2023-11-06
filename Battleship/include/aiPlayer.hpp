#ifndef AIPLAYER_HPP
#define AIPLAYER_HPP

#include "player.hpp"

class aiPlayer : public Player
{
    std::vector<std::pair<int, int>> potential_targets;

    std::pair<int, int> first_hit_position = {-1, -1}; // 最初にヒットした位置を記録する変数

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

    bool check_hit(int row, int col)
    {
        if (m_grid[row][col] != '~')
        {
            std::cout << "Im here 1" << std::endl;

            if (first_hit_position.first == -1 && first_hit_position.second == -1)
            {
                first_hit_position = {row, col}; // 最初にヒットした位置を更新する

                std::cout << "最初にヒットした位置を記録したよ" << std::endl;
            }
            return true;
        }
        return false;
    }

    bool is_ship_sunk(int row, int col) const
    {
        // Check if the cell at (row, col) has been attacked
        if (!attacks_grid[row][col])
        {
            return false; // If the cell has not been attacked, the ship cannot be sunk
        }

        // Retrieve the ID of the ship at the attacked cell
        char shipID = m_grid[row][col];

        // Check all cells for this ship ID
        for (unsigned int r = 0; r < m_grid_rows; ++r)
        {
            for (unsigned int c = 0; c < m_grid_cols; ++c)
            {
                if (m_grid[r][c] == shipID && !attacks_grid[r][c]) // !attacks_grid[][]で攻撃されていないセル
                {
                    return false; // If any cell with this ship ID has not been attacked, the ship is not sunk
                }
            }
        }

        // If all cells with this ship ID have been attacked, the ship is sunk
        return true;
    }

    // Helper function to update potential targets around the last hit position
    void update_potential_targets()
    {
        potential_targets.clear();
        static const std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (const auto &dir : directions)
        {
            int new_row = last_hit_position.first + dir.first;
            int new_col = last_hit_position.second + dir.second;
            if (isValid(new_row, new_col) && !isAttacked(new_row, new_col))
            {
                potential_targets.push_back({new_row, new_col});
            }
        }
    }

    void print_ai_selection(int row, int col)
    {
        std::cout << "AI's selection of row: " << row << std::endl;
        std::cout << "AI's selection of col: " << col << std::endl;
    }

public:
    aiPlayer() : Player() {}

    // Last hit position attack logic
    void logical_attack()
    {
        int row, col;

        // Update potential targets around the last hit position
        if (last_hit_position.first != -1 && last_hit_position.second != -1)
        {
            update_potential_targets();
        }

        // Select attack position from potential targets
        if (!potential_targets.empty())
        {
            int rand_index = getRandomInt(potential_targets.size());
            auto target = potential_targets[rand_index];
            row = target.first;  // Updated row value
            col = target.second; // Updated column value
        }
        else
        {
            // If there are no potential targets and the first hit position is valid
            if (first_hit_position.first != -1 && first_hit_position.second != -1)
            {
                // Reset last hit to first hit and update potential targets around it
                last_hit_position = first_hit_position;
                update_potential_targets();
                if (!potential_targets.empty())
                {
                    int rand_index = getRandomInt(potential_targets.size());
                    auto target = potential_targets[rand_index];
                    row = target.first;  // Updated row value
                    col = target.second; // Updated column value
                }
            }
            // If there are no potential targets at all, select a new random position
            if (potential_targets.empty())
            {
                do
                {
                    row = getRandomInt(m_grid_rows);
                    col = getRandomInt(m_grid_cols);
                } while (isAttacked(row, col)); // Avoid already attacked positions
            }
        }

        print_ai_selection(row, col); // Display the correct row and column
        Player::attack(row, col);     // Execute the attack

        // Update last_hit_position and attacks_grid based on the result of the attack
        if (check_hit(row, col)) // This method needs to reflect the result after the attack
        {
            if (is_ship_sunk(row, col))
            {
                std::cout << "船が沈んでいるようだから，リセットするね" << std::endl;
                potential_targets.clear();

                first_hit_position = {-1, -1}; // ここで最初にヒットした位置をリセットする
                last_hit_position = {-1, -1};  // ここで最後にヒットした位置をリセットする
            }
            else
            {
                last_hit_position = {row, col}; // Only update if it was a hit
            }
        }
        // Record that the cell has been attacked in attacks_grid
        attacks_grid[row][col] = true;
    }
};

#endif // AIPLAYER_HPP