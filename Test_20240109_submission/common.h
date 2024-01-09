#pragma once

#define CARD_NUM 52      //１デッキのカード枚数(ジョーカー抜き)
#define MARK_NUM 4
#define NUMBER_NUM 13
#define BC_DECK_NUM 6    //バカラのデッキ数
#define MIN_PAR_NUM 1    //ゲームに参加できる最小人数
#define MAX_PAR_NUM 5    //ゲームに参加できる最大人数

enum GameMode {
    NONE = 0,
    BACCARAT = 1,
    NAMECHANGE = 2,
};