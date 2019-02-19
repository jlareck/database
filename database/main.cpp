//
//  main.cpp
//  database
//
//  Created by Mykola Medynsky on 2/6/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//


#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <sqlite3.h>
#include <stdio.h>
using namespace std;
struct Monster{
    string id;
    string name;
    string healthPoint;
    string damage;
    string chanceOfUltimateAttack;
    string ultimateAttack;
    string date;
    string time;
};
//enum ultimateAttacks{ increaseDamage, extraDamage, healSelf, disableEnemy};

//bool checkId(vector<Monster>& monsters, string id)//перевірка на унікальність ID
//{
//    for (int i = 0; i < monsters.size(); i++)
//    {
//        if(monsters[i].id == id )
//        {
//            return false;
//        }
//    }
//    return true;
//}
//void getInfo(vector<Monster>&monsters) // Для читання з текстового файла
//{
//    ifstream file;
//    file.open("/Users/mykolamedynsky/Desktop/1semester/database/database/data");
//    string line;
//    Monster monster;
//    //  int i = 0;
//    string a;
//    getline(file, a);
//    while (!file.eof()){
//        //string var;
//        getline(file, line);
//        if (line=="")
//        {
//            continue;
//        }
//        else{
//            monster.id = line;
//            getline(file, monster.name);
//            getline(file, monster.healthPoint);
//            getline(file, monster.damage);
//            getline(file, monster.chanceOfUltimateAttack);
//            getline(file, monster.ultimateAttack);
//            getline(file, monster.time);
//            getline(file, monster.date);
//            monsters.push_back(monster);
//        }
//    }
//    file.close();
//}
//
//void setInfo(vector<Monster> monsters, bool flag){//записування в текстовий файл
//    ofstream file;
//    if(!flag)
//        file.open("/Users/mykolamedynsky/Desktop/1semester/database/database/data", ios_base::app);
//    else
//        file.open("/Users/mykolamedynsky/Desktop/1semester/database/database/data");
//    file<<monsters.size()<<endl;
//    for (int i = 0; i < monsters.size(); i++){
//        file << monsters[i].id<< endl;
//        file << monsters[i].name << endl;
//        file << monsters[i].healthPoint << endl;
//        file << monsters[i].damage << endl;
//        file << monsters[i].chanceOfUltimateAttack <<endl;
//        file << monsters[i].ultimateAttack << endl;
//        file << monsters[i].time << endl;
//        file << monsters[i].date << endl;
//
//    }
//    file.close();
//}
void createAndAddMonster(vector<Monster>& monsters)//создає і добавляє в вектор елемент
{
    Monster monster;
    cout << "Enter Name"<<endl;
    cin.ignore();
    getline(cin,monster.name);
    cout << "Enter health points"<<endl;
    cin >> monster.healthPoint;
    cout << "Enter damage" <<endl;
    cin >> monster.damage;
    cout << "Enter chance of ultimate attack in range 0 to 1"<<endl;
    cin >> monster.chanceOfUltimateAttack;
    cout << "Choose ultimate attack:\n 1 - increase damage\n 2 - repeat attack\n 3- healself\n 4 - disable enemy" <<endl;
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            monster.ultimateAttack = "increase damage";
            break;
        case 2:
            monster.ultimateAttack = "repeat attack";
            break;
        case 3:
            monster.ultimateAttack = "healself";
            break;
        case 4:
            monster.ultimateAttack = "disable enemy";
            break;
        default:{
            cout << "There is no option: "<< choice<<endl;
            monster.ultimateAttack = "none";
            break;
        }
            
    }
    time_t t = std::time(0);
    tm* now = std::localtime(&t);

    stringstream ss;
    if (now->tm_mday<10)
    {
        if (now->tm_mon<10)
            ss<<(now->tm_year + 1900) << "-0"<< (now->tm_mon + 1) << "-0" <<  now->tm_mday;
        else
            ss<<(now->tm_year + 1900) << '-'<< (now->tm_mon + 1) << "-0" <<  now->tm_mday;
    }
    else{
        if (now->tm_mon<10)
            ss<<(now->tm_year + 1900) << "-0"<< (now->tm_mon + 1) << '-' <<  now->tm_mday;
        else
            ss<<(now->tm_year + 1900) << '-'<< (now->tm_mon + 1) << '-' <<  now->tm_mday;
    }
    monster.date = ss.str();
    ss.str("");
    char timestamp_buf[10] = "";
    strftime (timestamp_buf, 10,"%H.%M.%S", localtime(&t));
    string timestamp = string(timestamp_buf);
    monster.time = timestamp;
    monsters.push_back(monster);
}

void printOneMonster(Monster monster)
{
    cout << "ID: " << monster.id<<endl;
    cout << "Name: " << monster.name << endl;
    cout << "Healthpoints: " << monster.healthPoint << endl;
    cout << "Damage: " << monster.damage << endl;
    cout << "Chance of ultimate attack: " << monster.chanceOfUltimateAttack << endl;
    cout << "Ultimate attack: " << monster.ultimateAttack << endl;
    cout << "Time of creation the monster: "<<monster.time << endl;
    cout << "Date of creation the monster: "<<monster.date << endl;
    cout << endl;
}
void addRandomMonster(vector<Monster>& monsters)
{
   // ctime(0);
    srand ( time(nullptr) );
    Monster monster;

    string names[] = {"Witch doctor", "Medusa", "Terrorblade", "Storm spirit", "Pudge", "Anti-Mage", "Phantom Assasin"};
    monster.name = names[rand()%7];
    int a = rand()%100;
    monster.healthPoint = to_string(a);
    monster.damage = to_string(a);
    monster.chanceOfUltimateAttack = to_string(0.5);
    monster.ultimateAttack = "increase damage";
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    stringstream ss;
    if (now->tm_mday<10)
    {
        if (now->tm_mon<10)
            ss<<(now->tm_year + 1900) << "-0"<< (now->tm_mon + 1) << "-0" <<  now->tm_mday;
        else
            ss<<(now->tm_year + 1900) << '-'<< (now->tm_mon + 1) << "-0" <<  now->tm_mday;
    }
    else{
        if (now->tm_mon<10)
            ss<<(now->tm_year + 1900) << "-0"<< (now->tm_mon + 1) << '-' <<  now->tm_mday;
        else
            ss<<(now->tm_year + 1900) << '-'<< (now->tm_mon + 1) << '-' <<  now->tm_mday;
    }
    monster.date = ss.str();
    ss.str("");
    
    char timestamp_buf[10] = "";
    strftime (timestamp_buf, 10,"%H.%M.%S", localtime(&t));
    string timestamp = string(timestamp_buf);
    monster.time = timestamp;
    printOneMonster(monster);
    monsters.push_back(monster);
    
}
void addRandomMonster(vector<Monster>& monsters, int i)//для бенчмарка бінарного файла
{
    srand ( time(nullptr) );
    Monster monster;
   monster.id = to_string(i);
//    identifier++;

   // cout << monster.id<<endl;
    string names[] = {"Witch doctor", "Medusa", "Terrorblade", "Storm spirit", "Pudge", "Anti-Mage","Phantom Assasin"};
    monster.name = names[rand()%7];
    int a = rand()%100;
    monster.healthPoint = to_string(a);
    monster.damage = to_string(a);
    monster.chanceOfUltimateAttack = to_string(0.5);
    monster.ultimateAttack = "increase damage";
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    stringstream ss;
    if (now->tm_mday<10)
    {
        if (now->tm_mon<10)
            ss<<(now->tm_year + 1900) << "-0"<< (now->tm_mon + 1) << "-0" <<  now->tm_mday;
        else
            ss<<(now->tm_year + 1900) << '-'<< (now->tm_mon + 1) << "-0" <<  now->tm_mday;
    }
    else{
        if (now->tm_mon<10)
            ss<<(now->tm_year + 1900) << "-0"<< (now->tm_mon + 1) << '-' <<  now->tm_mday;
        else
            ss<<(now->tm_year + 1900) << '-'<< (now->tm_mon + 1) << '-' <<  now->tm_mday;
    }
    monster.date = ss.str();
    ss.str("");
    
    char timestamp_buf[10] = "";
    strftime (timestamp_buf, 10,"%H.%M.%S", localtime(&t));
    string timestamp = string(timestamp_buf);
    monster.time = timestamp;
    monsters.push_back(monster);
    
}
void printAll(vector<Monster>monster)
{
    for (int i = 0; i< monster.size(); i++)
    {
        cout << "ID: " << monster[i].id<<endl;
        cout << "Name: " << monster[i].name << endl;
        cout << "Healthpoints: " << monster[i].healthPoint << endl;
        cout << "Damage: " << monster[i].damage << endl;
        cout << "Chance of ultimate attack: " << monster[i].chanceOfUltimateAttack << endl;
        cout << "Ultimate attack: " << monster[i].ultimateAttack << endl;
        cout << "Time of creation the monster: "<<monster[i].time << endl;
        cout << "Date of creation the monster: "<<monster[i].date << endl;
        cout << endl;
    }
}


void findMonsterByName(string name, vector<Monster> monsters)
{
    
    for (int i = 0; i < monsters.size(); i++)
    {
        int j = 0;
        while (monsters[i].name[j] == name[j])
        {
            j++;
        }
        if (j==name.length())
            printOneMonster(monsters[i]);
    }
}
void findMonsterByUltimateAttack(string ult, vector<Monster> monsters )
{
    bool flag = false;
    for (int i = 0; i < monsters.size(); i++)
    {
        if (ult == monsters[i].ultimateAttack)
        {
            printOneMonster(monsters[i]);
            flag = true;
        }
    }
    if (!flag) cout << "There is no monster with "<< ult<<endl;
}
void findMonsterByRangeOfDamage(int lower, int higher, vector<Monster> monsters)
{
    
    for(int i = 0; i < monsters.size(); i++)
    {
        
        if (stoi(monsters[i].damage)<higher && stoi(monsters[i].damage)>lower){
            printOneMonster(monsters[i]);
            
        }
    }
}
void findMonsterAfterSomeDate(string date,string time, vector<Monster> monsters)
{
    for(int i = 0; i < monsters.size(); i++)
    {
        if (monsters[i].date > date){
            printOneMonster(monsters[i]);
        }
        else if(date==monsters[i].date)
            if (monsters[i].time>time)
                printOneMonster(monsters[i]);
    }
}
int getSize()//по-суті кількість елементів в массиві може виступати за останнє id тому зчитування кількості елементів я виділив в окрему функцію
{
    ifstream file;
    
    file.open("/Users/mykolamedynsky/Desktop/1semester/database/database/size.bin",ios_base::binary|ios_base::in);
  //  file.clear();
    int size;
    //file.seekg(0);
    file.read ((char*)&size,sizeof(int));
    file.close();
    
    return size;
}
void setInfoInBinaryFile(vector<Monster> monsters , bool& flag){
    ofstream file;

    if (!flag){
        file.open("/Users/mykolamedynsky/Desktop/1semester/database/database/data.bin",ios_base::binary|ios_base::out);
        flag = true;
    }
    else
        file.open("/Users/mykolamedynsky/Desktop/1semester/database/database/data.bin",ios_base::binary|ios_base::out|ios_base::app);
    
  //  int pos = file.tellp();
//    file.seekp(pos);
    int size = monsters.size();
    file.write((char*)&monsters[0], size * sizeof(Monster));
    file.close();
}
void setSizeInBinaryFile(vector<Monster> monsters)
{
    ofstream sizeFile;
    sizeFile.open("/Users/mykolamedynsky/Desktop/1semester/database/database/size.bin", ios_base::binary|ios_base::out);

    int size = monsters.size();

    sizeFile.write((char*)&size, sizeof(size));
    sizeFile.close();
}

vector<Monster> readFromBinaryFile(int size)
{
    ifstream file;
    file.open("/Users/mykolamedynsky/Desktop/1semester/database/database/data.bin",ios_base::binary|ios_base::in);
    vector<Monster> monsters(size);
    cout<<"SIZE" << size<<endl;
    file.read ((char*)&monsters[0],monsters.size()* sizeof(Monster));
    file.close();
    return monsters;
}

void deleteMonsterByID(vector<Monster>&monsters, string id)
{
    int size = monsters.size();
    for (int i = 0; i < size; i++)
    {
        if (monsters[i].id==id) monsters.erase(monsters.begin()+i);
    }
}

vector<Monster> readFromSqlTable()
{
    vector<Monster> monsters;
    sqlite3 *db;
    int rc;
    Monster monster;
    sqlite3_stmt *res;
    rc = sqlite3_open("/Users/mykolamedynsky/Desktop/1semester/sqliteTest/Monsters.db", &db);
    if ( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
    }
    rc = sqlite3_prepare_v2(db, "SELECT ID, name, Health, Damage, UltChance, UltType, Date, Time FROM Monster Where Id", -1, &res, 0);
    while(sqlite3_step(res) == SQLITE_ROW)
    {
        monster.id = string(reinterpret_cast<const char *>(sqlite3_column_text(res, 0)));
        monster.name = string(reinterpret_cast<const char *>(sqlite3_column_text(res, 1)));
        monster.healthPoint = string(reinterpret_cast<const char *>(sqlite3_column_text(res, 2)));
        monster.damage = string(reinterpret_cast<const char *>(sqlite3_column_text(res, 3)));
        monster.chanceOfUltimateAttack = string(reinterpret_cast<const char *>(sqlite3_column_text(res, 4)));
        monster.ultimateAttack = string(reinterpret_cast<const char *>(sqlite3_column_text(res, 5)));
        monster.date = string(reinterpret_cast<const char *>(sqlite3_column_text(res, 6)));
        monster.time = string(reinterpret_cast<const char *>(sqlite3_column_text(res, 7)));
        monsters.push_back(monster);
        
    }
    sqlite3_close(db);
    return monsters;
}
int insertIntoSqlTable(vector<Monster> monsters) {
    sqlite3 *db;
    int rc = sqlite3_open("/Users/mykolamedynsky/Desktop/1semester/sqliteTest/Monsters.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }
    for (int i = 0; i<monsters.size(); i++){
      
        char name [monsters[i].name.length()+1];
        strcpy(name, monsters[i].name.c_str());
        
        char health [monsters[i].healthPoint.length()+1];
        strcpy(health, monsters[i].healthPoint.c_str());
        
        char damage [monsters[i].damage.length()+1];
        strcpy(damage, monsters[i].damage.c_str());
        
        char ultChance [monsters[i].chanceOfUltimateAttack.length()+1];
        strcpy(ultChance, monsters[i].chanceOfUltimateAttack.c_str());
        
        char ultType [monsters[i].ultimateAttack.length()+1];
        strcpy(ultType, monsters[i].ultimateAttack.c_str());
        
        char date [monsters[i].date.length()+1];
        strcpy(date, monsters[i].date.c_str());
        
        char time [monsters[i].time.length()+1];
        strcpy(time, monsters[i].time.c_str());
        
        
        sqlite3_stmt *stmt;
        if (monsters[i].id==""){
        sqlite3_prepare_v2(db, "INSERT INTO Monster (Name, Health, Damage, UltChance, UltType, Date, Time) values (?2, ?3, ?4, ?5, ?6, ?7, ?8);", -1, &stmt, NULL);
            
        }
        else{
            sqlite3_prepare_v2(db, "INSERT INTO Monster (ID, Name, Health, Damage, UltChance, UltType, Date, Time) values (?1, ?2, ?3, ?4, ?5, ?6, ?7, ?8);", -1, &stmt, NULL);
            int id = stoi(monsters[i].id);
             sqlite3_bind_int(stmt, 1, id);
        }
       
        sqlite3_bind_text(stmt, 2, name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, health, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, damage, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, ultChance, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, ultType, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 7, date, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 8, time, -1, SQLITE_STATIC);
      
        rc = sqlite3_step(stmt);
    }
    sqlite3_close(db);
    return 0;
}

void demo(vector<Monster> monsters)
{
    insertIntoSqlTable(monsters);
    addRandomMonster(monsters);
    monsters = readFromSqlTable();
    cout << "All monsters"<<endl;
    printAll(monsters);
    cout << "Searching by beginning name Ter" <<endl;
    findMonsterByName("Ter", monsters);
    cout << "Searching by range of damage from 25 to 70" << endl;
    findMonsterByRangeOfDamage(25, 70, monsters);
    cout << "Searching by ultimate attack increase damage"<<endl;
    findMonsterByUltimateAttack("increase damage", monsters);
    cout << "Searching monsters after time: 11.31.01 and date: 2019-02-10" <<endl;
    findMonsterAfterSomeDate("2019-02-10", "11.31.01", monsters);
    cout << "The end"<<endl;
}
void deleteAllDataFromSqlite()
{
    sqlite3 *db;
    int rc;
    rc = sqlite3_open("/Users/mykolamedynsky/Desktop/1semester/sqliteTest/Monsters.db", &db);
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "Delete From Monster", -1, &stmt, NULL);
    rc = sqlite3_step(stmt);
    sqlite3_close(db);
}
void deleteDataByID(int id)
{
    sqlite3 *db;
    int rc;
    rc = sqlite3_open("/Users/mykolamedynsky/Desktop/1semester/sqliteTest/Monsters.db", &db);
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "Delete From Monster Where ID = ?1", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    sqlite3_close(db);
}
void benchmarkSql( int n)
{
    deleteAllDataFromSqlite();
    vector<Monster>monsters;
    int time=0;
    int k = 0;
    while(time<10){
        int start_time = clock();
        for(int i = k; i < n; i++)
        {
            addRandomMonster(monsters);
        }
        insertIntoSqlTable(monsters);
        monsters = readFromSqlTable();
        cout << "Searching by beginning name Ter" <<endl;
        findMonsterByName("Ter", monsters);
        cout << "Searching by range of damage from 25 to 70" << endl;
        findMonsterByRangeOfDamage(25, 70, monsters);
        cout << "Searching by ultimate attack increase damage"<<endl;
        findMonsterByUltimateAttack("increase damage", monsters);
        cout << "Searching monsters after time: 11.31.01 and date: 2019-02-10" <<endl;
        findMonsterAfterSomeDate("2019-02-09", "11.31.01", monsters);
        cout << "The end"<<endl;
        int end_time = clock();
        k = n;
        n*=2;
        cout<< "Time of working" <<( end_time-start_time)/(1000*320)<<endl;
        time = (end_time-start_time)/(1000*320);
    }
    cout << "Number of added elements: " << monsters.size();
   
}
void benchmarkBinary(int n)
{
    int time = 0;

    int k = 0;
    fstream sizeFile;
    sizeFile.open("/Users/mykolamedynsky/Desktop/1semester/database/database/size.bin",ios_base::binary|ios_base::out);

     vector<Monster>monsters;
    bool flag = false;
    while(time<10){         // поки час не перевищив 10 секунд
     
         // встановлюємо id починаючи з останнього елемента (кількість елементів = id)
        int start_time = clock();
        //k = getSize();
        cout << getSize()<<endl;
       
        for(int i = getSize(); i < n; i++)
        {
            cout<< "Size " << i<<endl;
         
            addRandomMonster(monsters, i);
         
        }
        setInfoInBinaryFile(monsters, flag);
        setSizeInBinaryFile(monsters);
        monsters = readFromBinaryFile(getSize());
        cout << "Searching by beginning name Ter" <<endl;
        findMonsterByName("Ter", monsters);
        cout << "Searching by range of damage from 25 to 70" << endl;
       findMonsterByRangeOfDamage(25, 70, monsters);
        cout << "Searching by ultimate attack increase damage"<<endl;
        findMonsterByUltimateAttack("increase damage", monsters);
        cout << "Searching monsters after time: 11.31.01 and date: 2019-02-10" <<endl;
        findMonsterAfterSomeDate("2019-02-09", "11.31.01", monsters);
        cout << "The end"<<endl;
        int end_time = clock();
        cout<< "Time of working" <<( end_time-start_time)/(1000*320)<<endl;
        time =( end_time-start_time)/(1000*320);
        
        n*=2;
    }

    cout<< "Number of added elements" << monsters.size()<<endl;
    int size = 0;
    sizeFile.write((char*)&size, sizeof(size));
    sizeFile.close();
 
}
void interactiveInterface(vector<Monster> monster)
{
    bool flag = true, flagForSettingData = false;
    int action;
    while (flag)
    {
        cout << 1 << " - Create new monster" << endl;
        cout << 2 << " - Print all monsters" << endl;
        cout << 3 << " - Save data in file" << endl;
        cout << 4 << " - Restore data" << endl;
        cout << 5 << " - Find by beginning of name" << endl;
        cout << 6 << " - Find by range of damage" << endl;
        cout << 7 << " - Find by Ultimate attack"<<endl;
        cout << 8 << " - Find monster that was created after some time" << endl;
        cout << 9 << " - Create random monster" <<endl;
        cout << 10 << " - Delete monster by ID" <<endl;
        cout << 11 << " - Exit" << endl;
        cout << "Enter action" << endl;
        cin >> action;
        switch (action) {
            case 1:
                createAndAddMonster(monster);
                break;
            case 2:
                printAll(monster);
                break;
            case 3:
              //  setInfo(monster, flagForSettingData);
                insertIntoSqlTable(monster);
                 cout << "Data has been saved"<<endl;
                break;
            case 4:
               // getInfo(monster);
             //   flagForSettingData = true;
                monster = readFromSqlTable();
                cout << "Data has been read"<<endl;
                break;
            case 5:{
                string name;
                cout << "Enter the name" <<endl;
                cin.ignore();
                getline(cin, name);
                findMonsterByName(name, monster);
                break;
            }
            case 6:{
                int lower, upper;
                cout << "Enter lower range" <<endl;
                cin >> lower;
                cout << "Enter upper range" <<endl;
                cin >> upper;
                findMonsterByRangeOfDamage(lower, upper, monster);
                break;
            }
            case 7: {
                cout << "Enter ultimate attack (string) " <<endl;
                string ult;
                cin.ignore();
                getline(cin, ult);
                findMonsterByUltimateAttack(ult, monster);
                break;
            }
            case 8:{
                cout << "Enter date in format yyyy-mm-dd"<<endl;
                string date;
                cin>> date;
                cout << "Enter time in format hh.mm.ss" <<endl;
                string time;
                cin >> time;
                findMonsterAfterSomeDate(date, time, monster);
                break;
            }
            case 9:{
                addRandomMonster(monster);
                break;
            }
            case 10:{
                int id;
                cout << "Enter id of monster that you want to delete"<<endl;
                cin >> id;
                deleteDataByID(id);
                break;
            }
            case 11:{
                flag = false;
                insertIntoSqlTable(monster);
                cout << "Data has been saved. Good bye!"<<endl;
                break;
            }
            default:
                cout << "Error! Unexpected exit"<<endl;
                flag = false;
                break;
        }
    }
}

void launch ()
{
    vector<Monster> monsters;
    int action;
   
    cout << "Enter action" <<endl;
    cout << 1 << " - Interactive mode" <<endl;
    cout << 2 << " - Demo" <<endl;
    cout << 3 << " - Benchmark Sqlite" <<endl;
    cout << 4 << " - Benchmark Binary File" <<endl;
     cin>> action;
    switch (action) {
        case 1:
            interactiveInterface(monsters);
            break;
        case 2:
            demo(monsters);
            break;
        case 3:
            benchmarkSql(5);
            break;
        case 4:
            benchmarkBinary(5);
        default:
            cout << "Error" <<endl;
            break;
    }
    
}
int main()
{
    launch();
   // benchmarkBinary(1);
    //deleteAllDataFromSqlite();
   // benchmarkSql(1);
    //readFromSqlTable(monsters);
    //printAll(monsters);
    return 0;
}
