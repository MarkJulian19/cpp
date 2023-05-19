#include <iostream>
#include <string>
#include <cstdio>
#include <ctype.h>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
int line_num = 1;
enum type_of_lex {
    LEX_NULL, /* 0 */
    /* NULL, "and", "or", "goto", "bool", "do", "while", "if", "for", "else", 
    "true", "false", "not", "int", "read", "write", "break", "program" */
    LEX_AND,
    LEX_OR, 
    LEX_GOTO, 
    LEX_BOOL, 
    LEX_DO, 
    LEX_WHILE, 
    LEX_IF, 
    LEX_FOR, 
    LEX_ELSE, 
    LEX_TRUE, 
    LEX_FALSE, 
    LEX_NOT, 
    LEX_INT, 
    LEX_READ, 
    LEX_WRITE, 
    LEX_BREAK, 
    LEX_PROGRAM, 
    LEX_STRING, 
    LEX_STRUCT, 
    LEX_FIN, 
    /* NULL, "@", ";", ":", ",", "==", "(", ")", 
    "<", ">", "+", "-", "*", "/", ">=", 
    "<=", "!=", "=", "{", "}" */
    LEX_AT, 
    LEX_SEMICOLON, 
    LEX_COLON, 
    LEX_COMMA, 
    LEX_EQUAL, 
    LEX_OPENBRACKET, 
    LEX_CLOSEBRACKET, 
    LEX_LESS, 
    LEX_GREAT, 
    LEX_PLUS, 
    LEX_MINUS, 
    LEX_MULTIPLY, 
    LEX_DIVIDE, 
    LEX_GREATOREQUAL, 
    LEX_LESSOREQUAL,
    LEX_NOTEQUAL, 
    LEX_ASSIGN, 
    LEX_OPENBRACE, 
    LEX_CLOSEBRACE, 
    LEX_NUM, 
    LEX_ID, 
    LEX_STR, 
    POLIZ_LABEL, 
    POLIZ_ADDRESS, 
    POLIZ_GO, 
    POLIZ_FGO 
};

class Lex {     // класс Lex, объект класса хранит тип лексемы и значение
        type_of_lex t_lex;
        int v_lex;
    public:
        bool is_str = false;
        Lex (type_of_lex t = LEX_NULL, int v = 0): t_lex(t), v_lex(v) {
            if (t == LEX_STR)
                is_str = true;
            else
                is_str = false;
        }
        type_of_lex get_type () { return t_lex; }
        int get_value () { return v_lex; };
        void minus() { v_lex = 0 - v_lex; }
        friend ostream& operator << (ostream &s, Lex l);    // Вывод лексемы на экран в понятном для представления виде
};

class Ident {       // класс Ident, содержит информацию о лексемах
        string name;
        bool declare;
        type_of_lex type;
        bool assign;
        int value;
        string str_value;
    public:
        Ident (): declare(false), assign(false) {}
        bool operator == (const string& s) const {
            return name == s;
        }
        Ident (const string n) {
            name    = n;
            declare = false;
            assign  = false;
        }
        string get_name () { return name; }
        void put_name (const string n) { name = n; }
        bool get_declare () { return declare; }
        void put_declare () { declare = true; }
        type_of_lex get_type () { return type; }
        void put_type (type_of_lex t) { type = t; }
        bool get_assign () { return assign; }
        void put_assign (bool a) { assign = a; }
        int get_value () { return value; }
        void put_value (int v) { value = v; }
        string get_strvalue () const { return str_value; }
        void put_strvalue (string s) { str_value = s; }
};

vector<Ident> TID;      // массив идентификаторов, которые не объявлены как служебные слова

int put (const string & buf ) { // функиця, записывающая в таблицу новый идентификатор или возвращающая номер записи
    vector<Ident>::iterator k;
    if ((k = find(TID.begin(), TID.end(), buf)) != TID.end()) return k - TID.begin();
    TID.push_back(Ident(buf));
    return TID.size () - 1;
}

vector<string> TStr;        // массив строк string, используемых в программе

int put_str (const string & buf) {  // аналогичная функция для строк
    vector<string>::iterator k;
    if ((k = find(TStr.begin(), TStr.end(), buf)) != TStr.end()) return k - TStr.begin();
    TStr.push_back(buf);
    return TStr.size() - 1;
}

static int in_struct = 0;   // количество структур

class struc{
    public:
        string name;
        vector <Ident> TIDS;
};

vector <struc> TSTRUCT;
void print_TSTRUC()
{
    for (int i = 0; i < TSTRUCT.size(); i++)
    {
        cout << TSTRUCT[i].name << endl;
        for (int j = 0; j < TSTRUCT[i].TIDS.size(); j++)
        {
            cout<< '\t' << TSTRUCT[i].TIDS[j].get_name() << endl;;
        }
    }
}
int check_struct_name (const string & buf) {        // проверка имени структуры
    //cout << TSTRUCT.size() << endl;
    //cout << TSTRUCT[0].name << endl;
    for (int i = 0; i < TSTRUCT.size(); i++) {
        if (TSTRUCT[i].name == buf) {
            return i;
        }
    }
    cout << "Now such struct!";
    throw 'a';
}
int check_TID(const string &buf)
{
    for (int i0 = 0; i0 < TID.size(); i0++)
    {
        //cout << buf << ' ' << TID[i0].get_name() << endl;
        if (buf == TID[i0].get_name())
            return i0;
    }
    throw "No such IDent\n";
    return -1;
}
class Scanner {     // класс Scanner, просматривает файл и выделяет из файла лексемы
        FILE *fp;
        char c;
        // функция, просматривающая, есть ли слово buf в таблице list и возвращающая номер этого слова в таблице
        int look (const string buf, const char ** list ) {
            int i = 0;
            while (list[i]) {
                if (buf == list[i]) return i;
                i++;
            }
            return 0;
        }
        void gc () { c = fgetc (fp); }
    public:
        static const char *TW[], *TD[];
        Scanner (const char* program) {
            if (!(fp = fopen(program, "r" ))) throw  "cannot open file" ;
        }
        Lex get_lex ();
        ~Scanner () {       // в деструкторе нужно закрыть файл program
            fclose(fp);
        }
};

int bracket_balance = 0;
int brace_balance = 0;

const char * Scanner::TW[] = {
    "", "and", "or", "goto", "bool", "do", "while", "if", "for", "else",
  // 0    1      2      3       4      5      6       7     8       9     
    "true", "false", "not", "int", "read", "write", "break", "program", "string", "struct",  NULL
  //  10       11      12     13     14       15      16        17         18        19       20
}; 

const char * Scanner::TD[] = {
    "lex_fin", "@", ";", ":", ",", "==", "(", ")", "<", ">", "+", "-", "*", "/", ">=", 
  //    0       1    2    3    4     5    6    7    8    9    10   11   12   13   14
    "<=", "!=", "=", "{", "}", NULL                                                      
  // 15    16    17   18  19    20
};

ostream & operator<< ( ostream &s, Lex l ) {
    string n;
    string table;
    if (l.t_lex < LEX_FIN) {
        n = Scanner::TW[l.t_lex];
        table = "TW";
    }
    else if (l.t_lex >= LEX_FIN && l.t_lex < LEX_NUM) {
        n = Scanner::TD[ l.t_lex - LEX_FIN];
        table = "TD";
    }
    else if (l.t_lex == LEX_NUM) {
        n = "NUM";
        table = "number";
    }
    else if (l.t_lex == LEX_ID) {
        n = TID[l.v_lex].get_name ();
        table = "TID";
    }
    else if (l.t_lex == LEX_STR) {
        n = TStr[l.v_lex];
        table = "TStr";
    }else if (l.t_lex == POLIZ_LABEL) {
        n = "Label";
        table = "POLIZ";
    }else if (l.t_lex == POLIZ_ADDRESS) {
        n = "Addr";
        table = "POLIZ";
    }else if (l.t_lex == POLIZ_GO) {
        n = "!";
        table = "POLIZ";
    }else if (l.t_lex == POLIZ_FGO) {
        n = "!F";
        table = "POLIZ";
    }else throw l;
    s << table << " (" << n << ',' << l.v_lex << ");" << endl;
    return s;
}

Lex Scanner::get_lex () {
    enum state {H, IDENT, NUMB, COM, ALE, NEQ, STR};
    int d, j;    // d - число, которое мы можем встретить в программе, j - номер служебного слова
    string buf, str;    // buf - любое имя используемое в программе, str - строка string из программы
    state CS = H;
    do {
        gc();       // читаем символ в начале каждого цикла
        if (c == EOF) return Lex(LEX_FIN);     // Если файл закончился, то выходим из цикла
        switch (CS) {
            case H:
                if (c == ' ' || c == '\n' || c == '\r' || c == '\t')   // пропуск пробельных символов
                {
                    if (c == '\n')
                    {
                        line_num++;
                    }
                }
                else if (isalpha(c)) {      // поиск слова 
                    buf.push_back(c);
                    CS = IDENT;
                }else if (isdigit(c)) {     // поиск числа
                    d = c - '0';
                    CS = NUMB;
                }else if (c == '/'){        // проверка на начало комментария
                    gc();
                    if (c == '*') CS = COM;
                    else{
                        ungetc(c, fp);
                        buf.push_back('/');
                        if (j = look(buf, TD)) return Lex((type_of_lex)(j + (int) LEX_FIN), j);
                        else throw c;
                    }
                }else if (c == '=' || c == '<' || c == '>') {   // поиск операции сравнения
                    buf.push_back(c);
                    CS = ALE;
                }else if (c == '@') return Lex(LEX_FIN);    // символ обоначающий завершение программы
                else if (c == '!') {        // проверка на неравенство !=
                    buf.push_back(c);
                    CS = NEQ;
                }else if (c == '"') CS = STR;       // случай строки string
                else if (c == '(' || c == ')' || c == '{' || c == '}'){
                    if (c == '(') bracket_balance++;
                    else if (c == ')') bracket_balance--;
                    else if (c == '{') brace_balance++;
                    else if (c == '}') brace_balance--;
                    if (brace_balance < 0) throw "Баланс фигурных скобок нарушен";
                    if (bracket_balance < 0) throw "Баланс круглых скобок нарушен";
                    buf.push_back(c);
                    if (j = look(buf, TD)) return Lex((type_of_lex)(j + (int) LEX_FIN), j);
                    else throw c;
                }else{
                    buf.push_back(c);
                    if (j = look(buf, TD)) return Lex((type_of_lex)(j + (int) LEX_FIN), j);
                    else throw c;
                }
                break;
            case IDENT: 
                if (isalpha(c) || isdigit(c) || c == '.') buf.push_back(c); // получаем слово идентификатор (или служебное слово)
                else {
                    ungetc(c, fp); 
                    if (j = look(buf, TW)) return Lex((type_of_lex) j, j); 
                    else {
                        j = put(buf);
                        return Lex(LEX_ID, j);
                    }
                }
                break;
            case NUMB:
                if (isdigit(c)) d = d * 10 + (c - '0'); // получаем число int
                else {
                    ungetc(c, fp);
                    return Lex(LEX_NUM, d);
                }
                break;
            case COM: 
                if (c == '*') {         // ищем конец комментария
                    gc();
                    if (c == '/') CS = H;
                    else ungetc(c, fp);     // на случай если встретим **/, чтобы комментарий завершился
                }else if (c == '@') throw c;    // даже внутри комментария заканчиваем программу если встретим @
                break;
            case ALE:
                if (c == '=') {     // >=, <=, или ==
                    buf.push_back(c);
                    j = look(buf, TD);
                    return Lex((type_of_lex)(j + (int) LEX_FIN), j);
                }else{              // >, <, или =
                    ungetc(c, fp);
                    j = look(buf, TD);
                    return Lex((type_of_lex)(j + (int) LEX_FIN), j);
                }
                break;
            case NEQ:
                if (c == '=') {     // !=
                    buf.push_back(c);
                    j = look(buf, TD);
                    return Lex(LEX_NOTEQUAL, j);
                }else throw '!';    //ошибка
                break;
            case STR:
                str.clear();    // очистка буфера
                while (c != '"') {      // запись строки в буфер
                    str.push_back(c); 
                    gc();
                }
                j = put_str(str);       // добавление новой строки в TStr - таблицу строк
                return Lex(LEX_STR, j);
                break;
        }
    } while (true);     // выход из цикла либо по throw либо по return
};



void print_TID () {     // вывод на экран таблицы TID
    cout << "TID:" << endl;
    if (TID.size() == 0) cout << "Таблица пустая" << endl;
    for (int k = 0; k < TID.size(); k++) 
        cout << TID[k].get_name() << " - " << k <<  "  " << TID[k].get_type() <<  endl;
}

void print_TStr () {    // вывод на экран таблицы TStr
    cout << "TStr:" << endl;
    if (TStr.size() == 0) cout << "Таблица пустая" << endl;
    for (int k = 0; k < TStr.size(); k++)
        cout << TStr[k] << " - " << k << endl;
}

///// Parser /////

// аргументы функции - стек и элемент такого же типа, что и элементы стека
// функция присваивает второму операнду верхушку стека и изымает этот элемент из стека
template <class T, class T_EL>          
void from_st (T & st, T_EL & i) {
    i = st.top(); 
    st.pop();
}

stack <vector <int> > stbreak;      // стек векторов для прерываний циклов с помощью break
// это стек на случай вложенных циклов. Вектор int содержит информацию о места прерываний
// то есть о местах в ПОЛИЗе, куда нужно будет положить адреса для выходов по break
// это вектор

vector <int> TGOTO;             // вектор меток для оператора GoTo, откуда можно переходить и куда можно переходить
                                // он содержит информацию обо всех метках
vector <int> numJ;              // вектор номеров меток для оператора GoTo, куда можно переходить и откуда можно переходить
vector <int> checkJ;            // вектор меток, по которым мы переходим

void print_goto_vec (vector <int> A) {    // вывод на экран векторов выше
    if (A.size() == 0) cout << "Вектор пустой" << endl;
    for (int k = 0; k < A.size(); k++)
        cout << A[k] << " - " << k << endl;
}

void check_jump (int n){        // проверка метки GoTo не объявлена ли она дважды и добавление новой метки в таблицу
    vector<int>::iterator k;
    if ((k = find(checkJ.begin(), checkJ.end(), n)) != checkJ.end()) {
        cout<<"Дважды объявлена одна метка GoTo" << endl;
        throw "Метка GoTo объявлена дважды";
    }else checkJ.push_back(n);
}

int putgoto (const int buf, const int n) {      // добавление новой метки GoTo в вектор адресов меток
    vector<int>::iterator k;
    if ((k = find(TGOTO.begin(), TGOTO.end(), buf)) != TGOTO.end())  
        return numJ[k-TGOTO.begin()];
    if (n != 0) {
        TGOTO.push_back(buf);
        numJ.push_back(n);
    }
    return 0;
}

class Parser {
    Lex          curr_lex;      // текущая лексема
    type_of_lex  c_type;        // тип текущей лексемы
    int          c_val;         // значение текущей лексемы
    Scanner      scan;          // сканер, получающий очередную лексему
    stack < int >           st_int;     // стек чисел - переменных, которые будут инициализованы
    stack < type_of_lex >   st_lex;     // стек типов лексем - для ПОЛИЗа
    void  P();                  // проверка начала программы и инициализации переменных
    void  STRUC();              // проверка верности структур
    void  D1();                 // проверка верности начальной инициализации
    void  D();                  // проверка названий переменных в начальной инициализации
    void  B();                  // проверка целостности программы от { до }
    void  S();                  // проверка зарезервированных функций программы (for, if, write, goto, while ...)
    void  A();                  // проверка присваивания
    void  OR();                 // проверка верности or
    void  AND();                // проверка верности and
    void  E();                  // проверка сравнений
    void  PM();                 // проверка + и -
    void  MD();                 // проверка * и /
    void  Fin();                // проверка верности переменных, строк и констант
    void  dec (type_of_lex type);   // внесение информации об идентификаторе класса Ident
    void  check_id ();          // проверка была ли инициализирована переменная (идентификатор)
    void  check_op ();          // проверка возможности применить операцию (проверка типов операндов)
    void  check_not ();         // проверка возможности применить операцию not (применима только к boolean)
    void  eq_type ();           // проверка равенства типов при присваивании
    void  eq_bool ();           // проверка принадлежности к типу boolean
    void  check_id_in_read ();  // проверка 
    void  gl () {               // проверка была ли внесена информация об идентификаторе (Ident)
        curr_lex  = scan.get_lex ();        // получение и печать на экран очередной лексемы
        c_type    = curr_lex.get_type ();
        //cout << curr_lex;
        c_val     = curr_lex.get_value ();
    }
public:
    vector <Lex> poliz;         // вектор ПОЛИЗа
    Parser (const char *program): scan (program) {}
    void analyze();
};

// функция, проверяющая чтобы код программы верно закончился и выводит полученный ПОЛИЗ
void Parser::analyze () {       
    //cout << "ANALYZE" << endl;
    gl();       // получение первой лексемы
    P();        // обработка кода программы
    if (c_type != LEX_FIN) throw curr_lex;      // если последняя не FIN то ошибка
    
    if (TGOTO.size() != checkJ.size()) throw "Есть переходы по необъявленным меткам";
    
    cout << "\n\nПолученный ПОЛИЗ" << endl;
    for (Lex l : poliz) cout << l;          // вывод полученных лексем ПОЛИЗа
    cout << "Конец ПОЛИЗа" << endl;
}

// функция, проверяющая program в начале кода программы и вызывающая фунции проверки верности инициализации структор и переменных
// и начинающая проверку программы после инициализации
void Parser::P () {             
    //cout << "P" << endl;
    if (c_type == LEX_PROGRAM) {        // проверка что программа начинается со слова "program"
        gl();
    }
    else throw curr_lex;           // если программа начинается не с program то это ошибка
    while (c_type == LEX_STRUCT) {      // обработка структур, struct идут сразу после "program"
        STRUC();
        gl();
    }
    D1();                  // когда структуры закончились мы обрабатываем инициализацию переменных
    if (c_type != LEX_OPENBRACE) throw curr_lex;        // проверка наличия { после инициализации        
    B();                   // проверка тела кода программы (в {})
}

/*
Все имена переменных попадают в таблицу TID на этапе лексического анализа.
Если переменная инициализируется, то поле declare в классе Ident принимает значение true (изначально false).
Если же переменная объявляется только как поле структуры, то она попадает в таблицу TIDS данной структуры, а значение declare 
идентификатора остается false, поэтому обратиться к переменной (идентификатору), как к самостоятельной переменной нельзя.
Если идентификатор (переменная) объявляется и среди переменных, используемых в программе и как поле структуры, то эти два
идентификатора будут иметь разные "смыслы" несмотря на одинаковые названия.
*/

// проверка верности описания структуры
void Parser::STRUC(){
    //cout << "STRUC" << endl;
    type_of_lex buft1;  // тип лексемы поля структуры
    Ident buft2;        // сохранение информации о поле структурыКод программы введен корректно
    struc buft;         // сохранение информации о структуре
    gl();               // получение новой лексемы сразу после слова "struct"
    if (c_type != LEX_ID) {       // проверка существования имени структуры, если имя не написано - ошибка
        cout<<"Не найдено имя структуры" << endl;
        throw curr_lex;
    }
    buft.name = TID[c_val].get_name();     // записываем в буфер информации о структуре имя структуры
    gl();                               // взятие следующей за именем структуры лексемы
    if (c_type != LEX_OPENBRACE) {       // проверка наличия { после имени, если нет - ошибка
        cout<<"Необходима {" << endl;
        throw curr_lex;
    }
    gl();
    while (c_type != LEX_CLOSEBRACE) {       // проверка полей структуры пока не встретим '}'
        if (c_type == LEX_INT || c_type == LEX_BOOL || c_type == LEX_STRING) {      // выбирается типа переменной
            if (c_type == LEX_STRING) buft1 = LEX_STR;  // если тип string, то следующие идентификаторы (переменные) именют тип лексемы LEX_STR
            else buft1 = c_type;     // если тип int или boolean, то идентификаторы также имеют тип int или boolean
        }else{                    // если тип полей описан неверно, то это ошибка
            cout << "Неизвестный тип" << endl;
            throw curr_lex;
        }
        gl();
        while (c_type != LEX_SEMICOLON) {        // перебор всех полей данного типа, объявленных через запятую
            if (c_type != LEX_ID) {     // если идентификатор имеет запрещенное имя, то это ошибка
                cout << "Ошибка инициализации в структуре" << endl;
                throw curr_lex;
            }
            buft2.put_name(TID[c_val].get_name());      // кладем имя поля в буфер (класса Ident)
            buft2.put_type(buft1);                      // и тип поля кладем туда же
            buft.TIDS.push_back(buft2);                 // записываем этот буфер в таблицу TIDS, содержащую информацию о полях данной структуры
            gl();
            if (c_type == LEX_COMMA) gl();              // пропускаем запятые, они в обработке при инициализации не нуждаются
            else if(c_type != LEX_SEMICOLON){   // после имени нового поля должна быть , или ; иначе ошибка 
                cout << "Не встречено ; где это необходимо" << endl;
                throw curr_lex;
            }
        }
        gl();
    }
    TSTRUCT.push_back(buft);        // записываем в вектор содержащий информацию о структурах новую структуру
}

// проверка верности начальной инициализации переменных
void Parser::D1 () {
    //cout << "D1" << endl;
    if (c_type == LEX_INT || c_type == LEX_BOOL || c_type == LEX_STRING) {     // нахождение типа переменной
        D ();
        while (c_type == LEX_SEMICOLON) {
            gl ();
            if (c_type != LEX_INT && c_type != LEX_BOOL && c_type != LEX_STRING) break;     // проверка чтобы не был дважды объявлен тип
            D();
        }
    }else if (c_type == LEX_ID) {    // нахождение имени структуры
        int j, val_buf;
        j = check_struct_name(TID[c_val].get_name());
        string s = TID[c_val].get_name();
        //cout << j << endl;
        gl();
        string buft3;
        for (int i = 0; i < TSTRUCT[j].TIDS.size(); i++) {      // нахождение и проверка переменных в струкрутах
            TID[c_val].put_type(LEX_STRUCT);
            TID[c_val].put_declare();
            // c_val = j;
            TID[c_val].put_strvalue(s);
            buft3 = TID[c_val].get_name();
            buft3 = buft3 + '.' + TSTRUCT[j].TIDS[i].get_name();
            val_buf = put(buft3);           // добавление имени поля структуры в таблицу полей структуры
            st_int.push(val_buf);
            dec(TSTRUCT[j].TIDS[i].get_type());
        }
        gl();
        if (c_type != LEX_SEMICOLON) {
            cout << "Не встречено ; где это необходимо" << endl;
            throw curr_lex;
        }
        gl();
        if(c_type != LEX_OPENBRACE) D1();       // новый тип переменной - новый оборот в рекурсии
    }else throw curr_lex;
}

// функция, проверяющая верность присваивания переменным начальных значений при инициализации и имена переменных
void Parser::D () {
    //cout << "D" << endl;
    type_of_lex buf1;
    buf1 = c_type;
    gl();
    if (c_type != LEX_ID) throw curr_lex;       // если инициализируется не переменная, то это ошибка
    else{
        if (buf1 == LEX_STRING){
            //cout << "\t\t" << curr_lex << endl;
            curr_lex.is_str = true;              //нужно будет в функциии Interoretator
        }
        st_int.push(c_val);
        int buf5 = c_val;
        gl ();
        if (c_type == LEX_ASSIGN) {       // проверка происходящего при присваивании
            poliz.push_back(Lex(POLIZ_ADDRESS, buf5));      // в стек ПОЛИЗа попадает значение переменной
            gl();                       // тут начинается проверка того, что присваивается переменной
            if ((buf1 == LEX_INT && (c_type == LEX_MINUS || c_type == LEX_NUM)) ||
               (buf1 == LEX_BOOL && (c_type == LEX_TRUE || c_type == LEX_FALSE)) ||
               (buf1 == LEX_STRING && c_type == LEX_STR)) {  
                if (c_type == LEX_MINUS) {      // например a = -b; идет проверка минуса
                    gl();
                    if (c_type == LEX_NUM) curr_lex.minus();
                    else{
                        cout << "Не найдено число" << endl;
                        throw curr_lex;
                    }
                }
                poliz.push_back(curr_lex);      // в стек ПОЛИЗа попадает присваиваемое значение 
                gl();
                poliz.push_back(Lex(LEX_ASSIGN));       // в стек ПОЛИЗа кладем знак =
            }else{
                cout << "Неверная начальная инициализация" << endl;
                throw curr_lex;
            }
        }
        while (c_type == LEX_COMMA) {           // повторяем описанные выше действия, если в программе они идут через запятую
            gl ();
            if (c_type != LEX_ID) throw curr_lex;   // если что-то присваивается не переменной, то это ошибка
            else{
                if (buf1 == LEX_STRING){
                    //cout << "\t\t" << curr_lex << endl;
                    curr_lex.is_str = true;              //нужно будет в функциии Interoretator
                }
                st_int.push(c_val);
                buf5 = c_val;
                gl();
                if (c_type == LEX_ASSIGN) {     // проверка происходящего при присваивании
                    poliz.push_back(Lex(POLIZ_ADDRESS, buf5));      // в стек ПОЛИЗа попадает значение переменной
                    gl();                       // тут начинается проверка того, что присваивается переменной
                    if ((buf1 == LEX_INT && (c_type == LEX_MINUS || c_type == LEX_NUM)) ||
                       (buf1 == LEX_BOOL && (c_type == LEX_TRUE || c_type == LEX_FALSE)) ||
                       (buf1 == LEX_STRING && c_type == LEX_STR)) {  
                        if (c_type == LEX_MINUS) {      // например a = -b; идет проверка минуса
                            gl();
                            if (c_type == LEX_NUM) curr_lex.minus();
                            else{
                                cout << "Не найдено число" << endl;
                                throw curr_lex;
                            }
                        }
                        poliz.push_back(curr_lex);      // в стек ПОЛИЗа попадает присваиваемое значение 
                        gl();
                        poliz.push_back(Lex(LEX_ASSIGN));       // в стек ПОЛИЗа кладем знак =
                    }else{
                        cout << "Неверная начальная инициализация" << endl;
                        throw curr_lex;
                    }
                }
            }
        }
        if (c_type != LEX_SEMICOLON) throw curr_lex;    // ошибка если нет ; в конце инициализации переменной
        else{
            if (buf1 == LEX_INT) dec(LEX_INT);      // переменная типа int инициализирована - это записывается в идентификатор Ident переменной
            else if (buf1 == LEX_BOOL) dec(LEX_BOOL);    // переменная типа bool инициализирована 
            else
            if (buf1 == LEX_STRING) dec(LEX_STR);     // переменная типа string инициализирована 
            else throw curr_lex;                // иначе лексема имеет неверный тип
        }
    }
}

// функция, проверяющая что тело программы начинается с { и заканчивается }
// эта функция вызывает функцию S(), проверяющую верность всех операций
void Parser::B () {
    //cout << "B" << endl;
    if (c_type == LEX_OPENBRACE) {      // проверка наличия {
        gl();
        while (c_type != LEX_CLOSEBRACE) {      // цикл, пока не встретится }
            S ();
            if (!(c_type == LEX_CLOSEBRACE && brace_balance == 0)) gl();
            if (c_type == LEX_FIN) throw "Не найдена } в конце программы";
        }
        if (c_type == LEX_CLOSEBRACE) {         // корректное завершение при встрече последней }
            cout << "Код программы введен корректно" << endl;
            gl ();
        }else throw curr_lex;
    }else throw curr_lex;
}

// функция, выполняющая проверку всех операций программы, таких как if, for, while, read, и других из таблицы TW
void Parser::S () {
    //cout << "S" << endl;
    int pl0, pl1, pl2, pl3, pl4, pl5, pl6, pl7;
    if (c_type == LEX_OPENBRACE) {        // встретилось выражение в фигурных скобках
        gl();
        while (c_type != LEX_CLOSEBRACE) {    // вызов себя же пока не встретится }
            S();
            gl();
        }
    }// операторы в {} закончились
    else if (c_type == LEX_ID) {        // случай, если мы встретили идентификатор (переменную)
        if (TID[c_val].get_declare() == false) {    // если она встретилась первый раз 
            int buf7 = c_val;
            gl();
            if (c_type == LEX_COLON) {          // и после стоит двоеточие
                check_jump(buf7);               // то возможно это метка перехода - проверим это
                int buf8;
                if ((buf8 = putgoto(buf7, poliz.size())) != 0) {
                    int buf9 = poliz.size();
                    poliz[buf8] = Lex(POLIZ_LABEL, buf9);   // вставляем в нужное место стека ПОЛИЗа адрес перехода GoTo
                }
                gl();  
                S();
            }else{
                cout<<"Переменная не инициализирована" << endl;
                throw curr_lex;
            }
        }else A();                  // если встреченная переменная уже инициализована (функцией dec) то идем дальше
    }// конец случая идентификатора
    else if (c_type == LEX_IF) {      // проверка верности функции if и внесение всех необходимых данных в стек ПОЛИЗа
        gl ();
        if (c_type != LEX_OPENBRACKET) throw curr_lex;    // обязательно наличие ( сразу после "if"
        gl();
        A();
        eq_bool();
        pl2 = poliz.size();                     // запоминаем куда класть адрес перехода по false
        poliz.push_back(Lex());                 // кладем пустую лексему, чтобы потом заменить ее адресом перехода
        poliz.push_back(Lex(POLIZ_FGO));        // кладем в стек ПОЛИЗа команду перехода по false
        if (c_type == LEX_CLOSEBRACKET) {       // обязательно наличие ) после условия
            gl();   
            S();                // проверка и заполнение тела if 
            pl3 = poliz.size();                 // запоминаем куда класть адрес безусловного перехода
            poliz.push_back(Lex());             // кладем пустую лексему, чтобы заменить ее потом адресом безусловного перехода
            poliz.push_back(Lex(POLIZ_GO));     // кладем в полиз безусловный переход
            poliz[pl2] = Lex(POLIZ_LABEL, poliz.size());    // перед условным переходом кладем метку - куда переходить
            if (c_type == LEX_CLOSEBRACE) gl();         // если встретили { - берем следующую лексему
            if (c_type == LEX_SEMICOLON) gl();          // если встретили ; - берем следующую лексему
            if (c_type == LEX_ELSE) {           // если встретили else - берем новую лексему и вызываем рекурсивно функцию S()
                gl();
                S();                            // заполнение и проверка тела else
                poliz[pl3] = Lex(POLIZ_LABEL, poliz.size());        // адрес перехода по else 
            }else throw curr_lex;
        }else throw curr_lex;
    }// конец if
    else if (c_type == LEX_WHILE) {         // проверка верности цикла while и внесение необходимых операций в стек ПОЛИЗа
        pl0 = poliz.size();
        gl();
        stbreak.push(vector<int>());
        if (c_type != LEX_OPENBRACKET) throw curr_lex;      // условие while обязательно должно начинаться с (
        gl();
        A();
        eq_bool();              // условие while должно быть типа boolean
        pl1 = poliz.size();
        poliz.push_back(Lex());         // кладем в ПОЛИЗ пустую лексему чтобы позже положить туда адрес перехода
        poliz.push_back(Lex(POLIZ_FGO));        // кладем в полиз переход по false
        if (c_type == LEX_CLOSEBRACKET) {           // условие while должнно заканчиваться ), иначе - ошибка
            gl();
            S();
            poliz.push_back(Lex(POLIZ_LABEL, pl0));         // после тела while кладем в стек ПОЛИЗа адрес перехода в начало цикла
            poliz.push_back(Lex(POLIZ_GO));                 // кладем в ПОЛИЗ команду безусловного перехода
            poliz[pl1] = Lex(POLIZ_LABEL, poliz.size());    // на место пустой лексемы кладем адрес переода по false
            while (!stbreak.top().empty()) {                    // из стека stbreak переносим в ПОЛИЗ адрес для break, если такой есть
                poliz[stbreak.top().back()] = Lex(POLIZ_LABEL, poliz.size());
                stbreak.top().pop_back();
            }
            stbreak.pop();
        }else throw curr_lex;
    }// конец while
    else if ( c_type == LEX_BREAK) {    // проверка верности оператора break и внесение необходимых данных в ПОЛИЗ
        if (stbreak.size() == 0) {      // если стек stbreak отвечающий за прерывания пустой (то есть мы находимся не в цикле), то это ошибка
            cout << "Нельза прерваться с break - нет цикла" << endl;
            throw curr_lex;
        }
        stbreak.top().push_back(poliz.size());  // кладем в стек stbreak размер стека ПОЛИЗа - чтобы знать место прерывания
        poliz.push_back(Lex());     // кладем в стек ПОЛИЗа пустую лексему, которая будет заменена адресом
        poliz.push_back(Lex(POLIZ_GO));     // кладем в стек ПОЛИЗа коменду перехода
        gl();
        if (c_type != LEX_SEMICOLON) {      // после оператора break необходима ;
            cout<<"Необходима ; после оператора break" << endl;
            throw curr_lex;
        }
    }// конец break
    else if (c_type == LEX_GOTO) {      // проверка верности оператора GoTo и внесение необходимых данных в стек ПОЛИЗа
        gl();
        if (c_type == LEX_ID) {         // после оператора должна стоять метка - идентификатор перехода
            int buf6 = putgoto(c_val, 0);   // проверяем значение, куда нужно перейти
            if (buf6 != 0) {            // если такое уже встречалось, то
                poliz.push_back(Lex(POLIZ_LABEL, buf6));    // кладем в стек ПОЛИЗа адрес перехода
                poliz.push_back(Lex(POLIZ_GO));             // и команду перехода
            }
            else{               // если не встречалось, то запоминаем его
                putgoto(c_val, poliz.size());       
                poliz.push_back(Lex());         // кладем пустую лексему в стек ПОЛИЗа, чтобы потом заменить на адрес перехода
                poliz.push_back(Lex(POLIZ_GO)); // операция безусловного перехода в стек ПОЛИЗа
            }
            gl();
            if (c_type != LEX_SEMICOLON) {      // в конце обязательно должна быть ;
                cout << "Необходима ; псле метки GoTo" << endl;
                throw curr_lex;
            }
        }else{                  // если после слова goto нет метки, то это ошибка
            cout<<"Ошибка GoTo";
            throw curr_lex;
        }
    }// конец GoTo
    else if (c_type == LEX_READ) {      // проверка верности оператора read и внесение необходимых данных в ПОЛИЗ
        gl ();
        if (c_type == LEX_OPENBRACKET) {        // после слова read должна стоять (
            gl ();
            if (c_type == LEX_ID) {         // проверка идентификатора (переменной) для операции read
                check_id_in_read();
                poliz.push_back(Lex(POLIZ_ADDRESS, c_val));         // кладем в ПОЛИЗ адрес переменной
                gl();
            }else throw curr_lex;
            if (c_type == LEX_CLOSEBRACKET) {       // после обязательно должна быть )
                gl();
                if (c_type != LEX_SEMICOLON) {      // после оператора должна стоять ;
                    cout << "Необходима ;" << endl;
                    throw curr_lex;
                }
                poliz.push_back(Lex(LEX_READ));     // кладем лексему read в ПОЛИЗ
            }else throw curr_lex;
        }else throw curr_lex;
    }// конец read
    else if (c_type == LEX_WRITE) {         // проверка верности оператора write и внесение необходимых данных в стек ПОЛИЗа
        gl();
        if (c_type == LEX_OPENBRACKET) {        // после слова write должна стоять (
            gl();
            A();       // нахождение операндов write
            poliz.push_back(Lex(LEX_WRITE));        // внесение лексемы write в стек ПОЛИЗа
            while (c_type == LEX_COMMA) {   // если операндов несколько, то учтем их все
                gl();
                A();        // нахождение операндов write
                poliz.push_back(Lex(LEX_WRITE));
            }
            if (c_type == LEX_CLOSEBRACKET) {       // после операндов должна стоять )
                gl();
                if (c_type != LEX_SEMICOLON) {      // в конце обязательно нужно ;
                    cout << "Необходима ;" << endl;
                    throw curr_lex;
                }
            }else throw curr_lex;
        }else throw curr_lex;
    }// конец write
    else if (c_type == LEX_FOR) {       // проверка верности цикла for и внесение необходимых операций в стек ПОЛИЗа
        stbreak.push(vector<int>());
        gl();
        if(c_type != LEX_OPENBRACKET) throw curr_lex;       // условие цикла for обязательно должно начинаться с (
        gl();
        if (c_type != LEX_SEMICOLON) {          // проверка условия в for (нужное; *; *)
            A();                           
            if (c_type != LEX_SEMICOLON) throw curr_lex;
        }
        gl();
        pl6 = poliz.size();                 // запоминание индекса ПОЛИЗа, куда после положится адрес перехода
        if (c_type != LEX_SEMICOLON) {      // проверка второго условия в for(*; нужное; *)
            A();
            if (c_type != LEX_SEMICOLON) throw curr_lex;
        }
        gl();
        pl4 = poliz.size();                 // запоминание инндекса элемента ПОЛИЗа, куда после будет положен адрес перехода
        poliz.push_back(Lex());             // кладем в ПОЛИЗ пусую лексему, чтобы потом заменить ее на нужный адрес перехода
        poliz.push_back(Lex(POLIZ_FGO));    // кладем в ПОЛИЗ операцию безусловного перехода
        pl5 = poliz.size();                 // запоминаем индекс элемента ПОЛИЗа, куда после будет положен адрес перехода
        poliz.push_back(Lex());             // кладем пустую лексему, чтобы после заменить ее на нужный адрес перехода
        poliz.push_back(Lex(POLIZ_GO));     // кладем в ПОЛИЗ команду безусловного перехода
        pl7 = poliz.size();                 // запоминаем индекс элемента ПОЛИЗа, куда позже положим адрес перехода
        if (c_type != LEX_SEMICOLON && c_type != LEX_CLOSEBRACKET) {    // проверка последнего условия в цикле for (*; *; нужное)
            A();                            
            if (c_type != LEX_CLOSEBRACKET) throw curr_lex;     // в конце условия for должна быть )
        }
        poliz.push_back(Lex(POLIZ_LABEL, pl6));         // кладем адрес выхода из ПОЛИЗа после условий цикла
        poliz.push_back(Lex(POLIZ_GO));                 // кладем в ПОЛИЗ операцию безусловного перехода
        poliz[pl5] = Lex(POLIZ_LABEL, poliz.size());    // кладем адрес перехода в нужное место (pl5) ПОЛИЗа
        if (c_type != LEX_CLOSEBRACKET) throw curr_lex;  // тело цикла должно заканчиваться }
        gl();
        S();                                        // заполняем тело цикла for
        poliz.push_back(Lex(POLIZ_LABEL, pl7));     // кладем в ПОЛИЗ адрес перехода на начало цикла
        poliz.push_back(Lex(POLIZ_GO));             // и кладем операцию безусловного перехода
        poliz[pl4] = Lex(POLIZ_LABEL, poliz.size());    // в нужное место (pl4) ПОЛИЗа кладем необходимый адрес перехода
        while (!stbreak.top().empty()) {            // заполняем адреса выходов по break если они есть
            poliz[stbreak.top().back()] = Lex(POLIZ_LABEL, poliz.size());
            stbreak.top().pop_back();
        }
        stbreak.pop();
    }// конец for
}

// функция, проверяющая наличие и верность присваивания в программе
// и вызывающая нижележащие функции, которые также вызывают функции ниже до F()
void Parser::A (){
    //cout << "A" << endl;
    OR();
    if (c_type == LEX_ASSIGN) {
        gl();
        A();            // возможность нескольких присваиваний
        eq_type();      // проверка типов переменных стоящих по разные стороны от знака =
        poliz.push_back(Lex(LEX_ASSIGN));       // кладем в стек знак =
    }
}

// функция, проверяющая наличие и верность операции or
void Parser::OR (){
    //cout << "OR" << endl;
    AND();
    if (c_type == LEX_OR) {
        st_lex.push(c_type);    // кладем в стек операций or, если такая операция встретилась
        gl();
        AND();
        check_op();        // проверка типов переменных, стоящих с разных сторон от or
    }
}

// функция, проверяющая наличие и верность операции and
void Parser::AND (){
    //cout << "AND" << endl;
    E();
    if (c_type == LEX_AND) {
        st_lex.push(c_type);    // кладем в стек операций and, если такая операция встретилась
        gl();
        E();
        check_op();         // проверка типов переменных, стоящих с разных сторон от and
    }
}

// функция, проверяющая наличие и верность операций сравнения
void Parser::E () {
    //cout << "E" << endl;
    PM();
    if (c_type == LEX_EQUAL  || c_type == LEX_LESS || c_type == LEX_GREAT ||
       c_type == LEX_LESSOREQUAL || c_type == LEX_GREATOREQUAL || c_type == LEX_NOTEQUAL) {
        st_lex.push(c_type);    // кладем операцию в стек операций, если такая встретилась
        gl();
        PM();
        check_op();         // проверка типов переменных, стоящих в с разных сторон операции
    }
}

// функция, проверяющая наличие и верность операций + и -
void Parser::PM () {
    //cout << "PM" << endl;
    MD();
    while (c_type == LEX_PLUS || c_type == LEX_MINUS) {
        st_lex.push(c_type);    // кладем операцию в стек операций
        gl();
        MD();
        check_op();        // проверяем верность типов операндов
    }
}

// функция, проверяющая наличие и верность операций * и /
void Parser::MD () {
    //cout << "MD" << endl;
    Fin();
    while (c_type == LEX_MULTIPLY || c_type == LEX_DIVIDE) {
        st_lex.push(c_type);    // кладем операцию в стек операций
        gl();
        Fin();       
        check_op();         // проверка верности типов операндов
    }
}

// функция, проверяющая знаки, скобки, строки, переменные и числа
// и заполняющая стек ПОЛИЗа
void Parser::Fin () {
    //cout << "Fin" << endl;
    if (c_type == LEX_ID) {         // проверка переменной
        check_id();        
        int buf2;
        buf2 = c_val;
        gl();
        if (c_type == LEX_ASSIGN) poliz.push_back(Lex(POLIZ_ADDRESS, buf2));    // при присваивании кладем в стек ПОЛИЗа адрес переменной
        else poliz.push_back(Lex(LEX_ID, buf2));           // если не присваивание, то кладем в стек ПОЛИЗа значение переменной
    }else if (c_type == LEX_NUM) {      // проверка числа
        st_lex.push(LEX_INT);
        poliz.push_back(curr_lex);      // кладем в стек ПОЛИЗа число
        gl();
    }else if (c_type == LEX_STR) {      // проверка строки
        st_lex.push(LEX_STR);
        poliz.push_back(curr_lex);      // кладем в стек ПОЛИЗа строку
        gl();
    }else if (c_type == LEX_TRUE) {     // проверка true
        st_lex.push(LEX_BOOL);
        poliz.push_back(Lex(LEX_TRUE, 1));      // кладем true в стек ПОЛИЗа
        gl();
    }else if (c_type == LEX_FALSE) {     // проверка false
        st_lex.push(LEX_BOOL);
        poliz.push_back(Lex(LEX_FALSE, 0));     // кладем в стек ПОЛИЗа false
        gl();
    }else if (c_type == LEX_NOT) {      // проверка not
        gl();
        Fin();      // рекурсивный вызов функции для дальнейшей проверки
        check_not();
    }else if (c_type == LEX_OPENBRACKET) {      // проверка происходящего в скобках
        gl();
        A();
        if (c_type == LEX_CLOSEBRACKET) gl();
        else throw curr_lex;            // ошибка, если не найдена закрывающая скобка )
    }else if (c_type == LEX_MINUS) {     // проверка унарного минуса
        Lex zero(LEX_NUM, 0);
        cout << zero;
        st_lex.push(LEX_INT);
        poliz.push_back(zero);          // кладем в стек 0 для изменения выражения справа от унарного минуса
    }else throw curr_lex;               // ошибка, при неверном типе лексемы
}

// считывание из стека номер строки таблицы TID и занесение информации о типе соответствующих переменных,
// о наличии их описаний и контроллирует повторное описание переменных
void Parser::dec (type_of_lex type) {       // внесение информации о типе идентификатора класса Ident
    int i;                                  // и идентификация переменной в программе
    while (!st_int.empty()) {
        from_st(st_int, i);
        if (TID[i].get_declare()) throw "Идентификация переменной второй раз";
        else{
            TID[i].put_declare();
            TID[i].put_type(type);
        }
    }
}

// проверка была ли переменная описана, если да то ее тип надо занести в стек
void Parser::check_id () {              // проверка идентификатора - был ли он инициализирован
    if (TID[c_val].get_declare())                   // если идектификатор инициализирован (с помощью dec), то 
        st_lex.push ( TID[c_val].get_type () );     // положить в st_lex его тип
    else throw "Не объявленный идентификатор";
}

// проверка соответствия типов операндов данной двуместной операции
void Parser::check_op () {      // проверка операции - возможно ли такое в программе или запрещено языком
    type_of_lex t1, t2, op, t = LEX_INT, r = LEX_BOOL;
    from_st(st_lex, t2);        // берем из стека операцию и операнды
    from_st(st_lex, op);
    from_st(st_lex, t1);
    if (t1 == t2 && t1 == LEX_STR) {    // случай для строки
        if (op == LEX_LESS || op == LEX_GREAT || op == LEX_EQUAL || op == LEX_NOTEQUAL) st_lex.push(LEX_BOOL);
        else if(op == LEX_PLUS || op == LEX_EQUAL) st_lex.push(LEX_STR);
        else throw "Неверные типы операндов"; 
    }else{              // сучай для числа
        if (op == LEX_PLUS || op == LEX_MINUS || op == LEX_MULTIPLY || op == LEX_DIVIDE) r = LEX_INT;
        if (op == LEX_OR || op == LEX_AND) t = LEX_BOOL;
        if (t1 == t2 && t1 == t) st_lex.push(r);        // кладем обратно в стек тип операции на случай нескольких операций
        else throw "Неверные типы операндов";
    }
    poliz.push_back(Lex(op));       // кладем лексему - операцию в ПОЛИЗ
}

void Parser::check_not () {     // проверка возможности применить операцию not
    if (st_lex.top() != LEX_BOOL) throw "Неверный тип для операции not";
    else poliz.push_back(Lex(LEX_NOT));
}

void Parser::eq_type () {       // проверка равенства тиров при присваивании
    type_of_lex t;
    from_st(st_lex, t);
    if (t != st_lex.top()) throw "Неверные типы операндов в присваивании";
}

void Parser::eq_bool () {       // проверка принадлежности к классу boolean
    if (st_lex.top() != LEX_BOOL) throw "Выражение не является типом boolean";
    st_lex.pop();
}

// проверка была ли внесена информация об индентификаторе класса в Ident
void Parser::check_id_in_read () {      
    if (!TID[c_val].get_declare()) throw "Идентификатор для read не объявлен";      // проверка идентификатора для оператора read
}

class Executer {
public:
    void execute ( vector<Lex> & poliz );
};
 
void Executer::execute ( vector<Lex> & poliz ) {
    Lex pc_el;                                          //текущий элемент ПОЛИЗа
    stack < int > args;                                 //сюда кладём численные константы
    stack <string> str_args;                            //сюда кладём строчные константы
    stack <type_of_lex> types;
    type_of_lex op1, op2;
    int flag_str = 0;                                   // 1 когда операнды - строки, 0 - иначе
    int i, j, index = 0, size = poliz.size();           //буферы для действий с операндами, индекс в ПОЛИЗе, размер ПОЛИЗа
    string s1, s2;
    string buf_str1;
    //print_TID();
    cout << "\n\n\n";
    //print_TSTRUC();
    while ( index < size ) {
        pc_el = poliz [ index ];
        //cout << pc_el << endl;
        //cout << TID[0].get_value() << i << j << endl;
        switch ( pc_el.get_type () ) {
            case LEX_TRUE: case LEX_FALSE: case LEX_NUM: case POLIZ_ADDRESS: case POLIZ_LABEL:
                //cout << "1" << endl;
                args.push ( pc_el.get_value () );
                if (pc_el.get_type() == POLIZ_ADDRESS)
                    types.push(TID[args.top()].get_type());
                else
                    types.push(pc_el.get_type());
                break;
 
            case LEX_STR:
                types.push(pc_el.get_type());
                i = pc_el.get_value();
                args.push(i);
                // str_args.push( TStr[i] );
                // flag_str = 1;
                break;

            case LEX_ID:
                 //cout << "ID" << endl;
                i = pc_el.get_value ();
                if (TID[i].get_type() == LEX_STRUCT)
                {
                    TID[i].put_value(i);
                    s1 = TID[i].get_name();
                    //cout << s1 << endl;
                    //cout << TID[i].get_value() << endl;
                    int k1 = check_struct_name(TID[i].get_strvalue());
                    for (int j = 0; j < TSTRUCT[k1].TIDS.size(); j++)
                    {
                        s1 = TID[i].get_name();
                        s2 = TSTRUCT[k1].TIDS[j].get_name();
                        s1 = s1 + "." + s2;
                        int i1 = check_TID(s1);
                        if (!TID[i1].get_assign())
                        {
                            throw "POLIZ: indefinite identifier++";
                        }
                    }
                    TID[i].put_assign(true);
                }
                if ( TID[i].get_assign () ) {
                    types.push(TID[i].get_type());
                    args.push ( TID[i].get_value () );
                    //cout << i << endl;
                    //cout << args.top() << " " << types.top() << "###\n";
                    break;
                }
                else
                  throw "POLIZ: indefinite identifier--";
                
 
            case LEX_NOT:
                 //cout << "NOT" << endl;
                from_st ( args, i );
                args.push( !i );
                break;
 
            case LEX_OR:
                 //cout << "OR" << endl;
                from_st ( args, i ); 
                from_st ( args, j );
                args.push ( j || i );
                break;
 
            case LEX_AND:
                 //cout << "AND" << endl;
                from_st ( args, i );
                from_st ( args, j );
                args.push ( j && i );
                break;
 
            case POLIZ_GO:
                 //cout << "GO" << endl;
                from_st ( args, i );
                index = i - 1;
                break;
 
            case POLIZ_FGO:
                 //cout << "FGO" << endl;
                from_st ( args, i );
                from_st ( args, j );
                if ( !j ) index = i - 1;
                break;
 
            case LEX_WRITE:
                // cout << 8 << endl;
                from_st ( args, j );
                from_st( types, op1);
                if (op1 == LEX_STR)
                {
                    cout << TStr[j] << endl;
                    flag_str = 0;
                }
                else
                    cout << j << endl;
                break;
 
            case LEX_READ:
                // cout << 9 << endl;
                int k;
                
                from_st( types, op1 );
                from_st ( args, i );
                if ( op1 == LEX_INT ) {
                    cout << "Input int value for " << TID[i].get_name () << endl;
                    cin >> k;
                    TID[i].put_value (k);
                    TID[i].put_assign (true);
                    break;
                }
                else if (op1 == LEX_STR)
                {
                    cout << "Input string value for " << TID[i].get_name() << endl;
                    cin >>  buf_str1;
                    j = put_str(buf_str1);
                    TID[i].put_value(j);
                    TID[i].put_assign(true);
                    break;
                }
                else {
                    string j;
                    while (1) {
                        cout << "Input boolean value (true or false) for " << TID[i].get_name() << endl;
                        cin >> j;
                        if ( j != "true" && j != "false" ) {
                            cout << "Error in input:true/false" << endl;
                            continue;
                        }
                        k = ( j == "true" ) ? 1 : 0;
                        TID[i].put_value (k);
                        TID[i].put_assign (true);
                        break;
                    }
                }

                // TID[i].put_value (k);
                // TID[i].put_assign (true);
                break;
 
            case LEX_PLUS:
                // cout << 10 << endl;
                from_st( types, op1);
                from_st( types, op2);
                if (op1 != LEX_STR && op2 != LEX_STR)
                {
                    from_st ( args, i );
                    from_st ( args, j );
                    args.push ( i + j );
                    types.push(LEX_INT);
                }
                else
                {
                    // from_st( str_args, s2 );
                    // from_st( str_args, s1 );
                    from_st ( args, i );
                    from_st ( args, j );
                    int ch = put_str(TStr[j] + TStr[i]);
                    //str_args.push(s1 + s2);
                    args.push(ch);
                    types.push(LEX_STR);
                    
                }
                break;
 
            case LEX_MULTIPLY:
               // cout << 11 << endl;
                from_st ( args, i );
                from_st ( args, j );
                args.push ( i * j );
                break;
 
            case LEX_MINUS:
                //cout << 12 << endl;
                from_st ( args, i );
                from_st ( args, j );
                args.push ( j - i );
                break;
 
            case LEX_DIVIDE:
                //cout << 13 << endl;
                from_st ( args, i );
                from_st ( args, j );
                if (i) {
                    args.push ( j / i );
                    break;
                }
                else
                    throw "POLIZ:divide by zero";
 
            case LEX_EQUAL:
                //cout << 14 << endl;
                from_st ( args, i );
                from_st ( args, j );
                args.push ( i == j );
                break;
 
            case LEX_LESS:
               // cout << 15 << endl;
                from_st ( args, i );
                from_st ( args, j );
                args.push ( j < i );
                break;
 
            case LEX_GREAT:
                //cout << 16 << endl;
                from_st ( args, i );
                from_st ( args, j );
                args.push ( j > i );
                break;
 
            case LEX_LESSOREQUAL:
                //cout << 17 << endl;
                from_st ( args, i );
                from_st ( args, j );
                args.push ( j <= i );
                break;
 
            case LEX_GREATOREQUAL:
                //cout << 19 << endl;
                from_st ( args, i );
                from_st ( args, j );
                args.push ( j >= i );
                break;
 
            case LEX_NOTEQUAL:
                //cout << 20 << endl;
                from_st ( args, i );
                from_st ( args, j );
                args.push ( j != i );
                break;
 
            case LEX_ASSIGN:
                //cout << 21 << endl;
                from_st ( args, i );
                from_st ( args, j );
                from_st( types, op1);
                from_st( types, op2);
                if (op1 == LEX_STRUCT || op2 == LEX_STRUCT)
                {
                    //cout << i << endl;
                    if (TID[i].get_strvalue() != TID[j].get_strvalue())
                    {
                        throw "Разные типы структур";
                    }
                    int k1 = check_struct_name(TID[i].get_strvalue());
                    for (int l = 0; l < TSTRUCT[k1].TIDS.size(); l++)
                    {
                        s1 = TID[j].get_name();
                        //cout << s1 << endl;
                        s2 = TID[i].get_name();
                        s1 = s1 + "." + TSTRUCT[k1].TIDS[l].get_name();         
                        s2 = s2 + "." + TSTRUCT[k1].TIDS[l].get_name();
                        //cout << s1 << endl;
                        int i0, j0;
                        i0 = check_TID(s2);
                        j0 = check_TID(s1);
                        TID[j0].put_value(TID[i0].get_value());
                        TID[j0].put_assign(true);
                    }
                }
                // cout << i << " " << j << endl;
                TID[j].put_value (i);
                //cout << j << " j" << endl;
                TID[j].put_assign (true); 
                flag_str = 0;
                break;
 
            default:
                throw "POLIZ: unexpected elem";
        }//end of switch
        ++index;
        
    };//end of while
    cout << "Finish of executing!!!" << endl;
}
 
class Interpretator {
    Parser   pars;
    Executer E;
public:
    Interpretator ( const char* program ): pars (program) {}
    void     interpretation ();
};
 
void Interpretator::interpretation () {
    pars.analyze ();
    E.execute ( pars.poliz );
}

int main(){   
    try{
        Interpretator I ( "test.txt" );
        I.interpretation ();
        return 0;
    }catch(char c){
        cout << "Встречен неизвестный символ " << c << "\tСтрока " << line_num <<  endl;
    }catch(Lex l){
        cout << "Встречена неизвестная лексема " << l << "\tСтрока " << line_num << endl;
    }catch(const char* str){
        cout << str << "\tСтрока " << line_num << endl;
    }
    return 0;
}