#include <iostream>
#include <cstring>
#include <vector>
#include <typeinfo>
#include <set>
#include <iterator>

using namespace std;

class Locuinta{
    char nume_client[];
    int aria;
    double discount;
    int pret_inchiriere;
public:
    Locuinta()
    {
    }

    Locuinta(const Locuinta& cpy)
    {
        strcpy(nume_client, cpy.nume_client);
        aria = cpy.aria;
        discount = cpy.discount;
    }

    ~Locuinta()
    {
        strcpy(nume_client, NULL);
    }
    void set_pret_inchiriere(int n)
    {
        pret_inchiriere = n;
    }
    int get_aria()
    {
        return aria;
    }
    int get_discount()
    {
        return discount;
    }
    int get_pret()
    {
        return pret_inchiriere;
    }
    friend istream& operator>>(istream& in, Locuinta& l)
    {

        cout<< "Numele clientului: ";
        in>>l.nume_client;
        cout<<"Aria: ";
        in>>l.aria;
        cout<<"Discount: ";
        in>>l.discount;
        cout<<"Pret: ";
        in>>l.pret_inchiriere;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Locuinta& l)
    {
        out<<l.nume_client;
        out<<l.aria;
        out<<l.discount;
        out<<l.pret_inchiriere;
        return out;
    }
    virtual void afisare(Locuinta l)
    {
        cout<<l;
    }
};

class Apartament: public Locuinta{
    int etaj;

public:
    Apartament(){}
    ~Apartament()
    {
        etaj = -1;
    }

    friend istream& operator>>(istream& in, Apartament& a){
        cout<<"Numar etaj: ";
        in>>a.etaj;

        return in;
    }

    friend ostream& operator<<(ostream& out, const Apartament& a){
        out<<"Etajul: "<<a.etaj;

        return out;
    }
    void afisare(Apartament a)
    {
        cout<<a;
    }
    int pret_apart(Apartament& a)
    {
        int s = 0;
        s = a.get_aria() * a.get_pret() - a.get_discount() * a.get_aria() * a.get_pret();
        return s;
    }

};

class Casa: public Locuinta{
    int curte;
    int etaj[];
    int numar_etaje;
    int pret_curte;
public:
    Casa(){}
    ~Casa(){
        curte=0;
        numar_etaje=0;
    }
    friend istream& operator>>(istream& in, Casa& c){
        cout<<"Suprafata curte: ";
        in>>c.curte;
        cout<<"Nr etaje: ";
        in>>c.numar_etaje;
        for(int i=1;i<=c.numar_etaje;++i){
            cout<<"Suprafata pe etajul "<<i<<" : ";
            in>>c.etaj[i];
        }
        cout<<"Pret curte: ";
        in>>c.pret_curte;
        return in;
    }

    friend ostream& operator<<(ostream& out, Casa& c){
        out<<c.curte;
        out<<c.numar_etaje;
        for(int i=1; i<=c.numar_etaje; ++i)
        {
            out<<c.etaj[i];
        }
        return out;
    }
    void afisare(Casa c)
    {
        cout<<c;
    }
    int pret_casa(Casa& c)
    {
        int s = 0;
        int k=0;
        s = c.pret_curte * c.curte;
        for (int i=1;i<=c.numar_etaje;++i)
        {
            k+=c.etaj[i];
        }
        s += k * c.get_pret();
        s -= s * c.get_discount();
        return s;
    }
};
template <class T>
class Gestiune{
    set<pair<Locuinta, T> > s;
public:
    Gestiune()
    {
        s.clear();

    }

    Gestiune& operator+=(const Gestiune& cpy)
    {
        if (typeid(cpy.s ) == typeid(pair<Locuinta, Apartament>) ||
            typeid(cpy.s ) == typeid(pair<Locuinta, Casa>))
        {
            s.insert(cpy.s);
        }
    }
};

template <class Casa> int functie(Casa c)
{
    int x = c.pret_casa(c);
    return x;
}

int main()
{

    int nr_case, n;
    cin>>nr_case;
    Casa c[100];
    for (int i = 1; i<= nr_case; ++i)
    {
        cin>>c[i];
        cout<<"pret inchiriere: ";
        cin>>n;
        c[i].set_pret_inchiriere(n);
        cout<<functie(c[i]);
    }
}
