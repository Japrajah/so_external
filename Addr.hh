#pragma once

struct game
{
	static inline unsigned long long Base;
	static inline unsigned long long g_entitymanager;
	static inline unsigned long long umbra_camera;
	static inline int pid;
	static int ReaderInit();
	
};







bool read(unsigned long long address, void* buffer, unsigned long long  size);
template <typename T> T read(unsigned long long address) {
	T buffer{};
	read(address, &buffer, sizeof(T));
	return buffer;
}
template <typename T> T read(void* address) {
	T buffer{};
	read((unsigned long long )address, &buffer, sizeof(T));
	return buffer;
}
