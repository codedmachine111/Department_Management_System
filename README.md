# Department Management System

Developed for the OOPS course at KLETU, this project is a software solution to manage departments. It handles student and division management with ease, making departmental operations simple and efficient.

## Features

- Student Management: Efficient handling of student data, including personal information and academic details.
- Division Management: Organized management of divisions, including class scheduling, and maintaining performance.
- Admin login: Mysql database for storing admin data.

## TODOs
- Assignment management accross all divisions
- All data migration to DB

# Flowchat
- To be updated..
![image](https://github.com/codedmachine111/Department_Management_System/assets/88738817/2a858b55-7130-4a58-bff5-5f7868ff2d5a)

## How to run

1. - Fork the [repo](https://github.com/codedmachine111/Department_Management_System)
   - Clone the repo to your local machine `git clone https://github.com/codedmachine111/Department_Management_System.git`
   - Change current directory `cd Department_Management_System`
2. Install and setup Mysql Server and Workbench: [Tutorial for windows](https://youtu.be/ipDbKQh712U?si=ELb1agFFvPgyUp37)

3. Run the code:
  - `cd src`
  - `g++ main.cpp -o main -Wall -Werror  -I "path/to/your/mysql/server/include" -L "path/to/your/mysql/server/lib" -lmysql`
  - `.\main`
> **Note**
> Replace the "YOUR_DB_PASS" in `main.cpp` with your database password.

## Tools used
<p align="left">
   <img src="https://raw.githubusercontent.com/isocpp/logos/master/cpp_logo.png" height="50px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <img src="https://www.svgrepo.com/show/439233/mysql.svg" height="50px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
</p>

## Contribution

Contributions are welcome! If you have any suggestions, improvements, or bug fixes, please submit a pull request or open an issue on the GitHub repository.

## License

This project is licensed under the [MIT License](LICENSE).
