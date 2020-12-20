# DGIST Object-Oriented Programming Team Project!
## 2020 Fall Semester Team Project - Digitalization of Entry Log List for Tracking COVID-19🦠

### Summary
- **Team Member**
  * 강휘현, 류준상, 배현진, 심건희
  
- **Topic Description**
  * 강의실 등의 DGIST 시설을 이용할 때, 학생증(혹은 사원증)을 태그하여 간편히 전자 출입명부를 작성하는 시스템

- **Verified Operating System**
  * Windows / Visual Studio 2019
  * Create a project in Visual Studio and import `main.cpp`, `teamproject.cpp`, and `teamproject.h`. Then, compile and run `main.cpp`.
  
- **About Code**
  * `main.cpp`, `teamproject.cpp`, `teamproject.h` in [main_project](https://github.com/bae3559/OOP_TeamProject_2020/blob/main/main_project)
     - 전자 출입명부의 메인 프로젝트

  * `RFID_students.ino` in [RFID_arduino](https://github.com/bae3559/OOP_TeamProject_2020/blob/main/RFID_arduino)
     - RFID Reader was developed using Arduino Leonardo board and RC522 (RFID module). The Arduino Leonardo board is suitable for connection with our program because the computer recognizes it as an input device such as a keyboard and mouse.
     - When the RFID card is tagged to the RFID module, the code reads the unique ID of the RFID card and transmits it through keyboard input. By default, it is built into the Arduino board, so users do not have to do any extra work, such as compile or run programs, when used. (Simply plug and play)
     - If you want to compile, open this file in the Arduino program and upload it to the Arduino board. The written code needs the MFRC522 library written by GithubCommunity.

  * `UI files` in [ui](https://github.com/bae3559/OOP_TeamProject_2020/blob/main/ui)
     - 편리한 프로그램 사용을 위해 GUI 개발
     - 오류로 인하여 현재 작동하지 않음
___
### Execution
- **There are 6 menus that we can choose.**  

  ```
  0. Register the RFID Card
  1. Enter the room
  2. Exit the room
  3. Check current room status
  4. Check your enter time
  5. Exit the program
  ```

- **Example of excution**

  ***1. Input the Room number***
  
  - If you run the project file successfully, then you can input the room number.
    
  - Then you can check the ‘Entry_logs’ folder in C:\ and ‘room_number.csv’, ‘students.csv’ file.
    
  - If there is already the students.csv file then we don’t make it again. 
    
  ***2. Enroll the RFID Card***
  
  - After choosing the menu 0, you have to input your student ID, Student name, and then just tag your Student Card to the RFID Reader module. The information that you enter is written in the students.csv file. Then, enrollment is finished.
  
  ***3. Enter the Room***
  - When you want to enter the room, you just choose menu 1, and tag the card to the RFID reader. Then you have to input your temperature and you can check these information and entry time in ‘room_number.csv’ file.
  
  ***4.	Check the Current Status of the Room***
  
  - If you choose menu 3, it shows the students who are in the room now.

  ***5.	Exit the Room***

  - When you want to exit the room, you have to choose menu 2. Same with enter, if you tag the card to the reader machine then the process is finished. After that, you can check that the exit time is written in the ‘room_number.csv’ file.

  ***6.	Check the Current Status of the Room***

  - You can check that the room is empty.

  ***7.	Check your Entering Time***

  - Also, you can check your entry time with entering your Student ID. 
___
### Documents
- [**Proposal**](https://github.com/bae3559/OOP_TeamProject_2020/blob/main/Documents/proposal.pdf)

- [**Final Report**](https://github.com/bae3559/OOP_TeamProject_2020/blob/main/Documents/final_report.pdf)

