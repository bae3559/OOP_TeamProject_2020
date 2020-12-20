#include <iostream>
#include <time.h>
#ifndef __SE271_project__
#define __SE271_project__

struct Student {
	__int64 RFID;
	int ID;
	std::string name;
	float temperature;
	time_t in;
	time_t out;
	struct Student* next;
};

class Room {

public:
	Room();
	virtual ~Room();
	virtual void register_student();

	virtual int in(__int64 rfid);

	virtual int out(__int64 rfid);

	virtual void show();

	virtual int checkin(int id);

	virtual void search(int id);

	virtual int size() { return student_num; }

	virtual void operator[](int id);

	int room_address;

private:
	int student_num = 0;
	int all_entry_num = 0;
	Student* head = new Student();
};


#endif