#include <iostream>
#include "../utils.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

vector<long long> toSourceDestinationRange(string line) {
    vector<string> srcDestStr = splitString(line, ' ');
    vector<long long> res;
    transform(srcDestStr.begin(), srcDestStr.end(), std::back_inserter(res),
              [](string& str) { return stoll(str); });
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
    unordered_map<long long, long long> seedSoilMap;
    unordered_map<long long, long long> soilFertilizerMap;
    unordered_map<long long, long long> fertilizerWaterMap;
    unordered_map<long long, long long> waterLightMap;
    unordered_map<long long, long long> lightTemperatureMap;
    unordered_map<long long, long long> temperatureHumidityMap;
    unordered_map<long long, long long> humidityLocationMap;
    // 7 bc seeds: + space is 7 characters
    vector<string> seedsStr = splitString(
        (lines[0].substr(7, lines[0].length())), ' ');
    vector<int> seeds;
    transform(seedsStr.begin(), seedsStr.end(), std::back_inserter(seeds),
                  [](string& str) { return stoll(str); });
    for (int i = 1; i < lines.size(); i++) {
        if (lines[i] == seedToSoilMapStr) {
            cout << "Processing seed soil map" << endl;
            while (lines[i+1] != "") {
                // process to seed soil map
                vector<long long> srcDestRange = toSourceDestinationRange(lines[i + 1]);
                for (long long j = 0; j < srcDestRange[2]; j++) {
                    seedSoilMap[srcDestRange[1] + j] = srcDestRange[0] + j; 
                }

                // cout << "current line is " << lines[i + 1] << endl;
                // cout << "seedSoil map is " << seedSoilMap << endl;
                i++;
            }

        } else if (lines[i] == soilToFertilizerStr) {
            cout << "Processing soil fertilizier map" << endl;
            while (lines[i + 1] != "") {
                // process to seed soil map
                vector<long long> srcDestRange = toSourceDestinationRange(lines[i + 1]);
                // cout << "current line is " << lines[i + 1] << endl;
                for (long long j = 0; j < srcDestRange[2]; j++) {
                    soilFertilizerMap[srcDestRange[1] + j] =
                        srcDestRange[0] + j;
                }
                i++;
            }

        } else if (lines[i] == fertilizerToWaterStr) {
                cout << "Processing fertilizier water map" << endl;
            while (lines[i + 1] != "") {
                // cout << "current line is " << lines[i + 1] << endl;
                vector<long long> srcDestRange = toSourceDestinationRange(lines[i + 1]);
                for (long long j = 0; j < srcDestRange[2]; j++) {
                    fertilizerWaterMap[srcDestRange[1] + j] =
                        srcDestRange[0] + j;
                }
                i++;
            }

        } else if (lines[i] == waterToLightStr) {
                cout << "Processing water light map" << endl;
            while (lines[i + 1] != "") {
                // cout << "current line is " << lines[i + 1] << endl;
                vector<long long> srcDestRange = toSourceDestinationRange(lines[i + 1]);
                for (long long j = 0; j < srcDestRange[2]; j++) {
                    waterLightMap[srcDestRange[1] + j] =
                        srcDestRange[0] + j;
                }
                i++;
            }

        } else if (lines[i] == lightToTemperatureStr) {
                cout << "Processing light temperature map" << endl;
            while (lines[i + 1] != "") {
                // cout << "current line is " << lines[i + 1] << endl;
                vector<long long> srcDestRange = toSourceDestinationRange(lines[i + 1]);
                for (long long j = 0; j < srcDestRange[2]; j++) {
                    lightTemperatureMap[srcDestRange[1] + j] = srcDestRange[0] + j;
                }
                i++;
            }

        } else if (lines[i] == temperatureToHumidityStr) {
                cout << "Processing temperature humidify map" << endl;
            while (lines[i + 1] != "") {
                // process to seed soil map
                vector<long long> srcDestRange = toSourceDestinationRange(lines[i + 1]);
                // cout << "current line is " << lines[i + 1] << endl;
                for (long long j = 0; j < srcDestRange[2]; j++) {
                    temperatureHumidityMap[srcDestRange[1] + j] =
                        srcDestRange[0] + j;
                }
                i++;
            }

        } else if (lines[i] == humidityToLocationStr) {
                cout << "Processing humidify location map" << endl;
            while (lines[i + 1] != "") {
                // process to seed soil map
                // cout << "current line is " << lines[i + 1] << endl;
                vector<long long> srcDestRange = toSourceDestinationRange(lines[i + 1]);
                for (long long j = 0; j < srcDestRange[2]; j++) {
                    humidityLocationMap[srcDestRange[1] + j] =
                        srcDestRange[0] + j;
                }
                i++;
            }
        }
    }
    long long res = LLONG_MAX;

    for (auto seed : seeds) {
        cout << "seed is " << seed << endl;
        long long soil = seedSoilMap[seed];
        if (soil == 0) {
            soil = seed;
        }
        long long fertilizer = soilFertilizerMap[soil];
        if (fertilizer == 0) {
            fertilizer = soil;
        }
        long long water = fertilizerWaterMap[fertilizer];
        if (water == 0) {
            water = fertilizer;
        }
        long long light = waterLightMap[water];
        if (light ==0) {
            light = water;
        }
        long long temp = lightTemperatureMap[light];
        if (temp == 0) {
            temp = light;
        }
        long long humidity = temperatureHumidityMap[temp];
        if (humidity == 0) {
            humidity = temp;
        }
        long long location = humidityLocationMap[humidity];
        if (location == 0) {
            location = humidity;
        }
        // cout << "location is " << location << endl;
        res = min(res, location);
    }
    cout << "min location is " << res << endl;
    return 0;
}