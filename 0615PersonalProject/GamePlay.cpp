#include <iostream>
#include "GamePlay.h"
#include "Player.h"
using namespace std;

Player player;

void GamePlay::Play_Main()	//전반적인 게임 흐름. 필요한 함수는 이 코드 안에서 갖고 놀기.
{
	Tutorial();


}

void GamePlay::Tutorial()
{
	//온갖 시작 멘트와 각 기능 소개
	//뭔가 이벤트가 있을 때 배경이 바뀌는 함수도 있으면 좋을 것 같긴 한데...
	printf("플레이어의 이름을 입력해 주세요 : ");	//걍 튜토리얼을 플레이어 클래스에 넣어야 할듯?
	cin >> player.Name;
	printf("[%s]님, ____의 세계에 오신 것을 환영합니다!\n", player.Name.c_str());

	printf("기본 장비를 지급해 드렸습니다. 인벤토리 창과 장비 창을 열어보세요");
}

void GamePlay::BasicOptin()
{
	printf("1. \n\n");
}


