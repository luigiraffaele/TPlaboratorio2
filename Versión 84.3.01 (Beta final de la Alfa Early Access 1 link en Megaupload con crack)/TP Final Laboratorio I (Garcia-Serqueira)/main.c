#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include "gotoxy.h"
#define MAX_BUF 50
#define ESC 27
const char *meses[] = {"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};
const char *dias[] = {"Domingo","Lunes","Martes","Miercoles","Jueves","Viernes","Sabado"};
const char nombre_archivoPELI[]="PELICULAS.dat";
const char nombre_archivoUSER[]="USUARIOS.dat";

typedef struct
{
    int idUsuario;
    char nombreUsuario[30];
    int pass[2][5];
    int anioNacimiento;
    char genero;  // ‘m’ o ‘f’
    char pais[20];
    int peliculasVistas[30]; //Guarda los id de las películas.
    int cantVistas; // Es el válidos de películas vistas.
    int eliminado;   // indica 1 o 0 si el cliente fue eliminado
} stUsuario;

typedef struct
{
    int idPelicula;
    char nombrePelicula[50];//cambio documentado
    char nombreOrigPeli[50];//cambio documentado
    char director[40];      //cambio documentado
    char genero[20];
    char pais[20];
    int anio;
    float valoracion;
    int pm;
///    (0- si es ATP / 13: mayor de trece / 16: mayor de 16 / 18: mayor de 18;
    int eliminado;  // indica 1 o 0 si la película fue eliminada
} stPelicula;

void formatoFecha()
{
    char buf[MAX_BUF];
    time_t seconds = time(NULL);
    struct tm *now = localtime(&seconds);

    (void) printf("%s, %s %d, %d\n", dias[now->tm_wday], meses[now->tm_mon], now->tm_mday, now->tm_year + 1900);
    (void) strftime(buf, MAX_BUF, "%A, %B %e, %Y", now);
    (void) printf("%s\n", buf);
    return EXIT_SUCCESS;
}

///FUNCIONES USUARIOS Y ADMIN
void registroUsuarioUNO (char nombre_archivoUSER[]); /// Carga un usuario solo utilizado en las altas tanto de admin como de registro

void pass_Encrypt (int Mat[2][5], char pass[11]); ///Pasa de la contraseña escrita por el usuario a una matriz de numeros

void pass_Decrypt (char passVacio[10], int ContraMatri[2][5]); /// Proceso inverso a la funcion anterior

int pass_verf(int pass_1[2][5],int pass_2[2][5]);

int Logueo_Usr (char nombre_archivo[]); ///Funcion para logueo del usuario devuelve el id del usuario en caso de acierto,caso contrario 0

int cantidadElementoUsuarios(char nombre_archivo[]);

void mostrarcontrasena(char contra[][5]);

void muestraUsuario (stUsuario muestra); ///Muestra un Usuario , utilizado en sub menu de usuario y como modulo para una funcion en admin

void mostrarUsuarios(char nombre_archivoUSER[]);

int consultaIDuser(char nombre_archivoUSER[], int ID);

void mod_campo_usuario(char nombre_archivo[],int ID_usr);

void mod_campos_usuario(char nombre_archivo[],int ID_usr);

int validacionNombreArchivo(char nombre_archivoUSER[],char nombreAComparar[30]);

int verf_campo_elim(char nombre_archivo[], int ID_peli); ///-1 si no esta , 0 si esta disponible y 1 si esta eliminada

void mod_campo_pelisvist(char nombre_archivo[], int ID_peli,int ID_usr); ///Agrega en 1 la cantidad de vistas , y agrega el id de la pelicula que se esta viendo al arreglo del usuario

int valor_cantidad_vistas(int id_usr,char nombre_archivo[]); /// necesita el id del usuario que logueo y devuelve la cantidad de vistas

int  peliculas_que_vio(char nombre_archivo[],int id_usr,char generoMasVisto[],int ids_peliculas_usr[]); ///modifica un arreglo con los ids de las peliculas que vio el usuario en el ambito del sub menu y devuelve la cantidad de vistas

void IDS_a_genero(char nombre_archivo[],int arregloDeIDS[],int val_deIDS,char arreglovaciodeGeneros[][20]);   /// va a pasar cada id de pelicula en su correspondiente genero

void mayor_genero(int val, char generos_usr[][20],char genero_masVisto[]);

void sugerenciasConVistas( char nombre_archivo[],char genero_para_buscar[]);

void sugerenciasNoVistas(char nombre_archivo[]);

///FUNCIONES PELICULAS

void cargarPeliculas(char nombre_archivoPELI[]);

void mod_campo_peliculas(char nombre_archivo[],int ID_pel);

int cantidadElementoPeliculas(char nombre_archivo[]);

void mostrarPeliculas(char nombre_archivo[]);

void ver_perfil(char nombre_archivo[], int ID);

void consultarID(char nombre_archivo[], int ID);

void muestraPelicula (stPelicula xyz);

int validacionNombrePeliculaA(char nombre_archivoPELI[],char nombreAComparar[30]);

int validacionNombrePeliculaB(char nombre_archivoPELI[],char nombreAComparar[30]);

///Funciones Listados
int bajadaAarreglo( char nombre_archivo[],stPelicula a[],int dim);

int posicionMenor (stPelicula a[], int posicion, int validos);

void ordenacionSeleccion(stPelicula a[],int validos);

void insertar_ordenado(stPelicula a[],int bandera,stPelicula dato);

void ordenacionInsercion(stPelicula a[],int validos);

void listados_muestra_pelis(stPelicula a[],int validos);
///Menus ------------------------------------------------------------------

void menuPrincipal();

void switchPrincipal(int op);

void switchMenuUsuario(int op,int id_us);

void menuOpciones();

void switchMenuPeliculas(int op, char nombre_archivo[]);

void switchMenuBajaUsuario(int op);

int main()
{
    menuPrincipal();
gotoxy(50,10);
printf("GRACIAS POR TANTO\n");
gotoxy(50,11);
printf("\t  Y\n");
gotoxy(50,12);
printf("PERDON POR TAN POCO \n");

}
void menuPrincipal(int op)
{
    system("color 02");
    char control;
    int opcion;
    do
    {
        system("cls");
        formatoFecha();
        printf("\n(Ingrese una opcion)\n");
        printf("\n1. INICIAR SESION");
        printf("\n2. ADMIN");
        printf("\n3. REGISTRARSE");
        printf("\n4. OPCIONES");
        printf("\n0. SALIR");
        printf("\n\nOPCION: ");
        fflush(stdin);
        scanf("%i", &opcion);
        system("cls");
        switchPrincipal(opcion);

        system("cls");
        printf("Desea volver al Menu Principal?\n(s) MENU\n(n) FINALIZAR APLICACION\n\n");
        fflush(stdin);
        printf("%c\n", control = getch());

    }
    while(control == 's');
    system("cls");
}

void switchPrincipal(int op)
{
    int id;
    int correcto=1;
    int result=0;
    switch(op)
    {
    case 1:
        while (correcto==1)
        {
            result=Logueo_Usr(nombre_archivoUSER);
            if(result>0)
            {
                correcto=0;
            }
        }
        system("pause");
        system("cls");
        switchMenuUsuario(op,result);
        system("pause");
        system("cls");
        break;
    case 2:
        while (correcto==1)
        {
            result=Logueo_ADM(nombre_archivoUSER);
            if(result>0)
            {
                correcto=0;
            }
        }
        system("pause");
        system("cls");
        switchMenuADM(op,result);
        system("pause");
        system("cls");
        break;
    case 3:
        registroUsuarioUNO(nombre_archivoUSER);
        system("pause");
        system("cls");
        break;
    case 4:
        menuOpciones();
        system("pause");
        system("cls");
        break;
    case 0:
        printf("\n\nFINALIZANDO APLICACION...\n");
        break;
    default:
        printf("//OPCION INVALIDA//\n\nPor favor, intente nuevamente.\n");
        system("pause");
        system("cls");
        break;
    }
}
void switchMenuUsuario(int op,int id_us)
{
    int id=id_us;
    char control;

    /// Seccion Listados
    int dimension=cantidadElementoPeliculas(nombre_archivoPELI);
    stPelicula peliculas_orden[dimension];
    bajadaAarreglo(nombre_archivoPELI,peliculas_orden,dimension);
    int listas;

///VER PELICULA

    int peli_vista;
    int check=0;

    ///SUGERENCIAS
    char genero_MV[20];
    int arreglo_pelis_usr[30];
    int Pelis_delUsr_vistas=0;
    char arreglo_generos[30][20];
    char genero_masVisto[20];
    do
    {
        printf("\n(Ingrese una opcion)\n");
        printf("\n1. VER PERFIL");
        printf("\n2. MOSTRAR PELICULAS");
        printf("\n3. VER PELICULA");
        printf("\n4. SUGERENCIAS ");
        printf("\n0. SALIR \n");
        fflush(stdin);
        printf("Su opcion: ");
        scanf("%i", &op);
        system("cls");

        switch(op)
        {



        case 1:

            ///MOSTRAR USUARIO

            ver_perfil(nombre_archivoUSER,id);
            system("pause");
            system("cls");
            break;
        case 2:
            ///LISTADOS DE MUESTRA AL USUARIO SOLO ID Y TITULOS

            printf("\n Como desea ver el listado?: 1. [Genero] 2.[Titulo]: ");
            fflush(stdin);
            scanf("%d",&listas);
            if(listas==1)
            {
                ordenacionInsercion(peliculas_orden,dimension);
                listados_muestra_pelis(peliculas_orden,dimension);

            }
            else
            {
                if (listas==2)
                {
                    ordenacionSeleccion(peliculas_orden,dimension);
                    listados_muestra_pelis(peliculas_orden,dimension);

                }
                else
                {
                    printf("\n Opcion invalida\n");
                }
            }
            system("pause");
            system("cls");
            break;
        case 3:

            ///VER PELICULA

            printf("\n Ingrese el ID de la pelicula que desea ver: ");
            fflush(stdin);
            scanf("%d", &peli_vista);

            check=verf_campo_elim(nombre_archivoPELI,peli_vista);
            if(check==0)
            {
                mod_campo_pelisvist(nombre_archivoUSER,peli_vista,id);
            }
            system("pause");
            system("cls");
            break;
        case 4:
            ///RECOMENDACIONES DE PELICULAS
            Pelis_delUsr_vistas=valor_cantidad_vistas(id,nombre_archivoUSER); ///Verifica
            if(Pelis_delUsr_vistas>0)/// si tiene
            {
                peliculas_que_vio(nombre_archivoUSER,id,genero_MV,arreglo_pelis_usr); ///ARREGLO DE IDS DE PELIS
                IDS_a_genero(nombre_archivoPELI,arreglo_pelis_usr,Pelis_delUsr_vistas,arreglo_generos );///pasa los IDS A UN ARREGLO DE GENEROS CON CADA GENERO DE LAS RESPECTIVAS IDS
                mayor_genero(Pelis_delUsr_vistas,arreglo_generos,genero_masVisto);
                sugerenciasConVistas(nombre_archivoPELI,genero_masVisto);
            }
            else /// si no tiene
            {
                sugerenciasNoVistas(nombre_archivoPELI);

            }

            system("pause");
            system("cls");
            break;
        case 0:
            printf("\n\nFINALIZANDO APLICACION...\n");
            break;
        default:
            printf("//OPCION INVALIDA//\n\nPor favor, intente nuevamente.\n");
            system("pause");
            system("cls");
            break;




        }
        system("cls");
        printf("Desea Continuar?\n(s) MENU\n(n) FINALIZAR APLICACION\n\n");
        fflush(stdin);
        printf("%c\n", control = getch());
    }
    while (control=='s');

    system("cls");           ///while ((getche () ) != ESC

}

void switchMenuADM (int op)
{
    char control;
    do
    {


        printf("\nSUB-MENU DE ADMINISTRADOR: ");
        printf("\n(Ingrese una opcion)\n");
        printf("\n1. USUARIOS");
        printf("\n2. PELICULAS");
        //printf("\n3. ");
        printf("\n0. SALIR \n");
        fflush(stdin);
        printf("\nSU OPCION: ");
        fflush(stdin);
        scanf("%i", &op);
        system("cls");

        switch(op)
        {
        case 1:
            switchMenuUsuarioADM();
            system("pause");
            system("cls");
            break;
        case 2:
            switchMenuPelicula();
            system("pause");
            system("cls");
            break;
        case 0:
            printf("\n\nFINALIZANDO APLICACION...\n");
            break;
        }
        system("cls");
        printf("Desea Continuar en ADM?\n(s) MENU\n(n) FINALIZAR APLICACION\n\n");
        fflush(stdin);
        printf("%c\n", control = getch());
    }
    while (control=='s');
}

void switchMenuUsuarioADM()
{
    char control;
    char controlseguir='s';
    int op;
    int ID=0;
    int campo=0;
    int valido=0;
    int flag3=0;
    do
    {
        printf("\n(Ingrese una opcion)\n");
        printf("\n1. DAR DE ALTA UN USUARIO");
        printf("\n2. DAR DE BAJA UN USUARIO");
        printf("\n3. MODIFICAR UN USUARIO");
        printf("\n4. VER TODOS LOS USUARIOS");
        printf("\n0. SALIR \n");
        fflush(stdin);
        scanf("%i", &op);
        system("cls");



        switch (op)
        {
        case 1:
            while (controlseguir == 's')
            {
                registroUsuarioUNO(nombre_archivoUSER);
                printf("\nCargar otro?: ");
                fflush(stdin);
                scanf("%c",&controlseguir);
            }
            system("pause");
            system("cls");
            break;
        case 2:
            printf("\nIngrese el ID a dar de baja: ");
            fflush(stdin);
            scanf("%i",&ID);
            mod_campo_usuario(nombre_archivoUSER, ID);
            system("pause");
            system("cls");
            break;
        case 3:
            printf("\nIngrese el ID del usuario a modificar: ");
            fflush(stdin);
            scanf("%i",&ID);
            valido=consultaIDuser(nombre_archivoUSER, ID); /// falta un while para que no ponga cualquiera
            mod_campos_usuario(nombre_archivoUSER, ID);
            system("pause");
            system("cls");
            break;

        case 4:
            mostrarUsuarios(nombre_archivoUSER);
            system("pause");
            system("cls");
            break;
        case 0:
            printf("\n\nFINALIZANDO APLICACION...\n");
            break;
        }
        system("cls");
        printf("Desea Continuar en ADM Usuarios?\n(s) MENU\n(n) FINALIZAR APLICACION\n\n");
        fflush(stdin);
        printf("%c\n", control = getch());
    }
    while (control=='s');
}

void switchMenuPelicula()
{
    int op;
    int idpeliAeliminar=0;
    int validos=cantidadElementoPeliculas(nombre_archivoPELI);
    stPelicula xyz[validos];
    bajadaAarreglo(nombre_archivoPELI, xyz, validos);
    int consulta=0;
    int IDPelicula=0;
    char control;
    char controlseguir='s';
    do
    {
        printf("\n(Ingrese una opcion)\n");
        printf("\n1. DAR DE ALTA UNA PELICULA");
        printf("\n2. DAR DE BAJA UNA PELICULA");
        printf("\n3. VER TODAS LAS PELICULAS (sin detalle)");
        printf("\n4. CONSULTAR PELICULA X ID (con detalle)");
        printf("\n5. MODIFICAR EL CAMPO DE ALGUNA PELICULA");
        printf("\n0. SALIR \n");
        fflush(stdin);
        scanf("%i", &op);
        system("cls");

        switch(op)
        {
        case 1:
            while (controlseguir == 's')
            {
                cargarPeliculas(nombre_archivoPELI);
                printf("\nCargar otro?: ");
                scanf("%c",&controlseguir);
            }
            system("pause");
            system("cls");
            break;
        case 2:
            printf("\nIngrese el ID de la pelicula a eliminar: ");
            fflush(stdin);
            scanf("%i",&idpeliAeliminar);
            mod_campo_peliculas(nombre_archivoPELI,idpeliAeliminar);
            system("pause");
            system("cls");
            break;
        case 3:
            listados_muestra_pelis(xyz, validos);
            system("pause");
            system("cls");
            break;
        case 4:
            printf("Ingrese el ID a buscar: ");
            fflush(stdin);
            scanf("%i",&consulta);
            consultaID(nombre_archivoPELI, consulta);
            system("pause");
            system("cls");
            break;
        case 5:
            printf("Ingrese el ID de la pelicula a modificar: ");
            fflush(stdin);
            scanf("%i",&IDPelicula);
            mod_campos_peliculas(nombre_archivoPELI, IDPelicula);
            system("pause");
            system("cls");
        case 0:
            printf("\n\nFINALIZANDO APLICACION...\n");
            break;
        default:
            printf("//OPCION INVALIDA//\n\nPor favor, intente nuevamente.\n");
            system("pause");
            system("cls");
            break;
        }
        system("cls");
        printf("Desea Continuar en ADM Peliculas?\n(s) MENU\n(n) FINALIZAR APLICACION\n\n");
        fflush(stdin);
        printf("%c\n", control = getch());
    }
    while (control=='s');
}

void menuOpciones()
{
    char controlcolor;
    int opcion=0;

    printf("Desea cambiar el color? (s/n): ");
    fflush(stdin);
    scanf("%c",&controlcolor);

    if (controlcolor=='s')
    {
        printf("\nElegir opciones de colores: ");
        printf("\033[01;32m\n1. FONDO NEGRO  - TEXTO VERDE");
        printf("\033[22;35m\n2. FONDO NEGRO  - TEXTO VIOLETA");
        printf("\033[22;31m\n3. FONDO NEGRO  - TEXTO ROJO");
        printf("\033[22;37m\n4. FONDO GRIS   - TEXTO NEGRO\n");
        fflush(stdin);
        scanf("%i",&opcion);

        if (opcion==1)
            system("color 02");
        if (opcion==2)
            system("color 0D");
        if (opcion==3)
            system("color 04");
        if (opcion==4)
            system("color 80");
        else
            system("COLOR");
    }
    else
        system("pause");
}

///-------------------------------------------------------------------------------------------------------------------

///Listados y ordenamientos
void ordenacionInsercion(stPelicula a[],int validos)
{
    int bandera=0;
    while (bandera<validos-1)
    {
        insertar_ordenado(a,bandera,a[bandera+1]);
        bandera++;
    }
}
void insertar_ordenado(stPelicula a[],int bandera,stPelicula dato)
{

    int i=bandera;
    while (i>=0 && strcmpi(dato.genero,a[i].genero)==-1)
    {
        a[i+1]=a[i];
        i--;
    }
    a[i+1]=dato;
}
void ordenacionSeleccion(stPelicula a[],int validos)
{
    int posmenor;
    stPelicula aux;
    int i=0;
    while(i<validos-1)
    {
        posmenor=posicionMenor(a,i,validos);
        aux=a[posmenor];
        a[posmenor]=a[i];
        a[i]=aux;
        i++;
    }
}
int posicionMenor (stPelicula a[], int posicion, int validos)
{
    stPelicula menor=a[posicion];
    int posmenor=posicion;
    int i=posicion+1;

    while (i<validos)
    {
        if (strcmpi(menor.nombrePelicula,a[i].nombrePelicula)==1)
        {
            menor=a[i];
            posmenor=i;
        }
        i++;
    }
    return posmenor;
}
int bajadaAarreglo( char nombre_archivo[],stPelicula a[],int dim)
{
    stPelicula bajado;
    FILE *archi;
    int i=0;
    archi=fopen(nombre_archivo,"rb");
    if (archi!=NULL)
    {
        while (fread(&bajado,sizeof(stPelicula),1,archi)>0 && i<dim)
        {
            a[i]=bajado;
            i++;
        }
        fclose(archi);
    }
    else
    {
        printf("Fallo de lectura.");
    }
    return i; /// los validos para despues trabajar con este dato
}

void muestraPelicula (stPelicula xyz)
{

    puts("\n---------------------------------------------");
    printf("\nID Pelicula:           \n\t");
    printf("%d \n",xyz.idPelicula);
    printf("\nNombre de la Pelicula: \n\t");
    puts(xyz.nombrePelicula);
    printf("\nNombre Original:       \n\t");
    puts(xyz.nombreOrigPeli);
    printf("\nDirector:              \n\t");
    puts(xyz.director);
    printf("\nGenero:                \n\t");
    puts(xyz.genero);
    printf("\nPais de Origen:        \n\t");
    puts(xyz.pais);
    printf("\nAnio de estreno:       \n\t");
    printf("%i \n",xyz.anio);
    printf("\nValoracion (segun IMDb)\n\t");
    printf("%.1f/10 \n",xyz.valoracion);
    printf("\nRating segun INCAA:    \n\t");
    if (xyz.pm!=1000)
        if (xyz.pm==0)
            printf("Apto para Todo Publico\n");
    if (xyz.pm==13)
        printf("Apta para mayores de 13\n");
    if (xyz.pm==16)
        printf("Apta para mayores de 16\n");
    if (xyz.pm==18)
        printf("Apta para mayores de 18\n");
    if (xyz.pm!=0 && xyz.pm!=13 && xyz.pm!=16 && xyz.pm!=18)
        printf("Califacion Pendiente.\n");
    puts("\n---------------------------------------------");
}

///---------------------------------------------------------------------------------------------
void registroUsuarioUNO (char nombre_archivoUSER[]) /// Carga un usuario solo utilizado en las altas tanto de admin como de registro
{
    stUsuario nuevo;
    FILE *archi;
    int flag=1;
    char passprovisorio[11];
    int j,k;
    int matix[2][5]= {0};
    char control;
    archi=fopen(nombre_archivoUSER,"ab");
    int correcto=1;
    if (archi!=NULL)
    {
        puts(" \n -------------------------------------");
        nuevo.idUsuario=cantidadElementoUsuarios(nombre_archivoUSER)+1;
        while (correcto==1)
        {
            printf("Ingrese Nombre de Usuario: ");
            fflush(stdin);
            gets(&nuevo.nombreUsuario);
            correcto=validacionNombreArchivo(nombre_archivoUSER,nuevo.nombreUsuario);
            if ((correcto)!=0)
            {
                printf("Usuario no disponible");
            }
        }
        while (flag==1)
        {
            printf("\nIngrese su password: ");
            fflush(stdin);
            gets(passprovisorio);
            if (strlen (passprovisorio)==10)
            {
                flag=0;
            }
        }

        pass_Encrypt(matix,passprovisorio);
        for (j=0; j<2; j++)
        {
            for (k=0; k<5; k++)
            {
                nuevo.pass[j][k]=matix[j][k];
            }
        }
        printf("\nIngrese el anio de nacimiento: ");
        fflush(stdin);
        scanf("%d",&nuevo.anioNacimiento);

        printf("\nIngrese genero (m/f): ");
        fflush(stdin);
        scanf("%c",&nuevo.genero);

        printf("\nIngrese su pais: ");
        fflush(stdin);
        gets(&nuevo.pais);

        nuevo.eliminado=0;
        nuevo.peliculasVistas[0]=0;
        nuevo.cantVistas=0;
        puts("\n -------------------------------------");

        fwrite(&nuevo,sizeof(stUsuario),1,archi);

        fclose(archi);
    }
}
void consultaID(char nombre_archivo[], int ID) ///cons de peli
{
    stPelicula xyz;
    xyz.idPelicula=1;
    FILE *archi;
    archi=fopen(nombre_archivo,"rb");
    if (archi!=NULL)
    {
        while (!feof(archi))
        {
            fread(&xyz,sizeof(stPelicula),1,archi);
            if (!feof(archi))
            {
                if(ID==xyz.idPelicula)
                {
                    muestraPelicula(xyz);
                }
            }
        }
        fclose(archi);
    }
}

int Logueo_Usr (char nombre_archivo[]) ///Funcion para logueo del usuario devuelve el id del usuario en caso de acierto,caso contrario 0
{
    stUsuario aux;
    int segunda_comp=1;
    int acierto=1;
    int noAparece=0;
    int passmatrix[2][5]= {0};
    char nombre_prov[30];
    char pass_prov_ing[11];


    printf("\nIngrese su nombre de usuario: \n");
    fflush(stdin);
    gets(nombre_prov);

    printf("\nIngrese su clave: \n");
    fflush(stdin);
    scanf("%s",pass_prov_ing);
    pass_Encrypt(passmatrix,pass_prov_ing);
    FILE*archi;
    archi=fopen(nombre_archivo,"rb");
    if(archi!=NULL)
    {


        while (!feof(archi) && acierto==1)
        {
            fread(&aux,sizeof(stUsuario),1,archi);
            if (!feof(archi) && acierto==1)
            {
                if (strcmpi(nombre_prov,aux.nombreUsuario)==0 && aux.eliminado==0)
                {
                    acierto =0;
                    segunda_comp=pass_verf(passmatrix,aux.pass);

                    if(segunda_comp==0)
                    {
                        printf("\nIngreso con exito.\n");
                        return aux.idUsuario;
                    }
                    else
                    {
                        printf("\nClave Incorrecta.\n");
                        return 0;
                    }

                }
            }
        }
        if (segunda_comp==1)
        {
            printf("\n Usuario no encontrado \n");
            return 0;
        }
    }

}

int Logueo_ADM () ///Ingreso de usuario para el ADMINISTRADOR
{
    char nombre_prov[30];
    char nombre_adminhardcodeado[30]="admin";
    char pass_provisional[30];
    char pass_adminhardcodeado[11]="santamaria";
    int acierto1=0;
    int acierto2=0;
    int exito=0;

    while (acierto1==0 || acierto2==0)
    {
        printf("\nIngrese su credenciales de ADMIN: \n");
        fflush(stdin);
        gets(nombre_prov);

        printf("\nIngrese su clave: \n");
        fflush(stdin);
        scanf("%s",pass_provisional);

        if (strcmpi(nombre_prov, nombre_adminhardcodeado)==0)
            acierto1=1;
        if (strcmpi(pass_provisional,pass_adminhardcodeado)==0)
            acierto2=1;

        if (acierto1==1 && acierto2==1)
        {
            exito=1;
            printf("BIENVENIDO DE VUELTA.\n");
            return exito;
        }
        else
            printf("\nCredenciales incorrectas.\n");
        system("pause");
        system("cls");

    }
}
int cantidadElementoUsuarios(char nombre_archivo[])
{
    FILE * archi;
    int a=0;
    archi=fopen(nombre_archivo, "rb");
    if (archi!=NULL)
    {
        fseek(archi, 0, SEEK_END);
        a = ftell(archi)/(sizeof(stUsuario));
    }
    return a;
}
void pass_Encrypt (int Mat[2][5], char pass[11]) ///Pasa de la contraseña escrita por el usuario a una matriz de numeros
{
    int Inversa[2][2]= {{1,6},{1,7}};
    int i,f,c,j,k,x=0;
    int ContEncrip[2][5]= {0};

    for (f=0; f<2; f++)
    {
        for (c=0; c<5; c++)
        {
            ContEncrip[f][c]=pass[x];
            x++;
        }
    }


//OPERACION DE MULTIPLICACION
    for (i=0; i<2; i++)
    {
        for (j=0; j<5; j++)
        {
            for (k=0; k<2; k++)
            {
                Mat[i][j]=(Mat[i][j]+(Inversa[i][k]*ContEncrip[k][j]));
            }
        }
    }
}
void pass_Decrypt (char passVacio[11], int ContraMatri[2][5]) /// Proceso inverso a la funcion anterior
{
    int A[2][2]= {{7,-6},{-1,1}};
    int i,j,k,z;
    int Desencriptada[2][5]= {0};
    printf("\nClave: ");

    z=0;
    for (i=0; i<2; i++)
    {
        for (j=0; j<5; j++)
        {

            for (k=0; k<2; k++)
            {
                Desencriptada[i][j]=Desencriptada[i][j]+(A[i][k]*ContraMatri[k][j]);
            }
            passVacio[z]=Desencriptada[i][j];
            printf("%c",passVacio[z]);
            z++;

        }
    }
}
int pass_verf(int pass_1[2][5],int pass_2[2][5])
{
    int j;
    int i;
    int contador=0;
    int u=1;


    for(i=0; i<2; i++)
    {
        for(j=0; j<5; j++)
        {
            if(pass_1[i][j]==pass_2[i][j])
                contador++;
        }
    }
    if(contador==10)
    {
        u=0;
    }
    return u;  /// retorna 1 si no son iguales y 0 si son iguales
}
void muestraUsuario (stUsuario muestra) ///Muestra un Usuario , utilizado en sub menu de usuario y como modulo para una funcion en admin
{
    char password[11];

    puts("\n-------------------------------------");
    printf("\nID num.: %d\n",muestra.idUsuario);
    printf("\nNombre de Usuario: ");
    puts(muestra.nombreUsuario);
    pass_Decrypt(password,muestra.pass);

    if (muestra.genero=='m')
        printf("\nGenero: Masculino");
    else if (muestra.genero=='f')
        printf("\nGenero: Femenino");
    else
        printf("\nGenero: Otro\n");
    printf("\nAnio de nacimiento: %d",muestra.anioNacimiento);
    printf("\nPais: ");
    puts(muestra.pais);
    printf("\nCantidad Peliculas Vistas: %d",muestra.cantVistas);
    printf("\nPeliculas Vistas ID: ");
    int i=0; ///Posicion para poder mostrar todos los Id de las peliculas
    while (i<muestra.cantVistas)
    {
        printf("[%d]",muestra.peliculasVistas[i]);
        i++;

    }
    if (muestra.eliminado==1)
    {
        printf("\nEl usuario esta eliminado.\n");
    }
    else if(muestra.eliminado==0)
    {
        printf("\nEl usuario esta activo.\n");
    }
    puts("\n-------------------------------------");

}
void mostrarUsuarios(char nombre_archivoUSER[])
{
    stUsuario muestra;
    FILE *archi;
    archi=fopen(nombre_archivoUSER,"rb");
    if (archi!=NULL)
    {
        while (!feof(archi))
        {
            fread(&muestra,sizeof(stUsuario),1,archi);
            if (!feof(archi))
            {
                muestraUsuario(muestra);
            }
        }
    }
}
int consultaIDuser(char nombre_archivo[], int ID) ///muestra 1 usuario por id
{
    stUsuario xyz;
    int flag=0;
    FILE *archi;
    archi=fopen(nombre_archivo,"rb");
    if (archi!=NULL)
    {
        while (!feof(archi))
        {
            fread(&xyz,sizeof(stUsuario),1,archi);
            if (!feof(archi))
            {
                if(ID==xyz.idUsuario)
                {
                    muestraUsuario(xyz);
                    flag=1;
                }
            }
        }
        fclose(archi);
    }
    return flag;
}

int validacionNombreArchivo(char nombre_archivoUSER[],char nombreAComparar[30])
{
    stUsuario comparador;
    int flag=0;
    FILE * archi;
    archi=fopen(nombre_archivoUSER,"rb");

    if (archi!=NULL)
    {
        while (!feof(archi) && flag==0)
        {
            fread(&comparador,sizeof(stUsuario),1,archi);
            if (!feof(archi) && flag==0)
            {
                if (strcmpi(nombreAComparar,comparador.nombreUsuario)==0)
                {
                    flag=1;
                }
            }
        }

        return flag;
    }
    else
    {
        printf("No abrio.");
        int validacion=-1;
        return validacion;
    }
}
int verf_campo_elim(char nombre_archivo[], int ID_peli) ///-1 si no esta , 0 si esta disponible y 1 si esta eliminada
{
    stPelicula a;
    int flag=1;
    int posib=-1;
    FILE *archi;
    archi=fopen(nombre_archivo,"rb");
    if (archi!=NULL)
    {
        while (!feof(archi) &&flag==1)
        {
            fread(&a,sizeof(stPelicula),1,archi);
            if (!feof(archi)&&flag==1)
            {
                if(ID_peli==a.idPelicula)
                {
                    flag=0;
                    if (a.eliminado==1)
                    {
                        printf("\nPelicula eliminada");
                        posib=1;

                    }
                    else
                    {
                        printf("\n Pelicula disponible");
                        muestraPelicula(a);
                        posib=0;
                    }
                }
            }
        }
        if (flag==1)
        {
            printf("\n Pelicula no existente");
        }
        fclose(archi);
    }
    return posib;
}
void mod_campo_pelisvist(char nombre_archivo[], int ID_peli,int ID_usr) ///Agrega en 1 la cantidad de vistas , y agrega el id de la pelicula que se esta viendo al arreglo del usuario
{
    stUsuario a;
    int flag=1;
    int i=0;
    FILE *archi;
    archi=fopen(nombre_archivo,"r+b");
    if (archi!=NULL)
    {
        while (!feof(archi) &&flag==1)
        {
            fread(&a,sizeof(stUsuario),1,archi);
            if (!feof(archi)&&flag==1)
            {
                if(ID_usr==a.idUsuario)
                {
                    flag=0;

                    i=a.cantVistas;
                    a.peliculasVistas[i]=ID_peli;
                    a.cantVistas++;
                }
            }
        }
        fseek(archi,sizeof(stUsuario)*(ID_usr-1),SEEK_SET);
        fwrite(&a,sizeof(stUsuario),1,archi);
        fclose(archi);
    }
}
void cargarPeliculas(char nombre_archivoPELI[]) /// carga una pelicula
{
    stPelicula xyz;
    FILE *archi;
    int correctoA=1;
    int correctoB=1;
    char control='s';
    archi=fopen(nombre_archivoPELI,"ab");
    if (archi!=NULL)
    {

        puts("\n ------------------------------------------------");
        xyz.idPelicula=cantidadElementoPeliculas(nombre_archivoPELI)+1;
            while (correctoA==1)
            {
                printf("\nIngrese nombre (en castellano) de la Pelicula: ");
                fflush(stdin);
                gets(&xyz.nombrePelicula);
                correctoA=validacionNombrePeliculaA(nombre_archivoPELI,xyz.nombrePelicula);
                if ((correctoA)!=0)
                {
                    printf("Esa pelicula ya ha sido cargada.");
                }
            }
            while (correctoB==1)
            {
                printf("\nIngrese el nombre en su idioma original:       ");
                fflush(stdin);
                gets(xyz.nombreOrigPeli);
                correctoB=validacionNombrePeliculaB(nombre_archivoPELI,xyz.nombreOrigPeli);
                if ((correctoB)!=0)
                {
                    printf("Esa pelicula ya ha sido cargada.");
                }
            }
        printf("\nIngrese director:                              ");
        fflush(stdin);
        gets(xyz.director);
        printf("\nIngrese genero:                                ");
        fflush(stdin);
        gets(xyz.genero);
        printf("\nIngrese pais de la que proviene:               ");
        fflush(stdin);
        gets(xyz.pais);
        printf("\nIngrese el anio de su estreno:                 ");
        fflush(stdin);
        scanf("%i",&xyz.anio);
        printf("\nIngrese valoracion (segun IMDb):               ");
        fflush(stdin);
        scanf("%f",&xyz.valoracion);
        printf("\nIngrese la calificacion (segun INCAA):          ");///"0": ATP, "13"/"16"/"18": "Mayores de 13/16/18"; Otro número: "Calificación pendiente."
        fflush(stdin);
        scanf("%i",&xyz.pm);
        puts("\n-------------------------------------------------");
        xyz.eliminado=0;

        fwrite(&xyz,sizeof(stPelicula),1,archi);
        fclose(archi);
    }
}
void mod_campo_peliculas(char nombre_archivo[],int ID_pel) /// modifica el campo eliminado de peliculas
{
    stPelicula a;
    int flag=1;
    int i=0;
    FILE *archi;
    archi=fopen(nombre_archivoPELI,"r+b");
    if (archi!=NULL)
    {
        while (!feof(archi) && flag==1)
        {
            fread(&a,sizeof(stPelicula),1,archi);
            if (!feof(archi)&&flag==1)
            {
                if(ID_pel==a.idPelicula)
                {
                    if (a.eliminado==0)
                    {
                        flag=0;
                        a.eliminado=1;
                        printf("\nLa pelicula con el ID %i ha sido eliminada.\n",ID_pel);
                    }
                    else if(a.eliminado==1)
                    {
                        flag=0;
                        a.eliminado=0;
                        printf("\nLa pelicula con el ID %i ha sido restaurada.\n",ID_pel);
                    }
                }
            }
            fseek(archi,sizeof(stPelicula)*(ID_pel-1),SEEK_SET);
            fwrite(&a,sizeof(stPelicula),1,archi);
            fclose(archi);
        }
    }
}
int cantidadElementoPeliculas(char nombre_archivo[])
{
    FILE * archi;
    int a=0;
    archi=fopen(nombre_archivo, "rb");
    if (archi!=NULL)
    {
        fseek(archi, 0, SEEK_END);
        a = ftell(archi)/(sizeof(stPelicula));
        fclose(archi);
    }
    return a;
}
void listados_muestra_pelis(stPelicula a[],int validos) /// listados
{
    int i=0;
    printf(" ID   |    TITULO");
    while (i<validos)
    {
        if (a[i].eliminado!=1)
        {
            if (a[i].idPelicula < 10)
                printf("\n [#00%d] %s",a[i].idPelicula,a[i].nombrePelicula);
            else if (a[i].idPelicula >=10 && a[i].idPelicula < 100)
                printf("\n [#0%d] %s",a[i].idPelicula,a[i].nombrePelicula);
            else
                printf("\n [#%d] %s",a[i].idPelicula,a[i].nombrePelicula);
        }
        i++;

    }
    printf("\n");
}
void mod_campo_usuario(char nombre_archivo[],int ID_usr) /// modifica el campo eliminado solamente
{
    stUsuario a;
    int i=0;
    FILE *archi;
    archi=fopen(nombre_archivo,"r+b");
    if (archi!=NULL)
    {
        fseek(archi,sizeof(stUsuario)*(ID_usr-1),SEEK_SET);
        fread(&a,sizeof(stUsuario),1,archi);




                if (a.eliminado==0)
                {

                    a.eliminado=1;
                    printf("\nEl usuario con el ID %i ha sido eliminado.\n",ID_usr);
                }
                else if(a.eliminado==1)
                {

                    a.eliminado=0;
                    printf("\nEl usuario con el ID %i ha sido restaurado.\n",ID_usr);
                }


        fseek(archi,sizeof(stUsuario)*(ID_usr-1),SEEK_SET);
        fwrite(&a,sizeof(stUsuario),1,archi);
        fclose(archi);
    }
}

void mostrarPeliculas(char nombre_archivo[]) /// muestra una pelicula
{
    stPelicula xyz;
    FILE *archi;
    archi=fopen(nombre_archivo,"rb");
    if (archi!=NULL)
    {
        while (!feof(archi))
        {
            fread(&xyz,sizeof(stPelicula),1,archi);
            if (!feof(archi))
            {
                muestraPelicula(xyz);
            }
        }
        fclose(archi);
    }
}
void ver_perfil(char nombre_archivo[], int ID) /// muestra un perfil entero de usuario
{
    stUsuario a;

    FILE *archi;
    archi=fopen(nombre_archivo,"rb");
    if (archi!=NULL)
    {
        while (!feof(archi))
        {
            fread(&a,sizeof(stUsuario),1,archi);
            if (!feof(archi))
            {
                if(ID==a.idUsuario)
                {
                    muestraUsuario(a);
                }


            }
        }
        fclose(archi);
    }
}
int valor_cantidad_vistas(int id_usr,char nombre_archivo[])/// necesita el id del usuario que logueo y devuelve la cantidad de vistas
{
    stUsuario a;
    int result=0;
    FILE *archi;
    archi=fopen(nombre_archivo,"rb");
    if (archi!=NULL)
    {
        while (!feof(archi))
        {
            fread(&a,sizeof(stUsuario),1,archi);
            if (!feof(archi))
            {
                if(id_usr==a.idUsuario)
                {
                    result=a.cantVistas;
                }

            }
        }
        fclose(archi);
    }
    return result;
}
int  peliculas_que_vio(char nombre_archivo[],int id_usr,char generoMasVisto[],int ids_peliculas_usr[]) ///modifica un arreglo con los ids de las peliculas que vio el usuario en el ambito del sub menu y devuelve la cantidad de vistas
{
    stUsuario a;

    char aux_gen[20];
    int aux_cant=0;
    char gen_mas[20];
    int gen_cant=0;
    int ids_val=0;
    int i=0;
    FILE *archi;
    archi=fopen(nombre_archivo,"rb");
    while (!feof(archi))
    {
        fread(&a,sizeof(stUsuario),1,archi);
        if (!feof(archi))
        {
            if(id_usr==a.idUsuario)
            {
                ids_val=a.cantVistas;
                while (i<ids_val)
                {
                    ids_peliculas_usr[i]=a.peliculasVistas[i];
                    i++;
                }

            }
        }
    }
    fclose(archi);
    return ids_val;
}
void IDS_a_genero(char nombre_archivo[],int arregloDeIDS[],int val_deIDS,char arreglovaciodeGeneros[][20])   /// va a pasar cada id de pelicula en su correspondiente genero
{
    FILE *archi;
    stPelicula a;
    int i=0;
    archi=fopen(nombre_archivo,"rb");
    if(archi!=NULL)
    {
        while (i<val_deIDS)
        {
            while (!feof(archi))
            {
                fread(&a,sizeof(stPelicula),1,archi);
                if (!feof(archi))
                {
                    if(arregloDeIDS[i]==a.idPelicula)
                    {
                        strcpy(arreglovaciodeGeneros,a.genero);
                        i++;
                        fseek(archi,0,SEEK_SET);
                    }

                }
            }
        }
    }
    fclose(archi);
}
void mayor_genero(int val, char generos_usr[][20],char genero_masVisto[]) ///genero mas visto o en su defecto el primer genero que tome de igual cantidad
{
    int aciertos=1;
    int j=0;
    int i=0;
    strcpy(genero_masVisto,generos_usr[i]);
    char aux_genero[20];
    int aciertos_aux=0;
    while (j<val)
    {
        i=0;
        aciertos_aux=0;
        strcpy(aux_genero,generos_usr[j]);
        while (i<val)
        {
            if (strcmpi(aux_genero,generos_usr[i])==0)
            {
                aciertos_aux++;
            }
            i++;
        }

        if(aciertos_aux>aciertos)
        {
            strcpy(genero_masVisto,aux_genero);
            aciertos=aciertos_aux;
        }
        j++;
    }
}
void sugerenciasConVistas( char nombre_archivo[],char genero_para_buscar[]) ///muestra peliculas en base a el mayor genero
{
    stPelicula sug;
    int num_deSug=0;
    FILE *archi;
    archi=fopen(nombre_archivo,"rb");
    if (archi!=NULL)
    {
        printf("\n SUGERENCIAS:");
        while (!feof(archi)&& num_deSug<5)
        {
            fread(&sug,sizeof(stPelicula),1,archi);
            if(!feof(archi) && num_deSug<5)
            {
                if( sug.valoracion>7 && strcmpi(genero_para_buscar,sug.genero)==0)
                {
                    printf("\n[%d]TITULO:%s",sug.idPelicula,sug.nombrePelicula);
                    num_deSug++;
                }
            }
        }
    }
    fclose(archi);
}
void sugerenciasNoVistas(char nombre_archivo[]) /// sugiere peliculas si no tiene vistas
{
    stPelicula sug;
    int num_deSug=0;
    FILE *archi;
    archi=fopen(nombre_archivo,"rb");
    if (archi!=NULL)
    {
        printf("\n SUGERENCIAS:");
        while (!feof(archi)&&num_deSug<5)
        {
            fread(&sug,sizeof(stPelicula),1,archi);
            if(!feof(archi) && num_deSug<5)
            {
                if( sug.valoracion>8)
                {
                    printf("\n[%d]TITULO: %s",sug.idPelicula,sug.nombrePelicula);
                    num_deSug++;
                }
            }
        }
    }
    fclose(archi);
}

void mod_campos_usuario(char nombre_archivo[],int ID_usr) /// modifica los campos de un usuario
{
    stUsuario a;
    int flag3=0;
    int flagNombre=0;
    int i=0;
    char nombProv[30];
    int campo;
    FILE *archi;




    archi=fopen(nombre_archivo,"r+b");
    if (archi!=NULL)
    {

        fseek(archi,sizeof(stUsuario)*(ID_usr-1),SEEK_SET);
        fread(&a,sizeof(stUsuario),1,archi);

        printf("\n1. Anio de Nacimiento");
        printf("\n2. Genero");
        printf("\n3. Pais");
        printf("\n4. Activo/Eliminado\n");

        while (flag3==0)
        {
            printf("\nIngrese el campo a modificar: ");
            fflush(stdin);
            scanf("%i",&campo);
            if (campo>0 && campo<5)
            {
                flag3=1;
            }
        }
        /*
                if (campo==1)
                {
                    while (flagNombre==0)
                    {
                        printf("Ingrese el nuevo nombre de usuario: ");
                        fflush(stdin);
                        scanf("%s",&nombProv);
                        if (validacionNombreArchivo(nombre_archivoUSER, nombProv)==1)
                        {
                            a.nombreUsuario[30]=nombProv;
                            flagNombre=1;
                        }
                        else if(validacionNombreArchivo(nombre_archivoUSER, nombProv)==0)
                            printf("Nombre ocupado, ingrese otro. ");
                        system("pause");
                    }
                }*/
        if (campo==1)
        {
            printf("Modifique el anio de nacimiento: ");
            fflush(stdin);
            scanf("%i",&a.anioNacimiento);
        }
        if (campo==2)
        {
            printf("Modifique el genero: ");
            fflush(stdin);
            a.genero = getche();
        }
        if (campo==3)
        {
            printf("Modifique el pais: ");
            fflush(stdin);
            scanf("%s",&a.genero);
        }
        if (campo==4)
        {
            if (a.eliminado==0)
            {
                a.eliminado=1;
                printf("\nEl usuario con el ID %i ha sido eliminado.\n",ID_usr);
            }
            else if(a.eliminado==1)
            {
                a.eliminado=0;
                printf("\nEl usuario con el ID %i ha sido restaurado.\n",ID_usr);
            }
        }


        fseek(archi,sizeof(stUsuario)*(ID_usr-1),SEEK_SET);
        fwrite(&a,sizeof(stUsuario),1,archi);
        fclose(archi);
    }
}

int validacionNombrePeliculaA(char nombre_archivoPELI[],char nombreAComparar[30])
{
    stPelicula comparador;
    int flag=0;
    FILE * archi;
    archi=fopen(nombre_archivoPELI,"rb");

    if (archi!=NULL)
    {
        while (!feof(archi) && flag==0)
        {
            fread(&comparador,sizeof(stPelicula),1,archi);
            if (!feof(archi) && flag==0)
            {
                if (strcmpi(nombreAComparar,comparador.nombrePelicula)==0)
                {
                    flag=1;
                }
            }
        }

        return flag;
    }
    else
    {
        printf("No abrio.");
        int validacion=-1;
        return validacion;
    }
}
int validacionNombrePeliculaB(char nombre_archivoPELI[],char nombreAComparar[30])
{
    stPelicula comparador;
    int flag=0;
    FILE * archi;
    archi=fopen(nombre_archivoPELI,"rb");

    if (archi!=NULL)
    {
        while (!feof(archi) && flag==0)
        {
            fread(&comparador,sizeof(stPelicula),1,archi);
            if (!feof(archi) && flag==0)
            {
                if (strcmpi(nombreAComparar,comparador.nombreOrigPeli)==0)
                {
                    flag=1;
                }
            }
        }

        return flag;
    }
    else
    {
        printf("No abrio.");
        int validacion=-1;
        return validacion;
    }
}

void mod_campos_peliculas(char nombre_archivo[],int ID_peli) /// modifica los campos de un usuario
{
    stPelicula xyz;
    int flag3=0;
    int flagNombre=0;
    int i=0;
    int correctoA=1;
    int correctoB=1;
    char nombProv[30];
    int campo;
    FILE *archi;

    archi=fopen(nombre_archivo,"r+b");
    if (archi!=NULL)
    {

        fseek(archi,sizeof(stPelicula)*(ID_peli-1),SEEK_SET);
        fread(&xyz,sizeof(stPelicula),1,archi);

        printf("\n1. Nombre en castellano. \t Actual: %s",xyz.nombrePelicula);
        printf("\n2. Nombre Original.      \t Actual: %s",xyz.nombreOrigPeli);
        printf("\n3. Director.             \t Actual: %s",xyz.director);
        printf("\n4. Genero                \t Actual: %s",xyz.genero);
        printf("\n5. Pais                  \t Actual: %s",xyz.pais);
        printf("\n6. Valoracion            \t Actual: %.2f",xyz.valoracion);
        printf("\n7. Anio de estreno       \t Actual: %i",xyz.anio);

        while (flag3==0)
        {
            printf("\nIngrese el campo a modificar: ");
            fflush(stdin);
            scanf("%i",&campo);
            if (campo>0 && campo<8)
            {
                flag3=1;
            }
        }
        if (campo==1)
        {
            while (correctoA==1)
            {
                printf("\Modifique el nombre (en castellano) de la Pelicula: ");
                fflush(stdin);
                gets(&xyz.nombrePelicula);
                correctoA=validacionNombrePeliculaA(nombre_archivoPELI,xyz.nombrePelicula);
                if ((correctoA)!=0)
                {
                    printf("Esa pelicula ya ha sido cargada.");
                }
            }
        }
        if (campo==2)
        {
            while (correctoB==1)
            {
                printf("\Modifique el nombre (original) de la Pelicula: ");
                fflush(stdin);
                gets(&xyz.nombreOrigPeli);
                correctoB=validacionNombrePeliculaB(nombre_archivoPELI,xyz.nombreOrigPeli);
                if ((correctoB)!=0)
                {
                    printf("Esa pelicula ya ha sido cargada.");
                }
            }
        }
        if (campo==3)
        {
            printf("Modifique el director: ");
            fflush(stdin);
            gets(&xyz.director);
        }
        if (campo==4)
        {
            printf("Modifique el genero: ");
            fflush(stdin);
            gets(&xyz.genero);
        }
        if (campo==5)
        {
            printf("Modifique el pais: ");
            fflush(stdin);
            gets(&xyz.pais);
        }
        if (campo==6)
        {
            printf("Modifique la valoracion: ");
            fflush(stdin);
            scanf("%f",&xyz.valoracion);
        }
        if (campo==7)
        {
            printf("Modifique la anio de estreno: ");
            fflush(stdin);
            scanf("%i",&xyz.anio);
        }
        fseek(archi,sizeof(stPelicula)*(ID_peli-1),SEEK_SET);
        fwrite(&xyz,sizeof(stPelicula),1,archi);
        fclose(archi);
    }
}
