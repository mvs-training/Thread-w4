#include "stdafx.h"
#include "Controller.h"
#include"Model.h"


Controller::Controller()
{
}
void Controller::ConnectDB() {
	m.ConnectDB();
}
void Controller::DisConnectDB() {
	m.DisConnectDB();
}
int Controller::DangNhap() {
	return m.DangNhap();
}
int Controller::DangKyTK() {
	return m.DangKyTK();
}
void Controller::DangXuat() {
	m.DangXuat();
}
int Controller::AddFriend() {
	return m.AddFriend();
}
int Controller::Block() {
	return m.Block();
}
int Controller::GuiTinNhan1() {
	return m.GuiTinNhan1();
}
int Controller::GuiTinNhan2() {
	return m.GuiTinNhan2();
}
int Controller::XemCacTinNhanDaGui() {
	return m.XemCacTinNhanDaGui();
}
int Controller::XemTinNhanDen() {
	return m.XemTinNhanDen();
}
void Controller::DanhSachBanbe() {
	m.DanhSachBanbe();
}

void Controller::Error() {
	m.Error();
}
void Controller::setNguoidung(string s) {
	m.setNguoidung(s);
}
string Controller::getNguoidung() {
	return m.getNguoidung();
}
Controller::~Controller()
{
}
