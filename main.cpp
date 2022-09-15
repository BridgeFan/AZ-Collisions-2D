#include <iostream>
#include "Point.h"
#include <fstream>
#include <vector>
#include <sstream>
#include "Algorithms.h"
#include <chrono>

std::vector< std::vector<Point>> handle_input(char* file_name);
std::vector<std::string> split(const std::string& s, char delim);
std::vector<Point> parse_input_polygon(const std::string& input_polygon, unsigned char polygon_number);
void print_polygons(const std::vector< std::vector<Point>>& polygons);
void save_output(bool result, const char* output_name);

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "Not enough argumetns!" << std::endl;
        return -1;
    }
    std::vector< std::vector<Point>> polygons = handle_input(argv[1]);
    print_polygons(polygons);
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    auto edges1 = toEdges(polygons[0]);
    auto edges2 = toEdges(polygons[1]);

    bool algorithm_result = arePolygonsIntersecting(polygons[0], polygons[1], false) ||
            arePolygonsIntersecting(polygons[0], polygons[1], true) ||
            horizontal_vertical_intersection(edges1, edges2);
    //algorithm_result = ... algorithm function
    end = std::chrono::system_clock::now();
    auto elapsed_micro = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time: " << elapsed_micro.count()/1000.0l << "ms\n";
    const char* output_name = argc > 2 ? argv[2] : "test_outputs.txt";
    
    save_output(algorithm_result, output_name);
    return 0;
}

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

std::vector< std::vector<Point>> handle_input(char* file_name) {
    std::vector< std::vector<Point>> result_polygons;
    try
    {
        std::ifstream input_file(file_name);
        std::string first_polygon_str;
        std::string second_polygon_str;
        if (input_file.is_open()) {
            //load 2 lines with points coordinates from file
            input_file >> first_polygon_str;
            input_file >> second_polygon_str;
        }
        std::vector<Point> first_polygon = parse_input_polygon(first_polygon_str, 1);
        std::vector<Point> second_polygon = parse_input_polygon(second_polygon_str, 2);

        result_polygons.push_back(first_polygon);
        result_polygons.push_back(second_polygon);

        input_file.close();
    }
    catch(const std::ifstream::failure& e)
    {
        std::cerr << e.what() << '\n';
    }
    return result_polygons;
}

std::vector<Point> parse_input_polygon(const std::string& input_polygon, unsigned char polygon_number) {
    char delim_points = ';';
    char delim_coordinates = ',';
    //split input string ie. "0.0,0.0;0.0,2.0;4.0,2.0;4.0,0.0" to ["0.0,0.0", "0.0,2.0", "4.0,2.0", "4.0,0.0"]
    std::vector<std::string> polygon_points = split(input_polygon, delim_points);
    std::vector<Point> output_polygon_points;

    for (const auto& point_str : polygon_points) {
        //split input string ie. "0.0,0.0" to ["0.0", "0.0"]
        std::vector<std::string> point_coordinates = split(point_str, delim_coordinates);
        double x = std::stod(point_coordinates[0]);
        double y = std::stod(point_coordinates[1]);

        Point next_point = { x, y, polygon_number };
        output_polygon_points.push_back(next_point);
    }

    return output_polygon_points;
}

void print_polygons(const std::vector< std::vector<Point>>& polygons) {
    for (auto polygon : polygons) {
        for (auto point : polygon) {
            std::cout << "Point in polygon " << (short)point.polygon << ": [" << point.x << "," << point.y << "]" << std::endl;
        }
    }
}

void save_output(bool result, const char* output_name) {
    try
    {
        std::ofstream myfile;
        std::string result_value = result ? "TRUE" : "FALSE";
        myfile.open(output_name, std::fstream::out);
        myfile << result_value;
        myfile.close();
    }
    catch (const std::ifstream::failure& e)
    {
        std::cout << "ERROR during result saving" << std::endl;
    }
    
}