#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

class LoginUser
{
 public:

    LoginUser()
    {
        accessGranted = 0;
    }
    void login()
    {
        cout << " If you are a user, please enter your user name. \nUsername:";
        cin >> userNameAttempt;

        int usrID = checkFile(userNameAttempt, "users.dat");
        if(usrID != 0)
        {
            cout << "Password:";
            cin >> passwordAttempt;

            int pwdID = checkFile(passwordAttempt, "pswds.dat");
            if(usrID == pwdID)
            {
                cout << "Hello user. \n" << endl;;
                login();

            }
            else
            {
                cout << "The password is wrong.Try again." << endl;
                login();
            }
        }
        else
        {
            cout << "There is no user with this nick." << endl;
            login();
        }
    }

    void addUser(const string username, const string password)
    {
        if(checkFile(username, "users.dat") != 0)
        {
            cout << "That username is not available." << endl;
            return;
        }

        int id = 1 + getLastID();
        saveFile(username, "users.dat", id);
        saveFile(password, "pswds.dat", id);
    }

    int getLastID()
    {
        fstream file;
        file.open("users.dat", ios::in);
        file.seekg(0, ios::end);

        if(file.tellg() == -1)
            return 0;

        string s;

        for(int i = -1; s.find("#") == string::npos; i--)
        {
            file.seekg(i, ios::end);
            file >> s;
        }

        file.close();
        s.erase(0, 4);

        int id;
        istringstream(s) >> id;

        return id;
    }

    int checkFile(string attempt, const char* p_fileName)
    {
        string line;
        fstream file;

        string currentChar;
        long long eChar;

        file.open(p_fileName, ios::in);
        
        while(1)
        {
            file >> currentChar;
            if(currentChar.find("#ID:") != string::npos)
            {
                if(attempt == line)
                {
                    file.close();
                    currentChar.erase(0, 4);
                    int id;
                    istringstream(currentChar) >> id;
                    return id;
                }
                else
                {
                    line.erase(line.begin(), line.end());
                }
            }
            else
            {
                istringstream(currentChar) >> eChar;
                line += (char)decrypt(eChar);
                currentChar = "";
            }

            if(file.peek() == EOF)
            {
                file.close();
                return 0;
            }
        }
    }

    void saveFile(string p_line, const char* p_fileName, const int& id)
    {
        fstream file;
        file.open(p_fileName, ios::app);
        file.seekg(0, ios::end);

        if(file.tellg() != 0)
            file << "\n";

        file.seekg(0, ios::beg);

        for(int i = 0; i < p_line.length(); i++)
        {
            file << encrypt(p_line[i]);
            file << "\n";
        }

        file << "#ID:" << id;
        file.close();
    }

    long long encrypt(int p_letter)
    {
        return powf(p_letter, 5) * 4 - 14;
    }
    int decrypt(long long p_letter)
    {
        return powf((p_letter + 14) / 4, 1/5.f);
    }

private:
    string userNameAttempt;
    string passwordAttempt;
    bool accessGranted;
};

int main()
{
    LoginUser app;
    //app.addUser("hammada@coursework.com", "hammadapass");
    app.login();
    cin.get();
}