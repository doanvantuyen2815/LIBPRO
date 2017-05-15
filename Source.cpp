#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <iomanip>
#pragma warning(disable:4996)
using namespace std;
class NguoiDung {
private:
public:
	char MasoNguoiDung[5];
	int sCMND;
	char tenNguoiDung[30];
	char ngaySinh[15];
	char diaChi[50];
	char tenDangNhap[30];
	char MatKhau[20];
	bool trangThai = 1;
	int chucVu;
	int dem = 0;

	void doc(fstream&);
	void ghi(fstream&);
	void nhap();
};
void NguoiDung::nhap() {
	cout << "Nhap ma so CMND: "; cin >> sCMND; cin.ignore();
	cout << "Nhap ho ten: "; cin.getline(tenNguoiDung, 30);
	cout << "Nhap ngay sinh: "; cin.getline(ngaySinh, 12);
	cout << "Nhap dia chi: "; cin.getline(diaChi, 20);
	cout << "Nhap ten Tai khoan: "; cin.getline(tenDangNhap, 30);
	cout << "Nhap Mat khau: "; cin.getline(MatKhau, 20);
	cout << "Nhap ma Chuc Vu: "; cin >> chucVu;
}
void NguoiDung::ghi(fstream &ofs) {
	ofs.write(reinterpret_cast< const char * > (this), sizeof(NguoiDung));
}
void NguoiDung::doc(fstream &ifs) {
	ifs.read(reinterpret_cast< char * > (this), sizeof(NguoiDung));
}
class Quyen {
public:
	unsigned int stt;
	bool DocGia = 0;
	bool ThuThu = 0;
	bool Admin = 0;
	char tenQuyen[100] = "";

	void doc(fstream&);
	void ghi(fstream&);
};
void Quyen::ghi(fstream &ofs) {
	ofs.write(reinterpret_cast< const char * > (this), sizeof(NguoiDung));
}
void Quyen::doc(fstream &ifs) {
	ifs.read(reinterpret_cast< char * > (this), sizeof(NguoiDung));
}
int TruyXuatNgDung(NguoiDung v[]) {
	fstream inFile("UserData.DAT", ios::in);
	int dem = 0;
	while (!inFile.eof()) {
		v[dem].doc(inFile);
		dem++;
	}
	/*
	for (int i=0; i<dem-1; i++){
	cout << "sCMND: " << v[i].sCMND << endl;
	cout << "tenNguoiDung: " << v[i].tenNguoiDung << endl;
	cout << "ngaySinh: " << v[i].ngaySinh << endl;
	cout << "diaChi: " << v[i].diaChi << endl;
	cout << "Ten Tai khoan: " << v[i].tenDangNhap <<endl;
	cout << "Chuc vu: ";
	if (v[i].chucVu == 1) cout << "Administration" <<endl;
	else if (v[i].chucVu == 2) cout << "Thu Thu" << endl;
	else cout << "Doc Gia" << endl;
	}
	*/
	inFile.close();
	return dem - 1;
}
void CapNhatNgDung(NguoiDung v[]) {
	int m;
	fstream outFile("UserData.DAT", ios::app);
	cout << "Nhap so luong:"; cin >> m;
	for (int i = 0; i<m; i++) {
		cout << "Nhap Du lieu Nguoi thu " << i + 1 << " :" << endl;
		v[i].nhap();
		v[i].ghi(outFile);
		cout << endl;
	}
	outFile.close();
}
int Chucnang(NguoiDung ngDung[], int quyen, int &m, Quyen q[], char tdn[]) {
	char delay[100];
	//#######Quyen 0. Them Nguoi dung#######################################################

	if (quyen == 0) {
		CapNhatNgDung(ngDung);
		m = TruyXuatNgDung(ngDung);
		cout << "Them hoan tat!" << endl;
		
	}

	//#######Quyen 1. Khoa nguoi dung#######################################################

	else if (quyen == 1) {
		system("cls");
		int cm;
		int i;
		int tt = 0;
		fstream outFile("UserData.DAT", ios::out);
		cout << "Nhap so CMND: "; cin >> cm; cin.ignore();
		for (i = 0; i<m; i++) {
			if (cm == ngDung[i].sCMND) {
				ngDung[i].trangThai = 0;
				cout << "Khoa thanh cong!" << endl;
				tt = 1;
			}
			ngDung[i].ghi(outFile);
		}
		if (tt == 0) cout << "Khong tim thay nguoi nay!" << endl;
		outFile.close();
	}

	//#######Quyen 2. Mo Khoa nguoi dung#######################################################

	else if (quyen == 2) {
		system("cls");
		int cm;
		int i;
		int tt = 0;
		fstream outFile("UserData.DAT", ios::out);
		cout << "Nhap so CMND: "; cin >> cm; cin.ignore();
		for (i = 0; i<m; i++) {
			if (cm == ngDung[i].sCMND) {
				ngDung[i].trangThai = 1;
				cout << "Mo Khoa thanh cong!" << endl;
				tt = 1;
			}
			ngDung[i].ghi(outFile);
		}
		if (tt == 0) cout << "Khong tim thay nguoi nay!" << endl;
		outFile.close();
	}
	//#######Quyen 3. Quan ly quyen.########################################################

	else if (quyen == 3) {           //
		system("cls");
		cout << "Bang phan quyen hien tai:" << endl;
		cout << "__________________________________________________________________" << endl;
		cout << setw(5) << left << "|MS" << setw(30) << left << "|Ten Quyen" << setw(10) << left << "|Admin" << setw(10) << left << "|Thu thu" << setw(10) << left << "|Doc gia" << "|" << endl;
		//fstream inFile("Quyen.DAT", ios::in);
		cout << "|____|_____________________________|_________|_________|_________|" << endl;

		int dem = 19;
		/*
		while (!inFile.eof()){
		q[dem].doc(inFile);
		dem++;
		}
		*/
		for (int i = 0; i<dem; i++) {
			cout << "|" << setw(4) << left << q[i].stt << "|" << setw(29) << left << q[i].tenQuyen;
			if (q[i].Admin == 1) cout << "|" << setw(5) << right << "x" << setw(4) << " ";
			else cout << "|" << setw(9) << right << " ";
			if (q[i].ThuThu == 1) cout << "|" << setw(5) << right << "x" << setw(4) << " ";
			else cout << "|" << setw(9) << right << " ";
			if (q[i].DocGia == 1) cout << "|" << setw(5) << right << "x" << setw(4) << " ";
			else cout << "|" << setw(9) << right << " ";
			cout << "|" << endl;
		}
		cout << "|____|_____________________________|_________|_________|_________|" << endl;
		int op;

		cout << "\t1. Sua Quyen." << endl;
		cout << "\t2. Thoat." << endl;
		cout << "\t Nhap Lua chon: "; cin >> op;
		switch (op) {
		case 2: {
			break;
		}
		case 1: {
			int ms;
			cout << "Nhap ma quyen muon sua: "; cin >> ms; cin.ignore();
			for (int i = 0; i<dem; i++) {
				if (ms == q[i].stt) {
					cout << "Nhap ma tran uy quyen(A T D): ";
					cin >> q[i].Admin >> q[i].ThuThu >> q[i].DocGia; cin.ignore();
					break;
				}

			}
			cout << "Da sua thanh cong!" << endl;
			break;
		}
		}
	}

	//#######Quyen 9. Doi mat khau###########################################################################

	else if (quyen == 9) {
		system("cls");
		char mkc[20];
		char mk1[20];
		char mk2[20];
		int kt1 = 0, kt2 = 0;
		for (int i = 0; i<m; i++) {
			if (strcmp(tdn, ngDung[i].tenDangNhap) == 0) {
				while (kt1 == 0) {
					cout << "Nhap mat khau cu: "; cin.getline(mkc, 20);
					if (strcmp(mkc, ngDung[i].MatKhau) == 0) {
						do {
							cout << "Nhap mat khau moi: "; cin.getline(mk1, 20);
							cout << "Nhap lai mat khau moi: "; cin.getline(mk2, 20);
							if (strcmp(mk1, mk2) == 0) {
								strcpy(ngDung[i].MatKhau, mk1);
								kt2 = 1;
							}
							else cout << "Khong khop. Nhap lai: " << endl;
						} while (kt2 == 0);
						cout << "Doi mat khau thanh cong! " << endl;
						kt1 = 1;
					}
					else cout << "Sai mat khau!" << endl;
				}

				break;
			}
		}
		fstream outFile("UserData.DAT", ios::out);
		for (int i = 0; i<m; i++) {
			ngDung[i].ghi(outFile);
		}
		outFile.close();
	}

	//########Quyen 11. Doi mat khau####################################################################3

	else if (quyen == 11) {
		system("cls");
		int cm;
		fstream outFile("UserData.DAT", ios::out);
		cout << "Nhap so CMND: "; cin >> cm; cin.ignore();
		for (int i = 0; i < m; i++) {
			if (cm == ngDung[i].sCMND) {
				strcpy(ngDung[i].MatKhau, "1");
				ngDung[i].ghi(outFile);
				cout << "Mat khau da duoc reset" << endl;
			}
			else cout << "Khong tim thay nguoi nay";
			outFile.close();
		}
	}
	//##########//Quyen 17. Xem danh sach Nguoi dung.########################################################

	else if (quyen == 17) {
		cout << setw(15) << left << "So CMND" << setw(30) << left << "Ho va ten" << setw(15) << left << "Ngay sinh" << setw(30) << left << "Dia chi" << setw(15) << left << "Chuc vu" << setw(15) << left << "Trang thai" << endl;
		m = TruyXuatNgDung(ngDung);
		for (int i = 0; i<m; i++) {
			cout << setw(15) << left << ngDung[i].sCMND << setw(30) << left << ngDung[i].tenNguoiDung << setw(15) << left << ngDung[i].ngaySinh << setw(30) << left << ngDung[i].diaChi << setw(15) << left;
			if (ngDung[i].chucVu == 1) cout << "Administration";
			else if (ngDung[i].chucVu == 2) cout << "Thu Thu";
			else cout << "Doc Gia";
			cout << setw(15) << left;
			if (ngDung[i].trangThai == 1) cout << "Hoat Dong" << endl;
			else cout << "Bi khoa" << endl;
		}

	}

	//##########//Quyen 18. thoat.########################################################

	else if (quyen == 18) {
		system("cls");
		int qq;
		cout << "Ban muon thoat?(yes = 1, no = 0) "; cin >> qq; cin.ignore();
		return qq;
	}
	return 0;
}
int main() {
	/*
	fstream outFile("Quyen.DAT", ios::out);
	Quyen quyen[30];
	for (int i=0; i < 19; i++){
	quyen[i].stt = i;
	cout << "2 : "; cin >> quyen[i].DocGia >> quyen[i].ThuThu >> quyen[i].Admin;cin.ignore();
	cout << "3 : "; cin.getline(quyen[i].tenQuyen,50);
	quyen[i].ghi(outFile);
	}
	//*/
	///*
	Quyen quyen[19];
	quyen[0].stt = 0; quyen[0].Admin = 1; strcpy(quyen[0].tenQuyen, "Them nguoi dung.");
	quyen[1].stt = 1; quyen[1].Admin = 1; strcpy(quyen[1].tenQuyen, "Khoa nguoi dung.");
	quyen[2].stt = 2; quyen[2].Admin = 1; strcpy(quyen[2].tenQuyen, "Mo khoa nguoi dung.");
	quyen[3].stt = 3; quyen[3].Admin = 1; strcpy(quyen[3].tenQuyen, "Quan ly quyen.");
	quyen[9].stt = 9; quyen[9].Admin = quyen[9].ThuThu = quyen[9].DocGia = 1; strcpy(quyen[9].tenQuyen, "Doi mat khau.");
	quyen[11].stt = 11; quyen[11].Admin = 1; strcpy(quyen[11].tenQuyen, "Reset mat khau");
	quyen[17].stt = 17; quyen[17].Admin = quyen[17].ThuThu = 1; strcpy(quyen[17].tenQuyen, "Xem danh sach tai khoan.");
	quyen[18].stt = 18; quyen[18].Admin = quyen[18].ThuThu = quyen[18].DocGia = 1; strcpy(quyen[18].tenQuyen, "Dang xuat.");
	/*
	fstream inFile("Quyen.DAT", ios::in);
	int dem=0;
	while (!inFile.eof()){
	quyen[dem].doc(inFile);
	dem++;
	}
	*/
	NguoiDung ngDung[100];
	char tdn[30];
	//char u[30] = "root\0";
	//char p[20] = "toor\0";
	//CapNhatNgDung(ngDung);
	fstream outFile("UserData.DAT", ios::app);

	while (true) {
		int m, kt = 0, k;
		int chucvu;
		m = TruyXuatNgDung(ngDung);
		int op;
		//cout << m << endl;
		char user[30], pass[20];
		do {
			system("cls");
			cout << "################Dang Nhap################" << endl;
			cout << "Ten Dang Nhap: "; cin.getline(user, 30);
			cout << "Mat Khau: "; cin.getline(pass, 20);
			char u[5] = "root";
			char p[5] = "toor";
			//cout <<ngDung[0].tenDangNhap<<endl;
			//cout << ngDung[0].MatKhau<< endl;
			if (strcmp(user, u) == 0 && strcmp(pass, p) == 0) {
				cout << "Dang nhap thanh cong!" << endl;
				chucvu = 1;
				kt = 1;
			}
			else {
				for (k = 0; k<m; k++) {
					if (strcmp(user, ngDung[k].tenDangNhap) == 0) {
						if (strcmp(pass, ngDung[k].MatKhau) == 0) {
							if (ngDung[k].trangThai == 0) {
								cout << "Tai khoan cua ban da bi khoa! lien he ad de duoc mo lai! " << endl;
								break;
							}
							else {
								cout << "Dang nhap thanh cong!" << endl;
								chucvu = ngDung[k].chucVu;
								strcpy(tdn, ngDung[k].tenDangNhap);
								kt = 1;
								break;
							}
						}
						else {
							cout << "Sai mat khau. Dang nhap that bai!" << endl;
							break;
						}
					}
				}

				if (k == m) {
					cout << "Sai ten dang nhap!" << endl;
				}
			}
		} while (kt != 1);
		do {
			switch (chucvu) {
			case 1: {
				cout << "__________________________________________________________________" << endl;
				cout << "|        Ban dang dang nhap voi tu cach la Administration        |" << endl;
				cout << "|________________________________________________________________|" << endl;
				cout << "|             ################ Menu #################            |" << endl;
				cout << "|________________________________________________________________|" << endl;
				for (k = 0; k<19; k++) {
					if (quyen[k].Admin == 1) {
						cout << setw(5) << left << "|";
						cout << setw(2) << right << quyen[k].stt << ". "
							<< setw(40) << left << quyen[k].tenQuyen
							<< setw(17) << right << "|" << endl;
					}
				}
				cout << "|________________________________________________________________|" << endl;
				cout << "Nhap Lua chon: "; cin >> op;
				kt = Chucnang(ngDung, op, m, quyen, tdn);
				break;
			}
			case 2: {
				cout << "__________________________________________________________________" << endl;
				cout << "|            Ban dang dang nhap voi tu cach la Thu thu           |" << endl;
				cout << "|________________________________________________________________|" << endl;
				cout << "|             ################ Menu #################            |" << endl;
				cout << "|________________________________________________________________|" << endl;
				for (k = 0; k<19; k++) {
					if (quyen[k].ThuThu == 1) {
						cout << setw(5) << left << "|";
						cout << setw(2) << right << quyen[k].stt << ". "
							<< setw(40) << left << quyen[k].tenQuyen
							<< setw(17) << right << "|" << endl;
					}
				}
				cout << "|________________________________________________________________|" << endl;
				cout << "Nhap Lua chon: "; cin >> op; cin.ignore();
				kt = Chucnang(ngDung, op, m, quyen, tdn);
				break;
			}
			default: {
				cout << "__________________________________________________________________" << endl;
				cout << "|            Ban dang dang nhap voi tu cach la Doc gia           |" << endl;
				cout << "|________________________________________________________________|" << endl;
				cout << "|             ################ Menu #################            |" << endl;
				cout << "|________________________________________________________________|" << endl;
				for (k = 0; k<19; k++) {
					if (quyen[k].DocGia == 1) {
						cout << setw(5) << left << "|";
						cout << setw(2) << right << quyen[k].stt << ". "
							<< setw(40) << left << quyen[k].tenQuyen
							<< setw(17) << right << "|" << endl;
					}
				}
				cout << "|________________________________________________________________|" << endl;
				cout << "Nhap Lua chon: "; cin >> op; cin.ignore();
				kt = Chucnang(ngDung, op, m, quyen, tdn);
				break;
			}
			}
		} while (kt != 1);
	}
	//*/
	return 0;
}
