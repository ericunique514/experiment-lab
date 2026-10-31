#pragma once

#include <string>
#include <vector>
//#include <optional>

#include "experiment.hpp"

std::vector<UserRecord> loadUsersFromCsv(
    const std::string& filename);

std::vector<std::string> splitCsvLine(
    const std::string& line);

/*
std::optional<double> parseOptionalDouble(
    const std::string& text);

std::optional<int> parseOptionalInt(
    const std::string& text);
*/