#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include<ctime>
#include"Header.h"
using namespace std;

int main()
{
    const char* RED_TEXT = "\033[31m";
    const char* GREEN_TEXT = "\033[32m";
    const char* YELLOW_TEXT = "\033[33m";
    const char* BLUE_TEXT = "\033[34m";
    const char* MAGENTA_TEXT = "\033[35m";
    const char* CYAN_TEXT = "\033[36m";
    const char* RESET_TEXT = "\033[0m";
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set the text color to blue
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    const char* red = "\033[31m";
    cout <<BLUE_TEXT << "         _____   ______   ____   ____    ____   ______   ______  |   /\n";
    cout << "\033[43m|       |      | |      |       |    | |      | |      | |  / \n";
    cout << "\033[43m|       |      | |      |       |    | |      | |      | | /  \n";
    cout << "\033[43m|_____  |______| |      |____   |____| |      | |      | |/   \n";
    cout << "\033[43m|       |      | |      |       |    | |      | |      | |\\  \n";
    cout << "\033[43m|       |      | |      |       |    | |      | |      | | \\ \n";
    cout << "\033[43m|       |      | |____  |____   |____| |______| |______| |  \\ \n";
    cout << RESET_TEXT;

    const int MAX_USER = 10;
    cout << GREEN_TEXT;
    User users[MAX_USER];
    int numUsers;
    cout << "Enter the number of users to register: ";
    cin >> numUsers;
    cout << RESET_TEXT;
    for (int i = 0; i < numUsers; ++i)
    {

        string newUserID, newName, newEmail, newPassword, newBirthdate;
        cout << YELLOW_TEXT;
        cout << "Enter userID for User " << i + 1 << ": ";
        cin >> newUserID;
        cout << "Enter name for User " << i + 1 << ": ";
        cin.ignore();
        getline(cin, newName);
        cout << "Enter email for User " << i + 1 << ": ";
        cin >> newEmail;
        cout << "Enter password for User " << i + 1 << ": ";
        cin >> newPassword;
        cout << "Enter birthdate for User " << i + 1 << " (YYYY-MM-DD): ";
        cin >> newBirthdate;
        cout << RESET_TEXT;
        users[i] = User();
        users[i].setUserID(newUserID);
        users[i].setName(newName);
        users[i].setEmail(newEmail);
        users[i].setPassword(newPassword);
        users[i].setBirthdate(newBirthdate);
        users[i].registerUser();
    }

    bool exit = false;
    while (!exit)
    {
        int choice;
        cout << GREEN_TEXT;
        string newUserID, email, password;
        string coverPhoto;
        string profilePic;
        string response;
        string profilePicPath;
        string coverPhotoPath;
        string postContent;
        string postUser;
        Search searchObj;
        cout << "\nMenu:\n";
        cout << "1.\033[44m Authenticate User\n";
        cout << "2. \033[44m Update Profile Picture and Cover Photo\n";
        cout << "3. \033[44m Send and Respond to Friend Requests\n";
        cout << "4. \033[44m crete post\n";
        cout << "5. \033[44m like post\n";
        cout << "6. \033[44m comment post\n";
        cout << "7. \033[44m chat with your friend\n:";
        cout << "8. \033[44m create group\n";
        cout << "9. \033[44m create page\n";
        cout << "10.\033[44m search Your friends\n";
        cout << "11.\033[44m exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << RESET_TEXT;
        switch (choice)
        {
        case 1:
        {
            cout << BLUE_TEXT;
            // Display list of users for selection
            cout << "Available users for authentication:\n";
            for (int i = 0; i < numUsers; ++i)
            {
                cout << i << ". " << users[i].getName() << " (" << users[i].getEmail() << ")\n";
            }

            int selectedUserIndex;
            cout << "Enter the index of the user you want to authenticate: ";
            cin >> selectedUserIndex;

            if (selectedUserIndex >= 0 && selectedUserIndex < numUsers)
            {
                string password;
                cout << "Enter password for user '" << users[selectedUserIndex].getName() << "': ";
                cin >> password;

                if (User::authenticateUser(users[selectedUserIndex].getEmail(), password))
                {
                    cout << "Authentication successful for user '" << users[selectedUserIndex].getName() << "'!\n";
                }
                else
                {
                    cout << "Authentication failed for user '" << users[selectedUserIndex].getName() << "'!\n";
                }
            }
            else
            {
                cout << "Invalid user index!\n";
            }
            cout << RESET_TEXT;
            break;
        }
        case 2:
        {
            cout << RED_TEXT;
            cout << "Enter user index to update profile: ";
            int userIndex;
            cin >> userIndex;

            if (userIndex < 0 || userIndex >= numUsers)
            {
                cout << "Invalid user index.\n";
                break;
            }

            int photoChoice;
            cout << "Select photo to update:\n";
            cout << "1. Profile Picture\n";
            cout << "2. Cover Photo\n";
            cout << "Enter your choice: ";
            cin >> photoChoice;

            if (photoChoice == 1)
            {
                // cout << "Enter path for the new profile picture: ";
                string newProfilePicPath;

                newProfilePicPath = "C:\\Users\\Dell\\Pictures\\Screenshots\\Screenshot (2).png";

                users[userIndex].setProfilePicture(newProfilePicPath);
                cout << "Profile picture updated for User " << userIndex << endl;
            }
            else if (photoChoice == 2)
            {
                cout << "Enter path for the new cover photo: ";
                string newCoverPhotoPath;
                newCoverPhotoPath = "C:\\Users\\Dell\\Pictures\\Screenshots\\Screenshot (2).png";
                users[userIndex].setCoverPhoto(newCoverPhotoPath);
                cout << "Cover photo updated for User " << userIndex << endl;
            }
            else
            {
                cout << "Invalid choice.\n";
                break;
            }
            users[userIndex].registerUser();
            cout << RESET_TEXT;
            break;
        }
        case 3:
        {
            cout << YELLOW_TEXT;
            cout << "Enter sender's index (0 to " << numUsers - 1 << "): ";
            int senderIndex;
            cin >> senderIndex;

            if (senderIndex < 0 || senderIndex >= numUsers)
            {
                cout << "Invalid sender's index.\n";
                break;
            }

            cout << "Enter receiver's index (0 to " << numUsers - 1 << "): ";
            int receiverIndex;
            cin >> receiverIndex;

            if (receiverIndex < 0 || receiverIndex >= numUsers)
            {
                cout << "Invalid receiver's index.\n";
                break;
            }

            users[senderIndex].sendFriendRequest(users[receiverIndex]);
            cout << "Friend request sent from User " << senderIndex << " to User " << receiverIndex << ".\n";

            cout << "Do you want to respond to the request? (yes/no): ";
            cin >> response;

            if (response == "yes")
            {
                int action;
                cout << "Enter '1' to accept or '2' to decline: ";
                cin >> action;

                if (action == 1)
                {
                    users[receiverIndex].acceptFriendRequest(users[senderIndex].getUserID());
                }
                else if (action == 2)
                {
                    users[receiverIndex].declineFriendRequest(users[senderIndex].getUserID());
                }
                else
                {
                    cout << "Invalid action. No action taken.\n";
                }
            }
            cout << RESET_TEXT;
            break;
        }
        case 4:
        {
            cout << BLUE_TEXT;
            cout << "Enter user index to create post: ";
            int userIndex1;
            cin >> userIndex1;

            if (userIndex1 < 0 || userIndex1 >= numUsers)
            {
                cout << "Invalid user index.\n";
                break;
            }

            cout << "Enter post content: ";
            cin.ignore();
            getline(cin, postContent);

            cout << "Enter post id: ";
            cin >> postUser;

            Post post(postUser, postContent, postUser);
            post.createpost();
            cout << RESET_TEXT;
            break;
        }
        case 5:
        {
            cout << GREEN_TEXT;
            cout << "Enter user index to like post: ";
            int userIndex2;
            cin >> userIndex2;

            if (userIndex2 < 0 || userIndex2 >= numUsers)
            {
                cout << "Invalid user index.\n";
                break;
            }

            cout << "Enter post id: ";
            cin >> postUser;

            if (users[userIndex2].isFriend(postUser))
            {
                Like like(postUser, postUser);
                like.likepost(users[userIndex2]);
            }
            else
            {
                cout << "You can only like posts of your friends." << endl;
            }
            cout << RESET_TEXT;
            break;
        }

        case 6:
        {
            cout << RED_TEXT;
            cout << "Enter user index to comment post: ";
            int userIndex3;
            cin >> userIndex3;

            if (userIndex3 < 0 || userIndex3 >= numUsers)
            {
                cout << "Invalid user index.\n";
                break;
            }

            cout << "Enter post id: ";
            cin >> postUser;

            if (users[userIndex3].isFriend(postUser))
            {
                cout << "Enter comment: ";
                cin.ignore();
                getline(cin, postContent);

                Comment comment(postUser, postUser, postContent);
                comment.commentpost(users[userIndex3]);
            }
            else
            {
                cout << "You can only comment on posts of your friends." << endl;
            }
            cout << RESET_TEXT;
            break;
        }
        case 7:
        {
            cout << CYAN_TEXT;
            cout << "Enter sender's index (0 to " << numUsers - 1 << "): ";
            int senderIndex;
            cin >> senderIndex;

            if (senderIndex < 0 || senderIndex >= numUsers)
            {
                cout << "Invalid sender's index.\n";
                break;
            }

            cout << "Enter receiver's index (0 to " << numUsers - 1 << "): ";
            int receiverIndex;
            cin >> receiverIndex;

            if (receiverIndex < 0 || receiverIndex >= numUsers)
            {
                cout << "Invalid receiver's index.\n";
                break;
            }

            cout << "Enter message: ";
            cin.ignore();
            getline(cin, postContent);

            Message message(users[senderIndex].getUserID(), users[receiverIndex].getUserID());

            message.sendMessage(users[senderIndex]);
            cout << RESET_TEXT;
            break;
        }
        case 8:
        {
            cout << RED_TEXT;
            cout << "Enter user index to create group: ";
            int userIndex4;
            cin >> userIndex4;

            if (userIndex4 < 0 || userIndex4 >= numUsers)
            {
                cout << "Invalid user index.\n";
                break;
            }
            int groupOption;
            cout << "Select an option:\n";
            cout << "1. Create a new group\n";
            cout << "2. Join an existing group\n";
            cout << "Enter your choice: ";
            cin >> groupOption;

            if (groupOption == 1)
            {
                cout << "Enter group name: ";
                cin.ignore();
                getline(cin, postContent);

                cout << "Enter group id: ";
                cin >> postUser;

                groupsandpages group(postUser, postUser, postContent, postContent, postContent, postContent);
                group.creategroup();
            }
            else if (groupOption == 2)
            {
                cout << "Enter group id: ";
                cin >> postUser;

                groupsandpages group(postUser, postUser, postContent, postContent, postContent, postContent);
                group.existinggroup();
            }
            else
            {
                cout << "Invalid choice.\n";
            }
            cout << RESET_TEXT;
            break;
        }
        case 9:
        {
            cout << YELLOW_TEXT;
            cout << "Enter user index to create page: ";
            int userIndex5;
            cin >> userIndex5;

            if (userIndex5 < 0 || userIndex5 >= numUsers)
            {
                cout << "Invalid user index.\n";
                break;
            }

            cout << "Enter page name: ";
            cin.ignore();
            getline(cin, postContent);

            cout << "Enter page id: ";
            cin >> postUser;

            groupsandpages page(postUser, postUser, postContent, postContent, postContent, postContent);
            page.createpage();
            cout << RESET_TEXT;
            break;
        }
        case 10:
        {
            cout << GREEN_TEXT;
            cout << "Enter user's index to search his common friends: ";
            int userIndex6;
            cin >> userIndex6;

            cout << "Enter user's index to check whether he is common friend of " << userIndex6 << " or not : ";
            int userIndex7;
            cin >> userIndex7;
            if (userIndex6 < 0 || userIndex6 >= numUsers || userIndex7 < 0 || userIndex7 >= numUsers)
            {
                cout << "Invalid user index.\n";
            }
            searchObj.searchUsersWithCommonFriends(users[userIndex6], users[userIndex7]);
            cout << RESET_TEXT;
            break;
        }
        case 12:
        {
            cout << "Invalid choice! Please select a valid option.\n";
            exit = true;
            break;
        }
        }
    }
    return 0;
}