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

## 3. Operation reload as friend

- 成员函数不能满足使用要求
- 普通函数，又不能访问类的私有成员

```cpp
class Complex
{
        double real, imag;
    public:
        Complex(double r, double i): real(r), imag(i){};
        Complex operator+(double r);
};
Complex Complex::operator+(double r)
{
    return Complex( real + r, imag);
}
```

- 经过上述重载后

```cpp
Complex c;
c = c + 5; // Have defination，equal to c = c.operator + (5);
c = 5 + c; // complie error
```

- In order to make the expression above correct, need reload + as general function

```cpp
Complex operator+(double r, const Complex & c)
{
    return Complex(c.real + r, c.imag);
}
```

- General function can't visit private member, so we load opeartor + as friend function

```cpp
class Complex
{
        double real, imag;
    public:
        Complex( double r, double i): real(r), imag(i){};
        Complex operator+(double r);
        friend Complex operator +(double r, const Complex &c);
};
```

## 4. Example of operator reload

```cpp
int main()
{
    CArray a; // The beginning array is empty
    for (int i=0; i<5; ++i)
        a.push_back(i); // need dynamic locate memory
    CArray a2,a3;
    a2 = a;// need reload
    for(int i=0; i<a.length();++i)
        cout<<a2[i]<<"";// need reload
    a2 = a3; // a2 is empty
    for (int i=0; i<a2.length();++i)//a2.length() return 0
        cout<<a2[i]<<"";
    cout<<endl;
    a[3]=100;
    CArray a4(a); // Need write copy construct function
    for(int i=0; i<a4.length();++i)
        cout<<a4[i]<<"";
    return 0;
}
```

- How to define the CArray class to satisfy the above

```cpp
class CArray
{
        int size; //# of elements
        int *ptr;// ptr to array
    public:
        CArray(int s=0)
        CArray(CArray &a);
        ~CArray();
        void push_back(int v);
        CArray & operator = (const CArray &a);

        int length(){ return size;}

        int & CArray::operator[](int i)
        {
            return ptr[i];
        }
};

CArray::CArray(int s):size(s)
{
    if( s==0)
        ptr = NULL;
    else
        ptr = new int[s];
}

CArray::CArray(CArray &a)
{
    if(!a.ptr)
    {
        ptr =NULL;
        size = 0;
        return;
    }
    ptr = new int[a.size];
    memcpy(ptr, a.ptr, sizeof(int ) *a.size);
    size = a.size;
}

CArray::~CArray()
{
    if(ptr) delete []ptr;
}

CArray &CArray::operator = (const CArray &a)
{
    if(ptr == a.ptr)
        return *this;
    if(a.ptr==NULL)
    {
        if(ptr) delete []ptr;
        ptr = NULL;
        size = 0;
        return *this;
    }

    if(size < a.size>)// if original size is large enough, do not need to resize
    {
        if(ptr)
            delete [] ptr;
        ptr = new int[a.size];
    }
    memcpy(ptr, a.ptr, sizeof(int)*a.size);
    size = a.size;
    return *this;
} // CArray &CArray::operator = (const CArray &a)

void CArray::push_back(int v)
{
    if(ptr)
    {
        int *tmpPtr = new int[size+1];
        memcpy(tmpPtr, ptr, sizeof(int)*size);
        delete [] ptr;
        ptr = tmpPtr
    }
    else
        ptr = new int[1];
    ptr[size++] = v;
}

```

## 5. OStream operator reload

```cpp
ostream &ostream::operator<<(int n)
{
    return *this;
}

ostream &ostream::operator<<(const char *s)
{
    return *this;
}


```
