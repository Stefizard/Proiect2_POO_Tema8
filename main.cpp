#include <iostream>
#include <typeinfo>
using namespace std;
class Complex
{
    float Re;
    float Im;
public:
    int getRe(){ return Re;}
    int getIm(){ return Im;}
    void setRe(int Re){ this->Re=Re;}
    void setIm(int Im){ this->Im=Im;}
    Complex(float Re=0, float Im=0)
    {
        this->Re=Re;
        this->Im=Im;
    }
    Complex(const Complex &numar)
    {
        Re=numar.Re;
        Im=numar.Im;
    }
    ~Complex()
    {

    }
    friend istream& operator>>(istream& in, Complex &numar)
    {
        float r, i;
        cout<<"Partea reala = ";
        cin>>r;
        cout<<"Partea imaginara = ";
        cin>>i;
        numar.setRe(r);
        numar.setIm(i);
        return in;
    }
    friend ostream& operator<<(ostream& out, Complex numar)
    {
        if (numar.getRe()!=0)
        {
            cout<<numar.getRe();
            if (numar.getIm()==1) cout<<"+i";
            else if (numar.getIm()>0) cout<<"+"<<numar.getIm()<<"i";
            if (numar.getIm()==-1) cout<<"-i";
            else if (numar.getIm()<0) cout<<numar.getIm()<<"i";
        }
        else
        {
            if (numar.getIm()==0) cout<<numar.getRe();
            else if (numar.getIm()==1) cout<<"i";
            else if (numar.getIm()==-1) cout<<"-i";
            else cout<<numar.getIm()<<"i";
        }
        return out;
    }
    Complex operator=(Complex c)
    {
        this->setRe(c.getRe());
        this->setIm(c.getIm());
        return *this;
    }
    Complex operator*(Complex c)
    {
        Complex cat;
        cat.setRe(this->getRe()*c.getRe()-this->getIm()*c.getIm());
        cat.setIm(this->getRe()*c.getIm()+this->getIm()*c.getRe());
        return cat;
    }
    Complex operator-(Complex c)
    {
        Complex dif;
        dif.setRe(this->getRe()-c.getRe());
        dif.setIm(this->getIm()-c.getIm());
        return dif;
    }
    Complex operator+(Complex c)
    {
        Complex tot;
        tot.setRe(this->getRe()+c.getRe());
        tot.setIm(this->getIm()+c.getIm());
        return tot;
    }
};
struct nod
{
    int c;
    Complex info;
    nod * next;
};
struct nod_col
{
    int l;
    nod * linie;
    nod_col * next;
};
class Matrice
{
protected:
    nod_col *mat;
public:
    nod_col * getmat(){ return mat;}
    Matrice()
    {
        this->mat=NULL;
    }
    //copierea se face in derivate
    ~Matrice()
    {

    }
    virtual bool triunghiulara_inf (nod_col *mat)=0;
    virtual bool triunghiulara_sup (nod_col *mat)=0;
    virtual void diagonala (nod_col *mat)=0;
};
class Matrice_oarecare:public Matrice
{
    int lin;
    int col;
public:
    int getlin(){ return lin;}
    int getcol(){ return col;}
    void setlin(int lin){ this->lin=lin;}
    void setcol(int col){ this->col=col;}
    Matrice_oarecare(int lin, int col)
    {
        this->lin=lin;
        this->col=col;
        nod_col * parc=mat;
        nod_col * nou;
        for (int i=0;i<lin;i++)
        {
            nou=new nod_col;
            nou->l=i;
            nou->linie=NULL;
            nou->next=NULL;
            if (mat==NULL) mat=nou;
            else parc->next=nou;
            parc=nou;
        }
    }
    void eliminare_memorie(nod_col * matrice)
    {
        nod *parcl, *auxl;
        nod_col *parcc=matrice, *auxc;
        if (matrice==NULL) return;
        for (int i=0; i<this->lin;i++)
        {
            parcl=parcc->linie;
            while (parcl!=NULL)
            {
                auxl=parcl;
                parcl=parcl->next;
                delete auxl;
            }
            auxc=parcc;
            parcc=parcc->next;
            delete auxc;
        }
    }
    Matrice_oarecare(const Matrice_oarecare &cop)
    {
        eliminare_memorie(this->mat);
        this->mat=NULL;
        this->lin=cop.lin;
        this->col=cop.col;
        nod *parclcop, *parclnou, * nou;
        nod_col *parcccop=cop.mat, *parccnou, * noucol;
        for (int i=0; i<this->lin;i++)
        {
            noucol=new nod_col;
            noucol->l=i;
            noucol->linie=NULL;
            noucol->next=NULL;
            if (this->mat==NULL) this->mat=noucol;
            else parccnou->next=noucol;
            parccnou=noucol;
            parclcop=parcccop->linie;
            parclnou=NULL;
            while (parclcop!=NULL)
            {
                nou = new nod;
                nou->c=parclcop->c;
                nou->info=parclcop->info;
                nou->next=NULL;
                if (parclnou==NULL) parccnou->linie=nou;
                else parclnou->next=nou;
                parclnou=nou;
                parclcop=parclcop->next;
            }
            parcccop=parcccop->next;
        }
    }
    ~Matrice_oarecare()
    {
        eliminare_memorie(mat);
        this->mat=NULL;
    }
    friend istream& operator>>(istream& in, Matrice_oarecare &matrice)
    {
        int linie, coloana;
        cout<<"Pozitia elementului:"<<endl;
        cout<<"Linia = ";
        cin>>linie;
        cout<<"Coloana = ";
        cin>>coloana;
        if (linie>=matrice.getlin() || coloana>=matrice.getcol())
        {
            cout<<"Nu exista pozitia in matrice!"<<endl;
            return in;
        }
        nod *parcl, *nou;
        nod_col *parcc=matrice.mat;
        for (int i=0; i<linie;i++)
        {
            parcc=parcc->next;
        }
        nou = new nod;
        nou->c = coloana;
        parcl=parcc->linie;
        if (parcl==NULL || parcl->c>coloana)
        {
            parcc->linie=nou;
            nou->next=parcl;
            cin>>nou->info;
            return in;
        }
        while (parcl->next!=NULL && parcl->next->c<=coloana)
        {
            parcl=parcl->next;
        }
        if (parcl->c==coloana)
        {
            cout<<"Pozitie deja ocupata!"<<endl;
            return in;
        }
        else
        {
            nou->next=parcl->next;
            parcl->next=nou;
            cin>>nou->info;
        }
        return in;
    }
    friend ostream& operator<<(ostream& out, Matrice_oarecare &matrice)
    {
        nod *parcl;
        nod_col *parcc=matrice.mat;
        for (int i=0; i<matrice.lin;i++)
        {
            parcl=parcc->linie;
            for (int j=0;j<matrice.col;j++)
            {
                if (parcl!=NULL && parcl->c==j)
                {
                    cout<<parcl->info<<" ";
                    parcl=parcl->next;
                }
                else cout<<"0 ";
            }
            cout<<endl;
            parcc=parcc->next;
        }
        return out;
    }
    Matrice_oarecare& operator=(Matrice_oarecare &cop)
    {
        eliminare_memorie(this->mat);
        this->mat=NULL;
        this->lin=cop.lin;
        this->col=cop.col;
        nod *parclcop, *parclnou, * nou;
        nod_col *parcccop=cop.mat, *parccnou, * noucol;
        for (int i=0; i<this->lin;i++)
        {
            noucol=new nod_col;
            noucol->l=i;
            noucol->linie=NULL;
            noucol->next=NULL;
            if (this->mat==NULL)
            {
                this->mat=noucol;
            }
            else parccnou->next=noucol;
            parccnou=noucol;
            parclcop=parcccop->linie;
            parclnou=NULL;
            while (parclcop!=NULL)
            {
                nou = new nod;
                nou->c=parclcop->c;
                nou->info=parclcop->info;
                nou->next=NULL;
                if (parclnou==NULL) parccnou->linie=nou;
                else parclnou->next=nou;
                parclnou=nou;
                parclcop=parclcop->next;
            }
            parcccop=parcccop->next;
        }
        return *this;
    }
    bool triunghiulara_inf (nod_col *mat)
    {
        cout<<"Matricea nu este triunghiulara, fiindca nu este patratica."<<endl;
        return 0;
    }
    bool triunghiulara_sup (nod_col *mat)
    {
        cout<<"Matricea nu este triunghiulara, fiindca nu este patratica."<<endl;
        return 0;
    }
    void diagonala (nod_col *mat)
    {
        cout<<"Matricea nu este diagonala, fiindca nu este patratica."<<endl;
    }
};
class Matrice_patratica:public Matrice
{
    int dim;
public:
    int getdim(){ return dim;}
    void setdim(int dim){ this->dim=dim;}
    Matrice_patratica(int dim)
    {
        this->dim=dim;
        nod_col * parc=mat;
        nod_col * nou;
        for (int i=0;i<dim;i++)
        {
            nou=new nod_col;
            nou->l=i;
            nou->linie=NULL;
            nou->next=NULL;
            if (mat==NULL) mat=nou;
            else parc->next=nou;
            parc=nou;
        }
    }
    void eliminare_memorie(nod_col * matrice)
    {
        nod *parcl, *auxl;
        nod_col *parcc=matrice, *auxc;
        if (matrice==NULL) return;
        for (int i=0; i<this->dim;i++)
        {
            parcl=parcc->linie;
            while (parcl!=NULL)
            {
                auxl=parcl;
                parcl=parcl->next;
                delete auxl;
            }
            auxc=parcc;
            parcc=parcc->next;
            delete auxc;
        }
    }
    Matrice_patratica(const Matrice_patratica &cop)
    {
        eliminare_memorie(this->mat);
        this->mat=NULL;
        this->dim=cop.dim;
        nod *parclcop, *parclnou, * nou;
        nod_col *parcccop=cop.mat, *parccnou, * noucol;
        for (int i=0; i<this->dim;i++)
        {
            noucol=new nod_col;
            noucol->l=i;
            noucol->linie=NULL;
            noucol->next=NULL;
            if (this->mat==NULL) this->mat=noucol;
            else parccnou->next=noucol;
            parccnou=noucol;
            parclcop=parcccop->linie;
            parclnou=NULL;
            while (parclcop!=NULL)
            {
                nou = new nod;
                nou->c=parclcop->c;
                nou->info=parclcop->info;
                nou->next=NULL;
                if (parclnou==NULL) parccnou->linie=nou;
                else parclnou->next=nou;
                parclnou=nou;
                parclcop=parclcop->next;
            }
            parcccop=parcccop->next;
        }
    }
    ~Matrice_patratica()
    {
        eliminare_memorie(mat);
        this->mat=NULL;
    }
    friend istream& operator>>(istream& in, Matrice_patratica &matrice)
    {
        int linie, coloana;
        cout<<"Pozitia elementului:"<<endl;
        cout<<"Linia = ";
        cin>>linie;
        cout<<"Coloana = ";
        cin>>coloana;
        if (linie>=matrice.getdim() || coloana>=matrice.getdim())
        {
            cout<<"Nu exista pozitia in matrice!"<<endl;
            return in;
        }
        nod *parcl, *nou;
        nod_col *parcc=matrice.mat;
        for (int i=0; i<linie;i++)
        {
            parcc=parcc->next;
        }
        nou = new nod;
        nou->c = coloana;
        parcl=parcc->linie;
        if (parcl==NULL || parcl->c>coloana)
        {
            parcc->linie=nou;
            nou->next=parcl;
            cin>>nou->info;
            return in;
        }
        while (parcl->next!=NULL && parcl->next->c<=coloana)
        {
            parcl=parcl->next;
        }
        if (parcl->c==coloana)
        {
            cout<<"Pozitie deja ocupata!"<<endl;
            return in;
        }
        else
        {
            nou->next=parcl->next;
            parcl->next=nou;
            cin>>nou->info;
        }
        return in;
    }
    friend ostream& operator<<(ostream& out, Matrice_patratica &matrice)
    {
        nod *parcl;
        nod_col *parcc=matrice.mat;
        for (int i=0; i<matrice.dim;i++)
        {
            parcl=parcc->linie;
            for (int j=0;j<matrice.dim;j++)
            {
                if (parcl!=NULL && parcl->c==j)
                {
                    cout<<parcl->info<<" ";
                    parcl=parcl->next;
                }
                else cout<<"0 ";
            }
            cout<<endl;
            parcc=parcc->next;
        }
        cout<<"det = "<<matrice.det(matrice,0)<<endl;
        return out;
    }
    Matrice_patratica& operator=(Matrice_patratica &cop)
    {
        eliminare_memorie(this->mat);
        this->mat=NULL;
        this->dim=cop.dim;
        nod *parclcop, *parclnou, * nou;
        nod_col *parcccop=cop.mat, *parccnou=this->mat, * noucol;
        for (int i=0; i<this->dim;i++)
        {
            noucol=new nod_col;
            noucol->l=i;
            noucol->linie=NULL;
            noucol->next=NULL;
            if (this->mat==NULL)
            {
                this->mat=noucol;
            }
            else parccnou->next=noucol;
            parccnou=noucol;
            parclcop=parcccop->linie;
            parclnou=NULL;
            while (parclcop!=NULL)
            {
                nou = new nod;
                nou->c=parclcop->c;
                nou->info=parclcop->info;
                nou->next=NULL;
                if (parclnou==NULL) parccnou->linie=nou;
                else parclnou->next=nou;
                parclnou=nou;
                parclcop=parclcop->next;
            }
            parcccop=parcccop->next;
        }
        return *this;
    }
    bool triunghiulara_inf (nod_col *mat)
    {
        nod *parcl;
        nod_col *parcc=mat;
        for (int i=0; i<this->dim;i++)
        {
            parcl=parcc->linie;
            while (parcl!=NULL)
            {
                if (parcl->c < parcc->l) return 0;
                parcl=parcl->next;
            }
            parcc=parcc->next;
        }
        return 1;
    }
    bool triunghiulara_sup (nod_col *mat)
    {
        nod *parcl;
        nod_col *parcc=mat;
        for (int i=0; i<this->dim;i++)
        {
            parcl=parcc->linie;
            while (parcl!=NULL)
            {
                if (parcl->c > parcc->l) return 0;
                parcl=parcl->next;
            }
            parcc=parcc->next;
        }
        return 1;
    }
    void diagonala (nod_col *mat)
    {
        bool ti,ts;
        ti=triunghiulara_inf(mat);
        ts=triunghiulara_sup(mat);
        if (!ti && !ts)
        {
            cout<<"Matricea nu este triunghiulara."<<endl;
            return;
        }
        //if (ti || ts) cout<<"Matricea este triunghiulara."<<endl;
        if (ti && ts) cout<<"Matricea este diagonala."<<endl;
        else cout<<"Matricea nu este diagonala."<<endl;
    }
    Complex det (Matrice_patratica &matrice, int indice)
    {
        Complex S(0,0), retin;
        Complex zero(0,0);
        if (matrice.dim==1)
        {
            if (matrice.mat->linie!=NULL) return matrice.mat->linie->info;
            else return zero;
        }
        Matrice_patratica aux(matrice);
        nod *parcl, *parclsterg;
        nod_col *parcc=aux.mat, *prec=aux.mat;
        bool zerodet=0;
        for (int i=0; i<aux.dim; i++)
        {
            aux=matrice;
            parcc=aux.mat;
            prec=aux.mat;
            zerodet=0;
            for (int j=0; j<aux.dim; j++)
            {
                parcl=parcc->linie;
                if (parcl==NULL)
                {
                    return zero; //aici daca nu e pe prima linie, nu merge, desi intra in if; problema este de la return zero, nu stiu de ce
                }
                if (parcc->l==i)
                {
                    if (parcl->c==indice)
                    {
                        retin=parcl->info;
                    }
                    else
                    {
                        retin=zero;
                        zerodet=1;
                    }
                    if (zerodet==1) break;
                    while (parcl!=NULL)
                    {
                        parclsterg=parcl;
                        parcl=parcl->next;
                        delete parclsterg;
                    }
                    if (parcc==aux.mat)
                    {
                        aux.mat=parcc->next;
                        delete prec;
                        parcc=aux.mat;
                        prec=aux.mat;
                    }
                    else
                    {
                        prec->next=parcc->next;
                        delete parcc;
                        parcc=prec->next;
                    }
                }
                else
                {
                    if (parcl!=NULL && parcl->c==indice)
                    {
                        parcc->linie=parcl->next;
                        delete parcl;
                    }
                    prec=parcc;
                    parcc=parcc->next;
                }
            }
            if (zerodet==1) continue;
            aux.dim--;
            if ((i)%2==0)
            {
                S=S+retin*det(aux,indice+1);
            }
            else
            {
                S=S-retin*det(aux,indice+1);
            }
        }
        return S;
    }
};
/*class Nr_Mat
{
    int n;
    Matrice **v;
public:
    int getn(){ return n;}
    Matrice** getv(){ return v;}
    void citire()
    {
        cout<<"Numarul de matrici: ";
    cin>>n;
    int li, co;
    v=new Matrice*[n];
    for (int i=0;i<n;i++)
    {
        cout<<"Matricea "<<i+1<<":"<<endl;
        cout<<"Numarul de linii: ";
        cin>>li;
        cout<<"Numarul de coloane: ";
        cin>>co;
        if (li==co)
        {
            v[i]=new Matrice_patratica(li);
        }
        else
        {
            v[i]=new Matrice_oarecare(li,co);
        }
    }
    }
    ~Nr_Mat()
    {
        delete []v;
    }
};*/
int main()
{
    int n;
    Matrice **v;
    cout<<"Numarul de matrici: ";
    cin>>n;
    int li, co;
    v=new Matrice*[n];
    for (int i=0;i<n;i++)
    {
        cout<<"Matricea "<<i+1<<":"<<endl;
        cout<<"Numarul de linii: ";
        cin>>li;
        cout<<"Numarul de coloane: ";
        cin>>co;
        if (li==co)
        {
            v[i]=new Matrice_patratica(li);
        }
        else
        {
            v[i]=new Matrice_oarecare(li,co);
        }
    }
    int o,i;
    while (1)
    {
        cout<<"[1-afisarea matricei (cu determinant la cele patratice); 2-setare elemente; 3-verificare diagonala; 4-exit]"<<endl<<"Optiunea ";
        cin>>o;
        if (o==4) break;
        cout<<"Carei matrice doriti sa ii aplicati optiunea? (indicele incepe de la 1)"<<endl<<"Matricea ";
        cin>>i;
        if (i>n || i<1)
        {
            cout<<"Nu exista aceasta matrice!"<<endl;
            continue;
        }
        i--;
        switch (o)
        {
            case 1:
            {
                if (typeid(*v[i])==typeid(Matrice_patratica)) cout<<*(Matrice_patratica*)(v[i])<<endl;
                if (typeid(*v[i])==typeid(Matrice_oarecare)) cout<<*(Matrice_oarecare*)(v[i])<<endl;
                break;
            }
            case 2:
            {
                if (typeid(*v[i])==typeid(Matrice_patratica)) cin>>*dynamic_cast<Matrice_patratica*>(v[i]);
                if (typeid(*v[i])==typeid(Matrice_oarecare)) cin>>*dynamic_cast<Matrice_oarecare*>(v[i]);
                cout<<endl;
                break;
            }
            case 3:
            {
                v[i]->diagonala(v[i]->getmat());
                break;
            }
            default: cout<<"Optiune invalida!"<<endl;
        }
    }
    return 0;
}
