CREATE DATABASE IF NOT EXISTS mydb;
USE mydb;
CREATE TABLE IF NOT EXISTS hostel (
    id INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(50) UNIQUE,
    Bed INT,
    Fee INT
);
CREATE TABLE IF NOT EXISTS students (
    id INT AUTO_INCREMENT PRIMARY KEY,
    student_name VARCHAR(50),
    hostel_name VARCHAR(50),
    FOREIGN KEY (hostel_name) REFERENCES hostel(Name)
);
