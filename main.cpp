#include "Dioses.h" 
#include "Stack.h"

using namespace std;

int main(){
     Dios dios1(5000,"Mariangel");
    
     Dios dios2(5000,"Tito");

     Stack masoLleno(true);
     masoLleno.desplegarCartas();
     Stack masoRepuesto(1);

    for (int i = 0; i < 5; i++)
    {   Cartas carta = masoLleno.obtenerCarta();
        masoRepuesto.agregarCarta(carta);
        if (carta.getTipo()==1)
        {
            cout<<"Sacamos una carta de: " << carta.getTipoString()<<endl;
            carta.cartaMilagro(&dios1,&dios2);
            //carta.cartaMilagro(&dios1,&dios2);
            cout << "Soy "<< dios2.getNombre()<< " y estos son mis fieles: "<<dios2.getFieles()<<endl; 
            cout << "Soy "<< dios1.getNombre()<< " y estos son mis fieles: "<<dios1.getFieles()<<endl<<endl<<endl;
        }else if (carta.getTipo()==2)
        {
            cout<<"Sacamos una carta de: " << carta.getTipoString()<<endl;
            carta.cartaTraicion(&dios1,&dios2);
            cout << "Soy "<< dios2.getNombre()<< " y estos son mis fieles: "<<dios2.getFieles()<<endl; 
            cout << "Soy "<< dios1.getNombre()<< " y estos son mis fieles: "<<dios1.getFieles()<<endl<<endl<<endl;
        }else if (carta.getTipo()==3)
        {
            cout<<"Sacamos una carta de: " << carta.getTipoString()<<endl;
            carta.cartaAnarquia();
            // cout << "Soy "<< dios2.getNombre()<< " y estos son mis fieles: "<<dios2.getFieles()<<endl; 
            // cout << "Soy "<< dios1.getNombre()<< " y estos son mis fieles: "<<dios1.getFieles()<<endl<<endl<<endl;
            
        }else if (carta.getTipo()==4)
        {
            cout<<"Sacamos una carta de: " << carta.getTipoString()<<endl;
            carta.cartaUnion();
            // cout << "Soy "<< dios2.getNombre()<< " y estos son mis fieles: "<<dios2.getFieles()<<endl; 
            // cout << "Soy "<< dios1.getNombre()<< " y estos son mis fieles: "<<dios1.getFieles()<<endl<<endl<<endl;
            
        }else if (carta.getTipo()==5)
        {
            cout<<"Sacamos una carta de: " << carta.getTipoString()<<endl;
            Dios nuevo=carta.cartaNuevoDios(&dios1,&dios2);
            cout << "Soy "<< dios2.getNombre()<< " y estos son mis fieles: "<<dios2.getFieles()<<endl; 
            cout << "Soy "<< dios1.getNombre()<< " y estos son mis fieles: "<<dios1.getFieles()<<endl<<endl<<endl;
            cout << "Soy "<< nuevo.getNombre() << " y estos son mis fieles: "<<nuevo.getFieles()<<endl;
        }else if (carta.getTipo()==5)
        {
            cout<<"Sacamos una carta de: " << carta.getTipoString()<<endl;
            Dios nuevo=carta.cartaNuevoDios(&dios1,&dios2);
            cout << "Soy "<< dios2.getNombre()<< " y estos son mis fieles: "<<dios2.getFieles()<<endl; 
            cout << "Soy "<< dios1.getNombre()<< " y estos son mis fieles: "<<dios1.getFieles()<<endl<<endl<<endl;
            cout << "Soy "<< nuevo.getNombre() << " y estos son mis fieles: "<<nuevo.getFieles()<<endl;
        }else if (carta.getTipo()==5)
        {
            cout<<"Sacamos una carta de: " << carta.getTipoString()<<endl;
            masoLleno.regresaCartas(&masoRepuesto);

            

        }else if (carta.getTipo()==7)
        {
            cout<<"Sacamos una carta de: " << carta.getTipoString()<<endl;
            carta.cartaMuerte(&dios1);
            cout << "Soy "<< dios2.getNombre()<< " y estos son mis fieles: "<<dios2.getFieles()<<endl; 
            cout << "Soy "<< dios1.getNombre()<< " y estos son mis fieles: "<<dios1.getFieles()<<endl<<endl<<endl;
        }
        
    }

    masoRepuesto.desplegarCartas();
    
    


    //  cout <<endl<<endl <<"Antes de la carta de traicion: "<<endl<<endl<<endl;

    //  cout << "Soy "<< dios2.getNombre()<< " y estos son mis fieles: "<<dios2.getFieles()<<endl; 

    //  cout << "Soy "<< dios1.getNombre()<< " y estos son mis fieles: "<<dios1.getFieles()<<endl<<endl<<endl; 
     

    //  dios1.cartaMuerte();
    //  cout <<endl<<endl<<endl;
    //  cout << "Despues de la carta de muerte: "<<endl<<endl<<endl;

    //  cout << "Soy "<< dios1.getNombre()<< " y estos son mis fieles: "<<dios1.getFieles()<<endl<<endl<<endl<<endl; 

     //cout << "Soy "<< dios1.getNombre()<< " y estos son mis fieles: "<<dios1.getFieles()<<endl<<endl<<endl; 

     

    

    return 0;
}






