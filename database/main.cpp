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
#include <stdio.h>
#include <time.h>
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

int identifier;
void createAndAddMonster(vector<Monster>& monsters)
{
    Monster monster;
    cout << "ID"<<endl;

    monster.id = to_string(identifier+1);
    cout << monster.id<<endl;
    identifier++;
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
    
    time_t t = std::time(0);   // get time now
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
    
    ss<< (now->tm_hour)<<':'<<(now->tm_min)<<':'<<(now->tm_sec);
    monster.time = ss.str();
    ss.str("");
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
    srand ( time(nullptr) );
    Monster monster;
    monster.id = to_string(identifier+1);
    identifier++;
  
    cout << monster.id<<endl;
    string names[] = {"Witch doctor", "Storm spirit", "Terrorblade"};
    monster.name = names[rand()%3];
    int a = rand();
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
int getMaxId(vector<Monster> monsters)
{
    int max=0;
    for (int i = 0; i<monsters.size();i++)
    {
        if (stoi(monsters[i].id)>max)
        {
            max = stoi(monsters[i].id);
        }
    }
    return max;
}
void setLastId(int max)
{
    ofstream file;
    file.open("/Users/mykolamedynsky/Desktop/1semester/database/database/size");
    file << max;
    file.close();
}
void setInfo(vector<Monster> monsters, bool flag){
    fstream file;
    if(!flag)
        file.open("/Users/mykolamedynsky/Desktop/1semester/database/database/data", ios_base::app);
    else
        file.open("/Users/mykolamedynsky/Desktop/1semester/database/database/data");
 
    setLastId(getMaxId(monsters));
    for (int i = 0; i < monsters.size(); i++){
        file << monsters[i].id<< endl;
        file << monsters[i].name << endl;
        file << monsters[i].healthPoint << endl;
        file << monsters[i].damage << endl;
        file << monsters[i].chanceOfUltimateAttack <<endl;
        file << monsters[i].ultimateAttack << endl;
        file << monsters[i].time << endl;
        file << monsters[i].date << endl;
    }
    file.close();
}

void getInfo(vector<Monster>&monsters)
{
    ifstream file;
    file.open("/Users/mykolamedynsky/Desktop/1semester/database/database/data");
    string line;
    Monster monster;
    string a;
    getline(file, a);
    while (!file.eof()){
        //string var;
        getline(file, line);
        if (line=="")
        {
            continue;
        }
        else{
            monster.id = line;
            getline(file, monster.name);
            getline(file, monster.healthPoint);
            getline(file, monster.damage);
            getline(file, monster.chanceOfUltimateAttack);
            getline(file, monster.ultimateAttack);
            getline(file, monster.time);
            getline(file, monster.date);
            monsters.push_back(monster);
        }
    }
    file.close();
}
void demo(vector<Monster> monsters)
{
    getInfo(monsters);
    addRandomMonster(monsters);
    printAll(monsters);
    setInfo(monsters, true);
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
        cout << 10 << " - Exit" << endl;
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
                setInfo(monster, flagForSettingData);
                break;
            case 4:
                getInfo(monster);
                flagForSettingData = true;
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
                flag = false;
                break;
            }
            default:
                cout << "Error"<<endl;
                flag = false;
                break;
        }
    }
}
void launch()
{
    vector<Monster> monsters;
    ifstream file;
    file.open("/Users/mykolamedynsky/Desktop/1semester/database/database/size");
    string a;
    file>>a;
    file.close();
    if (a=="") identifier = 0;
    else identifier = stoi(a);
    interactiveInterface(monsters);
}
int main(int argc, const char * argv[]) {
    launch();
    return 0;
}
