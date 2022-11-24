#pragma once

#include "InvertedIndex.h"

struct RelativeIndex{
    size_t doc_id;
    float rank;
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};
class SearchServer {
public:
    /**
* @param idx в конструктор класса передаётся ссылка на класс
InvertedIndex,
* чтобы SearchServer мог узнать частоту слов встречаемых в
запросе
*/
    SearchServer(InvertedIndex& idx) : _index(idx){ };
    /**
* Метод обработки поисковых запросов
* @param queries_input поисковые запросы взятые из файла
requests.json
* @return возвращает отсортированный список релевантных ответов для
заданных запросов
*/

    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input){
        std::vector<std::vector<RelativeIndex>> result = std::vector<std::vector<RelativeIndex>>(queries_input.size());

        //ConverterJSON conv = ConverterJSON(_index.path);

        for(int i=0;i< queries_input.size();i++){
            std::vector<RelativeIndex> resultCase =std::vector<RelativeIndex>();
            std::vector<std::string> words = _index.split(queries_input[i], " ");
            for(int j =0; j< words.size();j++){
                std::vector<Entry> entry =_index.GetWordCount(words[j]);

                for(int l=0; l< _index.docsSize;l++)
                    for(int k=0;k<entry.size();k++){
                        if(entry[k].doc_id == l){
                            bool  uses = false;
                            for(int h=0;h<resultCase.size();h++)
                                if(resultCase[h].doc_id == l)
                                {
                                    resultCase[h].rank+= entry[k].count;
                                    uses = true;
                                    break;
                                }
                            if(uses)
                                break;

                            RelativeIndex  index = RelativeIndex();
                            index.doc_id = l;
                            index.rank = entry[k].count;
                            resultCase.push_back(index);
                           // std::cout << index.doc_id<< std::endl;
                            //std::cout << resultCase[resultCase.size()-1].doc_id << std::endl;
                            break;
                        }
                    }
            }
            float resultMax=0;
            for(int j=0;j<resultCase.size();j++)
                for(int k=j;k<resultCase.size();k++)
                    if(resultCase[j].rank < resultCase[k].rank){
                        RelativeIndex a =resultCase[k];
                        resultCase[k]=resultCase[j];
                        resultCase[j] = a;
                    }
            if(resultCase.size()>0)
                resultMax = resultCase[0].rank;

            if(resultMax ==0)
                resultCase = std::vector<RelativeIndex>();
            else
            {
                ConverterJSON conv = ConverterJSON(_index.path);
                int c = conv.GetResponsesLimit();
                c = (resultCase.size()>c)? c:resultCase.size();
                for(int k=0;k<c;k++){
                    /*
                int b=k;
                for(int j=k;j<resultCase.size();j++)
                    if(resultCase[b].rank < resultCase[j].rank)
                        b=j;
                float g =resultCase[k].rank;
                resultCase[k].rank = resultCase[b].rank;
                resultCase[b].rank=g;
*/
                    resultCase[k].rank /=resultMax;
                }
            }
            result[i] = resultCase;

        }
        return result;
    };
private:
    InvertedIndex _index;
};


