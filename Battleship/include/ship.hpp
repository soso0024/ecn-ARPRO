#ifndef SHIP_HPP
#define SHIP_HPP

struct Ship
{
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

#endif // SHIP_HPP