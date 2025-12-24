#include <Sefn/InputUtils.hpp>
#include <cassert>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

namespace {
const std::string WHITESPACE = " \n\r\t\f\v";

void lTrim(std::string &s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    if (start == std::string::npos) {
        s.clear();
    } else {
        s.erase(0, start);
    }
}

void rTrim(std::string &s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    if (end == std::string::npos) {
        s.clear();
    } else {
        s.erase(end + 1);
    }
}

void trim(std::string &s) {
    rTrim(s);
    lTrim(s);
}
}  // namespace

/**
 * @brief Main system class for managing hospital operations.
 *
 * Handles patient intake, queue management for different specializations,
 * and data persistence.
 */
class HospitalSystem {
    const int MAX_SPEC = 20;

    /**
     * @brief Represents a single patient record.
     */
    struct Patient {
        bool status{false};  ///< false for regular, true for urgent
        std::string name;

        Patient(std::string name, bool status) : status(status), name(name) {}
        Patient() = default;

        /**
         * @brief Deserializes a patient from a string.
         * @param str Formatted string from the database file.
         */
        Patient(std::string str) {
            if (str.length() < 2 || !isValidName(str.substr(1))) {
                // Handle the error gracefully. For now, let's create an invalid patient.
                name = "INVALID_DATA";
                status = false;
                std::cerr << "Warning: Corrupted patient data found in file: " << str << std::endl;
            } else {
                status = (str[0] == '1');
                name = str.substr(1);
            }
        }
        std::string toString() const {
            std::ostringstream oss;
            oss << status << name;
            return oss.str();
        }
        void print() const {
            std::cout << "\t" << std::left << std::setw(25) << name;
            std::cout << (status ? "\turgent\n" : "\tregular\n");
        }
    };

    /**
     * @brief Manages a queue of patients for a specific specialization.
     */
    struct HospitalQueue {
        int id{-1};
        const char DELIM = '|';
        const int MAX_QUEUE = 5;
        std::deque<Patient> patients;

        /**
         * @brief Adds a patient to the queue.
         * @param p The patient to add.
         * @return true if added successfully, false if queue is full.
         */
        bool push(Patient &p) {
            if ((int)patients.size() >= MAX_QUEUE) {
                return false;
            }
            if (p.status) {
                patients.push_front(p);
            } else {
                patients.push_back(p);
            }
            return true;
        }

        /**
         * @brief Removes and returns the next patient.
         * @return A pair containing success status and the patient object.
         */
        std::pair<bool, Patient> pop() {
            Patient ret = Patient();
            if (patients.empty()) {
                return {false, ret};
            } else {
                ret = patients.front();
                patients.pop_front();
                return {true, ret};
            }
        }
        void operator=(const HospitalQueue &other) {
            id = other.id;
            patients = other.patients;
        }
        HospitalQueue(int id = -1) : id(id) {}

        /**
         * @brief Deserializes a queue from a file string.
         */
        HospitalQueue(std::string str) {
            std::string part;
            std::istringstream iss(str);

            // Read specialization ID
            if (getline(iss, part, DELIM)) {
                try {
                    id = std::stoi(part);  // Use std::stoi for safe conversion
                } catch (const std::exception &e) {
                    std::cerr << "Warning: Corrupted queue data in file. Invalid ID: " << part
                              << std::endl;
                    id = -1;  // Set to an invalid state
                    return;   // Stop parsing this corrupted line
                }
            }

            // Read patients
            while (getline(iss, part, DELIM)) {
                if (!part.empty())  // Avoid creating patients from empty parts
                    patients.push_back(Patient(part));
            }
        }
        bool isEmpty() const { return patients.empty(); }
        std::string toString() const {
            std::ostringstream oss;
            oss << id << DELIM;
            for (auto &p : patients) {
                oss << p.toString() << DELIM;
            }
            return oss.str();
        }
        void print() const {
            if (patients.empty()) {
                return;
            }
            std::cout << "There are " << patients.size() << " in specialization " << id + 1
                      << ": \n";
            for (auto &p : patients) {
                p.print();
            }
        }
    };
    std::vector<HospitalQueue> specializations;
    static bool isValidName(std::string name) {
        if (name.size() < 3) {
            return false;
        }
        for (char c : name) {
            if (!islower(c) && c != ' ') {
                return false;
            }
        }
        return true;
    }
    static std::string readName() {
        std::string ret;
        std::cout << "\tEnter name: ";
        getline(std::cin, ret);
        trim(ret);
        while (!isValidName(ret)) {
            std::cout << "\tInvlid name. Try again: ";
            getline(std::cin, ret);
            trim(ret);
        }
        return ret;
    }
    static int readInRange(const std::string &prompt, int indentTabs, int start, int end) {
        std::string errorMessage = "Value must be between " + std::to_string(start) + " and " +
                                   std::to_string(end) + ".\n";
        return Sefn::readValidatedInput<int>(
            prompt, indentTabs, [start, end](int r) { return r >= start && r <= end; },
            errorMessage);
    }
    int readSpecialization() {
        std::string prompt = "Enter specialization[1 - " + std::to_string(MAX_SPEC) + "]: ";
        static const int indentTabs = 1;
        return readInRange(prompt, indentTabs, 1, MAX_SPEC);
    }
    static bool readStatus() {
        static const std::string prompt = "Enter status(0 or 1): ";
        return readInRange(prompt, 1, 0, 1);
    }

    // Core Business Logic

    void addPatient() {
        int spec = readSpecialization();
        specializations[spec].id = spec;
        Patient p = Patient(readName(), readStatus());
        if (!specializations[spec].push(p)) {
            std::cout << "Sorry, we cannot add anymore patients at this specialization\n";
        }
    }

    void getNextPatient() {
        int spec = readSpecialization();
        auto [success, p] = specializations[spec].pop();
        if (success) {
            std::cout << "\t" << p.name << ", please go with the Dr\n";
        } else {
            std::cout << "\tNo patients at the moment. Have rest, Dr\n";
        }
    }

    void printAllPatients() const {
        std::cout << "\n***************\n";
        for (auto &spec : specializations) {
            if (spec.id != -1) {
                spec.print();
            }
        }
        std::cout << "\n***************\n";
    }

    /**
     * @brief Loads the hospital state from 'patients.txt'.
     */
    void loadDatabase() {
        std::ifstream database("patients.txt");
        std::string spec_str;
        specializations.clear();
        specializations.resize(MAX_SPEC);
        while (getline(database, spec_str)) {
            HospitalQueue spec = HospitalQueue(spec_str);
            specializations[spec.id] = spec;
        }
        database.close();
    }

    /**
     * @brief Saves the current hospital state to 'patients.txt'.
     */
    void updateDatabase() {
        std::ofstream database("patients.txt");
        for (auto &spec : specializations) {
            if (!spec.isEmpty()) database << spec.toString() << "\n";
        }
        database.close();
    }

   public:
    /**
     * @brief Starts the application loop.
     */
    void run() {
        std::cout << "\n**********Welcome**********\n";
        loadDatabase();
        while (true) {
            std::cout << "\nEnter your choice: \n";
            std::cout << "\t1) Add a new patient\n";
            std::cout << "\t2) Print all patients\n";
            std::cout << "\t3) Get next patient\n";
            std::cout << "\t4) Exit\n";
            int choice = readInRange("", 0, 1, 4);
            switch (choice) {
                case 1:
                    addPatient();
                    break;
                case 2:
                    printAllPatients();
                    break;
                case 3:
                    getNextPatient();
                    break;
                case 4:
                    updateDatabase();
                    std::cout << "\n************Bye************\n";
                    return;
            }
        }
    }
};

int main() {
    HospitalSystem system;
    system.run();
    return 0;
}