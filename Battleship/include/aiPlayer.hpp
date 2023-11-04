#ifndef AIPLAYER_HPP
#define AIPLAYER_HPP

#include "player.hpp"

class aiPlayer : public Player
{
public:
    aiPlayer() : Player() {}
    void attack()
    {
        // AIの攻撃ロジック
        int row = getRandomInt(10);
        int col = getRandomInt(10);

        print_ai_selection(row, col);

        // 基底クラスのattackメソッドを呼び出す
        Player::attack(row, col);
    }

    void logical_attack()
    {
        int row, col;
        // Check if the last hit position is valid
        if (last_hit_position.first != -1 && last_hit_position.second != -1)
        {
            // Logic to attack around the last hit position
            // TODO: Implement the logic to check around the last_hit_position
        }
        else
        {
            // Select a random position that has not been attacked yet
            do
            {
                row = getRandomInt(10);
                col = getRandomInt(10);
            } while (attacks_grid[row][col]); // Exclude already attacked positions
        }
        // Perform the attack on the selected position
        print_ai_selection(row, col);

        // Call the base class attack method
        Player::attack(row, col);
        // Update last_hit_position and attacks_grid based on the attack result
        // TODO: Implement the method to get the result of the attack
        bool hit = false; // Replace with actual attack result
        if (hit)
        {
            last_hit_position = {row, col};
        }
        attacks_grid[row][col] = true;
    }

    void print_ai_selection(int row_index, int col_index)
    {
        std::cout << "AI's selection of row: " << row_index << std::endl;
        std::cout << "AI's selection of col: " << col_index << std::endl;
    }
};

#endif // AIPLAYER_HPP