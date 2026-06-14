#pragma once
#include <string>
#include "Player.h"

class GamePlay
{
public:
	void Play_Main();
	void Intro();
	void CollectTrash(Player& player);
	void VisitShop(Player& player);
	void InvestSP(Player& player);
	void DungeonBattle(Player& player);
	void LastGame(Player& player);
};

struct Monster
{
	std::string Name;
	int HP;
	int MaxHP;
	int AttackPower;
};