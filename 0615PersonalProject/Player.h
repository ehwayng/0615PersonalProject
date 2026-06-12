#pragma once

class Player
{
public:
	int Level = 1;
	int Money = 0;
	int HP = 0;
	int Exp = 0;
	int QuestClearList;	//적당한 자료구조 활용

	void ApplyDamage(int Damage);						//Enemy랑 함수 이름 겹쳐도 되는지? 아니면 부모 클래스를 만들어야 하는지... 왠지 만들어야 할 것 같지? 먼저 만들걸 아오
	void GetDamage(int Damage);
	void Die();											//죽으면 경험치와 돈 일정 퍼센트 잃기
	void GetReward(int RewardMoney, int RewardExp);		//배틀, 던전클리어, 게임승리, 퀘스트클리어 시 보상 얻는 함수
	void GetRest();										//아무것도 진행중이지 않는 상태에서 휴식을 취하고 체력을 회복할 수 있다.


private:
	const int MaxLevel = 30;
	const int MaxHP = 100;
	int MaxExp = 100 + ((Level - 1) * 50);	//초기 경험치통 100 + 레벨업마다 50씩 증가

	inline bool BeDead();
};

