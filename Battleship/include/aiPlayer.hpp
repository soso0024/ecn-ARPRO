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
        int row = getRandomInterval(10);
        int col = getRandomInterval(10);

        std::cout << "AI's selection of row: " << row << std::endl;
        std::cout << "AI's selection of col: " << col << std::endl;

        // 基底クラスのattackメソッドを呼び出す
        Player::attack(row, col);
    }
};

#endif // AIPLAYER_HPP