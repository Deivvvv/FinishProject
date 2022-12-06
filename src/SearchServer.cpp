#include "SearchServer.h"



std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input){
    std::vector<std::vector<RelativeIndex>> result = std::vector<std::vector<RelativeIndex>>(queries_input.size());


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
            ConverterJSON conv = ConverterJSON();
            conv.SetPath(_index.path);
            int c = conv.GetResponsesLimit();
            c = (resultCase.size()>c)? c:resultCase.size();
            for(int k=0;k<c;k++){
                resultCase[k].rank /=resultMax;
            }
        }
        result[i] = resultCase;

    }
    return result;
};