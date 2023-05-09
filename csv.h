#pragma once

#include<sstream>
#include<vector>
#include<string>

using namespace std;


namespace csv
{
    typedef vector<vector<string>> csv_t;

    //parsing text into csv 
    csv_t parse(string data) {
        vector<vector<string>> result;
        vector<string> row;
        string cell;
        bool in_quotes = false;
        for (char c : data) {
            if (c == '"') {
                in_quotes = !in_quotes;
            }
            else if (c == ',' && !in_quotes) {
                row.push_back(cell);
                cell.clear();
            }
            else if (c == '\n' && !in_quotes) {
                row.push_back(cell);
                result.push_back(row);
                row.clear();
                cell.clear();
            }
            else {
                cell += c;
            }
        }
        if (!cell.empty()) {
            row.push_back(cell);
            result.push_back(row);
        }
        return result;
    }
    //converting csv to text
    string convert(csv_t data) {
        string result;
        for (auto& row : data) {
            for (auto& cell : row) {
                bool need_quotes = false;
                for (char c : cell) {
                    if (c == '"' || c == ',' || c == '\n') {
                        need_quotes = true;
                        break;
                    }
                }
                if (need_quotes) {
                    result += '"';
                    for (char c : cell) {
                        if (c == '"') {
                            result += '"';
                        }
                        result += c;
                    }
                    result += '"';
                }
                else {
                    result += cell;
                }
                result += ',';
            }
            result.back() = '\n';
        }
        return result;
    }
}