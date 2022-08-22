#pragma once


namespace game
{
	extern unsigned long long Base;
	extern unsigned long long g_entitymanager;
}



namespace mem
{
	bool ReaderInit();

}



bool read(unsigned long long address, void* buffer, unsigned long long  size);
template <typename T> T read(unsigned long long address) {
	T buffer{};
	read(address, &buffer, sizeof(T));
	return buffer;
}
