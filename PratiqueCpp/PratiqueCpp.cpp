
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
const string ClientsFileName = "DataClient.txt";
const string UserFileName = "Users.txt";
void ShowTransactionsMenu();
void ShowMainMenue();
void GoBackToTransactionMenue();

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

struct sUser
{
    string UserName;
    string Password;
    short Permission;
};

short AddClient = 2;
short DeleteClient = 4;
short UpdateClient = 8;
short ShowClientList = 16;
short FindClient = 32;

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector <string> vClientData;
    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double
    return Client;
}

sUser ConvertLineUsertoRecord(string Line, string Seperator = "#//#")
{
    sUser User;
    vector <string> vUserData;
    vUserData = SplitString(Line, Seperator);

    User.UserName = vUserData[0];
    User.Password = vUserData[1];
    User.Permission = stoi(vUserData[2]);
    return User;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}
string ConvertRecordUserToLine(sUser User,string Seperater = "#//#")
{
    string stUserRecord = "";
    stUserRecord += User.UserName + Seperater;
    stUserRecord += User.Password + Seperater;
    stUserRecord += to_string(User.Permission ) ;

    return stUserRecord;


}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vClients.push_back(Client);
        }

        MyFile.close();

    }
    return false;
}
bool UserExistsByAccountNumber(string UserName, string FileName)
{

    vector <sUser> vUser;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sUser User;

        while (getline(MyFile, Line))
        {
            User = ConvertLineUsertoRecord(Line);
            if (User.UserName == UserName )
            {
                MyFile.close();
                return true;
            }
            vUser.push_back(User);
        }

        MyFile.close();

    }
    return false;
}



sClient ReadNewClient()
{
    sClient Client;
    cout << "Enter Account Number? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

short ReadPermessionsToSet(sUser User)
{
    User.Permission = 0;

    
    char answer ;
     answer = 'n';

    cout << "show client list y/n ?";
    cin >> answer;

    if (answer == 'y' || answer == 'Y')
        User.Permission = User.Permission | ShowClientList;
    if((User.Permission& ShowClientList) == ShowClientList)
    return User.Permission;

}

sUser ReadNewUser()
{
    sUser User;
    cout << "Enter User Name? ";

    getline(cin >> ws, User.UserName);

    while (UserExistsByAccountNumber(User.UserName, UserFileName))
    {
        cout << "\User with [" << User.UserName << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, User.UserName);
    }

    cout << "Enter Password? ";
    getline(cin, User.Password);

    User.Permission = ReadPermessionsToSet(User);

    return User;
}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

void PrintClientRecordLine(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintListRecordLine(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}



void ShowAllClientsScreen()
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n " << endl;
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}


bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{
    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;
}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    for (sClient& C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }

    return false;
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }

        }

        MyFile.close();
    }

    return vClients;
}

void AddDataLineToFile(string FileName, string  stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }
}



void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewUser()
{
    sUser User;
    User = ReadNewUser();
    AddDataLineToFile(UserFileName,ConvertRecordUserToLine(User));
}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        //system("cls");
        cout << "Adding New Client:\n\n";

        AddNewClient();

        cout << "\n Client Added Successfully , do you want to add more clients? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

void AddNewUsers()
{
    char AddMore = 'Y';
    do
    {
        cout << "Adding New Client:\n\n";
        AddNewUser();
        cout << "\n User Added Successfully , do you want to add more clients? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            //Refresh Clients 
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;

}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);

}

void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();
}


void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}



void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}
bool AddAmountToBalance(string AccountNumber, double Amount, vector <sClient>& vClients)
{
    char Answer = 'Y';
    cout << "\n Are you sure you want to add Amount to Balance ? y/n ?";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClient& c : vClients)
        {
            if (AccountNumber == c.AccountNumber)
            {
                c.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "you add Amount succefuly your Amount Become " << c.AccountBalance;
                return true;
            }

        }

    }

    return false;

}



void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\t Deposit Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);
    double Amount;
    cout << "\nEnter an Amount";
    cin >> Amount;

    if (AddAmountToBalance(AccountNumber, Amount, vClients))
    {
        cout << "\n\nPress any key to go back...";
        system("pause>0");
    }
    else
    {
        cout << "\nOperation canceled or failed.";
        cout << "\n\nPress any key to go back...";
        system("pause>0");
    }


    GoBackToTransactionMenue();

}
void ShowWithrawScren()
{
    cout << "\n-----------------------------------\n";
    cout << "\t Withraw Screen";
    cout << "\n-----------------------------------\n";
    sClient Client;
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);
    double Amount;
    cout << "\nEnter an Amount : ";
    cin >> Amount;

    while (Amount > Client.AccountBalance)
    {
        cout << "\n Amount Exeeds the Balance , you can withdraw up to : " << Client.AccountBalance;

        cout << "\n Please enter an other Amount : ";

        cin >> Amount;
    }

    if (AddAmountToBalance(AccountNumber, Amount * -1, vClients))
    {
        cout << "\n\nPress any key to go back...";
        system("pause>0");
    }
    else
    {
        cout << "\nOperation canceled or failed.";
        cout << "\n\nPress any key to go back...";
        system("pause>0");
    }


    GoBackToTransactionMenue();



}

void ShowTotalBalancerScreen()
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tBalance List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {
            PrintListRecordLine(Client);
            cout << endl;
        }

    double TotalBalance = 0;

    for (sClient Client : vClients)
    {
        TotalBalance += Client.AccountBalance;
    }

    cout << "\n Total Balance : " << TotalBalance;


    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;


}

void ShowAddUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\t Add User Screen";
    cout << "\n-----------------------------------\n";

    AddNewUser();
}

enum enMainMenueOptions
{
    eListClients = 1, eAddNewClient = 2,
    eDeleteClient = 3, eUpdateClient = 4,
    eFindClient = 5, eTransactions = 6,ManageUsers = 7 , eExit = 8
};

enum enTransactionMenuOptions
{
    eDeposit = 1, eWithdraw = 2, eTotalBalancer = 3, eMainMenu = 4
};

enum enManageUsersMenuOptions
{
    eListUsers = 1, AddUser = 2,DeleteUser = 3 , UpdateUser = 4, FindUser = 5, MainMenue = 6
};

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();

}
void GoBackToTransactionMenue()
{
    cout << "\n\nPress any key to go back to Transaction  Menue...";
    system("pause>0");
    ShowTransactionsMenu();

}

short ReadMainMenueOption()
{
    cout << "Choose the number what do you want to do [1 to 8]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

short ReadTransactionMenueOption()
{
    cout << "Choose the number what do you want to do [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}
short ReadManageUsersOption()
{
    cout << "Choose the number what do you want to do [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}
void PerformTransactionMenuOption(enTransactionMenuOptions TransactionMenuOption)
{
    switch (TransactionMenuOption)
    {
    case enTransactionMenuOptions::eDeposit:
        system("cls");
        ShowDepositScreen();
        break;
    case enTransactionMenuOptions::eWithdraw:
        system("cls");
        ShowWithrawScren();
        GoBackToTransactionMenue();
        break;

    case enTransactionMenuOptions::eTotalBalancer:
        system("cls");
        ShowTotalBalancerScreen();
        GoBackToTransactionMenue();
        break;
    case enTransactionMenuOptions::eMainMenu:
        system("cls");
        GoBackToMainMenue();
        break;

    }

}

void PerformManageUsersMenuOption(enManageUsersMenuOptions UsersMenuOption)
{
    switch (UsersMenuOption)
    {
    case enManageUsersMenuOptions :: AddUser :
        system("cls");
        ShowAddUserScreen();

    }
}

void ShowTransactionsMenu()
{
    system("cls");

    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] withdraw  .\n";
    cout << "\t[3] Total Balance.\n";
    cout << "\t[4] Main Menu  .\n";

    cout << "===========================================\n";
    PerformTransactionMenuOption((enTransactionMenuOptions)ReadTransactionMenueOption());

}

void ShowManageUsersMenuScreen()
{
    cout << "===========================================\n";
    cout << "\t\Manage Users  Menue Screen\n";
    cout << "===========================================\n";

    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User  .\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User .\n";
    cout << "\t[5] Find User  .\n";
    cout << "\t[6] Main Menue  .\n";

    PerformManageUsersMenuOption((enManageUsersMenuOptions)ReadManageUsersOption());

}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eAddNewClient:
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eTransactions:
        system("cls");
        ShowTransactionsMenu();
        break;
    case enMainMenueOptions::eExit:
        system("cls");
        ShowEndScreen();
        break;
    case enMainMenueOptions :: ManageUsers:
        system("cls");
        ShowManageUsersMenuScreen();
        GoBackToMainMenue();

    }
}

void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions .\n";
    cout << "\t[7] ManageUsers.\n";
    cout << "\t[8] Exit.\n";
    cout << "===========================================\n";


    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}


int main()
{
    ShowMainMenue();
    system("pause>0");

    return 0;
}