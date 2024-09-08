#include "catcatcatcatcatcat.h"
#include "catttttttttttcattttttttttt.h"
#include "catcatcatttttttttt.h"
#include "catcatcat.h"
#include "catcatcatcatcat.h"


PVOID cat::catcatcatcatcatcatcatcatcatcatcat(const char* cattttttttttttttttttttt)
{
	PVOID address = nullptr;
	ULONG size = 0;
	
	auto status = ZwQuerySystemInformation(SystemModuleInformation, &size, 0, &size);
	if (status != STATUS_INFO_LENGTH_MISMATCH)
		return nullptr;

	auto* moduleList = static_cast<PSYSTEM_MODULE_INFORMATION>(ExAllocatePoolWithTag(NonPagedPool, size, cat_tag));
	if (!moduleList)
		return nullptr;

	status = ZwQuerySystemInformation(SystemModuleInformation, moduleList, size, nullptr);
	if (!NT_SUCCESS(status))
		goto end;

	for (auto i = 0; i < moduleList->ulModuleCount; i++)
	{
		auto module = moduleList->Modules[i];
		if (strstr(module.ImageName, cattttttttttttttttttttt))
		{
			address = module.Base;
			break;
		}
	}
	
end:
	ExFreePool(moduleList);
	return address;
}


bool cat::catcatcatcatcatcatcatcatcatcatcatcat(const char* cat, const char* pattern, const char* mask)
{
	for (; *mask; ++cat, ++pattern, ++mask) 
	{
		if ('x' == *mask && *cat != *pattern)
		{
			return false;
		}
	}

	return true;
}


PVOID cat::catcatcatcatcatcatcatcatcatcatcatcatcat(PVOID cat, int length, const char* pattern, const char* mask)
{
	length -= static_cast<int>(strlen(mask));
	for (auto i = 0; i <= length; ++i) 
	{
		const auto* data = static_cast<char*>(cat);
		const auto* address = &data[i];
		if (catcatcatcatcatcatcatcatcatcatcatcat(address, pattern, mask))
			return PVOID(address);
	}

	return nullptr;
}


PVOID cat::catcatcatcatcatcatcatcatcatcatcatcatcatcat(PVOID cat, const char* pattern, const char* mask)
{
	PVOID match = nullptr;

	auto* headers = reinterpret_cast<PIMAGE_NT_HEADERS>(static_cast<char*>(cat) + static_cast<PIMAGE_DOS_HEADER>(cat)->e_lfanew);
	auto* sections = IMAGE_FIRST_SECTION(headers);
	
	for (auto i = 0; i < headers->FileHeader.NumberOfSections; ++i) 
	{
		auto* section = &sections[i];
		if ('EGAP' == *reinterpret_cast<PINT>(section->Name) || memcmp(section->Name, ".text", 5) == 0)
		{
			match = catcatcatcatcatcatcatcatcatcatcatcatcat(static_cast<char*>(cat) + section->VirtualAddress, section->Misc.VirtualSize, pattern, mask);
			if (match) 
				break;
		}
	}

	return match;
}


void cat::catcatcatcatcatcatcatcatcatcatcatcatcatcatcat(char* cattttt, const int length)
{
	if (!cattttt)
		return;

	static const char cat[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	auto cattttttt = KeQueryTimeIncrement();

	for (auto n = 0; n <= length; n++)
	{
		auto catt = RtlRandomEx(&cattttttt) % static_cast<int>(sizeof(cat) - 1);
		cattttt[n] = cat[catt];
	}
}