#pragma once

//폐지 등급
enum TrashGrade
{
	Grade_Normal, // 일반 폐지
	Grade_Rare,   // 희귀 고철
	Grade_Legend  // 전설의 가전제품
};

//폐지 데이터
struct Trash
{
	std::string TrashName;
	int BaseValue;
	TrashGrade Grade;
};


class Player
{
public:
	std::string Name;
	int Level = 1;
	int Money = 100000;
	int HP = 100;
	int MaxHP = 100;
	int SP = 1;			//스탯포인트


	int CollectLevel = 1;	//수집스킬 : 폐기물의 기본가치 증가
	int DismLevel = 1;		//분해스킬 : 폐기물 분해시 잭팟 확률 증가
	int AttackPower = 0;	//전투시 공격력

	void ShowInfo();
/*	void ApplyDamage(int Damage);
	void Die();											
	void GetReward(int RewardMoney, int RewardExp);	
	void GetRest();	
	void Savings(int InMoney);	
	void Gamble(int InMoney)*/;
};

