#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

class VIDEO {
private:
    static int nextVideoID;
    int video_ID;
    string movie_Title;
    string genre;
    string production;
    int number_of_Copies;
    string movie_Filename;

public:
    int getVideoID() const { return video_ID; }
    string getMovieTitle() const { return movie_Title; }
    string getGenre() const { return genre; }
    string getProduction() const { return production; }
    int getNumberOfCopies() const { return number_of_Copies; }
    string getMovieFilename() const { return movie_Filename; }
    void add_NewVideo(list<VIDEO>& videoList);
    void rent_Video(queue<int>& rentedVideos);
    void return_Video(queue<int>& rentedVideos);
    void show_Details();
    void display_all_Videos(const list<VIDEO>& videoList);
    bool is_available(stack<int>& rentedVideos);
};

class CUSTOMER {
protected:
    static int nextCustomerID;
    int customer_ID;
    string customer_Name;
    string customer_Address;

public:
    void add_Customer(list<CUSTOMER>& customerList);
    void show_Customer_Details(const list<CUSTOMER>& customerList);
    void list_Videos_Rented(const list<VIDEO>& videoList, queue<int>& rentedVideos);

    int get_Customer_ID();
};

class CUSTOMER_RENT : public CUSTOMER {
protected:
    int rentedCustomer_ID = 0;
    stack<int> rentedVideos;

public:
    CUSTOMER_RENT(int id) : rentedCustomer_ID(id) {};
    int get_Customer_ID();
    void rentVideo(int videoId, queue<int>& rentedVideos) { rentedVideos.push(videoId); }
};

int VIDEO::nextVideoID = 0;
int CUSTOMER::nextCustomerID = 0;

// Function to read the contents of a file into a string
string readFromFile(const string& filename) {
    ifstream file(filename);
    if (file) {
        string contents((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        return contents;
    }
    else {
        cout << "Failed to read from file: " << filename << endl;
        return "";
    }
}

// Function to write a string to a file
void writeToFile(const string& filename, const string& content) {
    ofstream file(filename);
    if (file) {
        file << content;
        cout << "Data written to file: " << filename << endl;
    }
    else {
        cout << "Failed to write to file: " << filename << endl;
    }
}

void VIDEO::add_NewVideo(list<VIDEO>& videoList) {
    VIDEO newVideo;
    string newTitle, newGenre, newProduction, newFilename;
    int newCopies;

    cout << "Enter the title of the movie: ";
    cin.ignore();
    getline(cin, newTitle);

    cout << "Enter the genre of the movie: ";
    getline(cin, newGenre);

    cout << "Enter the production of the movie: ";
    getline(cin, newProduction);

    cout << "Enter the number of copies available: ";
    cin >> newCopies;

    cout << "Enter the filename of the movie: ";
    cin.ignore();
    getline(cin, newFilename);

    newVideo.video_ID = nextVideoID++;
    newVideo.movie_Title = newTitle;
    newVideo.genre = newGenre;
    newVideo.production = newProduction;
    newVideo.number_of_Copies = newCopies;
    newVideo.movie_Filename = newFilename;

    videoList.push_back(newVideo);

    // Write the updated video file contents back to the file
    string videoData;
    for (const auto& video : videoList) {
        string videoEntry = to_string(video.video_ID) + "," + video.movie_Title + "," + video.genre + "," + video.production + "," + to_string(video.number_of_Copies) + "," + video.movie_Filename + "\n";
        videoData += videoEntry;
    }
    writeToFile("VIDEO.txt", videoData);

    cout << "New video added successfully!" << endl;
}

void VIDEO::rent_Video(queue<int>& rentedVideos) {
    int videoId;
    cout << "Enter the video ID to rent: ";
    cin >> videoId;

    rentedVideos.push(videoId);

    cout << "Video rented successfully!" << endl;
}

void VIDEO::return_Video(queue<int>& rentedVideos) {
    int videoId;
    cout << "Enter the video ID to return: ";
    cin >> videoId;

    stack<int> tempStack;

    while (!rentedVideos.empty()) {
        int rentedVideo = rentedVideos.front();
        rentedVideos.pop();

        if (rentedVideo != videoId) {
            tempStack.push(rentedVideo);
        }
    }

    while (!tempStack.empty()) {
        int rentedVideo = tempStack.top();
        tempStack.pop();

        rentedVideos.push(rentedVideo);
    }

    cout << "Video returned successfully!" << endl;
}

void VIDEO::show_Details() {
    int videoId;
    cout << "Enter the video ID: ";
    cin >> videoId;

    // Read the current contents of the video file
    string videoData = readFromFile("VIDEO.txt");

    // Find the details for the specified video
    size_t pos = videoData.find(to_string(videoId) + ",");
    if (pos != string::npos) {
        size_t endPos = videoData.find('\n', pos);
        string videoDetails = videoData.substr(pos, endPos - pos);

        // Split the video details into individual fields
        string delimiter = ",";
        size_t fieldPos = 0;
        string field;
        while ((fieldPos = videoDetails.find(delimiter)) != string::npos) {
            field = videoDetails.substr(0, fieldPos);
            cout << field << endl;
            videoDetails.erase(0, fieldPos + delimiter.length());
        }
        cout << videoDetails << endl;
    }
    else {
        cout << "Video not found." << endl;
    }
}

void VIDEO::display_all_Videos(const list<VIDEO>& videoList) {
    // Display all the videos
    cout << "All Videos:" << endl;
    for (const auto& video : videoList) {
        cout << "Video ID: " << video.video_ID << endl;
        cout << "Title: " << video.movie_Title << endl;
        cout << "Genre: " << video.genre << endl;
        cout << "Production: " << video.production << endl;
        cout << "Number of Copies: " << video.number_of_Copies << endl;
        cout << "Filename: " << video.movie_Filename << endl;
        cout << endl;
    }
}

bool VIDEO::is_available(stack<int>& rentedVideos) {
    int videoId;
    cout << "Enter the video ID: ";
    cin >> videoId;

    stack<int> tempStack;

    while (!rentedVideos.empty()) {
        int rentedVideo = rentedVideos.top();
        rentedVideos.pop();

        if (rentedVideo == videoId) {
            cout << "Video is not available." << endl;

            while (!tempStack.empty()) {
                int rentedVideo = tempStack.top();
                tempStack.pop();

                rentedVideos.push(rentedVideo);
            }

            return false;
        }
        else {
            tempStack.push(rentedVideo);
        }
    }

    while (!tempStack.empty()) {
        int rentedVideo = tempStack.top();
        tempStack.pop();

        rentedVideos.push(rentedVideo);
    }

    cout << "Video is available." << endl;
    return true;
}

void CUSTOMER::add_Customer(list<CUSTOMER>& customerList) {
    CUSTOMER newCustomer;
    string newName, newAddress;
    cout << "Enter the name of the customer: ";
    cin.ignore();
    getline(cin, newName);

    cout << "Enter the address of the customer: ";
    getline(cin, newAddress);

    newCustomer.customer_ID = nextCustomerID++;
    newCustomer.customer_Name = newName;
    newCustomer.customer_Address = newAddress;

    customerList.push_back(newCustomer);

    // Write the updated customer file contents back to the file
    string customerData;
    for (const auto& customer : customerList) {
        string customerEntry = to_string(customer.customer_ID) + "," + customer.customer_Name + "," + customer.customer_Address + "\n";
        customerData += customerEntry;
    }
    writeToFile("CUSTOMER.txt", customerData);

    cout << "New customer added successfully!" << endl;
}

void CUSTOMER::show_Customer_Details(const list<CUSTOMER>& customerList) {
    int customerId;
    cout << "Enter the customer ID: ";
    cin >> customerId;

    // Find the details for the specified customer
    for (const auto& customer : customerList) {
        if (customer.customer_ID == customerId) {
            cout << "Customer ID: " << customer.customer_ID << endl;
            cout << "Name: " << customer.customer_Name << endl;
            cout << "Address: " << customer.customer_Address << endl;
            cout << endl;
            return;
        }
    }

    cout << "Customer not found." << endl;
}

void CUSTOMER::list_Videos_Rented(const list<VIDEO>& videoList, queue<int>& rentedVideos) {
    int customerId;
    cout << "Enter the customer ID: ";
    cin >> customerId;

    cout << "Videos rented by the customer:" << endl;

    bool found = false;

    // Iterate over rented videos queue and check for customer's rented videos
    queue<int> tempQueue = rentedVideos;
    while (!tempQueue.empty()) {
        int rentedVideoId = tempQueue.front();
        tempQueue.pop();

        for (const auto& video : videoList) {
            if (video.getVideoID() == rentedVideoId) {
                cout << "Video ID: " << video.getVideoID() << endl;
                cout << "Title: " << video.getMovieTitle() << endl;
                cout << "Genre: " << video.getGenre() << endl;
                cout << "Production: " << video.getProduction() << endl;
                cout << "Number of Copies: " << video.getNumberOfCopies() << endl;
                cout << "Filename: " << video.getMovieFilename() << endl;
                cout << endl;

                found = true;
                break;
            }
        }

        if (found) {
            break;
        }
    }

    if (!found) {
        cout << "No videos rented by the customer." << endl;
    }
}

int CUSTOMER::get_Customer_ID() {
    return customer_ID;
}

int CUSTOMER_RENT::get_Customer_ID() {
    return rentedCustomer_ID;
}

int main() {
    list<VIDEO> videoList;
    list<CUSTOMER> customerList;
    queue<int> rentedVideos;

    int choice;
    while (true) {
        try {
            cout << "-----------------------------" << endl;
            cout << "Video Store Management System" << endl;
            cout << "-----------------------------" << endl;
            cout << "[1] New Video" << endl;
            cout << "[2] Rent a Video" << endl;
            cout << "[3] Return a Video" << endl;
            cout << "[4] Show Video Details" << endl;
            cout << "[5] Display all Videos" << endl;
            cout << "[6] Check Video Availability" << endl;
            cout << "[7] Customer Maintenance" << endl;
            cout << "[8] Exit Program" << endl << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                // New Video
                VIDEO video;
                video.add_NewVideo(videoList);
                break;
            }
            case 2: {
                // Rent a Video
                VIDEO video;
                video.rent_Video(rentedVideos);
                break;
            }
            case 3: {
                // Return a Video
                VIDEO video;
                video.return_Video(rentedVideos);
                break;
            }
            case 4: {
                // Show Video Details
                VIDEO video;
                video.show_Details();
                break;
            }
            case 5: {
                // Display all Videos
                VIDEO video;
                video.display_all_Videos(videoList);
                break;
            }
            case 6: {
                // Check Video Availability
                VIDEO video;
                if (video.is_available(reinterpret_cast<stack<int>&>(rentedVideos)))
                {
                    cout << "Video is available." << endl;
                }
                else
                {
                    cout << "Video is not available." << endl;
                }
                break;
            }
            case 7: {
                // Customer Maintenance
                int customerChoice;
                cout << "-----------------------------" << endl;
                cout << "Customer Maintenance" << endl;
                cout << "-----------------------------" << endl;
                cout << "[1] Add New Customer" << endl;
                cout << "[2] Show Customer Details" << endl;
                cout << "[3] List Videos Rented by Customer" << endl;
                cout << "Enter your choice: ";
                cin >> customerChoice;

                switch (customerChoice) {
                case 1: {
                    CUSTOMER customer;
                    customer.add_Customer(customerList);
                    break;
                }
                case 2: {
                    CUSTOMER customer;
                    customer.show_Customer_Details(customerList);
                    break;
                }
                case 3: {
                    CUSTOMER customer;
                    customer.list_Videos_Rented(videoList, rentedVideos);
                    break;
                }
                default: {
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
                }
                break;
            }
            case 8: {
                // Exit Program
                return 0;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
            }
        }
        catch (const exception& e) {
            cout << "An error occurred: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return 0;
}
