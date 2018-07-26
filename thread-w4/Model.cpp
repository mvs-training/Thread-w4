#include "stdafx.h"
#include "Model.h"
#include <iostream>
#include <string>
#include<conio.h>
#include <vector>
using namespace std;

Model::Model()
{

}
void Model::ConnectDB() {
	rc = sqlite3_open("MyDb.db", &db);
}
void Model::DisConnectDB() {
	sqlite3_close(db);
}
void Model::setNguoidung(string s) {
	nguoidung = s;
}
string Model::getNguoidung() {
	return nguoidung;
}
int Model::DangNhap() {
	string taikhoan;
	string matkhau;
	cout << "Nhap tai khoan:";
	cin >> taikhoan;

	cout << "Nhap mat khau:";
	cin >> matkhau;
	string sqlSelect = "SELECT taiKhoan FROM Nguoidung WHERE taiKhoan=";
	sqlSelect = sqlSelect + "'" + taikhoan + "'" + " AND matKhau='" + matkhau + "';";
	ConnectDB();

	rc = sqlite3_get_table(db, sqlSelect.c_str(), &results, &rows, &columns, &error);

	if (rc)
	{
		DisConnectDB();
		return 0;
	}
	if (rows == 1) {
		setNguoidung(taikhoan);
		DisConnectDB();
		return 1;

	}
	DisConnectDB();
	return -1;
}
int Model::DangKyTK() {
	string taikhoan;
	string matkhau;
	string hoten;
	string diachi;
	cout << "Nhap tai khoan can dang ky:";
	cin >> taikhoan;
	cout << "Nhap mat khau can dang ky:";
	cin >> matkhau;
	cin.ignore();
	cout << "Nhap ho ten:";
	getline(cin, hoten);
	cout << "Nhap dia chi:";
	getline(cin, diachi);
	ConnectDB();
	string sqlInsert = "INSERT INTO Nguoidung VALUES('" + (string)taikhoan + "','" + (string)matkhau + "','" + (string)hoten + "','" + (string)diachi + "');";
	rc = sqlite3_get_table(db, sqlInsert.c_str(), &results, &rows, &columns, &error);
	if (rc)
	{
		DisConnectDB();
		return 0;
	}

	DisConnectDB();
	return 1;
}
void Model::DangXuat() {
	setNguoidung("");
}
int Model::AddFriend() {
	string taikhoan;
	cout << "Nhap chinh xac TAI KHOAN can AddFriend:";
	cin >> taikhoan;
	ConnectDB();
	//KIEM TRA XEM TAI KHOAN CAN ADDFRIEND CO TON TAI KO
	string sql = "SELECT taiKhoan FROM Nguoidung WHERE taiKhoan='" + taikhoan + "';";
	rc = sqlite3_get_table(db, sql.c_str(), &results, &rows, &columns, &error);
	if (rc)
	{
		return 0;
	}
	else if (rows == 0) {
		return -1;
	}
	//NEU TAI KHOAN CAN ADDFRIEND TON TAI THI TIEN HANH LAM CAC BUOC DUOI
	else if (rows == 1) {
		//KIEM TRA XEM TAI KHOAN CAN ADDFRIEND DA CO TRONG BANG TRANG THAI VOI TAI KHOAN DANG NHAP HAY CHUA NEU CO THI TIEN HANH UPDATE THANH BAN BE
		string sqlSelect = "SELECT nguoiDung1,nguoiDung2 FROM Trangthai WHERE nguoiDung1='" + getNguoidung() + "' AND nguoiDung2='" + taikhoan + "';";
		rc = sqlite3_get_table(db, sqlSelect.c_str(), &results, &rows, &columns, &error);
		//NEU 2 TAI KHOAN NAY DA CO TRONG 1 HANG CUA BANG TRANG THAI THI TIEN HANH UPDATE
		if (rows == 1) {
			string sqlUpdate1 = "UPDATE Trangthai SET trangThai='ban be' WHERE nguoiDung1='" + getNguoidung() + "' AND nguoiDung2='" + taikhoan + "';";
			rc = sqlite3_exec(db, sqlUpdate1.c_str(), NULL, NULL, &error);
			if (rc) {
				return 0;
			}
			string sqlUpdate2 = "UPDATE Trangthai SET trangThai='ban be' WHERE nguoiDung2='" + getNguoidung() + "' AND nguoiDung1='" + taikhoan + "';";
			rc = sqlite3_exec(db, sqlUpdate2.c_str(), NULL, NULL, &error);
			if (rc) {
				return 0;
			}
			return 1;
		}
		//NEU 2 TAI KHOAN NAY CHUA CO TRONG BANG TRANGTHAI THI TIEN HANH INSERT VOI TRANG THAI LA BAN BE
		else if (rows == 0) {
			string sqlInsert1 = "INSERT INTO Trangthai VALUES('" + getNguoidung() + "','" + taikhoan + "','ban be');";
			rc = sqlite3_exec(db, sqlInsert1.c_str(), NULL, NULL, &error);
			if (rc) {
				return 0;
			}
			string sqlInsert2 = "INSERT INTO Trangthai VALUES('" + taikhoan + "','" + getNguoidung() + "','ban be');";
			rc = sqlite3_exec(db, sqlInsert2.c_str(), NULL, NULL, &error);
			if (rc) {
				return 0;
			}

		}

	}
	DisConnectDB();
	return 1;
}
int Model::Block() {
	string taikhoan;
	cout << "Nhap chinh xac TAI KHOAN can Block:";
	cin >> taikhoan;
	ConnectDB();
	//KIEM TRA XEM TAI KHOAN CAN BLOCK CO TON TAI KO
	string sql = "SELECT taiKhoan FROM Nguoidung WHERE taiKhoan='" + taikhoan + "';";
	rc = sqlite3_get_table(db, sql.c_str(), &results, &rows, &columns, &error);
	if (rc)
	{
		return 0;
	}
	else if (rows == 0) {
		return -1;
	}
	//NEU TAI KHOAN CAN BLOCK TON TAI THI TIEN HANH LAM CAC BUOC DUOI
	else if (rows == 1) {
		//KIEM TRA XEM TAI KHOAN CAN BLOCK DA CO TRONG BANG TRANG THAI VOI TAI KHOAN DANG NHAP HAY CHUA NEU CO THI TIEN HANH UPDATE THANH BAN BE
		string sqlSelect = "SELECT nguoiDung1,nguoiDung2 FROM Trangthai WHERE nguoiDung1='" + getNguoidung() + "' AND nguoiDung2='" + taikhoan + "';";
		rc = sqlite3_get_table(db, sqlSelect.c_str(), &results, &rows, &columns, &error);
		//NEU 2 TAI KHOAN NAY DA CO TRONG 1 HANG CUA BANG TRANG THAI THI TIEN HANH UPDATE
		if (rows == 1) {
			string sqlUpdate1 = "UPDATE Trangthai SET trangThai='block' WHERE nguoiDung1='" + getNguoidung() + "' AND nguoiDung2='" + taikhoan + "';";
			rc = sqlite3_exec(db, sqlUpdate1.c_str(), NULL, NULL, &error);
			if (rc) {
				return 0;
			}
			string sqlUpdate2 = "UPDATE Trangthai SET trangThai='block' WHERE nguoiDung2='" + getNguoidung() + "' AND nguoiDung1='" + (string)taikhoan + "';";
			rc = sqlite3_exec(db, sqlUpdate2.c_str(), NULL, NULL, &error);
			if (rc) {
				return 0;
			}
			return 1;
		}
		//NEU 2 TAI KHOAN NAY CHUA CO TRONG BANG TRANGTHAI THI TIEN HANH INSERT VOI TRANG THAI LA BAN BE
		else if (rows == 0) {
			string sqlInsert1 = "INSERT INTO Trangthai VALUES('" + getNguoidung() + "','" + taikhoan + "','block');";
			rc = sqlite3_exec(db, sqlInsert1.c_str(), NULL, NULL, &error);
			if (rc) {
				return 0;
			}
			string sqlInsert2 = "INSERT INTO Trangthai VALUES('" + (string)taikhoan + "','" + getNguoidung() + "','block');";
			rc = sqlite3_exec(db, sqlInsert2.c_str(), NULL, NULL, &error);
			if (rc) {
				return 0;
			}

		}

	}
	DisConnectDB();
	return 1;
}
int Model::GuiTinNhan1() {
	string taikhoan;
	cout << "Nhap tai khoan can gui TIN NHAN:";
	cin >> taikhoan;
	ConnectDB();
	//KIEM TRA XEM TAI KHOAN CAN GUI TIN NHAN CO TON TAI KO
	string sql = "SELECT taiKhoan FROM Nguoidung WHERE taiKhoan='" + taikhoan + "';";
	rc = sqlite3_get_table(db, sql.c_str(), &results, &rows, &columns, &error);
	if (rc)
	{
		DisConnectDB();
		return 0;
	}
	else if (rows == 0) {
		DisConnectDB();
		return -1;
	}
	//kiem tra xem tai khoan co bi block hay ko, neu bi block thi ko the gui tin nhan
	string sqlSelect = "SELECT * FROM Trangthai WHERE nguoiDung1='" + getNguoidung() + "' AND nguoiDung2='" + taikhoan + "' AND trangThai='block';";
	rc = sqlite3_get_table(db, sqlSelect.c_str(), &results, &rows, &columns, &error);
	if (rc) {
		DisConnectDB();
		return 0;

	}
	if (rows == 1) {
		DisConnectDB();
		return -2;
	}
	string noidung;
	cout << "nhap noi dung tin nhan can gui di:";
	cin.ignore();

	getline(cin, noidung);
	string sqlMess = "INSERT INTO Messenger VALUES('" + getNguoidung() + "','" + taikhoan + "','" + noidung + "','chua doc');";

	rc = sqlite3_exec(db, sqlMess.c_str(), NULL, NULL, &error);
	if (rc) {
		DisConnectDB();
		return 0;
	}
	return 1;
	DisConnectDB();
}
int Model::XemCacTinNhanDaGui() {
	ConnectDB();
	string sqlSelect = "SELECT * FROM MESSENGER WHERE nguoiDung1='" + getNguoidung() + "';";
	rc = sqlite3_get_table(db, sqlSelect.c_str(), &results, &rows, &columns, &error);
	if (rc) {
		DisConnectDB();
		return 0;
	}
	else
	{
		// Display Table

		for (int rowCtr = 1; rowCtr <= rows; ++rowCtr)
		{
			for (int colCtr = 0; colCtr < columns; ++colCtr)
			{
				// Determine Cell Position
				int cellPosition = (rowCtr * columns) + colCtr;

				// Display Cell Value
				cout.width(12);
				cout.setf(ios::left);
				if (colCtr == 0) {
					cout << "Nguoi gui:";
				}
				if (colCtr == 1) {
					cout << "Nguoi nhan:";
				}
				if (colCtr == 2) {
					cout << "Noi dung tin nhan:";
				}
				if (colCtr == 3) {
					cout << "Trang thai tin nhan:";
				}
				cout << results[cellPosition] << endl;
			}

			// End Line
			cout << endl;


		}
		DisConnectDB();
	}
	return 1;
}
int Model::GuiTinNhan2() {
	ConnectDB();
	cout << "Bam Ctrl +L de chon nguoi muon gui tin nhan:" << endl;
	char c = getch();
	if (c == 12) {
		string sqlSelect = "SELECT nguoiDung2 FROM Trangthai WHERE nguoiDung1='" + getNguoidung() + "' AND trangThai='ban be';";
	
		rc = sqlite3_get_table(db, sqlSelect.c_str(), &results, &rows, &columns, &error);
		if (rc) {
			DisConnectDB();
			return 0;
		}
		if (rows == 0) {
			cout << "Khong co ban be nao" << endl;
			return -1;
		}
		cout << "Danh sach ban be:" << endl;
		int cellPosition;
		for (int rowCtr = 1; rowCtr <= rows; ++rowCtr)
		{
			for (int colCtr = 0; colCtr < columns; ++colCtr)
			{
				// Determine Cell Position
				cellPosition = (rowCtr * columns) + colCtr;
				cout << cellPosition << ". " << results[cellPosition] << endl;

			}

			// End Line
			cout << endl;


		}
		cout << "Chon so thu tu cua nguoi can gui tin nhan:";
		int chon;
		while (true) {
			cin >> chon;
			if (chon >= 1 && chon <= cellPosition) break;
		}
		cout << "TO: " << (string)results[chon] << endl;
		string taikhoan = (string)results[chon];
		string noidung;
		cout << "Nhap noi dung tin nhan:";
		cin.ignore();
		getline(cin, noidung);
		string sqlMess = "INSERT INTO Messenger VALUES('" + getNguoidung() + "','" + taikhoan + "','" + noidung + "','chua doc');";

		rc = sqlite3_exec(db, sqlMess.c_str(), NULL, NULL, &error);
		if (rc) {
			DisConnectDB();
			return 0;
		}
		return 1;
	}
	DisConnectDB();
	return -1;
}
int Model::XemTinNhanDen() {
	ConnectDB();
	string sqlSelect = "SELECT * FROM MESSENGER WHERE nguoiDung2='" + getNguoidung() + "';";
	rc = sqlite3_get_table(db, sqlSelect.c_str(), &results, &rows, &columns, &error);
	if (rc) {
		DisConnectDB();
		return 0;
	}
	else
	{
		// Display Table

		for (int rowCtr = 1; rowCtr <= rows; ++rowCtr)
		{
			for (int colCtr = 0; colCtr < columns; ++colCtr)
			{
				// Determine Cell Position
				int cellPosition = (rowCtr * columns) + colCtr;

				// Display Cell Value
				cout.width(12);
				cout.setf(ios::left);
				if (colCtr == 0) {
					cout << "Nguoi gui:";
				}
				if (colCtr == 1) {
					cout << "Nguoi nhan:";
				}
				if (colCtr == 2) {
					cout << "Noi dung tin nhan:";
				}
				if (colCtr == 3) {
					cout << "Trang thai tin nhan:";
				}
				cout << results[cellPosition] << endl;
			}

			// End Line
			cout << endl;


		}
		// update lai bang messsenger vi cac tin nhac deu da duoc doc
		string sqlUpdate = "UPDATE Messenger SET Trangthai='da doc' WHERE nguoiDung2='" + getNguoidung() + "';";
		rc = sqlite3_exec(db, sqlUpdate.c_str(), NULL, NULL, &error);
		if (rc) {
			DisConnectDB();
			return 0;
		}

	}
	DisConnectDB();
	return 1;
}
void Model::DanhSachBanbe() {
	//Danh sach ban be mac dinh
	string sql = "SELECT nguoiDung2 FROM Trangthai WHERE nguoiDung1='" + getNguoidung() + "' AND " + "trangThai='ban be';";
	ConnectDB();
	rc = sqlite3_get_table(db, sql.c_str(), &results, &rows, &columns, &error);
	if (rc) {
		cout << "Loi ko lay duoc data: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_free(error);
	}
	else
	{
		// Display Table
		cout << "Danh sach ban be:" << endl;
		for (int rowCtr = 1; rowCtr <= rows; ++rowCtr)
		{
			for (int colCtr = 0; colCtr < columns; ++colCtr)
			{
				// Determine Cell Position
				int cellPosition = (rowCtr * columns) + colCtr;

				// Display Cell Value
				cout.width(12);
				cout.setf(ios::left);

				cout << results[cellPosition] << endl;
			}

			// End Line
			cout << endl;


		}
	}
	cout << "An ctrl+C de xap xep lai danh sach ban be:" << endl;
	char c = getch();
	if (c == 3) {
		string sqlSelect = "SELECT DISTINCT  thanhPho FROM Nguoidung;";

		rc = sqlite3_get_table(db, sqlSelect.c_str(), &results, &rows, &columns, &error);
		vector<string> thanhpho;
		if (rc) {
			cout << "Loi: " << sqlite3_errmsg(db) << endl << endl;
			sqlite3_free(error);
		}
		for (int rowCtr = 1; rowCtr <= rows; ++rowCtr)
		{
			thanhpho.push_back(results[rowCtr]);
		}
		for (int i = 0; i < thanhpho.size(); i++) {
			string sqlSelectND = "SELECT Trangthai.nguoiDung2 FROM Nguoidung,Trangthai WHERE Trangthai.nguoiDung1='" + getNguoidung() + "' AND Trangthai.nguoiDung2=Nguoidung.taiKhoan AND Nguoidung.thanhPho='" + thanhpho[i] + "' AND Trangthai.trangThai='ban be';";
			rc = sqlite3_get_table(db, sqlSelectND.c_str(), &results, &rows, &columns, &error);
			if (rc) {
				cout << "Loi: " << sqlite3_errmsg(db) << endl << endl;
				sqlite3_free(error);
			}
			if (rows > 0) {
				cout << thanhpho[i] << endl;
			}
			for (int rowCtr = 1; rowCtr <= rows; ++rowCtr) {
				cout << rowCtr << "." << results[rowCtr] << endl;
			}

		}

	}

}

void Model::Error() {
	cout << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
	sqlite3_free(error);
}

Model::~Model()
{
}
