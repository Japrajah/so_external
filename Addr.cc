#include "Addr.hh"
#include "common/process.h"
#include <Windows.h>
static  DBVM dbvm;
const Process* g_proc;
//const CR3 UserCR3 = dbvm.GetCR3();
//const CR3 KrnlCR3 = [&] {
//	const uintptr_t GsBase = dbvm.ReadMSR(IA32_KERNEL_GS_BASE_MSR);
//	//The process is not kva-shadowed.
//	if (dbvm.GetPhysicalAddress(GsBase, UserCR3))
//		return UserCR3;
//
//	error("KVA-SHADOWED"e);
//
//	CR3 cr3 = 0;
//	//Finding KernelDirectoryBase...
//	for (size_t Offset = 0x1000; Offset < 0x10000 &&
//		!dbvm.RPM(GsBase + Offset, &cr3, sizeof(cr3), UserCR3); Offset += 0x1000);
//
//	verify(cr3);
//	return cr3;
//}();
constexpr auto pass1 = 0xfafafa;
constexpr auto pass2= 0xDedafafa;
constexpr auto pass3 = 0xfffefafa;


int game::ReaderInit()
{
	if (!dbvm.GetVersion())
	{
		dbvm.SetPassword(pass1, pass2, pass3);
			if (!dbvm.GetVersion())
			{
				return false;
			}
	}
	else
	{
		dbvm.ChangePassword(pass1, pass2, pass3);
	}
	auto passtest = dbvm.GetMemory();
	printf("%x\n", passtest);


	//auto eacsys = GetKernelModuleAddressVerified("EasyAntiCheat.sys");
	//if (eacsys)
	//{
	//	auto physaddr = dbvm.GetPhysicalAddress((uintptr_t)eacsys, KrnlCR3);

	//	ChangeRegOnBPInfo BP{};
	//	BP.changeRIP = true;
	//	BP.newRIP = 0xDEADBEAF;
	//	dbvm.ChangeRegisterOnBP(physaddr, BP);
	//}	



	 auto pd = GetPIDByProcessName("sogame.exe"e);
	if (!pd)
		return 0;
		//error("[USER]Can't find procces!"e); //  replcae with std::exeption?

	static  Kernel processkrnl(dbvm);
	static const auto proc = Process(processkrnl, pd, 0);
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
//processkrnl.GetKernelCR3(4);



// 48 8B ? ? ? ? ? 48 8B ? ? E8 ? ? ? ? 48 8B ? 48 8B ? E8


return pd;
}


bool read(unsigned long long address, void* buffer, unsigned long long size) {

	return   g_proc->ReadProcessMemory(address, buffer, size);
}




