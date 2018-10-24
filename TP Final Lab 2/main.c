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


//Baja


//Modificación


//Consulta


//Listados




/// ----------------------------TDA LISTA SIMPLE -------------------------------------------

//inicLista()


//crearNodoLista()


//agregarAlPrincipio()


//agregarAlFinal()


//agregarEnOrdenPorNombreDePelicula()


//mostrarLista()


//borrarNodoPorIdPelicula()


///---------------------------------------- TDA ARBOL --------------------------------------------

//inicArbol()
nodoArbolPelicula* inicArbol ()
{
    return NULL;
}

//crearNodoArbol()


//insertarNodoArbol (ordenado por idPelicula)


//mostrarArbol (son tres funciones, recorriendo inOrder, postOrder, preOrder)


//borrarUnNodoArbol (buscarlo por idPelicula)


//buscarPelicula(por idPelicula)


//cargarArbolDesdeArchivo()



///----------------------------------- FUNCIONES DE USUARIOS ------------------------------------------

//Alta


//Baja


//Modificación


//Consulta y Listados de Usuarios


//manejo del password encriptado






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

            break;

        default :
            printf("opcion invalida/n");
            break;


        }








    }







    return 0;
}
