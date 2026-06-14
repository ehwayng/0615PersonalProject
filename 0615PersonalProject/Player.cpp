#include <iostream>
#include "Player.h"

void Player::ShowInfo()
{
    printf("\n================================\n");
    printf("         ** 내 정보 **\n");
    printf("--------------------------------\n");
    printf(" ▶ 레     벨 : %d\n", Level);
    printf(" ▶ 보유 금액 : %d원\n", Money);
    printf(" ▶ 체력 (HP) : %d / %d\n", HP, MaxHP);
    printf(" ▶ 스탯포인트: %d\n", SP);
    printf(" ▶ 스      킬: [수집] %dlv\n               [분해] %dlv\n               [공격] %dlv\n", CollectLevel, DismLevel, AttackPower);
    printf("================================\n\n");
}
