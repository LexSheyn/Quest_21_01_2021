#pragma once
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std;

void clearscreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    // Get the number of cells in the current buffer
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire buffer with spaces
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    // Fill the entire buffer with the current colors and attributes
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    // Move the cursor home
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

void write(string text, int ms)
{
    string a = text;
    int time = ms;

    for (int i = 0; i < a.length(); i++)
    {
        Sleep(time);

        cout << a[i];
    }
}

void writedel(string text, int speed, int delay)
{
    string t = text;
    int time = speed;       // Milliseconds
    int del = delay;        // Milliseconds
    int len = t.length();

    for (int i = 0; i < t.length(); i++)
    {
        Sleep(time);

        cout << t[i];
    }

    Sleep(del);

    cout << string(t.length(), '\b');

    for (int i = 0; i < t.length(); i++)
    {
        for (int i = 0; i < len; i++)
        {
            //Sleep(time);

            cout << t[i];
        }
        Sleep(15);
        cout << string(len, '\b');
        cout << string(len, ' ');
        cout << string(len, '\b');
        len--;
    }
}

void outdel(string text, int speed)
{
    string t = text;
    int time = speed;       // Milliseconds
    //int del = delay;        // Milliseconds
    int len = t.length();

    for (int i = 0; i < t.length(); i++)
    {
        //Sleep(time);

        cout << t[i];
    }

    //Sleep(del);

    cout << string(t.length(), '\b');

    for (int i = 0; i < t.length(); i++)
    {
        for (int i = 0; i < len; i++)
        {
            //Sleep(time);

            cout << t[i];
        }
        Sleep(15);
        cout << string(len, '\b');
        cout << string(len, ' ');
        cout << string(len, '\b');
        len--;
    }
}

//void writedel2(string text, int speed, int delay)
void writedel2(string text, int speed)
{
    string t = text;
    int time = speed;       // Milliseconds
    //int del = delay;        // Milliseconds
    int len = t.length();

    for (int i = 0; i < t.length(); i++)
    {
        //Sleep(time);

        cout << t[i];
    }

    //Sleep(del);

    cout << string(t.length(), '\b');

    for (int i = 0; i < t.length(); i++)
    {
        for (int i = 0; i < len; i++)
        {
            //Sleep(time);

            cout << t[i];
        }
        Sleep(time);
        //cout << string(len, '\b');
        //cout << string(len, ' ');
        //cout << string(len, '\b');
        clearscreen();
        cout << "\n\n    ";
        len--;
    }
}

void writedel3(string text, int speed, int delay)
{
    string t = text;
    int time = speed;       // Milliseconds
    int del = delay;        // Milliseconds
    int len = t.length();
 
    for (int i = 0; i < t.length(); i++)
    {
        Sleep(time);

        cout << t[i];
    }

    Sleep(del);

    cout << string(t.length(), '\b');

    for (int i = 0; i < len ; i++)
    {
        clearscreen();
        cout << "\n\n    " << t;
        t.erase(t.end() - 1);
        Sleep(100);
    }
}

void next()
{
    string continune = ">> Next...";
    cout << "\n\n    ";
    cout << continune;
}

void end()
{
    string continune = ">> THE END";
    cout << "\n\n    ";
    cout << continune;
}

void restart()
{
    string continune = ">> RESTART";
    cout << "\n\n    ";
    cout << continune;
}

//void flashtext(string text, int delay, int time)
void flashtext(string text)
{
    cout << ">> ";

    for (int i = 0; i < 4; i++)
    {
        cout << text;
        Sleep(100);
        cout << string(text.length(), '\b');
        cout << string(text.length(), ' ');
        Sleep(100);
        cout << string(text.length(), '\b');
        //clearscreen();
        //Sleep(200);
    }
    clearscreen();
}

void flashtext2(string text)
{    
    for (int i = 0; i < 4; i++)
    {
        cout << text;
        Sleep(300);
        cout << string(text.length(), '\b');
        cout << string(text.length(), ' ');
        Sleep(300);
        cout << string(text.length(), '\b');
        //clearscreen();
        //Sleep(200);
    }    
}

void dead()
{
    clearscreen();
    string continune = "YOU DIED";
    cout << "\n\n    ";
    flashtext2(continune);
    cout << continune;
    Sleep(1000);
    cout << "\n\n    ";
    cout << "Press any key to continune...";
}