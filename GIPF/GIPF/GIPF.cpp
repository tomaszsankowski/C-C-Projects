#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

void writeBoard(int S, int K, int GW, int GB, char** board, int freeWhite, int freeBlack, char currentRound) {
    const int ILOSC_LITEREK = 2 * S - 1;
    //tworzenie planszy tablicy na ktorej wypiszemy plansze
    int kolumny_wypisanie = 4 * S - 3;
    int wiersze_wypisanie = ILOSC_LITEREK;
    char** tablica = new char* [wiersze_wypisanie];
    for (int i = 0; i < wiersze_wypisanie; i++) {
        tablica[i] = new char[kolumny_wypisanie];
        for (int j = 0; j < kolumny_wypisanie; j++)
            tablica[i][j] = ' ';

    }


    //przypisanie elemntow planszy do tablicy
    //ustawiamy najpierwsz wszystkie a potem b potem c itd.
    for (int i = 0; i < ILOSC_LITEREK; i++) {
        int x_value;
        if (i < S)
            x_value = i;
        else
            x_value = S - 1 + 2 * (i - S + 1);
        int y_value;
        if ((S - 1 + i) < wiersze_wypisanie)
            y_value = (S - 1 + i);
        else
            y_value = wiersze_wypisanie - 1;
        int length = ILOSC_LITEREK - abs(i + 1 - S);//max index in "column"
        for (int j = 0; j < length; j++) {
            tablica[y_value--][x_value++] = board[i + 1][j + 1];

        }

    }


    //wypisanie planszy
    cout << S << " " << K << " " << GW << " " << GB << endl;
    cout << freeWhite << " " << freeBlack << " " << currentRound << endl;
    for (int i = 0; i < wiersze_wypisanie; i++) {
        for (int j = 0; j < kolumny_wypisanie; j++)
            cout << tablica[i][j];
        cout << endl;

    }


    for (int i = 0; i < wiersze_wypisanie; i++)
        delete[] tablica[i];
    delete[] tablica;
    return;
}

bool domove(int a, int b, int c, int d, int S, char** board, char currentRound) {
    if (board[c][d] == '_') {
        board[c][d] = board[a][b];
        return true;

    }
    else if (board[c][d] == '+')
        return false;
    else {
        int dx = c - a;
        int dy = d - b;
        if (dx != 0 && c == S) {
            if (dy == 0)
                dy = -1;
            else
                dy = 0;
            if (domove(c, d, c + dx, d + dy, S, board, currentRound)) {
                board[c][d] = board[a][b];
                board[a][b] = '_';
                return true;

            }
            else
                return false;

        }
        else {
            if (domove(c, d, c + dx, d + dy, S, board, currentRound)) {
                board[c][d] = board[a][b];
                board[a][b] = '_';
                return true;

            }
            else
                return false;

        }

    }
}

bool move(int S, char** board, char currentRound) {
    // move from (a,b) to (c,d)
    int a, b, c, d;//odpowiednie indeksy tablicy
    char chara, charc;
    string movement;
    cin >> movement;
    a = movement[0] - 'a';
    chara = movement[0];
    size_t dashIndex = movement.find('-');
    string number1Str = movement.substr(1, dashIndex - 1);
    b = stoi(number1Str) - 1;
    c = movement[dashIndex + 1] - 'a';
    charc = movement[dashIndex + 1];
    string number2Str = movement.substr(dashIndex + 2);
    d = stoi(number2Str) - 1;
    const int ILOSC_LITEREK = 2 * (S + 1) - 1;
    if (a<0 || a>ILOSC_LITEREK - 1 || b < 0 || b>(ILOSC_LITEREK - abs(S - a) - 1)) {
        cout << "BAD_MOVE_" << chara << b + 1 << "_IS_WRONG_INDEX" << endl << endl;
        return false;

    }
    if (c<0 || c>ILOSC_LITEREK - 1 || d < 0 || d>(ILOSC_LITEREK - abs(S - c) - 1)) {
        cout << "BAD_MOVE_" << charc << d + 1 << "_IS_WRONG_INDEX" << endl << endl;
        return false;

    }
    if ((a != 0 && a != ILOSC_LITEREK - 1) && (b != 0 && b != (ILOSC_LITEREK - abs(S - a) - 1))) {
        cout << "BAD_MOVE_" << chara << b + 1 << "_IS_WRONG_STARTING_FIELD" << endl << endl;
        return false;

    }
    if (c == 0 || c == ILOSC_LITEREK - 1 || d == 0 || d == (ILOSC_LITEREK - abs(S - c) - 1)) {
        cout << "BAD_MOVE_" << charc << d + 1 << "_IS_WRONG_DESTINATION_FIELD" << endl << endl;
        return false;

    }
    //sprawdzamy kierunek ruchu
    bool isMoveGood = false;
    if ((a == 0) && (c == 1 && (d == b || d == b + 1)))//rzad a
        isMoveGood = true;
    else if ((a == ILOSC_LITEREK - 1) && (c == ILOSC_LITEREK - 2 && (d == b || d == b + 1)))//rzad ostatni
        isMoveGood = true;
    else if ((a == S) && (c == S) && ((b == 0 && d == 1) || (b == 2 * S && d == 2 * S - 1)))
        isMoveGood = true;
    else if (a < S) {//z lewej od srodka
        if (b == 0) {//na dole
            if ((a == c && b == d - 1) || (a == c - 1 && b == d - 1))
                isMoveGood = true;

        }
        if (b == S + a) {//na gorze
            if ((a == c && b == d + 1) || (a == c - 1 && b == d))
                isMoveGood = true;

        }

    }
    else if (a > S) {//z prawej od srodka
        if (b == 0) {//na dole
            if ((a == c && b == d - 1) || (a == c + 1 && b == d - 1))
                isMoveGood = true;

        }
        if (b == a - 1) {//na gorze
            if ((a == c && b == d + 1) || (a == c + 1 && b == d))
                isMoveGood = true;

        }

    }
    board[a][b] = currentRound;
    if (!isMoveGood) {
        cout << "UNKNOWN_MOVE_DIRECTION" << endl << endl;

    }
    else {
        if (domove(a, b, c, d, S, board, currentRound)) {
            board[a][b] = '+';
            return true;

        }
        else {
            cout << "BAD_MOVE_ROW_IS_FULL " << endl;

        }

    }
    board[a][b] = '+';
    return false;
}

int areThereRows(char** board, int S, int K) {
    char currentSearch = 'W';
    int counterOfRows = 0;
    int counterOfPawns = 0;
    const int ILOSC_LITEREK = 2 * (S + 1) - 1;
    for (int i = 1; i < 2 * S; i++) {//1. kierunek
        counterOfPawns = 0;
        int length = ILOSC_LITEREK - abs(S - i);//max index in "column"
        for (int j = 1; j < length - 1; j++) {
            if (board[i][j] == '_')
                counterOfPawns = 0;
            else if (board[i][j] == currentSearch)
                counterOfPawns++;
            else {
                if (currentSearch == 'W')
                    currentSearch = 'B';
                else
                    currentSearch = 'W';
                counterOfPawns = 1;

            }
            if (counterOfPawns == K) {
                counterOfRows++;
                counterOfPawns = 0;

            }

        }

    }
    int x, y;
    for (int i = 0; i < 2 * S - 1; i++) {//2. kierunek
        counterOfPawns = 0;
        if (i < S) {
            x = 1;
            y = S - i;

        }
        else {
            x = i - S + 2;
            y = 1;

        }
        int length = 2 * S - 1 - abs(S - i - 1);//max index in "column"
        while (length > 0) {
            length--;
            if (board[x][y] == '_')
                counterOfPawns = 0;
            else if (board[x][y] == currentSearch)
                counterOfPawns++;
            else {
                if (currentSearch == 'W')
                    currentSearch = 'B';
                else
                    currentSearch = 'W';
                counterOfPawns = 1;

            }
            if (counterOfPawns == K) {
                counterOfRows++;
                counterOfPawns = 0;

            }
            if (x < S)
                y++;
            x++;

        }

    }
    for (int i = 0; i < 2 * S - 1; i++) {//3. kierunek
        counterOfPawns = 0;
        if (i > S - 1) {
            x = 1;
            y = 2 * S - i - 1;

        }
        else {
            x = S - i;
            y = 2 * S - i - 1;

        }
        int length = 2 * S - abs(S - i);//max index in "column"
        while (length > 0) {
            length--;
            if (board[x][y] == '_')
                counterOfPawns = 0;
            else if (board[x][y] == currentSearch)
                counterOfPawns++;
            else {
                if (currentSearch == 'W')
                    currentSearch = 'B';
                else
                    currentSearch = 'W';
                counterOfPawns = 1;

            }
            if (counterOfPawns == K) {
                counterOfRows++;
                counterOfPawns = 0;

            }
            if (x >= S)
                y--;
            x++;

        }

    }

    return counterOfRows;
}

int notObviousMove(char** board, int K, int S, char wantedColor) {// zwraca numer kierunku ruchu lub -1 jak cos sie nie zgadza
    int a, b, c, d;
    string p1, p2;
    cin >> p1 >> p2;
    a = p1[0] - 'a';
    c = p2[0] - 'a';
    string n1 = p1.substr(1);
    string n2 = p2.substr(1);
    b = stoi(n1) - 1;
    d = stoi(n2) - 1;
    char current = 'W';
    if (a == c) {//1.kierunek
        if (abs(b - d) != K - 1) {
            cout << "WRONG_INDEX_OF_CHOSEN_ROW" << endl;
            return -1;

        }
        if (b > d) {
            current = board[a][b--];
            while (b > d) {
                if (board[a][b--] != current) {
                    cout << "WRONG_INDEX_OF_CHOSEN_ROW" << endl;
                    return -1;

                }

            }

        }
        else {//b>d
            current = board[a][d--];
            while (b > d) {
                if (board[a][d--] != current) {
                    cout << "WRONG_INDEX_OF_CHOSEN_ROW" << endl;
                    return -1;

                }

            }

        }
        if (current != wantedColor) {
            cout << "WRONG_COLOR_OF_CHOSEN_ROW" << endl;
            return -1;

        }
        return 1;

    }
    else if (((c > a) && (b <= d)) || ((a > c) && (d <= b))) {//2. kierunek
        if (c > a) {
            current = board[a][b];
            bool isSameColor = true;
            for (int i = 0; i < 4; i++) {
                if (board[a][b] != current)
                    isSameColor = false;
                if (i != 3) {
                    if (a < S)
                        b++;
                    a++;

                }

            }
            if (a != c || b != d || !isSameColor) {
                cout << "WRONG_INDEX_OF_CHOSEN_ROW" << endl;
                return -1;

            }
            if (current != wantedColor) {
                cout << "WRONG_COLOR_OF_CHOSEN_ROW" << endl;
                return -1;

            }
            return 2;

        }
        else {//a>c
            current = board[a][b];
            bool isSameColor = true;
            for (int i = 0; i < 4; i++) {
                if (board[a][b] != current)
                    isSameColor = false;
                if (i != 3) {
                    if (a < S)
                        b--;
                    a--;

                }

            }
            if (a != c || b != d || !isSameColor) {
                cout << "WRONG_INDEX_OF_CHOSEN_ROW" << endl;
                return -1;

            }
            if (current != wantedColor) {
                cout << "WRONG_COLOR_OF_CHOSEN_ROW" << endl;
                return -1;

            }
            return 2;

        }

    }
    else if (((c > a) && (b >= d)) || ((a > c) && (b <= d))) {//3. kierunek
        if (c > a) {
            current = board[a][b];
            bool isSameColor = true;
            for (int i = 0; i < 4; i++) {
                if (board[a][b] != current)
                    isSameColor = false;
                if (i != 3) {
                    if (a >= S)
                        b--;
                    a++;

                }

            }
            if (a != c || b != d || !isSameColor) {
                cout << "WRONG_INDEX_OF_CHOSEN_ROW" << endl;
                return -1;

            }
            if (current != wantedColor) {
                cout << "WRONG_COLOR_OF_CHOSEN_ROW" << endl;
                return -1;

            }
            return 3;

        }
        else {//a>c
            current = board[a][b];
            bool isSameColor = true;
            for (int i = 0; i < 4; i++) {
                if (board[a][b] != current)
                    isSameColor = false;
                if (i != 3) {
                    if (a >= S)
                        b++;
                    a--;

                }

            }
            if (a != c || b != d || !isSameColor) {
                cout << "WRONG_INDEX_OF_CHOSEN_ROW" << endl;
                return -1;

            }
            if (current != wantedColor) {
                cout << "WRONG_COLOR_OF_CHOSEN_ROW" << endl;
                return -1;

            }
            return 3;

        }

    }
    else {
        cout << "WRONG_INDEX_OF_CHOSEN_ROW" << endl;
        return -1;

    }
}

bool sprawdzBicia(int S, int K, char** board, int& freeWhite, int& freeBlack, bool isObvious, char player) {
    char currentSearch = 'W';
    char streakColor = 'W';
    int pawnsToDelete = 0;
    bool found = false;
    int counterOfPawns = 0;
    const int ILOSC_LITEREK = 2 * (S + 1) - 1;
    int direction = 0;
    if (!isObvious) {//najpierw usuwamy wskazany przez gracza rzad
        direction = notObviousMove(board, K, S, player);
        if (direction == -1)
            return false;

    }
    if (direction == 0 || direction == 1) {
        for (int i = 1; i < 2 * S; i++) {//1. kierunek (e1-e9)
            found = false;
            counterOfPawns = 0;
            pawnsToDelete = 0;
            int length = ILOSC_LITEREK - abs(S - i);
            for (int j = 1; j < length - 1; j++) {
                if (board[i][j] == '_') {
                    if (found) {
                        int tmp = j - 1;
                        while (pawnsToDelete > 0) {
                            if (board[i][tmp] == 'W') {
                                if (streakColor == 'W')
                                    freeWhite++;
                                board[i][tmp] = '_';

                            }
                            else {
                                if (streakColor == 'B')
                                    freeBlack++;
                                board[i][tmp] = '_';

                            }
                            tmp--;
                            pawnsToDelete--;

                        }
                        found = false;

                    }
                    pawnsToDelete = 0;
                    counterOfPawns = 0;

                }
                else if (board[i][j] == 'W') {
                    if (currentSearch == 'W')
                        counterOfPawns++;
                    else {
                        currentSearch = 'W';
                        counterOfPawns = 1;

                    }
                    pawnsToDelete++;

                }
                else if (board[i][j] == 'B') {
                    if (currentSearch == 'B')
                        counterOfPawns++;
                    else {
                        currentSearch = 'B';
                        counterOfPawns = 1;

                    }
                    pawnsToDelete++;

                }
                if (counterOfPawns == K) {
                    found = true;
                    streakColor = currentSearch;

                }

            }
            if (found) {
                int tmp = length - 2;
                while (pawnsToDelete > 0) {
                    if (board[i][tmp] == 'W') {
                        if (streakColor == 'W')
                            freeWhite++;
                        board[i][tmp] = '_';

                    }
                    else {
                        if (streakColor == 'B')
                            freeBlack++;
                        board[i][tmp] = '_';

                    }
                    tmp--;
                    pawnsToDelete--;

                }
                found = false;

            }

        }

    }
    int x, y;
    if (direction == 0 || direction == 2) {
        for (int i = 0; i < 2 * S - 1; i++) {//2. kierunek (a1-i5)
            found = false;
            counterOfPawns = 0;
            pawnsToDelete = 0;
            if (i < S) {
                x = 1;
                y = S - i;

            }
            else {
                x = i - S + 2;
                y = 1;

            }
            int length = 2 * S - 1 - abs(S - i - 1);
            int tmplength = length;
            while (tmplength > 0) {
                tmplength--;
                if (board[x][y] == '_') {
                    if (found) {
                        int tmpx = x;
                        int tmpy = y;
                        if (tmpx <= S)
                            tmpy--;
                        tmpx--;
                        while (pawnsToDelete > 0) {
                            if (board[tmpx][tmpy] == 'W') {
                                if (streakColor == 'W')
                                    freeWhite++;
                                board[tmpx][tmpy] = '_';

                            }
                            else {
                                if (streakColor == 'B')
                                    freeBlack++;
                                board[tmpx][tmpy] = '_';

                            }
                            if (tmpx <= S)
                                tmpy--;
                            tmpx--;
                            pawnsToDelete--;

                        }
                        found = false;

                    }
                    pawnsToDelete = 0;
                    counterOfPawns = 0;

                }
                else if (board[x][y] == 'W') {
                    if (currentSearch == 'W')
                        counterOfPawns++;
                    else {
                        currentSearch = 'W';
                        counterOfPawns = 1;

                    }
                    pawnsToDelete++;

                }
                else if (board[x][y] == 'B') {
                    if (currentSearch == 'B')
                        counterOfPawns++;
                    else {
                        currentSearch = 'B';
                        counterOfPawns = 1;

                    }
                    pawnsToDelete++;

                }
                if (counterOfPawns == K) {
                    found = true;
                    streakColor = currentSearch;

                }
                if (x < S)
                    y++;
                x++;

            }
            if (found) {
                if (x <= S)
                    y++;
                x++;
                while (pawnsToDelete > 0) {
                    if (board[x][y] == 'W') {
                        if (streakColor == 'W')
                            freeWhite++;
                        board[x][y] = '_';

                    }
                    else {
                        if (streakColor == 'B')
                            freeBlack++;
                        board[x][y] = '_';

                    }
                    if (x <= S)
                        y--;
                    x--;
                    pawnsToDelete--;

                }
                found = false;

            }

        }

    }
    if (direction == 0 || direction == 3) {
        for (int i = 0; i < 2 * S - 1; i++) {//3. kierunek (a5-i1)
            found = false;
            counterOfPawns = 0;
            pawnsToDelete = 0;
            if (i > S - 1) {
                x = 1;
                y = 2 * S - i - 1;

            }
            else {
                x = S - i;
                y = 2 * S - i - 1;

            }
            int length = 2 * S - abs(S - i);
            int tmplength = length;
            while (tmplength > 0) {
                tmplength--;
                if (board[x][y] == '_') {
                    if (found) {
                        int tmpx = x;
                        int tmpy = y;
                        if (tmpx > S)
                            tmpy++;
                        tmpx--;
                        while (pawnsToDelete > 0) {
                            if (board[tmpx][tmpy] == 'W') {
                                if (streakColor == 'W')
                                    freeWhite++;
                                board[tmpx][tmpy] = '_';

                            }
                            else {
                                if (streakColor == 'B')
                                    freeBlack++;
                                board[tmpx][tmpy] = '_';

                            }
                            if (tmpx > S)
                                tmpy++;
                            tmpx--;
                            pawnsToDelete--;

                        }
                        found = false;

                    }
                    pawnsToDelete = 0;
                    counterOfPawns = 0;

                }
                else if (board[x][y] == 'W') {
                    if (currentSearch == 'W')
                        counterOfPawns++;
                    else {
                        currentSearch = 'W';
                        counterOfPawns = 1;

                    }
                    pawnsToDelete++;

                }
                else if (board[x][y] == 'B') {
                    if (currentSearch == 'B')
                        counterOfPawns++;
                    else {
                        currentSearch = 'B';
                        counterOfPawns = 1;

                    }
                    pawnsToDelete++;

                }
                if (counterOfPawns == K) {
                    found = true;
                    streakColor = currentSearch;

                }
                if (x >= S)
                    y--;
                x++;

            }
            if (found) {
                if (x > S)
                    y++;
                x--;
                while (pawnsToDelete > 0) {
                    if (board[x][y] == 'W') {
                        if (streakColor == 'W')
                            freeWhite++;
                        board[x][y] = '_';

                    }
                    else {
                        if (streakColor == 'B')
                            freeBlack++;
                        board[x][y] = '_';

                    }
                    if (x > S)
                        y++;
                    x--;
                    pawnsToDelete--;

                }
                found = false;

            }

        }

    }
    return true;
}

bool readBoard() {

    //start
    int S, K, GW, GB;
    int freeBlack, freeWhite;
    char currentRound;
    cin >> S >> K >> GW >> GB >> freeWhite >> freeBlack >> currentRound;
    const int ILOSC_LITEREK = 2 * (S + 1) - 1;
    int blackCounter = GB;
    int whiteCounter = GW;

    //buffor na plansze i wczytywanie do buffora
    int height = ILOSC_LITEREK - 2;
    char** buffer = new char* [height];
    for (int i = 0; i < height; i++) {
        int length = height - abs(S - i - 1);
        buffer[i] = new char[length];
        for (int j = 0; j < length; j++)
            buffer[i][j] = '_';

    }
    for (int i = 0; i < height; i++) {//wczytywanie kolejnych wierszy
        int iloscWczytanychZnakow = 0;
        int space = height - abs(S - i - 1);//ilosc znakow jakie chcemy wczytac
        while (char c = getchar()) {
            if (c == ' ')
                continue;
            else if (c == 'B') {
                buffer[i][iloscWczytanychZnakow] = c;
                iloscWczytanychZnakow++;
                blackCounter--;

            }
            else if (c == 'W') {
                buffer[i][iloscWczytanychZnakow] = c;
                iloscWczytanychZnakow++;
                whiteCounter--;

            }
            else if (c == '_') {
                buffer[i][iloscWczytanychZnakow] = c;
                iloscWczytanychZnakow++;

            }
            else if (c == '\n') {
                if (iloscWczytanychZnakow != space && iloscWczytanychZnakow != 0) {
                    cout << "WRONG_BOARD_ROW_LENGTH" << endl << endl;
                    for (int j = 0; j < height; j++)
                        delete[] buffer[j];
                    delete[] buffer;
                    return false;

                }
                else if (iloscWczytanychZnakow != 0)
                    break;

            }

        }

    }

    if (blackCounter < freeBlack) {
        cout << "WRONG_BLACK_PAWNS_NUMBER " << endl << endl;
        for (int i = 0; i < height; i++)
            delete[] buffer[i];
        delete[] buffer;
        return false;

    }
    if (whiteCounter < freeWhite) {
        cout << "WRONG_WHITE_PAWNS_NUMBER " << endl << endl;
        for (int i = 0; i < height; i++)
            delete[] buffer[i];
        delete[] buffer;
        return false;

    }
    //tworzenie planszy oraz przepisywanie z buffora do planszy
    int* przesuniecieBuffor = new int[height];
    for (int i = 0; i < height; i++)
        przesuniecieBuffor[i] = 0;
    char** board = new char* [ILOSC_LITEREK];
    for (int i = 0; i < ILOSC_LITEREK; i++) {
        int length = ILOSC_LITEREK - abs(S - i);//max index in "column"
        board[i] = new char[length];
        for (int j = 0; j < length; j++) {
            if (i == 0 || i == ILOSC_LITEREK - 1)
                board[i][j] = '+';
            else if (j == 0 || j == length - 1)
                board[i][j] = '+';
            else
                board[i][j] = '_';

        }

    }

    for (int i = 1; i < ILOSC_LITEREK - 1; i++) {
        int posx;
        if (i <= S)
            posx = S - 2 + i;
        else
            posx = 2 * S - 2;
        int length = ILOSC_LITEREK - abs(S - i);//max index in "column"
        for (int j = 1; j < length - 1; j++) {
            board[i][j] = buffer[posx][przesuniecieBuffor[posx]];
            przesuniecieBuffor[posx]++;
            posx--;

        }

    }

    int kLengthRows = areThereRows(board, S, K);
    if (kLengthRows == 0)
        cout << "BOARD_STATE_OK" << endl << endl;
    else {
        if (kLengthRows == 1)
            cout << "ERROR_FOUND_1_ROW_OF_LENGTH_K" << endl;
        else
            cout << "ERROR_FOUND_" << kLengthRows << "_ROWS_OF_LENGTH_K" << endl;
        for (int i = 0; i < ILOSC_LITEREK; i++)
            delete[] board[i];
        for (int i = 0; i < height; i++)
            delete[] buffer[i];
        delete[] przesuniecieBuffor;
        delete[] buffer;
        delete[] board;
        return false;

    }

    string command;
    bool isCommandSet = false;
    while (true) {
        if (!isCommandSet) {
            if (!(cin >> command))
                break;

        }
        isCommandSet = false;
        if (command == "PRINT_GAME_BOARD")
            writeBoard(S, K, GW, GB, board, freeWhite, freeBlack, currentRound);
        else if (command == "LOAD_GAME_BOARD") {
            for (int i = 0; i < ILOSC_LITEREK; i++)
                delete[] board[i];
            for (int i = 0; i < height; i++)
                delete[] buffer[i];
            delete[] przesuniecieBuffor;
            delete[] buffer;
            delete[] board;
            return true;

        }
        else if (command == "DO_MOVE") {
            if (move(S, board, currentRound)) {
                if (!(cin >> command))
                    break;
                char player = 'W';
                if (command == "w:" || command == "b:") {
                    if (command == "b:")
                        player = 'B';
                    if (sprawdzBicia(S, K, board, freeWhite, freeBlack, false, player)) {
                        cout << "MOVE_COMMITTED" << endl;
                        if (currentRound == 'W') {
                            currentRound = 'B';
                            freeWhite--;

                        }
                        else {
                            currentRound = 'W';
                            freeBlack--;

                        }

                    }

                }
                else {
                    sprawdzBicia(S, K, board, freeWhite, freeBlack, true, player);
                    isCommandSet = true;
                    cout << "MOVE_COMMITTED" << endl;
                    if (currentRound == 'W') {
                        currentRound = 'B';
                        freeWhite--;

                    }
                    else {
                        currentRound = 'W';
                        freeBlack--;

                    }

                }

            }

        }

    }
    //zwolnienie pamieci
    for (int i = 0; i < ILOSC_LITEREK; i++)
        delete[] board[i];
    for (int i = 0; i < height; i++)
        delete[] buffer[i];
    delete[] przesuniecieBuffor;
    delete[] buffer;
    delete[] board;
    return false;
}

int main() {

    string command;
    while (cin >> command) {
        if (command == "LOAD_GAME_BOARD")
            while (readBoard());
        if (command == "PRINT_GAME_BOARD")
            cout << "EMPTY_BOARD" << endl;

    }

    return 0;
}