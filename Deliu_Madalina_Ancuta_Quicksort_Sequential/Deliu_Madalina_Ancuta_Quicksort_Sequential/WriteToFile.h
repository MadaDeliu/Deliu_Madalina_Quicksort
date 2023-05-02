#ifndef WRITE_TO_FILE_H
#define WRITE_TO_FILE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

void writeInputToFile(const std::string& file_name, const std::vector<int>& arr);
void writeOutputToFile(const std::string& file_name, const std::vector<int>& arr);

#endif