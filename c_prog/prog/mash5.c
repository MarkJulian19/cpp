fopen(const char *name, const char *mode);
/*Если указатель на файл нулл - ошибка*/

modes:
"r" "r+" // read, r+ -- чтение запись, на чтение файл должен существовать
"w" "w+" // если фвайл существовал, то файл обнуляется(указатель перебрасывается на начало)
"a" "a+" // запись в конец(добавление), а+ добавление и чтение
"x" // проверка на сущ. файла
"b" "t" // 

int fclose(FILE*)//RETURNS -1 if error, otherwise 0

FILE*tmpfile(); // w+  "b" "t"
if(!fp) {perror("fp");
}
errno char* <-strerror();
fgetc-fputc
fgets-fputs
fscanf-fprintf
fread(void *buf, size_t size, size_t nobj, FILE*fp)//size - size of obj, nobj - ammount of obj
fwrite(const void *buf, -||-)
return: -1 -- err
        <=n

example
>./a.out file
>cat >file
xyuxyuxyuxyuxyuxyuxyuxyuyxuyxuyxuyxuyxyuxyuxyuyxuyxuyxuyxuyxuyux







