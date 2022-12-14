# FinishProject
Программа создавалась на ОС Windows, работоспособность и коректность работы программы на других ОС не проверялась и не поддерживается

Данная программа разработана для поиска документов в которых записана искомая информация по введенному слову или предложению


Запуск программы

![image](https://user-images.githubusercontent.com/52557350/203739047-3fde9c25-6a68-45ca-978e-2a75cead46cb.png)

Для запуска программы необходимо запустить программу из папки с ней.
Программа запуститься и закроется после её выполнения, обновив файл answers.json в корневой папке проекта.


Использование программы

![image](https://user-images.githubusercontent.com/52557350/203739387-600dbd9d-09be-45d5-aa1b-86cbff42f5da.png)

Зайдя в файл answers.json можно просмотреть результаты работы программы

В разделах "request***" указаны результаты поиска файлов по введенным запросам *-номер запроса

В разделах "doc_id*" указан номер пути из списка документов добавленных для поиска по их содержимому *-номер результата

В разделах "rank*" указан рейтинг документа(на сколько документ подходит под ваш запрос) *-номер результата

"result": false - Обозначает что ни один из документов не содержит запрашиваемой вами информации.

![image](https://user-images.githubusercontent.com/52557350/203742439-dee40df7-d644-4744-807c-9bc901ab8968.png)


Пользовательский ввод данных

Данные в программу добавляются через следующие файлы:

в файле requests.json задаются фразы используемые для поиска на совпадение в файлах

![image](https://user-images.githubusercontent.com/52557350/203740012-39ead491-d6ee-4e39-b85f-2af4b3ba8fc9.png)![image](https://user-images.githubusercontent.com/52557350/203740355-be57cd95-cf3a-4c18-bae5-fbde929175c3.png)


в файле config.json 

![image](https://user-images.githubusercontent.com/52557350/203740780-8495d7a1-4091-46f9-8560-afca8c029e38.png)

через переменную "max_responses" указывается максимальное кол-во результатов записываемых в answers.json

![image](https://user-images.githubusercontent.com/52557350/203740618-727f1a15-6f7a-449b-a4be-efc07407690f.png)

через переменную "files" указывается пути к файлам для выполнения по ним поиска введенных запросов.
путь к фаилам указывается следующий образом

![image](https://user-images.githubusercontent.com/52557350/203741013-926ee5ad-13c1-4e6b-9d7f-090ac6e386aa.png)![image](https://user-images.githubusercontent.com/52557350/203741259-b035b467-56cb-48f2-be62-a85fdca3733c.png)




Автоматическое тестирование

В исходном проекте в папке tests расположены файлы с окончанием на *_test.cpp
В них представлены автотесты для тестирования в IDE для разработки Cline или подобных.

![image](https://user-images.githubusercontent.com/52557350/203742032-9c0cae38-61c9-47b9-88f4-7734904f510d.png)
![image](https://user-images.githubusercontent.com/52557350/203742131-89afed53-6caf-4265-a16f-0d2543ae82ef.png)


