#include "game.h"


struct medal {
    std::string name;
    int cost;
};

medal medals[6] = {
    {"Bronze", 100},
    {"Silver", 500},
    {"Gold", 1000},
    {"Super", 2000},
    {"Far Out", 5000},
    {"Crazy", 10000},
};

int main()
{
    LoginHandler lHandler = LoginHandler();
    lHandler.PopUsers();
    srand(time(0));

	//your main function lives here
    int x = 1;
	while(x == 1)
    {
        std::cout << std::endl;
        std::cout << "Enter an option:" << std::endl;
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Play a minigame" << std::endl;
        std::cout << "3. Check out Medals" << std::endl;
        std::cout << "4. Quit" << std::endl;
        int input = (int)PromptForInput("What would you like to do?", 1, 4);
        
        switch (input)
        {
            case 1:
                RunLogin(lHandler);
                break;
            case 2:
                lHandler.currentUser.money += RunProblem();
                break;
            case 3:
                ModifyRoom(lHandler);
                break;
            case 4:
                x = 0;
                lHandler.LogOut();
                break;
            default:
                break;
        }
    }
}

int LoginHandler::PopUsers()
{
    std::ifstream accountIn;
    accountIn.open("accounts.txt");
    if (accountIn.is_open())
    {
        accountIn >> this->numUsers;
        this->users = new struct user[numUsers];
        for (int i = 0; i < numUsers; i++)
        {
            std::string uname;
            accountIn >> uname;
            std::string pwd;
            accountIn >> pwd; 
            int uID;
            accountIn >> uID;
            int nMeds;
            accountIn >> nMeds;
            std::string m[6];
            users[i] = {uname, pwd, uID, {}, 0};
            for (int i = 0; i < nMeds; i++)
            {
                accountIn >> users[i].medals[i];
            }
        }
        return 1;
    } else
    {
        std::cout << "File opening error for 'accounts.txt'. Are you sure that the file is located in the directory?" << std::endl;
        return 0;
    }
}

int LoginHandler::LogOut()
{
    if (currentUser.username == "")
    {
        std::cout << std::endl << "Looks like you aren't logged in. Would you like to create an account (y/n):";
        std::string input;
        std::cin >> input;
        if (input == "y")
        {
            std::cout << std::endl << "Enter a username: ";
            std::cin >> input;
            currentUser.username = input;
            std::cout << std::endl << "Enter a password: ";
            std::cin >> input;
            currentUser.password = input;

            std::ofstream outFile ("accounts.txt");
            if (!outFile.is_open())
            {
                std::cout << std::endl << "Error: Problem opening file 'menu.txt'.";
                std::cout << "To save menu changes, resolve the issue and restart the program before altering the menu." << std::endl;
            } else 
            {
                outFile << numUsers + 1 << '\n';
                for (int i = 0; i < numUsers; i++)
                {
                    outFile << users[i].username << " ";
                    outFile << users[i].password << " ";
                    outFile << users[i].money << " "; 
                    outFile << users[i].numMeds << " "; 
                    for (int j = 0; j < currentUser.numMeds; j++)
                        outFile << " " << users[i].medals[j];
                    outFile << '\n';
                }
                outFile << currentUser.username << " ";
                outFile << currentUser.password << " ";
                outFile << currentUser.money << " ";
            }
        }
    }
    
}

int LoginHandler::Login(std::string uname, std::string pwd)
{
    for (int i = 0; i < numUsers; i++)
    {
        if (uname == users[i].username)
        {
            if (pwd == users[i].password)
            {
                currentUser = users[i];
                std::cout << std::endl << "Logged in as " << currentUser.username;
            }
        }
    }
    return 1;
}

void LoginHandler::PrintUsers()
{
    for (int i = 0; i < numUsers; i++)
    {
        std::cout << std::endl << "User: " << users[i].username << " " << users[i].password << " " << users[i].money;
    }
}

int RunProblem()
{
    int cashReward = 0;
    int x = 1;
    while (x == 1)
    {
        int num1 = rand() % 100;
        int num2 = rand() % 100;

        std::cout << std::endl << "Solve the following equation, or type 'b' to exit:";
        std::cout << std::endl << std::endl << num1 << " + " << num2 << " = ";
        std::string input;
        std::cin >> input;
        if (input != "b")
        {
            if ((int)ToNum(input) == num1 + num2) 
            {
                cashReward += num1 + num2;
                std::cout << std::endl << "Correct! You've made $" << cashReward << " so far!";
            }
        } else x = 0;
    }
    return cashReward;
}
void RunLogin(LoginHandler lHandler)
{
    std::cout << std::endl << "Enter your username: ";
    std::string uname;
    std::cin >> uname;
    std::cout << std::endl << "Enter your password: ";
    std::string pwd;
    std::cin >> pwd;
    lHandler.Login(uname, pwd);
}


void ShowMedals(LoginHandler lHandler)
{
    for (int i = 0; i < lHandler.currentUser.numMeds; i++)
    {
        std::cout << std::endl << lHandler.currentUser.medals[i];
    } 
}
void ModifyRoom(LoginHandler lHandler)
{
    int x = 1;
    while (x == 1)
    {
        std::cout << std::endl;
        std::cout << "Enter an option:" << std::endl;
        std::cout << "1. Buy medals" << std::endl;
        std::cout << "2. View medals" << std::endl;
        std::cout << "3. Quit" << std::endl;
        int input = (int)PromptForInput("What would you like to do?", 1, 3);
        switch (input)
        {
            case 1:
                BuyMedals(lHandler);
                break;
            case 2:
                ShowMedals(lHandler);
                break;
            case 3:
                x=0;
                break;
            default:
                break;
        }
    }
}

void BuyMedals(LoginHandler lHandler)
{
    int x = 1;
    while (x == 1)
    {
        std::cout << "Medal Shop......Current Balance: $" << lHandler.currentUser.money << std::endl;

        for (int i = 0; i < sizeof(medals); i++)
        {
            std::cout << std::endl << i + 1 << "." << medals[i].name << "......" << medals[i].cost;
        }
        int input = (int)PromptForInput("What would you like to buy?", 1, sizeof(medals));
        if (medals[input].cost < lHandler.currentUser.money)
        {
            std::cout << std::endl << "You bought the " << medals[input].name << "medal!";
            lHandler.currentUser.money -= medals[input].cost;
            lHandler.currentUser.numMeds++;
            lHandler.currentUser.medals[lHandler.currentUser.numMeds] = medals[input].name;
        }
    }
}

float PromptForInput(std::string prompt, float minInput, float maxInput) 
{
    std::cout << std::endl << std::endl << prompt;
    std::string input;
    std::cin >> input;

    float inputInt = ToNum(input);
    if (inputInt == -1 || inputInt < minInput || inputInt > maxInput)
    { 
        std::cout << "Error: Invalid input";
        PromptForInput(prompt, minInput, maxInput);
    }
    return inputInt;
}

float ToNum(std::string s)
{
    /*
    * The basic logic converts each char into a single digit using its ASCII value.
    * Any value outside of the 48-57 range (the 0-9 numerical range) automatically throws an error.
    * It converts by multipying each digit by a multiple of 10 based on its 'place', and then summing those results
    * So, the number 816 would be processed as (8 x 10^2) + (1 x 10^1) + (6 x 16^0) or 800 + 10 + 6.
    * 
    * In the case of a float input, we store the index of the decimal (defaults to the end). At the return statement, we
    * divide entire result by 10^(string length - decimal location).
    */

    float result = 0;
    int decimalIndex = s.length();
    for (int i = 0; i < s.length(); i++)               
    {                                 
        if (int(s[i]) >= 48 && int(s[i]) <= 57)        
        { 
            /*total +=  digit 0-9 * 10 ^ (inverse position in string)*/
            result += float(s[i] - 48) * pow(10, s.length() - (i + (int)(decimalIndex > i)));
        }
        else if (int(s[i]) == 46 && decimalIndex > i)
        {
            decimalIndex = i;
        } else return -1;
    }
    /*
     *  "Its like atoi(), only better somehow!"
     */
    return (result / pow(10, (s.length() - decimalIndex)));
}