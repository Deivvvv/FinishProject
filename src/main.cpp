#include "SearchServer.h"
#include <iostream>

std::string FindPath(std::string word){
    int a=0;
    for( int i=0;i<word.size();i++)
        if(word[i] =='\\')
                a=i;

    std::string str;
    for( int i=0;i<a;i++)
        str +=word[i];

    std::cout << str << std::endl;

    return str;
}

int main(int argc, char *argv[])
{
    //openFile
    std::string mainPath = FindPath(std::string(argv[0]));
    InvertedIndex index;
    index.SetPath(mainPath);

    ConverterJSON conv = ConverterJSON();
    conv.SetPath(mainPath);
    index.UpdateDocumentBase(conv.GetTextDocuments());

    SearchServer search(index);
    std::vector<std::vector<RelativeIndex>> result = search.search(conv.GetRequests());

    std::vector<std::vector<std::pair<int, float>>> answers = std::vector<std::vector<std::pair<int, float>>>(result.size());
    for(int i=0;i< result.size();i++){
        std::vector<std::pair<int, float>>resultCase =std::vector<std::pair<int, float>>(result[i].size());
        for(int i1=0;i1< result[i].size();i1++){

            std::pair<int, float> resultCaseData =  std::pair<int, float>();
            resultCaseData.first = result[i][i1].doc_id;
            resultCaseData.second = result[i][i1].rank;
            resultCase[i1] = resultCaseData;
        }
        answers[i] = resultCase;
    }
    conv.putAnswers(answers);

    return 0;
};
