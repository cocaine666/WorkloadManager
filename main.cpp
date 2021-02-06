#include <iostream>
#include <experimental/filesystem>
#include "system_information.hpp"
#include <Windows.h>
#include<tchar.h>

int main()
{
    std::cout << "WorkloadManager - 1.0.0.0 [alpha] - UID: \"dev\"\n\n";

    // post system information 
    
    int core_count = get_core_count();
    float ram_amount = get_phys_ram();
    std::string cpu_name = get_cpu_name();
    bool has_ht_smt = ht_smt_availability();
    const std::string workload_name = "workload.exe";
    using std::experimental::filesystem::exists;

    std::cout << "CPU Detected -> " << cpu_name << std::endl;
    std::cout << "Available cores -> " << core_count << std::endl;
    std::cout << "Hyperthreading/SMT -> " << (has_ht_smt ? "Supported" : "Not supported") << std::endl;

    // check if workload is present 

    if (exists("C:\\Users\\Malbasic\\source\\repos\\WorkloadTemplate\\Release\\WorkloadTemplate.exe")) {
   
        std::cout << "Workload is present." << std::endl;
        PROCESS_INFORMATION process_info; 

        STARTUPINFO startup_info; 

        wchar_t cmd_args[] = L" 1 1"; // TODO: implement a better way of storing arguments for multiple instances running different arguments

        ZeroMemory(&startup_info, sizeof(startup_info));
        startup_info.cb = sizeof startup_info;

        for (int i = 0; i < core_count; i++) {
            if (CreateProcess(L"C:\\Users\\Malbasic\\source\\repos\\WorkloadTemplate\\Release\\WorkloadTemplate.exe", cmd_args,
                NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL,
                NULL, &startup_info, &process_info))
            {
                // WaitForSingleObject(process_info.hProcess, INFINITE); - we don't want to wait until program finishes here, not really nice to just comment it out
                CloseHandle(process_info.hThread);
                CloseHandle(process_info.hProcess);

                std::cout << "Successfully used instance #" << i+1 << " CreateProcess to start the program." << std::endl;
            }
            else
            {
                std::cout << "Couldn't start the process." << std::endl;
            }
        }
    }
    else {
        std::cout << "Workload is not present. Please select your workload file built with our template!";
    }
    

    




    //start doing things = find CPU cores and post system information in the information box -- DONE
    //print system info -- DONE 
    //check_default_workload_presence(); -- DONE
    //if(present) {start doing things} -- DONE
    //else {browse the directory and find workload} 
    



    return 0;
}


