#include "Addr.hh"
#include "common/process.h"
#include <Windows.h>
static  DBVM dbvm;
const Process* g_proc = nullptr;
unsigned long long game::Base;
void* game_mem;
bool mem::ReaderInit()
{
	auto pid = GetPIDByProcessName("sogame.exe"e);
	if (!pid)
		error("[USER]Can't find procces!"e); //  replcae with std::exeption?

	Kernel processkrnl(dbvm);
	const auto proc = Process(processkrnl, pid, 0);
	g_proc = &proc;
	game::Base = proc.GetBaseAddress();
	if (!game::Base)
		error("[DEV]Can't Get Base Address!"e);
	
auto  proc_size = proc.GetSizeOfImage();
game_mem = VirtualAlloc(0, proc_size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
if (!game_mem)
error("[DEV]Failed allocate game_mem"e);


auto chain69 = proc.ScanCurrentModule("48 8B 05 ? ? ? ? 4C 8B 50 28"e); // replace this with pattern scan from file instead reading .text section  from process memory
if (!chain69)
error("[DEV]Can't find EntityManager!"e);
auto g_entitymanager = chain69 + read<int>(chain69 + 3i64) + 7i64;


read(game::Base, game_mem, proc_size);

	
}


bool read(unsigned long long address, void* buffer, unsigned long long size) {

	return g_proc->ReadProcessMemory(address, buffer, size);
}




