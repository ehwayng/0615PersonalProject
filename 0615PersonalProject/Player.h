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
	int Money = 10000;
	int HP = 100;
	int MaxHP = 100;
	int SP = 1;			//스탯포인트


	int CollectLevel = 1;	//수집스킬 : 폐기물의 기본가치 증가
	int DismLevel = 1;		//분해스킬 : 폐기물 분해시 잭팟 확률 증가
	int AttackPower = 0;	//전투시 공격력

	void ShowInfo();
};

//주거지 표시 및 레벨업 시 성장멘트 출력을 위한 주거지 목록
static const std::string houses[] =
{
	"",
	"반지하",
	"하숙집",
	"20년 된 원룸",
	"10년 된 원룸",
	"구축 오피스텔",
	"신축 오피스텔",
	"거실 있는 집",
	"널찍한 투룸",
	"복도식 아파트"
};

