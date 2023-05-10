#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define BUFSIZE 256
enum type_of_lex
{
    LEX_NULL, /*0*/
    LEX_AND,
    LEX_BOOL,
    LEX_DO,
    LEX_ELSE,
    LEX_IF,
    LEX_FALSE,
    LEX_INT,
    LEX_NOT,
    LEX_OR,
    LEX_PROGRAM, /*10*/
    LEX_READ,
    LEX_STRING,
    LEX_TRUE,
    LEX_GOTO,
    LEX_BREAK,
    LEX_WHILE,
    LEX_WRITE,
    LEX_FOR,     /*18*/
    TYPE_STRUCT, /*19*/
    LEX_QUOTE,   /*20*/
    LEX_BEGIN,   /*21*/  //'{'
    LEX_END,
    LEX_SEMICOLON,
    LEX_COMMA,
    LEX_COLON,
    LEX_NEQ,   //'!='
    LEX_ASSIGN,
    LEX_LPAREN, /*28*/
    LEX_RPAREN,
    LEX_EQ,     //"="
    LEX_LSS,
    LEX_GTR,
    LEX_PLUS,
    LEX_MINUS,
    LEX_TIMES,
    LEX_SLASH,
    LEX_LEQ,
    LEX_GEQ,       /*38*/
    LEX_PERCENT,   
    LEX_NUM,       /*40*/
    LEX_STR,       /*41*/
    LEX_ID,        
    POLIZ_LABEL,   
    POLIZ_ADDRESS, 
    POLIZ_GO,      
    POLIZ_FGO,     
    LV_STRING,     
    LV_INT,        
    LV_BOOL        
};

class Ident //класс работающий с идентификаторами составляется TID таблица идентификаторов
{
    std::string name;
    std::string string_value;
    bool declare;
    type_of_lex type;
    bool assign;
    int value;

public:
    Ident()
    {
        declare = false;
        assign = false;
    }
    bool operator==(const std::string &s) const
    {
        return name == s;
    }
    Ident(const std::string new_str)
    {
        name = new_str;
        declare = false;
        assign = false;
    }
    std::string get_name() const
    {
        return name;
    }
    void put_name(std::string new_name)
    {
        name = new_name;
    }
    bool get_declare() const
    {
        return declare;
    }
    void put_declare()
    {
        declare = true;
    }
    type_of_lex get_type() const
    {
        return type;
    }
    void put_type(type_of_lex t)
    {
        type = t;
    }
    bool get_assign() const
    {
        return assign;
    }
    void put_assign()
    {
        assign = true;
    }
    int get_value() const
    {
        return value;
    }
    void put_value(int val)
    {
        value = val;
    }
    std::string get_str_val() const
    {
        return string_value;
    }
    void put_str_val(std::string str)
    {
        string_value = str;
    }
};




class Lex  //TODO класс, хранящий в себе лексему, в данный момент только возвращается в виде временного объекта планируется обрабатывать лексемы
{
    type_of_lex t_lex;
    int v_lex;
    std::string s_lex;

public:
    Lex(type_of_lex t = LEX_NULL, int v = 0) : t_lex(t), v_lex(v), s_lex("") {}
    Lex(type_of_lex t, std::string str1, int v = 0) : t_lex(t), v_lex(v), s_lex(str1) {}
    type_of_lex get_type() const
    {
        return t_lex;
    }
    int get_value() const
    {
        return v_lex;
    }
    std::string get_str() const
    {
        return s_lex;
    }
    void put_type(type_of_lex t)
    {
        t_lex = t;
    }
    friend std::ostream &operator<<(std::ostream &s, Lex l);
};



class Scanner //сканирует лексемы и возвращает объект Lex
{
    FILE *fp;
    char c;
    int search(const std::string buf, const char **list);
    void gc();

public:
    int row, column;
    static int balance;//баланс скобок
    // bool st_start = false;
    static bool lex_flag;//флаг того что лексер закончил работу
    static const char *TW[], *TD[];//определены ниже таблицы служебных слов и ограничителей
    Scanner(const char *program); // создание класса сканер, подаем на вход имя файла
    Lex get_lex();
    ~Scanner() { fclose(fp); }
};
std::vector<Ident> TID; // таблица идентификаторов анализируемой программы
int Scanner::balance = 0;
bool Scanner::lex_flag = true;

// таблица служебных слов модельного языка
const char *
    Scanner::TW[] = {"" /*0*/, "and" /*1*/, "bool" /*2*/, "do" /*3*/, "else" /*4*/, "if" /*5*/, "false" /*6*/, "int" /*7*/, "not" /*8*/, "or" /*9*/, "program" /*10*/,
                     "read" /*11*/, "string" /*12*/, "true" /*13*/, "goto" /*14*/, "break" /*15*/, "while" /*16*/, "write" /*17*/, "for" /*18*/, "struct" /*19*/, NULL};

// таблица ограничителей модельного языка
const char *
    Scanner::TD[] = {"\"" /*0*/, "{" /*1*/, "}" /*2*/, ";" /*3*/, "," /*4*/, ":" /*5*/, "!=" /*6*/, "=" /*7*/, "(" /*8*/, ")" /*9*/,
                     "==" /*10*/, "<" /*11*/, ">" /*12*/, "+" /*13*/, "-" /*14*/, "*" /*15*/, "/" /*16*/, "<=" /*17*/, ">=" /*18*/, "%" /*19*/, NULL};

int Scanner::search(const std::string buf, const char **list)//функция ищет служебное слово или ограничитель в TW или TD
{
    int i = 0;
    while (list[i])
    {
        if (buf == list[i])
            return i;
        ++i;
    }
    return 0;
}

void Scanner::gc()
{
    c = fgetc(fp);
    if ((c == EOF) && (balance != 0))//пока баланс не будет равен 0
    {
        char s[BUFSIZE];
        sprintf(s, "%s (%d): Не хватает закрывающей скобки. Строка %d, cтолбец %d\n", __FILE__, __LINE__, row, column);
        std::string str = std::string(s);
        throw str;
    }
}

Scanner::Scanner(const char *program) : row(1), column(0)
{
    if (!(fp = fopen(program, "r")))
    {
        char s[BUFSIZE];
        sprintf(s, "%s (%d): Не удалось открыть файл\n", __FILE__, __LINE__);
        std::string str = std::string(s);
        throw str;
    }
}

int put(const std::string &buf)
{
    std::vector<Ident>::iterator k;

    if ((k = find(TID.begin(), TID.end(), buf)) != TID.end())
        return k - TID.begin();
    TID.push_back(Ident(buf));
    return TID.size() - 1;
}

Lex Scanner::get_lex()
{
    enum state
    {
        H, //начальное состояние
        IDENT, 
        ST_IDENT,//!пока лишнее
        NUMB, //состояние считывания чисел
        SLASH, //либо деление либо комментарий
        COM, //начало коментария
        COM_TIMES, //ждем конец коментария
        ALE, // знаки сравнения =<>
        NEQ, //"!=""
        STR, //состояние считывания строки
        START,//!пока лишнее
        FINISH//!=пока лишнее
    };
    int d, j;
    string buf;//хранит в себе лексему до момента ее распознавания в одном из состояний
    string buf1;//!пока лишнее
    state CS = H;
    do
    {
        column++;
        gc(); //проверка баланса скобок и конца файла
        switch (CS)
        {
        case H:
            if (c == ' ' || c == '\n' || c == '\r' || c == '\t')//пропускаем лишние символы или если нашли \n то переходи на новую строку
            {
                if (c == '\n')
                {
                    column = 0;
                    row++;
                }
            }
            else if (c == '{')
            {
                balance++;
                return Lex(LEX_BEGIN, '{');
            }
            else if (c == '}')
            {
                // if (st_start == true)
                // {
                //     st_start = false;
                // }
                balance--;
                cout<<balance<<endl;
                if (balance < 0)
                {
                    char s[BUFSIZE];
                    sprintf(s, "%s (%d): Непонятная закрывающая скобка. Строка %d, cтолбец %d\n", __FILE__, __LINE__, row, column);
                    std::string str = std::string(s);
                    throw str;
                }
                if ((balance == 0) && (lex_flag))
                {
                    string s = "OK_LETS_GO";
                    lex_flag = false;
                    throw s;
                }
                return Lex(LEX_END, '}');
            }
            else if (islower(c))
            {
                buf.push_back(c);
                CS = IDENT;
            }
            else if (isdigit(c))
            {
                d = c - '0';
                CS = NUMB;
            }
            else if (c == '/')
            {
                buf.push_back(c);
                CS = SLASH;
            }
            else if (c == '=' || c == '<' || c == '>')
            {
                buf.push_back(c);
                CS = ALE;
            }
            else if (c == '!')
            {
                buf.push_back(c);
                CS = NEQ;
            }
            else if (c == '"')
            {
                CS = STR;
            }
            else
            {
                buf.push_back(c);
                if ((j = search(buf, TD)))
                {
                    return Lex((type_of_lex)(j + (int)LEX_QUOTE), j);
                }
            }
            break;
        case IDENT:
            if (isalpha(c) || isdigit(c) || c == '.')
            {
                buf.push_back(c);
            }
            else
            {
                ungetc(c, fp);
                column--;
                if ((j = search(buf, TW)))
                {
                    return Lex((type_of_lex)j, j);
                }
                else
                {
                    j = put(buf);//TODO лишние символы
                    return Lex(LEX_ID, j);
                }
            }
            break;
        case NUMB:
            if (isdigit(c))
            {
                d = d * 10 + (c - '0');
            }
            else
            {
                ungetc(c, fp);
                column--;
                return Lex(LEX_NUM, d);
            }
            break;
        case SLASH:
            if (c == '*')
            {
                CS = COM;
                buf.pop_back();
            }
            else
            {
                ungetc(c, fp);
                column--;
                j = search(buf, TD);
                return Lex(LEX_SLASH, j);
            }
            break;
        case COM:
            if (c == '*')
                CS = COM_TIMES;
            break;
        case COM_TIMES:
            if (c == '/')
                CS = H;
            else
                CS = COM;
            break;
        case ALE:
            if (c == '=')
            {
                buf.push_back(c);
                j = search(buf, TD);
                return Lex((type_of_lex)(j + (int)LEX_QUOTE), j);
            }
            else
            {
                ungetc(c, fp);
                column--;
                j = search(buf, TD);
                return Lex((type_of_lex)(j + (int)LEX_QUOTE), j);
            }
            break;
        case NEQ:
            if (c == '=')
            {
                buf.push_back(c);
                j = search(buf, TD);
                return Lex(LEX_NEQ, j);
            }
            else
            {
                char s[BUFSIZE];
                sprintf(s, "%s (%d): После '!' должно идти '='. Строка %d, cтолбец %d\n", __FILE__, __LINE__, row, column);
                string str = string(s);
                throw str;
            }
            break;
        case STR:
            if (c != '"')
            {
                buf.push_back(c);
            }
            else
                return Lex(LEX_STR, buf);
            break;
        } // end switch
    } while (true);
}
ostream &operator<<(ostream &s, Lex l)
{
    string t;
    if (l.t_lex <= TYPE_STRUCT)
        t = Scanner::TW[l.t_lex];
    else if (l.t_lex >= LEX_QUOTE && l.t_lex <= LEX_PERCENT)
        t = Scanner::TD[l.t_lex - LEX_QUOTE];
    else if (l.t_lex == LEX_NUM)
        t = "NUMB";
    else if (l.t_lex == LEX_ID)
        t = TID[l.v_lex].get_name();
    else if (l.t_lex == LEX_STR)
    {
        s << "STR," << l.s_lex << endl;
        return s;
    }
    else if (l.t_lex == POLIZ_LABEL)
        t = "Label";
    else if (l.t_lex == POLIZ_ADDRESS)
        t = "Addr";
    else if (l.t_lex == POLIZ_GO)
        t = "!";
    else if (l.t_lex == POLIZ_FGO)
        t = "!F";
    else
    {
        cout << l;
        char s[BUFSIZE];
        sprintf(s, "%s (%d): Ошибка печати, недопустимая лексема\n", __FILE__, __LINE__);
        string str = string(s);
        throw str;
    }
    s << t << ',' << l.v_lex << endl;
    return s;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Дайте на вход имя файла" << endl;
        exit(1);
    }

    Scanner scan(argv[1]);
    while (1)
    {
        try
        {
            Lex l1 = scan.get_lex();
            // cout << l1.get_value();
            cout << l1;
        }
        catch (string str)
        {
            if (str == "OK_LETS_GO")
            {
                Lex l2 = Lex(LEX_END, '}');
                cout << l2;
                cout << str << endl;
                break;
            }
            else
            {
                cout << str << endl;
                return 0;
            }
        }
    }
    return 0;
}