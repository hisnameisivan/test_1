# test_1
Тестовое задание от работодателя  
\*.txt файл в формате  
```
user_id;count;country
11231;6;Russia
11232;1;Ukraine
1122;1;Ukraine
``` 
Нужно вывести статистику по country:  
```
country;sum(count) (сумма по count);count_uniq(user_id) (число уникальных user_id для country)
``` 
Предусмотреть устойчивость программы к ошибке формата, если строка не соответствует формату, она пропускается.  

Запуск:  
```
make 
./test test.txt
```
