#pragma once

class Player
{
public:
	std::string Name;
	int Level = 1;
	int Money = 0;
	int HP = 0;
	int Exp = 0;
	int SP = 0;

	//생성자 필요

	int CollectLevel = 1;
	int DismLevel = 1;
	int AttackPower = 0;

	//함수 : 수집, 판매, 분해, 전투 시 공격/피격, 패배/승리, 보상 등
	void ApplyDamage(int Damage);						//Enemy랑 함수 이름 겹쳐도 되는지? 아니면 부모 클래스를 만들어야 하는지... 
	void GetDamage(int Damage);
	void Die();											//죽으면 경험치와 돈 일정 퍼센트 잃기
	void GetReward(int RewardMoney, int RewardExp);	
	void GetRest();										//휴식을 취해 체력을 회복하거나 지능(?)을 올릴 수 있다.
	void Savings(int InMoney);							//적금 통장에 돈을 저축해놓을 수 있다. 이율은 실시간으로 변동되며, 원할 때 확인할 수 있다.
	void Gamble(int InMoney);							//차라리 도박이 나을지도 몰라...


private:
	const int MaxLevel = 30;
	const int MaxHP = 100;
	int MaxExp = 100 + ((Level - 1) * 50);	//초기 경험치통 100 + 레벨업마다 50씩 증가

	inline bool BeDead();
};

