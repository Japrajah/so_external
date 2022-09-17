#include <windows.h>
#include <iostream>
#include <thread>

#include "Addr.hh"
#include "BigWorld/bw_entities.hh"
#include "temp_overlay/overlay.h"


void TestLoop()
{
	auto entitymanager = EntityManager::instance();
	
	std::cout << entitymanager << std::endl;
	while (true)
	{
		auto camera = CameraImpl::Instance();
		bool cahedmatrix = false;
		if (!camera) continue;
	
		auto entitiesmap = entitymanager->Entities();
		auto iter = entitiesmap.iter->next();

		for (size_t i = 0; i < entitiesmap.num; i++)
		{
			auto entity = iter->entity();
			iter = iter->next();
			if (!entity) continue;
		
				auto avatar = BW_Cast(entity, PlayerAvatar); // trash
				if (!avatar) continue;
				Vector2 testscreen;
				auto testpos = avatar->position();
				if (!camera->ProjectWorldToScreen(testpos,&testscreen,&cahedmatrix))  continue;

		}

		Sleep(1);
	} 


}




int main()
{
	setlocale(LC_ALL, "Russian");
	int pid = 0;
	while (true)
	{
		if (GetAsyncKeyState(VK_F2))
		{
			pid = game::ReaderInit();
			if (pid)
				break;
		}
	

	Sleep(5);
	}
	//std::thread(TestLoop).join();

	initoverlay(pid);
	

	
	Sleep(-1);
}

