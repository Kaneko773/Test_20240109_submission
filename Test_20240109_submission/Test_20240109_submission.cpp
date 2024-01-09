// Test_20240109_submission.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#define _CRT_SECURE_NO_WARNINGS
#include "common.h"
#include "Shoe.h"
#include "Player.h"
#include "Dealer.h"
#include <iostream>
#include <cstring>
using namespace std;

void NameChange(Player* p, int& nNPCNum);
void Baccarat(Shoe* shoe, Player* p);

enum GameMode {
    NONE = 0,
    BACCARAT  = 1,
    NAMECHANGE = 2,
};

const char* NPCNAME[MAX_PAR_NUM] = {
    "NPC1",
    "NPC2",
    "NPC3",
    "NPC4",
    "NPC5"
};

int main()
{
    srand(time(NULL));

    Shoe shoe;
    Dealer dealer("dealer");
    Player player[MAX_PAR_NUM] = { NPCNAME[0], NPCNAME[1], NPCNAME[2], NPCNAME[3], NPCNAME[4] };
    int participantNum = 0;
    int notNPCNum = 0;

    int mode = 0;
    bool conti = true;

    do{
        printf("操作できるプレイヤーが %d 人、NPCが %d 人です\n", notNPCNum, MAX_PAR_NUM - notNPCNum);
        cout << "1.バカラ\n2.名前変更\n"
             << "0.ゲームを終了" << endl;
        cout << "\nゲームを選択　＞　" << flush;
        cin >> mode;
        system("cls");
        switch (mode) {
        case NONE: conti = false;  break;
        case BACCARAT: Baccarat(&shoe, player); break;
        case NAMECHANGE: NameChange(player, notNPCNum); break;
        default: break;
        }
    } while (conti);
}

void NameChange(Player* p, int& nNPCNum) {
    int select = 0;
    do{
        cout << "・名前がNPCのプレイヤーはコンピュータが操作します" << endl
            << "・名前を変更したプレイヤーを操作することが出来ます" << endl
            << "・名前を削除した場合、そのプレイヤーはNPCになります" << endl
            << "以下がゲームに参加予定の５人です" << endl;
        for (int i = 0; i < MAX_PAR_NUM; ++i) {
            cout << p[i].get_pName();
            if (i < MAX_PAR_NUM - 1) { cout << ", "; }
        }cout << endl;
        cout << "1:名前を変更する, 2:名前を削除する, 3:ゲーム選択へ戻る　＞　" << flush;
        cin >> select;
        system("cls");

        if (select == 1) {
            bool conti = true;
            do {
                int num;

                cout << "以下がゲームに参加予定の５人です" << endl;
                for (int i = 0; i < MAX_PAR_NUM; ++i) {
                    cout << p[i].get_pName();
                    if (i < MAX_PAR_NUM - 1) { cout << ", "; }
                }cout << endl;

                cout << "左から何人目の名前を変更しますか？(終了する場合は0を入力)　＞　" << flush;
                cin >> num;
                if (num == 0) {
                    conti = false;
                    system("cls");
                }
                else if (MIN_PAR_NUM <= num && num <= MAX_PAR_NUM) {
                    char name[100] = { '0' };
                    cout << "名前を入力　＞　" << flush;
                    cin >> name;
                    char* pName = new char[strlen(name) + 1];
                    for (int i = 0; i < (strlen(name) + 1); ++i) {
                        pName[i] = name[i];
                    }
                    p[num - 1].set_pName(pName);
                    if (pName != nullptr) {
                        delete[] pName;
                        pName = nullptr;
                    }
                    if (!p[num - 1].get_playerOrNot()) {
                        p[num - 1].change_playerOrNot();
                        ++nNPCNum;
                    }
                    system("cls");
                }
            } while (conti);
        }
        else if (select == 2) {
            int pNum = 0;
            for (int i = 0; i < MAX_PAR_NUM; ++i) {
                if (p[i].get_playerOrNot()) ++pNum;
            }
            if (pNum > 0) {
                bool conti = true;
                do {
                    int num;

                    cout << "以下がゲームに参加予定の５人です" << endl;
                    for (int i = 0; i < MAX_PAR_NUM; ++i) {
                        cout << p[i].get_pName();
                        if (i < MAX_PAR_NUM - 1) { cout << ", "; }
                    }cout << endl;
                    cout << "左から何人目の名前を削除しますか？(終了する場合は0を入力)　＞　" << flush;
                    cin >> num;
                    if (num == 0) {
                        conti = false;
                        system("cls");
                    }
                    else if (MIN_PAR_NUM <= num && num <= MAX_PAR_NUM) {
                        if (p[num - 1].get_playerOrNot()) {
                            p[num - 1].set_pName(NPCNAME[num - 1]);
                            p[num - 1].change_playerOrNot();
                            --nNPCNum;
                            system("cls");
                        }
                        else {
                            cout << endl << "その人はNPCです" << endl << endl;
                        }
                    }
                } while (conti);
            }
            else {
                cout << "現在、全員NPCです" << endl << endl;
            }
        }
        else if (select == 3) {
            return;
        }
    } while (true);
}

void Baccarat(Shoe* shoe, Player* p) {
    shoe->set_shoe(BC_DECK_NUM);
    bool conti = true;
    do {
        system("cls");

        int prediction;
        do {
            cout << "「どちらが勝つ」または「引き分け」かを予想してください" << endl;
            printf("1:%s, 2:%s, 3:引き分け　　あなたの予想　＞　", p[0].get_pName(), p[1].get_pName());
            cin >> prediction;
        } while (prediction < 1 || 3 < prediction);

        //p[0]がバンカー,p[1]がプレイヤー扱い

        for (int i = 0; i < 2; ++i) {
            p[1].takeCard(shoe);
            p[0].takeCard(shoe);
        }

        //ゲーム開始
        //ナチュラル(終了)
        if ((p[0].BCcalcScore() == 8 || p[0].BCcalcScore() == 9) ||
            (p[1].BCcalcScore() == 8 || p[1].BCcalcScore() == 9)){
        }
        //終了
        else if ((p[0].BCcalcScore() == 6 || p[0].BCcalcScore() == 7) &&
                 (p[1].BCcalcScore() == 6 || p[1].BCcalcScore() == 7)) {
        }
        else {
            //プレイヤー５以下
            if (p[1].BCcalcScore() <= 5) {
                p[1].takeCard(shoe);
            }
            //プレイヤーが３枚目を引いていない
            if (p[1].get_handNum() == 2) {
                if (0 <= p[0].BCcalcScore() || p[0].BCcalcScore() <= 5) {
                    p[0].takeCard(shoe);
                }
            }
            //プレイヤーが３枚目を引いてる
            else {
                switch (p[1].get_pHand(3)->get_number())
                {
                case 0: 
                    if (p[0].BCcalcScore() <= 3) p[0].takeCard(shoe);
                    break;
                case 1: 
                    if (p[0].BCcalcScore() <= 3) p[0].takeCard(shoe);
                    break;
                case 2: 
                    if (p[0].BCcalcScore() <= 4) p[0].takeCard(shoe);
                    break;
                case 3: 
                    if (p[0].BCcalcScore() <= 4) p[0].takeCard(shoe);
                    break;
                case 4: 
                    if (p[0].BCcalcScore() <= 5) p[0].takeCard(shoe);
                    break;
                case 5: 
                    if (p[0].BCcalcScore() <= 5) p[0].takeCard(shoe);
                    break;
                case 6: 
                    if (p[0].BCcalcScore() <= 6) p[0].takeCard(shoe);
                    break;
                case 7: 
                    if (p[0].BCcalcScore() <= 6) p[0].takeCard(shoe);
                    break;
                case 8: 
                    if (p[0].BCcalcScore() <= 2) p[0].takeCard(shoe);
                    break;
                case 9: 
                    if (p[0].BCcalcScore() <= 3) p[0].takeCard(shoe);
                    break;
                }
            }
        }

        //手札表示
        cout << "======================" << endl;
        cout << "        result          " << endl;
        cout << "======================" << endl;

        cout << "======================" << endl;
        cout << p[0].get_pName() << endl;
        for (int i = 0; i < p[0].get_handNum(); ++i) {
            p[0].get_pHand(i + 1)->Show();
        }cout << endl;
        cout << "得点:" << p[0].BCcalcScore() << endl;
        cout << "======================" << endl;

        cout << "======================" << endl;
        cout << p[1].get_pName() << endl;
        for (int i = 0; i < p[1].get_handNum(); ++i) {
            p[1].get_pHand(i + 1)->Show();
        }cout << endl;
        cout << "得点:" << p[1].BCcalcScore() << endl;
        cout << "======================" << endl;

        //勝敗判定
        if (p[0].BCcalcScore() == p[1].BCcalcScore()) {
            cout << "引き分けです" << endl;
            if (prediction == 3) {
                cout << "予想が的中しました" << endl;
            }
            else {
                cout << "予想が外れました" << endl;
            }
        }
        else if (p[0].BCcalcScore() > p[1].BCcalcScore()) {
            cout << p[0].get_pName() << " の勝ちです" << endl;
            if (prediction == 1) {
                cout << "予想が的中しました" << endl;
            }
            else {
                cout << "予想が外れました" << endl;
            }
        }
        else {
            cout << p[1].get_pName() << " の勝ちです" << endl;
            if (prediction == 2) {
                cout << "予想が的中しました" << endl;
            }
            else {
                cout << "予想が外れました" << endl;
            }
        }

        //リセット
        p[0].reset_pHand();
        p[1].reset_pHand();
        shoe->set_shoe(BC_DECK_NUM);

        //再戦確認
        int select;
        cout << endl << "再戦しますか？" << endl;
        cout << "1:再戦, 2:ゲーム選択画面へ　＞　" << flush;
        cin >> select;
        if (select == 1) {
            
        }
        else if (select == 2) {
            conti = false;
            system("cls");
            cout << "バカラを終了しました" << endl;
        }
    } while (conti);
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
