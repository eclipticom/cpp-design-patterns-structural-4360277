#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Storage
{
public:
    virtual const string getContents() = 0;
    virtual ~Storage() = default;
};

class SecureStorage : public Storage
{
public:
    explicit SecureStorage(const string &data) : m_Contents(data) {}

    const string getContents()
    {
        return m_Contents;
    }

private:
    const string m_Contents;
};

class SecureStorageProxy : public Storage
{
public:
    explicit SecureStorageProxy(const string &data, const string &pwd) : m_password(pwd), m_secureStorage(make_unique<SecureStorage>(data)) {}


    const string getContents() override
    {
        // Limit access to sensitive data
        if (m_isAuthenticated)
        {
            return m_secureStorage->getContents();
        }
        return "Access Denied";
    }
    private:        
        unique_ptr<SecureStorage> m_secureStorage;
        string m_password;
        bool m_isAuthenticated = false;
};


int main()
{

    cout << "\nWrong password: \n";
    SecureStorageProxy secureStorage1("Top Secret Information", "wrong_password");
    cout << "Sensitive Data: " << secureStorage1.getContents() << endl;

    cout << "\nCorrect password: \n";
    SecureStorageProxy secureStorage2("Top Secret Information", "wrong_password");
    cout << "Sensitive Data: " << secureStorage2.getContents() << endl;


    return 0;
}
