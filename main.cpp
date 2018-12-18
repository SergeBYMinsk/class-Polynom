//
//  main.cpp
//  ООП_КОНТРОЛЬНАЯ_2_v3
//
//  Created by Sergey Sterlikov on 12/4/18.
//  Copyright © 2018 Sergey Sterlikov. All rights reserved.
//

#include <iostream>
#include <memory.h>
#include <math.h>
using namespace std;

//Разработать класс «Многочлен» – Polynom степени n. Написать несколько конструкторов, в том числе конструктор копирования. Реализовать методы для вычисления значения полинома; сложения, вычитания и умножения полиномов. Перегрузить операции сложения, вычитания, умножения, инкремента, декремента, индексирования, присваивания. Создать массив объектов класса. Передать его в функцию, вычисляющую сумму полиномов массива и возвращающую полином результат, который выводится на экран в головной программе.
                                            //класс Polynom
class Polynom
{
private:
    unsigned int deg;                    //степень полинома
    double *koef;                       //указатель на массив коэффициентов полинома
                                        //koef[i] - коэффициент при i-й степени,
                                        //koef[0] - коэффициент при нулевой степени
    void CorrectDeg();                  // функция корректировки степени полинома
    
public:
    Polynom();                                           //конструктор без параметров
    Polynom(unsigned int, double*);                     //конструктор с параметрами
    Polynom(const Polynom &);                            //копирующий конструктор
    ~Polynom();                                             //деструктор
    
    unsigned int GetDeg();                          //функция получения степени полинома
    double GetKoef(unsigned int);                   //функция получения коэффициента при i-й степени
    unsigned int SetKoef(double, unsigned int);      //функция задания коэффициента при i-й степени, возвращает степень полинома
    void CalculateValue(double x);                    //вычислить значение полинома
    Polynom operator + (const Polynom &);            //оператор сложения двух полиномов
    Polynom operator - (const Polynom &);            //оператор вычитания двух полиномов
    Polynom operator = (const Polynom &);                //оператор присваивания
    friend Polynom MultConst(double, Polynom &);        //дружественная функция умножения полинома на константу
    void InputPolynom();                                 //функция ввода полинома
    void OutputPolynom();                                    //функция вывода полинома
};
                        // конструктор без параметров: создается полином нулевой степени с коэффициентом при нулевой степени равным нулю
Polynom::Polynom()
{
    deg=0;
    koef=new double[deg+1];
    koef[0]=0.0;
}
                                                // конструктор с параметрами
                                                // new_deg - степень создаваемого полинома
                                                // newkoef - указатель на new_deg+1 - элементный массив с коэффициентами
                                                //    полинома, где newkoef[i] - коффициент при i-й степени
                                                //   и newkoef[0] - коэффициент при нулевой степени
                                                // В результате степень полинома будет наибольшим номером ненулевого
                                                // элемента массива new_koef и меньше или равна new_deg (по определению степени полинома)
Polynom::Polynom(unsigned int new_deg, double *new_koef)
{
    deg=0;
    for(int i=0;i<=new_deg;i++)
        if(new_koef[i]!=0) deg=i;                               //инициализация переменной степени
    koef=new double[deg+1];
    for(int i=0;i<=deg;i++)
        koef[i]=new_koef[i];                                    //инициализация массива коэффициентов
}
                                                                //копирующий конструктор
Polynom::Polynom(const Polynom &f)
{
    deg=f.deg;
    koef=new double[deg+1];
    for(int i=0;i<=deg;i++)
        koef[i]=f.koef[i];
}
                                                                //деструктор
Polynom::~Polynom()
{
    delete[] koef;
}
                                                            // функция получения степени полинома
unsigned int Polynom::GetDeg()
{
    return deg;
}
                                                        // функция получения коэффициента при i-й степени
double Polynom::GetKoef(unsigned int i)
{
    if(i<=deg)
        return koef[i];
    else
        return 0.0;
}
                                                                // функция задания коэффициента при i-й степени
unsigned int Polynom::SetKoef(double new_koef, unsigned int i)
{
    if(i<=deg)
        koef[i]=new_koef;
    else
        return deg;
    CorrectDeg();
    return deg;
}
                                    //*************** CalculateValue *****************************
void Polynom::CalculateValue(double x)
{
    double s=0;
    int i;
    for(s=koef[0],i=1;i<=deg;i++)
        s=s+koef[i]*pow(x,i);
    cout<<"f("<<x<<") = ";
    cout<< s <<endl;
}
                                            //оператор сложения двух полиномов
Polynom Polynom::operator + (const Polynom &t)
{
    int i;
    Polynom *result;
    if(deg>=t.deg)
    {                                              //если степень первого полинома больше степени второго
        result=new Polynom(deg,koef);
        for(i=0;i<=t.deg;i++)
            result->koef[i]=result->koef[i]+t.koef[i];
    }
    else
    {                                                      //если степень второго полинома больше степень первого
        result=new Polynom(t.deg,t.koef);
        for(i=0;i<=deg;i++)
            result->koef[i]=result->koef[i]+koef[i];
    }
    result->CorrectDeg();
    return *result;
}
                                                                //оператор вычитания двух полиномов
Polynom Polynom::operator - (const Polynom &t)
{
    int i;
    Polynom *result;
    if(deg>=t.deg)
    {                                                       //если степень первого полинома больше степени второго
        result=new Polynom(deg,koef);
        for(i=0;i<=t.deg;i++)
        {
            if (result->koef[i] >= t.koef[i])
                result->koef[i]=result->koef[i]-t.koef[i];
            else
                result->koef[i]=t.koef[i] - result->koef[i];
        }
    }
    else
    {                                                    //если степень второго полинома больше степень первого
        result=new Polynom(t.deg,t.koef);
        for(i=0;i<=deg;i++)
        {
            if (result->koef[i] >= t.koef[i])
                result->koef[i]=result->koef[i]-t.koef[i];
            else
                result->koef[i]=t.koef[i] - result->koef[i];
        }
    }
    result->CorrectDeg();
    return *result;
}
                                                        //оператор присваивания
Polynom Polynom::operator = (const Polynom &t)
{
    deg=t.deg;
    delete[] koef;
    koef=new double[deg+1];
    for(int i=0;i<=deg;i++)
        koef[i]=t.koef[i];
    return *this;
}
                                                    //оператор умножения числа на полином
Polynom operator * (double K, Polynom &t)
{
    return MultConst(K,t);
}
                                                        //оператор умножения полинома на число
Polynom operator * (Polynom &t, double K)
{
    return MultConst(K,t);
}
                                                    //функция реализующая умножение полинома на число
Polynom MultConst(double K, Polynom &t)
{
    if(K==0)
    {
        Polynom result;
        return result;
    }
    else
    {
        int deg=t.deg;
        double *tmp_koef=new double[deg+1];
        for(int i=0;i<=deg;i++)
            tmp_koef[i]=K*t.koef[i];
        Polynom result(deg,tmp_koef);
        delete[] tmp_koef;
        return result;
    }
}
                                            // функция корректировки степени полинома: коэффициент
                                            // при максимальной степени должен быть ненулевым
void Polynom::CorrectDeg()
{
    if(koef[deg]==0)
    {
        do
        {
            deg--;
        }
        while(deg && koef[deg]==0);
    }
}
                                            //функция ввода полинома
void Polynom::InputPolynom()
{
    cout << "Введите степень полинома: ";
    cin >> deg;
    delete[] koef;
    koef=new double[deg+1];
    for(int i=0;i<deg;i++)
    {
        cout << "K" << i << " = ";
        cin >> koef[i];
    }
    do
    {
        cout << "K" << deg << " = ";
        cin >> koef[deg];
        if(koef[deg]==0)
            cout << "K" << deg << " не может быть нулевым!!!\n";
    }
    while(!koef[deg]);
}

void Polynom::OutputPolynom()
{
    if(koef[deg]==1)
        cout << "X^" << deg;
    else if(koef[deg]==-1)
        cout << "-X^" << deg;
    else
        cout << koef[deg] << "X^" << deg;
    
    for(int i=deg-1;i>0;i--)
    {
        if(koef[i]>0)
        {
            if(koef[i]==1)
                cout << " + " << "X^" << i;
            else
                cout << " + " << koef[i] << "X^" << i;
        }
        else
            if (koef[i]<0)
            {
                if (koef[i]==-1)
                    cout << " - " << "X^" << i;
                else
                    cout << " - " << (-1)*koef[i] << "X^" << i;
            }
    }
    if(koef[0]>0)
        cout << " + " << koef[0] << "\n";
    else if(koef[0]<0)
        cout << " - " << (-1)*koef[0] << "\n";
}

int main()
{
    int choice;
    Polynom P1, P2;
    cout << "Введите полином 1:" << endl;
    P1.InputPolynom();
    cout << "Введите полином 2:" << endl;
    P2.InputPolynom();
    P1.OutputPolynom();
    P2.OutputPolynom();
    
    while (1)
    {
        cout << "\n****** Меню ******" << endl;
        cout << "1: Сложение\n2: Вычитание\n3: Умножение\n4: Вычисление\n5: Вывод полиномов\n0: Exit" << endl;
        cin >> choice;
        switch (choice)
        {
            case 1:
                cout <<  "\n--------------- Сложение полиномов ---------------\n";
                P1=P1+P2;
                P1.OutputPolynom();
                break;
            case 2:
                cout << "\n------------- Вычитание полиномов -------------\n";
                P1=P1-P2;
                P1.OutputPolynom();
                break;
            case 3:
                cout << "\n------------- Умножение полинома 1 на число -------------\n";
                double G;
                cout <<"Введите число:";
                cin >> G;
                P1=P1*G;
                P1.OutputPolynom();
                break;
            case 4:
                cout << "\n------------- Вычисление полинома 1-------------\n";
                double K;
                cout <<"Введите число Х = ";
                cin >> K;
                P1.CalculateValue(K);
                break;
            case 5:
                cout << "\n------------- Вывод полиномов 1 и 2-------------\n";
                P1.OutputPolynom();
                P2.OutputPolynom();
                break;
            case 0:
                cout << "Выход!!!" << endl;
                exit(0);
        }
    }
    return 0;
}
