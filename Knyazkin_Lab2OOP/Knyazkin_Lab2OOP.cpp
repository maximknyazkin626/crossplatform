// Knyazkin_Lab2OOP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "framework.h"
#include "Knyazkin_Lab2OOP.h"
#include "Knyazkin_player.h"
#include "Knyazkin_team.h"
#include "Knyazkin_coach.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Единственный объект приложения

CWinApp theApp;

using namespace std;


void PrintMenu()
{
    //system("cls");
    cout << "1. Add Player to Team    " << endl
        << "2. Add Coach to Team" << endl
        << "3. View Players from Team" << endl
        << "4. Save Team to File   " << endl
        << "5. Load Team from File " << endl
        << "6. Delete Team         " << endl
        << "0. Exit                       " << endl;
}

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // инициализировать MFC, а также печать и сообщения об ошибках про сбое
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: вставьте сюда код для приложения.
            wprintf(L"Критическая ошибка: сбой при инициализации MFC\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: вставьте сюда код для приложения.
            Knyazkin_team Team;
            while (true)
            {
                PrintMenu();
                int i;
                cout << "Choose the option: ";
                cin >> i;
                switch (i)
                {
                case 1:
                {
                    shared_ptr<Knyazkin_player> player = make_shared<Knyazkin_player>();
                    player.get()->ReadPlayers();
                    Team.AddPlayer(player);
                    break;
                }
                case 2:
                {
                    shared_ptr<Knyazkin_coach> coach = make_shared<Knyazkin_coach>();
                    coach.get()->ReadPlayers();
                    Team.AddPlayer(coach);
                    break;
                }
                case 3:
                {
                    Team.PrintPlayers();
                    break;
                }
                case 4:
                {
                    Team.WritePlayersToFile();
                    break;
                }
                case 5:
                {
                    Team.ReadPlayersFromFile();
                    break;
                }
                case 6:
                {
                    Team.DeletePlayers();
                    break;
                }
                case 0:
                {
                    return 0;
                    break;
                }
                default: cout << "Wrong action!" << endl;
                }
            }
        
        }
    }
    else
    {
        // TODO: измените код ошибки в соответствии с потребностями
        wprintf(L"Критическая ошибка: сбой GetModuleHandle\n");
        nRetCode = 1;
    }

    return nRetCode;
}
