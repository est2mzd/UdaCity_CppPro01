#include <optional>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <io2d.h>
#include "route_model.h"
#include "render.h"
#include "route_planner.h"

#include "my_utility.h"
using std::cout;
using std::cin;
using std::string;
using std::vector;

using namespace std::experimental;

static std::optional<std::vector<std::byte>> ReadFile(const std::string &path)
{   
    // read binary, ate = at the end -> read fron TOP to END
    std::ifstream is{path, std::ios::binary | std::ios::ate};
    if( !is )
        return std::nullopt;
    
    // get the size of input stream , create "contens"
    auto size = is.tellg();
    std::vector<std::byte> contents(size);    
    
    // seek the start position , and read all of the stream
    is.seekg(0);
    is.read((char*)contents.data(), size);

    if( contents.empty() )
        return std::nullopt;
    
    // return contents, move pointer 
    return std::move(contents);
}

int main(int argc, const char **argv)
{    
    std::string osm_data_file = "";
    if( argc > 1 ) {
        for( int i = 1; i < argc; ++i )
            // "-f" -> user can define OSM file to use
            if( std::string_view{argv[i]} == "-f" && ++i < argc )
                osm_data_file = argv[i];
    }
    else {
        // if user do not define file, "../mpa.osm" will be used.
        std::cout << "To specify a map file use the following format: " << std::endl;
        std::cout << "Usage: [executable] [-f filename.osm]" << std::endl;
        osm_data_file = "../map.osm";
    }
    
    // define vector
    std::vector<std::byte> osm_data;

    // read osm file data into "data". type of "data" is std::vector<std::byte>
    if( osm_data.empty() && !osm_data_file.empty() ) {
        std::cout << "Reading OpenStreetMap data from the following file: " <<  osm_data_file << std::endl;
        auto data = ReadFile(osm_data_file);
        if( !data )
            std::cout << "Failed to read." << std::endl;
        else
            osm_data = std::move(*data);
    }
    
    // TODO 1: Declare floats `start_x`, `start_y`, `end_x`, and `end_y` and get
    // user input for these values using std::cin. Pass the user input to the
    // RoutePlanner object below in place of 10, 10, 90, 90.
    float start_x, start_y, end_x, end_y;
    string input_str;
    cout << "input 4 values separated by comma." << "\n";
    cout << "start_x, start_y, end_x, end_y" << "\n";
    cin >> input_str;
    vector<string> input_str_list = split(input_str, ',');
    
    // check input -1
    if (input_str.empty()){
        cout << "you input no value. this program is stopped!" << "\n";
        return 1;
    }

    // check input -2
    if (input_str_list.size()!=4){
        cout << "you must input 4 values. this program is stopped" << "\n";
        return 1;  
    }
    
    // input values
    start_x = std::stof(input_str_list[0]);
    start_y = std::stof(input_str_list[1]);
    end_x   = std::stof(input_str_list[2]);
    end_y   = std::stof(input_str_list[3]);

    // Build Model.
    RouteModel model{osm_data};

    // Create RoutePlanner object and perform A* search.
    //RoutePlanner route_planner{model, 10, 10, 90, 90};
    RoutePlanner route_planner{model, start_x, start_y, end_x, end_y};
    route_planner.AStarSearch();

    std::cout << "Distance: " << route_planner.GetDistance() << " meters. \n";

    // Render results of search.
    Render render{model};

    auto display = io2d::output_surface{400, 400, io2d::format::argb32, io2d::scaling::none, io2d::refresh_style::fixed, 30};
    display.size_change_callback([](io2d::output_surface& surface){
        surface.dimensions(surface.display_dimensions());
    });
    display.draw_callback([&](io2d::output_surface& surface){
        render.Display(surface);
    });
    display.begin_show();
}
