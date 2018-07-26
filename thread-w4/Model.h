#pragma once
#include "sqlite3.h"
#include	<iostream>
#include <string>
using namespace std;
class Model
{
private:
	int rc;
	char *error;
	char **results = NULL;
	int rows, columns;
	sqlite3 *db;
	string nguoidung;
public:
	Model();
	void ConnectDB();
	void DisConnectDB();
	int DangKyTK();
	int DangNhap();
	void DangXuat();
	void SuaTTBanBe();
	int AddFriend();
	int Block();
	void DanhSachBanbe();
	int GuiTinNhan1();
	int GuiTinNhan2();
	int XemCacTinNhanDaGui();
	int XemTinNhanDen();
	void ReplyTinNhan();
	void ThongTinBanBe();
	void DanhSachBanBeTime();
	void DanhSachBanBeCity();
	void setNguoidung(string);
	string getNguoidung();
	void Error();
	~Model();
};

