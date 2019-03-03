//
//  main.cpp
//  database
//
//  Created by Mykola Medynsky on 2/6/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//

#include <ctime>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <sqlite3.h>
#include <stdlib.h>
#include <iostream>
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
void createAndAddMonster(vector<Monster>& monsters)//юзер создає і добавляє в вектор елемент
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
void addRandomMonster(vector<Monster>& monsters)//cтворюється рандомний монстр і виводиться на екран
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


void findMonsterByName(string name, vector<Monster> monsters)//юзер задає початок слова по якому відбуватиметься пошук монстра
{
    bool find = false;
    for (int i = 0; i < monsters.size(); i++)
    {
        int j = 0;
        while (monsters[i].name[j] == name[j])
        {
            j++;
        }
        if (j==name.length()){
            printOneMonster(monsters[i]);
            find =true;
        }
    }
    if (!find)
        cout << "There is no match in system" <<endl;
}
void findMonsterByUltimateAttack(string ult, vector<Monster> monsters )//юзер має ввести точну назву спеціальної атаки
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
    bool find = false;
    for(int i = 0; i < monsters.size(); i++)
    {
        
        if (stoi(monsters[i].damage)<higher && stoi(monsters[i].damage)>lower){
            printOneMonster(monsters[i]);
            find = true;
            
        }
    }
    if(!find)
        cout <<"There is no match in system" <<endl;
}
void findMonsterAfterSomeDate(string date,string time, vector<Monster> monsters) {
    bool find = false;
    for(int i = 0; i < monsters.size(); i++)
    {
        if (monsters[i].date > date){
            printOneMonster(monsters[i]);
            find  = true;
        }
        else if(date==monsters[i].date)
            if (monsters[i].time>time){
                printOneMonster(monsters[i]);
                find = true;
            }
    }
    if(!find)
        cout << "There is no match in system" <<endl;
}
int getSize()//по-суті кількість елементів в массиві може виступати за останнє id тому зчитування кількості елементів я виділив в окрему функцію
{
    ifstream file;
    
    file.open("/Users/mykolamedynsky/Desktop/1semester/database/database/size.bin",ios_base::binary|ios_base::in);//вкажіть шлях до файла
  
    int size;
    
    file.read ((char*)&size,sizeof(int));
    file.close();
    
    return size;
}
void setInfoInBinaryFile(vector<Monster> monsters , bool& flag)//записування даних в бінарний файл flag - виступає як змінна яка показує чи відкривається цей файл вперше під час запуску програми
{
    ofstream file;

    if (!flag){ // якщо вперше то файл просто перезаписується новими данними
        file.open("/Users/mykolamedynsky/Desktop/1semester/database/database/data.bin",ios_base::binary|ios_base::out);//вкажіть шлях до файла
        flag = true;
    }
    else// якщо ні то до файла додається інформація в кінець
        file.open("/Users/mykolamedynsky/Desktop/1semester/database/database/data.bin",ios_base::binary|ios_base::out|ios_base::app);//вкажіть шлях до файла

    int size = monsters.size();
    file.write((char*)&monsters[0], size * sizeof(Monster));
    file.close();
}
void setSizeInBinaryFile(vector<Monster> monsters)//записування кількості елементів в окремий файл
{
    ofstream sizeFile;
    sizeFile.open("/Users/mykolamedynsky/Desktop/1semester/database/database/size.bin", ios_base::binary|ios_base::out);//вкажіть шлях до файла

    int size = monsters.size();

    sizeFile.write((char*)&size, sizeof(size));
    sizeFile.close();
}

vector<Monster> readFromBinaryFile(int size)
{
    ifstream file;
    file.open("/Users/mykolamedynsky/Desktop/1semester/database/database/data.bin",ios_base::binary|ios_base::in);//вкажіть шлях до файла
    vector<Monster> monsters(size);
    file.read ((char*)&monsters[0],monsters.size()* sizeof(Monster));
    file.close();
    return monsters;
}

vector<Monster> readFromSqlTable()//зчитування з sqlite бази данних
{
    vector<Monster> monsters;
    sqlite3 *db;
    int rc;
    Monster monster;
    sqlite3_stmt *stmt;
    rc = sqlite3_open("/Users/mykolamedynsky/Desktop/1semester/database/database/Monsters.db", &db);//вкажіть шлях до файла
    if ( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
    }
    rc = sqlite3_prepare_v2(db, "SELECT ID, name, Health, Damage, UltChance, UltType, Date, Time FROM Monster Where Id", -1, &stmt, 0);
   
    while(sqlite3_step(stmt) == SQLITE_ROW)
    {
        monster.id = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        monster.name = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
        monster.healthPoint = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
        monster.damage = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));
        monster.chanceOfUltimateAttack = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)));
        monster.ultimateAttack = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5)));
        monster.date = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6)));
        monster.time = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7)));
        monsters.push_back(monster);
        
    }
    
    sqlite3_close(db);
    return monsters;
}
int insertIntoSqlTable(vector<Monster>& monsters)//записування в sqlite базу данних
{
    sqlite3 *db;
    int rc = sqlite3_open("/Users/mykolamedynsky/Desktop/1semester/database/database/Monsters.db", &db);//вкажіть шлях до файла
    
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }
    for (int i = 0; i<monsters.size(); i++){
        const char* name = monsters[i].name.c_str();
    //    strcpy(name, monsters[i].name.c_str());
        
        const char* health = monsters[i].healthPoint.c_str();
     //   strcpy(health, monsters[i].healthPoint.c_str());
        
        const char* damage = monsters[i].damage.c_str();
      //  strcpy(damage, monsters[i].damage.c_str());
        
        const char* ultChance = monsters[i].chanceOfUltimateAttack.c_str();
        //strcpy(ultChance, monsters[i].chanceOfUltimateAttack.c_str());
        
        const char* ultType = monsters[i].ultimateAttack.c_str();
       // strcpy(ultType, monsters[i].ultimateAttack.c_str());
        
        const char* date = monsters[i].date.c_str();
  //      strcpy(date, monsters[i].date.c_str());
        
        const char* time = monsters[i].time.c_str();
      //  strcpy(time, monsters[i].time.c_str());
        
        
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
        monsters[i].id = to_string(sqlite3_last_insert_rowid(db));
        cout << monsters[i].id<<endl;
    }
   
    sqlite3_close(db);
    return 0;
}

void demo()
{
    vector<Monster> monsters;
    addRandomMonster(monsters);
    insertIntoSqlTable(monsters);
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
void deleteAllDataFromSqlite()//видалення усіх елементів(для бенчмарка щоб при запуску цього режиму база даних була чиста)
{
    sqlite3 *db;
    int rc;
    rc = sqlite3_open("/Users/mykolamedynsky/Desktop/1semester/database/database/Monsters.db", &db);//вкажіть шлях до файла
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "Delete From Monster", -1, &stmt, NULL);
    rc = sqlite3_step(stmt);
    sqlite3_close(db);
}
void deleteDataByID(int id)//функція яка видаляє з бази даних Sqlite
{
    sqlite3 *db;
    int rc;
    rc = sqlite3_open("/Users/mykolamedynsky/Desktop/1semester/database/database/Monsters.db", &db);//вкажіть шлях до файла
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "Delete From Monster Where ID = ?1", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    sqlite3_close(db);
}

int get_file_size(std::string filename) // path to file
{
    FILE *p_file = NULL;
    p_file = fopen(filename.c_str(),"rb");
    fseek(p_file,0,SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return size;
}
void vacuum()
{
    sqlite3 *db;
    int rc;
    rc = sqlite3_open("/Users/mykolamedynsky/Desktop/1semester/database/database/Monsters.db", &db);//вкажіть шлях до файла
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "Vacuum", -1, &stmt, NULL);
    rc = sqlite3_step(stmt);
    sqlite3_close(db);
}
void benchmarkSql( int n)//якщо що в бенчмарку на початку видаляються всі елементи
{
    deleteAllDataFromSqlite();
    vacuum();
    vector<Monster>monsters;
    string file = "/Users/mykolamedynsky/Desktop/1semester/database/database/Monsters.db";
    
    double time=0;
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
        cout<< "For " << n << " elements "<< " Bytes: " <<  get_file_size(file)<< "  Time of working (seconds): " <<(double)( end_time-start_time)/(1000*320)<<endl;
        time = (end_time-start_time)/(1000*320);
    }
    cout << "Number of added elements: " << monsters.size();
    cout << "Time of working: "<<time<<endl;
   
}

void benchmarkBinary(int n)//в бенчмарку на початку видаляються всі елементи. І я невпевнений в тому що правильно працює ця функція тому що в дивному порядку іноді виводить елементи, але я не до кінця розумію чому
{
    int time = 0;
    fstream sizeFile;
    sizeFile.open("/Users/mykolamedynsky/Desktop/1semester/database/database/size.bin",ios_base::binary|ios_base::out);//вкажіть шлях до файла
    int size = 0;
    sizeFile.write((char*)&size, sizeof(size));
    sizeFile.close();
    vector<Monster>monsters;
    string file = "/Users/mykolamedynsky/Desktop/1semester/database/database/data.bin";
    bool flag = false;
    while(time<10){
        int start_time = clock();
        for(int i = getSize(); i < n; i++)
        {
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
        cout<< "For " << n << " elements "<< " Bytes: " <<  get_file_size(file)<< "  Time of working (seconds): " <<(double)( end_time-start_time)/(1000*320)<<endl;

        time =( end_time-start_time)/(1000*320);
        
        n*=2;
    }
    cout<< "Number of added elements" << monsters.size()<<endl;
    cout<< "Time of working: " <<time<<endl;

 
}
void interactiveInterface()//усі дані збережені в інтерактивному режимі зберігаються в базу даних Sqlite
{
    vector<Monster> monster;
    bool flag = true;
    
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
        cout << 11 << " - Delete all data"<<endl;
        cout << 12 << " - Save data and exit" << endl;
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
                insertIntoSqlTable(monster);
                cout << "Data has been saved"<<endl;
                break;
            case 4:
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
                deleteAllDataFromSqlite();
                cout << "All data has been deleted" <<endl;
                break;
            }
            case 12:{
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
    
    int action;
   
    cout << "Enter action" <<endl;
    cout << 1 << " - Interactive mode" <<endl;
    cout << 2 << " - Demo" <<endl;
    cout << 3 << " - Benchmark Sqlite" <<endl;
    cout << 4 << " - Benchmark Binary File" <<endl;
     cin>> action;
    switch (action) {
        case 1:
            interactiveInterface();
            break;
        case 2:
            demo();
            break;
        case 3:
            benchmarkSql(5);
            break;
        case 4:
            benchmarkBinary(5);
            break;
        default:
            cout << "Error! there is no option " << action <<endl;
            break;
    }
    
}

int main()
{
    launch();
    return 0;
}
