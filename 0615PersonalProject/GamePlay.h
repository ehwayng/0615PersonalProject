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

//던전 내 몬스터 구조체
struct Monster
{
	std::string Name;
	int HP;
	int MaxHP;
	int AttackPower;
};
