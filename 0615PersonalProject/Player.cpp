#include <iostream>
#include "Player.h"

void Player::ApplyDamage(int Damage)
{

}

void Player::GetDamage(int Damage)
{
	HP -= Damage;
	printf("당신은 [%d]의 데미지를 입었습니다.\n▶ 남은 HP : %d\n", Damage, HP);
	if (BeDead)
	{
		Die();
	}
}

void Player::Die()
{
	//돈과 경험치 30%씩 잃기 (캐스팅 활용)
}

void Player::GetReward(int RewardMoney, int RewardExp)
{
}

void Player::GetRest()
{
	HP += 50;
}

inline bool Player::BeDead()
{
	if (HP == 0)
		return true;
	else
		return false;
}

