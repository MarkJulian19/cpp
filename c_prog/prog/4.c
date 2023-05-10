union U {
    int i;
    double d;
    char c;
};

int F(int n){
    union U{
        int i;
        char c[4];
    };
    char cv;
    union U U1={n};
    cv = U.c[0];
    U.c[0]=U.c[3];
    U.c[3]=cv;
    return U.i;
}
struct S{
    int d1:1;
    unsigned int d2:2;
    _Bool d3:1;
    int  :2;
    int d4:1;
}fl;
.тип
.клсс памяти
auto стек
register регистер нельзя обращаться по памяти
static сегмент данных программы int G=5;
extern 
int G;
int f(int x);
int main(){
    int G;
    {int i; 
    }
}
int f(int x){static int n=0;}
