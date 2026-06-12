#pragma once
class GamePlay
{
public:
	void Play_Main();
	void Tutorial();
	void BasicOptin();		//기본 옵션
	void Battle();

	bool Warning = false;			//전투 발생 조건이 충족되었는지 랜덤함수로 폐지 주울때마다 결정하기?
};

