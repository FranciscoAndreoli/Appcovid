#include<stdio.h>
#include<conio.h>
#include<iostream>
using namespace std;
void ayuda()
{
	cout << "Ayuda" << endl;
	cout << "\nPresionando las tecla indicadas se puede empezar a utilizar las diferentes funcionalidades de nuestro software.";
	cout << "\n Las opciones 1, 2, 3 y 4 le permiten gestionar todo lo relacionado a insumos, medicos, pacientes e internaciones respectivamente. Realizar el alta, la baja y la modificacion de los elementos que desee en cada una de las opciones"<<endl;
}
int main()
{
	int opcion;
  do {
       cout << "\n*****************************************************";
       cout << "\nMenu IRIDIUM  Para Gestion De Recursos Hospitalarios";
       cout << "\n*****************************************************";
       cout << "\n 1. Gestion de Insumos";
       cout << "\n 2. Gestion de Medicos";
       cout << "\n 3. Gestion de Pacientes";
       cout << "\n 4. Gestion de Internacion";
       cout << "\n 5. Ayuda";
       cout << "\n 6. Salir";
       cout << "\nIngrese su eleccion: ";
       cin >> opcion;
       switch(opcion) {
	      case 1: 
		  		cout << "\n1. Insumos";
	      		system("C:\\Iridium\\Insumos.exe");
            	cout<<"\n\n\nPresione una tecla para volver al menu";
		        getch();
		        break;
	      case 2:  
		  		cout << "\n 2. Medico";
	      		system("C:\\Iridium\\Medicos.exe");
		        cout<<"\n\n\nPresione una tecla para volver al menu";
		        getch();
		        break;
	      case 3:
	      	   cout << "\n 3. Pacientes";
	      	   system("C:\\Iridium\\Pacientes.exe");
		       cout<<"\n\n\nPresione una tecla para volver al menu";
		       getch();
		       break;
	      case 4:  
	      	   cout << "\n 4. Internacion";
	      	   system("C:\\Iridium\\Internacion.exe");
		       cout<<"\n\n\nPresione una tecla para volver al menu";
		       getch();
		       break;
	      case 5:
		  		ayuda();
		  		cout<<"\n\n\nPresione una tecla para volver al menu";
		    	getch();
		    	break;
		  case 6:
		  	
		    ;
       }
     }
  while (opcion != 6);
  
  	return 0;

}
