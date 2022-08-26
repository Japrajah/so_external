#include <iostream>
#include <thread>
#include <Windows.h>
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
			auto type = entity->ob_type();
			if (!type) continue;
			auto name = type->tp_name();
			auto dict = entity->ob_dict();
			if (!dict) continue;
		
	

			std::cout << dict <<" <-dict " << name << std::endl;
		}
		Sleep(1000);
		
	}












}







int main()
{
	game::ReaderInit();
	std::thread(TestLoop).join();
	Sleep(-1);
}

