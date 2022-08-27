#include <Windows.h>
#include <iostream>
#include <thread>

#include "Addr.hh"
#include "BigWorld/bw_entities.hh"


void TestLoop()
{
	auto entitymanager = EntityManager::instance();
	std::cout << entitymanager << std::endl;
	while (true)
	{
		auto entitiesmap = entitymanager->Entities();
		auto iter = entitiesmap.iter->next();

		for (size_t i = 0; i < entitiesmap.num; i++)
		{
			auto entity = iter->entity();
			iter = iter->next();
			if (!entity) continue;
		
				auto f = BW_Cast(entity, Creature); // trash
				auto avatar = f();
				if (!avatar) continue;
				
				auto nickname = avatar->name();

				//auto skeleton = avatar->skeletonCollider();
				std::wcout << nickname->to_wstring() << std::endl;

				//std::cout << dict <<" <-dict " << name << std::endl;
			
		}

		Sleep(1);
	}


}







int main()
{
	setlocale(LC_ALL, "Russian");
	game::ReaderInit();

	std::thread(TestLoop).join();
	Sleep(-1);
}

