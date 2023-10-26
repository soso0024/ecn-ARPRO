#include <iostream>
#include <vector>

// #include "include/grid.hpp"
#include "player.hpp"
#include "ship.hpp"
#include "utility.hpp"

int main()
{
    Player player;

    player.fleetPlacement();

    printGrid(player.m_grid);

    return 0;
}