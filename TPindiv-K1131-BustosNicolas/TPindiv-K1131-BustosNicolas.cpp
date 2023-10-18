#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;

typedef struct
{
    int Legajo;
    char NomyAp[30];
    int Antiguedad;
}Alumnos_s;

typedef struct
{
    int CodM;
    char Nombre[30];
    int Capacidad; //max de alumnos que pueden cursarla
}Materias_s;

typedef struct
{
    int Legajo;
    int CodM;
}Inscripciones_s;

typedef struct
{
    int capacidad;
    int capAux;
    int cantAlInsc;
    int CodAux;
    char NombreMataux[30];
    int antiguedadAux;
    int contadorAntiguedad=0;

}MateriasAux;

typedef struct
{
    int LegajoAux;
    int AntiguedadAux;
    char NomyApAux[30];
}AlumnosAux;

struct Nodo
{
    Alumnos_s datosAlumnos;
    Nodo *sgte;
};


void generacionAlumnos()
{
    Alumnos_s datoalu;

    FILE *archAlumnos;

    archAlumnos= fopen("Alumnos.dat","wb");

    cout<<"Ingrese el Legajo del Alumno (finaliza el ingreso con 0):"<<endl;
    cin>>datoalu.Legajo;

    while(datoalu.Legajo!=0)
    {
        cout<<"Ingrese el Nombre y Apellido del Alumno: "<<endl;
        getchar();
        gets(datoalu.NomyAp);

        cout<<"Ingrese antiguedad"<<endl;
        cin>>datoalu.Antiguedad;

        fwrite(&datoalu, sizeof(datoalu), 1, archAlumnos);

        cout<<"Ingrese el Legajo del Alumno (finaliza el ingreso con 0):"<<endl;
        cin>>datoalu.Legajo;
    }
    fclose(archAlumnos);
}

void lecturaAlumnos()
{
    Alumnos_s datoalu;

    FILE *archAlumnos;

    archAlumnos= fopen("Alumnos.dat","rb");

    if(archAlumnos==NULL)
    {
        cout<<"NO EXISTE EL ARCHIVO"<<endl;
    }

    cout<< "listado de alumnos"<< endl;
    cout << "Legajo " <<" \t Nombre " << " \t Antiguedad" << endl;

    fread(&datoalu, sizeof(datoalu),1,archAlumnos);
        while(!feof(archAlumnos))
        {
            cout <<"  " << datoalu.Legajo << " \t     " << datoalu.NomyAp << "  \t     " << datoalu.Antiguedad << endl;
            fread(&datoalu,sizeof(datoalu),1,archAlumnos);
        }
    fclose(archAlumnos);
}

void generacionMaterias()
{
    Materias_s mate;
    FILE *archMaterias;
    archMaterias=fopen("Materias.dat","wb");
    cout<<"Ingresar codigo de materia (finaliza el ingreso con 0):" <<endl;
    cin>>mate.CodM;
        while(mate.CodM!=0)
        {

            cout<<"Ingrese nombre materia" <<endl;
            getchar();
            gets(mate.Nombre);

            cout<<"Ingrese capacidad disponible" <<endl;
            cin>>mate.Capacidad;


            fwrite(&mate,sizeof(mate),1,archMaterias);

            cout<<"Ingresar codigo de materia (finaliza el ingreso con 0):" <<endl;
            cin>>mate.CodM;
        }
    fclose(archMaterias);
}

void lecturaMaterias()
{
    Materias_s mate;
    FILE *archMaterias;
    archMaterias=fopen("Materias.dat","rb");

    if(archMaterias==NULL)
    {
        cout<<"NO EXISTE EL ARCHIVO"<<endl;
    }
    cout << "Listado de Materias" << endl;
	cout << "Codigo " <<"\t   Nombre " <<"\t\t Capacidad" << endl;
	fread(&mate,sizeof(mate),1,archMaterias);
    while(!feof(archMaterias)){
        cout <<" " << mate.CodM << " \t " << mate.Nombre << " \t      " << mate.Capacidad <<endl;
        fread(&mate,sizeof(mate),1,archMaterias);
    }
    fclose(archMaterias);
}

void generacionInscripciones(){
    Inscripciones_s inscrip;
    FILE *archInscripciones;

    archInscripciones=fopen("Inscripciones.dat","wb");
    cout<<"Ingresar Legajo (finaliza con 0):" <<endl;
    cin>>inscrip.Legajo;
    while(inscrip.Legajo!=0){
        cout<<"Ingrese codigo de materia" <<endl;
        cin>>inscrip.CodM;
        fwrite(&inscrip,sizeof(inscrip),1,archInscripciones);
        cout<<"Ingresar Legajo (finaliza con 0):" <<endl;
        cin>>inscrip.Legajo;
    }
    fclose(archInscripciones);
}

void lecturaInscripciones(){
    Inscripciones_s inscrip;
    FILE *archInscripciones;
    archInscripciones=fopen("Inscripciones.dat","rb");
    if (archInscripciones==NULL){
        cout<<"EL ARCHIVO NO EXISTE"<<endl;
    }
    cout << "Listado de Inscripciones" << endl;
	cout << "Legajo " <<" Codigo" << endl;
	fread(&inscrip,sizeof(inscrip),1,archInscripciones);
    while(!feof(archInscripciones)){
        cout <<"  " << inscrip.Legajo << "      " << inscrip.CodM <<endl;
        fread(&inscrip,sizeof(inscrip),1,archInscripciones);
    }
    fclose(archInscripciones);
}
void insertaOrdenado(Nodo * &lista, Alumnos_s datos)
{
    Nodo *nuevo_nodo= new Nodo();
    nuevo_nodo->datosAlumnos = datos;

    if( (lista==NULL) || (strcmp(nuevo_nodo->datosAlumnos.NomyAp, lista->datosAlumnos.NomyAp)<0))
    {
        nuevo_nodo->sgte=lista;
        lista=nuevo_nodo;
    }
    else
    {
        Nodo *aux1 = lista;
        Nodo *aux2;

            while((aux1 != NULL)&&(strcmp(nuevo_nodo->datosAlumnos.NomyAp, lista->datosAlumnos.NomyAp)>0))
            {
                aux2=aux1;
                aux1=aux1->sgte;
            }
            aux2->sgte=nuevo_nodo;
            nuevo_nodo->sgte=aux1;
    }
}
void mostrarListaRechazados(Nodo*Lista)
{
    cout<<" NOMBRE Y APELLIDO \t\t LEGAJO"<<endl;
    while(Lista != NULL)
    {
        cout<< Lista->datosAlumnos.NomyAp<<" "<<Lista->datosAlumnos.Legajo<<" "<<endl;
        Lista= Lista->sgte;
    }

}
int buscarAlumnoAnt(int legajo, AlumnosAux *alu,int cant2)
{
    int k;
    int ubicacion=0;
    for(k=0; k<cant2; k++)
    {
        if(alu[k].LegajoAux==legajo)
        {
            ubicacion=k;

        }
    }
    return ubicacion;
}
void cargarAlumnoRechazadoLista(Nodo * &lista,int legajo )
{
    Alumnos_s alumno;
    FILE *archAlumnos;
    archAlumnos= fopen("Alumnos.dat","rb");
    fread(&alumno, sizeof(alumno), 1, archAlumnos);

    while(!feof(archAlumnos))
    {
        if(alumno.Legajo==legajo)
        {
            insertaOrdenado(lista,alumno);
        }
        fread(&alumno, sizeof(alumno), 1, archAlumnos);
    }
    fclose(archAlumnos);
}
int copiadatosmate(MateriasAux *datos)
{
    int i=0;
    Materias_s mate;
    FILE *archMaterias;
    archMaterias=fopen("Materias.dat","rb");

    if(archMaterias==NULL)
    {
        cout<<"NO EXISTE EL ARCHIVO"<<endl;
    }
	fread(&mate,sizeof(mate),1,archMaterias);
    while(!feof(archMaterias)){

       datos[i].capacidad=mate.Capacidad;
       datos[i].CodAux= mate.CodM;
       datos[i].capAux= mate.Capacidad;
       strcpy(datos[i].NombreMataux,mate.Nombre);
       datos[i].CodAux= mate.CodM;
        i++;

        fread(&mate,sizeof(mate),1,archMaterias);
    }
    fclose(archMaterias);

    return i;
}
int copiadatosAlumno(AlumnosAux *datos)
{
    int i=0;
    Alumnos_s alu;

    FILE *archAlumnos;

    archAlumnos= fopen("Alumnos.dat","rb");


    if(archAlumnos==NULL)
    {
        cout<<"NO EXISTE EL ARCHIVO"<<endl;
    }
	fread(&alu, sizeof(alu),1,archAlumnos);
        while(!feof(archAlumnos)){

       datos[i].AntiguedadAux=alu.Antiguedad;
       datos[i].LegajoAux= alu.Legajo;
       strcpy(datos[i].NomyApAux, alu.NomyAp);
        i++;

        fread(&alu,sizeof(alu),1,archAlumnos);
    }
    fclose(archAlumnos);

    return i;
}
int buscaMateria(MateriasAux *datos, int pedido, int cant)
{
    int i=0;
    int pos=0;

    for(i=0; i<cant; i++)
    {
        if(datos[i].CodAux == pedido)
        {
            cout<<"Codigo de materia encontrado"<<endl;
            pos=i;

        }
    }

    return pos;

}

void cargarInscriptosAMateria(Nodo * &Lista,MateriasAux *datos,AlumnosAux *alu, int cant,int cant2)
{
    unsigned int pos=0;
    int pedido=0;
    unsigned int anti=0;
    int leg;
    Inscripciones_s inscrip;
    FILE *archInscripciones;
    archInscripciones=fopen("Inscripciones.dat","rb");
    if (archInscripciones==NULL){
        cout<<"EL ARCHIVO NO EXISTE"<<endl;
    }

	fread(&inscrip,sizeof(inscrip),1,archInscripciones);
    while(!feof(archInscripciones)){

        pedido=inscrip.CodM;
        pos=buscaMateria(datos,pedido,cant);
        leg=inscrip.Legajo;

        if(datos[pos].capAux<=0)
        {
            cout<<"alumno rechazado"<<endl;
               cargarAlumnoRechazadoLista(Lista, leg);//inserto a lista de rechazados
        }
        else
        {
            anti=buscarAlumnoAnt(leg,alu,cant2);
            datos[pos].antiguedadAux+=alu[anti].AntiguedadAux;
            datos[pos].contadorAntiguedad++;
            datos[pos].capAux--;
        }

        fread(&inscrip,sizeof(inscrip),1,archInscripciones);
    }
    fclose(archInscripciones);
}

int MateriasinInscriptos(MateriasAux *datos, int cant)
{
    int j=0;
    int cantidadSin=0;

    for(j=0;j<cant;j++)
    {
        if(datos[j].capacidad == datos[j].capAux)
        {
            cantidadSin++;
        }

    }
    return cantidadSin;
}


void imprimePromedioant(MateriasAux *datos, int cant)
{
    int n=0;
    float prom[cant];


    for(n=0; n<cant;n++)
    {
        if(datos[n].contadorAntiguedad!=0)
        {
            prom[n]=(float)(datos[n].antiguedadAux)/datos[n].contadorAntiguedad;
        }
        else
        {
            prom[n]=0;
        }
        cout<<"Promedio de antiguedad :"<<prom[n]<<" Materia: "<<datos[n].NombreMataux<<endl;
    }
}


int main()
{
    Nodo* Lista = NULL;
    MateriasAux Datos[40];
    AlumnosAux Alumnos[999];
    int posicion=0;
    int posicion2=0;
    int cant_Mat_Sin=0;
    int opcion;
    cout << "**********************************************************************************************************************" << endl;
    cout << "\t\t\t\t\t Elegir opcion deseada(leer archivos antes de probar funcionalidades)" << endl;
    cout << "\t\t\t\t\t 1. Generacion de Archivo Alumnos" << endl;
    cout << "\t\t\t\t\t 2. Lectura Archivo ALUMNOS" << endl;
    cout << "\t\t\t\t\t 3. Generacion Archivo Materias" << endl;
    cout << "\t\t\t\t\t 4. Lectura Archivo Materias" << endl;
    cout << "\t\t\t\t\t 5. Generacion Archivo Inscripciones" << endl;
    cout << "\t\t\t\t\t 6. Lectura Archivo Inscripciones" << endl;
    cout << "\t\t\t\t\t 7. Cargar Inscripciones en Materias" << endl;
    cout << "\t\t\t\t\t 8. Cantidad de materias sin inscriptos" << endl;
    cout << "\t\t\t\t\t 9. Promedio antiguedad de inscriptos por materia" << endl;
    cout << "\t\t\t\t\t 10. Alumnos no inscriptos por exceder capacidad" << endl;
    cout << "\t\t\t\t\t 11. Salir" << endl;
    cout << "***********************************************************************************************************************" << endl;
    cin >> opcion;
    while(opcion!=11){
                    switch(opcion){
                        case 1:
                        generacionAlumnos();
                        break;

                        case 2:
                        lecturaAlumnos();
                        posicion2=copiadatosAlumno(Alumnos);
                        break;

                        case 3:
                        generacionMaterias();
                        break;

                        case 4:
                        lecturaMaterias();
                        posicion=copiadatosmate(Datos);
                        break;

                        case 5:
                        generacionInscripciones();
                        break;

                        case 6:
                        lecturaInscripciones();
                        break;

                        case 7:

                            cargarInscriptosAMateria(Lista,Datos,Alumnos, posicion,posicion2);

                        break;

                        case 8:
                            cant_Mat_Sin=MateriasinInscriptos(Datos, posicion);
                            cout<<"Cantidad de Materias que no tuvieron ningun alumno inscripto: "<<cant_Mat_Sin<<endl;
                        break;

                        case 9:
                            imprimePromedioant(Datos, posicion);

                        break;

                        case 10:
                            mostrarListaRechazados(Lista);

                        break;

                        default:
                        cout <<"ERROR! La opcion seleccionada es invalida"<<endl;
                        break;
                    }
            cout << "********************************************************************************************************************" << endl;
            cout << "\t\t\t\t\t Elegir opcion deseada (leer archivos antes de probar funcionalidades)" << endl;
            cout << "\t\t\t\t\t 1. Generacion de Archivo Alumnos" << endl;
            cout << "\t\t\t\t\t 2. Lectura Archivo ALUMNOS" << endl;
            cout << "\t\t\t\t\t 3. Generacion Archivo Materias" << endl;
            cout << "\t\t\t\t\t 4. Lectura Archivo Materias" << endl;
            cout << "\t\t\t\t\t 5. Generacion Archivo Inscripciones" << endl;
            cout << "\t\t\t\t\t 6. Lectura Archivo Inscripciones" << endl;
            cout << "\t\t\t\t\t 7. Cargar Inscripciones en Materias" << endl;
            cout << "\t\t\t\t\t 8. Cantidad de materias sin inscriptos" << endl;
            cout << "\t\t\t\t\t 9. Promedio antiguedad de inscriptos por materia" << endl;
            cout << "\t\t\t\t\t 10. Alumnos no inscriptos por exceder capacidad" << endl;
            cout << "\t\t\t\t\t 11. Salir" << endl;
            cout << "*********************************************************************************************************************" << endl;
            cin >> opcion;
    }

    cout<<"\t\t\t\t\t EL PROGRAMA HA FINALIZADO"<<endl;
    return 0;
}
