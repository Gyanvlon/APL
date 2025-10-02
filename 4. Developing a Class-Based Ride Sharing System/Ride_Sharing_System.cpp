#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>

// Base Ride class demonstrating encapsulation and inheritance foundation
class Ride {
private:
    int rideID;
    std::string pickupLocation;
    std::string dropoffLocation;
    double distance;

protected:
    double baseFareRate;
public:
    // Constructor
    Ride(int id, const std::string& pickup, const std::string& dropoff, double dist)
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distance(dist), baseFareRate(2.0) {}

    // Virtual destructor for proper polymorphism
    virtual ~Ride() = default;
    // Virtual method for polymorphism - to be overridden by subclasses
    virtual double fare() const {
        return distance * baseFareRate;
    }
    // Method to display ride details
    virtual void rideDetails() const {
        std::cout << "Ride ID: " << rideID << std::endl;
        std::cout << "Pickup: " << pickupLocation << std::endl;
        std::cout << "Dropoff: " << dropoffLocation << std::endl;
        std::cout << "Distance: " << distance << " miles" << std::endl;
        std::cout << "Fare: $" << std::fixed << std::setprecision(2) << fare() << std::endl;
    }

    // Getter methods (encapsulation)
    int getRideID() const { return rideID; }
    std::string getPickupLocation() const { return pickupLocation; }
    std::string getDropoffLocation() const { return dropoffLocation; }
    double getDistance() const { return distance; }

    // Virtual method to get ride type (for polymorphism demonstration)
    virtual std::string getRideType() const { return "Standard"; }
};

// StandardRide class - inheritance and polymorphism
class StandardRide : public Ride {
public:
    StandardRide(int id, const std::string& pickup, const std::string& dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {
        baseFareRate = 2.0;
    }

    // Override fare method (polymorphism)
    double fare() const override {
        return getDistance() * baseFareRate;
    }

    std::string getRideType() const override {
        return "Standard";
    }
};

// PremiumRide class - inheritance and polymorphism
class PremiumRide : public Ride {
private:
    double luxuryMultiplier;

public:
    PremiumRide(int id, const std::string& pickup, const std::string& dropoff, double dist)
        : Ride(id, pickup, dropoff, dist), luxuryMultiplier(1.8) {
        baseFareRate = 3.5;
    }

    // Override fare method with premium pricing (polymorphism)
    double fare() const override {
        return getDistance() * baseFareRate * luxuryMultiplier;
    }

    std::string getRideType() const override {
        return "Premium";
    }

    void rideDetails() const override {
        std::cout << "=== PREMIUM RIDE ===" << std::endl;
        Ride::rideDetails();
        std::cout << "Luxury Multiplier: " << luxuryMultiplier << "x" << std::endl;
    }
};

// Driver class demonstrating encapsulation
class Driver {
private:
    int driverID;
    std::string name;
    double rating;
    std::vector<std::shared_ptr<Ride>> assignedRides; // Encapsulated - private member

public:
    Driver(int id, const std::string& driverName, double driverRating)
        : driverID(id), name(driverName), rating(driverRating) {}

    // Method to add ride (controlled access to private member)
    void addRide(std::shared_ptr<Ride> ride) {
        assignedRides.push_back(ride);
    }

    // Method to display driver info
    void getDriverInfo() const {
        std::cout << "\n=== DRIVER INFORMATION ===" << std::endl;
        std::cout << "Driver ID: " << driverID << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Rating: " << rating << "/5.0" << std::endl;
        std::cout << "Total Rides Completed: " << assignedRides.size() << std::endl;
        
        double totalEarnings = 0.0;
        for (const auto& ride : assignedRides) {
            totalEarnings += ride->fare();
        }
        std::cout << "Total Earnings: $" << std::fixed << std::setprecision(2) << totalEarnings << std::endl;
    }

    // Getter methods (controlled access)
    int getDriverID() const { return driverID; }
    std::string getName() const { return name; }
    double getRating() const { return rating; }
    size_t getRideCount() const { return assignedRides.size(); }
};

// Rider class demonstrating encapsulation
class Rider {
private:
    int riderID;
    std::string name;
    std::vector<std::shared_ptr<Ride>> requestedRides; // Encapsulated - private member

public:
    Rider(int id, const std::string& riderName)
        : riderID(id), name(riderName) {}

    // Method to request a ride (controlled access to private member)
    void requestRide(std::shared_ptr<Ride> ride) {
        requestedRides.push_back(ride);
        std::cout << "Ride requested by " << name << " (ID: " << riderID << ")" << std::endl;
    }

    // Method to view ride history
    void viewRides() const {
        std::cout << "\n=== RIDER RIDE HISTORY ===" << std::endl;
        std::cout << "Rider: " << name << " (ID: " << riderID << ")" << std::endl;
        std::cout << "Total Rides: " << requestedRides.size() << std::endl;
        
        double totalSpent = 0.0;
        for (size_t i = 0; i < requestedRides.size(); ++i) {
            std::cout << "\n--- Ride " << (i + 1) << " ---" << std::endl;
            requestedRides[i]->rideDetails();
            totalSpent += requestedRides[i]->fare();
        }
        std::cout << "\nTotal Amount Spent: $" << std::fixed << std::setprecision(2) << totalSpent << std::endl;
    }

    // Getter methods (controlled access)
    int getRiderID() const { return riderID; }
    std::string getName() const { return name; }
    size_t getRideCount() const { return requestedRides.size(); }
};

// Demonstration function showing polymorphism
void demonstratePolymorphism(const std::vector<std::shared_ptr<Ride>>& rides) {
    std::cout << "\n=== POLYMORPHISM DEMONSTRATION ===" << std::endl;
    std::cout << "Processing different ride types polymorphically:" << std::endl;
    
    double totalFares = 0.0;
    for (const auto& ride : rides) {
        std::cout << "\n--- " << ride->getRideType() << " Ride ---" << std::endl;
        ride->rideDetails(); // Polymorphic call
        totalFares += ride->fare(); // Polymorphic call
    }
    
    std::cout << "\nTotal Fares for All Rides: $" << std::fixed << std::setprecision(2) << totalFares << std::endl;
}

int main() {
    std::cout << "=== RIDE SHARING SYSTEM - C++ IMPLEMENTATION ===" << std::endl;
    std::cout << "Demonstrating OOP Principles: Encapsulation, Inheritance, and Polymorphism" << std::endl;

    // Create different types of rides (inheritance and polymorphism)
    auto standardRide1 = std::make_shared<StandardRide>(1, "Downtown", "Airport", 15.5);
    auto premiumRide1 = std::make_shared<PremiumRide>(2, "Hotel", "Convention Center", 8.2);
    auto standardRide2 = std::make_shared<StandardRide>(3, "Mall", "University", 12.0);
    auto premiumRide2 = std::make_shared<PremiumRide>(4, "Airport", "Luxury Resort", 25.8);

    // Create driver and rider objects (encapsulation)
    Driver driver1(101, "John Smith", 4.8);
    Driver driver2(102, "Sarah Johnson", 4.9);
    Rider rider1(201, "Alice Brown");
    Rider rider2(202, "Bob Wilson");

    // Assign rides to drivers
    driver1.addRide(standardRide1);
    driver1.addRide(premiumRide1);
    driver2.addRide(standardRide2);
    driver2.addRide(premiumRide2);

    // Riders request rides
    rider1.requestRide(standardRide1);
    rider1.requestRide(premiumRide2);
    rider2.requestRide(premiumRide1);
    rider2.requestRide(standardRide2);

    // Display driver information (encapsulation demonstration)
    driver1.getDriverInfo();
    driver2.getDriverInfo();

    // Display rider ride history (encapsulation demonstration)
    rider1.viewRides();
    rider2.viewRides();

    // Demonstrate polymorphism with mixed ride types
    std::vector<std::shared_ptr<Ride>> allRides = {standardRide1, premiumRide1, standardRide2, premiumRide2};
    demonstratePolymorphism(allRides);

    return 0;
}