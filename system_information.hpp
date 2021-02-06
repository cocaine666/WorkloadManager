#pragma once

#include <iostream>
#include <thread>
#include <windows.h>
#include <intrin.h>
#include <sysinfoapi.h>

float get_phys_ram() {

	MEMORYSTATUSEX statex;

	statex.dwLength = sizeof(statex); 

	GlobalMemoryStatusEx(&statex);
	float ram_amount = statex.ullTotalPhys / (1024 * 1024 * 1024);
	
	return ram_amount;
}

bool ht_smt_availability() {

	int cpu_information[4];
	__cpuid(cpu_information, 4);

	bool has_ht_smt = (cpu_information[3] & (1 << 28)) > 0;

	return has_ht_smt;
}

int get_core_count() {

	SYSTEM_INFO system_info;
	GetSystemInfo(&system_info);
	int core_count = system_info.dwNumberOfProcessors;
	return core_count;

}

std::string get_cpu_name()
{
	int cpu_information[4] = { -1 };
	char cpu_string[0x40];
	__cpuid(cpu_information, 0x80000000);
	unsigned int nExIds = cpu_information[0];

	memset(cpu_string, 0, sizeof(cpu_string));

	for (int i = 0x80000000; i <= nExIds; ++i)
	{
		__cpuid(cpu_information, i);
		if (i == 0x80000002)
			memcpy(cpu_string, cpu_information, sizeof(cpu_information));
		else if (i == 0x80000003)
			memcpy(cpu_string + 16, cpu_information, sizeof(cpu_information));
		else if (i == 0x80000004)
			memcpy(cpu_string + 32, cpu_information, sizeof(cpu_information));
	}
	return cpu_string;
}