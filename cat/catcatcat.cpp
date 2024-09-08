#include <ntifs.h>
#include "catcatcatcat.h"
#include "catcatcatcatcat.h"
#include "catcatcat.h"
#include "catcat.h"


char* cat::catcatcatcatcatcatcatcatcatttttttcatcattttttttt(SMBIOS_HEADER* header, SMBIOS_STRING string)
{
	const auto* start = reinterpret_cast<const char*>(header) + header->Length;

	if (!string || *start == 0)
		return nullptr;

	while (--string)
	{
		start += strlen(start) + 1;
	}

	return const_cast<char*>(start);
}


void cat::catcatcatcatcatcatcatcatcattttttt(char* string)
{
	const auto length = static_cast<int>(strlen(string));

	auto* buffer = static_cast<char*>(ExAllocatePoolWithTag(NonPagedPool, length, cat_tag));
	cat::catcatcatcatcatcatcatcatcatcatcatcatcatcatcat(buffer, length);
	buffer[length] = '\0';

	memcpy(string, buffer, length);

	ExFreePool(buffer);
}


NTSTATUS cat::catcatcatcatcatcatcatcatcatttttttcatcatttt(SMBIOS_HEADER* header)
{
	if (!header->Length)
		return STATUS_UNSUCCESSFUL;

	if (header->Type == 0)
	{
		auto* type0 = reinterpret_cast<SMBIOS_TYPE0*>(header);

		auto* vendor = catcatcatcatcatcatcatcatcatttttttcatcattttttttt(header, type0->Vendor);
		catcatcatcatcatcatcatcatcattttttt(vendor);
	}

	if (header->Type == 1)
	{
		auto* type1 = reinterpret_cast<SMBIOS_TYPE1*>(header);

		auto* manufacturer = catcatcatcatcatcatcatcatcatttttttcatcattttttttt(header, type1->Manufacturer);
		catcatcatcatcatcatcatcatcattttttt(manufacturer);

		auto* productName = catcatcatcatcatcatcatcatcatttttttcatcattttttttt(header, type1->ProductName);
		catcatcatcatcatcatcatcatcattttttt(productName);

		auto* serialNumber = catcatcatcatcatcatcatcatcatttttttcatcattttttttt(header, type1->SerialNumber);
		catcatcatcatcatcatcatcatcattttttt(serialNumber);
	}

	if (header->Type == 2)
	{
		auto* type2 = reinterpret_cast<SMBIOS_TYPE2*>(header);

		auto* manufacturer = catcatcatcatcatcatcatcatcatttttttcatcattttttttt(header, type2->Manufacturer);
		catcatcatcatcatcatcatcatcattttttt(manufacturer);

		auto* productName = catcatcatcatcatcatcatcatcatttttttcatcattttttttt(header, type2->ProductName);
		catcatcatcatcatcatcatcatcattttttt(productName);

		auto* serialNumber = catcatcatcatcatcatcatcatcatttttttcatcattttttttt(header, type2->SerialNumber);
		catcatcatcatcatcatcatcatcattttttt(serialNumber);
	}

	if (header->Type == 3)
	{
		auto* type3 = reinterpret_cast<SMBIOS_TYPE3*>(header);

		auto* manufacturer = catcatcatcatcatcatcatcatcatttttttcatcattttttttt(header, type3->Manufacturer);
		catcatcatcatcatcatcatcatcattttttt(manufacturer);

		auto* serialNumber = catcatcatcatcatcatcatcatcatttttttcatcattttttttt(header, type3->SerialNumber);
		catcatcatcatcatcatcatcatcattttttt(serialNumber);
	}
	
	return STATUS_SUCCESS;
}


NTSTATUS cat::catcatcatcatcatcatcatcatcatttttttcatcatt(void* mapped, ULONG size)
{
	auto* endAddress = static_cast<char*>(mapped) + size;
	while (true)
	{
		auto* header = static_cast<SMBIOS_HEADER*>(mapped);
		if (header->Type == 127 && header->Length == 4)
			break;
		
		catcatcatcatcatcatcatcatcatttttttcatcatttt(header);
		auto* end = static_cast<char*>(mapped) + header->Length;
		while (0 != (*end | *(end + 1))) end++;
		end += 2;
		if (end >= endAddress)
			break;	

		mapped = end;
	}
	
	return STATUS_SUCCESS;
}


NTSTATUS cat::catcatcat()
{
	auto* cat = cat::catcatcatcatcatcatcatcatcatcatcat("ntoskrnl.exe");
	if (!cat)
	{
		cat::catctatttttttttttttttttttttttttttt("Failed to find ntoskrnl.sys base!\n");
		return STATUS_UNSUCCESSFUL;
	}

	auto* physicalAddress = static_cast<PPHYSICAL_ADDRESS>(cat::catcatcatcatcatcatcatcatcatcatcatcatcatcat(cat, "\x48\x8B\x0D\x00\x00\x00\x00\x48\x85\xC9\x74\x00\x8B\x15", "xxx????xxxx?xx")); // WmipFindSMBiosStructure -> WmipSMBiosTablePhysicalAddress
	if (!physicalAddress)
	{
		cat::catctatttttttttttttttttttttttttttt("Failed to find SMBIOS physical address!\n");
		return STATUS_UNSUCCESSFUL;
	}

	physicalAddress = reinterpret_cast<PPHYSICAL_ADDRESS>(reinterpret_cast<char*>(physicalAddress) + 7 + *reinterpret_cast<int*>(reinterpret_cast<char*>(physicalAddress) + 3));
	if (!physicalAddress)
	{
		cat::catctatttttttttttttttttttttttttttt("Physical address is null!\n");
		return STATUS_UNSUCCESSFUL;
	}

	auto* sizeScan = cat::catcatcatcatcatcatcatcatcatcatcatcatcatcat(cat, "\x8B\x1D\x00\x00\x00\x00\x48\x8B\xD0\x44\x8B\xC3\x48\x8B\xCD\xE8\x00\x00\x00\x00\x8B\xD3\x48\x8B", ("xx????xxxxxxxxxx????xxxx"));  // WmipFindSMBiosStructure -> WmipSMBiosTableLength
	if (!sizeScan)
	{
		cat::catctatttttttttttttttttttttttttttt("Failed to find SMBIOS size!\n");
		return STATUS_UNSUCCESSFUL;
	}

	const auto size = *reinterpret_cast<ULONG*>(static_cast<char*>(sizeScan) + 6 + *reinterpret_cast<int*>(static_cast<char*>(sizeScan) + 2));
	if (!size)
	{
		cat::catctatttttttttttttttttttttttttttt("SMBIOS size is null!\n");
		return STATUS_UNSUCCESSFUL;
	}

	auto* mapped = MmMapIoSpace(*physicalAddress, size, MmNonCached);
	if (!mapped)
	{
		cat::catctatttttttttttttttttttttttttttt("Failed to map SMBIOS structures!\n");
		return STATUS_UNSUCCESSFUL;
	}
	
	catcatcatcatcatcatcatcatcatttttttcatcatt(mapped, size);
	
	MmUnmapIoSpace(mapped, size);
	
	return STATUS_SUCCESS;
}