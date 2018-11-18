#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// ------------------------- ESTRUCTURAS -----------------------------------

typedef struct
{
    int idPelicula;
    char nombrePelicula[60];
    char director[30];
    char genero[20];
    char pais[20];
    int anio;
    int valoracion;
    int pm;
    int eliminado;
} stPelicula;

typedef struct
{
    stPelicula p;
    struct nodoListaPelicula * sig;
} nodoListaPelicula;


typedef struct
{
    stPelicula p;
    struct nodoArbolPelicula * izq;
    struct nodoArbolPelicula * der;
} nodoArbolPelicula;



typedef struct
{
    int admin;
    int idUsuario;
    char nombreUsuario[15];
    char genero;
    char pais[20];
    int pass[2][5];
    int anioNacimiento;
    int eliminado;
} stUsuario;



typedef struct
{
    stUsuario usr;
    nodoListaPelicula * listaPelis;
} stCelda;


typedef struct
{
    int idAutoincremental;
    int idUsuario;
    int idPelicula;
} stPelisVistas;


/// ------------------- FUNCIONES DE PELICULAS ---------------------------------
//Alta

stPelicula cargarPelicula(char nombre_archivoPELI []);  ///Carga una pelicula y la retorna
//Baja
//Modificación
void modificarPeliculas(nodoArbolPelicula *arbol,int id);  ///Permite modificar los valores de los campos de una pelicula
void cargaPeliculaArchivo ( char nombre_archivo[], stPelicula nuevo); ///Carga una estructura de pelicula nuevo al archivo
void sobreEscribirPeliEnArchivo(char nombre_archivo[],stPelicula nuevo);
int validacionNombrePeliculaA(char nombre_archivoPELI[],char nombreAComparar[30]);

/// ----------------------------TDA LISTA SIMPLE -------------------------------------------
//inicLista()
nodoListaPelicula * inicLista();
//crearNodoLista()
nodoListaPelicula * crearNodoListaPelicula(stPelicula pelicula);
//agregarAlPrincipio
nodoListaPelicula * agregarAlPrincipio(nodoListaPelicula * lista, nodoListaPelicula * nuevoNodo);
//agregarAlFinal()
nodoListaPelicula * agregarAlFinal(nodoListaPelicula * lista, nodoListaPelicula * nuevoNodo);
//agregarEnOrdenPorNombreDePelicula()
nodoListaPelicula * agregarEnOrden(nodoListaPelicula * lista, nodoListaPelicula * nuevoNodo);
//mostrarLista()
void mostrarLista(nodoListaPelicula * lista);
//borrarNodoPorIdPelicula()
nodoListaPelicula * borrarNodo(int idPelicula, nodoListaPelicula * lista);

///---------------------------------------- TDA ARBOL --------------------------------------------
//inicArbol()
nodoArbolPelicula* inicArbol ();
//crearNodoArbol()
nodoArbolPelicula * crearNodoArbol(stPelicula pelicula);
//insertarNodoArbol (ordenado por idPelicula)
nodoArbolPelicula* insertarNodoArbol (nodoArbolPelicula* arbol, stPelicula nuevo);
//mostrarArbol (son tres funciones, recorriendo inOrder, postOrder, preOrder)
void mostrarPelicula(stPelicula aux); ///Muestra el contenido de una pelicula
void mostrarPeliculaConNumeros(stPelicula aux);
void Recorriendo_preorder (nodoArbolPelicula*arbol);
void Recorriendo_inorder ( nodoArbolPelicula*arbol);
void Recorriendo_postorder (nodoArbolPelicula * arbol);
stPelicula bajaPeliculas(nodoArbolPelicula *arbol,int id);
//borrarUnNodoArbol (buscarlo por idPelicula)
//auxiliares
nodoArbolPelicula * buscar_nodo_mas_derech(nodoArbolPelicula*arbol);
nodoArbolPelicula * buscar_nodo_mas_izqu(nodoArbolPelicula*arbol);
nodoArbolPelicula * borrarUnNodoArbol (int dato, nodoArbolPelicula* arbol); /// el dato es el id de la pelicula por borrar
nodoArbolPelicula *buscarPelicula (nodoArbolPelicula* arbol, int dato);
//cargarArbolDesdeArchivo()
//auxiliar
int cantidadPelisArchivo( char nombre_archivo_pelis[]);
int ArchivoAArreglo ( char archivo[],stPelicula arreglito[]);
nodoArbolPelicula* ArregloPelisToArbol ( int inic, int fin, int cantidad, nodoArbolPelicula *arbol, stPelicula pelis[]);
nodoArbolPelicula* cargarArbolDesdeArchivo (nodoArbolPelicula * arbol, char nombre_archivo_pelis[]);
///----------------------------FUNCIONES DE PELIS VISTAS---------------------------------------------
/// provisorio
int buscarUsuario(stCelda adl[],int id,int cant);
int cantidadPeliculasVistasArchi(char nombre_archivo[]);
stPelisVistas crearNuevaPeliVista( int idUsr, int idPeli, char nombre_archivo_PelisVistas[]);
void cargaPeliVistasArchivo ( char nombre_archivo[], stPelisVistas nuevo); ///Carga una estructura de pelivista nueva al archivo
void  CargaPeliVistaAlArregloUsr (nodoArbolPelicula*arbol, stCelda arreglo[], int validos_Arreglo, char nombre_archivo[]); ///arreglo de usuarios ya cargado y recorre el archivo de pelisVistas a medidad que encuentra
///----------------------------------- FUNCIONES DE USUARIOS ------------------------------------------
//Alta
void pasarMatrixAString(char contrasenia[11],int contraseniaMatrix[2][5]);
void pasarContraseniaAMatrix(char contrasenia[11],int contraseniaMatrix[2][5]);
void encriptarContrasenia(int contraseniaMatrix[2][5],int pass[2][5]);
void desencriptarContrasenia(int contraseniaMatrix[2][5],int pass[2][5]);
stUsuario cargarUsuario(); ///genera un usuario, lo carga y lo retorna
//Modificación
void mostrarUsuarioConNumeros(stUsuario aux);  ///Muestra el contenido de un usuario listado por numeros
void cargaUsuarioArchivo ( char nombre_archivo[], stUsuario nuevo); ///Carga una estructura de usuario nuevo al archivo
void mostrarUsuario(stCelda adl);
void mostrarListaPelisVistas(nodoListaPelicula *lista, nodoArbolPelicula *arbolPeliculas);
void mostrarUsuarios(stCelda adl[],int cant, nodoArbolPelicula *arbolPeliculas);
int cantidadElementoUsuarios(char nombre_archivo[]);
void sobreEscribirUsuarioEnArchivo(char nombre_archivo[],stUsuario nuevo) ;
int validacionNombreArchivo(char nombre_archivoUSER[],char nombreAComparar[30]);
stUsuario eliminarUsuario(stCelda adl[],int *cant,int id);
int main()
{


    ///SWITCH

    ///Espacio reservado para definicion de variables
    int respuesta;
    char continuar = 's';
    int userValido = 0;
    int adminValido = 0;
    int respuestaOpcionesUser=0;
    char continuarOpcionesUser = 's';
    int respuestaOpcionesAdmin=0;
    char continuarOpcionesAdmin = 's';
    int respuestaOpcionesAdminPeliculas=0;
    char continuarOpcionesAdminPeliculas = 's';
    int respuestaOpcionesAdminUsers=0;
    char continuarOpcionesAdminUsers = 's';

    ///Switch para pantalla inicial

    while(continuar == 's')
    {

        continuarOpcionesAdmin ='s';
        continuarOpcionesAdminPeliculas ='s';
        continuarOpcionesAdminUsers ='s';
        continuarOpcionesUser ='s';

        printf("Bienvenido a NerdFlix \n");

        printf("1. ENTRAR \n");
        printf("2. ADMIN \n");
        printf("3. SIGN UP \n");
        printf("ELIJA OPCION \n");
        scanf("%d",&respuesta);

        system("cls");

        switch(respuesta)
        {

        case 1:  ///ENTRAR ===================================================================================

            /* while(userValido == 0)
             {
                 userValido = validacionUser();
             }
             if(userValido == 1) */
        {
            while(continuarOpcionesUser=='s')
            {

                ///reseteamos las variables para poder utilizar la funcion volver en el switch
                continuarOpcionesAdmin ='s';
                continuarOpcionesAdminPeliculas ='s';
                continuarOpcionesAdminUsers ='s';
                continuarOpcionesUser ='s';



                printf("1.PERFIL \n");

                printf("2.PELICULAS \n");

                printf("3.VER \n");

                printf("4.RECOMENDACIONES \n");

                printf("5.HISTORIAL \n");

                printf("6.SALIR \n");

                printf("ELIJA OPCION \n");

                scanf("%d",&respuestaOpcionesUser);

                system("cls");

                switch(respuestaOpcionesUser)
                {

                case 1: ///PERFIL

                    ///IMPRIME INFORMACION DEL USUARIO
                    break;

                case 2: ///PELICULAS

                    ///SWITCH CON 2 OPCIONES TITULO O GENERO LUEGO MUESTRA LAS PELICULAS ORDENADAS

                    break;

                case 3: /// VER

                    ///FUNCION PARA ELEJIR UNA PELICULA Y VERLA, PODRIA ESTAR ADENTRO DE LA FUNCION ANTERIOR(A DEBATIR)

                    break;

                case 4: /// RECOMENDACIONES

                    ///ORDENA PELICULAS EN BASE A LO QUE FUE VISTO RECIENTEMENTE

                    break;

                case 5: /// HISTORIAL

                    /// IMPRIME HISTORIAL DE PELICULAS VISTAS RECIENTEMENTE

                    break;

                case 6: /// Vuelve al menu anterior

                    continuarOpcionesUser= 'n';



                    break;


                default:

                    printf("opcion invalida\n");

                    break;
                }
            }

        }
        break;
        ///==================================================================================================



        case 2: /// ADMIN ====================================================================================



            /* while(adminValido == 0)
            {
            adminValido = validacionAdmin();
            }
            if(adminValido == 1) */


            while(continuarOpcionesAdmin=='s')
            {

                continuarOpcionesAdmin ='s';
                continuarOpcionesAdminPeliculas ='s';
                continuarOpcionesAdminUsers ='s';
                continuarOpcionesUser ='s';

                printf("1.Administrar Peliculas \n");
                printf("2.Administrar Usuarios \n");
                printf("3.SALIR \n");
                printf("ELIJA UNA OPCION \n");

                scanf("%d",&respuestaOpcionesAdmin);

                system("cls");

                switch(respuestaOpcionesAdmin)
                {

                case 1:///adm peliculas

                    while(continuarOpcionesAdminPeliculas=='s')
                    {

                        continuarOpcionesAdmin ='s';
                        continuarOpcionesAdminPeliculas ='s';
                        continuarOpcionesAdminUsers ='s';
                        continuarOpcionesUser ='s';

                        printf("1.ALTA \n");
                        printf("2.BAJA \n");
                        printf("3.MODIFICAR \n");
                        printf("4.CONSULTA \n");
                        printf("5.LISTADOS \n");
                        printf("6. VOLVER \n");
                        printf("ELIJA UNA OPCION \n");

                        scanf("%d",&respuestaOpcionesAdminPeliculas);

                        system("cls");

                        switch(respuestaOpcionesAdminPeliculas)
                        {

                        case 1: ///alta peliculas

                            break;

                        case 2: ///baja peliculas

                            break;

                        case 3: /// modificar peliculas

                            break;

                        case 4: /// consultar peliculas

                            break;

                        case 5: /// listados de peliculas

                            break;

                        case 6: /// Vuelve al menu anterior

                            continuarOpcionesAdminPeliculas= 'n';



                            break;

                        default:

                            printf("opcion invalida\n");

                            break;
                        }

                    }
                    break;

                case 2:///adm users


                    while(continuarOpcionesAdminUsers=='s')
                    {

                        continuarOpcionesAdmin ='s';
                        continuarOpcionesAdminPeliculas ='s';
                        continuarOpcionesAdminUsers ='s';
                        continuarOpcionesUser ='s';

                        printf("1.ALTA \n");
                        printf("2.BAJA \n");
                        printf("3.MODIFICAR \n");
                        printf("4.CONSULTA \n");
                        printf("5.LISTADOS \n");
                        printf("6.VOLVER \n");
                        printf("ELIJA UNA OPCION \n");

                        scanf("%d",&respuestaOpcionesAdminUsers);

                        system("cls");

                        switch(respuestaOpcionesAdminUsers)
                        {

                        case 1: ///alta usuarios

                            break;

                        case 2: ///baja usuarios

                            break;

                        case 3: /// modificar usuarios

                            break;

                        case 4: /// consultar usuarios

                            break;

                        case 5: /// listados de usuarios

                            break;

                        case 6: /// volver

                            continuarOpcionesAdminUsers = 'n';

                            break;

                        default:

                            printf("opcion invalida\n");
                        }

                    }

                    break;

                case 3:
                    continuarOpcionesAdmin = 'n';
                    break;







                default:

                    printf("opcion invalida \n");


                }
            }


            break;

        case 3: /// SIGN UP


            ///llamar funcion de cadastrar usuarios
            /// con ese usr nuevo relooccear el arreglo y agrregarlo al final

            break;

        default :
            printf("opcion invalida/n");
            break;


        }

    }


    return 0;
}

//Alta
stPelicula cargarPelicula(char nombre_archivoPELI[]) /// carga una pelicula
{
    stPelicula xyz;
    int correctoA=1;
    puts("\n ------------------------------------------------");
    xyz.idPelicula=cantidadPelisArchivo(nombre_archivoPELI)+1;
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


    return xyz;
}
//Modificación
void modificarPeliculas(nodoArbolPelicula *arbol,int id)  ///Permite modificar los valores de los campos de una pelicula
{
    int flag = 0;
    int opcion;
    char continuar = 's';
    nodoArbolPelicula * aux1;
    stPelicula aux;

    aux1=buscarPelicula(arbol,id);


    while(flag == 0)
    {
        {
            flag = 1;
            while(continuar == 's')
            {
                printf("= Modificar Pelicula =\n\n");
                mostrarPeliculaConNumeros(aux);
                printf("Opcion: ");
                scanf("%i",&opcion);

                switch(opcion)
                {
                case 1:
                    printf("Nombre: ");
                    fflush(stdin);
                    gets(&aux1->p.nombrePelicula);
                    break;
                case 2:
                    printf("Director: ");
                    fflush(stdin);
                    gets(&aux1->p.director);
                    break;
                case 3:
                    printf("Genero: ");
                    fflush(stdin);
                    gets(&aux1->p.genero);
                    break;
                case 4:
                    printf("Pais: ");
                    fflush(stdin);
                    gets(&aux1->p.pais);
                    break;
                case 5:
                    printf("Anio: ");
                    fflush(stdin);
                    scanf("%i",&aux1->p.anio);
                    break;
                case 6:
                    printf("Valoracion: ");
                    fflush(stdin);
                    scanf("%i",&aux1->p.valoracion);
                    break;
                case 7:
                    printf("PM: ");
                    fflush(stdin);
                    scanf("%i",&aux1->p.pm);
                    break;
                }
                printf("Modificar otro campo? s/n ");
                fflush(stdin);
                scanf("%c",&continuar);
                system("cls");
            }

        }
    }
}

void cargaPeliculaArchivo ( char nombre_archivo[], stPelicula nuevo) ///Carga una estructura de pelicula nuevo al archivo
{

    FILE *archi;
    archi=fopen(nombre_archivo,"ab");

    if( archi!=NULL)
    {
        fwrite(&nuevo,sizeof(stPelicula),1,archi);

        fclose(archi);
    }
}
//inicLista()
nodoListaPelicula * inicLista()
{
    return NULL;
}
//crearNodoLista()
nodoListaPelicula * crearNodoListaPelicula(stPelicula pelicula)
{
    nodoListaPelicula* aux =(nodoListaPelicula*) malloc(sizeof(nodoListaPelicula));

    aux->p = pelicula;
    aux->sig  = NULL;

    return aux;
}
//agregarAlPrincipio()
nodoListaPelicula * agregarAlPrincipio(nodoListaPelicula * lista, nodoListaPelicula * nuevoNodo )
{

    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo->sig = lista;
        lista = nuevoNodo;

    }

    return lista;
}

//agregarAlFinal()
nodoListaPelicula * agregarAlFinal(nodoListaPelicula * lista, nodoListaPelicula * nuevoNodo)
{
    nodoListaPelicula * seg = lista;
    if(lista)
    {
        seg = seg->sig;
    }

    if(!lista)
    {
        lista = nuevoNodo;
    }
    else
    {

        if(!seg)
        {
            lista->sig = nuevoNodo;
        }
        else
        {

            lista = agregarAlFinal(lista->sig,nuevoNodo);
        }

    }

    return lista;
}
//agregarEnOrdenPorNombreDePelicula()
nodoListaPelicula * agregarEnOrden(nodoListaPelicula * lista, nodoListaPelicula * nuevoNodo)
// agrega un nuevo nodo a la lista manteniendo el orden.
{
    //Si la lista esta vacia agrego el primer elemento.
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        // si el nuevo elemento es menor que el primero de la lista,
        // agrego al principio.
        if(strcmp(nuevoNodo->p.nombrePelicula,lista->p.nombrePelicula)<0)
            lista = agregarAlPrincipio(lista, nuevoNodo);
        else
        {
            // busco el lugar en donde insertar el nuevo elemento.
            // necesito mantener la direccion de memoria del nodo anterior
            // al nodo que tiene un nombre mayor al del nuevo nodo.
            nodoListaPelicula * ante = lista;
            nodoListaPelicula * seg = lista->sig;
            while( (seg != NULL)&&(strcmp(nuevoNodo->p.nombrePelicula,seg->p.nombrePelicula)>=0) )
            {
                ante = seg;
                seg = seg->sig;
            }
            // inserto el nuevo nodo en el lugar indicado.
            nuevoNodo->sig = seg;
            ante->sig = nuevoNodo;
        }
    }
    return lista;
}
//mostrarLista()
void mostrarLista(nodoListaPelicula * lista)
{

    if(lista)
    {
        mostrarPelicula(lista->p);
        mostrarLista(lista->sig);
    }

}
//borrarNodoPorIdPelicula()
nodoListaPelicula * borrarNodo(int idPelicula, nodoListaPelicula * lista)
// elimino un nodo de la lista y retorno un puntero al primer elemento de la misma.
// esto ultimo es necesario para el caso en que se elimina el primer elemento de la lista,
// se modifica el contenido de la variable lista, y eso no se puede hacer de la forma en
// que esta declarada. Para poder hacerlo deber¡a poner **lista. :)
{
    nodoListaPelicula * seg;
    nodoListaPelicula * ante;	//apunta al nodo anterior que seg.

    if((lista != NULL) && (idPelicula == lista->p.idPelicula))
    {
        nodoListaPelicula * aux = lista;
        lista = lista->sig; //salteo el primer nodo.
        free(aux); //elimino el primer nodo.
    }
    else
    {
        seg = lista;
        while((seg != NULL) && (idPelicula == seg->p.idPelicula))
        {
            ante = seg;	//adelanto una posicion la var ante.
            seg = seg->sig; //avanzo al siguiente nodo.
        }
        //en este punto tengo en la variable ante la direccion de memoria del
        //nodo anterior al buscado, y en la variable seg, la dir de memoria del
        //nodo que quiero borrar.
        if( seg!= NULL)
        {
            ante->sig = seg->sig; //salteo el nodo que quiero eliminar.
            free(seg); //elimino el nodo.
        }
    }
    return lista; //debo retornar el puntero al primer nodo, por el tipo de pasaje de parametros.
    //No puedo modificar el contenido de la var lista, que no es lo mismo
    //que modificar *lista (contenido de la direccion de memoria apuntada
    //por lista.
    //Otra forma de resolverlo es poner el par metro **lista. :)
}
//inicArbol()
nodoArbolPelicula* inicArbol ()
{
    return NULL;
}
//crearNodoArbol()
nodoArbolPelicula * crearNodoArbol(stPelicula pelicula)
{
    nodoArbolPelicula* aux=(nodoArbolPelicula*) malloc(sizeof(nodoArbolPelicula));

    aux->p=pelicula;
    aux->der=NULL;
    aux->izq=NULL;

    return aux;
}
//insertarNodoArbol (ordenado por idPelicula)

nodoArbolPelicula* insertarNodoArbol (nodoArbolPelicula* arbol, stPelicula nuevo )
{
    if(arbol==NULL)
    {
        arbol = crearNodoArbol(nuevo);
    }
    else
    {
        if(nuevo.idPelicula>arbol->p.idPelicula)
        {
            arbol->der=insertarNodoArbol(arbol->der,nuevo);
        }
        else
        {
            arbol->izq=insertarNodoArbol(arbol->izq, nuevo);
        }
    }
    return arbol;
}
//mostrarArbol (son tres funciones, recorriendo inOrder, postOrder, preOrder)
void mostrarPelicula(stPelicula aux) ///Muestra el contenido de una pelicula
{
    printf("ID: %i \n",aux.idPelicula);
    printf("Nombre: %s \n",aux.nombrePelicula);
    printf("Director: %s \n",aux.director);
    printf("Genero: %s \n",aux.genero);
    printf("Pais: %s \n",aux.pais);
    printf("Anio: %i \n",aux.anio);
    printf("Valoracion: %i \n",aux.valoracion);
    printf("PM: %i \n",aux.pm);
    printf("Eliminado: %i \n\n",aux.eliminado);
}
void mostrarPeliculaConNumeros(stPelicula aux)
{
    printf("1 Nombre:     %s \n",aux.nombrePelicula);
    printf("2 Director:   %s \n",aux.director);
    printf("3 Genero:     %s   \n",aux.genero);
    printf("4 Pais:       %s   \n",aux.pais);
    printf("5 Anio:       %i   \n",aux.anio);
    printf("6 Valoracion: %i   \n",aux.valoracion);
    printf("7 PM:         %i   \n",aux.pm);
    printf("8 Eliminado:  %i   \n\n",aux.eliminado);
}
void Recorriendo_preorder (nodoArbolPelicula*arbol)
{
    if(arbol!=NULL)
    {
        if(arbol->p.eliminado!=1)
        {
            mostrarPelicula(arbol->p);
        }
        Recorriendo_preorder(arbol->izq);
        Recorriendo_preorder(arbol->der);
    }
}

void Recorriendo_inorder ( nodoArbolPelicula*arbol)
{
    if(arbol!=NULL)
    {
        Recorriendo_inorder(arbol->izq);
        if(arbol->p.eliminado!=1)
        {
            mostrarPelicula(arbol->p);
        }
        Recorriendo_inorder(arbol->der);
    }
}
void Recorriendo_postorder (nodoArbolPelicula * arbol)
{
    if(arbol!=NULL)
    {
        Recorriendo_postorder(arbol->izq);
        Recorriendo_postorder(arbol->der);
        if(arbol->p.eliminado!=1)
        {
            mostrarPelicula(arbol->p);
        }
    }
}
//borrarUnNodoArbol (buscarlo por idPelicula)
//auxiliares
nodoArbolPelicula * buscar_nodo_mas_derech(nodoArbolPelicula*arbol)
{
    nodoArbolPelicula *res;
    if(arbol->der)
    {
        res=buscar_nodo_mas_derech(arbol->der);
    }
    return res;
}
nodoArbolPelicula * buscar_nodo_mas_izqu(nodoArbolPelicula*arbol)
{
    nodoArbolPelicula *res;
    if(arbol->izq)
    {
        res=buscar_nodo_mas_izqu(arbol->izq);
    }
    return res;
}

nodoArbolPelicula * borrarUnNodoArbol (int dato, nodoArbolPelicula* arbol) /// el dato es el id de la pelicula por borrar
{
    if ( arbol!=NULL )
    {
        if (dato==arbol->p.idPelicula)
        {
            if(arbol->izq!=NULL)
            {
                nodoArbolPelicula *MasDer= buscar_nodo_mas_derech(arbol->izq);
                arbol->p=MasDer->p;
                arbol->izq=borrarUnNodoArbol(MasDer->p.idPelicula,arbol->izq);
            }
            else
            {
                if (arbol->der!=NULL)
                {
                    nodoArbolPelicula* masIzq= buscar_nodo_mas_izqu(arbol->der);
                    arbol->p=masIzq->p;
                    arbol->der=borrarUnNodoArbol(masIzq->p.idPelicula,arbol->der);
                }
                else
                {
                    free(arbol);
                    arbol=NULL;
                }
            }
        }
        if ( dato>arbol->p.idPelicula)
        {
            arbol->der=borrarUnNodoArbol(dato,arbol->der);
        }
        if ( dato<arbol->p.idPelicula)
        {
            arbol->izq=borrarUnNodoArbol(dato,arbol->izq);

        }
    }
    return arbol;
}
nodoArbolPelicula *buscarPelicula (nodoArbolPelicula* arbol, int dato)
{
    nodoArbolPelicula *rta=NULL;
    /// si no esta retornamos NULL

    if (arbol!=NULL)
    {
        if(dato==arbol->p.idPelicula)
        {
            rta=arbol;
        }
        else
        {
            if(dato>arbol->p.idPelicula)
            {
                rta=buscarPelicula(arbol->der, dato);
            }
            else
            {
                rta=buscarPelicula(arbol->izq, dato);
            }
        }
    }
    return rta;
}
//cargarArbolDesdeArchivo()
//auxiliar
int cantidadPelisArchivo( char nombre_archivo_pelis[])
{
    int cant;
    stPelicula aux;

    FILE *archi=NULL;
    archi=fopen(nombre_archivo_pelis,"rb");
    if (archi!=NULL)
    {
        fseek(archi, 0, SEEK_END);

        cant=ftell(archi)/sizeof(stPelicula);
    }
    fclose(archi);
    return cant;
}

int ArchivoAArreglo ( char archivo[],stPelicula arreglito [] )
{
    int i=0;

    stPelicula auxiliar;
    FILE * archi;
    archi=fopen(archivo,"rb");
    if(archi!=NULL)
    {
        while (fread(&auxiliar,sizeof(stPelicula),1,archivo)>0)
        {

            arreglito[i]=auxiliar;
            i++;

        }
        fclose(archi);
    }

    return i;
}



nodoArbolPelicula* ArregloPelisToArbol ( int inic, int fin, int cantidad, nodoArbolPelicula *arbol, stPelicula pelis[] )
{
    int nuevofin=fin;
    int nuevoinic=inic;
    int aux;
    nodoArbolPelicula * rta;
    int medio;
    if (cantidad>0)
    {
        if (cantidad%2==0)
        {
            medio = cantidad/2 ;
        }
        else
        {
            medio=(cantidad/2)+1;
        }

        arbol=insertarNodoArbol(arbol,pelis[medio]);
        cantidad--;

        nuevofin=medio-1;
        arbol->izq=ArregloPelisToArbol(nuevoinic,nuevofin,medio,arbol,pelis); // primero para la izquierda)

        nuevoinic = medio+1;
        nuevofin=fin;
        arbol->der=ArregloPelisToArbol(nuevoinic,nuevofin,medio,arbol,pelis); // ahora a la derecha
    }
    else
    {
        arbol=NULL;
    }
    rta=arbol;
    return rta;
}
nodoArbolPelicula* cargarArbolDesdeArchivo (nodoArbolPelicula * arbol, char nombre_archivo_pelis[])
{

    stPelicula aux;
    int cant= cantidadPelisArchivo(nombre_archivo_pelis);
    stPelicula arregloAux[cant];
    int validos_arreglo=ArchivoAArreglo(nombre_archivo_pelis,arregloAux);
    arbol=ArregloPelisToArbol(0,validos_arreglo,validos_arreglo+1,arbol,arregloAux);


    return arbol;
}
/// provisorio
int buscarUsuario(stCelda adl[],int id,int cant)
{
    int i = 0;
    int flag = 0;

    while(adl[i].usr.idUsuario != id)
    {
        i++;
        if(adl[i].usr.idUsuario == id)
        {
            flag = 1;
        }

        if(flag == 0)
        {
            i=-1;
        }
    }
    return i;
}
int cantidadPeliculasVistasArchi(char nombre_archivo[])
{
    FILE * archi;
    int a=0;
    archi=fopen(nombre_archivo, "rb");
    if (archi!=NULL)
    {
        fseek(archi, 0, SEEK_END);
        a = ftell(archi)/(sizeof(stPelisVistas));
        fclose(archi);
    }
    return a;
}
stPelisVistas crearNuevaPeliVista( int idUsr, int idPeli, char nombre_archivo_PelisVistas[])
{
    stPelisVistas nuevo;

    nuevo.idAutoincremental=cantidadPeliculasVistasArchi(nombre_archivo_PelisVistas)+1 ;
    nuevo.idPelicula=idPeli;
    nuevo.idUsuario=idUsr;

    return nuevo;
}
void cargaPeliVistasArchivo ( char nombre_archivo[], stPelisVistas nuevo) ///Carga una estructura de pelivista nueva al archivo
{

    FILE *archi;
    archi=fopen(nombre_archivo,"ab");

    if( archi!=NULL)
    {
        fwrite(&nuevo,sizeof(stPelisVistas),1,archi);

        fclose(archi);
    }
}
void  CargaPeliVistaAlArregloUsr (nodoArbolPelicula*arbol, stCelda arreglo[], int validos_Arreglo, char nombre_archivo[]) ///arreglo de usuarios ya cargado y recorre el archivo de pelisVistas a medidad que encuentra
{

    stPelisVistas PeliVistaAux;
    stPelicula PeliculaAux;
    FILE *archi;
    archi=fopen(nombre_archivo,"rb");
    if(archi!=NULL)
    {
        while (fread(&PeliVistaAux,sizeof(stPelisVistas),1,archi)>0)
        {
            int pos= buscarUsuario(arreglo,PeliVistaAux.idUsuario,validos_Arreglo);
            if (pos>-1)
            {

                nodoArbolPelicula* nodoAux=buscarPelicula(arbol,PeliVistaAux.idPelicula);
                PeliculaAux=nodoAux->p;
                nodoListaPelicula * nuevo=crearNodoListaPelicula(PeliculaAux);
                arreglo[pos].listaPelis=agregarAlFinal( arreglo[pos].listaPelis,nodoAux);
            }
        }
        fclose(archi);
    }
}
//Alta
void pasarMatrixAString(char contrasenia[11],int contraseniaMatrix[2][5])
{
    int fila;
    int columna;
    int i = 0;
    contrasenia[10]='\0';
    for(columna=0; columna<5; columna++)
    {
        for(fila=0; fila<2; fila++)
        {
            contrasenia [i] = contraseniaMatrix[fila][columna];
            i++;
        }
    }
}
void pasarContraseniaAMatrix(char contrasenia[11],int contraseniaMatrix[2][5])
{
    int fila;
    int columna;
    int i = 0;

    for(columna=0; columna<5; columna++)
    {
        for(fila=0; fila<2; fila++)
        {
            contraseniaMatrix[fila][columna] = contrasenia [i];
            i++;
        }
    }
}

void encriptarContrasenia(int contraseniaMatrix[2][5],int pass[2][5])
{
    int testigo[2][2];
    int row,col;
    int i;

    testigo[0][0]=1;
    testigo[0][1]=0;
    testigo[1][0]=2;
    testigo[1][1]=1;

    for(row=0; row<2; row++)
    {
        for(col=0; col<5; col++)
        {
            pass[row][col] = testigo[row][0]*contraseniaMatrix[0][col]+testigo[row][1]*contraseniaMatrix[1][col];
        }
    }
}


///
void desencriptarContrasenia(int contraseniaMatrix[2][5],int pass[2][5])
{
    int testigo[2][2];
    int row,col;
    int i;

    testigo[0][0]=1;
    testigo[0][1]=0;
    testigo[1][0]=-2;
    testigo[1][1]=1;

    for(row=0; row<2; row++)
    {
        for(col=0; col<5; col++)
        {
            pass[row][col] = testigo[row][0]*contraseniaMatrix[0][col]+testigo[row][1]*contraseniaMatrix[1][col];
        }
    }
}



stUsuario cargarUsuario(char nombre_archivoUSER[]) ///genera un usuario, lo carga y lo retorna
{
    stUsuario user;
    char temp[11];
    int auxMatrix[2][5];
    int i = 0;
    int correcto=1;
    int flag=1;

    user.idUsuario=cantidadElementoUsuarios(nombre_archivoUSER)+1;
    while (correcto==1)
    {
        printf("Ingrese Nombre y Apellido: ");
        fflush(stdin);
        gets(&user.nombreUsuario);
        correcto=validacionNombreArchivo(nombre_archivoUSER,user.nombreUsuario);
        if ((correcto)!=0)
        {
            printf("Usuario no disponible");
        }
    }
    while (flag==1)
    {
        printf("Password (10 caracteres): ");
        fflush(stdin);
        gets(&temp);
        if (strlen(temp)==10)
        {
            flag=0;
        }
    }

    pasarContraseniaAMatrix(temp,auxMatrix);
    encriptarContrasenia(auxMatrix,user.pass);
    printf("Anio de Nacimiento: ");
    scanf("%i",&user.anioNacimiento);
    printf("Genero m/f: ");
    fflush(stdin);
    scanf("%c",&user.genero);
    printf("Pais: ");
    fflush(stdin);
    gets(&user.pais);

    user.eliminado = 0;
    user.admin = 0;

    return user;
}

//Baja

//Modificación
void mostrarUsuarioConNumeros(stUsuario aux)  ///Muestra el contenido de un usuario listado por numeros
{
    char pass[11];
    int matrix[2][5];
    desencriptarContrasenia(aux.pass,matrix);
    pasarMatrixAString(pass,matrix);
    printf("1 Nombre:     %s \n",aux.nombreUsuario);
    printf("2 Pass:       %s \n",pass);
    printf("3 Genero:     %c   \n",aux.genero);
    printf("4 Nacimiento: %i   \n",aux.anioNacimiento);
    printf("5 Pais:       %s   \n",aux.pais);
    printf("6 Admin:       %i   \n",aux.admin);
}



void cargaUsuarioArchivo ( char nombre_archivo[], stUsuario nuevo) ///Carga una estructura de usuario nuevo al archivo
{

    FILE *archi;
    archi=fopen(nombre_archivo,"ab");

    if( archi!=NULL)
    {
        fwrite(&nuevo,sizeof(stUsuario),1,archi);

        fclose(archi);
    }
}

void modificarUsuario(stUsuario *aux) ///Permite modificar el contenido de cada campo del usuario
{
    int flag = 0;
    int opcion;
    char continuar = 's';
    char temp[11]; ///cambie 10por11
    int auxMatrix[2][5];




    while(continuar == 's')
    {
        printf("= Modificar Usuario =\n\n");
        mostrarUsuarioConNumeros(*aux);
        printf("Opcion: ");
        scanf("%i",&opcion);

        switch(opcion)
        {
        case 1:
            printf("Nombre: ");
            fflush(stdin);
            gets(&aux->nombreUsuario);
            break;
        case 2:
            printf("Pass (10 caracteres): ");
            fflush(stdin);
            gets(&temp);
            pasarContraseniaAMatrix(temp,auxMatrix);
            encriptarContrasenia(auxMatrix,aux->pass);

            break;
        case 3:
            printf("Genero: ");
            fflush(stdin);
            gets(&aux->genero);
            break;
        case 4:
            printf("Nacimiento: ");
            scanf("%i",&aux->anioNacimiento);
            break;
        case 5:
            printf("Pais: ");
            fflush(stdin);
            gets(&aux->pais);
            break;

        case 6:
            printf("Admin: 0:No 1:Si ");
            fflush(stdin);
            scanf("%d",&aux->admin);
            break;

        }
        printf("Modificar otro campo? s/n ");
        fflush(stdin);
        scanf("%c",&continuar);
        system("cls");
    }

}

//Consulta y Listados de Usuarios

void mostrarUsuario(stCelda adl)
{

    printf("\n Admin: %d",adl.usr.admin);
    printf("\n idUsuario: %d", adl.usr.idUsuario);
    printf("\n nombreUsuario: %s",adl.usr.nombreUsuario);
    printf("\n genero: %c", adl.usr.genero);
    printf("\n pais: %s ", adl.usr.pais);
    printf("\n Nacimiento: %d ", adl.usr.anioNacimiento);

}
void mostrarListaPelisVistas(nodoListaPelicula *lista, nodoArbolPelicula *arbolPeliculas)
{

    if(lista != NULL)
    {
        nodoArbolPelicula * aux = buscarPelicula(arbolPeliculas,lista->p.idPelicula);
        mostrarPelicula(aux->p);
        printf("\n");
        mostrarListaPelisVistas(lista->sig,arbolPeliculas);


    }

}


void mostrarUsuarios(stCelda adl[],int cant, nodoArbolPelicula *arbolPeliculas)
{
    int i;
    for(i=0; i<cant; i++)
    {
        mostrarUsuario(adl[i]);
        mostrarListaPelisVistas(adl[i].listaPelis,arbolPeliculas);
        printf("---------------------------------------------------------------------------");
    }
}

void sobreEscribirPeliEnArchivo(char nombre_archivo[],stPelicula nuevo)
{
    stPelicula a;

    FILE *archi;
    archi=fopen(nombre_archivo,"r+b");
    if (archi!=NULL)
    {
        fseek(archi,sizeof(stPelicula)*(nuevo.idPelicula-1),SEEK_SET);
        fread(&a,sizeof(stPelicula),1,archi);
        a=nuevo;
        fseek(archi,sizeof(stPelicula)*(nuevo.idPelicula-1),SEEK_SET);
        fwrite(&a,sizeof(stPelicula),1,archi);
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
void sobreEscribirUsuarioEnArchivo(char nombre_archivo[],stUsuario nuevo){

    stUsuario a;
    FILE *archi;
    archi=fopen(nombre_archivo,"r+b");
    if (archi!=NULL)
    {
        fseek(archi,sizeof(stUsuario)*(nuevo.idUsuario-1),SEEK_SET);
        fread(&a,sizeof(stUsuario),1,archi);
        a=nuevo;
        fseek(archi,sizeof(stUsuario)*(nuevo.idUsuario-1),SEEK_SET);
        fwrite(&a,sizeof(stUsuario),1,archi);
        fclose(archi);
    }
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

stPelicula bajaPeliculas(nodoArbolPelicula *arbol,int id)  ///Permite modificar los valores de los campos de una pelicula
{

    nodoArbolPelicula * aux1;
    stPelicula aux;

    aux1=buscarPelicula(arbol,id);


    aux1->p.eliminado = 1;

    return aux1->p;
}

stUsuario eliminarUsuario(stCelda adl[],int cant,int id)
{
    int pos = buscarUsuario(adl,id,*cant);
    stUsuario user = adl[pos].usr;
    user.eliminado=1;

    return user;
}
