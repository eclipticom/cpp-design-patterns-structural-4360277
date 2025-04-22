#include <iostream>
#include <string>
#include <memory>
#include <ctime>
#include <random>

using namespace std;

class CloudStorage
{
public:
    virtual bool uploadContents(const string& content) = 0;
    virtual int getFreeSpace() = 0;
    virtual ~CloudStorage() = default;
};

class CloudDrive : public CloudStorage
{
public:
    bool uploadContents(const string& content) override
    {
        cout << "Uploading " << content.length() << " bytes to CloudDrive: " << endl;

        return true;
    }

    int getFreeSpace() override
    {
        // Implement the logic for getting the free space on CloudDrive here.
        // const int size = arc4random_uniform(20);
        const int size = 15;
        cout << "Available CloudDrive storage: " << size << "GB" << endl;
        return size;
    }
};

class FastShare : public CloudStorage
{
public:
    bool uploadContents(const string& content) override
    {
        cout << "Uploading " << content.length() << " bytes to FastShare: " << endl;
        return true;
    }

    int getFreeSpace() override
    {
        // const int size = arc4random_uniform(10);
        const int size = 6;
        cout << "Available FastShare storage: " << size << "GB" << endl;
        return size;
    }
};

// 3rd party service
class VirtualDrive
{
public:
    bool uploadData(const string& data, const int uniqueID)
    {
        cout << "Uploading to VirtualDrive: \"" << data << "\" ID: " << uniqueID << endl;
        return true;
    }
    int usedSpace()
    {
        //return arc4random_uniform(10);
        return 5;
    }
    const int totalSpace = 15;
};


/// Adaptor class
class VirtualDriveAdaptor : public CloudStorage, public VirtualDrive
{
public:
    bool uploadContents(const string& content) override
    {
        cout << "LegacyClassAdaptor: Uploading " << content.length() << " bytes to VirtualDrive: " << endl;

        // Generate a unique ID for the upload.
        const int uniqueID = rand() % 1000; // Random ID for demonstration purposes.
        return uploadData(content, uniqueID);
    }

    int getFreeSpace() override
    {
        const int usedSpace = VirtualDrive::usedSpace();
        const int freeSpace = VirtualDrive::totalSpace - usedSpace;
        cout << "Available LegacyClassAdaptor storage: " << freeSpace << "GB" << endl;
        return freeSpace;
    }   
};


int main()
{

    // std::random_device rd; // Seed generator
    // std::mt19937 gen(rd()); // Mersenne Twister engine
    // std::uniform_int_distribution<> dist(0, 40); // Range: [0, 40]
    
    // for (auto i = 0; i < 5; ++i)
    // {
    //     int randomValue = dist(gen);
    //     cout << "Random value: " << randomValue << endl;
    // }

    
    // Create an array of pointers to CloudStorage objects.
    const std::unique_ptr<CloudStorage> cloudServices[]
    {
        std::make_unique<CloudDrive>(),
        std::make_unique<FastShare>(),
        std::make_unique<VirtualDriveAdaptor>(),
    };

    // Iterate through the array and invoke the uploadContents and getFreeSpace
    // methods on each object.
    const string content = "Beam me up, Scotty!";
    for (const auto &service : cloudServices)
    {        
        service->uploadContents(content);
        service->getFreeSpace();
        cout << endl;
    }

    return 0;
}
