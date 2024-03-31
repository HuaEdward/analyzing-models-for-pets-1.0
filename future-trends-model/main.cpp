#include <iostream>
#include <vector>
#include <random>
using namespace std;

//Sample input:
//Cat: amount: 1000000, age: 6, lifetime: 12
//Dog: amount: 1000000, age: 6, lifetime: 11
//Lizard: amount: 1000000, age: 2, lifetime: 6
//Rabbit: amount: 1000000, age: 6, lifetime: 10

string spec;
double std_deviation;

struct Pet {
    int currentAge;
    int lifetime;

    Pet(int age, int avgLifetime) : currentAge(age) {
        random_device rd;
        mt19937 gen(rd());
        normal_distribution<> d(avgLifetime, std_deviation);
        lifetime = round(d(gen));
    }

    bool isAlive() {
        return currentAge < lifetime;
    }

    void ageOneYear() {
        currentAge++;
    }
};

int main() {
    int numPets, avgAge, avgLifetime;
    cout << "Enter the specie of pets: ";
    cin >> spec;
    cout << "Enter the number of pets: ";
    cin >> numPets;
    cout << "Enter the age of the pets: ";
    cin >> avgAge;

    if (spec == "CAT" || spec == "Cat") {
        std_deviation = 1.6;
        avgLifetime = 12;
    } else if (spec == "DOG" || spec == "Dog") {
        std_deviation = 1.6;
        avgLifetime = 11;
    } else if (spec == "RABBIT" || spec == "Rabbit") {
        std_deviation = 1.4;
        avgLifetime = 10;
    } else if (spec == "LIZARD" || spec == "Lizard") {
        std_deviation = 0.8;
        avgLifetime = 6;
    } else {
        cout << "The model of this specie is still in progress :)";
        return 0;
    }
    
    if (avgAge >= avgLifetime) {
        cout << "Wow! Your pets alreay have a longer life than the average!";
        return 0;
    }

    vector<Pet> pets;
    for (int i = 0; i < numPets; i++) {
        pets.push_back(Pet(avgAge, avgLifetime));
    }

    for (int year = 1; year <= 15; year++) {
        int survivingPets = 0;
        for (Pet &pet : pets) {
            if (pet.isAlive()) {
                survivingPets++;
            }
            pet.ageOneYear();
        }
        cout << "Year " << year << ": " << survivingPets << " pets are predicted to survive.\n";
    }

    return 0;
}
