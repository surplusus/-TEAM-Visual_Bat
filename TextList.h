#pragma once
#include<string>
#include<vector>


struct textlist
{
	std::string m_cleanse = "챔피언에 걸린 모든 이동 불가와(제압 및 공중\n으로 띄우는 효과 제외) 소환사 주문에 의한 해\n로운 효과를 제거하고 새로 적용되는 이동 불가\n 효과들의 지속시간을 3초가 65 % 감소시킵니\n다.\n기본 재사용 대기 시간:210초";
	std::string m_Ghost = "챔피언이 10초동안 유닛과 충돌하지 않게 되\n며 이동속도가 상승합니다. 이동 속도는 2초\n동안 점차 빨라져 레벨에 따라 최대 28~45%\n까지 상승합니다.\n기본 재사용 대기시간:180초";
	std::string m_heal = "챔피언과 대상 아군의 체력을 90~345만큼(챔\n피언 레벨에 따라 변동) 회복 시키고 1초동안 \n이동속도가 30% 증가합니다. 최근 소환사 주\n문 회복의 영향을 받은 유닛의 경우 치유량이\n 절반만 적용됩니다.\n\n기본 재사용 대기시간:240초";
	std::string m_Exhaust = "적 챔피언을 지치게 만들어 2.5초동안 이동속\n도를 30% 낮추며, 이 동안 가하는 피해량을 \n40% 낮춥니다.\n\n기본 재사용 대기시간:210초";
	std::string m_Flash = "커서 방향으로 챔피언이 짧은 거리를 순간이동\n 합니다.기본 재사용 대기시간:300초";
	std::string m_Smite = "대상 에픽 및 대형/중형 몬스터, 혹은 적 미니\n언에게 390~1000(챔피언 레벨에 따라 변동)\n의 고정 피해를 입힙니다. 몬스터에게 사용하면\n 자신의 최대 체력에 비례해 체력을 회복합니다.\n\n기본 재사용 대기시간:15초";
	std::string m_Teleport = "4초 동안 정신을 집중한 다음, 챔피언이 지정한\n 아군 구조물, 미니언, 혹은 와드로 순간이동합\n니다.\n기본 재사용 대기시간 360초";
	std::string m_Ignite = "적 챔피언을 불태워 5초동안 70~410의 고정\n 피해(챔피언 레벨에 따라 변동)를 입히고 모습\n을 드러내며 치료 효과를 감소시킵니다.\n\n기본 재사용 대기시간:180초";
	std::string m_Barrier = "2초동안 방어막으로 감싸 피해를\n 115~455(챔피언 레벨에 따라 변동)만큼 흡수\n합니다.\n기본 재사용 대기시간:180초";


	std::vector<std::string>	notice;

	void SetNotice()
	{
		notice.push_back(std::string("8"));
		notice.push_back(std::string("7"));
		notice.push_back(std::string("6"));
		notice.push_back(std::string("5"));
		notice.push_back(std::string("3"));
		notice.push_back(std::string("2"));
		notice.push_back(std::string("1"));
	}
};

enum TEXTTYPE
{
	NONE,
	REDYTIME,
	SPELLNAME,
	SPELLINFO,
	NOTICE,

	TIME,
	GOLD,
	KDA,
};