#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include "KVparser.h"


KVparser::KVparser(const std::string& filename)
: filename(filename) {
    fs.open(filename, std::fstream::in);
}

void KVparser::open_file(const std::string& filename) {
    this->filename = filename;
    if (fs.is_open())
        fs.close();
    this->fs.open(filename, std::fstream::in);
}

bool KVparser::is_open() {
    return fs.is_open();
}

void KVparser::parse_contents() {
    _check_empty_filename();
    _check_file_is_open();
    std::string line;
    while (fs >> line){
        _remove_indents(line);
        _remove_trailing_whitespaces(line);
        std::string key = _process_key(line);
        std::string value = _process_value(line);
        values.insert_or_assign(key, value);
    }
}

std::string KVparser::get_value(const std::string& key) {
    return values.at(key);
}

void KVparser::_check_empty_filename() {
    if (this->filename.empty()) {
        std::stringstream err;
        err << "Cannot parse. Need to open file first";
        throw std::runtime_error(err.str());
    }
}

void KVparser::_check_file_is_open() {
    if (!is_open()) {
        std::stringstream err;
        err << "Cannot parse. File " << this->filename << " is not open";
        throw std::runtime_error(err.str());
    }
}

void KVparser::set_delim(const std::string& delim) {
    this->delim = delim;
}

void KVparser::set_value_quoted(bool val) {
    value_quoted = val;
}

void KVparser::set_key_quoted(bool val) {
    key_quoted = val;
}

std::string KVparser::_process_key(std::string &line) {
    std::string key = line.substr(0, line.find(delim));
    if (key_quoted) {
        key.erase(0,1);
        key.erase(key.size()-1, 1);
    }
    return key;
}

std::string KVparser::_process_value(std::string &line) {
    std::string value = line.substr(line.find(delim)+1, line.size());
    if (value_quoted) {
        value.erase(0,1);
        value.erase(value.size()-1, 1);
    }
    return value;
}

KVparser::~KVparser() {
    fs.close();
}

void KVparser::debug_print() {
    std::cout << "Filename: " << filename << "\n";
    std::cout << "Status: " << (is_open() ? "is open" : "not open") << "\n";
    std::cout << "Delimiter: " << delim << "\n";
    std::cout << (key_quoted ? "keys quoted" : "keys unquoted") << "\n";
    std::cout << (value_quoted ? "values quoted" : "values unquoted") << "\n";
    for (auto i : values) {
        std::cout << i.first << " = " << i.second << "\n";
    }
}

void KVparser::_remove_indents(std::string& line) {
    while(line.front() == ' ')
        line.erase(0, 1);
}

void KVparser::_remove_trailing_whitespaces(std::string& line) {
    while(line.back() == ' ')
        line.erase(line.size()-1, 1);
}
