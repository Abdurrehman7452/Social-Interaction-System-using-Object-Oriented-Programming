# Social Interaction System in C++ using Object Oriented Programming
In this Repository, the Object Oriented Concepts in c++ are used to develop a social interaction system where a user can register him/herself and can make friend, can post, search post, can comment, can like and interact the other user with messaging in private or can make the group.


# Project Classes
- User.h:

Defines the User class with attributes like userID, name, email, password, etc.
Methods include setters and getters for user information, registration, authentication, friend management (request, accept, decline), etc.
Utilizes file handling (ofstream and ifstream) to manage user data persistence in user_data.txt.
Supports friend-related operations and authentication checks.
- Post:

Defines the Post class representing user posts with attributes like userid, content, postid, date.
Constructor initializes post information and captures current date.
Provides methods for setting/getting post details and creation of posts into post_data.txt or post_data.bin using file handling.
- Like:

Represents likes on posts (Like class), inheriting from Post.
Attributes include userid, postid, date.
Methods to set/get like details and perform like actions if users are friends, using file handling (like_data.txt or like_data.bin).
- Comment:

Defines the Comment class representing comments on posts, also inheriting from Post.
Attributes include userid, postid, comment, date.
Methods to set/get comment details and post comments if users are friends, using file handling (comment_data.txt or comment_data.bin).
Message:

Represents messages between users (Message class), inheriting from User.
Attributes include senderID, receiverID, message.
Methods for sending messages, storing in message_data.bin using binary file handling.
- groupsandpages:

Represents groups and pages (groupsandpages class), inheriting from User.
Attributes include groupid, pageid, groupname, pagename, grouppost, pagepost.
Methods for creating groups/pages and managing their data using binary file handling (group_data.bin, page_data.bin).
- Search:

Implements search functionalities (Search class), inheriting from User.
Methods to search users by location or find common friends between users.
Uses binary file handling (user_data.bin) for efficient data retrieval.
# Summary of Functionality:
User Management: Registration, authentication, friend requests, acceptance/decline.
Post Management: Creation of posts, likes, comments, using text or binary file storage.
Message Management: Sending messages between users, stored in binary format.
Groups and Pages: Creation and retrieval of group/page data, stored in binary files.
Search: User location-based search and finding common friends, using binary file data.
# Recommendations:
File Handling: Ensure robust error handling and validation in file operations.
Memory Management: Avoid potential memory leaks, especially with dynamically allocated resources.
Security: Consider encryption for sensitive user data stored in files.
Performance: Optimize file I/O operations, especially in scenarios with potentially large data sets.
These files provide a comprehensive framework for managing social media-like interactions and data persistence in a C++ application.
