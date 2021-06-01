#ifndef KVPARSER_H
#define KVPARSER_H

#include <string>
#include <map>
#include <fstream>

class KVparser {
private:
    std::string filename;
    std::string delim{"="};
    bool key_quoted{false};
    bool value_quoted{false};
    std::fstream fs;
    std::map<std::string, std::string> values{};
public:
    KVparser() = delete;
    KVparser(KVparser&) = delete;
    KVparser(KVparser&&) = delete;
    KVparser operator= (KVparser) = delete;
    KVparser operator= (KVparser&) = delete;
    KVparser operator= (KVparser&&) = delete;

    KVparser(const std::string& filename);
    ~KVparser();
    void open_file(const std::string& filename);
    bool is_open();
    void set_delim(const std::string& delim);
    void set_value_quoted(bool);
    void set_key_quoted(bool);
    void parse_contents();
    std::string get_value(const std::string& key);
    void debug_print();

private:
    void _check_empty_filename();
    void _check_file_is_open();
    void _remove_indents(std::string& line);
    void _remove_trailing_whitespaces(std::string& line);
    std::string _process_key(std::string& line);
    std::string _process_value(std::string& line);
};

#endif
