/*
 * Test program for name-generator
 */
#include <string>
#include "generator.h"

int main(int argc, char* argv[]) {
    std::string race = argv[1];
    std::string gender = argv[2];

    NameGenerator gen(race, gender);

    std::string first("");
    std::string last("");
    std::string full("");

    for(int i = 0; i < 10000; i++) {
        first = gen.make_first();
        last = gen.make_last();
        full = gen.make_name();

        // Check first name function
        if(first == "NULL") return 1;
        if(first.empty()) return 1;

        // Check last name function
        if(last == "NULL") return 1;
        if(last.empty()) return 1;

        // Check full name function
        if(full == "NULL") return 1;
        if(full.empty()) return 1;
    }

    return 0;
}