#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <iomanip>
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
        bool trangThai=1;
        int chucVu;
        int dem=0;

        void doc(fstream&);
        void ghi(fstream&);
        void nhap();
};
void NguoiDung::nhap(){
    cout << "Nhap ma so CMND: "; cin >> sCMND; cin.ignore();
    cout << "Nhap ho ten: "; cin.getline(tenNguoiDung,30);
    cout << "Nhap ngay sinh: "; cin.getline(ngaySinh, 12);
    cout << "Nhap dia chi: "; cin.getline(diaChi, 20);
    cout << "Nhap ten Tai khoan: "; cin.getline(tenDangNhap, 30);
    cout << "Nhap Mat khau: "; cin.getline(MatKhau, 20);
    cout << "Nhap ma Chuc Vu: "; cin >> chucVu;
}
void NguoiDung::ghi(fstream &ofs){
    ofs.write(reinterpret_cast< const char * > (this), sizeof(NguoiDung));
}
void NguoiDung::doc(fstream &ifs){
    ifs.read(reinterpret_cast< char * > (this), sizeof(NguoiDung));
}
class Quyen{
    public :
        unsigned int stt;
        bool DocGia;
        bool ThuThu;
        bool Admin;
        char tenQuyen[100];

        void doc(fstream&);
        void ghi(fstream&);
};
void Quyen::ghi(fstream &ofs){
    ofs.write(reinterpret_cast< const char * > (this), sizeof(NguoiDung));
}
void Quyen::doc(fstream &ifs){
    ifs.read(reinterpret_cast< char * > (this), sizeof(NguoiDung));
}
int TruyXuatNgDung(NguoiDung v[]){
    fstream inFile("UserData.DAT", ios::in);
    int dem=0;
    while (!inFile.eof()){
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
    return dem-1;
}
void CapNhatNgDung(NguoiDung v[]){
    int m;
    fstream outFile("UserData.DAT", ios::app);
    cout << "Nhap so luong:"; cin >>m;
    for(int i=0; i<m; i++){
        cout << "Nhap Du lieu Nguoi thu "<< i+1 << " :" <<endl;
        v[i].nhap();
        v[i].ghi(outFile);
        cout << endl;
    }
    outFile.close();
}
int Chucnang(NguoiDung ngDung[], int quyen,int &m, Quyen q[]){
char delay[100];
//#######Quyen 0. Them Nguoi dung#######################################################

    if (quyen == 0){
        CapNhatNgDung(ngDung);
        m = TruyXuatNgDung(ngDung);
        cout << "Them hoan tat!" << endl;
        cout << "Nhan phim bat ky de tiep tuc" <<endl;
        cin.getline(delay,100);
    }

//#######Quyen 1. Khoa nguoi dung#######################################################

    else if (quyen == 1){
        int cm;
        int i;
        int tt=0;
        fstream outFile("UserData.DAT", ios::out);
        cout << "Nhap so CMND: "; cin >> cm; cin.ignore();
        for ( i=0; i<m;i++){
            if (cm == ngDung[i].sCMND) {
                ngDung[i].trangThai = 0;
                cout << "Khoa thanh cong!"<< endl;
                tt = 1;
            }
            ngDung[i].ghi(outFile);
        }
        if (tt == 0) cout << "Khong tim thay nguoi nay!"<< endl;
        outFile.close();
        cout << "Nhan phim bat ky de tiep tuc" <<endl;
        cin.getline(delay,100);
    }

//#######Quyen 3. Quan ly quyen.########################################################

    else if (quyen == 3){           //
        cout << "Ma tran quyen hien tai:" << endl;
        cout << setw(5) << left <<"MS" << setw(50) << left << "Ten Quyen" << setw(20) <<left<< "Doi tuong"<< endl;
        fstream inFile("Quyen.DAT", ios::in);
        int dem=0;
        while (!inFile.eof()){
            q[dem].doc(inFile);
            dem++;
        }
        for (int i=0; i<dem-1; i++){
            cout << setw(5) <<left << q[i].stt << setw(50) <<left << q[i].tenQuyen;
            if (q[i].Admin == 1) cout << "|Admin|  ";
            if (q[i].ThuThu == 1) cout <<"|Thu thu|  ";
            if (q[i].DocGia == 1 ) cout<<"|Doc Gia|  ";
            cout << endl;
        }

        int op;
        cout << "\t1. Them Quyen." << endl;
        cout << "\t2. Sua quyen." <<endl;
        cout << "\t Nhap Lua chon: "; cin >> op;
        switch (op){
            case 1: {
                cout << "Nhap ms(khong trung voi ma quyen khac): "; cin >>q[dem-1].stt; cin.ignore();
                cout << "Nhap Ten Quyen: "; cin.getline(q[dem-1].tenQuyen,100); cin.ignore();
                cout << "Nhap ma doi tuong huong quyen(Admin Thu thu Doc Gia): ";cin >> q[dem-1].Admin >> q[dem-1].ThuThu >> q[dem-1].DocGia; cin.ignore();

                fstream outFile("Quyen.DAT", ios::app);
                q[dem-1].ghi(outFile);
                cout << "Them Thanh cong!" << endl;
                dem++;
                outFile.close();
                break;
            }
            case 2: {
                int ms;
                fstream outFile("Quyen.DAT", ios::out);
                cout << "Nhap ma quyen muon sua: "; cin >> ms ; cin.ignore();
                for (int i=0; i<dem-1;i++){
                    if (ms == q[i].stt) {
                        cout << "Nhap ma tran uy quyen(A T D): ";
                        cin >> q[i].Admin >> q[i].ThuThu >> q[i].DocGia; cin.ignore();
                    }
                    q[i].ghi(outFile);

                }
                cout << "Da sua thanh cong!"<< endl;
                outFile.close();
                break;
            }
        }
        cout << "Nhan phim bat ky de tiep tuc" <<endl;
        cin.getline(delay,100);
    }
//##########//Quyen 17. Xem danh sach Nguoi dung.########################################################

    else if (quyen == 17){
        cout << setw(15) << left << "So CMND" << setw(30) << left << "Ho va ten" << setw(15) << left << "Ngay sinh" << setw(30) << left << "Dia chi" << setw(15) << left << "Chuc vu" <<setw(15)<< left <<"Trang thai"<< endl;
        m = TruyXuatNgDung(ngDung);
        for (int i=0; i<m; i++){
            cout << setw(15) << left << ngDung[i].sCMND << setw(30) << left << ngDung[i].tenNguoiDung << setw(15) << left << ngDung[i].ngaySinh << setw(30) << left << ngDung[i].diaChi << setw(15) << left;
            if (ngDung[i].chucVu == 1) cout << "Administration";
            else if (ngDung[i].chucVu == 2) cout << "Thu Thu";
            else cout << "Doc Gia";
            cout << setw(15)<< left;
            if (ngDung[i].trangThai == 1) cout << "Hoat Dong" << endl;
            else cout << "Bi khoa" << endl;
        }
        cout << "Nhan phim bat ky de tiep tuc";
        cin.getline(delay,100);
    }

//##########//Quyen 18. thoat.########################################################

   else if (quyen == 18){
        int qq;
        cout << "Ban muon thoat?(yes = 1, no = 0) "; cin >> qq;
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
    Quyen quyen[30];
    fstream inFile("Quyen.DAT", ios::in);
    int dem=0;
    while (!inFile.eof()){
        quyen[dem].doc(inFile);
        dem++;
    }

    NguoiDung ngDung[100];
    int m, kt=0,k;
    int chucvu;
    //char u[30] = "root\0";
    //char p[20] = "toor\0";
    //CapNhatNgDung(ngDung);
    m = TruyXuatNgDung(ngDung);
    int op;
    //cout << m << endl;
    char user[30], pass[20];
    do{
        cout << "################Dang Nhap################" << endl;
        cout << "Ten Dang Nhap: "; cin.getline(user,30);
        cout << "Mat Khau: "; cin.getline(pass,20);
        char u[5]="root";
        char p[5]="toor";
        //cout <<ngDung[0].tenDangNhap<<endl;
        //cout << ngDung[0].MatKhau<< endl;
        if (strcmp(user, u) == 0 && strcmp(pass,p) == 0){
            cout << "Dang nhap thanh cong!" << endl;
            chucvu = 1;
            kt =1;
        } else {
            for (k=0; k<m; k++){
                if ( strcmp(user, ngDung[k].tenDangNhap) == 0){
                    if (strcmp(pass,ngDung[k].MatKhau)==0) {
                        if (ngDung[k].trangThai == 0){
                            cout << "Tai khoan cua ban da bi khoa! lien he ad de duoc mo lai! " << endl;
                            return -2;
                        }
                        else{
                            cout << "Dang nhap thanh cong!" << endl;
                            chucvu = ngDung[k].chucVu;
                            kt=1;
                            break;
                        }
                    }
                    else {
                        cout << "Sai mat khau. Dang nhap that bai!";
                        break;
                    }
                }
           }

           if (k==m) {
                cout << "Sai ten dang nhap!" << endl;
           }
       }
    } while (kt!=1);
    do {
        switch (chucvu){
            case 1: {
                cout << "Ban dang dang nhap voi tu cach la Administration." << endl;
                cout << "################Menu#################" << endl;
                for (k=0; k<dem;k++){
                    if(quyen[k].Admin == 1) cout << quyen[k].stt << ". " << quyen[k].tenQuyen << endl;
                }
                cout << "Nhap Lua chon: "; cin >> op;
                kt = Chucnang(ngDung,op,m,quyen);
                break;
            }
            case 2: {
                cout << "Ban dang dang nhap voi tu cach la Thu thu." << endl;
                cout << "################Menu#################" << endl;
                for (k=0; k<dem;k++){
                    if(quyen[k].ThuThu == 1) cout << quyen[k].stt << ". " << quyen[k].tenQuyen << endl;
                }
                break;
            }
            default: {
                cout << "Ban dang dang nhap voi tu cach la Doc Gia." << endl;
                cout << "################Menu#################" << endl;
                for (k=0; k<dem;k++){
                    if(quyen[k].DocGia == 1) cout << quyen[k].stt << ". " << quyen[k].tenQuyen << endl;
                }
                break;
            }
        }
    } while (kt != 1);
//*/
    return 0;
}
