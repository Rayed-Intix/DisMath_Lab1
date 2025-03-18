#include "Menu.h"
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

struct Node {
    char Char;
    int Freq;
    Node* Left;
    Node* Right;

    Node(char _C, int _F) 
        : Char(_C), Freq(_F), Left(nullptr), Right(nullptr) {};

    Node(char _C, int _F, Node* _L, Node* _R) 
        : Char(_C), Freq(_F), Left(_L), Right(_R) {};
};

struct Node4Char {
    char Char;
    int Freq;
    Node4Char* First;
    Node4Char* Second;
    Node4Char* Third;
    Node4Char* Fourth;

    Node4Char(char _C, int _F) 
        :   Char(_C), 
            Freq(_F), 
            First(nullptr), 
            Second(nullptr), 
            Third(nullptr), 
            Fourth(nullptr) {};

    Node4Char(char _C, int _F, Node4Char* _1st, Node4Char* _2nd, Node4Char* _3rd, Node4Char* _4th)
        :   Char(_C), 
            Freq(_F), 
            First(_1st), 
            Second(_2nd), 
            Third(_3rd), 
            Fourth(_4th) {};
};

bool Comp(Node* _L, Node* _R) {
    return _L->Freq < _R->Freq;
}

bool Comp4Char(Node4Char* _L, Node4Char* _R) {
    return _L->Freq < _R->Freq;
}

void CreateHuffmanTable2Char(Node* _Current, string _Code, char _ToAdd) {
    if (!_Current) {
        return;
    }
    _Code += _ToAdd;

    if (_Current->Char == '-') {
        CreateHuffmanTable2Char(_Current->Left, _Code, '0');
        CreateHuffmanTable2Char(_Current->Right, _Code, '1');
    }
    else {
        cout << _Current->Char << "\t" << _Code << endl;
    }
}

void CreateHuffmanTable4Char(Node4Char* _Current, string _Code, char _ToAdd) {
    if (!_Current) {
        return;
    }

    _Code += _ToAdd;

    if (_Current->Char == '-') {
        CreateHuffmanTable4Char(_Current->First, _Code, '0');
        CreateHuffmanTable4Char(_Current->Second, _Code, '1');
        CreateHuffmanTable4Char(_Current->Third, _Code, '2');
        CreateHuffmanTable4Char(_Current->Fourth, _Code, '3');
    }
    else {
        cout << _Current->Char << "\t" << _Code << endl;
    }
}

void Task1() {
    string Line = "БЫТЬ ЭНТУЗИАСТКОЙ СДЕЛАЛОСЬ ЕЕ ОБЩЕСТВЕННЫМ ПОЛОЖЕНИЕМ И ИНОГДА КОГДА "
                  "ЕЙ ДАЖЕ ТОГО НЕ ХОТЕЛОСЬ ОНА ЧТОБЫ НЕ ОБМАНУТЬ ОЖИДАНИЙ ЛЮДЕЙ ЗНАВШИХ ЕЕ "
                  "ДЕЛАЛАСЬ ЭНТУЗИАСТКОЙ СДЕРЖАННАЯ УЛЫБКА ИГРАВШАЯ ПОСТОЯННО НА ЛИЦЕ АННЫ "
                  "ПАВЛОВНЫ ХОТЯ И НЕ ШЛА К ЕЕ ОТЖИВШИМ ЧЕРТАМ ВЫРАЖАЛА КАК У ИЗБАЛОВАННЫХ ДЕТЕЙ "
                  "ПОСТОЯННОЕ СОЗНАНИЕ СВОЕГО МИЛОГО НЕДОСТАТКА ОТ КОТОРОГО ОНА НЕ ХОЧЕТ НЕ МОЖЕТ "
                  "И НЕ НАХОДИТ НУЖНЫМ ИСПРАВЛЯТЬСЯ В СЕРЕДИНЕ РАЗГОВОРА ПРО ПОЛИТИЧЕСКИЕ "
                  "ДЕЙСТВИЯ АННА ПАВЛОВНА РАЗГОРЯЧИЛАСЬ АХ НЕ ГОВОРИТЕ МНЕ ПРО АВСТРИЮ Я НИЧЕГО НЕ "
                  "ПОНИМАЮ МОЖЕТ БЫТЬ НО АВСТРИЯ НИКОГДА НЕ ХОТЕЛА И НЕ ХОЧЕТ ВОЙНЫ ОНА ПРЕДАЕТ "
                  "НАС РОССИЯ ОДНА ДОЛЖНА БЫТЬ СПАСИТЕЛЬНИЦЕЙ ЕВРОПЫ";

    string Alphabet = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ ";
    map<char, int> AmountChars;
    list<Node*> ListTree;
    list<Node4Char*> ListTree4Char;

    for (auto t : Alphabet) {
        AmountChars[t] = 0;
    }

    for (auto t : Line) {
        AmountChars[t] += 1;
    }

    for (auto it = AmountChars.begin(); it != AmountChars.end(); it++) {
        //cout << (*it).first << '\t' << (*it).second << '\n';
        Node* TempNode = new Node((*it).first, (*it).second);
        Node4Char* TempNode4Char = new Node4Char((*it).first, (*it).second);

        ListTree.push_back(TempNode);
        ListTree4Char.push_back(TempNode4Char);
    }

    ListTree.sort(Comp);
    ListTree4Char.sort(Comp4Char);

    for (auto it = ListTree.begin(); it != ListTree.end(); it++) {
        cout << (*it)->Char << ';' << (*it)->Freq << endl;
    }

    cout << "\n\n\n";

    while (ListTree.size() != 1) {
        Node* TempNode = new Node( '-',
                                   (*(ListTree.begin()))->Freq + (*next(ListTree.begin()))->Freq,
                                   (*(ListTree.begin())), 
                                   (*next(ListTree.begin())));
        ListTree.pop_front();
        ListTree.pop_front();
        ListTree.push_front(TempNode);
        ListTree.sort(Comp);
    }

    Node4Char* FirstTemp = new Node4Char('-', 
                                            (*(ListTree4Char.begin()))->Freq + (*next(ListTree4Char.begin()))->Freq + (*next(next(ListTree4Char.begin())))->Freq,
                                            *ListTree4Char.begin(), 
                                            *next(ListTree4Char.begin()),
                                            *next(next(ListTree4Char.begin())),
                                            nullptr);
    ListTree4Char.pop_front();
    ListTree4Char.pop_front();
    ListTree4Char.pop_front();
    ListTree4Char.push_front(FirstTemp);

    ListTree4Char.sort(Comp4Char);

    while (ListTree4Char.size() != 1) {
        Node4Char* TempN = new Node4Char('-',
            (*(ListTree4Char.begin()))->Freq + (*next(ListTree4Char.begin()))->Freq + (*next(next(ListTree4Char.begin())))->Freq + (*next(next(next(ListTree4Char.begin()))))->Freq,
            *ListTree4Char.begin(),
            *next(ListTree4Char.begin()),
            *next(next(ListTree4Char.begin())),
            *next(next(next(ListTree4Char.begin()))));

        //for (auto it = ListTree4Char.begin(); it != ListTree4Char.end(); it++) {
        //    cout << (*it)->Char << '\t' << (*it)->Freq << endl;
        //}
        //cout << "\n\n\n";

        ListTree4Char.pop_front();
        ListTree4Char.pop_front();
        ListTree4Char.pop_front();
        ListTree4Char.pop_front();
        ListTree4Char.push_front(TempN);

        ListTree4Char.sort(Comp4Char);
    }

    CreateHuffmanTable2Char(*ListTree.begin(), "", '\0');

    

    cout << "\n\n\n";

    cout << (*ListTree4Char.begin())->Freq << '\n';
    cout << (*ListTree.begin())->Freq << '\n';

    CreateHuffmanTable4Char(*ListTree4Char.begin(), "", '\0');
}

void Shuffle(string &_Str, vector<int> _Key) {
    string StrSource = _Str;

    for (int i = 0; i < _Str.size(); i++)
    {
        _Str[_Key[i] - 1] = StrSource[i];
    }
}

void Task2() {
    string Line = "аьнаТм-мас  йвксы р йыеноидогркзи шов хе срромпикг хсирводооРисс о.т Яи мтуча -ьтуьчнму  ерг се л,адоодще  а од ева кобвех ямнт илоеттипуо.п Яь илахренеп  аедалркоет нйе еклжоондпзнюьч о ищм.Я атскоо линвсулаут йорютув ук ре тооивтсднногоенкнем аод онгмч ,оаоирпт вдзе ъ.   е ";
    vector<string> Vec;
    vector<string> VecBase;

    const string KeyData = "123456";
    
    for (int i = 0; i < Line.size(); i) {
        string Temp = Line.substr(0, 6);
        Vec.push_back(Temp);
        Line = Line.substr(6);
    }

    for (auto it : Vec) {
        cout << it << '\n';
    }

    VecBase = Vec;
    vector<int> arr = { 1, 2, 3, 4, 5, 6 };
    sort(arr.begin(), arr.end());

    do {
        if (arr[4] == 1)
        {
            cout << "Key : \n" << arr[0] << arr[1] << arr[2] << arr[3] << arr[4] << arr[5] << "\nText : \n";
            for (auto it : Vec)
            {
               Shuffle(it, arr);
               cout << it;
            }
            cout << "\n--------\n";
        }
        Vec = VecBase;
    } while (next_permutation(arr.begin(), arr.end()));
}

int main() {
    setlocale(LC_ALL, "Russian");

    Menu Menu({{"Задание 1", Task1}, {"Задание 2", Task2}});

    Menu.StartUp();

    return 0;
}
