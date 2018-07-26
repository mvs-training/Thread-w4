#include "stdafx.h"
#include <ios>
#include <iostream>
#include "sqlite3.h"
#include "View.h"
#include<Windows.h>
#include"Model.h"
using namespace std;
DWORD WINAPI ThreadProc1(LPVOID lpParam);
DWORD WINAPI ThreadProc2(LPVOID lpParam);
HANDLE ghSemaphore;
Controller c;
int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE aThread[2];
	DWORD ThreadID;
	int i;

	int select;

	int trangthaidangnhap=0;
	do {
		cout << "chon cac chuc nang sau:" << endl;
		cout << "1.Dang nhap" << endl;
		cout << "2.Dang ky" << endl;
		cout << "3.Dang xuat" << endl;
		cout << "4.Add Friend" << endl;
		cout << "5.Block" << endl;
		cout << "6.Gui tin nhan theo cach nhap ten Tai Khoan" << endl;
		cout << "7.Gui tin nhan bang to hop phim Ctrl+L va xem cac tin da gui (2 thread)" << endl;
		//cout << "8.Xem tin nhan da gui" << endl;
		cout << "9.Xem tin nhan den" << endl;
		cout << "10.Xem danh sach ban be" << endl;
		cout << "Ban chon chuc nang:";

		cin >> select;
		switch (select)
		{
		case 1: {
			system("cls");
			if (trangthaidangnhap == 1) {
				cout << "-----------------------" << endl;
				cout << "Ban da dang nhap roi" << endl;
				cout << "-----------------------" << endl;
				break;
			}

			int check = c.DangNhap();
			if (check == 1) {
				cout << "-----------------------" << endl;
				cout << "Dang nhap thanh cong" << endl;
				cout << "-----------------------" << endl;
				
				trangthaidangnhap = 1;
				break;

			}
			if (check == 0) {
				c.Error();
				break;
			}
			if (check == -1) {
				cout << "-----------------------" << endl;
				cout << "Sai ten dang nhap hoac mat khau" << endl;
				cout << "-----------------------" << endl;
			}
			break;
		}
		case 2: {
			system("cls");
			int check = c.DangKyTK();
			if (check == 0) {
				c.Error();
				break;
			}
			else if (check == 1) {
				cout << "-----------------------" << endl;
				cout << "Dang ky thanh cong" << endl;
				cout << "-----------------------" << endl;
				break;
			}

		}
		case 3: {
			system("cls");
			trangthaidangnhap = 0;
			c.DangXuat();
			cout << "-----------------------" << endl;
			cout << "Dang xuat thanh cong" << endl;
			cout << "-----------------------" << endl;
			break;
		}
		case 4: {
			system("cls");
			if (trangthaidangnhap == 0) {
				cout << "-----------------------" << endl;
				cout << "Ban chua dang nhap " << endl;
				cout << "-----------------------" << endl;
				break;
			}
			int check = c.AddFriend();
			if (check == 0) {
				c.Error();
				break;
			}
			if (check == -1) {
				cout << "-----------------------" << endl;
				cout << "Nguoi dung can AddFriend nay ko ton tai " << endl;
				cout << "-----------------------" << endl;
				break;
			}

			cout << "-----------------------" << endl;
			cout << "Addfriend thanh cong " << endl;
			cout << "-----------------------" << endl;

			break;
		}
		case 5: {
			system("cls");
			if (trangthaidangnhap == 0) {
				cout << "-----------------------" << endl;
				cout << "Ban chua dang nhap " << endl;
				cout << "-----------------------" << endl;
				break;
			}
			int check = c.Block();
			if (check == 0) {
				c.Error();
				break;
			}
			if (check == -1) {
				cout << "-----------------------" << endl;
				cout << "Nguoi dung can Block nay ko ton tai " << endl;
				cout << "-----------------------" << endl;
				break;
			}
			cout << "-----------------------" << endl;
			cout << "Addfriend thanh cong " << endl;
			cout << "-----------------------" << endl;
			break;
		}
		case 6: {
			system("cls");
			if (trangthaidangnhap == 0) {
				cout << "------------------------" << endl;
				cout << "Ban chua dang nhap" << endl;
				cout << "------------------------" << endl;
				break;
			}
			int check = c.GuiTinNhan1();
			if (check == 0) {
				c.Error();
				break;
			}
			if (check == -1) {
				cout << "------------------------------------------" << endl;
				cout << "Nguoi dung can gui tin nhan nay ko ton tai " << endl;
				cout << "------------------------------------------" << endl;
				break;
			}
			if (check == -2) {
				cout << "------------------------------------------" << endl;
				cout << "Khong the gui tin nhan cho tai khoan block " << endl;
				cout << "------------------------------------------" << endl;
				break;
			}
			cout << "------------------------" << endl;
			cout << "Gui tin nhan thanh cong" << endl;
			cout << "------------------------" << endl;
			break;
		}
		case 7: {
			system("cls");
			if (trangthaidangnhap == 0) {
				cout << "------------------------" << endl;
				cout << "Ban chua dang nhap" << endl;
				cout << "------------------------" << endl;
				break;
			}
			ghSemaphore = CreateSemaphore(NULL,1,2,NULL);    

			aThread[0] = CreateThread(NULL,	0, (LPTHREAD_START_ROUTINE)ThreadProc1,NULL, 0, & ThreadID); 
			aThread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc2, NULL, 0, &ThreadID);
			WaitForMultipleObjects(2, aThread, TRUE, INFINITE);

			// Close thread and semaphore handles

			for (i = 0; i < 2; i++)
				CloseHandle(aThread[i]);

			CloseHandle(ghSemaphore);
			break;

		}
		
		case 9: {
			system("cls");
			if (trangthaidangnhap == 0) {
				cout << "------------------------" << endl;
				cout << "Ban chua dang nhap" << endl;
				cout << "------------------------" << endl;
				break;
			}
			int check = c.XemTinNhanDen();
			if (check == 0) {
				c.Error();
				break;
			}
			break;
		}
		case 10: {
			system("cls");
			if (trangthaidangnhap == 0) {
				cout << "------------------------" << endl;
				cout << "Ban chua dang nhap" << endl;
				cout << "------------------------" << endl;
				break;
			}
			c.DanhSachBanbe();
			break;
		}
		default:
			cout << "---------------------" << endl;
			cout << "Ban chon sai, Chon lai" << endl;
			cout << "---------------------" << endl;
			break;
		}
	} while (select);
	

	 
return 0;
}

DWORD WINAPI ThreadProc1(LPVOID lpParam)
{

	// lpParam not used in this example
	UNREFERENCED_PARAMETER(lpParam);

	DWORD dwWaitResult;
	BOOL bContinue = TRUE;
	int check;
	while (bContinue)
	{
		// Try to enter the semaphore gate.

		dwWaitResult = WaitForSingleObject(
			ghSemaphore,   // handle to semaphore
			0L);           // zero-second time-out interval

		switch (dwWaitResult)
		{
			// The semaphore object was signaled.
		case WAIT_OBJECT_0:
			// TODO: Perform task
			
			
			 check = c.GuiTinNhan2();
			if (check == 0) {
				c.Error();
				
			}
			else if (check == 1) {
				cout << "------------------------" << endl;
				cout << "Gui tin nhan thanh cong" << endl;
				cout << "------------------------" << endl;
			}
			else {
			cout << "------------------------" << endl;
			cout << "Chua gui duoc tin nhan" << endl;
			cout << "------------------------" << endl;
			}
			bContinue = FALSE;
			
			// Simulate thread spending time on task
			Sleep(5);

			// Release the semaphore when task is finished

			if (!ReleaseSemaphore(
				ghSemaphore,  // handle to semaphore
				1,            // increase count by one
				NULL))       // not interested in previous count
			{
				printf("ReleaseSemaphore error: %d\n", GetLastError());
			}
			break;

			// The semaphore was nonsignaled, so a time-out occurred.
		case WAIT_TIMEOUT:
			
			break;
		}
	}
	return TRUE;
}
DWORD WINAPI ThreadProc2(LPVOID lpParam)
{

	// lpParam not used in this example
	UNREFERENCED_PARAMETER(lpParam);
	int check;
	DWORD dwWaitResult;
	BOOL bContinue = TRUE;

	while (bContinue)
	{
		// Try to enter the semaphore gate.

		dwWaitResult = WaitForSingleObject(
			ghSemaphore,   // handle to semaphore
			0L);           // zero-second time-out interval

		switch (dwWaitResult)
		{
			// The semaphore object was signaled.
		case WAIT_OBJECT_0:
			// TODO: Perform task
		
			
			check = c.XemCacTinNhanDaGui();
			if (check == 0) {
				c.Error();
			
			}		
			// Simulate thread spending time on task
			bContinue = FALSE;
			Sleep(5);

			// Release the semaphore when task is finished

			if (!ReleaseSemaphore(
				ghSemaphore,  // handle to semaphore
				1,            // increase count by one
				NULL))       // not interested in previous count
			{
				printf("ReleaseSemaphore error: %d\n", GetLastError());
			}
			break;

			// The semaphore was nonsignaled, so a time-out occurred.
		case WAIT_TIMEOUT:

			break;
		}
	}
	return TRUE;
}
