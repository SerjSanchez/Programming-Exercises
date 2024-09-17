#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace cpp_logger {

    // To ensure single responsibility, the CppLogger struct only manages log entries and title.
    struct CppLogger {

        private: 
        inline static int count{0};

        public:
            string title;
            vector<string> entries{};

            CppLogger(const string &title) : title(title) { 
                cout << title << " created" << endl;
            }

            void add_entry(const string &entry) {
                count++;
                entries.push_back(entry);
                cout << "Entry " << to_string(count) << " created: " << entry << endl;
            }
    };

    // If we wanted to add persistance for the logger, we would need another struct, that stores loggers
    struct LoggerPersistance {
        public:
            static void storeLogger(const CppLogger &logger) {
                cout << "Not going to implement persistance, so let's say:" << endl;
                cout << logger.title << " stored!" << endl;
            }
    };
}