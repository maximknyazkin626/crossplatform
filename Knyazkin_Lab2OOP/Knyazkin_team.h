#pragma once
#include "pch.h"
#include "Knyazkin_player.h"
class Knyazkin_team
{
public:
	vector <shared_ptr<Knyazkin_player>> Team;
	void AddPlayer(shared_ptr<Knyazkin_player> sptr);
	void PrintPlayers();
	virtual void WritePlayersToFile();
	virtual void ReadPlayersFromFile();
	void DeletePlayers();
};