#pragma once

#include "ConverterJSON.h"
#include <vector>
#include <map>
#include <string>
#include <thread>

struct Entry
{
    size_t doc_id, count =1;
    // Данный оператор необходим для проведения тестовых сценариев
    bool operator ==(const Entry& other) const
    {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};

class InvertedIndex
{
public:
    InvertedIndex() = default;

    void SetPath(const std::string &_path);

    std::vector<std::string> split(std::string str, const std::string &token) const;

    void UpdateDocumentBaseThread( int a, const std::string &str);
    void UpdateDocumentBase(const std::vector<std::string> &input_docs);

    std::vector<Entry> GetWordCount(const std::string& word) const;

    int docsSize;
    std::string path;

private:
    std::vector<std::string> docs; // список содержимого документов
    std::map<std::string, std::vector<Entry>> freq_dictionary; // частотный словарь
};
