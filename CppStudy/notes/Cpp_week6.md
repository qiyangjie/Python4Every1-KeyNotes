# Cpp Note week 6

## 1. Virtual function and Polymorphism

### 1.1 Virtual function

```cpp
class base
{
    virtual int get();
};

int base::get(){}
```

The keyword "virtual" can be only used in class definition.

### 1.2 Polymorphism

- Type 1

```cpp
class CBase
{
    public:
        virtual void SomeVirtualFunction(){}
};

class Cderived:public CBase
{
    public:
     virtual void SomeVirtualFunction(){}
};

int main()
{
    CDerived ODerived;
    CBase *p = & Oderived;
    p -> SomeVirtualFunction();
    return 0;
}
```

- Type 2

```cpp
class CBase
{
    public:
        virtual void SomeVirtualFunction(){}
};
class CDerived:public CBase
{
    public:
        virtual void SomeVirtualFunction(){}
};
int main()
{
    CDerived ODerived;
    CBase &r = ODerived;
    r.SomeVirtualFunction();
    return 0;
}
```

- Example

```cpp
class A
{
    public:
        virtual void Print()
        {
            cout <<"A::Print"<<endl;
        }
};

class B:public A
{
    public:
    virtual void Print()
    {
        cout<<"B::Print"<<endl;
    }
};

class D:public A
{
    public:
    virtual void Print()
    {
        cout<<"D::Print"<<endl;
    }
};

class E:public B
{}
    virtual void Print()
    {
        cout<<"E::Print"<<endl;
    }
};

int main()
{
    A a;
    B b;
    E e;
    D d;

    A *pa = &a;
    B *pb = &b;
    D *pd = &d;
    E *pe = &e;

    pa -> Print(); // A:Print
    pa = pb;
    pa =>Print(); // B:Print
    pa = pd;
    pa ->Print();//D::Print
    pa = pe;
    pa->Print(); // E::Print
    return 0;
}
```

## 2. Example of Polymorphism

Check the slides.

## 3. More example

## 4. Dynamic Binding

## 5. Virtual deconstruction file

## 6. Pure virtual function
