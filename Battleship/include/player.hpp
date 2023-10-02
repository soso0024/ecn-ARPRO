#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

int getRandomInterval(const int t_max)
{
    // srand(time(NULL));
    return rand() % t_max;
}

struct Ship{
    Ship(const char t_ID,
         const unsigned int t_size)
    {
        m_ID = t_ID;
        m_size = t_size;
    }

    // Constructor
    char m_ID;
    unsigned int m_size;
};

struct Player
{
    // Constructor
    Player(){
        std::vector<char> row;
        row.resize(m_grid_cols);

        for(unsigned int it=0; it<row.size(); it++){
            row[it] = '~';
        }

        for(unsigned int it=0; it<m_grid_rows; it++)
            m_grid.push_back(row);

        // method 1
        // Adding a destroyer of size 3
        // m_feet is a vector of ships
        Ship destroyer('D', 3);
        Ship cruiser('C', 4);
        Ship minesweeper('M', 1);

        m_fleet.push_back(destroyer);
        m_fleet.push_back(cruiser);
        m_fleet.push_back(minesweeper);

        // method 2
        // m_fleet.push_back(Ship('D', 3));


        // method 1
        // ship is a Ship object
        // for(int it=0; it<ship.m_size; it++){
        //     m_grid[row_index][col_index+it] = ship.m_ID;
        // }

        // method 2
        // m_grid[row_index][col_index] = ship.m_ID;

        // method 3
        // auto selected_row = m_grid[row_index];
        // m_grid[row_index][col_index] = 'D';
}

void fleetPlacement(){
    // Instance of the ship to place
    for(Ship ship : m_fleet){
        // place the ship at coordinates
        // place horizontally, in growing columns
        // 船の数が多くなったら，ここを変える必要がある．
        int row_index = getRandomInterval(6);
        int col_index = getRandomInterval(m_grid_cols - (ship.m_size - 1)); // このプログラムは，船のサイズが1の場合には，col_indexが10になってしまう．
                                                                            // これは，col_indexが0から始まるためである．
                                                                            // そのため，col_indexの最大値を9にする必要がある．
                                                                            // これは，m_grid_cols - (ship.m_size - 1) - 1とすることで実現できる．

        // ship is a Ship object
        for(int it=0; it<ship.m_size; it++){
            m_grid[row_index][col_index+it] = ship.m_ID;
        }
    }
    // Ship ship = m_fleet[0];

    // place the ship at coordinates (5, 3)
    // place horizontally, in growing columns
    // 船の数が多くなったら，ここを変える必要がある．
    // int row_index = getRandomInterval(6);
    // int col_index = getRandomInterval(m_grid_cols - (ship.m_size - 1));

    // auto ship = m_fleet[0];

    // // ship is a Ship object
    // for(int it=0; it<ship.m_size; it++){
    //     m_grid[row_index][col_index+it] = ship.m_ID;
    // }
}

    // Default initialisation
    const unsigned int m_grid_cols { 10 };
    const unsigned int m_grid_rows { 10 };

    // Declaration
    std::vector<std::vector<char>> m_grid;

    std::vector<Ship> m_fleet;
};

#endif // PLAYER_HPP