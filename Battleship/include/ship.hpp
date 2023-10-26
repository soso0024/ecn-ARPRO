#ifndef SHIP_HPP
#define SHIP_HPP

// Ship構造体を定義
struct Ship
{
    char m_ID;             // 船の識別子
    unsigned int m_size;   // 船のサイズ
    unsigned int m_health; // 船の耐久度（ヒットポイント）

    // コンストラクタ
    Ship(const char t_ID,
         const unsigned int t_size,
         unsigned int t_health)
        : m_ID(t_ID), m_size(t_size), m_health(t_health) // メンバ変数の初期化
    {
    }
};

/*
: m_ID(t_ID), m_size(t_size): この部分は初期化リストと呼ばれ、コンストラクタが呼び出されたときにメンバ変数 m_ID と m_size を初期化

m_ID(t_ID), m_size(t_size): ここで m_ID には t_ID の値が、m_size には t_size の値がそれぞれ設定される。
*/

#endif // SHIP_HPP
