#ifndef CONVERTERJSON_H
#define CONVERTERJSON_H

#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using json = nlohmann::json;

class ConverterJSON {
public:
ConverterJSON() = default;

void SetPath(std::string _path);
/**
* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных
* в config.json
*/

//json OpenJson(std::string str);

//std::string OpenFile(std::string str);

std::vector<std::string> GetTextDocuments();


/**
* Метод считывает поле max_responses для определения предельного
* количества ответов на один запрос
* @return
*/
int GetResponsesLimit();
/**
* Метод получения запросов из файла requests.json
* @return возвращает список запросов из файла requests.json
*/
std::vector<std::string> GetRequests();
/**
* Положить в файл answers.json результаты поисковых запросов
*/
void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);

};
#endif // CONVERTERJSON_H
