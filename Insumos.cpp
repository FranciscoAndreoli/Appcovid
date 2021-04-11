#include <stdio.h>
#include <iostream>
#include <conio.h>

using namespace std;

struct insumos {
	int codigo;
	int stockActual;
	float precioUnitario;
	int stockMinimo;
	char nombre[30];
	bool bajaLogica;//1 activo 0 inactivo
};

void altasInsumos ();
long buscarInsumos (FILE *m, int leg);
void buscarInsumosxCod ();
void bajasInsumos ();
void depuracion ();
void modificacionesInsumos ();
void ayuda ();

int main()
{
	int opcion;
  do {
       cout << "\nOpciones del ABM del Archivo Insumos";
       cout << "\n1.Altas de insumos.";
       cout << "\n2.Modificaciones";
       cout << "\n3.Bajas Insumos";
       cout << "\n4.Buscar insumos por Codigo.";
       cout << "\n5.Depurar Archivo Insumos";
       cout << "\n6.Ayuda.";
       cout << "\n7.Salir";
       cout << "\nIngrese su eleccion: ";
       cin >> opcion;
       switch(opcion) {
	      case 1:  altasInsumos ();
            	cout<<"\nPresione una tecla para volver al menu";
		        getch();
		        break;
	      case 2:  modificacionesInsumos ();
		       cout<<"\nPresione una tecla para volver al menu";
		       getch();
		       break;
	      case 3:  bajasInsumos ();
		       cout<<"\nPresione una tecla para volver al menu";
		       getch();
		       break;
	      case 4: buscarInsumosxCod ();
		       cout<<"\nPresione una tecla para volver al menu";
		       getch();
		       break;
	      case 5: depuracion ();
		       cout<<"\nPresione una tecla para volver al menu";
		       getch();
		       break;
	      case 6: 
	      		ayuda ();
		  case 7:  ;
       }
     }
  while (opcion != 7);
  
  	return 0;

}
void altasInsumos ()
{
  FILE *m;
  m = fopen ("insumos.dat" , "a+b");
  if (m == NULL) {
		   cout << "Error de Apertura";
		   cout << "\nPresione una tecla... ";
		   getch();
		   exit (1);
		 }
      else {
	     insumos i;
	     long tam = sizeof (insumos);
	     cout << "\nIngrese codigo (con cero termina): ";
	     cin >> i.codigo;
	     
	     while (i.codigo != 0)
	       {
		 long pos = buscarInsumos (m, i.codigo);
		 if (pos == -1L){
				// no estaba repetido... lo carga y lo graba.
				cout << "Ingrese nombre: ";
				cin>> i.nombre;
				cout << "Ingrese stockActual: ";
				cin >> i.stockActual;
				cout << "Ingrese precioUnitario: ";
				cin >> i.precioUnitario;
				cout << "Ingrese stockMinimo: ";
				cin >> i.stockMinimo;
				i.bajaLogica = 1;
				fwrite (&i, tam, 1, m);
			}
		 else {
				cout << "\nCodigo repetido... ";
				cout << "\n...Alta rechazada";
				cout << "\nPulse una tecla para seguir...";
				getch();
		      }
		 //clrscr();
		 cout << "\nIngrese otro Codigo (con cero termina): ";
		 cin >> i.codigo;
	       }
	     fclose (m);
	   }
}


long buscarInsumos (FILE *m, int cod)
// Esta función busca un codigo en el archivo de insumos
// Si lo encuentra, retorna su posición (como número de byte)
// Si no lo encuentra, retorna el valor long -1 (o sea, -1L)
{  insumos r;
   int encontrado = 0;
   long pos_actual = ftell(m), tam = sizeof(insumos);
   long lugar = -1L;
   rewind (m);
   fread (&r, tam, 1, m);
   while (feof(m) == 0 && encontrado == 0) {
       if (r.bajaLogica == 1 && r.codigo == cod) {
			      encontrado = 1;
			      lugar = ftell(m) - tam;
			    }
       else  fread (&r, tam, 1, m);
   }
   fseek (m, pos_actual, SEEK_SET);
   return lugar;
}

void buscarInsumosxCod ()
// Esta función busca y muestra Insumos a partir de un codigo ingresado por el usuario.
// Si lo encuentra, retorna su posición (como número de byte)
// Si no lo encuentra, retorna el valor long -1 (o sea, -1L)
{  
  FILE *m;
  m = fopen ("insumos.dat","r+b");
  if (m == NULL) {
		   cout<< "Error de apertura:";
		   cout<< "\nPresione una tecla... ";
		   getch();
		   exit (1);
		 }
		 else{
		 		insumos r;
		 		int cod=0;
		 		int encontrado = 0;
		 		int flag=0;
		 		long pos_actual = 0;
		 		long tam = 0;
		 		cout << "Ingrese codigo del insumo (cero termina): ";
	   			cin >> cod;
	   			while (cod != 0 && encontrado==0 && flag!=1){
			    	pos_actual = ftell(m), tam = sizeof(insumos);
			        long lugar = -1L;
			    	rewind (m);
			    	fread (&r, tam, 1, m);
			    	while (feof(m) == 0 && encontrado == 0) {
				       if (r.bajaLogica == 1 && r.codigo == cod) {
							      encontrado = 1;
							      lugar = ftell(m) - tam;
							    }
				       else  fread (&r, tam, 1, m);
			   		}
			  
			  	if(encontrado==1){
			  			fseek (m, pos_actual, SEEK_SET);
					    cout << "\n\nEl insumo actual es: ";
						cout<< "\nCodigo:   " << r.codigo;
						cout<< "\nNombre:   " << r.nombre;
				        cout<< "\nStock Actual: " << r.stockActual;
				        cout<< "\nP Unitario: " << r.precioUnitario;
				        cout<< "\nStock Minimo: " << r.stockMinimo;
					  }else{
					  	flag=1;
					  	cout << "\nNo Existe Insumo registrado con el Codigo: "<< cod;
					  }
				}
				fclose(m);
			}
}
void bajasInsumos ()
{
  FILE *m;
  m = fopen ("insumos.dat","r+b");
  if (m == NULL) {
		   cout<< "Error de apertura:";
		   cout<< "\nPresione una tecla... ";
		   getch();
		   exit (1);
		 }
     else{
	   insumos r;
	   int res;
	   long tam = sizeof (insumos);
	   long pos;
	   cout << "Ingrese codigo del insumos a borrar (cero termina): ";
	   cin >> r.codigo;
	   while (r.codigo != 0){
			char elec;
			pos = buscarInsumos (m, r.codigo);
			if (pos != -1L){
				// lo encontró y lo lee...
				fseek(m, pos, SEEK_SET);
				fread (&r, tam, 1, m);
				// ...muestra el registro como estaba...
				cout << "\n\nEl registro actual es: ";
				cout << "Codigo: " << r.codigo;
				cout<< "\nNombre:   " << r.nombre;
			

				cout << "\n\n\nEsta  seguro de borrarlo (s/n)?: ";
				cin >> elec;
				if (elec == 's'){ // lo marca como borrado...
						  r.bajaLogica = 0;

						  // ... reubica el puntero...
						  fseek(m, pos, SEEK_SET);

						  // ... y lo vuelve a grabar
						  fwrite(&r, tam, 1, m);

						  cout << "\nRegistro borrado... ";
						  cout << "\nPulse una tecla...";
						  getch();
						}
				}
			else {cout<< "\nEse registro no existe";
			      cout<<"\nPulse una tecla para seguir";
			      getch();
			     }
			system("cls");
			cout << "Ingrese otro legajo (con cero termina): ";
			cin >> r.codigo;
	   }
	   fclose (m);
	 }
}

void depuracion ()
{
  FILE *m;
  m = fopen ("insumos.dat","rb");
  if (m == NULL) {
		   cout<< "Error de apertura:";
		   cout<< "\nPresione una tecla... ";
		   getch();
		   exit (1);
		 }
     else{
	  FILE *t;
	  int res;
	  long tam = sizeof (insumos);
	  insumos r;
	  cout << "\nProcediendo a compactar el archivo insumos";
	  cout << "\n\nPulse una tecla para empezar...";
	  getch();
	  t = fopen ("nuevo.dat" , "wb");
	  if (t == NULL){
		   cout << "\n\nError de Apertura del archivo temporal";
		   cout << "\nPresione una tecla... ";
		   getch();
		   fclose(m);
		   exit (1);
	  }
	     else {
		   fread(&r,tam,1,m);
		   while (feof(m) == 0){
			 if (r.bajaLogica == 1) fwrite (&r, tam, 1, t);
			 fread(&r,tam,1,m);
		   }
		   fclose(m);
		   fclose(t);
		   remove("insumos.dat");
		   rename("nuevo.dat", "insumos.dat");
		   cout<<"\n\nCompactación terminada...";
	  }
	 }
}


void modificacionesInsumos ()
{
  FILE *m;
  m = fopen ("insumos.dat","r+b");
  if (m == NULL) {
		    cout<< "error de apertura:";
		    cout<< "\nPresione una tecla... ";
		    getch();
		    exit (1);
		 }
     else{
	   insumos r;
	   int res;
	   long tam = sizeof (insumos);
	   long pos;
	   cout << "Ingrese Codigo del insumo a modificar cambiar (cero termina): ";
	   cin >> r.codigo;
	   while (r.codigo != 0){
			int elec;
			pos = buscarInsumos (m, r.codigo);
			if (pos != -1L){
				// lo encontr¢ y lo lee...
				fseek(m, pos, SEEK_SET);
				fread (&r, tam, 1, m);
				// ...muestra el registro como estaba...
				cout << "\n\nEl insumo actual es: ";
				cout<< "\nCodigo:   " << r.codigo;
				cout<< "\nNombre:   " << r.nombre;
				cout<< "\nStock Actual: " << r.stockActual;
				cout<< "\nP Unitario: " << r.precioUnitario;
				cout<< "\nStock Minimo: " << r.stockMinimo;
				// ...modifica el valor de los campos...
				do
				{
					cout<< "\n\nElija que desea Modificar.";
				   cout<< "\n1.Nombre.";
				   cout<< "\n2.Stock Actual.";
				   cout<< "\n3.P Unitario.";
				   cout<< "\n4.Stock Minimo.";
				   cout << "\n5.Salir.";
				   cout<< "\n\nIngrese opción: ";
				   cin >> elec;
				   switch(elec){
					case 1: cout << "\nNuevo Nombre: ";
						cin>> r.nombre;
						break;
					case 2: cout << "\nNuevo Stock Actual: ";
						cin >>r.stockActual;
						break;
					case 3: cout << "\nNuevo P Unitario: ";
						cin >>r.precioUnitario;
						break;
					case 4: cout << "\nNuevo Stock Minimo: ";
						cin >>r.stockMinimo;
						break;
					case 5: ;
				   }
                }
				while (elec != 5);
				//...Registro modificado en memoria...
				//...Ahora reubica su posición en el archivo...
				fseek(m, pos, SEEK_SET);
				//...y vuelve a grabar el registro.
				fwrite(&r, tam, 1, m);
			}
			else {cout<< "\nEse insumo no existe";
			      cout<< "\nPulse una tecla para seguir...";
			      getch();
			     }
			system("cls");
			cout << "Ingrese otro codigo (con cero termina): ";
			cin >> r.codigo;
	   }
	   fclose (m);
	 }
}

void ayuda (){

 	cout << "\nPresionando las tecla indicadas se puede empezar a utilizar las diferentes funcionalidades de nuestro software.";
 	cout << "\n1 de Altas de insumos -> Destinado a realizar las altas de los nuevos insumos adquiridos por el cliente.";
	cout << "\nEn Insumo se puede agregar los campos -Nombre -Stock Actual -Precio Unitario -Stock Minimo.";


}
