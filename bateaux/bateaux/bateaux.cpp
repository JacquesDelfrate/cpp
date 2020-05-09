#include <iostream>
#include <cmath>
using namespace std;

enum Pavillon { JollyRogers, CompagnieDuSenegal, CompagnieDOstende };

enum Etat { Intact, Endommage, Coule };

int sq(int x)
{
    return x * x;
}

class Coordonnees
{
public:
    Coordonnees(int un_x, int un_y) : x_(un_x), y_(un_y) {}
    int x() const {
        return x_;
    }
    int y() const {
        return y_;
    }
    void operator+=(Coordonnees const& autre); // à définir plus bas
private:
    int x_;
    int y_;
};


class Navire
{
    /*****************************************************
     * Compléter le code à partir d'ici
     *****************************************************/
public:
    Navire(int x, int y, Pavillon pavillon) : position_(x, y), pavillon_(pavillon) {};

    Coordonnees position();

    void avancer(int de_x, int de_y);
    void renflouer();

    ostream& afficher(ostream& sortie) const;
   
    const int rayon_rencontre = 10;

private:
    Pavillon pavillon_;
    Etat etat_ = Intact;
    Coordonnees position_;
};

void Coordonnees::operator+=(Coordonnees const& autre)
{
    this->x_ += autre.x();
    this->y_ += autre.y();
}

ostream& operator<<(ostream& sortie, Navire const& n) 
{
    return n.afficher(cout);
}

ostream& operator<<(ostream&, Coordonnees const& c)
{
    return cout << "( " << c.x() << ", " << c.y() << ")";
}

ostream& operator<<(ostream&, Pavillon const& p)
{
     if (p == JollyRogers)
        return cout << "pirate";
    else if (p == CompagnieDuSenegal)
        return cout << "français";
    else if (p == CompagnieDOstende)
        return cout << "autrichien";

    return cout << "pavillon inconnu";
}

ostream& operator<<(ostream&, Etat const& e)
{
    if (e == Intact)
        return cout << "intact";
    else if (e == Endommage)
        return cout << "ayant subi des dommages";
    else if (e == Coule)
        return cout << "coulé";

    return cout << "état inconnu";
}

double distance(const Coordonnees& c1, const Coordonnees& c2)
{
    return sqrt(pow((c1.x() - c2.x()), 2) + pow((c1.y() - c2.y()), 2));
}

double distance(Navire& v1, Navire& v2)
{

    return distance(v1.position(), v2.position());
}

Coordonnees Navire::position()
{
    return this->position_;
}

void Navire::renflouer()
{
    this->etat_ = Intact;
}

void Navire::avancer(int de_x, int de_y)
{
    if (etat_ != Coule)
    {
        Coordonnees c(de_x, de_y);
        position_ += c;
    }
}

ostream& Navire::afficher(ostream& sortie) const
{
    sortie << "bateau " << this->pavillon_ << " en " << this->position_ << " battant pavillon " << this->pavillon_ << ", " << this->etat_ << endl;

    return sortie;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

//void rencontre(Navire& ship1, Navire& ship2)
//{
//    cout << "Avant la rencontre :" << endl;
//    cout << ship1 << endl;
//    cout << ship2 << endl;
//    cout << "Distance : " << distance(ship1, ship2) << endl;
//    ship1.rencontrer(ship2);
//    cout << "Apres la rencontre :" << endl;
//    cout << ship1 << endl;
//    cout << ship2 << endl;
//}

int main()
{
    // Test de la partie 1
    cout << "===== Test de la partie 1 =====" << endl << endl;

    Navire ship(0, 0, JollyRogers);
    cout << ship << endl;
    //// Un bateau pirate 0,0
    //Pirate ship1(0, 0, JollyRogers);
    //cout << ship1 << endl;

    //// Un bateau marchand en 25,0
    //Marchand ship2(25, 0, CompagnieDuSenegal);
    //cout << ship2 << endl;

    //cout << "Distance : " << distance(ship1, ship2) << endl;

    //cout << "Quelques déplacements..." << endl;
    //cout << "  en haut à droite :" << endl;
    //// Se déplace de 75 unités à droite et 10 en haut
    //ship1.avancer(75, 10);
    //cout << ship1 << endl;

    //cout << "  vers le bas :" << endl;
    //ship1.avancer(0, -5);
    //cout << ship1 << endl;

    //cout << endl << "===== Test de la partie 2 =====" << endl << endl;

    //cout << "Bateau pirate et marchand ennemis (trop loins) :" << endl;
    //rencontre(ship1, ship2);

    //cout << endl << "Bateau pirate et marchand ennemis (proches) :" << endl;
    //ship1.avancer(-40, -2);
    //ship2.avancer(10, 2);
    //rencontre(ship1, ship2);

    //cout << endl << "Deux bateaux pirates ennemis intacts (proches) :" << endl;
    //Pirate ship3(33, 8, CompagnieDOstende);
    //rencontre(ship1, ship3);

    //cout << endl << "Bateaux pirates avec dommages, ennemis :" << endl;
    //rencontre(ship1, ship3);

    //cout << endl << "Bateaux marchands ennemis :" << endl;
    //Marchand ship4(21, 7, CompagnieDuSenegal);
    //Marchand ship5(27, 2, CompagnieDOstende);
    //rencontre(ship4, ship5);

    //cout << endl << "Pirate vs Felon :" << endl;
    //ship3.renflouer();
    //Felon ship6(32, 10, CompagnieDuSenegal);
    //rencontre(ship3, ship6);

    //cout << endl << "Felon vs Pirate :" << endl;
    //rencontre(ship6, ship3);

    return 0;
}
