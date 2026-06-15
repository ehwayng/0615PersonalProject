#include <iostream>
#include "Player.h"

void Player::ShowInfo()
{
    printf("==================================================\n");
    printf("                  [ 플레이어 정보 ]               \n");
    printf("==================================================\n");
    printf(" 이름 : %s | 레벨 : LV %d | 보유 SP : %d\n", Name.c_str(), Level, SP);
    //현재 레벨에 맞는 거주지 상시 노출 (10레벨 이상일 땐 의미 X 고정)
    if (Level <= 9) {
        printf(" 현재 보금자리 : 🏠 %s\n", houses[Level].c_str());
    }
    else {
        printf(" 현재 보금자리 : 🏰 복도식 아파트\n");
    }
    printf(" 보유 자산 : %d 원 | 체력 : %d / %d\n", Money, HP, MaxHP);
    printf("--------------------------------------------------\n");
    printf(" 수집력: LV %d | 분해 기술: LV %d | 공격력: %d\n", CollectLevel, DismLevel, AttackPower);
    printf("==================================================\n\n");
}
