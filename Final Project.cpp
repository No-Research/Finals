#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

// Video ADT
class Video {
private:
    int videoId;
    string movieTitle;
    string genre;
    string production;
    int numCopies;
    string movieImageFilename;

public:
    Video(int id, const string& title, const string& genre, const string& production, int copies, const string& imageFilename)
        : videoId(id), movieTitle(title), genre(genre), production(production), numCopies(copies), movieImageFilename(imageFilename) {}

    int getVideoId() const { return videoId; }
    string getMovieTitle() const { return movieTitle; }
    string getGenre() const { return genre; }
    string getProduction() const { return production; }
    int getNumCopies() const { return numCopies; }
    string getMovieImageFilename() const { return movieImageFilename; }

    void setNumCopies(int copies) { numCopies = copies; }
};

// Customer ADT
class Customer {
private:
    int customerId;
    string name;
    string address;

public:
    Customer(int id, const string& name, const string& address)
        : customerId(id), name(name), address(address) {}

    int getCustomerId() const { return customerId; }
    string getName() const { return name; }
    string getAddress() const { return address; }
};

// CustomerRent ADT
class CustomerRent {
private:
    int customerId;
    stack<int> rentedVideos;

public:
    CustomerRent(int id) : customerId(id) {}

    int getCustomerId() const { return customerId; }

    void rentVideo(int videoId) { rentedVideos.push(videoId); }

    void returnVideo() {
        if (!rentedVideos.empty()) {
            rentedVideos.pop();
        }
    }

    bool hasRentedVideos() const { return !rentedVideos.empty(); }

    stack<int> getRentedVideos() const { return rentedVideos; }

    void printRentedVideos() const {
        stack<int> temp = rentedVideos;
        while (!temp.empty()) {
            cout << "Video ID: " << temp.top() << endl;
            temp.pop();
        }
    }
};












// Function to load videos from text file
list<Video> loadVideosFromFile() {
    list<Video> videos;
    ifstream file("videos.txt");
    if (file.is_open()) {
        int id;
        string title, genre, production, imageFilename;
        int copies;

        while (file >> id >> title >> genre >> production >> copies >> imageFilename) {
            videos.emplace_back(id, title, genre, production, copies, imageFilename);
        }

        file.close();
    }
    return videos;
}

// Function to save videos to text file
void saveVideosToFile(const list<Video>& videos) {
    ofstream file("videos.txt");
    if (file.is_open()) {
        for (const Video& video : videos) {
            file << video.getVideoId() << " " << video.getMovieTitle() << " " << video.getGenre() << " "
                << video.getProduction() << " " << video.getNumCopies() << " " << video.getMovieImageFilename() << endl;
        }
        file.close();
    }
}

// Function to load customers from text file
queue<Customer> loadCustomersFromFile() {
    queue<Customer> customers;
    ifstream file("customers.txt");
    if (file.is_open()) {
        int id;
        string name, address;

        while (file >> id >> name >> address) {
            customers.emplace(id, name, address);
        }

        file.close();
    }
    return customers;
}

// Function to save customers to text file
void saveCustomersToFile(const queue<Customer>& customers) {
    ofstream file("customers.txt");
    if (file.is_open()) {
        queue<Customer> temp = customers;
        while (!temp.empty()) {
            const Customer& customer = temp.front();
            file << customer.getCustomerId() << " " << customer.getName() << " " << customer.getAddress() << endl;
            temp.pop();
        }
        file.close();
    }
}

// Function to save rented videos to text file
void saveRentedVideosToFile(const list<CustomerRent>& customerRents) {
    ofstream file("customer_rent.txt");
    if (file.is_open()) {
        for (const CustomerRent& customerRent : customerRents) {
            int customerId = customerRent.getCustomerId();
            stack<int>& rentedVideos = customerRent.getRentedVideos();

            while (!rentedVideos.empty()) {
                file << customerId << " " << rentedVideos.top() << endl;
                rentedVideos.pop();
            }
        }
        file.close();
    }
}

// Function to check if a video is available
bool isVideoAvailable(const list<Video>& videos, int videoId) {
    for (const Video& video : videos) {
        if (video.getVideoId() == videoId && video.getNumCopies() > 0) {
            return true;
        }
    }
    return false;
}

// Function to find a video by ID
const Video* findVideoById(const list<Video>& videos, int videoId) {
    for (const Video& video : videos) {
        if (video.getVideoId() == videoId) {
            return &video;
        }
    }
    return nullptr;
}

// Function to find a customer by ID
const Customer* findCustomerById(const queue<Customer>& customers, int customerId) {
    queue<Customer> temp = customers;
    while (!temp.empty()) {
        const Customer& customer = temp.front();
        if (customer.getCustomerId() == customerId) {
            return &customer;
        }
        temp.pop();
    }
    return nullptr;
}

int main() {
    list<Video> videos = loadVideosFromFile();
    queue<Customer> customers = loadCustomersFromFile();
    list<CustomerRent> customerRents;

    int choice;
    while (true) {
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
        cout << "[8] Exit Program" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            // New Video
            // TODO: Implement
            break;
        }
        case 2: {
            // Rent a Video
            // TODO: Implement
            break;
        }
        case 3: {
            // Return a Video
            // TODO: Implement
            break;
        }
        case 4: {
            // Show Video Details
            // TODO: Implement
            break;
        }
        case 5: {
            // Display all Videos
            // TODO: Implement
            break;
        }
        case 6: {
            // Check Video Availability
            // TODO: Implement
            break;
        }
        case 7: {
            // Customer Maintenance
            // TODO: Implement
            break;
        }
        case 8: {
            // Exit Program
            saveVideosToFile(videos);
            saveCustomersToFile(customers);
            saveRentedVideosToFile(customerRents);
            return 0;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    }

    return 0;
}
