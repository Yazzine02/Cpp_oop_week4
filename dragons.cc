#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int distance(int x, int y)
{
  return abs(x - y);
}

class Creature
{
  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
	public:
		Creature(string n,int lv,int pv,int f,int p=0)
		:name(n),level(lv),points_de_vie(pv),force(f),position_(p){}
		bool vivant(){
			if(points_de_vie>0)return true;
			else {
			    setPV(0);
			    return false;
			}
		}
		int points_attaque() {
			if(vivant())return level*force;
			else return 0;
		}
		
		void deplacer(int distance){//do i need to put const here
			if(vivant())setPosition(getPosition()+distance);
		}
		void adieux()const{
			cout<<name<<" n'est plus !"<<endl;
		}
		void faiblir(int damage){
			setPV(getPV()-damage);
			if(!vivant())adieux();
		}
		void afficher(){ 
		cout<< name<<", niveau: "<<level
         << ", points de vie: "<<points_de_vie
         << ", force: "<<force
         << ", points d'attaque: "<<points_attaque()
         << ", position: "<<position_<<endl;
		 }
		
		int getPosition()const {return position_;}
		void setPosition(int pos){position_=pos;}
		
		int getPV()const {return points_de_vie;}
		void setPV(int pv){points_de_vie=pv;}
		
		
		
		
		int position()const {
			return getPosition();
		}
	protected:
		const string name;
		int level,points_de_vie,force;
		int position_;

};

class Dragon:public Creature{
	public:
		Dragon(string n,int lv,int pv,int f,int por,int pos=0)
		:Creature(n,lv,pv,f,pos),portee_flamme_(por){}
		void voler(int pos){
			if(vivant())setPosition(pos);
		}
		void souffle_sur(Creature& bete){
			if(vivant() && bete.vivant()){
				if(distance(bete.getPosition(),getPosition())<=getPF()){
					bete.faiblir(points_attaque());
					faiblir(distance(bete.getPosition(),getPosition()));
					if(vivant() && !bete.vivant())level+=1;
				}
			}
		}
		int getPF()const {return portee_flamme_;}
		
	protected:
		int portee_flamme_;
};

class Hydre:public Creature{
	public:
		Hydre(string n,int lv,int pv,int f,int lon,int dose,int pos=0)
		:Creature(n,lv,pv,f,pos),longueur_cou_(lon),dose_poison_(dose){}
		void empoisonne(Creature& bete){
			if(vivant() && bete.vivant()){
				if(distance(bete.getPosition(),getPosition())<=getLON()){
					bete.faiblir(points_attaque()+getDOSE());
					if(vivant() && !bete.vivant())level+=1;
				}
			}
		}
		
		int getLON()const {return longueur_cou_;}
		
		int getDOSE()const {return dose_poison_;}
		
		
		
	protected:
		int longueur_cou_;
		int dose_poison_;
};
void combat(Dragon& dragon,Hydre& hydra){
	hydra.empoisonne(dragon);
	dragon.souffle_sur(hydra);
}
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
int main()
{
  Dragon dragon("Dragon rouge"   , 2, 10, 3, 20         );
  Hydre  hydre ("Hydre maléfique", 2, 10, 1, 10, 1,  42 );

  dragon.afficher();
  cout << "se prépare au combat avec :" << endl;
  hydre.afficher();

  cout << endl;
  cout << "1er combat :" << endl;
  cout << "    les créatures ne sont pas à portée, donc ne peuvent pas s'attaquer."
       << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "Le dragon vole à proximité de l'hydre :" << endl;
  dragon.voler(hydre.position() - 1);
  dragon.afficher();

  cout << endl;
  cout << "L'hydre recule d'un pas :" << endl;
  hydre.deplacer(1);
  hydre.afficher();

  cout << endl;
  cout << "2e combat :" << endl;
  cout << "\
  + l'hydre inflige au dragon une attaque de 3 points\n\
      [ niveau (2) * force (1) + poison (1) = 3 ] ;\n\
  + le dragon inflige à l'hydre une attaque de 6 points\n\
      [ niveau (2) * force (3) = 6 ] ;\n\
  + pendant son attaque, le dragon perd 2 points de vie supplémentaires\n\
       [ correspondant à la distance entre le dragon et l'hydre : 43 - 41 = 2 ].\
" << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "Le dragon avance d'un pas :" << endl;
  dragon.deplacer(1);
  dragon.afficher();

  cout << endl;
  cout << "3e combat :" << endl;
  cout << "\
  + l'hydre inflige au dragon une attaque de 3 points\n\
      [ niveau (2) * force (1) + poison (1) = 3 ] ;\n\
  + le dragon inflige à l'hydre une attaque de 6 points\n\
      [ niveau (2) * force (3) = 6 ] ;\n\
  + pendant son attaque, le dragon perd 1 point de vie supplémentaire\n\
       [ correspondant à la distance entre le dragon et l'hydre : 43 - 42 = 1 ] ;\n\
  + l'hydre est vaincue et le dragon monte au niveau 3.\
" << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "4e Combat :" << endl;
  cout << "    quand une créature est vaincue, rien ne se passe." << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  return 0;
}