#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream> // stringstream iss iss�� ���忡�� ���鹮�ڸ� �������� ���� 
#include <iomanip> // setw(��ü�ʺ�), setfill(����������ä���)

/*
* ����Ʈ�������(�Ǽ���)/ �����뿩�� ���α׷� ver 0.1
* tool: DevC++
* compiler: Mingw64, TDM GCC 4.9.2
* version: c++11
* �ۼ��� : ������_202122852

* �α��� ���
- �α��� ������� ����ڸ��� �ٸ� ������ �ٷ�
- ȸ������ ���̵� ������� �������� ó��

* ������ ���
- ���� �߰�
- ���� ����
- ���� ����
- �������� �ο� (�����ڰ���or����ڰ������� ��ȯ)
- ���� ����
- ����ϱ�
- �κ�(�α���ȭ������ ���ư���)

* ����� ���
- ���� �뿩
- ���� �ݳ�
- ���� �˻�
- �뿩���� ���� ����
- �ܾ� ����
- ���� ����
- ����ϱ�
- �κ�(�α���ȭ������ ���ư���)

* ��ü�� �� ���� �� ���� ���� ���� ���� ����ó�� "setter"
* �Է� �� �߸��� �ڷ��� ����ó��
* �߸��� �޴����� ����ó��
* �����迭 ������� ��������, ���� ���� ���� �� �迭 ũ�� �ø���

* ���� ���� �� �α��� ��
������ ���� ID: admin, PW: admin
����� ���� ID: user, PW: user
�׽�Ʈ �ÿ��� �ܼ�â�� ��ü ȭ������ ���ֽø� �����ϰڽ��ϴ�.

// 1.Video_info(���� ����), 2.User_accnt(����), 3.User_rental_video(������ �뿩�� ����)
// 1. �ڵ�, ����, ����, �帣, �󿵽ð�, ��������, �뿩����, ���
// 2. ���̵�, ���, �̸�, �̸���, ����, ����, �ݾ�, ����Ʈ, �뿩����, �뿩�뷮, ��������, ��ũ
// 3. ���� �ڵ�
�׽�Ʈ ������  ��� �� ������� �� ����Դϴ�.
*/

using namespace std;

class Video {
	private:
		string video_code; // ���� �ڵ�
		string name; //����
		string director; //����
		string genre; //�帣
		int running_time; //�󿵽ð�
		int age_limit; //���� ����
		int price; //�뿩 ����
		int amount; // ���
		// 1. �ڵ�, ����, ����, �帣, �󿵽ð�, ��������, �뿩����, ���
	public:
		// ������ �� ����ó��
		Video(string code="None", string _name="None", string dir="None", string _gen="None",
		      int time=0, int _age=0, int _price=0, int _amount=0) {
			video_code = code;
			name = _name;
			director = dir;
			genre = _gen;
			if(time < 0) {
				time = 0;
			}
			running_time = time;
			if(_age < 0) {
				_age = 0;
			}
			age_limit = _age;
			if(_price < 0) {
				_price = 0;
			}
			price = _price;
			if(_amount < 0) {
				_amount = 0;
			}
			amount = _amount;
		}
		//Get �Լ���
		string GetVideoCode(void) {
			return video_code;
		}
		string GetVideoName(void) {
			return name;
		}
		string GetDirector(void) {
			return director;
		}
		string GetGenre(void) {
			return genre;
		}
		int GetRunningTime(void) {
			return running_time;
		}
		int GetAgeLimit(void) {
			return age_limit;
		}
		int GetVideoPrice(void) {
			return price;
		}
		int GetVideoAmount(void) {
			return amount;
		}

		//Edit �Լ���
		void EditVideoCode(string code) {
			video_code = code;
		}
		void EditVideoName(string _name) {
			name = _name;
		}
		void EditDirector(string _director) {
			director = _director;
		}
		void EditGenre(string _genre) {
			genre = _genre;
		}
		void EditRunningTime(int time) {
			if(time < 0) {
				time = 0;
			}
			running_time = time;
		}
		void EditAgeLimit(int age) {
			if(age < 0) {
				age = 0;
			}
			age_limit = age;
		}
		void EditVideoPrice(int _price) {
			if(_price < 0) {
				_price = 0;
			}
			price = _price;
		}
		void EditVideoAmount(int _amount) {
			if(_amount < 0) {
				_amount = 0;
			}
			amount = _amount;
		}

		// ���� ���� ���� ����
		int PlusVideoAmount(int plus) {
			amount += plus;
		}
		int MinusVideoAmount(int minus) {
			amount -= minus;
			if (amount < 0) {
				amount = 0;
			}
		}
		// ���� ���� ���
		void ShowVideoInfo() {
			cout << setw(20) << left << "����" << setw(20) << left << "����" << setw(15) << "�帣" << setw(13) << "�󿵽ð�" << setw(13) << "��������" << setw(13) << "����" << setw(13) << "���" << endl;
			cout << "=======================================================================================================" << endl;
			cout << setw(20) << left << name << setw(20) << left << director << setw(15) << genre << setw(13) << running_time << setw(13) << age_limit << setw(13) << price << setw(13) << amount << endl;
			cout << "=======================================================================================================" << endl<<endl;
		}

};

class User {
	private:
		string id; // ���̵�
		string pw; // ��й�ȣ
		string name; // �̸�
		string e_mail; // �̸���
		string sex; // ���� or ����
		int age; //����
		int money; //������ �ݾ�
		int point; //����Ʈ
		string *r_video_arr; // �뿩�� ������ �����ڵ�
		int r_video_cnt; // �뿩�� ���� ����
		int r_video_capacity; // �뿩 ���� ���� �뷮
		int is_admin; //���� ���� ������ 1, ���� 0
		int rank; // ȸ����� ����� 0, �ǹ� 1, ��� 2

		friend Video;
	public:
		User(string _id="None", string _pw="None", string _name="None", string _e_mail="None",
		     string _sex="None", int _age=0, int _money=0,int _point=0, int _r_video_cnt=0, int r_video_capacity=10,
		     int _is_admin=0,int _rank=0) {
			id=_id;
			pw=_pw;
			name=_name;
			if(_sex!="����"||sex!="����") {
				sex="None";
			}
			sex=_sex;
			if(_age<0) {
				_age=0;
			}
			age=_age;
			if(_money<0) {
				_money=0;
			}
			money=_money;
			if(_point<0) {
				_point=0;
			}
			point=_point;
			if(_r_video_cnt<0) {
				_r_video_cnt=0;
			}
			r_video_cnt=_r_video_cnt;
			if(r_video_capacity<0) {
				r_video_capacity=0;
			}
			r_video_capacity=r_video_capacity;
			if(_is_admin<0||_is_admin>1) {
				_is_admin=0;
			}
			is_admin = _is_admin;
			if(_rank<0||_rank>2) {
				_rank=0;
			}
			rank = _rank;
			e_mail = _e_mail;
			r_video_arr = new string[r_video_capacity];
		}

		//Get �Լ���
		string GetId(void) {
			return id;
		}
		string GetPw(void) {
			return pw;
		}
		string GetName(void) {
			return name;
		}
		string GetSex(void) {
			return sex;
		}
		int GetAge(void) {
			return age;
		}
		int GetMoney(void) {
			return money;
		}
		int GetPoint(void) {
			return point;
		}
		int GetIsAdmin(void) {
			return is_admin;
		}
		int GetRank(void) {
			return rank;
		}
		int GetRentalingVideoCnt(void) {
			return r_video_cnt;
		}
		string GetRentalingVideoCode(int idx) {
			return r_video_arr[idx];
		}
		int GetVideoCapacity(void) {
			return r_video_capacity;
		}
		string GetE_mail(void) {
			return e_mail;
		}

		//Edit �Լ���
		void EditId(string _id) {
			id = _id;
		}
		void EditPw(string _pw) {
			pw = _pw;
		}
		void EditName(string _name) {
			name = _name;
		}
		void EditSex(string _sex) {
			sex = _sex;
		}
		void EditAge(int _age) {
			if(_age < 0) {
				_age = 0;
			}
			age = _age;
		}
		void EditE_mail(string str) {
			e_mail = str;
		}

		//money ���� �Լ�
		void PlusMoney(int plus) {
			money += plus;
		}
		void MinusMoney(int minus) {
			money -=  minus;
			if(money < 0) {
				money = 0;
			}
		}

		//Point ���� �Լ�
		void PlusPoint(int plus) {
			point += plus;
		}
		void MinusPoint(int minus) {
			point -= minus;
			if(point < 0) {
				point = 0;
			}
		}

		// ���� �뿩, �ݳ�
		void RentalVideo(string code) {
			if(r_video_capacity < 10) { // ���� �뷮 ����ó��
				r_video_capacity = 10;
			}
			r_video_arr[r_video_cnt++] = code;
			// ���� �迭 ���� 5�� ����
			if(r_video_capacity-5 == r_video_cnt) {
				r_video_capacity += 10;
				string *newarr = new string[r_video_capacity];
				for(int i=0; i<r_video_cnt; i++) {
					newarr[i] = r_video_arr[i];
				}

				delete[] r_video_arr;

				r_video_arr = newarr;
			}
		}

		void ReturnVideo(int idx) {
			for(int i=idx; i<r_video_cnt-1; i++) {
				r_video_arr[i] = r_video_arr[i+1];
			}
			this->MinusVideoCnt(1);
		}

		//��������, ��ũ ����
		int EditIsAdmin(int num) {
			is_admin = num;
		}
		int EditRank(int num) {
			rank = num;
		}

		// �뿩�� ���� ���� ����
		int PlusVideoCnt(int plus) {
			r_video_cnt += plus;
		}
		int MinusVideoCnt(int minus) {
			r_video_cnt -= minus;
			if(r_video_cnt < 0) {
				r_video_cnt = 0;
			}
		}

		// ���� ���� ���
		void ShowUserInfo(void) {
			cout<<"---------------------------------------"<<endl;
			cout<<"ID: "<<id<<" | "<<"PW: "<<pw<<endl;
			cout<<"�̸�: "<<name<<" |"<<"����: "<<sex<<" | "<<"����: "<<age<<endl;
			cout<<"�ݾ�: "<<money<<" | "<<"����Ʈ: "<<point<<" | "<<"�̸���: "<<e_mail<<endl;
			cout<<"---------------------------------------"<<endl<<endl;
		}

		~User() { // ���� �뿩 ���� �����Ҵ� ����
			for(int i=0; i<r_video_capacity; i++) {
				delete r_video_arr;
			}
			delete[] r_video_arr;
		}
};

class VideoRentalHandler {
	private:
		Video **video_arr; // ���� �迭
		int video_cnt; // ���� ����
		int video_capacity; // ���� �迭 ���뷮

		User **accnt_arr; // ���� ���� �迭
		int accnt_cnt; // ���� ���� �ο� ��
		int accnt_capacity; // ���� �迭 ���뷮
	public:
		// ������
		VideoRentalHandler(int video = 10, int accnt = 10)
			: video_cnt(0), accnt_cnt(0), video_capacity(video), accnt_capacity(accnt) {

			video_arr = new Video*[video_capacity];
			accnt_arr = new User*[accnt_capacity];
		}

		// ���� �α���, ȸ������
		void Load(void); // ����, ���� �ܺο��� �ε�
		void Save(void); // ������ ���� �ܺο� ����
		void Login(void);
		void CreateAccnt(void);
		void Loby(void);

		// ������ ���
		void AddVideo(void); // ���� �߰�
		void EditVideo(void); // ���� ���� ����
		void DeleteVideo(void); // ���� ����
		void AdminAuthority(void); // ������ ���� �ο�
		void AdminMenu(int user_idx); //�����ڿ� �޴�
		void ManageRental(void); // �뿩�� ���� ����

		// ����� ���
		void RentalVideo(int user_idx); // ���� �뿩
		void ReturnVideo(int user_idx); // ���� �ݳ�
		void ShowRentalingVideo(int user_idx); // �뿩 ���� ���� ����
		void ManageMoney(int user_idx); // �ܾ� ����
		void UserMenu(int user_idx); // ����ڿ� �޴�

		// ���� ���
		void SearchVideo(void); // ���� �˻�
		void ManageAccnt(int user_idx); // ���� ����(id,pw)
		void SetConsole(void); // �ܼ� ũ��, ��ġ, Ÿ��Ʋ ����

		// ��ϵ� ��� ���� ���
		void ShowAllVideoInfo(void) {
			if(video_cnt == 0) {
				cout<<"�ý��� �� ��ϵ� ������ �����ϴ�."<<endl;
			}
			for(int i=0; i<video_cnt; i++) {
				cout<<"["<<i<<"]"<<endl;
				video_arr[i]->ShowVideoInfo();
			}
		}

		// ��ϵ� ��� ���� ���
		void ShowAllUserInfo(void) {
			if(accnt_cnt == 0) {
				cout<<"�ý��� �� ��ϵ� ����ڰ� �����ϴ�."<<endl;
			}
			for(int i=0; i<accnt_cnt; i++) {
				cout<<"["<<i<<"]"<<endl;
				accnt_arr[i]->ShowUserInfo();
			}
		}

		~VideoRentalHandler() {
			for (int i = 0; i < video_capacity; i++) {
				delete video_arr[i]; // ���� �迭�� �� ��� ����
			}
			delete[] video_arr; // ���� �迭 ������ ����

			for (int i = 0; i < accnt_capacity; i++) {
				delete accnt_arr[i]; // ���� ���� �迭�� �� ��� ����
			}
			delete[] accnt_arr; // ���� ���� �迭 ������ ����
		}
};

void VideoRentalHandler::ManageRental(void) {
	int user_cnt=0,capacity=10,choice;
	User **temp_arr = new User*[capacity];

	for(int i=0; i<accnt_cnt; i++) { // �Ϲ� ����� ���� �ӽ� ���� �迭 ����

		if(accnt_arr[i]->GetIsAdmin() == 0) { // �����ڰ� �ƴ�  ������ �迭�� ���

			if(user_cnt==capacity-1) { // ���뷮 ���� �� ����ó��
				User **newarr = new User*[capacity*2];
				for(int i=0; i<user_cnt; i++) {
					newarr[i] = temp_arr[i];
				}

				for(int i=0; i<user_cnt; i++) {
					delete temp_arr[i];
				}
				delete[] temp_arr;

				temp_arr = newarr;
			}
			temp_arr[user_cnt++] = accnt_arr[i]; // �迭�� �߰�
		}
	}

	while(1) {

		cout<<"=== �뿩 ���� ==="<<endl;
		cout<<"[1] ���� �뿩 ��Ȳ ����"<<endl;
		cout<<"[2] ����� �뿩 ��Ȳ ����"<<endl;
		cout<<"[0] �޴��� ���ư���"<<endl;
		cout<<"����: ";
		cin>>choice;
		system("cls");

		switch(choice) {
			case 1:
				for(int i=0; i<video_cnt; i++) {
					cout<<"["<<i<<"]"<<endl;
					cout<<"����: "<<video_arr[i]->GetVideoName()<<endl;
					cout<<"��ȭ �ڵ�: "<<video_arr[i]->GetVideoCode()<<endl;
					cout<<"=== �뿩 �ο� ��� (ID, e-mail) ==="<<endl;
					for(int j=0; j<accnt_cnt; j++) { // j ��ü ������ ��
						for(int k=0; k<accnt_arr[j]->GetRentalingVideoCnt(); k++) { // k �뿩�� ���� ����
							if(video_arr[i]->GetVideoCode()==accnt_arr[j]->GetRentalingVideoCode(k)) {
								cout<<"ID: "<<accnt_arr[j]->GetId()<<", "<<"e-mail: "<<accnt_arr[j]->GetE_mail()<<endl;
							}
						}
					}
					cout<<endl;
				}
				system("PAUSE");
				system("cls");
				break;
			case 2:
				for(int i=0; i<user_cnt; i++) {
					cout<<"["<<i<<"]"<<endl;
					cout<<"�̸�: "<<temp_arr[i]->GetName()<<endl;
					cout<<"�̸���: "<<temp_arr[i]->GetE_mail()<<endl;
					if(temp_arr[i]->GetRentalingVideoCnt() == 0) { // �뿩���϶�
						cout<<" �뿩���� ������ �����ϴ�."<<endl;
					} else if(temp_arr[i]->GetRentalingVideoCnt() > 0) { // �뿩������ ���� ��
						cout<<"�뿩 ���: ";
						for(int j=0; j<temp_arr[i]->GetRentalingVideoCnt(); j++) {
							cout<<temp_arr[i]->GetRentalingVideoCode(j)<<" ";
						}
						cout<<endl;
					}
					cout<<endl;
				}
				system("PAUSE");
				system("cls");
				break;
			case 0:
				cout<<"�޴��� ���ư��ϴ�."<<endl;
				Sleep(500);
				system("cls");
				return;
			default:
				cout<<"�߸��� �Է��Դϴ�."<<endl;
				Sleep(500);
				system("cls");
				continue;
		}
	}
}

void VideoRentalHandler::SetConsole(void) {
// cols: ����, lines: ����  120 40  / 410 145
	system("mode con cols=211 lines=55 | title �����뿩���α׷�(�Ұ�) by Yulgok");
}

void VideoRentalHandler::AddVideo(void) {
	string code, name, dir, genre;
	int time, age, price, amount;
	cin.ignore();
	cout<<"=== ���ο� ������ �߰� ==="<<endl;
	cout<<"�����ڵ�: ";
	getline(cin, code);
	cout<<"�̸�: ";
	getline(cin, name);
	cout<<"����: ";
	getline(cin, dir);
	cout<<"�帣: ";
	getline(cin, genre);
	cout<<"����Ÿ��: ";
	cin>>time;
	cout<<"��������: ";
	cin>>age;
	cout<<"�뿩����: ";
	cin>>price;
	cout<<"���: ";
	cin>>amount;

	if(video_capacity-5 == video_cnt) {
		video_capacity += 10;
		Video **newarr = new Video*[video_capacity];

		for(int i=0; i<video_cnt; i++) {
			newarr[i] = video_arr[i];
		}

		for(int i=0; i<video_cnt; i++) {
			delete video_arr[i];
		}
		delete[] video_arr;

		video_arr = newarr;
	}
// 1. �ڵ�, ����, ����, �帣, �󿵽ð�, ��������, �뿩����, ���
	video_arr[video_cnt++] = new Video(code, name, dir, genre, time, age, price, amount);
	cout<<"���� �߰� �Ϸ�."<<endl;
	Sleep(1000);
	system("cls");
}

void VideoRentalHandler::EditVideo(void) {
	string name, dir, genre;
	int time, age, price, amount;
	int choice, idx;

// ��ü ���� ���
	while(1) {
		ShowAllVideoInfo();
		cout<<"=== ���� ���� ���� ==="<<endl;
		cout<<"[1] �˻��ϱ�"<<endl;
		cout<<"[2] �����ϱ�"<<endl;
		cout<<"[0] �޴� ���ư���"<<endl;
		cout<<"����: ";
		cin>>choice;

		switch(choice) {
			case 1:
				SearchVideo();
				break;
			case 2:
				cout<<"=== ������ ���� �ε��� ���� ==="<<endl;
				cout<<"����: ";
				cin>>idx;
				if(idx < 0 || idx >= video_cnt) {
					cout<<"�ùٸ� �ε����� �Է����ּ���."<<endl;
					Sleep(500);
					system("cls");
					continue;
				}
				while(1) {
					cout<<"=== ������ ������ ���� ==="<<endl;
					cout<<"[1] ���� �̸�"<<endl;
					cout<<"[2] ���� ����"<<endl;
					cout<<"[3] ���� �帣"<<endl;
					cout<<"[4] ���� ����Ÿ��"<<endl;
					cout<<"[5] ���� ��������"<<endl;
					cout<<"[6] ���� �뿩����"<<endl;
					cout<<"[7] ���� ���"<<endl;
					cout<<"[0] �޴��� ���ư���"<<endl;
					cout<<"����: ";
					cin>>choice;
					system("cls");
					cin.ignore();
					switch(choice) {
						case 1:
							cout<<"������ �̸� �Է�"<<endl;
							cout<<"�̸�: ";
							getline(cin, name);
							video_arr[idx]->EditVideoName(name);
							cout<<"������ �Ϸ��߽��ϴ�."<<endl;
							Sleep(500);
							system("cls");
							break;
						case 2:
							cout<<"������ ���� �Է�"<<endl;
							cout<<"����: ";
							getline(cin, dir);
							video_arr[idx]->EditDirector(dir);
							cout<<"������ �Ϸ��߽��ϴ�."<<endl;
							Sleep(500);
							system("cls");
							break;
						case 3:
							cout<<"������ �帣 �Է�"<<endl;
							cout<<"�帣: ";
							getline(cin, genre);
							video_arr[idx]->EditGenre(genre);
							cout<<"������ �Ϸ��߽��ϴ�."<<endl;
							Sleep(500);
							system("cls");
							break;
						case 4:
							cout<<"������ ����Ÿ�� �Է�"<<endl;
							cout<<"����Ÿ��: ";
							cin>>time;
							video_arr[idx]->EditRunningTime(time);
							cout<<"������ �Ϸ��߽��ϴ�."<<endl;
							Sleep(500);
							system("cls");
							break;
						case 5:
							cout<<"������ �������� �Է�"<<endl;
							cout<<"��������: ";
							cin>>age;
							video_arr[idx]->EditAgeLimit(age);
							cout<<"������ �Ϸ��߽��ϴ�."<<endl;
							Sleep(500);
							system("cls");
							break;
						case 6:
							cout<<"������ �뿩���� �Է�"<<endl;
							cout<<"�뿩����: ";
							cin>>price;
							video_arr[idx]->EditVideoPrice(price);
							cout<<"������ �Ϸ��߽��ϴ�."<<endl;
							Sleep(500);
							system("cls");
							break;
						case 7:
							cout<<"������ ��� �Է�"<<endl;
							cout<<"���: ";
							cin>>amount;
							video_arr[idx]->EditVideoAmount(amount);
							cout<<"������ �Ϸ��߽��ϴ�."<<endl;
							Sleep(500);
							system("cls");
							break;
						case 0:
							cout<<"�޴��� ���ư��ϴ�."<<endl;
							Sleep(500);
							system("cls");
							return;
						default:
							cout<<"�߸��� �Է��Դϴ�."<<endl;
							Sleep(500);
							system("cls");
							break;
					}
				}
				break;
			case 0:
				cout<<"�޴��� ���ư��ϴ�."<<endl;
				Sleep(500);
				system("cls");
				return;
			default:
				cout<<"�߸��� �Է��Դϴ�."<<endl;
				Sleep(500);
				system("cls");
				break;
		}
	}


}

void VideoRentalHandler::DeleteVideo(void) {
	int choice, idx;

	while(1) {
		ShowAllVideoInfo();
		cout<<"=== ���� ���� ���� ==="<<endl;
		cout<<"[1] �˻��ϱ�"<<endl;
		cout<<"[2] �����ϱ�"<<endl;
		cout<<"[0] �޴� ���ư���"<<endl;
		cout<<"����: ";
		cin>>choice;
		system("cls");

		switch(choice) {
			case 1:
				SearchVideo();
				break;
			case 2:
				cout<<"=== ������ ���� �ε��� ���� ==="<<endl;
				cout<<"����: ";
				cin>>idx;

				if(idx < 0 || idx >= video_cnt) {
					cout<<"�ùٸ� �ε����� �Է����ּ���"<<endl;
					Sleep(500);
					system("cls");
					continue;
				}
				while(1) {
					cout<<"���� ������ �ǰ���?"<<endl;
					cout<<"[1] ��"<<endl;
					cout<<"[2] �ƴϿ�"<<endl;
					cout<<"����: ";
					cin>>choice;
					if(choice == 1) {}
					else if(choice == 2) {
						cout<<"������ ����մϴ�."<<endl;
						Sleep(500);
						system("cls");
						continue;
					} else {
						cout<<"�߸��� �Է��Դϴ�"<<endl;
						Sleep(500);
						system("cls");
						continue;
					}

					delete video_arr[idx]; // �ش� �ε��� ���� ����
					for (int i = idx; i < video_capacity-1; i++) { // ���� ��ҵ� ��������
						video_arr[i] = video_arr[i + 1];
					}
					video_cnt--; // ���� ���� -1

					cout<<"������ �Ϸ��߽��ϴ�."<<endl;
					Sleep(500);
					system("cls");
					break;
				}
				break;
			case 0:
				cout<<"�޴��� ���ư��ϴ�."<<endl;
				Sleep(500);
				system("cls");
				return;
			default:
				cout<<"�߸��� �Է��Դϴ�."<<endl;
				Sleep(500);
				system("cls");
				break;
		}

	}

}

void VideoRentalHandler::SearchVideo(void) {
	string name, dir, genre;
	int flag=0;
	int choice;
	while(1) {
		flag=0;
		ShowAllVideoInfo();
		cout<<" === ���� �˻��ϱ� ==="<<endl;
		cout<<"[1] �̸� �˻�"<<endl;
		cout<<"[2] ���� �˻�"<<endl;
		cout<<"[3] �帣 �˻�"<<endl;
		cout<<"[0] �޴��� ���ư���"<<endl;
		cout<<"����: ";
		cin>>choice;
		cin.ignore();
		switch(choice) {
			case 1:
				cout<<"�̸�: ";
				getline(cin, name);
				for(int i=0; i<video_cnt; i++) {
					size_t npos = video_arr[i]->GetVideoName().find(name);
					if(npos != string::npos) {
						cout << "*" << endl;
						video_arr[i]->ShowVideoInfo();
						flag=1;
					}
				}
				if(flag==0) {
					cout<<"�ٽ� �õ����ּ���."<<endl;
					Sleep(500);
					system("cls");
				}
				break;
			case 2:
				cout<<"����: ";
				getline(cin, dir);
				for(int i=0; i<video_cnt; i++) {
					size_t npos = video_arr[i]->GetDirector().find(dir);
					if(npos != string::npos) {
						cout << "*" << endl;
						video_arr[i]->ShowVideoInfo();
						flag=1;
					}
				}
				if(flag==0) {
					cout<<"�ٽ� �õ����ּ���."<<endl;
					Sleep(500);
					system("cls");
				}
				break;
			case 3:
				cout<<"�帣: ";
				getline(cin, genre);
				for(int i=0; i<video_cnt; i++) {
					size_t npos = video_arr[i]->GetGenre().find(genre);
					if(npos != string::npos) {
						cout << "*" << endl;
						video_arr[i]->ShowVideoInfo();
						flag=1;
					}
				}
				if(flag==0) {
					cout<<"�ٽ� �õ����ּ���."<<endl;
					Sleep(500);
					system("cls");
				}
				break;
			case 0:
				cout<<"�޴��� ���ư��ϴ�."<<endl;
				Sleep(500);
				system("cls");
				return;
			default:
				cout<<"�߸��� �Է��Դϴ�."<<endl;
				Sleep(500);
				system("cls");
				break;
		}

	}


}

void VideoRentalHandler::AdminAuthority(void) {
	int choice, idx, flag=0;
	string name;

	while(1) {
		ShowAllUserInfo();
		cout<<"������ ���� �ο��ϱ�"<<endl;
		cout<<"[1] ������ �������� ��ȯ"<<endl;
		cout<<"[2] ����� �������� ��ȯ"<<endl;
		cout<<"[3] ����� �˻�"<<endl;
		cout<<"[0] �޴��� ���ư���"<<endl;
		cout<<"����: ";
		cin>>choice;
		system("cls");
		cin.ignore();
		switch(choice) {
			case 0:
				cout<<"�޴��� ���ư��ϴ�."<<endl;
				Sleep(500);
				system("cls");
				return;
			case 1:
				while(1) {
					cout<<"�ش� ������ �ε��� ����"<<endl;
					cout<<"����: ";
					cin>>idx;

					if(idx < 0 || idx >= accnt_cnt) {
						cout<<"�ùٸ� �ε����� �Է����ּ���"<<endl;
						Sleep(500);
						system("cls");
						continue;
					}
					break;
				}

				while(1) {
					cout<<"���� ������ �������� ��ȯ�Ұǰ���?"<<endl;
					cout<<"[1] ��"<<endl;
					cout<<"[2] �ƴϿ�"<<endl;
					cout<<"����: ";
					cin>>choice;
					if(choice == 1) {}
					else if(choice == 2) {
						cout<<"���Ѻο��� ����մϴ�."<<endl;
						Sleep(500);
						system("cls");
						break;
					} else {
						cout<<"�߸��� �Է��Դϴ�"<<endl;
						Sleep(500);
						system("cls");
						continue;
					}

					accnt_arr[idx]->EditIsAdmin(1);
					cout<<"���Ѻο��� �Ϸ��߽��ϴ�."<<endl;
					Sleep(500);
					system("cls");
					break;
				}

				break;
			case 2:
				while(1) {
					cout<<"�ش� ������ �ε��� ����"<<endl;
					cout<<"����: ";
					cin>>idx;

					if(idx < 0 || idx >= accnt_cnt) {
						cout<<"�ùٸ� �ε����� �Է����ּ���"<<endl;
						Sleep(500);
						system("cls");
						continue;
					}
					break;
				}

				while(1) {
					cout<<"���� ����� �������� ��ȯ�Ұǰ���?"<<endl;
					cout<<"[1] ��"<<endl;
					cout<<"[2] �ƴϿ�"<<endl;
					cout<<"����: ";
					cin>>choice;
					if(choice == 1) {}
					else if(choice == 2) {
						cout<<"���Ѻο��� ����մϴ�."<<endl;
						Sleep(500);
						system("cls");
						break;
					} else {
						cout<<"�߸��� �Է��Դϴ�"<<endl;
						Sleep(500);
						system("cls");
						continue;
					}

					accnt_arr[idx]->EditIsAdmin(0);
					cout<<"���Ѻο��� �Ϸ��߽��ϴ�."<<endl;
					Sleep(500);
					system("cls");
					break;
				}
				break;
			case 3:
				cout<<"=== ����� �˻� ==="<<endl;
				cout<<"�̸��Է�: ";
				getline(cin, name);
				for(int i=0; i<accnt_cnt; i++) {
					size_t npos = accnt_arr[i]->GetName().find(name);
					if(npos != string::npos) {
						cout << "*" << endl;
						accnt_arr[i]->ShowUserInfo();
						flag=1;
					}
				}
				if(flag==0) {
					cout<<"�ٽ� �õ����ּ���."<<endl;
					Sleep(500);
					system("cls");
				}
				break;
			default:
				cout<<"�߸��� �Է��Դϴ�"<<endl;
				Sleep(500);
				system("cls");
				break;
		}
	}
}

void VideoRentalHandler::ManageAccnt(int user_idx) {
	int choice, age;
	string id, pw, sex, name;

	while(1) {
		accnt_arr[user_idx]->ShowUserInfo();// �� ���� ����
		cout<<"=== ���� ���� ==="<<endl;
		cout<<"[1] ID ����"<<endl;
		cout<<"[2] PW ����"<<endl;
		cout<<"[3] ���� ����"<<endl;
		cout<<"[4] ���� ����"<<endl;
		cout<<"[5] �̸� ����"<<endl;
		cout<<"[0] �޴��� �̵�"<<endl;
		cout<<"����: ";
		cin>>choice;
		cin.ignore();
		switch(choice) {
			case 1:
				cout<<"=================="<<endl;
				cout<<"������ ID�� �Է�"<<endl;
				cout<<"ID: ";
				getline(cin, id);
				for(int i=0; i<accnt_cnt; i++) {
					if(accnt_arr[i]->GetId() == id) {
						cout<< "�̹� ������ id�� �����մϴ�" <<endl;
						Sleep(500);
						system("cls");
						continue;
					}
				}
				accnt_arr[user_idx]->EditId(id);
				cout<<"ID ����Ϸ�."<<endl;
				Sleep(500);
				system("cls");
				break;
			case 2:
				cout<<"=================="<<endl;
				cout<<"������ PW�� �Է�"<<endl;
				cout<<"PW: ";
				getline(cin, pw);
				accnt_arr[user_idx]->EditPw(pw);
				cout<<"PW ����Ϸ�."<<endl;
				Sleep(500);
				system("cls");
				break;
			case 3:
				while(1) {
					cout<<"=================="<<endl;
					cout<<"������ ������ ����"<<endl;
					cout<<"[1] ����";
					cout<<"[2] ����"<<endl;
					cout<<"����: ";
					cin>>choice;
					if(choice==1) {
						sex = "����";
						break;
					} else if(choice==2) {
						sex = "����";
						break;
					} else {
						cout<<"�ٽ� �Է����ּ���."<<endl;
						Sleep(500);
						system("cls");
						continue;
					}
				}
				accnt_arr[user_idx]->EditSex(sex);
				cout<<"���� ����Ϸ�."<<endl;
				Sleep(500);
				system("cls");
				break;
			case 4:
				cout<<"=================="<<endl;
				cout<<"������ ���̸� �Է�"<<endl;
				cout<<"����: ";
				cin>>age;
				accnt_arr[user_idx]->EditAge(age);
				cout<<"���� ����Ϸ�."<<endl;
				Sleep(500);
				system("cls");
				break;
			case 5:
				cout<<"=================="<<endl;
				cout<<"������ �̸��� �Է�"<<endl;
				cout<<"�̸�: ";
				cin>>name;
				accnt_arr[user_idx]->EditName(name);
				cout<<"�̸� ����Ϸ�."<<endl;
				Sleep(500);
				system("cls");
				break;
			case 0:
				cout<<"�޴��� ���ư��ϴ�."<<endl;
				Sleep(500);
				system("cls");
				return;
			default:
				cout<<"�߸��� �Է��Դϴ�."<<endl;
				Sleep(500);
				system("cls");
				break;
		}
	}

}

void VideoRentalHandler::RentalVideo(int user_idx) {
	int choice, idx;
	User *temp = accnt_arr[user_idx];

	while(1) {
		ShowAllVideoInfo();
		cout<<"=== ���� �뿩 ==="<<endl;
		cout<<"[1] �˻��ϱ�"<<endl;
		cout<<"[2] �뿩�ϱ�"<<endl;
		cout<<"[0] �޴� ���ư���"<<endl;
		cout<<"����: ";
		cin>>choice;

		switch(choice) {
			case 1:
				SearchVideo();
				break;
			case 2:
				cout<<"�뿩�� ������ �ε��� ����"<<endl;
				cout<<"����: ";
				cin>>idx;

				if(idx < 0 || idx >= video_cnt) {
					cout<<"�ùٸ� �ε����� �Է����ּ���"<<endl;
					Sleep(500);
					system("cls");
					continue;
				}

				if(temp->GetAge() < video_arr[idx]->GetAgeLimit()) {
					cout<<"������������ �ش� ������ �뿩�� �� �����ϴ�."<<endl;
					Sleep(500);
					system("cls");
					continue;
				}

				if(video_arr[idx]->GetVideoAmount() == 0) {
					cout<<"�ش� ������ ���� ����� �����ϴ�."<<endl;
					Sleep(500);
					system("cls");
					continue;
				}

				while(1) {
					cout<<"================="<<endl;
					cout<<"�뿩��: "<<video_arr[idx]->GetVideoPrice()<<endl;
					cout<<"�ܾ�: "<<temp->GetMoney()<<endl;
					cout<<"����Ʈ: "<<temp->GetPoint()<<endl;
					cout<<"����Ʈ�� ����ϰڽ��ϱ�? "<<endl<<endl;
					cout<<"[1] ��"<<endl;
					cout<<"[2] �ƴϿ�"<<endl;
					cout<<"[0] �޴��� ���ư���"<<endl;
					cout<<"����: ";
					cin>>choice;
					system("cls");

					switch(choice) {
						case 1:
							cout<<"�ܾ�+����Ʈ�� ����� �����մϴ�."<<endl;
							if(video_arr[idx]->GetVideoPrice() > temp->GetMoney()+temp->GetPoint()) {
								cout<<"�Ѿ��� �����մϴ�. ���� �� �������ּ���"<<endl;
								Sleep(500);
								system("cls");
								return;
							}
							temp->RentalVideo(video_arr[idx]->GetVideoCode()); //����� �뵮 �迭 ����
							temp->MinusMoney(video_arr[idx]->GetVideoPrice()); // �� ���̳ʽ�
							temp->PlusVideoCnt(1); // ���� ���� ī��Ʈ ����
							video_arr[idx]->MinusVideoAmount(1); // ���� ��� 1 ����
							cout<<"���� �뿩�� �Ϸ��߽��ϴ�."<<endl;
							Sleep(1000);
							system("cls");
							return;
							break;
						case 2:
							cout<<"�ܾ����θ� ����� �����մϴ�."<<endl;
							if(video_arr[idx]->GetVideoPrice() > temp->GetMoney()) {
								cout<<"�Ѿ��� �����մϴ�. ���� �� �������ּ���"<<endl;
								Sleep(500);
								system("cls");
								continue;
							}
							cout<<"���� �뿩�� �Ϸ��߽��ϴ�."<<endl;
							temp->RentalVideo(video_arr[idx]->GetVideoCode()); // ���� ����
							temp->MinusMoney(video_arr[idx]->GetVideoPrice());
							temp->PlusVideoCnt(1);
							video_arr[idx]->MinusVideoAmount(1);
							Sleep(1000);
							system("cls");
							return;
							break;
						case 0:
							cout<<"�޴��� ���ư��ϴ�."<<endl;
							Sleep(500);
							system("cls");
							return;
							break;
						default:
							cout<<"�߸��� �Է��Դϴ�."<<endl;
							Sleep(500);
							system("cls");
							continue;
					}
				}
				break;
			case 0:
				cout<<"�޴��� ���ư��ϴ�."<<endl;
				Sleep(500);
				system("cls");
				return;
			default:
				cout<<"�߸��� �Է��Դϴ�."<<endl;
				Sleep(500);
				system("cls");
				break;
		}
	}
}

void VideoRentalHandler::ReturnVideo(int user_idx) {
	int choice, idx;
	User *u = accnt_arr[user_idx];
// ���� �뿩���� ���� ���

	while(1) {
		ShowRentalingVideo(user_idx);
		cout<<"=== ���� �ݳ� ==="<<endl;
		cout<<"[1] �ݳ��ϱ�"<<endl;
		cout<<"[2] �뿩 ���� ���� ����"<<endl;
		cout<<"[0] �޴� ���ư���"<<endl;
		cout<<"����: ";
		cin>>choice;
		system("cls");

		switch(choice) {
			case 1:
				cout<<"�ݳ��� ������ �ε��� ����"<<endl;
				cout<<"����: ";
				cin>>idx; // ������ ���� �迭�� �ε���

				if(idx < 0 || idx >= u->GetRentalingVideoCnt()) {
					cout<<"�ùٸ� �ε����� �Է����ּ���."<<endl;
					Sleep(500);
					system("cls");
					continue;
				}

				for(int i=0; i<video_cnt; i++) { // �ݳ� �� ���� ���� ����
					if(video_arr[i]->GetVideoCode() == u->GetRentalingVideoCode(idx)) {
						video_arr[i]->PlusVideoAmount(1);
					}
				}
				u->ReturnVideo(idx); // ����ڰ� ���� �ݳ�
				cout<<"���� �ݳ� �Ϸ�."<<endl;
				Sleep(500);
				system("cls");
				break;
			case 2:
				ShowRentalingVideo(user_idx);
				break;
			case 0:
				cout<<"�޴��� ���ư��ϴ�."<<endl;
				Sleep(500);
				system("cls");
				return;
			default:
				cout<<"�߸��� �Է��Դϴ�."<<endl;
				Sleep(500);
				system("cls");
				break;
		}
	}
}

void VideoRentalHandler::ManageMoney(int user_idx) {
	int choice;

	while(1) {
		accnt_arr[user_idx]->ShowUserInfo();
		cout<<"=== �ݾ� ���� ==="<<endl;
		cout<<"[1] �� ����"<<endl;
		cout<<"[2] �� ����"<<endl;
		cout<<"[0] �޴� ���ư���"<<endl;
		cout<<"����: ";
		cin>>choice;
		system("cls");

		switch(choice) {
			case 1:
				cout<<"================"<<endl;
				cout<<"������ �ݾ� �Է�"<<endl;
				cout<<"�Է�: ";
				cin>>choice;

				accnt_arr[user_idx]->PlusMoney(choice);

				cout<<"������ �Ϸ�Ǿ����ϴ�."<<endl;
				Sleep(500);
				system("cls");
				break;
			case 2:
				cout<<"������ �ݾ� ����"<<endl;
				cout<<"�Է�: ";
				cin>>choice;

				accnt_arr[user_idx]->MinusMoney(choice);

				cout<<"������ �Ϸ�Ǿ����ϴ�."<<endl;
				Sleep(500);
				system("cls");
				break;
			case 0:
				cout<<"�޴��� ���ư��ϴ�."<<endl;
				Sleep(500);
				system("cls");
				return;
			default:
				cout<<"�߸��� �Է��Դϴ�."<<endl;
				Sleep(500);
				system("cls");
				break;
		}
	}
}


void VideoRentalHandler::Loby(void) {

	int choice;

	Load();

	while(1) {

		cout<< " === ���� �뿩 ���α׷� === " <<endl;
		cout<< " [1] �α��� " <<endl;
		cout<< " [2] ȸ������ " <<endl;
		cout<< " [0] ���� " <<endl;
		cout<<"����: ";
		cin>>choice;
		cin.ignore();
		switch(choice) {
			case 1:
				Login();
				break;
			case 2:
				CreateAccnt();
				break;
			case 0:
				cout << "���α׷��� �����մϴ�" << endl;
				Sleep(1000);
				system("cls");
				return;
			default:
				cout << "�߸��� �Է��Դϴ�" << endl;
				Sleep(1000);
				system("cls");
		}
	}
}

void VideoRentalHandler::CreateAccnt(void) {
	string id,pw,name,sex,e_mail;
	int age, choice;

	cout<<"=== ȸ������ ==="<<endl;
	cout<<"������ ID: ";
	getline(cin, id);
	if(cin.fail()) {
		cout<<"�߸��� �Է��Դϴ�."<<endl;
		return;
	}

	for(int i=0; i<accnt_cnt; i++) {
		if(accnt_arr[i]->GetId() == id) {
			cout<< "�̹� ������ id�� �����մϴ�" <<endl;
			Sleep(1000);
			system("cls");
			return;
		}
	}

	cout<<"================"<<endl;
	cout<<"������ PW: ";
	getline(cin, pw);
	if(cin.fail()) {
		cout<<"�߸��� �Է��Դϴ�."<<endl;
		return;
	}
	cout<<"================"<<endl;
	cout<<"�̸�: ";
	getline(cin, name);
	if(cin.fail()) {
		cout<<"�߸��� �Է��Դϴ�."<<endl;
		return;
	}
	cout<<"================"<<endl;
	cout<<"�̸���: ";
	getline(cin, e_mail);
	if(cin.fail()) {
		cout<<"�߸��� �Է��Դϴ�."<<endl;
		return;
	}

	while(1) {
		cout<<"================"<<endl;
		cout<<"������ �������ּ���."<<endl;
		cout<<"[1] ����, [2] ����"<<endl;
		cout<<"����: ";
		cin>>choice;
		if(choice==1) {
			sex = "����";
			break;
		} else if(choice==2) {
			sex = "����";
			break;
		} else {
			cout<<"�ٽ� �Է����ּ���."<<endl;
			Sleep(500);
			system("cls");
		}
	}

	while(1) {
		cout<<"================"<<endl;
		cout<<"����: ";
		cin>>age;
		if(cin.fail()) {
			cout<<"�߸��� �Է��Դϴ�."<<endl;
			return;
		}
		if(age < 0) {
			cout<<"�ùٸ� �������� �Է����ּ���"<<endl;
			Sleep(1000);
			system("cls");
			continue;
		} else {
			break;
		}
	}

	accnt_arr[accnt_cnt++] = new User(id,pw,name,e_mail,sex,age);
	cout<<"���� ������ �Ϸ��߽��ϴ�."<<endl;
	Sleep(1000);
	system("cls");
}

void VideoRentalHandler::Login(void) {
	string id, pw;
	int user_idx;
	int flag=0; // �α׾ƿ� �� ���

	cout<< "ID : ";
	getline(cin, id);
	cout<< "PW : ";
	getline(cin, pw);

	for(int i=0; i<accnt_cnt; i++) {
		if(accnt_arr[i]->GetId() == id && accnt_arr[i]->GetPw() == pw) {
			cout<< "�α��� ����!" <<endl;
			Sleep(1000);
			system("cls");
			if(accnt_arr[i]->GetIsAdmin() == 1) {
				cout<<" ������ ���� Ȯ��!"<<endl;
				flag = 1;
				Sleep(1000);
				system("cls");
				AdminMenu(i);
			} else {
				cout<<" �Ϲ� ���� Ȯ��!"<<endl;
				flag = 1;
				Sleep(1000);
				system("cls");
				UserMenu(i);
			}
		}
	}

	if(flag == 0) { // �ܼ� �α��� ���� ��
		cout<<"�α��� ����, ������ �ٽ� Ȯ�����ּ���"<<endl;
		Sleep(1000);
		system("cls");
	}

}

void VideoRentalHandler::ShowRentalingVideo(int user_idx) {
	User *user = accnt_arr[user_idx];
	int input;
	if(user->GetRentalingVideoCnt()==0) {
		cout<<"���� �뿩 ���� ������ �����ϴ�."<<endl;
		Sleep(1000);
		system("cls");
		return;
	}

	cout<<"=== �뿩 ���� ���� ��� ==="<<endl;
	for(int i=0; i<user->GetRentalingVideoCnt(); i++) {
		for(int j=0; j<video_cnt; j++) {
			if(user->GetRentalingVideoCode(i)==video_arr[j]->GetVideoCode()) {
				Video *v = video_arr[j];
				cout<<"["<<i<<"]"<<endl;
				cout << setw(20) << left << "����" << setw(20) << left << "����" << setw(15) << "�帣" << setw(13) << "�󿵽ð�" << setw(13) << "��������" << setw(13) << "����" << endl;
				cout << "=================================================================================================" << endl;
				cout << setw(20) << left << v->GetVideoName() << setw(20) << left << v->GetDirector() << setw(15) << v->GetGenre() << setw(13) << v->GetRunningTime() << setw(13) << v->GetAgeLimit() << setw(13) << v->GetVideoPrice() << endl;
				cout << "=================================================================================================" << endl<<endl;
			}
		}
	}

	system("PAUSE");
	system("cls");
}

void VideoRentalHandler::UserMenu(int user_idx) {
	int choice;

	while(1) {
		cout<<"=== ����� �޴� ==="<<endl;
		cout<<"[1] ���� �뿩"<<endl;
		cout<<"[2] ���� �ݳ�"<<endl;
		cout<<"[3] ���� �˻�"<<endl;
		cout<<"[4] �뿩 ���� ���� ����"<<endl;
		cout<<"[5] �ܾ� ����"<<endl;
		cout<<"[6] ���� ����"<<endl;
		cout<<"[7] ����ϱ�"<<endl;
		cout<<"[0] �κ�� ���ư���"<<endl;
		cout<<"����: ";
		cin>>choice;

		system("cls");
		switch(choice) {
			case 0:
				cout<<"�κ�� ���ư��ϴ�."<<endl;
				Sleep(1000);
				system("cls");
				return;
			case 1: // ���� �뿩
				RentalVideo(user_idx);
				break;
			case 2: // ���� �ݳ�
				ReturnVideo(user_idx);
				break;
			case 3: // ���� �˻�
				SearchVideo();
				break;
			case 4: // �뿩 ���� ���� ����
				ShowRentalingVideo(user_idx);
				break;
			case 5: // �ܾ� ����
				ManageMoney(user_idx);
				break;
			case 6: // ���� ����
				ManageAccnt(user_idx);
				break;
			case 7: // ��� �ϱ�
				Save();
				break;
			default:
				cout << "�߸��� �Է��Դϴ�" << endl;
				Sleep(500);
				system("cls");
		}

	}

}

void VideoRentalHandler::AdminMenu(int user_idx) {
	int choice;

	while(1) {
		cout<<"=== ������ �޴� ==="<<endl;
		cout<<"[1] ���� �߰�"<<endl;
		cout<<"[2] ���� ����"<<endl;
		cout<<"[3] ���� ����"<<endl;
		cout<<"[4] ���� �˻�"<<endl;
		cout<<"[5] ���� ���� ����"<<endl;
		cout<<"[6] ���� ����"<<endl;
		cout<<"[7] �뿩 ��Ȳ �ľ�"<<endl;
		cout<<"[8] ����ϱ�"<<endl;
		cout<<"[0] �κ�� ���ư���"<<endl;
		cout<<"����: ";
		cin>>choice;
		system("cls");

		switch(choice) {
			case 0:
				cout<<"�κ�� ���ư��ϴ�."<<endl;
				Sleep(500);
				system("cls");
				return;
			case 1: // ���� �߰�
				AddVideo();
				break;
			case 2: // ���� ����
				EditVideo();
				break;
			case 3: // ���� ����
				DeleteVideo();
				break;
			case 4: // ���� �˻�
				SearchVideo();
				break;
			case 5: // ������ ���� �ο�
				AdminAuthority();
				break;
			case 6: // ���� ����
				ManageAccnt(user_idx);
				break;
			case 7: // �뿩 ��Ȳ �ľ�
				ManageRental();
				break;
			case 8: // ��� �ϱ�
				Save();
				break;
			default:
				cout << "�߸��� �Է��Դϴ�" << endl;
				Sleep(500);
				system("cls");
		}

	}
}

void VideoRentalHandler::Save(void) {
// 1.Video_info(���� ����), 2.User_accnt(����), 3.User_rental_video(������ �뿩�� ����)
// 1. �ڵ�, ����, ����, �帣, �󿵽ð�, ��������, �뿩����, ���
// 2. ���̵�, ���, ����, ����, �ݾ�, ����Ʈ, �뿩����, �뿩�뷮, ��������, ��ũ
// 3. ���� �ڵ�

	typedef struct User {
		string id;
		string pw;
		string name;
		string sex;
		string e_mail;
		int age;
		int money;
		int point;
		int cnt;
		int capacity;
		int is_admin;
		int rank;
		string code;
	} user;

	typedef struct Video {
		string code;
		string name;
		string dir;
		string genre;
		int time;
		int age;
		int price;
		int amount;
	} video;
	user u;
	video v;

	ofstream writefile_1,writefile_2,writefile_3;
	//������ ���� �� ����
	writefile_1.open("Video_info.txt");
	writefile_2.open("User_accnt.txt");
	writefile_3.open("User_rental_video.txt");

	cout<<"�����ͺ��̽��� ������ �����մϴ�."<<endl;
	Sleep(500);

	for(int i=0; i<video_cnt; i++) {
		v.code = video_arr[i]->GetVideoCode();
		v.name = video_arr[i]->GetVideoName();
		v.dir = video_arr[i]->GetDirector();
		v.genre = video_arr[i]->GetGenre();
		v.time = video_arr[i]->GetRunningTime();
		v.age = video_arr[i]->GetAgeLimit();
		v.price = video_arr[i]->GetVideoPrice();
		v.amount = video_arr[i]->GetVideoAmount();

		writefile_1 << v.code << endl;
		writefile_1 << v.name << endl;
		writefile_1 << v.dir << endl;
		writefile_1 << v.genre << endl;
		writefile_1 << v.time << endl;
		writefile_1 << v.age << endl;
		writefile_1 << v.price << endl;
		writefile_1 << v.amount << endl;
	}
	writefile_1.close();
	cout<<"���� ������ ����߽��ϴ�."<<endl;
	Sleep(500);
// 2. ���̵�, ���, �̸�, �̸���, ����, ����, �ݾ�, ����Ʈ, �뿩����, �뿩�뷮, ��������, ��ũ
	for(int i=0; i<accnt_cnt; i++) {
		u.id = accnt_arr[i]->GetId();
		u.pw = accnt_arr[i]->GetPw();
		u.name = accnt_arr[i]->GetName();
		u.e_mail = accnt_arr[i]->GetE_mail();
		u.sex = accnt_arr[i]->GetSex();
		u.age = accnt_arr[i]->GetAge();
		u.money = accnt_arr[i]->GetMoney();
		u.point = accnt_arr[i]->GetPoint();
		u.cnt = accnt_arr[i]->GetRentalingVideoCnt();
		u.capacity = accnt_arr[i]->GetVideoCapacity();
		u.capacity = 10;
		u.is_admin = accnt_arr[i]->GetIsAdmin();
		u.rank = accnt_arr[i]->GetRank();

		writefile_2 << u.id << endl;
		writefile_2 << u.pw << endl;
		writefile_2 << u.name << endl;
		writefile_2 << u.e_mail << endl;
		writefile_2 << u.sex << endl;
		writefile_2 << u.age << endl;
		writefile_2 << u.money << endl;
		writefile_2 << u.point << endl;
		writefile_2 << u.cnt << endl;
		writefile_2 << u.capacity << endl;
		writefile_2 << u.is_admin << endl;
		writefile_2 << u.rank << endl;
	}
	writefile_2.close();
	cout<<"���� ������ ����߽��ϴ�."<<endl;
	Sleep(500);

	for(int i=0; i<accnt_cnt; i++) {
		for(int j=0; j<accnt_arr[i]->GetRentalingVideoCnt(); j++) {
			u.code = accnt_arr[i]->GetRentalingVideoCode(j);
			writefile_3 << u.code << " ";
		}
		writefile_3 << endl;
	}

	writefile_3.close();
	cout<<"���� �뿩 ���� ������ ����߽��ϴ�."<<endl;
	Sleep(500);

	cout<<"������ ������ �Ϸ��߽��ϴ�."<<endl;
	Sleep(500);
	system("cls");
}

void VideoRentalHandler::Load(void) {
// 1.Video_info(���� ����), 2.User_accnt(����), 3.User_rental_video(������ �뿩�� ����)
// 1. �ڵ�, ����, ����, �帣, �󿵽ð�, ��������, �뿩����, ���
// 2. ���̵�, ���, ����, ����, �ݾ�, ����Ʈ, �뿩����, �뿩�뷮, ��������, ��ũ
// 3. ���� �ڵ�

	ifstream readfile_1, readfile_2, readfile_3;
	//ofstream writefile_3; // ������ �뿩�� ���� ���� ����
	stringstream s5;
	readfile_1.open("Video_info.txt");
	readfile_2.open("User_accnt.txt");
	readfile_3.open("User_rental_video.txt");
	//writefile_3.open("User_rental_video.txt"); // �� �ѱ� �뵵

	string v_code, v_name, v_dir, v_genre, v_time, v_age, v_price, v_amount;
	int _v_time, _v_age, _v_price, _v_amount;

	string u_id, u_pw, u_name, u_e_mail, u_sex, u_age, u_money, u_point, u_cnt, u_capacity, u_is_admin, u_rank;
	int _u_age, _u_money, _u_point, _u_cnt, _u_capacity, _u_is_admin, _u_rank;

	int user_idx=0;
	if (readfile_1.is_open()) {
		while (getline(readfile_1, v_code) && getline(readfile_1, v_name) && getline(readfile_1, v_dir)
		        && getline(readfile_1, v_genre) && getline(readfile_1, v_time) && getline(readfile_1, v_age)
		        && getline(readfile_1, v_price) && getline(readfile_1, v_amount)) {
			_v_time = stoi(v_time);
			_v_age = stoi(v_age);
			_v_price = stoi(v_price);
			_v_amount = stoi(v_amount);
			video_arr[video_cnt++] = new Video(v_code, v_name, v_dir, v_genre, _v_time, _v_age, _v_price, _v_amount);
		}
	} else {
		cout << "���� ������ ������ �������� �ʽ��ϴ�." << endl;
		Sleep(500);
	}

	readfile_1.close();
	cout<<"���� ������ �ε� ����."<<endl;
	Sleep(500);
// 2. ���̵�, ���, �̸�, �̸���, ����, ����, �ݾ�, ����Ʈ, �뿩����, �뿩�뷮, ��������, ��ũ
	if (readfile_2.is_open()) {
		while (getline(readfile_2, u_id) && getline(readfile_2, u_pw) && getline(readfile_2, u_name) && getline(readfile_2, u_e_mail)
		        && getline(readfile_2, u_sex) && getline(readfile_2, u_age) && getline(readfile_2, u_money) && getline(readfile_2, u_point)
		        && getline(readfile_2, u_cnt) && getline(readfile_2, u_capacity) && getline(readfile_2, u_is_admin) && getline(readfile_2, u_rank)
		      ) {
			s5<<u_age;
			s5>>_u_age;
			_u_money = stoi(u_money);
			_u_point = stoi(u_point);
			_u_cnt = stoi(u_cnt);
			_u_capacity = 10;
			_u_is_admin = stoi(u_is_admin);
			_u_rank = stoi(u_rank);
			accnt_arr[accnt_cnt++] = new User(u_id, u_pw, u_name, u_e_mail, u_sex, _u_age, _u_money, _u_point, _u_cnt, _u_capacity, _u_is_admin, _u_rank);
		}
	} else {
		cout << "���� ������ ������ �������� �ʽ��ϴ�." << endl;
		Sleep(500);
	}

	readfile_2.close();
	cout<<"���� ������ �ε� ����."<<endl;
	Sleep(500);

	string temp;
	int i=0;
	if(readfile_3.is_open()) {
		while (getline(readfile_3, temp)) { //ù ��° �ٺ��� �о����
			istringstream iss(temp);
			string code;
			while (iss >> code) { //�ܾ�� ������ �ε�
				accnt_arr[i]->RentalVideo(code);
			}
			i++;
		}
	} else {
		cout<<"���� �뿩 ���� ������ �������� �ʽ��ϴ�."<<endl;
	}

	readfile_3.close();
	cout<<"���� �뿩 ���� ������ �ε� ����."<<endl;
	Sleep(500);
	system("cls");
}

int main(void) {
	int flag;

	VideoRentalHandler V(10,10); //���� ����, ���� ���뷮
	V.SetConsole();

	V.Loby();
}
