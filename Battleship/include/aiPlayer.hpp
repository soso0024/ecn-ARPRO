#ifndef AIPLAYER_HPP
#define AIPLAYER_HPP

#include "player.hpp"

class aiPlayer : public Player
{
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
    std::vector<std::pair<int, int>> potential_targets;

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

public:
    aiPlayer() : Player() {}

    // Additional methods...

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
            // Select a new random position that has not been attacked yet
            do
            {
                row = getRandomInt(m_grid_rows);
                col = getRandomInt(m_grid_cols);
            } while (isAttacked(row, col)); // Avoid already attacked positions
        }

        print_ai_selection(row, col); // Display the correct row and column
        Player::attack(row, col);     // Execute the attack

        // Update last_hit_position and attacks_grid based on the result of the attack
        if (check_hit(row, col)) // This method needs to reflect the result after the attack
        {
            last_hit_position = {row, col}; // Only update if it was a hit
        }
        // Record that the cell has been attacked in attacks_grid
        attacks_grid[row][col] = true;
    }

    void print_ai_selection(int row, int col)
    {
        std::cout << "AI's selection of row: " << row << std::endl;
        std::cout << "AI's selection of col: " << col << std::endl;
    }
};

#endif // AIPLAYER_HPP