# Cpp Coursera -- Week 4

## 1. Operation Reload

Operation reload is a special pattern of function reload. Operation can be reload as general function and also can be reload as member function.

- Reload as general function situation.

```cpp
class Complex
{
    public:
        Complex( double r=0.0, double i=0.0)
        {
            real =r;
            imaginary =i;
        }
        double real;
        double imaginary;
};

Complex operator+(const Complex &a, const Complex &b)
{
    return Complex(a.real+b.real, a.imaginary + b.imaginary);
}

Complex a(1,2), b(2,3), c;

c= a + b;

```

- Reload as member function situation.

```cpp
class Complex
{
    public:
        Complex(double r = 0.0, double m = 0.0):
            real(r), imaginary(m){}
        Complex operator+(const Complex &);
        Complex operator-(const Complex &);
    private:
        double real;
        double imaginary;
};

Complex Complex::operator+(const Complex & operand2)
{
    return Complex(real + operand2.real,
                    imaginary + operand2.imaginary);
}

Complex Complex::operator-(const Complex & operand2)
{
    return Complex(real - operand2.real,
                    imaginary - operand2.imaginary);
}

int main(){
    Complex x,y(4.3, 8.2), z(3.3, 1.1);
    x = y+z;
    x = y-z;
    return 0;
}
```

## 2. Assignment operation reload

- The type of data in two sides of assignment operation can be different.

- Assginment operation can only reload as member function.

- Example

```cpp
class String
{
    private:
        char *str;
    public:
        String(): str(NULL){}
        const char *c_str(){return str;}
        char *operator = (const char *s);
        ~String();
}

char *String::operator = (const char *s)
{
    if(str) delete [] str;
    if(s)
    {
        str = new char[strlen(s)+1];
        strcpy(str,s);
    }
    else
        str = NULL;
    return str;
}

String::~String()
{
    if(str) delete [] str;
};

int main()
{
    String s;
    s = "Good Luck,";
    cout << s.c_str()<< endl;
    // string s2 = "hello!"; // This will call construction function, not operation
    s = "Shenzhou 8!";
    cout<<s.c_str()<<endl;
    return 0;
}
```

- Shallow copy
- Deep copy

```cpp
String & operator = (const String &s)
{
    if(str) delete [] str;
    str = new char[strlen(s.str)+1];
    strcpy(str,s.str);
    return *this;
}
```

- Current object assgin to itself

```cpp
String & String::operator = (const String &s)
{
    if(str == s.str) return *this;
    if(str) delete [] str;
    if(s.str)
    {
        str = new char[strlen(s.str)+1];
        ctrcpy(str, s.str)
    }
    else
        str = NULL;
    return *this;
}
```

- Return type of operation

-- void is bad choice

-- String is not good

-- When reload operation, do the best to keep the original stype of the operation.

- 为String类编写复制构造函数时，会面临和"="同样的问题，用同样的方法处理

```cpp
String::String(String & s)
{
    if(s.str)
    {
        str = new char[strlen(s.str)+1];
        strcpy(str,s.str);
    }
    else
        str = NULL;
}
```
