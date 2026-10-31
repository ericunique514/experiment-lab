#include "csv_reader.hpp"

#include <fstream> //file stream: file -> program
#include <iostream>


// =======================================================================

// receives a filename and returns a vector of user records
std::vector<UserRecord> loadUsersFromCsv(
    const std::string& filename)
{
    std::ifstream file {filename};

    if (!file)
    {
        std::cerr
            << "Could not open file: "
            << filename
            << '\n';

        return {};
    }

    std::vector<UserRecord> userInfoList;

    std::string line;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::vector<std::string> fields {
            splitCsvLine(line)
        };

        if (fields.size() != 5)
        {
            std::cerr
                << "Skipping invalid user row.\n";

            continue;
        }

        UserRecord userInfo;

        userInfo.userId = std::stoi(fields[0]);
        userInfo.device = fields[1];
        userInfo.variant = fields[2];
        userInfo.purchased = std::stoi(fields[3]);
        userInfo.orderPrice = std::stod(fields[4]);


        userInfoList.push_back(userInfo);
    }

    return userInfoList;
}
// =====================================================================

std::vector<std::string> splitCsvLine(
    const std::string& line)
{
    std::vector<std::string> fields;

    std::string field;
    bool insideQuotes {false};

    for (std::size_t i = 0; i < line.size(); ++i)
    {
        const char character {line[i]};

        if (character == '"')
        {
            // "" inside a quoted CSV field means one literal "
            if (insideQuotes &&
                i + 1 < line.size() &&
                line[i + 1] == '"')
            {
                field += '"';
                ++i;
            }
            else
            {
                insideQuotes = !insideQuotes;
            }
        }
        else if (character == ',' && !insideQuotes)
        {
            fields.push_back(field);
            field.clear();
        }
        else
        {
            field += character;
        }
    }

    // Remove Windows-style carriage return if present
    if (!field.empty() && field.back() == '\r')
    {
        field.pop_back();
    }

    fields.push_back(field);

    return fields;
}

/*
std::optional<double> parseOptionalDouble(
    const std::string& text)
{
    if (text.empty() ||
        text == "N/A" ||
        text == "Please Contact")
    {
        return std::nullopt;
    }

    std::string number;

    bool started {false};
    bool decimalSeen {false};

    for (char character : text)
    {
        if (std::isdigit(
                static_cast<unsigned char>(character)))
        {
            number += character;
            started = true;
        }
        else if (character == ',' && started)
        {
            // Ignore thousands separator: 1,850 → 1850
            continue;
        }
        else if (character == '.' &&
                 started &&
                 !decimalSeen)
        {
            number += character;
            decimalSeen = true;
        }
        else if (started)
        {
            // Stop after first complete number
            break;
        }
    }

    if (number.empty())
    {
        return std::nullopt;
    }

    try
    {
        return std::stod(number);
    }
    catch (...)
    {
        return std::nullopt;
    }
}

std::optional<int> parseOptionalInt(
    const std::string& text)
{
    const std::optional<double> number {
        parseOptionalDouble(text)
    };

    if (!number.has_value())
    {
        return std::nullopt;
    }

    return static_cast<int>(*number);
}
*/