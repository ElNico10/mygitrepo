#include "Command.hpp"
#include <sstream>

Command::Command() : name(""), description(""), points(0) {}

Command::Command(const std::string& name, const std::string& description, int points)
    : name(name), description(description), points(points) {}

std::string Command::getName() const { return name; }
std::string Command::getDescription() const { return description; }
int Command::getPoints() const { return points; }

void Command::setName(const std::string& name) { this->name = name; }
void Command::setDescription(const std::string& description) { this->description = description; }
void Command::setPoints(int points) { this->points = points; }

bool Command::operator==(const Command& other) const {
    return name == other.name;
}

std::string Command::toString() const {
    std::stringstream ss;
    ss << name << ",\"" << description << "\"," << points;
    return ss.str();
}