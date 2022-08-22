#include "Addr.hh"
#include "common/process.h"
static  DBVM dbvm;
const Process* g_proc = nullptr;
unsigned long long game::Base;

bool mem::ReaderInit()
{
	auto pid = GetPIDByProcessName("sogame.exe"e);
	if (!pid)
		error("[USER]Can't find procces!"e); //  replcae with std::exeption?

	Kernel processkrnl(dbvm);
	const auto proc = Process(processkrnl, pid, 0);
	g_proc = &proc;
	game::Base = proc.GetBaseAddress();

	auto chain69 = proc.ScanCurrentModule("48 8B 05 ? ? ? ? 4C 8B 50 28"e); // replace this with pattern scan from file instead reading .text section  from process memory
	if (!chain69)
		error("[DEV]Can't find EntityManager!"e);
	auto chain699 = proc.ScanCurrentModule("4C 8D ? ? ? ? ? 4C 8B ? 48 39 ? 08"e); // replace this with pattern scan from file instead reading .text section  from process memory
	if (!chain699)
		error("[DEV]Can't find method_cache(Python)!"e);

	auto g_entitymanager = chain69 + read<int>(chain69 + 3i64) + 7i64;

}


bool read(unsigned long long address, void* buffer, unsigned long long size) {

	return g_proc->ReadProcessMemory(address, buffer, size);
}




