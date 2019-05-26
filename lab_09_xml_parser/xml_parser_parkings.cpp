#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
#include <libxml++config.h>
#include <iostream>
#include <map>
#include <string>

struct parking {
    std::string number;
    std::string parking_space;

    parking(std::string n, std::string ps) {
        number = n;
        parking_space = ps;
    }
};

int main(int argc, char *argv[]) {
    std::locale::global(std::locale(""));

    Glib::ustring filepath;
    Glib::ustring input_district_city;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            int j = 1;
            std::string cmd = "";
            std::string arg = "";
            while (argv[i][j] != '=') {
                cmd += argv[i][j];
                j++;
            }
            j++;
            while (argv[i][j] != '\0') {
                arg += argv[i][j];
                j++;
            }
            if (cmd == "data") {
                filepath = arg;
            } else if (cmd == "district_city") {
                input_district_city = arg;
            } else {
                std::cout << "\"" << argv[i] << "\" is not a command.\n";
            }
        } else {
            std::cout << "\"" << argv[i] << "\" is not a command.\n";
        }
    }
    if (filepath == "") {
        std::cout << "Enter input_file name.\n";
        return 0;
    }
    if (input_district_city == "") {
        std::cout << "Enter district name.\n";
        return 0;
    }

    std::map<std::string, std::vector<parking>> district_city;
    bool is_open = false;
    std::string cur_number;
    std::string cur_parking_space;
    std::string cur_district_city;
    std::string cur_metro_station;

    xmlpp::TextReader reader(filepath);

    while (reader.read()) {
        if (reader.get_name() == "info_parking") {
            if (is_open && cur_district_city == input_district_city) {
                if (!district_city.count(cur_metro_station)) {
                    district_city.insert({cur_metro_station, std::vector<parking>()});
                }
                district_city.at(cur_metro_station).push_back(parking(cur_number, cur_parking_space));
            }
            is_open = 1 - is_open;
        }
        if (reader.get_name() == "district_city") {
            reader.read();
            cur_district_city = reader.get_value();
            reader.read();
        }
        if (reader.get_name() == "parking_space") {
            reader.read();
            cur_parking_space = reader.get_value();
            reader.read();
        }
        if (reader.get_name() == "number") {
            reader.read();
            cur_number = reader.get_value();
            reader.read();
        }
        if (reader.get_name() == "nearest_subway_station") {
            reader.read();
            cur_metro_station = reader.get_value();
            reader.read();
        }
    }

    for (auto metro : district_city) {
        std::cout << "Metro station: " << metro.first << std::endl;
        for (int i = 0; i < metro.second.size(); i++) {
            parking p = metro.second[i];
            std::cout << "Parking №" << p.number << " Count of parking spaces: " << p.parking_space << std::endl;
        }
    }

    return 0;
}
