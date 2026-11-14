#include<iostream>
#include<iomanip>
#include<cctype>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

const string FileName = "Bank2_Clients_Info.txt";
const string UsersFile = "Bank2_Users_Info.txt";

struct sClient
{
    string AccountNumber;
    string PINCode;
    string Name;
    string Phone;
    double AccountBalance;
};


struct sUser
{
    string UserName;
    string Password;
    short Permissions;
};

bool CheckAdmin(sUser admin);
vector <sUser> LoadUsersDataFromFile(string UsersFile);
void ShowClientsList_1();
void AddNewClient_2();
void DeleteClient_3();
void UpdateClientInfo_4();
void FindClient_5();
void BANK();
void Deposit_1();
void Withdraw_2();
void ShowBalancesList_3();
void TransactionsMenue();

sClient ReadNewClient(string AccountNumber);
string ConvertRecordToLine(sClient Client, string separator = "#//#");
sClient ConvertClientLineToRecord(string Line, string separator = "#//#");

string ReadString(string message);
void PrintRecord(sClient Record);
vector <sClient> LoadClientsDataFromFile(string FileName);
bool If_Found(vector <sClient>& vRecord, string AccountNumber, short& index);
void PrintInFile_WithoutIndex(vector <sClient>& vRecord, short index);
void ReadUpdatedInfo(vector <sClient>& vRecord, short index);
void PrintMainMenue();
void PrintTransactionsMenue();
void PrintClientRecord(sClient& Client);
void PrintClientBalance(sClient& Client);
void PrintAllClientsData(vector <sClient>& vClients);
void PrintAllBalances(vector <sClient>& vClients);
void PrintDeposit();
void PrintWithdraw();
int ReadPositiveNumber(string message);
bool AskIfSure(string message);

sClient ReadNewClient(string AccountNumber)
{
    sClient Client;

    cout << "Please Enter Client data :\n\n";

    Client.AccountNumber = AccountNumber;

    cout << "Enter PIN code : ";
    getline(cin >> ws, Client.PINCode);

    cout << "Enter name : ";
    getline(cin, Client.Name);

    cout << "Enter phone : ";
    getline(cin, Client.Phone);

    cout << "Enter account balance : ";
    cin >> Client.AccountBalance;

    return Client;
}

short AskAboutUserPermission(sUser User)
{
    short Permission = 0;
    if (AskIfSure("Do you want to give this user full access? (y/n)? "))
        return -1;

    if (AskIfSure("Do you want to give this user access to show Client list? (y/n)? "))
        Permission = Permission | 1;

    if (AskIfSure("Do you want to give this user access to add new Clients? (y/n)? "))
        Permission = Permission | 2;

    if (AskIfSure("Do you want to give this user access to delete Clients? (y/n)? "))
        Permission = Permission | 4;

    if (AskIfSure("Do you want to give this user access to update Clients info? (y/n)? "))
        Permission = Permission | 8;

    if (AskIfSure("Do you want to give this user access to find Clients? (y/n)? "))
        Permission = Permission | 16;

    if (AskIfSure("Do you want to give this user access to for transactions? (y/n)? "))
        Permission = Permission | 32;

    if (AskIfSure("Do you want to give this user access to manage users? (y/n)? "))
        Permission = Permission | 64;

    return Permission;
}

sUser ReadNewUser(string Username)
{
    sUser User;

    cout << "Please Enter User data :\n\n";

    User.UserName = Username;

    cout << "Enter Passowrd : ";
    getline(cin >> ws, User.Password);

    User.Permissions = AskAboutUserPermission(User);


    return User;
}

string ConvertRecordToLine(sClient Client, string separator)
{
    string str = "";
    str += Client.AccountNumber + separator;
    str += Client.PINCode + separator;
    str += Client.Name + separator;
    str += Client.Phone + separator;
    str += to_string(Client.AccountBalance);
    return str;
}

string ConvertRecordToLine(sUser User, string separator = "#//#")
{
    string str = "";
    str += User.UserName + separator;
    str += User.Password + separator;
    str += to_string(User.Permissions);
    return str;
}

sClient ConvertClientLineToRecord(string Line, string separator)
{
    sClient Record;

    int pos = Line.find(separator);
    Record.AccountNumber = Line.substr(0, pos);
    Line.erase(0, pos);
    Line.erase(0, separator.length());

    pos = Line.find(separator);
    Record.PINCode = Line.substr(0, pos);
    Line.erase(0, pos);
    Line.erase(0, separator.length());

    pos = Line.find(separator);
    Record.Name = Line.substr(0, pos);
    Line.erase(0, pos);
    Line.erase(0, separator.length());

    pos = Line.find(separator);
    Record.Phone = Line.substr(0, pos);
    Line.erase(0, pos);
    Line.erase(0, separator.length());

    Record.AccountBalance = stod(Line);


    return Record;

}

sUser ConvertUserLineToRecord(string Line, string separator = "#//#")
{
    sUser Record;

    int pos = Line.find(separator);
    Record.UserName = Line.substr(0, pos);
    Line.erase(0, pos);
    Line.erase(0, separator.length());

    pos = Line.find(separator);
    Record.Password = Line.substr(0, pos);
    Line.erase(0, pos);
    Line.erase(0, separator.length());

    pos = Line.find(separator);
    Record.Permissions = (short)stoi(Line);

    return Record;

}

void AddNewClient_2()
{
    system("cls");
    sClient TempRecord;
    string TempLine;
    fstream File;
    vector <sClient> vRecord = LoadClientsDataFromFile(FileName);
    short index = 0;
    File.open(FileName, ios::out | ios::app);
    if (File.is_open())
    {
        do
        {
            system("cls");
            string AccountNumber = ReadString("Please enter new account number : ");

            if (!If_Found(vRecord, AccountNumber, index))
            {
                TempRecord = ReadNewClient(AccountNumber);
                TempLine = ConvertRecordToLine(TempRecord);
                File << TempLine << endl;
            }
            else
            {
                cout << "This account number already exist !";
            }


        } while (AskIfSure("Do you want to add a new client ? (yes-> y /no-> n )"));

    }
    File.close();
    cout << "\nPress any key to go back to main menue... ";
    system("pause>0");
}

string ReadString(string message)
{
    string AccountNumber;

    cout << message;
    cin >> AccountNumber;

    return AccountNumber;
}

void PrintRecord(sClient Record)
{
    cout << "\nThe following is the extracted client record \n\n";
    cout << "Account Number  : " << Record.AccountNumber << endl;
    cout << "Phone           : " << Record.Phone << endl;
    cout << "PIN Code        : " << Record.PINCode << endl;
    cout << "Name            : " << Record.Name << endl;
    cout << "Account Balance : " << Record.AccountBalance << endl;
}

void PrintRecord(sUser Record)
{
    cout << "\nThe following is the extracted client record \n\n";
    cout << "Username    : " << Record.UserName << endl;
    cout << "Password    : " << Record.Password << endl;
    cout << "Permission  : " << Record.Permissions << endl;
}

vector <sClient> LoadClientsDataFromFile(string FileName)
{
    vector < sClient> vClient;
    string tempLine = "";
    fstream ClientsFile;
    ClientsFile.open(FileName, ios::in);
    if (ClientsFile.is_open())
    {
        while (getline(ClientsFile, tempLine))
        {
            vClient.push_back(ConvertClientLineToRecord(tempLine));
        }
        ClientsFile.close();
        return vClient;
    }
    else
    {
        cout << "ERROR with openinig file <<>><<>>";
        return vClient;
    }



}

bool If_Found(vector <sClient>& vRecord, string AccountNumber, short& index)
{
    index = 0;
    for (sClient& n : vRecord)
    {

        if (n.AccountNumber == AccountNumber)
            return true;
        index++;

    }
    return false;
}

bool If_Found(vector <sUser>& vRecord, string Username, short& index)
{
    index = 0;
    for (sUser& n : vRecord)
    {

        if (n.UserName == Username)
            return true;
        index++;

    }
    return false;
}

void PrintInFile_WithoutIndex(vector <sClient>& vRecord, short index)
{
    fstream File;
    File.open(FileName, ios::out);
    if (File.is_open())
    {
        for (sClient& n : vRecord)
        {
            if (n.AccountNumber == vRecord.at(index).AccountNumber)
                continue;
            else
            {
                File << ConvertRecordToLine(n) << endl;
            }
        }
        File.close();
    }

}

void PrintInFile_WithoutIndex(vector <sUser>& vRecord, short index)
{
    fstream File;
    File.open(UsersFile, ios::out);
    if (File.is_open())
    {
        for (sUser& n : vRecord)
        {
            if (n.UserName == vRecord.at(index).UserName)
                continue;
            else
            {
                File << ConvertRecordToLine(n) << endl;
            }
        }
        File.close();
    }

}

void ReadUpdatedInfo(vector <sClient>& vRecord, short index)
{

    cout << "Enter PIN code : ";
    getline(cin >> ws, vRecord.at(index).PINCode);

    cout << "Enter name : ";
    getline(cin, vRecord.at(index).Name);

    cout << "Enter phone : ";
    getline(cin, vRecord.at(index).Phone);

    cout << "Enter account palance : ";
    cin >> vRecord.at(index).AccountBalance;
}

void ReadUpdatedInfo(vector <sUser>& vRecord, short index, sUser user)
{

    cout << "Enter a new password for this user : ";
    getline(cin >> ws, vRecord.at(index).Password);

    if (user.Permissions == -1)
        vRecord.at(index).Permissions = AskAboutUserPermission(vRecord.at(index));

}

void DeleteClient_3()
{
    system("cls");
    short index;
    vector <sClient> vRecord = LoadClientsDataFromFile(FileName);
    string AccountNumber = ReadString("Enter the account number that you want to delete : ");
    if (If_Found(vRecord, AccountNumber, index))
    {
        PrintRecord(vRecord.at(index));
        if (AskIfSure("Do you want to delete this client ?(Yes -> y / No -> n) : "))
        {
            PrintInFile_WithoutIndex(vRecord, index);
            cout << endl << "This account has been deleted" << endl;
        }
    }
    else
    {
        cout << "\nthis account number not found !";
    }

    cout << "\nPress any key to go back to main menue... ";

}

void DeleteUser_23(sUser user)
{
    system("cls");
    short index;
    vector <sUser> vRecord = LoadUsersDataFromFile(UsersFile);
    string username = ReadString("Enter the username that you want to delete : ");

    if (If_Found(vRecord, username, index))
    {
        if (user.UserName == vRecord.at(index).UserName)
        {

            system("cls");
            system("color 4F");
            cout << "!!!!!!!!!!!!!\nDo you want to delete youself ??\nyou cant (>.<)";
        }
        else
        {


            if (!CheckAdmin(user) && CheckAdmin(vRecord.at(index)))
            {
                system("cls");
                system("color 4F");
                cout << "WTF!\nDo you want to delete Admin ??\nGo away -.-";
            }
            else
            {
                PrintRecord(vRecord.at(index));
                if (AskIfSure("Do you want to delete this User  ?(Yes -> y / No -> n) : "))
                {
                    PrintInFile_WithoutIndex(vRecord, index);
                    cout << endl << "This user has been deleted" << endl;
                }
            }
        }
    }
    else
    {
        cout << "\nthis username not found !";
    }

    cout << "\nPress any key to go back to main menue... ";
    system("pause>0");
    system("color 07");
}

void UpdateClientInfo_4()
{
    system("cls");
    short index;
    vector <sClient> vRecord = LoadClientsDataFromFile(FileName);
    string AccountNumber = ReadString("Enter the account number that you want to update : ");
    if (If_Found(vRecord, AccountNumber, index))
    {
        system("cls");
        PrintRecord(vRecord.at(index));
        if (AskIfSure("Do you want to Update the data for this client ?(Yes -> y / No -> n) : "))
        {
            ReadUpdatedInfo(vRecord, index);

            fstream File;
            File.open(FileName, ios::out);
            if (File.is_open())
            {
                for (sClient& n : vRecord)
                {
                    File << ConvertRecordToLine(n) << endl;
                }
                cout << "\n\nClient updated successfully\n";
            }

        }


    }
    else
    {
        cout << "\nthis account number not found !";
    }

    cout << "\nPress any key to go back to main menue... ";
    system("pause>0");

}

void UpdateUserInfo_24(sUser user)
{
    system("cls");
    short index;
    vector <sUser> vRecord = LoadUsersDataFromFile(UsersFile);
    string username = ReadString("Enter the username that you want to update : ");

    if (If_Found(vRecord, username, index))
    {



        if (!CheckAdmin(user) && CheckAdmin(vRecord.at(index)))
        {
            system("cls");
            system("color 4F");
            cout << "You cant update Admin info :-( ";
        }
        else
        {


            system("cls");
            PrintRecord(vRecord.at(index));
            if (AskIfSure("Do you want to Update the data for this user ?(Yes -> y / No -> n) : "))
            {
                ReadUpdatedInfo(vRecord, index, user);

                fstream File;
                File.open(UsersFile, ios::out);
                if (File.is_open())
                {
                    for (sUser& n : vRecord)
                    {
                        File << ConvertRecordToLine(n) << endl;
                    }
                    cout << "\n\nClient updated successfully\n";
                }

            }
        }

    }
    else
    {
        cout << "\nthis username not found !";
    }

    cout << "\nPress any key to go back to main menue... ";
    system("pause>0");
    system("color 07");
}

void PrintMainMenue()
{
    cout << "==============================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "==============================================\n";
    cout << "\t[1] Show clients list. \n";
    cout << "\t[2] Add new client. \n";
    cout << "\t[3] Delete clients. \n";
    cout << "\t[4] Update client info. \n";
    cout << "\t[5] Find client. \n";
    cout << "\t[6] Transactions. \n";
    cout << "\t[7] Manage Users. \n";
    cout << "\t[8] Log out. \n";
    cout << "==============================================\n";
}

void PrintManageUsersMenue()
{
    cout << "==============================================\n";
    cout << "\t\tManage Users Menue Screen\n";
    cout << "==============================================\n";
    cout << "\t[1] list users. \n";
    cout << "\t[2] Add new user. \n";
    cout << "\t[3] Delete user. \n";
    cout << "\t[4] Update user info. \n";
    cout << "\t[5] Find user. \n";
    cout << "\t[6] Main menu. \n";
    cout << "==============================================\n";
}

void PrintTransactionsMenue()
{
    cout << "==============================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "==============================================\n";
    cout << "\t[1] Deposit. \n";
    cout << "\t[2] Withdraw. \n";
    cout << "\t[3] Tatal balance. \n";
    cout << "\t[4] Main menue. \n";
    cout << "==============================================\n";
}

void PrintClientRecord(sClient& Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PINCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintUserRecord(sUser& User)
{
    cout << "| " << setw(15) << left << User.UserName;
    cout << "| " << setw(10) << left << User.Password;
    cout << "| " << setw(40) << left << User.Permissions;
}

void PrintClientBalance(sClient& Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientsData(vector <sClient>& vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sClient Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

void PrintAllUsersData(vector <sUser>& vUsers)
{
    cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ")User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Username";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "Permission";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sUser user : vUsers)
    {
        PrintUserRecord(user);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

void PrintAllBalances(vector <sClient>& vClients)
{
    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ")Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sClient Client : vClients)
    {
        PrintClientBalance(Client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

void ShowClientsList_1()
{
    system("cls");
    vector <sClient> vClients = LoadClientsDataFromFile(FileName);
    PrintAllClientsData(vClients);
    cout << "\nPress any key to go back to main menue... ";
    system("pause>0");
}

void ShowUsersList_21()
{
    system("cls");
    vector <sUser> vUser = LoadUsersDataFromFile(UsersFile);

    PrintAllUsersData(vUser);

    cout << "\nPress any key to go back to main menue... ";
    system("pause>0");
}

void ShowBalancesList_3()
{
    system("cls");
    vector <sClient> vClients = LoadClientsDataFromFile(FileName);
    PrintAllBalances(vClients);
    cout << "\nPress any key to go back to transactions menue... ";
    system("pause>0");
}

void FindClient_5()
{
    system("cls");
    short index;
    vector <sClient> vRecord = LoadClientsDataFromFile(FileName);
    string AccountNumber = ReadString("Enter the account number that you want to finde : ");
    if (If_Found(vRecord, AccountNumber, index))
    {
        system("cls");
        PrintRecord(vRecord.at(index));
    }
    else
    {
        cout << "\nthis account number not found !";
    }

    cout << "\nPress any key to go back to main menue... ";
    system("pause>0");
}

void FindUser_25()
{
    system("cls");
    short index;
    vector <sUser> vRecord = LoadUsersDataFromFile(UsersFile);
    string UserName = ReadString("Enter the Username that you want to finde : ");
    if (If_Found(vRecord, UserName, index))
    {
        system("cls");
        PrintRecord(vRecord.at(index));
    }
    else
    {
        cout << "\nthis username not found !";
    }

    cout << "\nPress any key to go back to main menue... ";
    system("pause>0");
}

void PrintDeposit()
{
    cout << "\n-----------------------------------------------------\n";
    cout << "\tDeposit screen";
    cout << "\n-----------------------------------------------------\n";
}

void PrintWithdraw()
{
    cout << "\n-----------------------------------------------------\n";
    cout << "\tWithdraw screen";
    cout << "\n-----------------------------------------------------\n";
}

int ReadPositiveNumber(string message)
{
    int num;
    do
    {
        cout << endl << message;
        cin >> num;
    } while (num < 0);
    return num;
}

bool AskIfSure(string message)
{
    char answer;
    cout << endl << message;
    cin >> answer;
    if (toupper(answer) == 'Y')
        return true;
    else
        return false;
}

void Deposit_1()
{
    system("cls");
    PrintDeposit();
    string AccountNumber = ReadString("Please enter account number : ");
    vector <sClient> vRecord = LoadClientsDataFromFile(FileName);
    short index = 0;
    if (If_Found(vRecord, AccountNumber, index))
    {
        PrintRecord(vRecord.at(index));
        int DepositAmount = ReadPositiveNumber("Please enter deposit amount : ");
        if (AskIfSure("Are you sure you want to perform this transaction? y/n :"))
        {

            vRecord.at(index).AccountBalance += DepositAmount;
            fstream File;
            File.open(FileName, ios::out);
            if (File.is_open())
            {
                for (sClient& n : vRecord)
                {
                    File << ConvertRecordToLine(n) << endl;
                }
                cout << "\n\nDeposit amount added successfully\n";
            }
        }
        cout << "\nPress any key to go back to main menue... ";
        system("pause>0");

    }
    else
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.";
        cout << "\nPress any key to go back to transactions menue... ";
        system("pause>0");
    }

}

void Withdraw_2()
{

    system("cls");
    PrintWithdraw();
    string AccountNumber = ReadString("Please enter account number : ");
    vector <sClient> vRecord = LoadClientsDataFromFile(FileName);
    short index = 0;
    if (If_Found(vRecord, AccountNumber, index))
    {
        PrintRecord(vRecord.at(index));
        int WithdrawAmount;
        do
        {
            WithdrawAmount = ReadPositiveNumber("Please enter withdraw amount : ");
        } while (WithdrawAmount > vRecord.at(index).AccountBalance);

        if (AskIfSure("Are you sure you want to perform this transaction? y/n :"))
        {

            vRecord.at(index).AccountBalance -= WithdrawAmount;
            fstream File;
            File.open(FileName, ios::out);
            if (File.is_open())
            {
                for (sClient& n : vRecord)
                {
                    File << ConvertRecordToLine(n) << endl;
                }
                cout << "\n\nWithdrawl completed successfully\n";
            }
        }
        cout << "\nPress any key to go back to main menue... ";
        system("pause>0");

    }
    else
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.";
        cout << "\nPress any key to go back to transactions menue... ";
        system("pause>0");
    }
}

void TransactionsMenue()
{
    int choice;
    do
    {
        system("cls");
        PrintTransactionsMenue();
        cout << "Choose what do you want to do? [1 to 4]? ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            Deposit_1();
            break;
        case 2:
            Withdraw_2();
            break;
        case 3:
            ShowBalancesList_3();
            break;
        case 4:
            break;
        }
    } while (choice != 4);
}

bool CheckAdmin(sUser admin)
{
    return (admin.Permissions == -1) ? true : false;
}

vector <sUser> LoadUsersDataFromFile(string UsersFile)
{
    vector < sUser> vUser;
    string tempLine = "";
    fstream File;
    File.open(UsersFile, ios::in);
    if (File.is_open())
    {
        while (getline(File, tempLine))
        {
            vUser.push_back(ConvertUserLineToRecord(tempLine));
        }
        File.close();
        return vUser;
    }
    else
    {
        cout << "ERROR with openinig file <<>><<>>";
        return vUser;
    }



}

void AddNewUser_22()
{
    system("cls");
    sUser TempRecord;
    string TempLine;
    fstream File;
    vector <sUser> vRecord = LoadUsersDataFromFile(UsersFile);
    short index = 0;
    File.open(UsersFile, ios::out | ios::app);
    if (File.is_open())
    {
        do
        {
            system("cls");
            string UserName = ReadString("Please enter a Username : ");

            if (!If_Found(vRecord, UserName, index))
            {
                TempRecord = ReadNewUser(UserName);
                TempLine = ConvertRecordToLine(TempRecord);
                File << TempLine << endl;
            }
            else
            {
                cout << "This username is already exist !";
            }


        } while (AskIfSure("Do you want to add a new client ? (yes-> y /no-> n )"));

    }
    File.close();
    cout << "\nPress any key to go back to main menue... ";
    system("pause>0");
}

void ManageUsers_7(sUser user)
{

    short choice;
    do
    {
        system("cls");
        PrintManageUsersMenue();
        cout << "Choose what do you want to do? [1 to 6]? ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            ShowUsersList_21();
            break;
        case 2:
            AddNewUser_22();
            break;
        case 3:
            DeleteUser_23(user);//
            break;
        case 4:
            UpdateUserInfo_24(user);//
            break;
        case 5:
            FindUser_25();
            break;
        case 6: //exit -> main menu
            break;
        }
    } while (choice != 6);
}

bool CheckIfHavePermission(sUser user, short choice)
{

    if (user.Permissions == -1 || choice == 8)
        return true;


    switch (choice)
    {
    case 1:
        choice = 1;
        break;
    case 2:
        choice = 2;
        break;
    case 3:
        choice = 4;
        break;
    case 4:
        choice = 8;
        break;
    case 5:
        choice = 16;
        break;
    case 6:
        choice = 32;
        break;
    case 7:
        choice = 64;
        break;
    }



    if (user.Permissions == -1)
        return true;
    return user.Permissions & choice;
}

void BANK(sUser user)
{


    short choice = 1;
    do
    {



        system("cls");
        PrintMainMenue();


        cout << "Choose what do you want to do? [1 to 8]? ";
        cin >> choice;



        if (CheckIfHavePermission(user, choice))
        {


            switch (choice)
            {
            case 1:
                ShowClientsList_1();
                break;
            case 2:
                AddNewClient_2();
                break;
            case 3:
                DeleteClient_3();
                break;
            case 4:
                UpdateClientInfo_4();
                break;
            case 5:
                FindClient_5();
                break;
            case 6:
                TransactionsMenue();
                break;
            case 7:
                ManageUsers_7(user);
                break;
            }

        }
        else
        {
            system("cls");
            cout << "\n------------------------------------";
            cout << "\nAccess Denied,";
            cout << "\nYou dont have permission to do this,";
            cout << "\nPlease contact your admin.";
            cout << "\n------------------------------------";
            cout << "\n\n\nPress any key to go back to main menue... ";
            system("pause>0");
            system("cls");
        }


    } while (choice != 8);
    system("cls");

}

void Login()
{
    short NumberOfAttempts = 5;
    string username;
    string password;
    cout << "==============================================\n";
    cout << "\t\tLogin Screen\n";
    cout << "==============================================\n";
    do
    {

        cout << "please enter the username : ";
        cin >> username;

        cout << "please enter the password : ";
        cin >> password;

        short index = 0;
        vector <sUser> vUsers = LoadUsersDataFromFile(UsersFile);


        if (If_Found(vUsers, username, index))
        {



            if (vUsers.at(index).Password == password)
            {

                BANK(vUsers.at(index));
                cout << "==============================================\n";
                cout << "\t\tLogin Screen\n";
                cout << "==============================================\n";
                NumberOfAttempts = 5;

            }
            else
            {

                system("cls");
                cout << "==============================================\n";
                cout << "\t\tLogin Screen\n";
                cout << "==============================================\n";
                cout << "\nInvalid Username or Password!\n";
                NumberOfAttempts--;

            }
        }
        else
        {
            system("cls");
            cout << "==============================================\n";
            cout << "\t\tLogin Screen\n";
            cout << "==============================================\n";
            cout << "\nthis username was not found!\n";
            NumberOfAttempts--;
        }

    } while (NumberOfAttempts > 0);
    system("cls");
    system("color 4F");
    while (true)
        cout << "BOLCK \a";

}

int main()
{



    Login();


    return 0;
}