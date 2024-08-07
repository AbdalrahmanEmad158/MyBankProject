#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
const string ClientsFileName = "MyFile.txt";
const string UserFileName = "MyFileU.txt";
void  ShowMainMenue();
void ShowTransactionsMenue();
void ShowManageUserMenue();
void Login();
enum enMainMenuePermissions { eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64 };
bool CheckAccessPermission(enMainMenuePermissions Permission);
struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};
struct  sUser
{
    string UserName;
    string Password;
    int Permissions;
    bool MarkForDelete = false;
};
sUser CurrentUser;


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
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double
    return Client;
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
sUser ConvertLinetoRecordU(string Line, string Seperator = "#//#")
{
    sUser user;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);

    user.UserName = vClientData[0];
    user.Password = vClientData[1];
    user.Permissions = stoi(vClientData[2]); //cast string to int

    return user;
}

string ConvertRecordToLineU(sUser user, string Seperator = "#//#")
{

    string stUser = "";
    stUser += user.UserName + Seperator;
    stUser += user.Password + Seperator;
    stUser += to_string(user.Permissions);
    return stUser;
}
vector <sClient> LoadCleintsDataFromFile(string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);  //read Mode
    if (MyFile.is_open())
    {
        string line;
        sClient Client;

        while (getline(MyFile, line))
        {
            Client = ConvertLinetoRecord(line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}
vector <sUser> LoadUserssDataFromFileU(string FileName)
{
    vector <sUser> vUser;
    fstream MyFileU;
    MyFileU.open(FileName, ios::in);  //read Mode
    if (MyFileU.is_open())
    {
        string line;
        sUser User;

        while (getline(MyFileU, line))
        {
            User = ConvertLinetoRecordU(line);
            vUser.push_back(User);
        }
        MyFileU.close();
    }
    return vUser;
}
void ShowAccessDeniedMessage()
{
    cout << "\n------------------------------------\n";
    cout << "Access Denied, \nYou dont Have Permission To Do this,\nPlease Conact Your Admin.";
    cout << "\n------------------------------------\n";
}
void PrintClientRecord(sClient Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PinCode;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(12) << Client.Phone;
    cout << "| " << left << setw(12) << Client.AccountBalance;
}
void PrintAllClientsData()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pListClients))
    {
        ShowAccessDeniedMessage();
        return;
    }



    vector <sClient> vClients;
    vClients = LoadCleintsDataFromFile(ClientsFileName);
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
    {
        for (sClient Client : vClients)
        {
            PrintClientRecord(Client);
            cout << endl;
        }
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
}
void PrintUserRecord(sUser User)
{
    cout << "| " << left << setw(15) << User.UserName;
    cout << "| " << left << setw(10) << User.Password;
    cout << "| " << left << setw(10) << User.Permissions;
}
void PrintAllUsersData()
{
    vector <sUser> vUser;
    vUser = LoadUserssDataFromFileU(UserFileName);
    cout << "\n\t\t\t\t\tClient List (" << vUser.size() << ") User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(10) << "Permissions";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    if (vUser.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
    {
        for (sUser& User : vUser)
        {
            PrintUserRecord(User);
            cout << endl;
        }
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient client;
        while (getline(MyFile, Line))
        {
            client = ConvertLinetoRecord(Line);
            if (client.AccountNumber == AccountNumber)
            {
                return true;
            }
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
void AddDataLineToFile(sClient Client, string stDataLine)
{
    fstream MyFile;
    MyFile.open("MyFile.txt", ios::out | ios::app);//append Mode
    //Write Mode
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
    //ConvertRecordToLine(Client);
    AddDataLineToFile(Client, ConvertRecordToLine(Client));
}
void AddMoreClient()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pAddNewClient))
    {
        ShowAccessDeniedMessage();
        return;
    }
    char AddMore = 'y';
    do
    {
        system("cls");
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;

    } while (AddMore == 'y' || AddMore == 'Y');


}
bool UserExistsByUserName(string UserName, string FileName)
{
    vector <sUser> vUser;
    fstream MyFileU;
    MyFileU.open(FileName, ios::in);//read Mode

    if (MyFileU.is_open())
    {
        string Line;
        sUser User;
        while (getline(MyFileU, Line))
        {
            User = ConvertLinetoRecordU(Line);
            if (User.UserName == UserName)
            {
                return true;
            }
        }
        MyFileU.close();

    }
    return false;
}
int ReadPermissionsToSet()
{
    int Permissions = 0;
    char Answer = 'n';
    cout << "\nDo you want to give full access? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        return -1;
    }
    cout << "\nDo you want to give access to : \n ";
    cout << "\nShow Client List? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pListClients;
    }
    cout << "\nAdd New Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pAddNewClient;
    }
    cout << "\nDelete Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pDeleteClient;
    }
    cout << "\nUpdate Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pUpdateClients;
    }
    cout << "\nFind Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pFindClient;
    }
    cout << "\nTransactions? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pTranactions;
    }
    cout << "\nManage Users? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pManageUsers;
    }
    return Permissions;
}
sUser ReadNewUser()
{
    sUser User;
    cout << "Enter User Name? ";
    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, User.UserName);

    while (UserExistsByUserName(User.UserName, UserFileName))
    {
        cout << "\n User with [" << User.UserName << "] already exists, Enter another User Name? ";
        getline(cin >> ws, User.UserName);
    }
    cout << "Enter Password? ";
    getline(cin, User.Password);

    User.Permissions = ReadPermissionsToSet();

    return User;
}
//bool CheckAccessPermission(enMainMenuePermissions Permission)
//{
//    if (.Permissions == enMainMenuePermissions::eAll)
//        return true;
//    if ((Permission & CurrentUser.Permissions) == Permission)
//        return true;
//    else
//        return
//        false;
//}
void AddDataLineToFile(sUser User, string stDataLine)
{
    fstream MyFileU;
    MyFileU.open("MyFileU.txt", ios::out | ios::app);//append Mode
    //Write Mode
    if (MyFileU.is_open())
    {
        MyFileU << stDataLine << endl;
        MyFileU.close();
    }

}

void AddNewUser()
{
    sUser User;
    User = ReadNewUser();
    //ConvertRecordToLineU(User);
    AddDataLineToFile(User, ConvertRecordToLineU(User));
}
void AddMoreUser()
{
    char AddMore = 'y';
    do
    {
        system("cls");
        cout << "Adding New User:\n\n";

        AddNewUser();
        cout << "\nUser Added Successfully, do you want to add more User? Y/N? ";
        cin >> AddMore;

    } while (AddMore == 'y' || AddMore == 'Y');


}
bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{
    vClients = LoadCleintsDataFromFile(ClientsFileName);
    for (sClient& c : vClients)
    {
        if (c.AccountNumber == AccountNumber)
        {
            Client = c;
            return true;
        }
    }
    return false;
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}
void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
}
void ShowFindClientScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pFindClient))
    {
        ShowAccessDeniedMessage();
        return;
    }
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
bool FindUserByUserName(string UserName, vector <sUser> vUsers, sUser& User)
{
    vUsers = LoadUserssDataFromFileU(UserFileName);
    for (sUser& u : vUsers)
    {
        if (u.UserName == UserName)
        {
            User = u;
            return true;
        }
    }
    return false;
}
string ReadUserUserName()
{
    string UserName = "";
    cout << "\nPlease enter UserName? ";
    cin >> UserName;
    return UserName;
}
void PrintUserCard(sUser User)
{
    cout << "\nThe following are the User details:\n";
    cout << "\nUser Name: " << User.UserName;
    cout << "\npassword     : " << User.Password;
    cout << "\nPermissions       : " << User.Permissions;
}
void ShowFindUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind User Screen";
    cout << "\n-----------------------------------\n";

    vector <sUser> vUser = LoadUserssDataFromFileU(UserFileName);
    sUser User;
    string UserName = ReadUserUserName();
    if (FindUserByUserName(UserName, vUser, User))
        PrintUserCard(User);
    else
        cout << "\nuser with user name[" << UserName << "] is not found!";
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

vector <sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);  //read Mode
    if (MyFile.is_open())
    {
        string line = "";
        for (sClient& C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete
                line = ConvertRecordToLine(C);
                MyFile << line << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}
bool MarkUserForDeleteByUsrName(string UserName, vector <sUser>& vUser)
{
    for (sUser& u : vUser)
    {
        if (u.UserName == UserName)
        {
            u.MarkForDelete = true;
            return true;
        }
    }
    return false;
}
vector <sUser> SaveUsersDataToFile(string FileName, vector<sUser> vUser)
{
    fstream MyFileU;
    MyFileU.open(FileName, ios::out);  //read Mode
    if (MyFileU.is_open())
    {
        string line = "";
        for (sUser& u : vUser)
        {
            if (u.MarkForDelete == false)
            {
                //we only write records that are not marked for delete
                line = ConvertRecordToLineU(u);
                MyFileU << line << endl;
            }
        }
        MyFileU.close();
    }
    return vUser;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
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
bool DeleteUserByUserName(string UserName, vector<sUser>& vUser)
{
    sUser User;
    char Answer = 'n';
    if (FindUserByUserName(UserName, vUser, User))
    {
        if (User.UserName == "Admin")
        {
            cout << "You can not Delete Admin user";
        }
        else
        {


            PrintUserCard(User);
            cout << "\n\nAre you sure you want delete this User? y/n ? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                MarkUserForDeleteByUsrName(UserName, vUser);
                SaveUsersDataToFile(UserFileName, vUser);
                //Refresh Clients 
                vUser = LoadUserssDataFromFileU(UserFileName);
                cout << "\n\nClient Deleted Successfully.";
                return true;
            }
        }
    }
    else
    {
        cout << "\nuser with user name  (" << UserName << ") is Not Found!";
        return false;
    }
}
void ShowDeleteClientScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
    {
        ShowAccessDeniedMessage();
        return;
    }
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";
    sClient Client;
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}
void ShowDeleteUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete User  Screen";
    cout << "\n-----------------------------------\n";
    sUser User;
    vector < sUser> vUser = LoadUserssDataFromFileU(UserFileName);
    string Username = ReadUserUserName();
    DeleteUserByUserName(Username, vUser);
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
bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
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
            cout << "\n\nClient update succes Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}
void ShowUpdateClientScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pUpdateClients))
    {
        ShowAccessDeniedMessage();
        return;
    }
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);

}
sUser ChangeUserRecordU(string UserName)
{
    sUser User;
    User.UserName = UserName;
    cout << "\n\nEnter Password? ";
    getline(cin >> ws, User.Password);
    User.Permissions = ReadPermissionsToSet();

    return User;
}
bool UpdateUserByUserName(string UserName, vector<sUser>& vUser)
{
    sUser User;
    char Answer = 'n';
    if (FindUserByUserName(UserName, vUser, User))
    {
        PrintUserCard(User);
        cout << "\n\nAre you sure you want update this User? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sUser& u : vUser)
            {
                if (u.UserName == UserName)
                {
                    u = ChangeUserRecordU(UserName);
                    break;
                }
            }
            SaveUsersDataToFile(UserFileName, vUser);
            cout << "\n\nUser update succes Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nUser with User Name (" << UserName << ") is Not Found!";
        return false;
    }
}
void ShowUpdateUserScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
    {
        ShowAccessDeniedMessage();
        return;
    }
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate User Info Screen";
    cout << "\n-----------------------------------\n";

    vector <sUser> vUser = LoadUserssDataFromFileU(UserFileName);
    string Username = ReadUserUserName();
    UpdateUserByUserName(Username, vUser);

}
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{
    char Answer = 'n';
    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;
                return true;
            }
        }
        return false;
    }
}
void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";
    sClient Client;
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }
    PrintClientCard(Client);
    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;
    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}


void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";
    sClient Client;
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }
    PrintClientCard(Client);
    double Amount = 0;
    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;
    //Validate that the amount does not exceeds the balance
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }     DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}
void PrintClientRecordBalanceLine(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}
void ShowTotalBalances()
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    double TotalBalances = 0;
    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
    {
        for (sClient& Client : vClients)
        {
            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;
            cout << endl;
        }
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;
    }
}
void ShowTotalBalancesScreen()
{
    ShowTotalBalances();
}
enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3, eShowMainMenue = 4 };
int ReadTransactionsMenueOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}
void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    ShowTransactionsMenue();
}

void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
{
    switch (TransactionMenueOption)
    {
    case enTransactionsMenueOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;
    }
    case enTransactionsMenueOptions::eWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactionsMenue();
        break;
    }
    case enTransactionsMenueOptions::eShowTotalBalance:
    {
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenue();
        break;
    }
    case enTransactionsMenueOptions::eShowMainMenue:
    {
        ShowMainMenue();
    }
    }
}
void ShowTransactionsMenue()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pTranactions))
    {
        ShowAccessDeniedMessage();
        return;
    }
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";
    PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}
void GoBackToUserMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowManageUserMenue();
}
enum enUserMenueOptions
{
    eListUser = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eShowMainMenueU = 6
};
int ReadUserMenueOption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

bool CheckAccessPermission(enMainMenuePermissions Permission)
{
    if (CurrentUser.Permissions == enMainMenuePermissions::eAll)
        return true;
    if ((Permission & CurrentUser.Permissions) == Permission)
        return true;
    else
        return false;
}

void PerfromUserMenueOption(enUserMenueOptions enUserMenueOptions)
{
    switch (enUserMenueOptions)
    {
    case enUserMenueOptions::eListUser:
    {
        system("cls");
        PrintAllUsersData();
        GoBackToUserMenue();
        break;
    }
    case enUserMenueOptions::eAddNewUser:
    {
        system("cls");
        AddMoreUser();


        GoBackToUserMenue();
        break;
    }
    case enUserMenueOptions::eDeleteUser:
    {
        system("cls");
        ShowDeleteUserScreen();
        GoBackToUserMenue();
        break;
    }
    case enUserMenueOptions::eUpdateUser:
    {
        system("cls");
        ShowUpdateUserScreen();
        GoBackToUserMenue();
        break;
    }
    case enUserMenueOptions::eFindUser:
    {
        system("cls");
        ShowFindUserScreen();
        GoBackToUserMenue();
        break;
    }
    case enUserMenueOptions::eShowMainMenueU:
    {
        ShowMainMenue();
    }
    }
}
void ShowManageUserMenue()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pManageUsers))
    {
        ShowAccessDeniedMessage();
        return;
    }
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tManage User Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show User List.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User Info.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue.\n";
    cout << "===========================================\n";
    PerfromUserMenueOption((enUserMenueOptions)ReadUserMenueOption());
}
void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}
enum enMainMenueOptions {
    eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6, eManageUser = 7, eLogin = 8
};
short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 8]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}
void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();
}
void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
        system("cls");
        PrintAllClientsData();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eAddNewClient:
        system("cls");
        AddMoreClient();
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
    case enMainMenueOptions::eShowTransactionsMenue:
        system("cls");
        ShowTransactionsMenue();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eManageUser:
        system("cls");
        ShowManageUserMenue();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eLogin:
        system("cls");
        Login();
        break;
    default:
        break;
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
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage user.\n";
    cout << "\t[8] log in.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}
bool LoadUserInfo(string UserName, string password, sUser& User, vector <sUser> vUsers = LoadUserssDataFromFileU(UserFileName))
{
    for (sUser& u : vUsers)
    {
        if (u.UserName == UserName)
        {
            if (u.Password == password)
            {
                User = u;
                return true;
            }
        }
    }
    return false;
}
bool  LoadUserInfo2(string Username, string Password)
{
    if (LoadUserInfo(Username, Password, CurrentUser))
        return true;
    else
        return false;
}
void Login()
{
    bool LoginFaild = false;
    string Username, Password;
    do
    {
        system("cls");
        cout << "\n---------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n---------------------------------\n";
        if (LoginFaild)
        {
            cout << "Invlaid Username/Password!\n";
        }
        cout << "Enter Username? ";
        cin >> Username;
        cout << "Enter Password? ";
        cin >> Password;
        LoginFaild = !LoadUserInfo2(Username, Password);

    } while (LoginFaild);
    ShowMainMenue();

}
int main()
{
    Login();
    system("pause>0");
    return 0;
}
