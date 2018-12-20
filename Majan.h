//
// Created by User on 2018/12/19.
//

#ifndef MAJANGAME_MAJAN_H
#define MAJANGAME_MAJAN_H

/*
 * Majan
 *   type: 1 for 花
 *         2 for 字
 *         3 for 萬
 *         4 for 筒
 *         5 for 條
 *   num: 萬筒條直接給數字
 *        花:
 *            1 for 春
 *            2 for 夏
 *            3 for 秋
 *            4 for 冬
 *            5 for 梅
 *            6 for 蘭
 *            7 for 竹
 *            8 for 菊
 *        字:
 *            1 for 東
 *            2 for 南
 *            3 for 西
 *            4 for 北
 *            5 for 中
 *            6 for 發
 *            7 for 白
 */
class Majan{
public:
    int type;
    int num;
    bool compare(Majan*);
    void print();
    bool operator ==(Majan a);
    bool operator >=(Majan a);
    bool operator <=(Majan a);
};

#endif //MAJANGAME_MAJAN_H
