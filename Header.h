#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

class User
{
private:
    static const int MAX_USERS = 10;
    string friendIDs[MAX_USERS];
    string userID;
    string name;
    string email;
    string password;
    string birthdate;
    string profilePicture;
    string coverPhoto;
    int friendCount = 0;
    int pendingRequestCount = 0;
    string pendingRequests[MAX_USERS];

public:
    string friends[MAX_USERS];
    User()
    {
        userID = "";
        name = "";
        email = "";
        password = "";
        birthdate = "";
        profilePicture = "";
        coverPhoto = "";
    }
    User(const string& newUserID, const string& newName, const string& newEmail, const string& newPassword, const string& newBirthdate)
        : userID(newUserID), name(newName), email(newEmail), password(newPassword), birthdate(newBirthdate) {}

    void setUserID(const string& newUserID)
    {
        userID = newUserID;
    }

    int getfriend()
    {
        return friendCount;
    }

    string getUserID() const
    {
        return userID;
    }

    void setName(const string& newName)
    {
        name = newName;
    }

    string getName() const
    {
        return name;
    }

    void setEmail(const string& newEmail)
    {
        email = newEmail;
    }

    string getEmail() const
    {
        return email;
    }

    void setPassword(const string& newPassword)
    {
        password = newPassword;
    }

    string getPassword() const
    {
        return password;
    }

    void setBirthdate(const string& newBirthdate)
    {
        birthdate = newBirthdate;
    }

    string getBirthdate() const
    {
        return birthdate;
    }

    bool isFriend(const string& friendID) const
    {
        for (int i = 0; i < friendCount; ++i)
        {
            if (friends[i] == friendID)
            {
                return true;
            }
        }
        return false;
    }
    virtual void registerUser()
    {
        ofstream outFile("user_data.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << userID << "," << name << "#" << email << ":" << password << "!" << birthdate << "," << profilePicture << "," << coverPhoto << "\n";
            cout << "User registered successfully!" << endl;
            outFile.close();
        }
        else
        {
            cout << "Error: Unable to open file for registration." << endl;
        }
    }

    static bool authenticateUser(const string& email, const string& password)
    {
        ifstream inFile("user_data.txt");
        if (inFile.is_open())
        {
            string line;
            while (getline(inFile, line))
            {
                string user_email, user_password;
                bool recording_email = false, recording_password = false;
                for (int i = 0; i < line.length(); i++)
                {
                    char c = line[i];
                    if (c == '#')
                    {
                        recording_email = true;
                        continue;
                    }
                    if (c == ':')
                    {
                        recording_email = false;
                        recording_password = true;
                        continue;
                    }
                    if (c == '!')
                    {
                        recording_password = false;
                        break;
                    }
                    if (recording_email)
                    {
                        user_email += c;
                    }
                    if (recording_password)
                    {
                        user_password += c;
                    }
                }
                if (user_email == email && user_password == password)
                {
                    cout << "User authenticated successfully!" << endl;
                    inFile.close();
                    return true;
                }
            }
            cout << "User authentication failed!" << endl;
            inFile.close();
            return false;
        }
        else
        {
            cout << "Error: Unable to open file for authentication." << endl;
            return false;
        }
    }

    void setProfilePicture(const string& picture)
    {
        profilePicture = picture;
        cout << "Profile picture updated!" << endl;
    }

    void setCoverPhoto(const string& photo)
    {
        coverPhoto = photo;
        cout << "Cover photo updated!" << endl;
    }

    void sendFriendRequest(User& friendUser)
    {
        friendUser.receiveFriendRequest(userID);
    }

    void receiveFriendRequest(const string& senderID)
    {
        if (pendingRequestCount < MAX_USERS)
        {
            pendingRequests[pendingRequestCount++] = senderID;
            cout << "Received friend request from User ID: " << senderID << endl;
        }
        else
        {
            cout << "Maximum pending requests reached." << endl;
        }
    }

    void acceptFriendRequest(const string& friendID)
    {
        if (friendCount < MAX_USERS)
        {
            friends[friendCount++] = friendID;

            // Write the updated friend list to a file for the current user
            ofstream outFile(userID + "_friends.txt", ios::binary | ios::app);
            if (outFile.is_open())
            {
                outFile << friendID << "\n";
                outFile.close();
            }

            ifstream inFile(friendID + "_friends.txt");
            string friendList;
            if (inFile.is_open())
            {
                getline(inFile, friendList);
                inFile.close();
            }

            // Append the current user to the friend's friend list
            ofstream friendOutFile(friendID + "_friends.txt");
            if (friendOutFile.is_open())
            {
                friendOutFile << userID << "\n"
                    << friendList;
                friendOutFile.close();
            }
            else
            {
                cout << "Error: Unable to open file for writing friend's friend list." << endl;
            }

            cout << "Friend request from User ID: " << friendID << " accepted!" << endl;
            return;
        }
        else
        {
            cout << "Cannot accept more friends. Friend limit reached." << endl;
            return;
        }
    }

    void declineFriendRequest(const string& friendID)
    {
        for (int i = 0; i < pendingRequestCount; ++i)
        {
            if (pendingRequests[i] == friendID)
            {
                for (int j = i; j < pendingRequestCount - 1; ++j)
                {
                    pendingRequests[j] = pendingRequests[j + 1];
                }
                pendingRequestCount--;
                cout << "Friend request from User ID: " << friendID << " declined!" << endl;
                return;
            }
        }
        cout << "No pending friend request from User ID: " << friendID << endl;
    }
};

class Post
{
    string userid, content, postid, date;

public:
    Post()
    {
        userid = "";
        content = "";
        postid = "";
        date = "";
    }
    Post(const string& newuserid, const string& newcontent, const string& newpostid)
        : userid(newuserid), content(newcontent), postid(newpostid)
    {

        time_t now = time(0);
        date = time(&now);
        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &now);
        date = string(buffer);
    }

    void setuserid(const string& newuserid)
    {
        userid = newuserid;
    }

    string getuserid() const
    {
        return userid;
    }

    void setcontent(const string& newcontent)
    {
        content = newcontent;
    }

    string getcontent() const
    {
        return content;
    }

    void setpostid(const string& newpostid)
    {
        postid = newpostid;
    }

    string getpostid() const
    {
        return postid;
    }

    string getdate() const
    {
        return date;
    }
    /*BINARY FILE HANDLING*/

   virtual void createpost() 
   {
        ofstream outFile("post_data.bin", ios::binary | ios::app); // Open in binary append mode
        if (outFile.is_open()) 
        {
            // Assuming userid, content, postid, and date are string variables
            outFile.write(userid.c_str(), userid.size() + 1); // Write userid as a C-string (with null terminator)
            outFile.write(content.c_str(), content.size() + 1); // Write content as a C-string (with null terminator)
            outFile.write(postid.c_str(), postid.size() + 1); // Write postid as a C-string (with null terminator)
            outFile.write(date.c_str(), date.size() + 1); // Write date as a C-string (with null terminator)
            cout << "Post created successfully on " << date << endl;
            outFile.close();
        }
        else {
            cout << "Error: Unable to open file for post creation." << endl;
        }
    }
   /* void createpost()
    {
        ofstream outFile("post_data.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << userid << "," << content << "#" << postid << "," << date << "\n";
            cout << "Post created successfully on " << date << endl;
            outFile.close();
        }
        else
        {
            cout << "Error: Unable to open file for post creation." << endl;
        }
    }
    */
};

class Like : public Post
{
    User user;
    string userid, postid, date;

public:
    Like()
    {
        userid = "";
        postid = "";
        date = "";
    }
    Like(const string& newuserid, const string& newpostid) : userid(newuserid), postid(newpostid)
    {
        time_t now;
        time(&now);
        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &now);
        date = string(buffer);
    }
    string getdate() const
    {
        return date;
    }
    void setuserid(const string& newuserid)
    {
        userid = newuserid;
    }
    string getuserid() const
    {
        return userid;
    }
    void setpostid(const string& newpostid)
    {
        postid = newpostid;
    }
    string getpostid() const
    {
        return postid;
    }
    void likepost(User& temp)
    {
        if (temp.isFriend(getuserid()))
        {
            ofstream outFile("like_data.txt", ios::app);
            if (outFile.is_open())
            {
                outFile << userid << "," << postid << "\n";
                cout << "Post liked successfully on !" << date << endl;
                outFile.close();
            }
            else
            {
                cout << "Error: Unable to open file for post like." << endl;
            }
        }
        else
        {
            cout << "You can only like posts of your friends." << endl;
        }
    }
   /*BINARY FILE HANDLING
   
   virtual void likepost(User& temp) {
        if (temp.isFriend(getuserid())) {
            ofstream outFile("like_data.bin", ios::binary | ios::app); // Open in binary append mode
            if (outFile.is_open()) {
                // Assuming userid and postid are string variables
                outFile.write(userid.c_str(), userid.size() + 1); // Write userid as a C-string (with null terminator)
                outFile.write(postid.c_str(), postid.size() + 1); // Write postid as a C-string (with null terminator)
                cout << "Post liked successfully on " << date << endl;
                outFile.close();
            }
            else {
                cout << "Error: Unable to open file for post like." << endl;
            }
        }
        else {
            cout << "You can only like posts of your friends." << endl;
        }
    }
    */
    ~Like() {}
};

class Comment : public Post
{
    string userid, postid, comment, date;
    User user;

public:
    Comment()
    {
        userid = "";
        postid = "";
        comment = "";
        date = "";
    }
    Comment(const string& newuserid, const string& newpostid, const string& newcomment) : userid(newuserid), postid(newpostid), comment(newcomment)
    {

        time_t now;
        time(&now);
        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &now);
        date = string(buffer);
    }
    string getdate() const
    {
        return date;
    }

    void setuserid(const string& newuserid)
    {
        userid = newuserid;
    }
    string getuserid() const
    {
        return userid;
    }
    void setpostid(const string& newpostid)
    {
        postid = newpostid;
    }
    string getpostid() const
    {
        return postid;
    }
    void setcomment(const string& newcomment)
    {
        comment = newcomment;
    }
    string getcomment() const
    {
        return comment;
    }
    /*BINARY FILE HANDLING
    
    void commentpost(User& temp) {
        if (temp.isFriend(getuserid())) {
            ofstream outFile("comment_data.bin", ios::binary | ios::app); // Open in binary append mode
            if (outFile.is_open()) {
                // Assuming userid, postid, and comment are string variables
                outFile.write(userid.c_str(), userid.size() + 1); // Write userid as a C-string (with null terminator)
                outFile.write(postid.c_str(), postid.size() + 1); // Write postid as a C-string (with null terminator)
                outFile.write(comment.c_str(), comment.size() + 1); // Write comment as a C-string (with null terminator)
                cout << "Post commented successfully on " << date << endl;
                outFile.close();
            } else {
                cout << "Error: Unable to open file for post comment." << endl;
            }
        } else {
            cout << "You cannot comment on posts of non-friends." << endl;
        }
    }
    */
    void commentpost(User& temp)
    {
        if (temp.isFriend(getuserid()))
        {
            ofstream outFile("comment_data.txt", ios::app);
            if (outFile.is_open())
            {
                outFile << userid << "," << postid << "," << comment << "\n";
                cout << "Post commented successfully on" << date << endl;
                outFile.close();
            }
            else
            {
                cout << "Error: Unable to open file for post comment." << endl;
            }
        }
        else
        {
            cout << "You can not comment on post of non friend." << endl;
        }
    }
};

class Message : public User
{
private:
    string senderID;
    string receiverID;
    string message;
    User* user;

public:
    Message()
    {
        senderID = "";
        receiverID = "";
        message = "";
    }
    Message(const string& sender, const string& receiver)
    {
        senderID = sender;
        receiverID = receiver;
    }
    Message(const string& newSenderID, const string& newReceiverID, const string& newMessage)
        : senderID(newSenderID), receiverID(newReceiverID), message(newMessage) {}

    void setSenderID(const string& newSenderID)
    {
        senderID = newSenderID;
    }
    string getSenderID() const
    {
        return senderID;
    }
    void setReceiverID(const string& newReceiverID)
    {
        receiverID = newReceiverID;
    }
    string getReceiverID() const
    {
        return receiverID;
    }
    void setMessage(const string& newMessage)
    {
        message = newMessage;
    }
    string getMessage() const
    {
        return message;
    }
    void sendMessage(User& temp) {
        ofstream outFile("message_data.bin", ios::app | ios::binary);

        if (outFile.is_open()) {
            cout << "Message sent successfully!" << endl;

            // Writing the data to the binary file
            outFile.write(senderID.c_str(), senderID.size());
            outFile.write("\0", sizeof(char)); // Add null character as a separator

            outFile.write(receiverID.c_str(), receiverID.size());
            outFile.write("\0", sizeof(char)); // Add null character as a separator

            outFile.write(message.c_str(), message.size());
            outFile.write("\0", sizeof(char)); // Add null character as a separator

            outFile.close();
        }
        else {
            cout << "Error: Unable to open file for message sending." << endl;
        }
    }
};
class groupsandpages : public User
{
private:
    string groupid;
    string pageid;
    string groupname;
    string pagename;
    string grouppost;
    string pagepost;

public:
    groupsandpages()
    {
        groupid = "";
        pageid = "";
        groupname = "";
        pagename = "";
        grouppost = "";
        pagepost = "";
    }
    groupsandpages(const string& newgroupid, const string& newpageid, const string& newgroupname, const string& newpagename, const string& newgrouppost, const string& newpagepost)
        : groupid(newgroupid), pageid(newpageid), groupname(newgroupname), pagename(newpagename), grouppost(newgrouppost), pagepost(newpagepost) {}

    void setgroupid(const string& newgroupid)
    {
        groupid = newgroupid;
    }
    string getgroupid() const
    {
        return groupid;
    }
    void setpageid(const string& newpageid)
    {
        pageid = newpageid;
    }
    string getpageid() const
    {
        return pageid;
    }
    void setgroupname(const string& newgroupname)
    {
        groupname = newgroupname;
    }
    string getgroupname() const
    {
        return groupname;
    }
    void setpagename(const string& newpagename)
    {
        pagename = newpagename;
    }
    string getpagename() const
    {
        return pagename;
    }
    void setgrouppost(const string& newgrouppost)
    {
        grouppost = newgrouppost;
    }
    string getgrouppost() const
    {
        return grouppost;
    }
    void setpagepost(const string& newpagepost)
    {
        pagepost = newpagepost;
    }
    string getpagepost() const
    {
        return pagepost;
    }
    void creategroup() {
        ofstream outFile("group_data.bin", ios::app | ios::binary);

        if (outFile.is_open()) {
            size_t idSize = groupid.size();
            size_t nameSize = groupname.size();
            size_t postSize = grouppost.size();

            // Write the size of each string as a header to know the size during reading
            outFile.write(reinterpret_cast<const char*>(&idSize), sizeof(size_t));
            outFile.write(groupid.c_str(), idSize);

            outFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(size_t));
            outFile.write(groupname.c_str(), nameSize);

            outFile.write(reinterpret_cast<const char*>(&postSize), sizeof(size_t));
            outFile.write(grouppost.c_str(), postSize);

            cout << "Group created successfully!" << endl;
            outFile.close();
        }
        else {
            cout << "Error: Unable to open file for group creation." << endl;
        }
    }


    void existinggroup() {
        ifstream inFile("group_data.bin", ios::binary);
        char c;
        if (inFile.is_open()) {
            string group_id, group_name, group_post;
            bool recording_id = false, recording_name = false;

            while (!inFile.eof()) {

                inFile.read(&c, sizeof(char));

                if (c == '\0') {
                    if (!recording_id) {
                        recording_id = true;
                    }
                    else if (!recording_name) {
                        recording_name = true;
                    }
                    else {
                        // End of group data, break loop
                        break;
                    }
                }
                else {
                    if (!recording_id) {
                        group_id += c;
                    }
                    else if (!recording_name) {
                        group_name += c;
                    }
                    else {
                        group_post += c;
                    }
                }
            }
            group_id.erase(group_id.find_last_not_of(" \n\r\t") + 1);
            group_name.erase(group_name.find_last_not_of(" \n\r\t") + 1);
            group_post.erase(group_post.find_last_not_of(" \n\r\t") + 1);
            if (group_id == getgroupid()) {
                cout << "You joined:\n";
                cout << "Group ID: " << group_id << endl;
                cout << "Group Name: " << group_name << endl;
                cout << "Group Posts: " << group_post << endl;
            }

            inFile.close();
        }
        else {
            cout << "Error: Unable to open file for reading group data." << endl;
        }
    }

    void createpage() {
        ofstream outFile("page_data.bin", ios::app | ios::binary);

        if (outFile.is_open()) {
            size_t idSize = pageid.size();
            size_t nameSize = pagename.size();
            size_t postSize = pagepost.size();

            // Writing pageid, pagename, and pagepost directly as binary data
            outFile.write(reinterpret_cast<const char*>(&idSize), sizeof(size_t));
            outFile.write(reinterpret_cast<const char*>(&pageid[0]), idSize * sizeof(char));

            outFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(size_t));
            outFile.write(reinterpret_cast<const char*>(&pagename[0]), nameSize * sizeof(char));

            outFile.write(reinterpret_cast<const char*>(&postSize), sizeof(size_t));
            outFile.write(reinterpret_cast<const char*>(&pagepost[0]), postSize * sizeof(char));

            cout << "Page created successfully!" << endl;
            outFile.close();
        }
        else {
            cout << "Error: Unable to open file for page creation." << endl;
        }
    }

};
class Search : public User
{
    User* user;
public:
    Search() {}

    void searchUsersByLocation(const string& location) {
        ifstream inFile("user_data.bin", ios::binary);

        if (inFile.is_open()) {
            string matchingUsers;
            bool found = false;

            while (!inFile.eof()) {
                size_t locationSize;
                inFile.read(reinterpret_cast<char*>(&locationSize), sizeof(size_t));

                if (inFile.eof()) {
                    break;
                }

                // Read the location string
                char* buffer = new char[locationSize];
                inFile.read(buffer, locationSize);
                string userLocation(buffer, locationSize);

                delete[] buffer;

                if (userLocation == location) {
                    found = true;

                    // If you have other user data stored here, read it similarly
                    // For example, read and append other user data to matchingUsers

                    matchingUsers += userLocation + "\n"; // For now, adding location only
                }
            }

            inFile.close();

            // Display matching users
            if (found) {
                cout << "Users from " << location << ":\n" << matchingUsers;
            }
            else {
                cout << "No users found from " << location << "." << endl;
            }
        }
        else {
            cout << "Error: Unable to open file for reading user data." << endl;
        }
    }

    void searchUsersWithCommonFriends(User& temp1, User& temp2)
    {

        bool found = false;


        for (int i = 0; i < temp1.getfriend(); i++)
        {
            for (int j = 0; j < temp2.getfriend(); j++)
            {
                if (temp1.friends[i] == temp2.friends[j])
                {

                    found = true;
                    cout << "common friend is " << temp1.friends[i] << endl;
                    break;
                }
            }
        }
        if (!found)
        {
            cout << "no common friend" << endl;
        }

        /*
        ifstream inFile("user_data.txt");
        if (inFile.is_open())
        {
            string matchingUsers;
            bool found = false;

            string line;
            while (getline(inFile, line))
            {
                string userFriends;
                bool recordingFriends = false;
                for (int i = 0; i < line.length(); i++)
                {
                    char c = line[i];
                    if (c == '@')
                    {
                        recordingFriends = true;
                        continue;
                    }
                    if (c == '#')
                    {
                        recordingFriends = false;
                        break;
                    }
                    if (recordingFriends)
                    {
                        userFriends += c;
                    }
                }

                bool found1 = false, found2 = false;
                string id;
                for (char c : userFriends)
                {
                    if (c == ',')
                    {
                        if (id == temp1.getUserID())
                            found1 = true;
                        if (id == temp2.getUserID())
                            found2 = true;
                        id.clear();
                    }
                    else
                    {
                        id += c;
                    }
                }
                if (!id.empty())
                {
                    if (id == temp1.getUserID())
                        found1 = true;
                    if (id == temp2.getUserID())
                        found2 = true;
                }

                if (found1 && found2)
                {
                    found = true;
                    matchingUsers += line + "\n";
                }
            }

            inFile.close();

            // Display matching users
            if (found)
            {
                cout << "Users with common friends:\n"
                     << matchingUsers;
            }
            else
            {
                cout << "No users found with common friends." << endl;
            }
        }
        else
        {
            cout << "Error: Unable to open file for reading user data." << endl;
        }
        */
    }

};
