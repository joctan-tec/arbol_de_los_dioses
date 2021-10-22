#include "Dioses.h" 

using namespace std;

int main(){
     Dios dios1(5000,"Nayat");
    
     Dios dios2(5000,"Atenea");
     cout <<endl<<endl <<"Antes de la carta de milagro: "<<endl<<endl<<endl;

     cout << "Soy "<< dios2.getNombre()<< " y estos son mis fieles: "<<dios2.getFieles()<<endl; 

     cout << "Soy "<< dios1.getNombre()<< " y estos son mis fieles: "<<dios1.getFieles()<<endl<<endl<<endl; 
     

     dios2 = dios1.cartaMilagro(dios2);

     cout << "Despues de la carta de milagro: "<<endl<<endl<<endl;

     cout << "Soy "<< dios2.getNombre()<< " y estos son mis fieles: "<<dios2.getFieles()<<endl; 

     cout << "Soy "<< dios1.getNombre()<< " y estos son mis fieles: "<<dios1.getFieles()<<endl<<endl<<endl; 

     

    

    return 0;
}






