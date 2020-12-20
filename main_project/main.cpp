#include "teamproject.h"
#include <Windows.h>
#include <iostream>

int main() {
	Room room;
	int id = 201811073;
	int enter = 1 ;
	int out = 1;
	
	int r;

	std::cout << "This room is " << room.room_address << std::endl<< std::endl;

	while (1) {
		std::cout << "-----------------------------------------" << std::endl;
		std::cout << "0. register the RFID Card!" << std::endl;
		std::cout << "1. enter the room! " << std::endl;
		std::cout << "2. exit the room!" << std::endl;
		std::cout << "3. check current room status!" << std::endl;
		std::cout << "4. check your enter time! and the students who is at the same time! " << std::endl;
		std::cout << "5. exit the program" << std::endl;

		std::cin >> r;
		std::cout << std::endl << std::endl;

		if (r == 0) {
			std::cout << "------------register the rfidcard-----------" << std::endl;
			room.register_student();
			std::cout << std::endl;
		}
		else if (r == 1) {
			std::cout << "Please tag the card " << std::endl;
			__int64 rfid;
			std::cin >> rfid;
			room.in(rfid);
		}
		else if (r == 2) {
			__int64 out_id;
			std::cout << "|                   please tag the CARD                         |" << std::endl;
			std::cin >> out_id;
			room.out(out_id);
		
		}
		else if (r == 3) {
			std::cout << "---------------current status---------------" << std::endl;
			room.show();
		
		}
		else if(r==4){
			int your_id;
			std::cout << "----------------your student_id : ------------" << std::endl;
			std::cin >> your_id;
			room.search(your_id);
		}
		else {
			continue;
		}
	
	}


}
