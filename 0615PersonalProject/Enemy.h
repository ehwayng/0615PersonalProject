#pragma once

class Enemy
{
public:
	int HP = 100;
	int AttackPower = 0;
	int DefensePower = 0;
	int RewardMoney = 0;
	int RewardExp = 0;

	void ApplyDamage();
	void GetDamage();
	void Die();

private:
	bool BeDead = false;
};

