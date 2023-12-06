#include <iostream>
#include "../utils.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<int> toSourceDestinationRange(string line) {
    vector<string> srcDestStr = splitString(line, ' ');
    vector<int> res;
    transform(srcDestStr.begin(), srcDestStr.end(), std::back_inserter(res),
              [](string& str) { return stoi(str); });
    return res;
}
int main() {
    vector<string> lines = readLines("input.txt");
    string seedToSoilMapStr = "seed-to-soil map:";
    string soilToFertilizerStr = "soil-to-fertilizer map:";
    string fertilizerToWaterStr = "fertilizer-to-water map:";
    string waterToLightStr = "water-to-light map:";
    string lightToTemperatureStr = "light-to-temperature map:";
    string temperatureToHumidityStr = "temperature-to-humidity map:";
    string humidityToLocationStr = "humidity-to-location map:";
    unordered_map<int, int> seedSoilMap;
    unordered_map<int, int> soilFertilizerMap;
    unordered_map<int, int> fertilizerWaterMap;
    unordered_map<int, int> waterLightMap;
    unordered_map<int, int> lightTemperatureMap;
    unordered_map<int, int> temperatureHumidityMap;
    unordered_map<int, int> humidityLocationMap;
    // 7 bc seeds: + space is 7 characters
    vector<string> seedsStr = splitString(
        (lines[0].substr(7, lines[0].length())), ' ');
    vector<int> seeds;
    transform(seedsStr.begin(), seedsStr.end(), std::back_inserter(seeds),
                  [](string& str) { return stoi(str); });
    for (int i = 1; i < lines.size(); i++) {
        if (lines[i] == seedToSoilMapStr) {
            cout << "Processing seed soil map" << endl;
            while (lines[i+1] != "") {
                // process to seed soil map
                vector<int> srcDestRange = toSourceDestinationRange(lines[i + 1]);
   
                cout << "current line is " << lines[i + 1] << endl;
                i++;
            }

        } else if (lines[i] == soilToFertilizerStr) {
                cout << "Processing soil fertilizier map" << endl;
            while (lines[i + 1] != "") {
                // process to seed soil map
                vector<int> srcDestRange = toSourceDestinationRange(lines[i + 1]);
                cout << "current line is " << lines[i + 1] << endl;
                i++;
            }

        } else if (lines[i] == fertilizerToWaterStr) {
                cout << "Processing fertilizier water map" << endl;
            while (lines[i + 1] != "") {
                cout << "current line is " << lines[i + 1] << endl;
                vector<int> srcDestRange = toSourceDestinationRange(lines[i + 1]);
                i++;
            }

        } else if (lines[i] == waterToLightStr) {
                cout << "Processing water light map" << endl;
            while (lines[i + 1] != "") {
                cout << "current line is " << lines[i + 1] << endl;
                vector<int> srcDestRange = toSourceDestinationRange(lines[i + 1]);
                i++;
            }

        } else if (lines[i] == lightToTemperatureStr) {
                cout << "Processing light temperature map" << endl;
            while (lines[i + 1] != "") {
                cout << "current line is " << lines[i + 1] << endl;
                vector<int> srcDestRange = toSourceDestinationRange(lines[i + 1]);
                i++;
            }

        } else if (lines[i] == temperatureToHumidityStr) {
                cout << "Processing temperature humidify map" << endl;
            while (lines[i + 1] != "") {
                // process to seed soil map
                vector<int> srcDestRange = toSourceDestinationRange(lines[i + 1]);
                cout << "current line is " << lines[i + 1] << endl;
                i++;
            }

        } else if (lines[i] == humidityToLocationStr) {
                cout << "Processing humidify location map" << endl;
            while (lines[i + 1] != "") {
                // process to seed soil map
                cout << "current line is " << lines[i + 1] << endl;
                vector<int> srcDestRange = toSourceDestinationRange(lines[i + 1]);
                i++;
            }
        }
    }
    int res = INT_MAX;

    for (auto seed : seeds) {
        int soil = seedSoilMap[seed];
        int fertilizer = soilFertilizerMap[soil];
        int water = fertilizerWaterMap[fertilizer];
        int light = waterLightMap[water];
        int temp = lightTemperatureMap[light];
        int humidity = temperatureHumidityMap[temp];
        int location = humidityLocationMap[humidity];
        res = min(res, location);
    }
    cout << "min location is " << res << endl;
    return 0;
}