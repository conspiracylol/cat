#include "catcatcatcatcatcat.h"
#include "catcatcatcatcatcatcat.h"
#include "catcatcatcatcat.h"
#include "catcatcat.h"
#include "catcatcatcat.h"
#include "cat.h"



void cat::catcatcatcatcatcatcatcat(PRAID_UNIT_EXTENSION extension)
{
	extension->_Smart.Telemetry.SmartMask = 0;
}


PDEVICE_OBJECT cat::catcatcatcatcatcatcat(const wchar_t* deviceName)
{
	UNICODE_STRING raidPort;
	RtlInitUnicodeString(&raidPort, deviceName);

	PFILE_OBJECT fileObject = nullptr;
	PDEVICE_OBJECT deviceObject = nullptr;
	auto status = IoGetDeviceObjectPointer(&raidPort, FILE_READ_DATA, &fileObject, &deviceObject);
	if (!NT_SUCCESS(status))
	{
		return nullptr;
	}

	return deviceObject->DriverObject->DeviceObject; // not sure about this
}


NTSTATUS cat::catcatcatcatcatcat(PDEVICE_OBJECT deviceArray, RaidUnitRegisterInterfaces registerInterfaces)
{
	auto status = STATUS_NOT_FOUND;
	
	while (deviceArray->NextDevice)
	{
		if (deviceArray->DeviceType == FILE_DEVICE_DISK)
		{
			auto* extension = static_cast<PRAID_UNIT_EXTENSION>(deviceArray->DeviceExtension);
			if (!extension)
				continue;
			
			const auto length = extension->_Identity.Identity.SerialNumber.Length;
			if (!length)
				continue;

			char original[256];
			memcpy(original, extension->_Identity.Identity.SerialNumber.Buffer, length);
			original[length] = '\0';

			auto* buffer = static_cast<char*>(ExAllocatePoolWithTag(NonPagedPool, length, cat_tag));
			buffer[length] = '\0';

			cat::catcatcatcatcatcatcatcatcatcatcatcatcatcatcat(buffer, length);
			RtlInitString(&extension->_Identity.Identity.SerialNumber, buffer);

			cat::catctatttttttttttttttttttttttttttt("Changed cat serial %s to cat %s.\n", original, buffer);

			status = STATUS_SUCCESS;
			ExFreePool(buffer);

			catcatcatcatcatcatcatcat(extension);

			registerInterfaces(extension);
		}

		deviceArray = deviceArray->NextDevice;
	}

	return status;
}


NTSTATUS cat::cat()
{
	auto* base = cat::catcatcatcatcatcatcatcatcatcatcat("storport.sys");
	if (!base)
	{
		cat::catctatttttttttttttttttttttttttttt("Failed to find cat base!\n");
		return STATUS_UNSUCCESSFUL;
	}

	const auto registerInterfaces = static_cast<RaidUnitRegisterInterfaces>(cat::catcatcatcatcatcatcatcatcatcatcatcatcatcat(base, "\x48\x89\x5C\x24\x00\x55\x56\x57\x48\x83\xEC\x50", "xxxx?xxxxxxx")); // RaidUnitRegisterInterfaces
	if (!registerInterfaces)
	{
		cat::catctatttttttttttttttttttttttttttt("Failed to find cat!\n");
		return STATUS_UNSUCCESSFUL;
	}

	
	
	auto status = STATUS_NOT_FOUND;
	for (auto i = 0; i < 2; i++)
	{
		const auto* raidFormat = L"\\Device\\RaidPort%d";
		wchar_t raidBuffer[18];
		RtlStringCbPrintfW(raidBuffer, 18 * sizeof(wchar_t), raidFormat, i);

		auto* device = catcatcatcatcatcatcat(raidBuffer);
		if (!device)
			continue;

		const auto loopStatus = catcatcatcatcatcat(device, registerInterfaces);
		if (NT_SUCCESS(loopStatus))
			status = loopStatus;
	}

	return status;
}


extern "C" POBJECT_TYPE* IoDriverObjectType;


NTSTATUS cat::catcat()
{
	auto* base = cat::catcatcatcatcatcatcatcatcatcatcat("disk.sys");
	if (!base)
	{
		cat::catctatttttttttttttttttttttttttttt(("Failed to find cat base!\n"));
		return STATUS_UNSUCCESSFUL;
	}

	const auto disableCat = static_cast<DiskEnableDisableFailurePrediction>(cat::catcatcatcatcatcatcatcatcatcatcatcatcatcat(base, ("\x4C\x8B\xDC\x49\x89\x5B\x10\x49\x89\x7B\x18\x55\x49\x8D\x6B\xA1\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x45\x4F"), ("xxxxxxxxxxxxxxxxxxx????xxx????xxxxxxx"))); // DiskEnableDisableFailurePrediction
	if (!disableCat)
	{
		cat::catctatttttttttttttttttttttttttttt(("Failed to find cat!\n"));
		return STATUS_UNSUCCESSFUL;
	}

	UNICODE_STRING driverDisk;
	RtlInitUnicodeString(&driverDisk, (L"\\Driver\\Disk"));

	PDRIVER_OBJECT driverObject = nullptr;
	auto catstat = ObReferenceObjectByName(&driverDisk, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, nullptr, 0, *IoDriverObjectType, KernelMode, nullptr, reinterpret_cast<PVOID*>(&driverObject));
	if (!NT_SUCCESS(catstat))
	{
		cat::catctatttttttttttttttttttttttttttt(("Failed to get cat!\n"));
		return STATUS_UNSUCCESSFUL;
	}

	PDEVICE_OBJECT deviceObjectList[64];
	RtlZeroMemory(deviceObjectList, sizeof(deviceObjectList));

	ULONG numberOfDeviceObjects = 0;
	catstat = IoEnumerateDeviceObjectList(driverObject, deviceObjectList, sizeof(deviceObjectList), &numberOfDeviceObjects);
	if (!NT_SUCCESS(catstat))
	{
		cat::catctatttttttttttttttttttttttttttt(("Failed to cat!\n"));
		return STATUS_UNSUCCESSFUL;
	}

	for (ULONG i = 0; i < numberOfDeviceObjects; ++i)
	{
		auto* deviceObject = deviceObjectList[i];
		disableCat(deviceObject->DeviceExtension, false);
		ObDereferenceObject(deviceObject);
	}

	ObDereferenceObject(driverObject);
	return STATUS_SUCCESS;
}