#include "Addr.hh"
#include "common/process.h"
#include <Windows.h>
static  DBVM dbvm;
const Process* g_proc;

bool game::ReaderInit()
{
	static auto pid = GetPIDByProcessName("sogame.exe"e);
	if (!pid)
		error("[USER]Can't find procces!"e); //  replcae with std::exeption?

	static  Kernel processkrnl(dbvm);
	static const auto proc = Process(processkrnl, pid, 0);
	g_proc = &proc;
	game::Base = g_proc->GetBaseAddress();
	if (!game::Base)
		error("[DEV]Can't Get Base Address!"e);
	
	

auto chain69 = g_proc->ScanCurrentModule("48 8B 05 ? ? ? ? 4C 8B 50 28"e); // replace this with pattern scan from file instead reading .text section  from process memory
if (!chain69)
error("[DEV]Can't find EntityManager!"e); // 

// umbra.dll  48 8B ? ? ? ? ? 48 8B ? ? E8 ? ? ? ? 48 8B ? 48 8B ? E8;
game::g_entitymanager = chain69 + read<int>(chain69 + 3i64) + 7i64;
game::umbra_camera = 0x180098220;



// 48 8B ? ? ? ? ? 48 8B ? ? E8 ? ? ? ? 48 8B ? 48 8B ? E8


return true;
}


bool read(unsigned long long address, void* buffer, unsigned long long size) {

	return   g_proc->ReadProcessMemory(address, buffer, size);
}




