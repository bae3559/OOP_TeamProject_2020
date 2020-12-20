# Team Project Proposal

## 1. Title of your project
 Digitalization of entry log list for tracking COVID-19

## 2. List team members: names (in Korean), email addresses, and student IDs 

name	Email address	Student ID
배현진	jinny3559@dgist.ac.kr	201811073
류준상	js52065@dgist.ac.kr	201811052
심건희	kh6362@dgist.ac.kr	201811097
강휘현	pull0825@dgist.ac.kr	201711006

## 3. What you plan to do, why & what is hard about it (i.e., motivation) 
Due to COVID-19, entry logs became mandatory. However, handwritten entry logs are often cumbersome, so many people are often not properly filled out because they are annoying. As some face-to-face lectures are also held at DGIST, it will be important information about who entered the same space. Therefore, through the introduction of electric entry logs using student ID cards, the program was planned to make it easier for students to write a list and to easily identify the contact person in the event of a single confirmed case.

## 4. Describe the implementation design of your project, e.g., classes with their member functions / major functions a. Provide details about what you are each in charge of. 
### 1) describe the implementation design of the project
struct student{
	int student ID - get student id using RFID reader machine 
float in time
float out time
float temperature
};
class namelist{
	private :
		// member functions
		struct student;
	public:
		function1 () : A function that gives more warnings when the temperature exceeds a certain value.
		function2 () : A function that provides a list of people in the same time zone by entering a specific ID.
};

( Assume that a one class as storing a list of people entering and leaving a classroom. )

A program that saves entering/leaving time to a room, temperature, and student ID.
The program can provide a list of contacted people who were with an infected person.

### 2) details in what we are in charge of
(this is temporary role, maybe it can be change.)
RFID reader data analysis and preprocessing : 류준상
Class design and make it : 강휘현, 심건희
Program UI design : 배현진

## 5. Experiments you will run and the results you expect 
Input : Student ID of people infected with COVID-19
Result : Return name list with some information(in/out time, temperature, and etc.) of who were in same classroom with infected person(input)

## 6. Metrics of success in detail: it should be quantifiable. 
When you enter the confirmed patient information, the list of contacts that were in the same space as the confirmed person is displayed at a specific time..

## 7. Describe the final project demo plan & what you will report in the final project report
### 1) demo plan
- take a student card to RFID. 
- Through RFID, get a Student ID as an input of the program.  
- launch a terminal to enter the temperature. If the temperature exceeds a certain value, will get a warning message. 
- Save the data with temperature, student ID, and entering time.
- When the student takes RFID again, save the out-time.
- If an infected person appears → entering an infected student’s Id would give us the list of students who were with the infected student.

### 2) In final project report
Explanation of using algorithm and data structure
Sample data and result
Evaluation about our algorithm
Method of get data from RFID
