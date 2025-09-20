#include <iostream>
#include <mysql.h>
#include <windows.h>
#include <sstream>
using namespace std;
const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "your_password";  
const char* DB = "mydb";
class Hostel {
private:
    string Name;
    int Bed, Fee;
public:
    Hostel(string name, int bed, int fee) {
        Name = name;
        Bed = bed;
        Fee = fee;
    }
    string getName() { return Name; }
    int getBed() { return Bed; }
    int getFee() { return Fee; }
};
int main() {
    MYSQL* conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0)) {
        cout << "Error: " << mysql_error(conn) << endl;
        return 1;
    }
    else {
        cout <<"Connected to Database!"<<endl;
    }

    Hostel h("3star", 5, 5000);
    string check = "SELECT * FROM hostel WHERE Name='" + h.getName() + "'";
    if (mysql_query(conn, check.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        if (mysql_num_rows(res) == 0) {
            stringstream ss1, ss2;
            ss1 << h.getBed();
            ss2 << h.getFee();
            string insert = "INSERT INTO hostel(Name, Bed, Fee) VALUES ('" + h.getName() + "', '" + ss1.str() + "', '" + ss2.str() + "')";
            mysql_query(conn, insert.c_str());
        }
        mysql_free_result(res);
    }

    bool exit = false;
    while (!exit) {
        system("cls");
        cout << endl;
        cout << "Hostel Management System" << endl;
        cout << "***********************************"<<endl;
        cout << "1. Reserve Bed" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter Your Choice: ";
        int val;
        cin >> val;
        if (val == 1) {
            string studentName;
            cout << endl;
            cout << "Enter Student Name: ";
            cin >> studentName;
            int totalBeds = 0;
            string getBeds = "SELECT Bed FROM hostel WHERE Name='" + h.getName() + "'";
            if (mysql_query(conn, getBeds.c_str()) == 0) {
                MYSQL_RES* res = mysql_store_result(conn);
                MYSQL_ROW row = mysql_fetch_row(res);
                if (row) totalBeds = atoi(row[0]);
                mysql_free_result(res);
            }

            if (totalBeds > 0) {
                totalBeds--;
                stringstream ss;
                ss << totalBeds;
                string update = "UPDATE hostel SET Bed='" + ss.str() + "' WHERE Name='" + h.getName() + "'";
                mysql_query(conn, update.c_str());
                string insertStudent = "INSERT INTO students(student_name, hostel_name) VALUES('" + studentName + "', '" + h.getName() + "')";
                mysql_query(conn, insertStudent.c_str());
                cout << endl;
                cout << "Bed reserved successfully in " << h.getName() << " for student " << studentName << endl;
                cout << "Please pay "<< h.getFee() <<" Dollars."<< endl;
            }
            else {
                cout << endl;
                cout << "Sorry.No beds available." <<endl;
            }
            Sleep(5000);
        }
        else if (val == 2) {
            exit = true;
            cout << "Goodbye" << endl;
            Sleep(2000);
        }
        else {
            cout << "Invalid Choice" << endl;
            Sleep(2000);
        }
    }

    mysql_close(conn);
    return 0;
}
