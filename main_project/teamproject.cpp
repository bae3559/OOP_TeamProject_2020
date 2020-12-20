#include "teamproject.h"
#include <time.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h> 
#include <sys/stat.h>
#include <direct.h>	
#include <cstdio>
#include <windows.h>
#include <vector>
#include "teamproject.h"


Room::Room() {
	// 처음에 ROOM 클래스가 생성되면 ENTRY_LOG 파일 안에 ROOM 넘버에 따른 로그 파일을 만들어 준다. 
	// ROOM 넘버는 사용자가 입력해주어야한다. 

	int num;
	std::cout << "Room number : ";
	std::cin >> num;
	room_address = num;
	head = NULL;

	//Create the folder
	int mkdir_make = _mkdir("C:\\Entry_logs");

	std::string temp;
	temp = std::to_string(room_address);

	//Create the room entry log
	std::string file_name;
	file_name = "C:\\Entry_logs\\room_" + temp + ".csv";

	std::cout << std::endl;

	std::fstream fs;
	fs.open(file_name);

	if (fs.is_open()) {
		std::cout << "'room_" << temp << "' file already exists!" << std::endl;
		fs.close();
	}

	else {
		fs.open(file_name, std::ios::out);
		std::cout << "'room_" << temp << "' file has been created!" << std::endl;
		fs << "Student ID,Name,Temperature,Entry Time,Exit Time" << std::endl;
		fs.close();
	}

	std::string file_name_1;

	file_name_1 = "C:\\Entry_logs\\students.csv";

	std::fstream fs1;
	fs1.open(file_name_1);

	if (fs1.is_open()) {
		std::cout << "Student file already exists!" << std::endl;
		fs1.close();
	}

	else {
		fs1.open(file_name_1, std::ios::out);
		std::cout << "Student file has been created!" << std::endl;
		fs1 << "Student ID,Name,RFID" << std::endl;
		fs1.close();
	}

	std::cout << std::endl;

}

Room::~Room() {
	Student* deleteNode;
	for (int i = 0; i < student_num; i++) {
		deleteNode = head;
		head = head->next;
		delete deleteNode;
	}
	student_num = 0;
	head = NULL;
}

void Room::register_student() {
	// STUDENT card를 RFID 리더기에 태깅하면 

	int id;
	__int64 rfid;
	std::string name;

	std::cout << "|          Student ID : ";
	std::cin >> id;
	std::cout << "|          Student name : ";
	std::cin >> name;

	std::cout << "|          Tag the RFID : ";
	std::cin >> rfid;

	std::string file_student;

	std::cout << "------------enroll success-----------";

	file_student = "C:\\Entry_logs\\students.csv";

	std::fstream fs1;

	fs1.open(file_student, std::ios::app);

	fs1 << id << "," << name << "," << rfid << std::endl;
	fs1.close();

}

int Room::in(__int64 rfid) {
	int id2;
	std::string name;
	float T;

	std::string file_student;

	file_student = "C:\\Entry_logs\\students.csv";
	std::fstream fs1;
	fs1.open(file_student);


	//Calculate number of enrolled student!
	int enroll_student = 0;
	std::string stu_num_line;
	while (!fs1.eof()) {
		std::getline(fs1, stu_num_line);
		enroll_student++;
	}
	fs1.clear();
	enroll_student = enroll_student - 2; //맨 윗줄이랑 맨 아랫줄 제거

	fs1.seekg(0, std::ios::beg);
	std::string line;
	std::getline(fs1, line, '\n');
	//

	for (int i = 0; i < enroll_student; i++) {

		std::string id_fs;
		std::string name_fs;
		std::string rfcard;

		std::getline(fs1, id_fs, ',');
		std::getline(fs1, name_fs, ',');
		std::getline(fs1, rfcard, '\n');

		std::cout << "id_fs " << id_fs << std::endl;
		std::cout << "name " << name_fs << std::endl;
		std::cout << "rfcard " << rfcard << std::endl;



		__int64 rfcard_fs = stoll(rfcard);

		if (rfcard_fs != rfid) {
			if (i == enroll_student - 1) {
				std::cout << "can't find your rfid card. please enroll the rfid card" << std::endl;
				return 0;
			}
			else {
				continue;
			}
		}
		else {
			id2 = stoi(id_fs);
			name = name_fs;
			std::cout << std::endl << "find the registered rfid" << std::endl;
			break;

		}

	}

	struct Student* new_student = new Student();
	new_student->name = name;
	new_student->ID = id2;
	new_student->RFID = rfid;
	std::cout << "Temperature : ";
	std::cin >> T;
	new_student->temperature = T;


	time_t curTime;

	curTime = time(NULL);

	new_student->in = curTime;

	struct tm newtime;
	__time32_t cur = new_student->in; _time32(&cur);
	_localtime32_s(&newtime, &cur);

	errno_t errNum;
	char buffer[32];

	errNum = asctime_s(buffer, 32, &newtime);
	std::cout << "your enter time : " << buffer << std::endl;

	std::string str(buffer);
	str.pop_back();

	std::string temp;
	temp = std::to_string(room_address);

	std::string file_name;

	file_name = "C:\\Entry_logs\\room_" + temp + ".csv";

	std::fstream fs;

	fs.open(file_name, std::ios::app);

	fs << new_student->ID << "," << new_student->name << "," << new_student->temperature << "," << str << "," << 0 << std::endl;

	fs.close();

	if (student_num == 0) {
		new_student->next = nullptr;
		head = new_student;
		++student_num;
		++all_entry_num;

	}
	else {
		Student* temp = head;
		for (int i = 0; i < student_num - 1; i++) {

			temp = temp->next;

		}
		new_student->next = nullptr;
		temp->next = new_student;

		++student_num;
		++all_entry_num;

	}
	return 1;

}

int Room::out(__int64 rfid) {

	int id;
	std::string file_student;
	file_student = "C:\\Entry_logs\\students.csv";

	std::fstream fs1;

	fs1.open(file_student);

	//Calculate number of enrolled student!
	int enroll_student = 0;
	std::string stu_num_line;
	while (!fs1.eof()) {
		std::getline(fs1, stu_num_line);
		enroll_student++;
	}
	fs1.clear();
	enroll_student = enroll_student - 2; //맨 윗줄이랑 맨 아랫줄 제거

	fs1.seekg(0, std::ios::beg);
	std::string line;
	std::getline(fs1, line, '\n');
	//

	for (int i = 0; i < enroll_student; i++) {

		std::string id_fs;
		std::string name_fs;
		std::string rfcard;

		std::getline(fs1, id_fs, ',');
		std::getline(fs1, name_fs, ',');
		std::getline(fs1, rfcard, '\n');

		__int64 rfcard_fs = stoll(rfcard);


		if (rfcard_fs != rfid) {
			if (i == enroll_student - 1) {
				std::cout << "can't find your rfid card. please enroll the rfid card" << std::endl;
				return 0;
			}
			else {
				continue;
			}
		}
		else {
			id = stoi(id_fs);
			std::cout << std::endl << "find the registered rfid" << std::endl;
			break;

		}

	}


	Student* tempNode = head;


	for (int i = 0; i < student_num; i++) {

		if (tempNode->ID == id) {


			(tempNode)->out = time(NULL);
			struct tm newtime;
			__time32_t curTime = tempNode->out;
			_time32(&curTime);
			_localtime32_s(&newtime, &curTime);

			errno_t errNum;
			char buffer[32];

			errNum = asctime_s(buffer, 32, &newtime);


			std::string str_buf(buffer);
			str_buf.pop_back();

			std::fstream fs;

			std::string temp;
			temp = std::to_string(room_address);

			using namespace std;

			struct enrollee
			{
				string id = "";
				string name = "";
				string temp = "";
				string enter = "";
				string exit = "";
			};

			std::string file_name;
			std::string temp_line;

			file_name = "C:\\Entry_logs\\room_" + temp + ".csv";
			fs.open(file_name, std::ios::in);
			
			struct enrollee enrollData;   // array of structs to store each enrollee and their respective data

			getline(fs, temp_line);


			std::vector  <struct enrollee> logs;

			for (int i = 0; i < all_entry_num; i++)
				
			{
				string id = "";
				string name = "";
				string temp = "";
				string enter = "";
				string exit = "";

				getline(fs, id, ',');
				getline(fs, name, ',');
				getline(fs, temp, ',');
				getline(fs, enter, ',');
				getline(fs, exit, '\n');

				enrollData.id = id;
				enrollData.name = name;
				enrollData.temp = temp;
				enrollData.enter = enter;
				enrollData.exit = exit;

				logs.push_back(enrollData);

			}
			
			string str_id;
			str_id = std::to_string(id);

			string str_zero;
			str_zero = std::to_string(0);

			for (int i = 0; i < logs.size(); i++)
			{
				if (logs[i].id == str_id && logs[i].exit == str_zero)
				{
					logs[i].exit = str_buf;
					std::cout << "your exit time : " << logs[i].exit << std::endl;
				}
			}

			fs.close();

			fs.open(file_name, std::ios::out);
			fs << "Student ID,Name,Temperature,Entry Time,Exit Time" << std::endl;

			for (int i = 0; i < all_entry_num; i++)
			{
				fs << logs[i].id << "," << logs[i].name << "," << logs[i].temp << "," << logs[i].enter << "," << logs[i].exit << std::endl;
			}

			fs.close();


			Student* deleteNode = tempNode;
			head = tempNode->next;
			delete deleteNode;
			--student_num;
			break;
		}

		else if ((tempNode->next)->ID == id) {

			(tempNode->next)->out = time(NULL);
			struct tm newtime;
			__time32_t curTime = (tempNode->next)->out;
			_time32(&curTime);
			_localtime32_s(&newtime, &curTime);

			errno_t errNum;
			char buffer[32];

			errNum = asctime_s(buffer, 32, &newtime);


			std::string str_buf(buffer);
			str_buf.pop_back();

			std::fstream fs;

			std::string temp;
			temp = std::to_string(room_address);

			using namespace std;

			struct enrollee
			{
				string id = "";
				string name = "";
				string temp = "";
				string enter = "";
				string exit = "";
			};


			// open the input file to read
			std::string file_name;
			std::string temp_line;

			file_name = "C:\\Entry_logs\\room_" + temp + ".csv";
			fs.open(file_name, std::ios::in);
			
			struct enrollee enrollData;   // array of structs to store each enrollee and their respective data

			getline(fs, temp_line);


			std::vector  <struct enrollee> logs;

			for (int i = 0; i < all_entry_num; i++)
				
			{
				string id = "";
				string name = "";
				string temp = "";
				string enter = "";
				string exit = "";

				getline(fs, id, ',');
				getline(fs, name, ',');
				getline(fs, temp, ',');
				getline(fs, enter, ',');
				getline(fs, exit, '\n');

				enrollData.id = id;
				enrollData.name = name;
				enrollData.temp = temp;
				enrollData.enter = enter;
				enrollData.exit = exit;

				logs.push_back(enrollData);

			}

			string str_id;
			str_id = std::to_string(id);

			string str_zero;
			str_zero = std::to_string(0);

			for (int i = 0; i < logs.size(); i++)
			{
				if (logs[i].id == str_id && logs[i].exit == str_zero)
				{
					logs[i].exit = str_buf;
					std::cout << "your exit time : " << logs[i].exit << std::endl;
				}
			}

			fs.close();

			fs.open(file_name, std::ios::out);
			fs << "Student ID,Name,Temperature,Entry Time,Exit Time" << std::endl;

			for (int i = 0; i < all_entry_num; i++)
			{
				fs << logs[i].id << "," << logs[i].name << "," << logs[i].temp << "," << logs[i].enter << "," << logs[i].exit << std::endl;
			}


			fs.close();

			Student* deleteNode = tempNode->next;
			tempNode->next = deleteNode->next;
			delete deleteNode;
			--student_num;
			break;
		}
		tempNode = tempNode->next;
	}
	return 1;
}

void Room::show() {

	if (student_num == 0) {
		std::cout << "room is empty" << std::endl;
	}
	else {
		std::cout << "-----------" << "room " << room_address << "-----------" << std::endl;
		Student* tempNode = head;

		for (int i = 0; i < student_num; i++) {
			std::cout << tempNode->ID << std::endl;

			tempNode = tempNode->next;
			if (tempNode == nullptr) {
				break;
			}
		}
		std::cout << "----------------------------------" << std::endl;
	}
}

int Room::checkin(int id) {
	if (student_num == 0) {
		return 0;
	}
	else {
		Student* tempNode = head;

		for (int i = 0; i < student_num; i++) {
			if (tempNode->ID == id) {
				return 1;
			}
			tempNode = tempNode->next;
			if (tempNode == nullptr) {
				break;
			}

		}
	}
	return 0;
}

void Room::search(int id) {

	std::string temp;
	temp = std::to_string(room_address);

	std::string file_name;
	file_name = "C:\\Entry_logs\\room_" + temp + ".csv";

	std::fstream fs;
	//std::ofstream output(file_name);
	fs.open(file_name);


	std::string line;
	std::getline(fs, line, '\n');

	for (int i = 0; i < all_entry_num; i++) {

		std::string fs_id;
		std::string fs_name;
		std::string fs_temperature;
		std::string fs_entry;
		std::string fs_exit;

		std::getline(fs, fs_id, ',');
		std::getline(fs, fs_name, ',');
		std::getline(fs, fs_temperature, ',');
		std::getline(fs, fs_entry, ',');
		std::getline(fs, fs_exit, '\n');

		std::string fs_entry_day = fs_entry.substr(0, 11);
		std::string fs_entry_h = fs_entry.substr(11, 2);
		std::string fs_entry_m = fs_entry.substr(14, 2);
		std::string fs_entry_s = fs_entry.substr(17, 2);

		if (id == stoi(fs_id)) {
			std::cout << fs_name << "  enter at  " << fs_entry << std::endl;

		}

	}
}

void Room::operator[](int id) {
	std::string temp;
	temp = std::to_string(room_address);

	std::string file_name;
	file_name = "C:\\Entry_logs\\room_" + temp + ".csv";

	std::fstream fs;
	fs.open(file_name);


	std::string line;
	std::getline(fs, line, '\n');

	for (int i = 0; i < all_entry_num; i++) {

		std::string fs_id;
		std::string fs_name;
		std::string fs_temperature;
		std::string fs_entry;
		std::string fs_exit;

		std::getline(fs, fs_id, ',');
		std::getline(fs, fs_name, ',');
		std::getline(fs, fs_temperature, ',');
		std::getline(fs, fs_entry, ',');
		std::getline(fs, fs_exit, '\n');

		std::string fs_entry_day = fs_entry.substr(0, 11);
		std::string fs_entry_h = fs_entry.substr(11, 2);
		std::string fs_entry_m = fs_entry.substr(14, 2);
		std::string fs_entry_s = fs_entry.substr(17, 2);

		if (id == stoi(fs_id)) {
			std::cout << fs_name << "  enter at  " << fs_entry << std::endl;

		}

	}

}
