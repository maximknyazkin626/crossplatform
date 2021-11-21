#pragma once
#include "Knyazkin_player.h"
class Knyazkin_coach :
    public Knyazkin_player
{
public:
    DECLARE_SERIAL(Knyazkin_coach);
    int experience;
    string former_team;
    Knyazkin_coach();
    ~Knyazkin_coach();
    void PrintPlayers();
    void ReadPlayers();
    virtual void Serialize(CArchive& ar);
};