#include <iostream>
#include <cstdio>
#include <Windows.h>
#include "GamePlay.h"
#include "Player.h"
using namespace std;


Player player;

void GamePlay::Play_Main()	//전반적인 게임 흐름. 필요한 함수는 이 코드 안에서 갖고 놀기.
{
    //폰트 기울임 활성화
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }

    srand(static_cast<unsigned int>(time(NULL)));   //랜덤 시드

    /* ---------------------------------------------------- */
    // 녹화시 빠른 진행을 위한 변수 세팅 (실제 진행시 주석 처리)
    //player.Level = 8;
    //player.Money = 100000;
    //player.AttackPower = 40;
    //player.MaxHP = 200;
    //player.HP = 150;
    /* ---------------------------------------------------- */

    Intro();        //시작 전 인트로
    
    while (true)    //게임 루프
    {
        system("cls");
        player.ShowInfo();

        int Choice;
        printf("1. 길거리로 나가 폐기물 줍기\n");
        printf("2. 고물상 방문하기\n");
        printf("3. 능력치 강화하기\n");
        printf("4. 게임 종료\n");
        printf("▶ 원하는 행동을 선택하세요: ");
        std::cin >> Choice;

        if (Choice == 1) {
            CollectTrash(player);
        }
        else if (Choice == 2) {
            VisitShop(player);
        }
        else if (Choice == 3) {
            InvestSP(player);
        }
        else if (Choice == 4) {
            printf("게임을 종료합니다. 다음에 만나요!\n");
            break;
        }
        else {
            printf("잘못된 입력입니다. 다시 선택해 주세요.\n");
            system("pause");
        }

        // 엔딩 조건 체크 (LV 10 달성 시 최종 라스트 게임으로 강제 전환)
        if (player.Level >= 10) {
            system("cls");
            player.Money += 10000000;
            printf("🎉 축하합니다! 레벨 10 달성의 보상으로 현금 1000만원이 즉시 지급됩니다!\n");
            printf("▶ 현재 잔액: %d원\n", player.Money);
            printf("=========================================================================\n");
            system("pause");

            LastGame(player);
            break;
        }
    }

    return;

}

void GamePlay::Intro()
{
	printf("플레이어의 이름을 입력해 주세요 : ");
	cin >> player.Name;
	
    system("cls");
    printf("==================================================\n");
    printf("              [ PROLOGUE: 프롤로그 ]             \n");
    printf("==================================================\n");
    printf(" 대기업 구조조정의 칼바람이 불던 3026년 봄...\n");
    printf(" 내집 마련의 꿈을 회사에 두고 나와야 했던 당신,\n");
    printf(" 이 빌딩숲 어디에도 제 한몸 갈 곳이 없습니다.\n");
    printf("--------------------------------------------------\n");
    system("pause");

    system("cls");
    printf("==================================================\n");
    printf("              [ PROLOGUE: 프롤로그 ]             \n");
    printf("==================================================\n");
    printf(" \033[3m'어떻게든 살아지겠지!'\033[0m 호기롭게 외쳤지만\n");
    printf(" 현실은 차갑기만 했습니다.\n\n");
    printf(" 통장 잔고는 단돈 10000원.\n");
    printf(" 당장 오늘의 밥값을 걱정하던 당신의 눈에\n");
    printf(" 길거리에 굴러다니는 박스와 빈 캔이 들어옵니다...\n");
    printf("--------------------------------------------------\n");
    system("pause");

    system("cls");
    printf("==================================================\n");
    printf("              [ PROLOGUE: 프롤로그 ]             \n");
    printf("==================================================\n");
    printf(" \033[3m'쓰이다 버려진 저 쓰레기들이 꼭 나같구나...'\033[0m\n");
    printf(" 그때 한 고물상 주인이 다가와 말합니다.\n\n");
    printf(" \033[3m'버려진 것들 중엔 누구도 몰라본 보물도 많지.\n");
    printf(" 자네라면 그 가치를 알아볼 수 있을 것 같은데...'\033[0m\n");
    printf("--------------------------------------------------\n");
    system("pause");

    system("cls");
    printf("==================================================\n");
    printf("   [ No RISK No HOME! : 쓰레기로 자수성가하기 ]\n");
    printf("==================================================\n");
    printf(" 전직 엘리트 사원의 눈물겨운 고물탐험기(?),\n");
    printf(" 지금 시작합니다!\n");
    printf("--------------------------------------------------\n");
    system("pause");
}

//폐기물 수집 및 분해, 던전 입장 프로세스
void GamePlay::CollectTrash(Player& player)
{
    system("cls");
    cout << "============= 🗑️ 폐기물 수집 GO! =============\n";
    cout << " 동네 골목길을 샅샅이 뒤지는 중... (슥삭슥삭)\n";
    cout << "==============================================\n";
    system("pause");

    //0~99 중 난수를 뽑아 폐지 등급 결정
    int rate = rand() % 100;
    Trash FoundTrash;

    if (rate < 70) { //70% 확률로 일반 폐기물
        int namePick = rand() % 3;
        string names[] = { "찌그러진 알루미늄 캔", "찢어진 택배 박스", "오래된 생수통" };
        FoundTrash = { names[namePick], 700, Grade_Normal };
    }
    else if (rate < 95) { // 25% 확률로 희귀 고철
        int namePick = rand() % 2;
        string names[] = { "녹슨 자전거 프레임", "구리 전선 한 묶음" };
        FoundTrash = { names[namePick], 3000, Grade_Rare };
    }
    else { // 5% 확률로 전설 아이템
        FoundTrash = { "★ 누군가 잃어버린 애플폰 ★", 15000, Grade_Legend };
    }

    // 플레이어의 수집 레벨에 따라 기본 가치 20%씩 보너스
    int FinalValue = FoundTrash.BaseValue * (1.0f + (player.CollectLevel - 1) * 0.2f);

    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    if (FoundTrash.Grade == Grade_Normal)
        printf("\n[NORMAL] 등급의 %s을(를) 발견했습니다!\n", FoundTrash.TrashName.c_str());
    else if (FoundTrash.Grade == Grade_Rare)
        printf("\n🎉 축하합니다! ✨[RARE]✨ 등급의 %s을(를) 발견했습니다!\n", FoundTrash.TrashName.c_str());
    else
        printf("\n🚨이럴수가!🚨 💎[LEGEND]💎 등급의 %s을(를) 발견했습니다!!\n", FoundTrash.TrashName.c_str());
    
    printf("💰 현재 상태의 감정가: %d원\n", FinalValue);
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("1. 즉시 고물상에 판매하기\n");
    printf("2. 대박 물건일지도? 분해하기\n");
    printf("▶ 행동을 선택하세요: ");
    int Choice;
    cin >> Choice;

    if (Choice == 1) { //판매
        player.Money += FinalValue;
        printf("\n💰 고물상에 넘깁니다. 주인이 값을 치러줍니다. 💵 + %d원\n", FinalValue);
        printf("▶ 현재 잔액 : %d원\n", player.Money);
    }
    else if (Choice == 2) { // 분해
        printf("\n🔧 뻰치와 드라이버로 조심스럽게 분해를 시작합니다...\n");
        system("pause");

        int decompRate = rand() % 100;  
        int jackpotChance = 10 + player.DismLevel;   //플레이어의 분해 스킬이 높을수록 대박 확률 보너스 부여

        if (decompRate < jackpotChance) {   // 대박. 등급에 따라 5배 ~ 50배 보상
            int multiplier = 5;
            if (FoundTrash.Grade == Grade_Rare) multiplier = 20;
            if (FoundTrash.Grade == Grade_Legend) multiplier = 50;

            int jackpotMoney = FinalValue * multiplier;
            player.Money += jackpotMoney;

            printf("🚨 [대 ∙ 박 ∙ 사 ∙ 건] 🚨\n");
            printf("💎 안에서 값비싼 '희귀 원료'가 쏟아집니다!!\n");
            printf("기존 가치의 %d배 보상! 💵 + %d원\n", multiplier, jackpotMoney);
        }
        else {  // 쪽박. 70% 확률로 절반, 30% 확률로 증발
            if (rand() % 10 < 3) {
                printf("💀 콰광! 분해 도중 전지가 폭발했습니다! (치료비 지출 -500원)\n");
                player.Money -= 500;
                player.HP -= 10;
            }
            else {
                int halfPrice = FinalValue / 2;
                player.Money += halfPrice;
                printf("😭 실패... 핵심 부품이 부서졌습니다. 고철값만 겨우 건졌습니다. 💵 + %d원\n", halfPrice);
            }
        }
        printf("▶ 현재 잔액: %d원\n", player.Money);
    }
    else {
        printf("다른 선택지는 없습니다. 판매와 분해 중에 고르세요!\n");
        system("pause");
    }

    // 20% 확률로 돌을 주워 던전 이벤트 유발
    if (rand() % 100 < 20) {    
        printf("\n'어라...?' 폐기물 더미 밑에서 기묘한 빛을 내는 [신비로운 돌]을 건드렸습니다!\n");
        printf("🌀 알 수 없는 강력한 힘에 이끌려 폐기물 던전으로 강제 소환됩니다!!\n");
        system("pause");

        DungeonBattle(player);
    }
    system("pause");
}

//고물상 방문 - HP회복, 승급게임, SP투자 선택지 함수
void GamePlay::VisitShop(Player& player)
{
    while (true) {
        system("cls");
        printf("==================================================\n");
        printf("       🏪 고물상 본점 (상점 & 승급 시험) 🏪\n");
        printf("==================================================\n");
        printf(" [보유 금액] %d원  |  [현재 레벨] LV %d\n", player.Money, player.Level);
        printf("--------------------------------------------------\n");
        printf("1. 💊 체력 회복하기 (드링크) : 1000원 [HP +50]\n");
        printf("2. 🎰 승급 미니게임 도전하기       : %d원\n", player.Level * 3000); // 레벨별 도전 비용 상승
        printf("3. 🔙 마을로 돌아가기\n");
        printf("==================================================\n");
        printf("▶ 무엇을 하시겠습니까? : ");

        int ShopChoice;
        cin >> ShopChoice;

        if (ShopChoice == 1) {  //체력 회복
            if (player.Money < 1000) {
                printf("\n❌ 고물상 주인: \"돈도 없는 녀석이 어디서 외상을 달래!\"\n");
            }
            else if (player.HP >= player.MaxHP) {
                printf("\n🔋 이미 체력이 가득 차 있어서 더 마실 수 없습니다.\n");
            }
            else {
                player.Money -= 1000;
                player.HP += 50;
                if (player.HP > player.MaxHP) player.HP = player.MaxHP;
                printf("\n🥤 시원한 피로회복제를 마셨습니다! 체력이 50 회복됩니다. (현재 HP: %d)\n", player.HP);
            }
            system("pause");
        }
        else if (ShopChoice == 2) { //레벨업 미니게임 도전
            int fee = player.Level * 3000; //도전 비용
            if (player.Money < fee) {
                printf("\n❌ 고물상 주인: \"이번 등급 시험을 보려면 %d원이 필요해. 더 벌어와!\"\n", fee);
                system("pause");
                continue;
            }

            // 판돈 차감
            player.Money -= fee;
            system("cls");
            printf("==================================================\n");
            printf("       🎰 레벨업 미니게임: 비밀번호를 맞춰라! 🎰\n");
            printf("==================================================\n");
            printf("고물상 주인이 비밀 금고의 번호(1~30) 중 하나를 생각했습니다.\n");
            printf("총 [5번]의 기회 안에 번호를 맞춰 레벨업과 SP 획득을 노립니다!\n");
            printf("--------------------------------------------------\n");
            system("pause");

            // 정답 번호 및 게임 세팅
            int answer = (rand() % 30) + 1;
            int chance = 5;
            bool isWin = false;

            while (chance > 0) {
                printf("\n[남은 기회: %d회] 생각하시는 숫자를 입력하세요 (1~30): ", chance);
                int guess;
                cin >> guess;

                if (guess == answer) {
                    printf("\n🎉 정답입니다! 금고가 철컥 열리며 숨겨진 노하우를 터득했습니다!\n");
                    isWin = true;
                    break;
                }
                else if (guess < answer) {
                    printf("🔺 UP! 그것보다는 큰 숫자입니다.\n");
                }
                else {
                    printf("🔻 DOWN! 그것보다는 작은 숫자입니다.\n");
                }
                chance--;
            }

            //게임 결과 처리
            if (isWin) {
                player.Level++;
                player.SP += 2; // 레벨업 보상 스탯 포인트 지급
                printf("\n레벨업 성공! [LV %d] 이(가) 되었습니다!\n", player.Level);
                printf("보상으로 능력치를 올릴 수 있는 [스탯포인트 2 SP]를 획득했습니다.\n");
                printf("이제 수집하는 폐기물의 기본 가치가 20%% 더 상승합니다.\n");

                //레벨업시 성장(이사) 멘트 추가
                if (player.Level <= 9)
                    printf("\n🏠 열심히 모은 돈으로 [%s]를 벗어나 [%s]로 이사합니다...\n", houses[player.Level - 1].c_str(), houses[player.Level].c_str());
            }
            else {
                printf("\n기회를 모두 날렸습니다! 정답은 [%d]였습니다.\n", answer);
                printf("고물상 주인: \"하하하! 지참금은 내가 잘 쓰마!\"\n");
                printf("레벨업에 실패했지만 다시 돈을 모아 도전할 수 있습니다.)\n");
            }
            system("pause");
        }
        else if (ShopChoice == 3) {
            printf("\n할 일이 생각나 마을로 발걸음을 돌립니다.\n");
            system("pause");
            break;
        }
        else {
            printf("\n잘못된 선택지입니다. 다시 선택해 주세요.\n");
            system("pause");
        }
    }
}

//SP 투자
void GamePlay::InvestSP(Player& player)
{
    while (true) {
        system("cls");
        printf("==================================================\n");
        printf("       🏋️ 능력치 강화 (스탯 포인트 투자) 🏋️\n");
        printf("==================================================\n");
        printf(" [보유 스탯포인트] %d SP\n", player.SP);
        printf("--------------------------------------------------\n");
        printf("1. 🚚 수집력 강화 (현재 LV %d) : 폐지 기본 가치 +20%%\n", player.CollectLevel);
        printf("2. 🔧 분해 기술   (현재 LV %d) : 분해 대박 확률 +1%%\n", player.DismLevel);
        printf("3. ⚔️ 전투 공격력 (현재 %d)   : 전투시 데미지 상승\n", player.AttackPower);
        printf("4. 🔙 마을로 돌아가기\n");
        printf("==================================================\n");
        printf("▶ 어떤 능력치를 올리시겠습니까? : ");

        int SPchoice;
        cin >> SPchoice;

        if (SPchoice == 4) {
            printf("\n강화를 마치고 마을로 돌아갑니다.\n");
            system("pause");
            break;
        }

        if (player.SP <= 0) {
            printf("\n❌ 투자할 스탯 포인트(SP)가 부족합니다! 승급 시험을 보고 오세요.\n");
            system("pause");
            continue;
        }

        if (SPchoice == 1) {
            player.CollectLevel++;
            player.SP--;
            printf("\n🚚 수집력이 강화되었습니다! (LV %d -> LV %d)\n", player.CollectLevel - 1, player.CollectLevel);
        }
        else if (SPchoice == 2) {
            player.DismLevel++;
            player.SP--;
            printf("\n🔧 분해 기술이 강화되었습니다! (LV %d -> LV %d)\n", player.DismLevel - 1, player.DismLevel);
        }
        else if (SPchoice == 3) {
            player.AttackPower += 5; //한 번에 5씩 상승
            player.SP--;
            printf("\n⚔️ 공격력이 강력해졌습니다! (현재 공격력: %d)\n", player.AttackPower);
        }
        else {
            printf("\n❌ 잘못된 선택지입니다.\n");
        }
        system("pause");
    }
}

//던전 입장시 호출
void GamePlay::DungeonBattle(Player& player)
{
    system("cls");
    printf("==================================================\n");
    printf("            🌀 폐기물 던전 진입 🌀\n");
    printf("==================================================\n");
    printf("어두컴컴한 고철 더미 사이에서 무시무시한 기운이 느껴집니다...\n");
    system("pause");

    // 던전 몬스터 생성
    Monster enemy;
    int mobPick = rand() % 3;
    if (mobPick == 0)
        enemy = { "방사능에 오염된 돌연변이 쥐", 40, 40, 8 };
    else if (mobPick == 1)
        enemy = { "버려진 불량 로봇", 60, 60, 12 };
    else
        enemy = { "🔥 거대 폐기물 슬라임 🔥", 100, 100, 18 };

    printf("\n🚨 쓰레기더미 속에서 [%s]이(가) 나타났다!\n", enemy.Name.c_str());
    system("pause");

    // 속성 스킬 횟수 제한 설정
    int elementalSkillCount = 2;

    // 턴제 전투 루프
    while (enemy.HP > 0 && player.HP > 0) {
        system("cls");
        printf("==================================================\n");
        printf("[플레이어] HP: %d / %d\n[%s] HP: %d / %d\n", player.HP, player.MaxHP, enemy.Name.c_str(), enemy.HP, enemy.MaxHP);
        printf("==================================================\n");
        printf("1. 연장 휘두르기 (기본 공격)\n");
        printf("2. 초고압 전류 배선 던지기 (속성 공격 / 남은 횟수: %d회)\n", elementalSkillCount);
        printf("3. 랜덤 공격 (랜덤 발동 / 10%% 확률로 플레이어 즉사)\n");
        printf("▶ 어떤 공격을 하시겠습니까? : ");

        int AttackChoice;
        cin >> AttackChoice;

        int playerDamage = 0;
        bool isPlayerTurnValueValid = true;

        switch (AttackChoice) {
        case 1: // 기본 공격 - 공격력 기반으로 변동
        {
            playerDamage = player.AttackPower + (rand() % 5);
            printf("\n⚔️ 뻰치를 휘둘러 기본 공격을 가했습니다! [%d의 데미지!]\n", playerDamage);
            enemy.HP -= playerDamage;
            break;
        }

        case 2: // 속성 공격 - 기본의 2배
        {
            if (elementalSkillCount > 0) {
                playerDamage = (player.AttackPower * 2) + (rand() % 10);
                printf("\n⚡ 고압 전류 배선을 던져 속성 공격을 가했습니다! [%d의 치명적 데미지!]\n", playerDamage);
                enemy.HP -= playerDamage;
                elementalSkillCount--;
            }
            else {
                printf("\n❌ 속성 공격 횟수를 다 썼습니다! 기회를 날렸습니다.\n");
            }
            break;
        }

        case 3: // 랜덤 공격
        {
            int randomRoll = rand() % 100;
            if (randomRoll < 10) { // 10% 확률로 즉사
                printf("\n💀 [치명적 오류] 무리하게 기계를 조작하다가 폭발했습니다! 즉사합니다!\n");
                player.HP = 0;
            }
            else if (randomRoll < 55) { // 45% 확률로 기본 공격
                playerDamage = player.AttackPower + (rand() % 5);
                printf("\n🎲 랜덤 결과 -> 기본 공격 발동! [%d의 데미지]\n", playerDamage);
                enemy.HP -= playerDamage;
            }
            else { // 45% 확률로 속성 공격 (횟수 차감 없음)
                playerDamage = (player.AttackPower * 2) + (rand() % 10);
                printf("\n🎲 랜덤 결과 -> 대성공! 속성 공격이 발동됩니다! [%d의 데미지]\n", playerDamage);
                enemy.HP -= playerDamage;
            }
            break;
        }

        default:
            printf("\n❌ 당황해서 헛손질을 했습니다! (잘못된 입력)\n");
            isPlayerTurnValueValid = false;
            break;
        }

        system("pause");

        // 몬스터가 죽었는지 체크
        if (enemy.HP <= 0) {
            break;
        }

        // 몬스터의 턴 (플레이어가 올바른 입력을 했을 때만 공격)
        if (isPlayerTurnValueValid && player.HP > 0) {
            int enemyDamage = enemy.AttackPower + (rand() % 4) - 2;
            if (enemyDamage < 1) enemyDamage = 1;

            printf("\n💥 [%s]의 반격! %d의 데미지를 입었습니다.\n", enemy.Name.c_str(), enemyDamage);
            player.HP -= enemyDamage;
            system("pause");
        }
    }

    // 전투 결과 처리
    system("cls");
    if (player.HP <= 0) {
        printf("💀💀💀💀💀💀💀💀💀💀\n");
        printf("던전에서 패배하여 쓰러졌습니다...\n");
        printf("지나가던 친절한 청소부가 구해줬지만, 치료비로 2000원이 지출됩니다.\n");
        player.Money -= 2000;
        if (player.Money < 0) player.Money = 0;
        player.HP = player.MaxHP / 2; // 체력 절반으로 부활
    }
    else {
        printf("🎉🎉🎉 던전 클리어! 🎉🎉🎉\n");
        printf("[%s]을(를) 완벽하게 고철로 만들었습니다!\n", enemy.Name.c_str());

        // 확정 보상으로 대박 특수 폐기물 지급
        int rewardMoney = 5000;
        player.Money += rewardMoney;
        printf("\n🎁 [★ 황금 고철 보물상자 ★]를 획득하여 고물상에 즉시 팔았습니다!\n");
        printf("💰 고물상 대금 지급: 💵 + %d원\n", rewardMoney);
    }
    system("pause");
}

//엔딩 게임
void GamePlay::LastGame(Player& player)
{
    system("cls");
    printf("🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨\n");
    printf("   [!!🚨 WARNING : 고물상 빌런의 기습 🚨!!]\n");
    printf("🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨\n");
    printf("모은 돈으로 마침내 성공의 문턱에 다다른 순간,\n");
    printf("고물상 주인이 검은 미소를 지으며 당신의 앞을 막아섭니다!\n\n");
    printf("고물상 주인: \033[3m흐흐흐... 등급 시험은 다 내 계략이었지.\n");
    printf("             네가 그동안 가져온 희귀 원료들로 '폐기물 지옥'을 만들었다!\033[0m\n");
    printf("그가 리모컨을 누르자, 거대한 고철 로봇이 굉음을 내며 진격해옵니다!\n");
    system("pause");

    // 라스트게임 1: 폐기물 던전 전투
    Monster finalBoss = { "🤖 고물상 마스터의 거대 고철 로봇 🤖", 150, 150, 20 }; //체력 150, 공격력 20의 보스
    printf("\n⚔️ 1차전 : 폐기물 보스와의 전투 START! ⚔*\n");
    system("pause");

    int bossElementalSkillCount = 3;    //최종전 속성공격 횟수

    while (finalBoss.HP > 0 && player.HP > 0) {
        system("cls");
        printf("======================================================\n");
        printf(" [플레이어] HP: %d / %d  |  [폐기물 보스] HP: %d / %d\n", player.HP, player.MaxHP, finalBoss.HP, finalBoss.MaxHP);
        printf("======================================================\n");
        printf("1. 연장 휘두르기 (기본 공격)\n");
        printf("2. 초고압 전류 배선 던지기 (속성 공격 / 남은 횟수: %d회)\n", bossElementalSkillCount);
        printf("3. 랜덤 공격 (랜덤 발동 / 10%% 확률로 플레이어 즉사)\n");
        printf("▶ 행동 선택: ");
        int choice; cin >> choice;

        int playerDamage = 0;
        bool isPlayerTurnValueValid = true;

        switch (choice) {
        case 1: // 기본 공격
            playerDamage = player.AttackPower + (rand() % 8) + 5; // 보스전 보너스 데미지 추가
            printf("\n⚔️ 콰앙! 연장을 풀파워로 휘둘렀습니다! [%d의 데미지!]\n", playerDamage);
            finalBoss.HP -= playerDamage;
            break;

        case 2: // 속성 공격
            if (bossElementalSkillCount > 0) {
                playerDamage = (player.AttackPower * 2.5f) + (rand() % 15); // 2.5배 치명타
                printf("\n⚡ 파지직-- 초고압 배선이 로봇의 심장부에 작렬합니다! [%d의 초강력 데미지!]\n", playerDamage);
                finalBoss.HP -= playerDamage;
                bossElementalSkillCount--;
            }
            else {
                printf("\n❌ 게이지가 부족합니다! 속성 공격 횟수를 다 썼습니다.\n");
            }
            break;

        case 3: // 랜덤 공격
        {
            int randomRoll = rand() % 100;
            if (randomRoll < 10) { //10% 확률로 플레이어 즉사
                printf("\n💀 [과부하] 기계를 무리하게 조작하다가 역풍을 맞았습니다! 즉사합니다!\n");
                player.HP = 0;
            }
            else if (randomRoll < 50) { //40% 확률로 기본 공격
                playerDamage = player.AttackPower + (rand() % 8) + 5;
                printf("\n🎲 랜덤 결과 -> 기본 공격 발동! [%d의 데미지]\n", playerDamage);
                finalBoss.HP -= playerDamage;
            }
            else { //50% 확률로 횟수 차감 없는 속성 공격
                playerDamage = (player.AttackPower * 2.5f) + (rand() % 15);
                printf("\n🎲 랜덤 결과 -> 속성공격 대성공!! [%d의 데미지]\n", playerDamage);
                finalBoss.HP -= playerDamage;
            }
            break;
        }

        default:
            printf("\n❌ 긴장한 나머지 조작을 실수했습니다! (턴 낭비)\n");
            isPlayerTurnValueValid = false;
            break;
        }

        system("pause");

        if (finalBoss.HP <= 0) break;

        //보스의 공격 턴
        if (isPlayerTurnValueValid && player.HP > 0) {
            int bossDamage = finalBoss.AttackPower + (rand() % 6) - 2; //20 내외의 데미지
            printf("\n💥 [%s]이(가) 폐기물 로켓을 발사했습니다! %d의 큰 데미지를 입었습니다.\n", finalBoss.Name.c_str(), bossDamage);
            player.HP -= bossDamage;
            system("pause");
        }
    }

    // 1차전 패배시 (체력 충전 후 재도전 기획 반영)
    if (player.HP <= 0) {
        printf("\n💀 쿠궁... 패배했습니다. 하지만 포기할 수 없습니다!\n");
        printf("정신을 바짝 차리고 체력을 회복해 다시 보스에게 도전합니다!\n");
        player.HP = player.MaxHP;
        system("pause");
        LastGame(player); // 재도전 루프
        return;
    }

    // 라스트게임 2: 고물상 주인과의 단판 게임 (Indian Game 변형)
    system("cls");
    printf("==================================================\n");
    printf("      ⚔️ 최종전 : 고물상 주인과의 단판 대결 ⚔\n");
    printf("==================================================\n");
    printf("고물상 주인: \"로봇을 부수다니 제법이군, %s...\n하지만 내가 죽지 않는 이상 끝없이 되살아날 거다!\n\n", player.Name.c_str());
    printf("주인이 카드 두 장을 꺼내 조커를 섞습니다.\n");
    printf("당신의 전재산 %d원이 이 한판에 모두 걸립니다.\n패배시 즉시 파산!\n", player.Money);
    printf("--------------------------------------------------\n");
    printf("1. 왼쪽 카드를 선택\n");
    printf("2. 오른쪽 카드를 선택\n");
    printf("▶ 당신의 운명을 아우를 선택은? : ");
    int cardChoice;
    cin >> cardChoice;

    printf("\n카드를 뒤집는 중...\n");
    system("pause");

    int winningCard = (rand() % 2) + 1; // 1 혹은 2가 당첨

    if (cardChoice == winningCard) {
        //해피엔딩
        system("cls");
        printf("==================================================\n");
        printf(" 🎉🎉🎉 배 ∙ 팅 ∙ 성 ∙ 공 🎉🎉🎉\n");
        printf("==================================================\n");
        printf("고물상 주인: \"으아악! 말도 안 돼! 내 심리를 읽다니...!\"\n");
        printf("고물상 주인은 순식간에 쓰러지고, 폐기물 지옥도 무너집니다.\n\n");
        printf("🏆 당신은 전재산을 지켜냄은 물론, 온동네를 구한 '고물상 히어로'로 추앙받습니다!\n");
        printf("주인이 남긴 억대 자산과 함께 그토록 꿈꾸던 호화로운 삶을 시작합니다!\n");
        system("pause");

        //쿠키
        system("cls");
        printf("🎬 [Cookie]\n");
        printf("--------------------------------------------------\n");
        printf("몇 년 후, 으리으리한 고물상 본점의 주인이 된 당신.\n");
        printf("문득 거리에서 땀흘리며 리어카를 끄는 젊은 청소부를 보게 됩니다.\n");
        printf("어떤 생각이 떠오른 당신은 의미심장한 미소로 다가갑니다...\n\n");
        printf("당신: \"젊은이. 고물 참 실하게 잘 줍는구만. 앞으로 나와 거래하겠나?\"\n");
        printf("--------------------------------------------------\n");
        printf("         - THE END (HAPPY ENDING) -\n");
    }
    else {
        //배드 엔딩
        system("cls");
        printf("==================================================\n");
        printf(" 💀💀💀 꽝! 패배 💀💀💀\n");
        printf("==================================================\n");
        printf("고물상 주인: \"하하하! 조커를 골랐구나! 네 놈의 재산은 이제 다 내 거다!\"\n");
        printf("당신은 전재산 %d원을 몽땅 뺏기고 빈털터리가 되었습니다...\n", player.Money);
        printf("평생 고물상 주인의 밑에서 무임금으로 폐지를 줍는 노예가 되었습니다.\n");
        printf("--------------------------------------------------\n");
        printf("         - THE END (BAD ENDING) -\n");
    }
    system("pause");
}
