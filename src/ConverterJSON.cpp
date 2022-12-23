#include "ConverterJSON.h"

std::string path;

void ConverterJSON::SetPath(std::string _path){
path= _path;
}
void  ScanFile(std::ifstream *file, std::string filePath){

    if(!file->good()){
        std::cout <<"File " + filePath+" no accses read" << std::endl;
      //std::exit(0);
    }
}
void  ScanSaveFile( std::string filePath){

    std::ifstream file(filePath);
    if(!file.is_open()){
        std::cout <<"File " + filePath+" saving error" << std::endl;
        //std::exit(0);
    }
    else
        std::cout <<"File " + filePath+" successfully saved" << std::endl;
    file.close();
}

json OpenJson(std::string str){
    std::ifstream file(path+"\\"+str);
    ScanFile(&file,path+"\\"+str);

    json j;
    if(!file.good())
        return j;

    j = json::parse(file);

    file.close();
    return j;
};

std::string OpenFile(std::string str){
    std::string wordFull =" ";
    std::string word;
    std::ifstream file(path+"\\"+str);
    ScanFile(&file,path+"\\"+str);
    if(!file.good())
        return "";
    while(!file.eof()){
        file >> word;
        if(wordFull == " ")
            wordFull = word;
        else
            wordFull +=" "+ word;
    }

    file.close();
    return   wordFull;
};

std::vector<std::string> ConverterJSON::GetTextDocuments(){
    std::vector<std::string> list;
    std::vector<std::string> vec = OpenJson("config.json")["files"];

    for(int i=0;i<vec.size();i++){
        list.push_back(OpenFile(vec[i]));
    }

    return list;
};


/**
* Метод считывает поле max_responses для определения предельного
* количества ответов на один запрос
* @return
*/
int ConverterJSON::GetResponsesLimit(){
    std::string str=  OpenJson("config.json")["config"]["max_responses"];
    return std::stoi(str);
};
/**
* Метод получения запросов из файла requests.json
* @return возвращает список запросов из файла requests.json
*/
std::vector<std::string> ConverterJSON::GetRequests(){
    return OpenJson("requests.json")["requests"];
};
/**
* Положить в файл answers.json результаты поисковых запросов
*/
void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers){

    auto requestStr =[](int a){
        std::string str = "request";
        std::string end =std::to_string(a);
        if(a>99)
            return str+end;
        if(a>9)
            return str+"0"+end;

        return str+"00"+end;
    };

    std::ofstream file;
    file.open(path+"\\answers.json", std::ofstream::out | std::ofstream::trunc);
    bool openFile = file.is_open();
    if(!openFile)
        std::cout <<"File answers.json saving error" << std::endl;

    std::string str;
    json j;
    for(int i=0;i<answers.size();i++){
        str = requestStr(i);
        bool use = answers[i].size()>0;
        j["answers"][str]["result"] = use;

        if(use){
            std::vector<std::pair<int, float>> vec =answers[i];
            for(int k=0;k<vec.size();k++){

                j["answers"][str]["relevance"]["doc_id"+std::to_string(k)]=vec[k].first;
                j["answers"][str]["relevance"]["rank"+std::to_string(k)]=vec[k].second;
            }
        }
    }

   // std::cout << j.dump(4) << std::endl;

    file << std::setw(4) << j<< std::endl;
    file.close();

    if(openFile)
        ScanSaveFile(path+"\\answers.json");
};