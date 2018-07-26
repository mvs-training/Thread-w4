#pragma once
#include"Model.h"
class Controller
{
private:
	Model m;
public:
	Controller();
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
	void Error();
	void setNguoidung(string);
	string getNguoidung();
	~Controller();
};

