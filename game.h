#ifndef GAME_H
#define GAME_H

#include <string>
#include <fstream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>

struct user
{
    std::string username;
    std::string password;
    int money; 
    std::string medals[6];
    int numMeds;
};
class LoginHandler
{
    private:
        int numUsers;
        struct user* users;
    public:
        struct user currentUser = {"", "", 0, {}, 0};
        int PopUsers();
        int Login(std::string uname, std::string pwd);
        void PrintUsers();
        int LogOut();
};

void BuyMedals(LoginHandler lHandler);
void ModifyRoom(LoginHandler lHandler);
void RunLogin(LoginHandler lHandler);
float PromptForInput(std::string prompt, float minInput, float maxInput); 
float ToNum(std::string s);
int RunProblem();

#endif