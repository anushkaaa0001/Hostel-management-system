# Hostel-management-system
Overview
The Hostel Management System is a console-based application designed to streamline the management of hostel facilities, specifically focusing on room allotment, floor management, and tracking student complaints. This system is built to serve two primary user roles: Admin and Student, each with different levels of access and functionalities.

Purpose:
The primary goal of the Hostel Management System is to facilitate the easy management of hostel rooms for administrators and improve the experience for students by providing a simple interface for booking rooms, viewing food menus, and registering complaints.

Key Features:
Admin Role:

Login with Authentication: The system ensures secure admin access through password authentication.
Hostel Management: Admins can add new hostels for different branches, and manage floors and rooms within those hostels.
Room Allotment: Admins can allot available rooms to students, ensuring that room availability is tracked in real-time.
Hostel Status Monitoring: Admins can view the current occupancy status of all hostels, including how many beds are available in each room.
Save Data: All modifications, including room bookings and hostel additions, can be saved to a text file, enabling data persistence between program executions.
Student Role:

Room Booking: Students can book available rooms by selecting a hostel, floor, and room number.
Food Menu: Students can view a weekly food menu, which includes different meals available on each day.
Complaint Registration: Students can register complaints related to room issues (like fan, light, or furniture problems) or personal issues, ensuring their concerns are tracked and addressed.
How It Works:
Admin's Workflow: The admin is responsible for the overall setup of the hostel, including the creation of hostels, floors, and rooms. The admin can allot rooms to students, monitor room availability, and manage data persistence by saving it to a file.

Student's Workflow: The student, after being allotted a room by the admin, can log into the system, view the food menu for the week, and register any complaints regarding their hostel facilities. They can select a room based on availability and enjoy the benefits of the hostel services.

Benefits:
Centralized Hostel Management: The system provides a centralized platform for managing all hostels, floors, and rooms. This eliminates manual tracking and reduces the chances of errors.
Room Availability Tracking: Admins can easily track room availability and prevent overbooking, ensuring that students are allotted only available rooms.
Real-time Complaint Handling: Students have a direct way to register complaints, ensuring their concerns are addressed in a timely manner by hostel management.
Data Persistence: All hostel and room-related data is stored in a text file, allowing the system to retain information across sessions.
Technologies Used:
C++: The program is written in C++, utilizing Object-Oriented Programming (OOP) principles to structure the application efficiently. The system uses data structures such as vectors and structs to manage hostels, floors, and rooms.
File Handling: The program uses file I/O operations to store and retrieve data, ensuring that changes persist between program runs.
Console-Based User Interface: The application runs in the terminal, where users interact with the system via text menus.
Target Users:
Administrators: Users who manage the hostels, add new floors, and allot rooms to students. They also have access to all functionalities, such as saving data to a file.
Students: Users who can book rooms, view the food menu, and register complaints. Students can only access their specific functions and cannot modify hostel data.
