#include <iostream>
#include "Addr.hh"

int main()
{
	game::ReaderInit();
	std::cout << std::hex << game::g_entitymanager << std::endl;
	read<int>(game::g_entitymanager);
}

}
