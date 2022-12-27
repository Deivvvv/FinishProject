#include "InvertedIndex.h"

#include <mutex>
std::mutex _look;
void InvertedIndex::SetPath(const std::string &_path)
{
    path = _path;
}

std::vector<std::string> InvertedIndex::split(std::string str, const std::string &token) const
{
    std::vector<std::string>result;
    while(str.size())
    {
        int index = str.find(token);
        if(index != std::string::npos)
        {
            result.push_back(str.substr(0,index));
            str = str.substr(index + token.size());
            if(str.size() == 0)
                result.push_back(str);
        }
        else
        {
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

void InvertedIndex::UpdateDocumentBaseThread(int a, const std::string &str)
{

    std::vector<std::string> textList = split(str, " ");
    for(int j = 0; j < textList.size(); j++)
    {
        auto search = freq_dictionary.find(textList[j]);
        if(search != freq_dictionary.end()){
            bool add =false;
            for(int k = 0; k < search->second.size() && !add; k++)
            {
                if(search->second[k].doc_id == a)
                {
                    add =true;
                    _look.lock();
                    search->second[k].count++;
                    _look.unlock();
                }
            }
            if(!add)
            {
                Entry wordCase = Entry();
                wordCase.doc_id = a;
                _look.lock();
                search->second.push_back(wordCase);
                _look.unlock();
            }
        }
        else
        {
            Entry wordCase = Entry();
            wordCase.doc_id = a;
            _look.lock();
            freq_dictionary[textList[j]].push_back(wordCase);
            _look.unlock();
        }
    }
}


void InvertedIndex::UpdateDocumentBase(const std::vector<std::string> &input_docs)
{
    std::vector<std::string> new_docs;
    for(int i = 0; i < input_docs.size(); i++)
    {
        bool add = false;
        for(int j = 0; j < docs.size() && !add; j++)
            add = (input_docs[i] == docs[j]);

        if(!add)
        {
            new_docs.push_back(input_docs[i]);
        }
    }


    std::vector<std::thread> threadList;
    for(int i = 0; i < new_docs.size(); i++)
    {
        int a = docs.size();
        threadList.emplace_back(&InvertedIndex::UpdateDocumentBaseThread, this,a ,new_docs[i]);
        docs.push_back(new_docs[i]);
    }

    for(int i =0;i<threadList.size();i++)
        threadList[i].join();

    docsSize = docs.size();
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) const
{
    auto search = freq_dictionary.find(word);
    if(search != freq_dictionary.end()){
        return search->second;
    }
    return std::vector<Entry>();

}