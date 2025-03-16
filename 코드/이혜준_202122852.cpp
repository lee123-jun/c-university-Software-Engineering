#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream> // stringstream iss iss가 문장에서 공백문자를 기준으로 분할 
#include <iomanip> // setw(전체너비), setfill(나머지공간채우기)

/*
* 소프트웨어공학(권세진)/ 비디오대여점 프로그램 ver 0.1
* tool: DevC++
* compiler: Mingw64, TDM GCC 4.9.2
* version: c++11
* 작성자 : 이혜준_202122852

* 로그인 기능
- 로그인 기능으로 사용자마다 다른 정보를 다룸
- 회원가입 아이디 비번으로 동명이인 처리

* 관리자 기능
- 비디오 추가
- 비디오 수정
- 비디오 삭제
- 계정권한 부여 (관리자계정or사용자계정으로 전환)
- 계정 관리
- 백업하기
- 로비(로그인화면으로 돌아가기)

* 사용자 기능
- 비디오 대여
- 비디오 반납
- 비디오 검색
- 대여중인 비디오 보기
- 잔액 관리
- 계정 관리
- 백업하기
- 로비(로그인화면으로 돌아가기)

* 객체들 값 대입 시 음수 같은 변수 값들 예외처리 "setter"
* 입력 시 잘못된 자료형 예외처리
* 잘못된 메뉴선택 예외처리
* 가변배열 사용으로 유저증가, 비디오 개수 증가 시 배열 크기 늘리기

* 최초 실행 후 로그인 시
관리자 계정 ID: admin, PW: admin
사용자 계정 ID: user, PW: user
테스트 시에는 콘솔창을 전체 화면으로 해주시면 감사하겠습니다.

// 1.Video_info(비디오 정보), 2.User_accnt(계정), 3.User_rental_video(유저가 대여한 비디오)
// 1. 코드, 제목, 감독, 장르, 상영시간, 연령제한, 대여가격, 재고량
// 2. 아이디, 비번, 이름, 이메일, 성별, 나이, 금액, 포인트, 대여개수, 대여용량, 계정유형, 랭크
// 3. 비디오 코드
테스트 데이터  사용 시 지켜줘야 할 양식입니다.
*/

using namespace std;

class Video {
	private:
		string video_code; // 비디오 코드
		string name; //제목
		string director; //감독
		string genre; //장르
		int running_time; //상영시간
		int age_limit; //연령 제한
		int price; //대여 가격
		int amount; // 재고량
		// 1. 코드, 제목, 감독, 장르, 상영시간, 연령제한, 대여가격, 재고량
	public:
		// 생성자 및 예외처리
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
		//Get 함수들
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

		//Edit 함수들
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

		// 보유 비디오 수량 조절
		int PlusVideoAmount(int plus) {
			amount += plus;
		}
		int MinusVideoAmount(int minus) {
			amount -= minus;
			if (amount < 0) {
				amount = 0;
			}
		}
		// 비디오 정보 출력
		void ShowVideoInfo() {
			cout << setw(20) << left << "제목" << setw(20) << left << "감독" << setw(15) << "장르" << setw(13) << "상영시간" << setw(13) << "연령제한" << setw(13) << "가격" << setw(13) << "재고량" << endl;
			cout << "=======================================================================================================" << endl;
			cout << setw(20) << left << name << setw(20) << left << director << setw(15) << genre << setw(13) << running_time << setw(13) << age_limit << setw(13) << price << setw(13) << amount << endl;
			cout << "=======================================================================================================" << endl<<endl;
		}

};

class User {
	private:
		string id; // 아이디
		string pw; // 비밀번호
		string name; // 이름
		string e_mail; // 이메일
		string sex; // 남자 or 여자
		int age; //나이
		int money; //충전한 금액
		int point; //포인트
		string *r_video_arr; // 대여한 비디오의 고유코드
		int r_video_cnt; // 대여한 비디오 개수
		int r_video_capacity; // 대여 가능 비디오 용량
		int is_admin; //계정 종류 관리자 1, 유저 0
		int rank; // 회원등급 브론즈 0, 실버 1, 골드 2

		friend Video;
	public:
		User(string _id="None", string _pw="None", string _name="None", string _e_mail="None",
		     string _sex="None", int _age=0, int _money=0,int _point=0, int _r_video_cnt=0, int r_video_capacity=10,
		     int _is_admin=0,int _rank=0) {
			id=_id;
			pw=_pw;
			name=_name;
			if(_sex!="남자"||sex!="여자") {
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

		//Get 함수들
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

		//Edit 함수들
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

		//money 관리 함수
		void PlusMoney(int plus) {
			money += plus;
		}
		void MinusMoney(int minus) {
			money -=  minus;
			if(money < 0) {
				money = 0;
			}
		}

		//Point 관리 함수
		void PlusPoint(int plus) {
			point += plus;
		}
		void MinusPoint(int minus) {
			point -= minus;
			if(point < 0) {
				point = 0;
			}
		}

		// 비디오 대여, 반납
		void RentalVideo(string code) {
			if(r_video_capacity < 10) { // 저장 용량 예외처리
				r_video_capacity = 10;
			}
			r_video_arr[r_video_cnt++] = code;
			// 가변 배열 설정 5씩 증가
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

		//계정관리, 랭크 관리
		int EditIsAdmin(int num) {
			is_admin = num;
		}
		int EditRank(int num) {
			rank = num;
		}

		// 대여한 비디오 개수 조절
		int PlusVideoCnt(int plus) {
			r_video_cnt += plus;
		}
		int MinusVideoCnt(int minus) {
			r_video_cnt -= minus;
			if(r_video_cnt < 0) {
				r_video_cnt = 0;
			}
		}

		// 유저 정보 출력
		void ShowUserInfo(void) {
			cout<<"---------------------------------------"<<endl;
			cout<<"ID: "<<id<<" | "<<"PW: "<<pw<<endl;
			cout<<"이름: "<<name<<" |"<<"성별: "<<sex<<" | "<<"나이: "<<age<<endl;
			cout<<"금액: "<<money<<" | "<<"포인트: "<<point<<" | "<<"이메일: "<<e_mail<<endl;
			cout<<"---------------------------------------"<<endl<<endl;
		}

		~User() { // 유저 대여 비디오 동적할당 해제
			for(int i=0; i<r_video_capacity; i++) {
				delete r_video_arr;
			}
			delete[] r_video_arr;
		}
};

class VideoRentalHandler {
	private:
		Video **video_arr; // 비디오 배열
		int video_cnt; // 비디오 개수
		int video_capacity; // 비디오 배열 수용량

		User **accnt_arr; // 유저 계정 배열
		int accnt_cnt; // 유저 계정 인원 수
		int accnt_capacity; // 계정 배열 수용량
	public:
		// 생성자
		VideoRentalHandler(int video = 10, int accnt = 10)
			: video_cnt(0), accnt_cnt(0), video_capacity(video), accnt_capacity(accnt) {

			video_arr = new Video*[video_capacity];
			accnt_arr = new User*[accnt_capacity];
		}

		// 최초 로그인, 회원가입
		void Load(void); // 계정, 비디오 외부에서 로드
		void Save(void); // 수정된 정보 외부에 저장
		void Login(void);
		void CreateAccnt(void);
		void Loby(void);

		// 관리자 기능
		void AddVideo(void); // 비디오 추가
		void EditVideo(void); // 비디오 내용 수정
		void DeleteVideo(void); // 비디오 삭제
		void AdminAuthority(void); // 관리자 권한 부여
		void AdminMenu(int user_idx); //관리자용 메뉴
		void ManageRental(void); // 대여된 비디오 관리

		// 사용자 기능
		void RentalVideo(int user_idx); // 비디오 대여
		void ReturnVideo(int user_idx); // 비디오 반납
		void ShowRentalingVideo(int user_idx); // 대여 중인 비디오 보기
		void ManageMoney(int user_idx); // 잔액 관리
		void UserMenu(int user_idx); // 사용자용 메뉴

		// 공통 기능
		void SearchVideo(void); // 비디오 검색
		void ManageAccnt(int user_idx); // 계정 관리(id,pw)
		void SetConsole(void); // 콘솔 크기, 위치, 타이틀 조정

		// 등록된 모든 비디오 출력
		void ShowAllVideoInfo(void) {
			if(video_cnt == 0) {
				cout<<"시스템 상에 등록된 비디오가 없습니다."<<endl;
			}
			for(int i=0; i<video_cnt; i++) {
				cout<<"["<<i<<"]"<<endl;
				video_arr[i]->ShowVideoInfo();
			}
		}

		// 등록된 모든 유저 출력
		void ShowAllUserInfo(void) {
			if(accnt_cnt == 0) {
				cout<<"시스템 상에 등록된 사용자가 없습니다."<<endl;
			}
			for(int i=0; i<accnt_cnt; i++) {
				cout<<"["<<i<<"]"<<endl;
				accnt_arr[i]->ShowUserInfo();
			}
		}

		~VideoRentalHandler() {
			for (int i = 0; i < video_capacity; i++) {
				delete video_arr[i]; // 비디오 배열의 각 요소 해제
			}
			delete[] video_arr; // 비디오 배열 포인터 해제

			for (int i = 0; i < accnt_capacity; i++) {
				delete accnt_arr[i]; // 유저 계정 배열의 각 요소 해제
			}
			delete[] accnt_arr; // 유저 계정 배열 포인터 해제
		}
};

void VideoRentalHandler::ManageRental(void) {
	int user_cnt=0,capacity=10,choice;
	User **temp_arr = new User*[capacity];

	for(int i=0; i<accnt_cnt; i++) { // 일반 사용자 계정 임시 가변 배열 설정

		if(accnt_arr[i]->GetIsAdmin() == 0) { // 관리자가 아닌  계정만 배열에 담기

			if(user_cnt==capacity-1) { // 수용량 넘을 시 예외처리
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
			temp_arr[user_cnt++] = accnt_arr[i]; // 배열에 추가
		}
	}

	while(1) {

		cout<<"=== 대여 관리 ==="<<endl;
		cout<<"[1] 비디오 대여 현황 보기"<<endl;
		cout<<"[2] 사용자 대여 현황 보기"<<endl;
		cout<<"[0] 메뉴로 돌아가기"<<endl;
		cout<<"선택: ";
		cin>>choice;
		system("cls");

		switch(choice) {
			case 1:
				for(int i=0; i<video_cnt; i++) {
					cout<<"["<<i<<"]"<<endl;
					cout<<"제목: "<<video_arr[i]->GetVideoName()<<endl;
					cout<<"영화 코드: "<<video_arr[i]->GetVideoCode()<<endl;
					cout<<"=== 대여 인원 목록 (ID, e-mail) ==="<<endl;
					for(int j=0; j<accnt_cnt; j++) { // j 전체 계정의 수
						for(int k=0; k<accnt_arr[j]->GetRentalingVideoCnt(); k++) { // k 대여한 비디오 개수
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
					cout<<"이름: "<<temp_arr[i]->GetName()<<endl;
					cout<<"이메일: "<<temp_arr[i]->GetE_mail()<<endl;
					if(temp_arr[i]->GetRentalingVideoCnt() == 0) { // 대여중일때
						cout<<" 대여중인 비디오가 없습니다."<<endl;
					} else if(temp_arr[i]->GetRentalingVideoCnt() > 0) { // 대여중이지 않을 때
						cout<<"대여 목록: ";
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
				cout<<"메뉴로 돌아갑니다."<<endl;
				Sleep(500);
				system("cls");
				return;
			default:
				cout<<"잘못된 입력입니다."<<endl;
				Sleep(500);
				system("cls");
				continue;
		}
	}
}

void VideoRentalHandler::SetConsole(void) {
// cols: 가로, lines: 세로  120 40  / 410 145
	system("mode con cols=211 lines=55 | title 비디오대여프로그램(소공) by Yulgok");
}

void VideoRentalHandler::AddVideo(void) {
	string code, name, dir, genre;
	int time, age, price, amount;
	cin.ignore();
	cout<<"=== 새로운 비디오를 추가 ==="<<endl;
	cout<<"비디오코드: ";
	getline(cin, code);
	cout<<"이름: ";
	getline(cin, name);
	cout<<"감독: ";
	getline(cin, dir);
	cout<<"장르: ";
	getline(cin, genre);
	cout<<"러닝타임: ";
	cin>>time;
	cout<<"연령제한: ";
	cin>>age;
	cout<<"대여가격: ";
	cin>>price;
	cout<<"재고량: ";
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
// 1. 코드, 제목, 감독, 장르, 상영시간, 연령제한, 대여가격, 재고량
	video_arr[video_cnt++] = new Video(code, name, dir, genre, time, age, price, amount);
	cout<<"비디오 추가 완료."<<endl;
	Sleep(1000);
	system("cls");
}

void VideoRentalHandler::EditVideo(void) {
	string name, dir, genre;
	int time, age, price, amount;
	int choice, idx;

// 전체 비디오 출력
	while(1) {
		ShowAllVideoInfo();
		cout<<"=== 기존 비디오 수정 ==="<<endl;
		cout<<"[1] 검색하기"<<endl;
		cout<<"[2] 수정하기"<<endl;
		cout<<"[0] 메뉴 돌아가기"<<endl;
		cout<<"선택: ";
		cin>>choice;

		switch(choice) {
			case 1:
				SearchVideo();
				break;
			case 2:
				cout<<"=== 수정할 비디오 인덱스 선택 ==="<<endl;
				cout<<"선택: ";
				cin>>idx;
				if(idx < 0 || idx >= video_cnt) {
					cout<<"올바른 인덱스를 입력해주세요."<<endl;
					Sleep(500);
					system("cls");
					continue;
				}
				while(1) {
					cout<<"=== 수정할 정보를 선택 ==="<<endl;
					cout<<"[1] 비디오 이름"<<endl;
					cout<<"[2] 비디오 감독"<<endl;
					cout<<"[3] 비디오 장르"<<endl;
					cout<<"[4] 비디오 러닝타임"<<endl;
					cout<<"[5] 비디오 연령제한"<<endl;
					cout<<"[6] 비디오 대여가격"<<endl;
					cout<<"[7] 비디오 재고량"<<endl;
					cout<<"[0] 메뉴로 돌아가기"<<endl;
					cout<<"선택: ";
					cin>>choice;
					system("cls");
					cin.ignore();
					switch(choice) {
						case 1:
							cout<<"수정할 이름 입력"<<endl;
							cout<<"이름: ";
							getline(cin, name);
							video_arr[idx]->EditVideoName(name);
							cout<<"수정을 완료했습니다."<<endl;
							Sleep(500);
							system("cls");
							break;
						case 2:
							cout<<"수정할 감독 입력"<<endl;
							cout<<"감독: ";
							getline(cin, dir);
							video_arr[idx]->EditDirector(dir);
							cout<<"수정을 완료했습니다."<<endl;
							Sleep(500);
							system("cls");
							break;
						case 3:
							cout<<"수정할 장르 입력"<<endl;
							cout<<"장르: ";
							getline(cin, genre);
							video_arr[idx]->EditGenre(genre);
							cout<<"수정을 완료했습니다."<<endl;
							Sleep(500);
							system("cls");
							break;
						case 4:
							cout<<"수정할 러닝타임 입력"<<endl;
							cout<<"러닝타임: ";
							cin>>time;
							video_arr[idx]->EditRunningTime(time);
							cout<<"수정을 완료했습니다."<<endl;
							Sleep(500);
							system("cls");
							break;
						case 5:
							cout<<"수정할 연령제한 입력"<<endl;
							cout<<"연령제한: ";
							cin>>age;
							video_arr[idx]->EditAgeLimit(age);
							cout<<"수정을 완료했습니다."<<endl;
							Sleep(500);
							system("cls");
							break;
						case 6:
							cout<<"수정할 대여가격 입력"<<endl;
							cout<<"대여가격: ";
							cin>>price;
							video_arr[idx]->EditVideoPrice(price);
							cout<<"수정을 완료했습니다."<<endl;
							Sleep(500);
							system("cls");
							break;
						case 7:
							cout<<"수정할 재고량 입력"<<endl;
							cout<<"재고량: ";
							cin>>amount;
							video_arr[idx]->EditVideoAmount(amount);
							cout<<"수정을 완료했습니다."<<endl;
							Sleep(500);
							system("cls");
							break;
						case 0:
							cout<<"메뉴로 돌아갑니다."<<endl;
							Sleep(500);
							system("cls");
							return;
						default:
							cout<<"잘못된 입력입니다."<<endl;
							Sleep(500);
							system("cls");
							break;
					}
				}
				break;
			case 0:
				cout<<"메뉴로 돌아갑니다."<<endl;
				Sleep(500);
				system("cls");
				return;
			default:
				cout<<"잘못된 입력입니다."<<endl;
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
		cout<<"=== 기존 비디오 삭제 ==="<<endl;
		cout<<"[1] 검색하기"<<endl;
		cout<<"[2] 삭제하기"<<endl;
		cout<<"[0] 메뉴 돌아가기"<<endl;
		cout<<"선택: ";
		cin>>choice;
		system("cls");

		switch(choice) {
			case 1:
				SearchVideo();
				break;
			case 2:
				cout<<"=== 삭제할 비디오 인덱스 선택 ==="<<endl;
				cout<<"선택: ";
				cin>>idx;

				if(idx < 0 || idx >= video_cnt) {
					cout<<"올바른 인덱스를 입력해주세요"<<endl;
					Sleep(500);
					system("cls");
					continue;
				}
				while(1) {
					cout<<"정말 삭제할 건가요?"<<endl;
					cout<<"[1] 예"<<endl;
					cout<<"[2] 아니요"<<endl;
					cout<<"선택: ";
					cin>>choice;
					if(choice == 1) {}
					else if(choice == 2) {
						cout<<"삭제를 취소합니다."<<endl;
						Sleep(500);
						system("cls");
						continue;
					} else {
						cout<<"잘못된 입력입니다"<<endl;
						Sleep(500);
						system("cls");
						continue;
					}

					delete video_arr[idx]; // 해당 인덱스 비디오 삭제
					for (int i = idx; i < video_capacity-1; i++) { // 뒤의 요소들 가져오기
						video_arr[i] = video_arr[i + 1];
					}
					video_cnt--; // 비디오 개수 -1

					cout<<"삭제를 완료했습니다."<<endl;
					Sleep(500);
					system("cls");
					break;
				}
				break;
			case 0:
				cout<<"메뉴로 돌아갑니다."<<endl;
				Sleep(500);
				system("cls");
				return;
			default:
				cout<<"잘못된 입력입니다."<<endl;
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
		cout<<" === 비디오 검색하기 ==="<<endl;
		cout<<"[1] 이름 검색"<<endl;
		cout<<"[2] 감독 검색"<<endl;
		cout<<"[3] 장르 검색"<<endl;
		cout<<"[0] 메뉴로 돌아가기"<<endl;
		cout<<"선택: ";
		cin>>choice;
		cin.ignore();
		switch(choice) {
			case 1:
				cout<<"이름: ";
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
					cout<<"다시 시도해주세요."<<endl;
					Sleep(500);
					system("cls");
				}
				break;
			case 2:
				cout<<"감독: ";
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
					cout<<"다시 시도해주세요."<<endl;
					Sleep(500);
					system("cls");
				}
				break;
			case 3:
				cout<<"장르: ";
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
					cout<<"다시 시도해주세요."<<endl;
					Sleep(500);
					system("cls");
				}
				break;
			case 0:
				cout<<"메뉴로 돌아갑니다."<<endl;
				Sleep(500);
				system("cls");
				return;
			default:
				cout<<"잘못된 입력입니다."<<endl;
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
		cout<<"관리자 권한 부여하기"<<endl;
		cout<<"[1] 관리자 계정으로 전환"<<endl;
		cout<<"[2] 사용자 계정으로 전환"<<endl;
		cout<<"[3] 사용자 검색"<<endl;
		cout<<"[0] 메뉴로 돌아가기"<<endl;
		cout<<"선택: ";
		cin>>choice;
		system("cls");
		cin.ignore();
		switch(choice) {
			case 0:
				cout<<"메뉴로 돌아갑니다."<<endl;
				Sleep(500);
				system("cls");
				return;
			case 1:
				while(1) {
					cout<<"해당 유저의 인덱스 선택"<<endl;
					cout<<"선택: ";
					cin>>idx;

					if(idx < 0 || idx >= accnt_cnt) {
						cout<<"올바른 인덱스를 입력해주세요"<<endl;
						Sleep(500);
						system("cls");
						continue;
					}
					break;
				}

				while(1) {
					cout<<"정말 관리자 계정으로 전환할건가요?"<<endl;
					cout<<"[1] 예"<<endl;
					cout<<"[2] 아니요"<<endl;
					cout<<"선택: ";
					cin>>choice;
					if(choice == 1) {}
					else if(choice == 2) {
						cout<<"권한부여를 취소합니다."<<endl;
						Sleep(500);
						system("cls");
						break;
					} else {
						cout<<"잘못된 입력입니다"<<endl;
						Sleep(500);
						system("cls");
						continue;
					}

					accnt_arr[idx]->EditIsAdmin(1);
					cout<<"권한부여를 완료했습니다."<<endl;
					Sleep(500);
					system("cls");
					break;
				}

				break;
			case 2:
				while(1) {
					cout<<"해당 유저의 인덱스 선택"<<endl;
					cout<<"선택: ";
					cin>>idx;

					if(idx < 0 || idx >= accnt_cnt) {
						cout<<"올바른 인덱스를 입력해주세요"<<endl;
						Sleep(500);
						system("cls");
						continue;
					}
					break;
				}

				while(1) {
					cout<<"정말 사용자 계정으로 전환할건가요?"<<endl;
					cout<<"[1] 예"<<endl;
					cout<<"[2] 아니요"<<endl;
					cout<<"선택: ";
					cin>>choice;
					if(choice == 1) {}
					else if(choice == 2) {
						cout<<"권한부여를 취소합니다."<<endl;
						Sleep(500);
						system("cls");
						break;
					} else {
						cout<<"잘못된 입력입니다"<<endl;
						Sleep(500);
						system("cls");
						continue;
					}

					accnt_arr[idx]->EditIsAdmin(0);
					cout<<"권한부여를 완료했습니다."<<endl;
					Sleep(500);
					system("cls");
					break;
				}
				break;
			case 3:
				cout<<"=== 사용자 검색 ==="<<endl;
				cout<<"이름입력: ";
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
					cout<<"다시 시도해주세요."<<endl;
					Sleep(500);
					system("cls");
				}
				break;
			default:
				cout<<"잘못된 입력입니다"<<endl;
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
		accnt_arr[user_idx]->ShowUserInfo();// 현 계정 정보
		cout<<"=== 계정 관리 ==="<<endl;
		cout<<"[1] ID 변경"<<endl;
		cout<<"[2] PW 변경"<<endl;
		cout<<"[3] 성별 변경"<<endl;
		cout<<"[4] 나이 변경"<<endl;
		cout<<"[5] 이름 변경"<<endl;
		cout<<"[0] 메뉴로 이동"<<endl;
		cout<<"선택: ";
		cin>>choice;
		cin.ignore();
		switch(choice) {
			case 1:
				cout<<"=================="<<endl;
				cout<<"변경할 ID를 입력"<<endl;
				cout<<"ID: ";
				getline(cin, id);
				for(int i=0; i<accnt_cnt; i++) {
					if(accnt_arr[i]->GetId() == id) {
						cout<< "이미 동일한 id가 존재합니다" <<endl;
						Sleep(500);
						system("cls");
						continue;
					}
				}
				accnt_arr[user_idx]->EditId(id);
				cout<<"ID 변경완료."<<endl;
				Sleep(500);
				system("cls");
				break;
			case 2:
				cout<<"=================="<<endl;
				cout<<"변경할 PW를 입력"<<endl;
				cout<<"PW: ";
				getline(cin, pw);
				accnt_arr[user_idx]->EditPw(pw);
				cout<<"PW 변경완료."<<endl;
				Sleep(500);
				system("cls");
				break;
			case 3:
				while(1) {
					cout<<"=================="<<endl;
					cout<<"변경할 성별을 선택"<<endl;
					cout<<"[1] 남자";
					cout<<"[2] 여자"<<endl;
					cout<<"선택: ";
					cin>>choice;
					if(choice==1) {
						sex = "남자";
						break;
					} else if(choice==2) {
						sex = "여자";
						break;
					} else {
						cout<<"다시 입력해주세요."<<endl;
						Sleep(500);
						system("cls");
						continue;
					}
				}
				accnt_arr[user_idx]->EditSex(sex);
				cout<<"성별 변경완료."<<endl;
				Sleep(500);
				system("cls");
				break;
			case 4:
				cout<<"=================="<<endl;
				cout<<"변경할 나이를 입력"<<endl;
				cout<<"나이: ";
				cin>>age;
				accnt_arr[user_idx]->EditAge(age);
				cout<<"나이 변경완료."<<endl;
				Sleep(500);
				system("cls");
				break;
			case 5:
				cout<<"=================="<<endl;
				cout<<"변경할 이름을 입력"<<endl;
				cout<<"이름: ";
				cin>>name;
				accnt_arr[user_idx]->EditName(name);
				cout<<"이름 변경완료."<<endl;
				Sleep(500);
				system("cls");
				break;
			case 0:
				cout<<"메뉴로 돌아갑니다."<<endl;
				Sleep(500);
				system("cls");
				return;
			default:
				cout<<"잘못된 입력입니다."<<endl;
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
		cout<<"=== 비디오 대여 ==="<<endl;
		cout<<"[1] 검색하기"<<endl;
		cout<<"[2] 대여하기"<<endl;
		cout<<"[0] 메뉴 돌아가기"<<endl;
		cout<<"선택: ";
		cin>>choice;

		switch(choice) {
			case 1:
				SearchVideo();
				break;
			case 2:
				cout<<"대여할 비디오의 인덱스 선택"<<endl;
				cout<<"선택: ";
				cin>>idx;

				if(idx < 0 || idx >= video_cnt) {
					cout<<"올바른 인덱스를 입력해주세요"<<endl;
					Sleep(500);
					system("cls");
					continue;
				}

				if(temp->GetAge() < video_arr[idx]->GetAgeLimit()) {
					cout<<"연령제한으로 해당 비디오를 대여할 수 없습니다."<<endl;
					Sleep(500);
					system("cls");
					continue;
				}

				if(video_arr[idx]->GetVideoAmount() == 0) {
					cout<<"해당 비디오의 남은 재고량이 없습니다."<<endl;
					Sleep(500);
					system("cls");
					continue;
				}

				while(1) {
					cout<<"================="<<endl;
					cout<<"대여료: "<<video_arr[idx]->GetVideoPrice()<<endl;
					cout<<"잔액: "<<temp->GetMoney()<<endl;
					cout<<"포인트: "<<temp->GetPoint()<<endl;
					cout<<"포인트를 사용하겠습니까? "<<endl<<endl;
					cout<<"[1] 예"<<endl;
					cout<<"[2] 아니오"<<endl;
					cout<<"[0] 메뉴로 돌아가기"<<endl;
					cout<<"선택: ";
					cin>>choice;
					system("cls");

					switch(choice) {
						case 1:
							cout<<"잔액+포인트로 계산을 진행합니다."<<endl;
							if(video_arr[idx]->GetVideoPrice() > temp->GetMoney()+temp->GetPoint()) {
								cout<<"총액이 부족합니다. 돈을 더 충전해주세요"<<endl;
								Sleep(500);
								system("cls");
								return;
							}
							temp->RentalVideo(video_arr[idx]->GetVideoCode()); //사용자 대뎌 배열 삽입
							temp->MinusMoney(video_arr[idx]->GetVideoPrice()); // 돈 마이너스
							temp->PlusVideoCnt(1); // 보유 비디오 카운트 증가
							video_arr[idx]->MinusVideoAmount(1); // 비디오 재고량 1 감소
							cout<<"비디오 대여를 완료했습니다."<<endl;
							Sleep(1000);
							system("cls");
							return;
							break;
						case 2:
							cout<<"잔액으로만 계산을 진행합니다."<<endl;
							if(video_arr[idx]->GetVideoPrice() > temp->GetMoney()) {
								cout<<"총액이 부족합니다. 돈을 더 충전해주세요"<<endl;
								Sleep(500);
								system("cls");
								continue;
							}
							cout<<"비디오 대여를 완료했습니다."<<endl;
							temp->RentalVideo(video_arr[idx]->GetVideoCode()); // 위와 동일
							temp->MinusMoney(video_arr[idx]->GetVideoPrice());
							temp->PlusVideoCnt(1);
							video_arr[idx]->MinusVideoAmount(1);
							Sleep(1000);
							system("cls");
							return;
							break;
						case 0:
							cout<<"메뉴로 돌아갑니다."<<endl;
							Sleep(500);
							system("cls");
							return;
							break;
						default:
							cout<<"잘못된 입력입니다."<<endl;
							Sleep(500);
							system("cls");
							continue;
					}
				}
				break;
			case 0:
				cout<<"메뉴로 돌아갑니다."<<endl;
				Sleep(500);
				system("cls");
				return;
			default:
				cout<<"잘못된 입력입니다."<<endl;
				Sleep(500);
				system("cls");
				break;
		}
	}
}

void VideoRentalHandler::ReturnVideo(int user_idx) {
	int choice, idx;
	User *u = accnt_arr[user_idx];
// 현재 대여중인 비디오 출력

	while(1) {
		ShowRentalingVideo(user_idx);
		cout<<"=== 비디오 반납 ==="<<endl;
		cout<<"[1] 반납하기"<<endl;
		cout<<"[2] 대여 중인 비디오 보기"<<endl;
		cout<<"[0] 메뉴 돌아가기"<<endl;
		cout<<"선택: ";
		cin>>choice;
		system("cls");

		switch(choice) {
			case 1:
				cout<<"반납할 비디오의 인덱스 선택"<<endl;
				cout<<"선택: ";
				cin>>idx; // 유저가 빌린 배열의 인덱스

				if(idx < 0 || idx >= u->GetRentalingVideoCnt()) {
					cout<<"올바른 인덱스를 입력해주세요."<<endl;
					Sleep(500);
					system("cls");
					continue;
				}

				for(int i=0; i<video_cnt; i++) { // 반납 된 비디오 개수 증가
					if(video_arr[i]->GetVideoCode() == u->GetRentalingVideoCode(idx)) {
						video_arr[i]->PlusVideoAmount(1);
					}
				}
				u->ReturnVideo(idx); // 사용자가 비디오 반납
				cout<<"비디오 반납 완료."<<endl;
				Sleep(500);
				system("cls");
				break;
			case 2:
				ShowRentalingVideo(user_idx);
				break;
			case 0:
				cout<<"메뉴로 돌아갑니다."<<endl;
				Sleep(500);
				system("cls");
				return;
			default:
				cout<<"잘못된 입력입니다."<<endl;
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
		cout<<"=== 금액 관리 ==="<<endl;
		cout<<"[1] 돈 충전"<<endl;
		cout<<"[2] 돈 인출"<<endl;
		cout<<"[0] 메뉴 돌아가기"<<endl;
		cout<<"선택: ";
		cin>>choice;
		system("cls");

		switch(choice) {
			case 1:
				cout<<"================"<<endl;
				cout<<"충전할 금액 입력"<<endl;
				cout<<"입력: ";
				cin>>choice;

				accnt_arr[user_idx]->PlusMoney(choice);

				cout<<"충전이 완료되었습니다."<<endl;
				Sleep(500);
				system("cls");
				break;
			case 2:
				cout<<"충전된 금액 인출"<<endl;
				cout<<"입력: ";
				cin>>choice;

				accnt_arr[user_idx]->MinusMoney(choice);

				cout<<"인출이 완료되었습니다."<<endl;
				Sleep(500);
				system("cls");
				break;
			case 0:
				cout<<"메뉴로 돌아갑니다."<<endl;
				Sleep(500);
				system("cls");
				return;
			default:
				cout<<"잘못된 입력입니다."<<endl;
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

		cout<< " === 비디오 대여 프로그램 === " <<endl;
		cout<< " [1] 로그인 " <<endl;
		cout<< " [2] 회원가입 " <<endl;
		cout<< " [0] 종료 " <<endl;
		cout<<"선택: ";
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
				cout << "프로그램을 종료합니다" << endl;
				Sleep(1000);
				system("cls");
				return;
			default:
				cout << "잘못된 입력입니다" << endl;
				Sleep(1000);
				system("cls");
		}
	}
}

void VideoRentalHandler::CreateAccnt(void) {
	string id,pw,name,sex,e_mail;
	int age, choice;

	cout<<"=== 회원가입 ==="<<endl;
	cout<<"생성할 ID: ";
	getline(cin, id);
	if(cin.fail()) {
		cout<<"잘못된 입력입니다."<<endl;
		return;
	}

	for(int i=0; i<accnt_cnt; i++) {
		if(accnt_arr[i]->GetId() == id) {
			cout<< "이미 동일한 id가 존재합니다" <<endl;
			Sleep(1000);
			system("cls");
			return;
		}
	}

	cout<<"================"<<endl;
	cout<<"생성할 PW: ";
	getline(cin, pw);
	if(cin.fail()) {
		cout<<"잘못된 입력입니다."<<endl;
		return;
	}
	cout<<"================"<<endl;
	cout<<"이름: ";
	getline(cin, name);
	if(cin.fail()) {
		cout<<"잘못된 입력입니다."<<endl;
		return;
	}
	cout<<"================"<<endl;
	cout<<"이메일: ";
	getline(cin, e_mail);
	if(cin.fail()) {
		cout<<"잘못된 입력입니다."<<endl;
		return;
	}

	while(1) {
		cout<<"================"<<endl;
		cout<<"성별을 선택해주세요."<<endl;
		cout<<"[1] 남자, [2] 여자"<<endl;
		cout<<"선택: ";
		cin>>choice;
		if(choice==1) {
			sex = "남자";
			break;
		} else if(choice==2) {
			sex = "여자";
			break;
		} else {
			cout<<"다시 입력해주세요."<<endl;
			Sleep(500);
			system("cls");
		}
	}

	while(1) {
		cout<<"================"<<endl;
		cout<<"나이: ";
		cin>>age;
		if(cin.fail()) {
			cout<<"잘못된 입력입니다."<<endl;
			return;
		}
		if(age < 0) {
			cout<<"올바른 형식으로 입력해주세요"<<endl;
			Sleep(1000);
			system("cls");
			continue;
		} else {
			break;
		}
	}

	accnt_arr[accnt_cnt++] = new User(id,pw,name,e_mail,sex,age);
	cout<<"계정 생성을 완료했습니다."<<endl;
	Sleep(1000);
	system("cls");
}

void VideoRentalHandler::Login(void) {
	string id, pw;
	int user_idx;
	int flag=0; // 로그아웃 한 경우

	cout<< "ID : ";
	getline(cin, id);
	cout<< "PW : ";
	getline(cin, pw);

	for(int i=0; i<accnt_cnt; i++) {
		if(accnt_arr[i]->GetId() == id && accnt_arr[i]->GetPw() == pw) {
			cout<< "로그인 성공!" <<endl;
			Sleep(1000);
			system("cls");
			if(accnt_arr[i]->GetIsAdmin() == 1) {
				cout<<" 관리자 계정 확인!"<<endl;
				flag = 1;
				Sleep(1000);
				system("cls");
				AdminMenu(i);
			} else {
				cout<<" 일반 계정 확인!"<<endl;
				flag = 1;
				Sleep(1000);
				system("cls");
				UserMenu(i);
			}
		}
	}

	if(flag == 0) { // 단순 로그인 실패 시
		cout<<"로그인 실패, 계정을 다시 확인해주세요"<<endl;
		Sleep(1000);
		system("cls");
	}

}

void VideoRentalHandler::ShowRentalingVideo(int user_idx) {
	User *user = accnt_arr[user_idx];
	int input;
	if(user->GetRentalingVideoCnt()==0) {
		cout<<"현재 대여 중인 비디오가 없습니다."<<endl;
		Sleep(1000);
		system("cls");
		return;
	}

	cout<<"=== 대여 중인 비디오 목록 ==="<<endl;
	for(int i=0; i<user->GetRentalingVideoCnt(); i++) {
		for(int j=0; j<video_cnt; j++) {
			if(user->GetRentalingVideoCode(i)==video_arr[j]->GetVideoCode()) {
				Video *v = video_arr[j];
				cout<<"["<<i<<"]"<<endl;
				cout << setw(20) << left << "제목" << setw(20) << left << "감독" << setw(15) << "장르" << setw(13) << "상영시간" << setw(13) << "연령제한" << setw(13) << "가격" << endl;
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
		cout<<"=== 사용자 메뉴 ==="<<endl;
		cout<<"[1] 비디오 대여"<<endl;
		cout<<"[2] 비디오 반납"<<endl;
		cout<<"[3] 비디오 검색"<<endl;
		cout<<"[4] 대여 중인 비디오 보기"<<endl;
		cout<<"[5] 잔액 관리"<<endl;
		cout<<"[6] 계정 관리"<<endl;
		cout<<"[7] 백업하기"<<endl;
		cout<<"[0] 로비로 돌아가기"<<endl;
		cout<<"선택: ";
		cin>>choice;

		system("cls");
		switch(choice) {
			case 0:
				cout<<"로비로 돌아갑니다."<<endl;
				Sleep(1000);
				system("cls");
				return;
			case 1: // 비디오 대여
				RentalVideo(user_idx);
				break;
			case 2: // 비디오 반납
				ReturnVideo(user_idx);
				break;
			case 3: // 비디오 검색
				SearchVideo();
				break;
			case 4: // 대여 중인 비디오 보기
				ShowRentalingVideo(user_idx);
				break;
			case 5: // 잔액 관리
				ManageMoney(user_idx);
				break;
			case 6: // 계정 관리
				ManageAccnt(user_idx);
				break;
			case 7: // 백업 하기
				Save();
				break;
			default:
				cout << "잘못된 입력입니다" << endl;
				Sleep(500);
				system("cls");
		}

	}

}

void VideoRentalHandler::AdminMenu(int user_idx) {
	int choice;

	while(1) {
		cout<<"=== 관리자 메뉴 ==="<<endl;
		cout<<"[1] 비디오 추가"<<endl;
		cout<<"[2] 비디오 수정"<<endl;
		cout<<"[3] 비디오 삭제"<<endl;
		cout<<"[4] 비디오 검색"<<endl;
		cout<<"[5] 계정 권한 관리"<<endl;
		cout<<"[6] 계정 관리"<<endl;
		cout<<"[7] 대여 현황 파악"<<endl;
		cout<<"[8] 백업하기"<<endl;
		cout<<"[0] 로비로 돌아가기"<<endl;
		cout<<"선택: ";
		cin>>choice;
		system("cls");

		switch(choice) {
			case 0:
				cout<<"로비로 돌아갑니다."<<endl;
				Sleep(500);
				system("cls");
				return;
			case 1: // 비디오 추가
				AddVideo();
				break;
			case 2: // 비디오 수정
				EditVideo();
				break;
			case 3: // 비디오 삭제
				DeleteVideo();
				break;
			case 4: // 비디오 검색
				SearchVideo();
				break;
			case 5: // 관리자 계정 부여
				AdminAuthority();
				break;
			case 6: // 계정 관리
				ManageAccnt(user_idx);
				break;
			case 7: // 대여 현황 파악
				ManageRental();
				break;
			case 8: // 백업 하기
				Save();
				break;
			default:
				cout << "잘못된 입력입니다" << endl;
				Sleep(500);
				system("cls");
		}

	}
}

void VideoRentalHandler::Save(void) {
// 1.Video_info(비디오 정보), 2.User_accnt(계정), 3.User_rental_video(유저가 대여한 비디오)
// 1. 코드, 제목, 감독, 장르, 상영시간, 연령제한, 대여가격, 재고량
// 2. 아이디, 비번, 성별, 나이, 금액, 포인트, 대여개수, 대여용량, 계정유형, 랭크
// 3. 비디오 코드

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
	//파일이 없을 시 생성
	writefile_1.open("Video_info.txt");
	writefile_2.open("User_accnt.txt");
	writefile_3.open("User_rental_video.txt");

	cout<<"데이터베이스에 정보를 저장합니다."<<endl;
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
	cout<<"비디오 정보를 백업했습니다."<<endl;
	Sleep(500);
// 2. 아이디, 비번, 이름, 이메일, 성별, 나이, 금액, 포인트, 대여개수, 대여용량, 계정유형, 랭크
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
	cout<<"계정 정보를 백업했습니다."<<endl;
	Sleep(500);

	for(int i=0; i<accnt_cnt; i++) {
		for(int j=0; j<accnt_arr[i]->GetRentalingVideoCnt(); j++) {
			u.code = accnt_arr[i]->GetRentalingVideoCode(j);
			writefile_3 << u.code << " ";
		}
		writefile_3 << endl;
	}

	writefile_3.close();
	cout<<"유저 대여 비디오 정보를 백업했습니다."<<endl;
	Sleep(500);

	cout<<"데이터 저장을 완료했습니다."<<endl;
	Sleep(500);
	system("cls");
}

void VideoRentalHandler::Load(void) {
// 1.Video_info(비디오 정보), 2.User_accnt(계정), 3.User_rental_video(유저가 대여한 비디오)
// 1. 코드, 제목, 감독, 장르, 상영시간, 연령제한, 대여가격, 재고량
// 2. 아이디, 비번, 성별, 나이, 금액, 포인트, 대여개수, 대여용량, 계정유형, 랭크
// 3. 비디오 코드

	ifstream readfile_1, readfile_2, readfile_3;
	//ofstream writefile_3; // 유저가 대여한 비디오 정보 저장
	stringstream s5;
	readfile_1.open("Video_info.txt");
	readfile_2.open("User_accnt.txt");
	readfile_3.open("User_rental_video.txt");
	//writefile_3.open("User_rental_video.txt"); // 줄 넘김 용도

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
		cout << "비디오 데이터 파일이 존재하지 않습니다." << endl;
		Sleep(500);
	}

	readfile_1.close();
	cout<<"비디오 데이터 로드 성공."<<endl;
	Sleep(500);
// 2. 아이디, 비번, 이름, 이메일, 성별, 나이, 금액, 포인트, 대여개수, 대여용량, 계정유형, 랭크
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
		cout << "유저 데이터 파일이 존재하지 않습니다." << endl;
		Sleep(500);
	}

	readfile_2.close();
	cout<<"유저 데이터 로드 성공."<<endl;
	Sleep(500);

	string temp;
	int i=0;
	if(readfile_3.is_open()) {
		while (getline(readfile_3, temp)) { //첫 번째 줄부터 읽어오기
			istringstream iss(temp);
			string code;
			while (iss >> code) { //단어로 나눠서 로딩
				accnt_arr[i]->RentalVideo(code);
			}
			i++;
		}
	} else {
		cout<<"유저 대여 비디오 파일이 존재하지 않습니다."<<endl;
	}

	readfile_3.close();
	cout<<"유저 대여 비디오 데이터 로드 성공."<<endl;
	Sleep(500);
	system("cls");
}

int main(void) {
	int flag;

	VideoRentalHandler V(10,10); //최초 계정, 비디오 수용량
	V.SetConsole();

	V.Loby();
}
