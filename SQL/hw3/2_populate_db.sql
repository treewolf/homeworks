/* set database */
USE cs13435;

/* values for Course */
INSERT INTO Course (CourseNo, CourseName, Department)
VALUES
	('CSC130', 'Data Structure and Algorithms', 'Computer Science'),
	('CSC133', 'Object-Oriented Computer Graphics', 'Computer Science'),
	('CSC134', 'Database Management Systems', 'Computer Science'),
	('CSC137', 'Computer Organization', 'Computer Science'),
	('PHIL4', 'Critical Thinking', 'Philosophy'),
	('MATH26B', 'Calculus I', 'Math');

/* values for Section */
INSERT INTO Section (CourseNo, SectionNo, Instructor)
VALUES
	('CSC130', 5, 'Y. Chen'),
	('CSC133', 12, 'M. Biroge'),
	('CSC133', 8, 'P. Dotti'),
	('CSC133', 6, 'P. Dotti'),
	('CSC134', 3, 'X. Sun'),
	('CSC137', 2, 'G. Morris'),
	('PHIL4', 1, 'H. Abrilia'),
	('MATH26B', 1, 'A. Schick');

/* values for Student
Sources - https://www.randomlists.com/random-addresses
*/
INSERT INTO Student (SSN, FirstName, LastName, Street, City, State, Zip)
VALUES
	(411996126, 'Tom', 'Hansen', '76 Kingston Street', 'Parlin', 'NJ', 32345),
	(262556453, 'Katie', 'Black', '2 Hartford Court', 'York', 'PA', 23478),
	(457634643, 'Timmy', 'Warner', '641 Market Ave.', 'Bethel Park', 'PA', 15102),
	(368989472, 'Austin', 'Powers', '7256 South Blue Spring St.', 'West New York', 'NJ', 07093),
	(789353489, 'Henry', 'Dredge', '169 Selby Street', 'Richmond', 'VA', 23223),
	(123890365, 'Jenny', 'Craigs', '41 South Road', 'Grand Island', 'NE', 68801);

/* values for ClassRoom */
INSERT INTO ClassRoom (RoomNo, Building, Capacity)
Values
	(5029, 'RVR', 30),
	(1002, 'RVR', 25),
	(201, 'BRH', 20),
	(1002, 'LNH', 15),
	(3012, 'AMC', 40);

/* values for Enrolls */
INSERT INTO Enrolls (SSN, SectionNo, CourseNo)
VALUES
        (411996126, 12, 'CSC133'), (411996126, 2, 'CSC137'),
        (262556453, 12, 'CSC133'), (262556453, 2, 'CSC137'), (262556453, 3, 'CSC134'),
        (457634643, 12, 'CSC133'), (457634643, 1, 'PHIL4'), (457634643, 1, 'MATH26B'),
        (368989472, 5, 'CSC130'), (368989472, 8, 'CSC133'), (368989472, 1, 'MATH26B'),
        (789353489, 1, 'PHIL4'), (789353489, 1, 'MATH26B'),
        (123890365, 8, 'CSC133'), (123890365, 2, 'CSC137');

/* values for Exam */
INSERT INTO Exam (CourseNo, SectionNo, ExamNo, E_Date, E_Time)
VALUES
	('CSC130', 5, 13, '2017-04-09', '17:30:00'),
	('CSC130', 5, 2, '2017-04-09', '12:00:00'),
	('CSC133', 8, 1, '2017-04-09', '17:30:00'),
	('CSC133', 8, 2, '2017-03-09', '13:30:00'),
	('CSC133', 12, 4, '2017-06-22', '12:00:00'),
	('CSC134', 3, 1, '2017-07-13', '14:15:00'),
	('CSC134', 3, 2, '2017-07-13', '16:15:00'),
	('CSC134', 3, 3, '2017-08-13', '14:15:00'),
	('CSC137', 2, 1, '2018-03-17', '08:00:00'),
	('CSC137', 2, 2, '2018-03-18', '08:00:00'),
	('MATH26B', 1, 8, '2017-04-09', '13:30:00'),
	('MATH26B', 1, 9, '2017-08-12', '07:00:00'),
	('MATH26B', 1, 2, '2017-04-03', '19:15:00'),
	('PHIL4', 1, 13, '2017-09-03', '19:15:00'),
	('PHIL4', 1, 15, '2017-12-03', '11:45:00'),
	('PHIL4', 1, 17, '2018-01-03', '10:00:00');

/* values for Takes */
INSERT INTO Takes (SSN, CourseNo, SectionNo, ExamNo, Result)
VALUES
	(123890365, 'CSC130', 5, 13, 'A'),
	(123890365, 'CSC133', 8, 2, 'A'),
	(123890365, 'PHIL4', 1, 13, 'A'),
	(123890365, 'MATH26B', 1, 9, 'A'),
	(262556453, 'CSC137', 2, 1, 'A'),
	(262556453, 'MATH26B', 1, 8, 'B'),
	(368989472, 'CSC133', 12, 4, 'B'),
	(368989472, 'MATH26B', 1, 9, 'C'),
	(368989472, 'PHIL4', 1, 17, 'F'),
	(411996126, 'CSC134', 3, 3, 'D'),
	(411996126, 'MATH26B', 1, 8, 'B'),
	(457634643, 'CSC134', 3, 3, 'C'),
	(457634643, 'MATH26B', 1, 2, 'B'),
	(789353489, 'PHIL4', 1, 15, 'B'),
	(789353489, 'CSC133', 12, 4, 'A');

/* values for ConductedIn */
INSERT INTO ConductedIn (RoomNo, Building, CourseNo, SectionNo, ExamNo)
VALUES
	(201, 'BRH', 'CSC137', 2, 1),
	(201, 'BRH', 'CSC134', 3, 1),
	(1002, 'LNH', 'CSC133', 8, 1),
	(1002, 'LNH', 'MATH26B', 1, 2),
	(5029, 'RVR', 'CSC133', 8, 1),
	(3012, 'AMC', 'CSC133', 12, 4),
	(1002, 'RVR', 'PHIL4', 1, 13),
	(1002, 'RVR', 'PHIL4', 1, 15);
