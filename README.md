# MyBankProject
this is my first repo


when you log in first 


user name is : Admin



password  is :  12345






then Show All user and update or delete or what do you want and log in with  the user you want









enum enMainMenuePermissions { eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64 };





if user has Permissions=1  that means he can only show all cliens




if user has Permissions=5  that means he can only show all cliens and DeleteClient





if user has Permissions=-1  that means he can do every thing he want







hints :

1: you can not add 2 user have the same User name 



2: you can not delete user Admin


3:  in user you can update password and Permissions only   not user name



4:  you can not add 2 client  have the same Account Number


5: in client you can update every thing except Account Number


































This is a well-written C++ program for managing client data. Here's a breakdown of the code and its functionalities:

Data Structures:

sClient: Struct to store client information (account number, pin code, name, phone, account balance).
sUser: Struct to store user information (username, password, permissions).
vector<sClient>: Vector to store a collection of client records.
vector<sUser>: Vector to store a collection of user records.
File Operations:

LoadCleintsDataFromFile: Reads client data from a file (ClientsFileName) and populates a vector of sClient structs.
LoadUserssDataFromFileU: Reads user data from a file (UserFileName) and populates a vector of sUser structs.
AddDataLineToFile: Appends a new line of data (formatted as a client or user record) to a specified file.
SaveCleintsDataToFile: Saves the updated client data (after deletion) back to the file.
SaveUsersDataToFile: Saves the updated user data (after deletion) back to the file.
User Management:

Login: (Not implemented in the provided code) Likely prompts the user for credentials and validates them against stored user data.
enMainMenuePermissions: Enum to define various permission levels for user access control.
CheckAccessPermission: Checks if the current user has the required permission to perform an action.
ShowAccessDeniedMessage: Displays a message when a user attempts to perform an action without sufficient permissions.
AddNewUser: Guides the user to create a new user account with a username, password, and permission level.
Client Management:

PrintAllClientsData: Displays a list of all clients with their account details.
ClientExistsByAccountNumber: Checks if a client exists based on their account number.
ReadNewClient: Prompts the user to enter new client information and creates an sClient object.
AddNewClient: Adds a new client record to the data file.
AddMoreClient: Provides a menu to repeatedly add new clients.
FindClientByAccountNumber: Searches for a client based on their account number and displays their details.
ShowFindClientScreen: Provides a menu to search for a client.
DeleteClientByAccountNumber: Prompts for confirmation before deleting a client record based on account number.
ShowDeleteClientScreen: Provides a menu to delete a client.
UpdateClientByAccountNumber: Prompts for confirmation and allows editing a client's information.
ShowUpdateClientScreen: Provides a menu to update client information.
DepositBalanceToClientByAccountNumber (Not fully implemented): Prompts for confirmation before potentially adding funds to a client's account balance.
Helper Functions:

SplitString: Splits a string into a vector of substrings based on a delimiter.
ConvertLinetoRecord: Converts a line of text data from a file into an sClient struct.
ConvertRecordToLine: Converts an sClient struct into a line of text data suitable for storing in a file.
ConvertLinetoRecordU: Converts a line of text data from a file into an sUser struct.
ConvertRecordToLineU: Converts an sUser struct into a line of text data suitable for storing in a file.
PrintClientRecord: Formats and displays the details of a single client.
PrintUserRecord: Formats and displays the details of a single user.
ReadClientAccountNumber: Prompts the user to enter a client's account number.
ReadUserUserName: Prompts the user to enter a user's username.
MarkClientForDeleteByAccountNumber: Marks a client record for deletion by setting a flag in the sClient object.
MarkUserForDeleteByUsrName: Marks a user record for deletion by setting a flag in the sUser object.
Overall, this code provides a solid foundation for a client management system with functionalities for adding, deleting, updating, searching, and displaying client data. It also implements basic user management with login and permission checks.       https://github.com/AbdalrahmanEmad158/MyBankProject
