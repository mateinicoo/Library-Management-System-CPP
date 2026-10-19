#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <memory>



using namespace std;

class Autor{
    private:
        string nume;
        int cartiPublicate;
        static int cnt;
    public:
        Autor(); // constructor fara parametri
        Autor(const string nume, const int cartiPublicate=0); // constructor cu parametri
        Autor(const Autor& p); // constructor de copiere
        ~Autor(){cnt--;} // destructor

        virtual Autor & operator = (const Autor& p){ // operator =
            this->nume=p.nume;
            this->cartiPublicate=p.cartiPublicate;
            return *this;
        }

        friend istream & operator >> (istream& in , Autor& p){ //operator de citire
            getline(in, p.nume);
            return in;
        }

        friend ostream & operator << (ostream& out , const Autor& p){ //operator de afisare
            out << p.nume;
            return out;
        }

        friend Autor operator ++(Autor& p); // operator supraincarcat ca functie membra

        Autor operator +=(const int nr){ // operator supraincarcat ca functie membra
            this->cartiPublicate += nr;
            return *this;
        }

        const int getCartiPublicare(){ // metoda get
            return this->cartiPublicate;
        }
        const string& getNume() const {
            return this->nume;
        }
        void setNume(const string nume){
            this->nume=nume;
        }

        static int numarAutori(){
            return cnt;
        }
};
int Autor::cnt=0;
Autor::Autor(){

    this->nume="Necunoscut";
    this->cartiPublicate=0;
    cnt++;
}
Autor::Autor(const string nume, const int cartiPublicate){
    this->nume=nume;
    this->cartiPublicate=cartiPublicate;
    cnt++;
}
Autor::Autor(const Autor& p){
    this->nume=p.nume;
    this->cartiPublicate=p.cartiPublicate;
    cnt++;
}
Autor operator ++(Autor& p){
    p.cartiPublicate++;
    return p;
}

//---------------------------------------------------------------------------------

class ManagerAutori{
    private:
        vector<Autor> autori;
        ManagerAutori(){}

    public:

        ManagerAutori(const ManagerAutori&) = delete;
        ManagerAutori& operator=(const ManagerAutori&) = delete;

        static ManagerAutori& getInstanta(){
            static ManagerAutori instanta;
            return instanta; 
        }

    void adaugaAutor(const Autor& a) {
        autori.push_back(a);
    }

    void afiseazaAutori() {
        for (auto& a : autori)
            cout << "Autor: " << a.getNume() << '\n';
    }

    Autor* cautaAutor(const string& nume) {
        for (auto& a : autori)
            if (a.getNume() == nume)
                return &a;
        return nullptr;
    }

    vector<Autor>& getAutori() {
        return autori;
    }

};

//---------------------------------------------------------------------------------

class AutorIstoric: public Autor{
    private:
        string domeniu;
    public:
        AutorIstoric(string nume, int cartiPublicate, string domeniu): Autor(nume, cartiPublicate), domeniu(domeniu) {}

        AutorIstoric(const AutorIstoric& a) : Autor(a), domeniu(a.domeniu) {}

        AutorIstoric& operator=(const AutorIstoric& a) {
            if (this != &a) {
                Autor::operator=(a); 
                domeniu = a.domeniu;
            }
            return *this;
        }

        const string& getDomeniu() const { return domeniu; }
};



//---------------------------------------------------------------------------------

class Document{
    protected:
        string titlu;
        Autor autor;
        int anPublicare;
    public:

        Document() = default;
        Document(const string titlu, const Autor& autor, int anPublicare): titlu(titlu), autor(autor), anPublicare(anPublicare){}
        Document(const Document& d): titlu(d.titlu), autor(d.autor), anPublicare(d.anPublicare) {}

        virtual void afisare() const = 0; // functie abstracta
        void afisareDocument() const{
            cout<<"Document: "<<titlu<<'\n';
        }
        virtual ~Document() = default;
};

//---------------------------------------------------------------------------------

class Articol: public Document{
    private:
        string revista;
    public:
        Articol() = default;
        Articol(string titlu, Autor& autor, int anPublicare, string revista): Document(titlu, autor, anPublicare), revista(revista){}
        void afisare() const override {
            cout<< "Titlu: " << titlu << ", Autor: " << autor.getNume() << ", Revista: " << revista << '\n';
        }
        virtual ~Articol() = default;

    };  

//---------------------------------------------------------------------------------


class Carte: public virtual Document{
    private:
        int nrPagini;
    public:
    Carte(){++autor;}

    Carte(const string& titlu, int nrPagini, Autor& autor, int anPublicare): Document(titlu, autor, anPublicare), nrPagini(nrPagini) {++autor;}

    Carte(const Carte& c) :nrPagini(c.nrPagini){
        ++autor;
        this->titlu=c.titlu;
        this->autor=c.autor;
    }

    virtual ~Carte() {}

    Carte& operator=(const Carte& c) {
        if (this != &c) {
            titlu = c.titlu;
            nrPagini = c.nrPagini;
            autor = c.autor;
        }
        return *this;
    }

    const string& getTitlu() const { return titlu; }
    const string& getAutor() const { return autor.getNume(); }
    int getNrPg() const { return nrPagini; }

    virtual void afisare() const {
        cout << "Titlu: " << titlu << ", Autor: " << autor.getNume() << ", Pagini: " << nrPagini << '\n';
    }
    

};

//---------------------------------------------------------------------------------

class CarteEducativa: public virtual Carte{
    private:
        string domeniu;
    public:
        
    CarteEducativa(const string& titlu, int nrPagini, Autor& autor, int anPublicare, const string& domeniu): Carte(titlu, nrPagini, autor, anPublicare), domeniu(domeniu) {}

    CarteEducativa(const CarteEducativa& c): Carte(c), domeniu(c.domeniu) {}

    CarteEducativa& operator=(const CarteEducativa& c) {
        if (this != &c) {
            Carte::operator=(c);
            domeniu = c.domeniu;
        }
        return *this;
    }

    const string& getDomeniu() const { return domeniu; }

    void afisare() const override {
        Carte::afisare();
        cout << "Domeniu: " << domeniu << '\n';
    }

};

//---------------------------------------------------------------------------------

class CarteCopii: public virtual Carte{
    protected:
        int varsta;
    public:
    CarteCopii(const string& titlu, int nrPagini, Autor& autor, int anPublicare, int varsta): Carte(titlu, nrPagini, autor, anPublicare), varsta(varsta) {}

    CarteCopii(const CarteCopii& c): Carte(c), varsta(c.varsta) {}

    CarteCopii& operator=(const CarteCopii& c) {
        if (this != &c) {
            Carte::operator=(c);
            varsta = c.varsta;
        }
        return *this;
    }

    int getVarsta() const { return varsta; }

    void afisare() const override {
        Carte::afisare();
        cout << "Varsta recomandata: " << varsta << '\n';
    }
};

//---------------------------------------------------------------------------------

class CarteScoalaPrimara: public CarteEducativa, public CarteCopii{ // clasa mostenita diamant
    private:
        int clasa;
    public:
    CarteScoalaPrimara(const string& titlu, int nrPagini, Autor& autor, int anPublicare, const string& domeniu, int varsta, int clasa): Carte(titlu, nrPagini, autor, anPublicare), CarteEducativa(titlu, nrPagini, autor, anPublicare, domeniu), CarteCopii(titlu, nrPagini, autor, anPublicare, varsta), clasa(clasa) {}

    CarteScoalaPrimara(const CarteScoalaPrimara& c): CarteEducativa(c), CarteCopii(c), clasa(c.clasa) {}

    CarteScoalaPrimara& operator=(const CarteScoalaPrimara& c) {
        if (this != &c) {
            CarteEducativa::operator=(c);
            CarteCopii::operator=(c);
            clasa = c.clasa;
        }
        return *this;
    }

    int getClasa() const { return clasa; }

    void afisare() const override {
        CarteEducativa::afisare();
        cout << "Varsta recomandata: " <<varsta<< '\n';
        cout << "Clasa: " << clasa << '\n';
    }
};

//---------------------------------------------------------------------------------

template <typename T> class Biblioteca {
    private:
        list<T> documente;
    public:
        Biblioteca(){}
        void adaugaDocument(T doc) {
            documente.push_back(doc);
        }

        void afisare() const {
            for (const auto& doc : documente)
                doc.afisareDocument();  // upcast
        }
};

//---------------------------------------------------------------------------------

class Editura{
    private:
        string nume;
        vector<Carte> carti;
    public:
        Editura();
        Editura(string nume);
        ~Editura(){}
        void adaugaCarte(Carte& carte){
            carti.push_back(carte);
        }
        string getNume(){
            return this->nume;
        }

        void afiseazaCarti(){
            for(int i=0; i<carti.size(); i++)
                cout<<"Titlu: "<<carti[i].getTitlu()<<"   "<<"Autor: "<<carti[i].getAutor()<<'\n';
            cout<<'\n';
        }

        static bool comp1(const Carte&a, const Carte&b){
            return a.getTitlu() < b.getTitlu();
        }
        static bool comp2(const Carte&a, const Carte&b){
            return a.getNrPg() < b.getNrPg();
        }
        void sortCarti(){
            cout<<"Cum vrei sa ordonezi cartile?\n1.Dupa titlu\n2.Dupa numarul de pagini\n";
            int opt;
            cin>>opt;
            if(opt==1)
                sort(carti.begin(), carti.end(), comp1);
            else
                sort(carti.begin(), carti.end(), comp2);  
        }

};
Editura::Editura(string nume){
    this->nume=nume;
}

//---------------------------------------------------------------------------------


class ManagerEdituri {
private:
    vector<Editura> edituri;
    ManagerEdituri() {}

public:
    ManagerEdituri(const ManagerEdituri&) = delete;
    ManagerEdituri& operator=(const ManagerEdituri&) = delete;

    static ManagerEdituri& getInstanta() {
        static ManagerEdituri instanta;
        return instanta;
    }

    void adaugaEditura(const Editura& e) {
        edituri.push_back(e);
    }

    void afiseazaEdituri() {
        for (auto& e : edituri)
            cout << "Editura: " << e.getNume() << '\n';
    }

    Editura* cautaEditura(const string& nume) {
        for (auto& e : edituri)
            if (e.getNume() == nume)
                return &e;
        return nullptr;
    }

    vector<Editura>& getEdituri() {
        return edituri;
    }
};

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

void Meniu()
{
    bool ok=0;
    Biblioteca<Articol> bibliotecaArticole;
    Biblioteca<Carte> bibliotecaCarti;
    while(ok==0){
        cout<<"-------------Meniu-------------\n";
        cout<<"Optiuni:\n";
        cout<<"1. Citeste n autori\n";
        cout<<"2. Afisare autori\n";
        cout<<"3. Adauga editura\n";
        cout<<"4. Adauga carte in editura\n";
        cout<<"5. Afiseaza cartile din editura\n";
        cout<<"6. Ordoneaza cartile din editura\n";
        cout<<"7. Adauga documente in bibliotece\n";
        cout<<"8. Afiseaza documentele din biblioteca\n";
        cout<<"9. Try-catch + dynamic cast\n";
        cout<<"10. Iesiti din meniu\n";

        int opt;
        cin>>opt;
        ManagerEdituri& managerE = ManagerEdituri::getInstanta();
        ManagerAutori& managerA = ManagerAutori::getInstanta();


        switch(opt)
        {

        case 1:{
            cout<<"Citeste n: ";
            int n;
            cin>>n;
            cout<<'\n';
            cin.ignore();
            for(int i=0; i<n; i++)
            {
                string nume;
                cout<<"Introdu numele autorului: ";
                getline(cin, nume);
                if(managerA.cautaAutor(nume)==nullptr){
                    Autor autor(nume);
                    managerA.adaugaAutor(autor);}
                else cout<<"Autorul "<<nume<<" exista deja.";
            }
            
            break;
        }
    //---------------------------------------------------------------------------------

        case 2:{
            managerA.afiseazaAutori();
            break;
        }
    //---------------------------------------------------------------------------------

        case 3:{
            string nume;
            cout<<"Introdu numele editurii: ";
            cin.ignore();
            getline(cin, nume);
            bool ok=0;
            for(int i=0; i<managerE.getEdituri().size(); i++)
                if(managerE.getEdituri()[i].getNume() == nume)
                {
                    ok=1;
                    break;
                }
            if(ok==1)
                cout<<"Editura exista deja\n";
            else{
            Editura editura(nume);
            managerE.adaugaEditura(editura);

            }
            break;}
    //---------------------------------------------------------------------------------

        case 4:{
            cout<<"Introdu numele editurii: ";
            string editura;
            cin.ignore();
            getline(cin, editura);
            bool ok=0;
            for(int i=0; i<managerE.getEdituri().size(); i++)
            {
                if(managerE.getEdituri()[i].getNume()==editura)
                    ok=1;
            }
            if(ok==0)
            {
                cout<<"EROARE: Editura nu a fost gasita.\n";
                break;
            }
            cout<<"Introdu numele cartii: ";
            string titlu;
            getline(cin, titlu);
            cout<<"Introdu numarul de pagini: ";
            int nrPagini;
            cin>>nrPagini;
            cin.ignore();
            cout<<"Introdu numele autorului: ";
            string nume;
            getline(cin, nume);
            int anPublicare;
            cout<<"Introdu anul de publicare: ";
            cin>>anPublicare;
            Autor autor;
            bool ok1=0;
            for(int i=0; i<managerA.getAutori().size(); i++)
                if(managerA.getAutori()[i].getNume()==nume){
                    autor=managerA.getAutori()[i];
                    ok1=1;
                    break;}
            if(ok1==0){
                cout<<"EROARE: Autorul nu a fost gasit.\n";
                break;
            }
            for(int i=0; i<managerE.getEdituri().size(); i++)
                if(managerE.getEdituri()[i].getNume()==editura){
                    Carte carte(titlu, nrPagini, autor, anPublicare);
                    managerE.getEdituri()[i].adaugaCarte(carte);
                    cout<<"Cartea \""<<titlu<<"\" a fost adaugata cu succes in editura "<<editura<<".\n";

                    break;}
            break;}
//---------------------------------------------------------------------------------

        case 5:{
            string editura;
            cout<<"Introdu numele editurii: ";
            cin.ignore();
            bool ok=0;
            getline(cin, editura);
            for(int i=0; i<managerE.getEdituri().size(); i++)
                if(managerE.getEdituri()[i].getNume()==editura){
                    ok=1;
                    managerE.getEdituri()[i].afiseazaCarti();}

            if(ok==0)
                cout<<"EROARE: Editura nu a fost gasita.\n";
            break;

        }

//---------------------------------------------------------------------------------

        case 6:
        {
            cout<<"Introdu numele editurii: ";
            string nume;
            cin.ignore();
            getline(cin, nume);

            Editura* ed = managerE.cautaEditura(nume);
            if (ed == nullptr) {
                cout << "EROARE: Editura nu a fost gasita.\n";
                break;
            }
            ed->sortCarti();

            break;
        }

//---------------------------------------------------------------------------------

        case 7:
        {
            cout<<"Ce documente vrei sa adaugi?\n1. Articol\n2. Carte\n";
            int c;
            cin>>c;
            if(c==1){

                cin.ignore();
                cout<<"Introdu titlul articolului: ";
                string titlu;
                getline(cin, titlu);
                cout<<"Introdu numele autorului: ";
                string nume;
                getline(cin, nume);
                Autor *autor = managerA.cautaAutor(nume);
                cout<<"Introdu anul de publicare: ";
                int an;
                cin>>an;
                cin.ignore();
                cout<<"Introdu numele revistei: ";
                string revista;
                getline(cin, revista);

                Articol articol(titlu, *autor, an, revista);
                bibliotecaArticole.adaugaDocument(articol);

            }
            else if(c==2)
            {
                cin.ignore();
                cout<<"Introdu titlul cartii: ";
                string titlu;
                getline(cin, titlu);
                cout<<"Introdu numele autorului: ";
                string nume;
                getline(cin, nume);
                Autor *autor = managerA.cautaAutor(nume);
                cout<<"Introdu numarul de pagini: ";
                int nr;
                cin>>nr;
                cout<<"Introdu anul de publicare: ";
                int an;
                cin>>an;
                Carte carte(titlu, nr, *autor, an);
                bibliotecaCarti.adaugaDocument(carte);
                
            }
        break;
        }

//---------------------------------------------------------------------------------

        case 8:
        {
            bibliotecaArticole.afisare();
            bibliotecaCarti.afisare();
            break;
        }

//---------------------------------------------------------------------------------


        case 9:
        {
            Autor autor("nume");
            cout << "Test try-catch + dynamic_cast\n";
            try {
                Document* doc = new Articol("Titlu articol", autor, 2024, "revista");
                
                Carte* c = dynamic_cast<Carte*>(doc);
                if (!c) {
                    throw std::bad_cast();
                }

                cout << "Conversia a reusit. Detalii carte:\n";
                c->afisare();
                
                    delete doc;
            } catch (const std::bad_cast& e) {
                cout << "Eroare la conversie cu dynamic_cast: " << e.what() << "\n";
            }
        


            try {
                Document* doc = new Carte("Enigma Otiliei", 202, autor, 1990);
                
                Carte& carteRef = dynamic_cast<Carte&>(*doc);  
                
                cout << "Conversia reusita cu referinta. Titlu: " << carteRef.getTitlu() << "\n";

                if (typeid(*doc) == typeid(Carte)) {
                    cout << "Tipul real este exact Carte.\n";
                }

                delete doc;
            } catch (const std::bad_cast& e) {
                cout << "Eroare la conversie cu dynamic_cast: " << e.what() << "\n";
            }


            break;
        }

//---------------------------------------------------------------------------------

        case 10:{
            ok = 1;
            break;}
        }
    }
}

//-------------------------------------------------------


int main()
{
    Meniu();
    return 0;
}