
#include <iostream>

unsigned int game = 0b00000000000000000000000000000000;

unsigned int mask2 = 0b11;


void DisplayGrid();
unsigned int GetBit(unsigned int i, int decal, int mask = 1);
void SetBit(unsigned int* i, unsigned int value, int pos, int mask);
void PlaceSign();
void GameLoop();
void WinCondition();

int main()
{
    GameLoop();
}

void GameLoop() {

    while (true) {

        DisplayGrid();
        PlaceSign();
        


    }
}

void DisplayGrid() {

    unsigned int placeSign = 0;
    int currentSign = 0;

    for (int i = 0; i < 9; i++) {

        if (i % 3 == 0) {
            std::cout << std::endl;
        }

        char sign = ' ';

        currentSign = GetBit(game, placeSign, 2);

        switch (currentSign) {
        case 0:
            sign = '.';
            break;
        case 1:
            sign = 'o';
            break;
        case 2:
            sign = 'x';
            break;
        }

        std::cout << sign;
        std::cout << " " ;

        placeSign++;
        placeSign++;

    }
    std::cout << std::endl;
}

void PlaceSign() {

    int turn = GetBit(game, 21);
    int value = 0;
    char sign = ' ';

    switch (turn) {
    case 0:

        sign = 'X';
        value = 1;
        break;
    case 1:

        sign = '0';
        value = 2;
        break;
    }

    int p = 0;

    do {
        std::cout << "Au joueur " << sign << ": ";
        std::cin >> p;
    } while (p - 48 > 0 && p - 48 < 10 && GetBit(game, p * 2, 2));

    SetBit(&game, value ,p * 2, 2);
    SetBit(&game, ~GetBit(game, 21, 1), 21, 1);

}

void WinCondition() {



}

unsigned int GetBit(unsigned int i, int decal, int mask) {

    int maskCounter = 1 ;

    for (int i = 0; i < mask; i++) {
        maskCounter <<= 1;
        maskCounter |= 1;
    }

    maskCounter >>= 1;

    unsigned int trueMask = maskCounter << decal;
    unsigned int oue = i & trueMask;
    return oue >> decal;

}

void SetBit(unsigned int* i, unsigned int value ,int pos,int mask) {
    
    int maskCounter = 1;
    unsigned int valueInt = *i;

    for (int i = 0; i < mask; i++) {
        maskCounter <<= 1;
        maskCounter |= 1;
    }

    maskCounter >>= 1;

    int erase = valueInt & ~(mask << pos);

    int finalInt = erase | (value << pos);

    *i = finalInt;

}
