#include <iostream>
#include <Windows.h>
#include <cstdio>

using namespace std;

const int arr_size = 100;
CRITICAL_SECTION critical_s;
volatile LONG arr[arr_size];

void Thread1(){
    srand(time_t(NULL));
    while(true){
        Sleep(1000);
        EnterCriticalSection(&critical_s);
        for ( int i = 0; i < arr_size; i++){
            arr[i] =  rand() * 300 / (RAND_MAX) -150;
        }
        LeaveCriticalSection(&critical_s);
    }
}

void Thread2(){
    srand(time_t(NULL));
    while(true){
        Sleep(500);
        EnterCriticalSection(&critical_s);
        for ( int i = 0; i < arr_size; i++){
            if (i % 2 ==1){
                arr[i] = 0;
            }
        }
        LeaveCriticalSection(&critical_s);
    }
}

int main(){
    InitializeCriticalSection(&critical_s);
    HANDLE hThread1, hThread2;
    DWORD IDThread_1, IDThread_2;

    if ((hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) Thread1, NULL, 0, &IDThread_1)) == NULL){
        int error = GetLastError();
        printf("error!\n", error);
        return error;
    }

    if ((hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) Thread2, NULL, 0, &IDThread_2)) == NULL){
        int error = GetLastError();
        printf("error!\n", error);
        TerminateThread(hThread1, 0);
        CloseHandle(hThread1);
        return error;
    }
    while (true){
        Sleep(1000);
        system("cls");
        for ( int i = 0; i < arr_size; i++){
            cout<< "arr[" << i<< "] = "<< arr[i] << endl;

        }
    }
    DeleteCriticalSection(&critical_s);
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    return 0;

}








