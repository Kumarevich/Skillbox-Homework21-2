#include <iostream>
#include <fstream>
#include <vector>

enum room_type {
    BEDROOM,
    KITCHEN,
    BATHROOM,
    NURSERY,
    LIVING_ROOM,
    INDEFINITE_ROOM
};

enum building_type {
    HOUSE,
    GARAGE,
    BARN,
    BATHS,
    INDEFINITE
};

struct room {
    room_type type;
    int square = 0;
};

struct current_floor {
    int height;
    int rooms_num = 1;
    std::vector<room> rooms;
};

struct building {
    building_type type;
    int square;
    bool heater;
    int floors_number = 1;
    std::vector<current_floor> floors;
};

struct area {
    int number;
    int square;
    int buildings_number;
    std::vector<building> buildings;
};

building_type build_type_func (const std::string& type) {
    if (type == "house") return HOUSE;
    else if (type == "garage") return GARAGE;
    else if (type == "barn") return BARN;
    else if (type == "baths") return BATHS;
    else return INDEFINITE;
}

room_type room_type_func (const std::string& room_type) {
    if (room_type == "bedroom") return BEDROOM;
    else if (room_type == "kitchen") return KITCHEN;
    else if (room_type == "bathroom") return BATHROOM;
    else if (room_type == "nursery") return NURSERY;
    else if (room_type == "livingroom") return LIVING_ROOM;
    else return INDEFINITE_ROOM;
}

void room_create (room& room_temp, int k) {
    std::cout << "Input the " << k + 1 << " room type: ";
    std::string room_type_temp;
    std::cin >> room_type_temp;
    room_temp.type = room_type_func(room_type_temp);
    std::cout << "Input the room square: ";
    std::cin >> room_temp.square;
}

void floor_create (current_floor& floor_temp, int j) {
    std::cout << "Input the floor #" << j + 1 << " height: ";
    std::cin >> floor_temp.height;
    std::cout << "Input the number of rooms: ";
    std::cin >> floor_temp.rooms_num;
    for (int k = 0; k < floor_temp.rooms_num; ++k) {
        room room_temp;
        room_create(room_temp, k);
        floor_temp.rooms.push_back(room_temp);
    }
}

void building_create (building& building_temp, int i) {
    std::cout << "Input the " << i+1 << " building square: ";
    std::cin >> building_temp.square;
    std::cout << "Input the " << i+1 << " building type: ";
    std::string build_type_temp;
    std::cin >> build_type_temp;
    building_temp.type = build_type_func(build_type_temp);
    if (building_temp.type == HOUSE || building_temp.type == BATHS) {
        std::cout << "Is there heater (1 - YES/0 - NO): ";
        std::cin >> building_temp.heater;
        if (building_temp.type == HOUSE) {
            std::cout << "Input the number of floors in this house: ";
            std::cin >> building_temp.floors_number;
            for (int j = 0; j < building_temp.floors_number; ++j) {
                current_floor floor_temp;
                floor_create(floor_temp, j);
                building_temp.floors.push_back(floor_temp);
            }
        }
    }
}

void area_create (area& area_temp) {
    std::cout << "Input the area number: ";
    std::cin >> area_temp.number;
    area_temp.square = 1000;
    std::cout << "Input number of buildings: ";
    std::cin >> area_temp.buildings_number;
    for (int i = 0; i < area_temp.buildings_number; ++i) {
        building building_temp;
        building_create(building_temp, i);
        area_temp.buildings.push_back(building_temp);
    }
}

std::string type_for_building(building_type type) {
    if (type == HOUSE) return "house";
    else if (type == GARAGE) return "garage";
    else if (type == BARN) return "barn";
    else if (type == BATHS) return "baths";
    else return "INDEFINITE";
}

std::string type_for_room(room_type type) {
    if (type == BEDROOM) return "bedroom";
    else if (type == KITCHEN) return "kitchen";
    else if (type == BATHROOM) return "bathroom";
    else if (type == LIVING_ROOM) return "livingroom";
    else if (type == NURSERY) return "nursery";
    else return "INDEFINITE ROOM";
}

void write_to_file (std::vector<area>& town, int count) {
    std::ofstream my_town("..\\town.txt", std::ios::app);
    for (int i = 0; i < count; ++i) {
        my_town << "Area N: " << town[i].number << "; square: " << town[i].square << "; number of buildings: " << town[i].buildings_number << std::endl;
        for (int j = 0; j < town[i].buildings_number; ++j) {
            my_town << "Building " << j + 1 << " is " << type_for_building(town[i].buildings[j].type) << "; square: "
                    << town[i].buildings[j].square << std::endl;
            if (town[i].buildings[j].type == HOUSE) {
                my_town << "Number of floors: " << town[i].buildings[j].floors_number << std::endl;
                for (int k = 0; k < town[i].buildings[j].floors_number; ++k) {
                    my_town << "Floor " << k + 1 << " height: " << town[i].buildings[j].floors[k].height
                            << "; number of rooms: " << town[i].buildings[j].floors[k].rooms_num << std::endl;
                    for (int l = 0; l < town[i].buildings[j].floors[k].rooms_num; ++l) {
                        my_town << "Room " << l + 1 << " type: "
                                << type_for_room(town[i].buildings[j].floors[k].rooms[l].type) << "; square: "
                                << town[i].buildings[j].floors[k].rooms[l].square << std::endl;
                    }
                }
            }
        }
    }
    my_town.close();
}

int main() {
    std::cout << "Start the town filling." << std::endl;
    bool filling = true;
    int count = 0;
    std::vector<area> town;
    while (filling) {
        area area_temp;
        area_create(area_temp);
        town.push_back(area_temp);
        ++count;
        std::cout << "One more area? (yes - 1/no - 0): ";
        std::cin >> filling;
    }
    write_to_file(town, count);
    return 0;
}
