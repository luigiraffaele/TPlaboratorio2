#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///================ ESTRUCT PELICULA =============================///
typedef struct {
      int idPelicula;
      char nombrePelicula[30];
      char director[20];
      char genero[20];
      char pais[20];
      int anio;
      int valoracion;
      int pm;      // (0- si es ATP / 13: mayor de trece /16: mayor de 16 / 18: mayor de 18
      int eliminado;   // indica 1 o 0 si la pel�cula fue eliminada
} pelicula;

///=============== ESTRUCT USUARIO =============================///

typedef struct{
    int idUsuario;
    char nombreUsuario[30];
    int pass[2][5];
    int anioNacimiento;
    char genero;  // �m� o �f�
    char pais[20];
    int peliculasVistas[30]; ///Guarda los id de las pel�culas.
    int cantVistas; /// Es el v�lidos de pel�culas vistas.
    int eliminado;   /// indica 1 o 0 si el cliente fue eliminado
}usuario;


///==============  FUNCIONES PELICULA  ==============================///
pelicula cargarPelicula(){ ///Carga una pelicula y la retorna
    pelicula aux;
    printf("Nombre: ");
    fflush(stdin);
    gets(&aux.nombrePelicula);
    printf("Director: ");
    fflush(stdin);
    gets(&aux.director);
    printf("Genero: ");
    fflush(stdin);
    gets(&aux.genero);
    printf("Pais: ");
    fflush(stdin);
    gets(&aux.pais);
    printf("Anio: ");
    fflush(stdin);
    scanf("%i",&aux.anio);
    printf("Valoracion(1-10): ");
    fflush(stdin);
    scanf("%i",&aux.valoracion);
    printf("PM(0,13,16,18): ");
    fflush(stdin);
    scanf("%i",&aux.pm);
    aux.eliminado = 0;
    return aux;
}

int existePelicula(char file[], pelicula peli){ ///Retorna 1 o 0 si una determinada pelicula se encuentra en el archivo
    int existe = 0;
    int control = 1;
    pelicula aux;
    FILE*archi = NULL;
    archi = fopen(file,"rb");
    if(archi != NULL){
        while(existe == 0 && control > 0 ){
            control = fread(&aux,sizeof(pelicula),1,archi);
            if(strcmpi(aux.nombrePelicula, peli.nombrePelicula)==0){
                existe = 1;
            }
        }
    }
    fclose(archi);
    return existe;
}

void altaPeliculas(char file[]){ ///Graba un archivo de peliculas llamando a la funcion cargarPelicula() tanta veces como el usuario desee
    int id = 0;
    pelicula aux;
    pelicula aux1;
    char continuar = 's';
    FILE*archi = NULL;
    archi = fopen(file,"rb");
    if(archi == NULL){
        archi = fopen(file,"wb");
        while(continuar == 's'){
            aux = cargarPelicula();
            if(existePelicula(archi,aux)==0){
                aux.idPelicula=id++;
                fwrite(&aux,sizeof(pelicula),1,archi);
            } else {
                printf("Pelicula existente\n");
            }
            printf("\nCargar nueva pelicula s/n: ");
            fflush(stdin);
            scanf("%c",&continuar);
        }
        fclose(archi);
    }else{
        archi = fopen(file,"r+b");
        while(continuar == 's'){
            aux = cargarPelicula();
            if(existePelicula(archi,aux)==0){
                fseek(archi,sizeof(pelicula)*(-1),SEEK_END);
                fread(&aux1,sizeof(pelicula),1,archi);
                aux.idPelicula = aux1.idPelicula + 1;
                fseek(archi,sizeof(pelicula)*0,SEEK_END);
                fwrite(&aux,sizeof(pelicula),1,archi);
            }else{
                printf("Pelicula existente\n");
            }
            printf("\nCargar nueva pelicula s/n: ");
            fflush(stdin);
            scanf("%c",&continuar);
        }
        fclose(archi);
    }
    fclose(archi);
}

void cambiarEstadoPelicula(char file[], int id){ ///Cambia el estado "Eliminado" de una pelicula de 0 a 1 o visceversa
    int flag = 0;
    pelicula aux;
    FILE*archi = NULL;
    archi = fopen(file,"r+b");
    if(archi != NULL){
        while(flag == 0){
            if(fread(&aux,sizeof(pelicula),1,archi) > 0 && aux.idPelicula == id){
                if(aux.eliminado == 0){
                    aux.eliminado = 1;
                    flag = 1;
                    fseek(archi,(-1)*sizeof(pelicula),SEEK_CUR);
                    fwrite(&aux,sizeof(pelicula),1,archi);
                } else {
                    aux.eliminado = 0;
                    flag = 1;
                    fseek(archi,(-1)*sizeof(pelicula),SEEK_CUR);
                    fwrite(&aux,sizeof(pelicula),1,archi);
                }
            }
        }
    }
    fclose(archi);
}

void modificarPeliculas(char file[],int id){ ///Permite modificar los valores de los campos de una pelicula
    int flag = 0;
    int opcion;
    char continuar = 's';
    pelicula aux;
    FILE*archi = NULL;
    archi = fopen(file,"r+b");
    if(archi!=NULL){
        while(flag == 0){
            if(fread(&aux,sizeof(pelicula),1,archi)>0 && aux.idPelicula == id){
                flag = 1;
                while(continuar == 's'){
                printf("= Modificar Pelicula =\n\n");
                mostrarPeliculaConNumeros(aux);
                printf("Opcion: ");
                scanf("%i",&opcion);

                switch(opcion){
                case 1:
                printf("Nombre: ");
                fflush(stdin);
                gets(&aux.nombrePelicula);
                break;
                case 2:
                printf("Director: ");
                fflush(stdin);
                gets(&aux.director);
                break;
                case 3:
                printf("Genero: ");
                fflush(stdin);
                gets(&aux.genero);
                break;
                case 4:
                printf("Pais: ");
                fflush(stdin);
                gets(&aux.pais);
                break;
                case 5:
                printf("Anio: ");
                fflush(stdin);
                scanf("%i",&aux.anio);
                break;
                case 6:
                printf("Valoracion: ");
                fflush(stdin);
                scanf("%i",&aux.valoracion);
                break;
                case 7:
                printf("PM: ");
                fflush(stdin);
                scanf("%i",&aux.pm);
                break;
                }
                printf("Modificar otro campo? s/n ");
                fflush(stdin);
                scanf("%c",&continuar);
                system("cls");
                }
            fseek(archi,(-1)*sizeof(pelicula),SEEK_CUR);
            fwrite(&aux,sizeof(pelicula),1,archi);
        }
      }
    }
    fclose(archi);
}

void mostrarPelicula(pelicula aux){///Muestra el contenido de una pelicula
    printf("ID:         %i \n",aux.idPelicula);
    printf("Nombre:     %s \n",aux.nombrePelicula);
    printf("Director:   %s \n",aux.director);
    printf("Genero:     %s   \n",aux.genero);
    printf("Pais:       %s   \n",aux.pais);
    printf("Anio:       %i   \n",aux.anio);
    printf("Valoracion: %i   \n",aux.valoracion);
    printf("PM:         %i   \n",aux.pm);
    printf("Eliminado:  %i   \n\n",aux.eliminado);
}

void mostrarPeliculaConNumeros(pelicula aux){
    printf("1 Nombre:     %s \n",aux.nombrePelicula);
    printf("2 Director:   %s \n",aux.director);
    printf("3 Genero:     %s   \n",aux.genero);
    printf("4 Pais:       %s   \n",aux.pais);
    printf("5 Anio:       %i   \n",aux.anio);
    printf("6 Valoracion: %i   \n",aux.valoracion);
    printf("7 PM:         %i   \n",aux.pm);
    printf("8 Eliminado:  %i   \n\n",aux.eliminado);
}

void mostrarPeliculaEnArchivo(char file[], int id){ ///Muestra el contenido de una pelicula especifica dentro de un archivo
    pelicula aux;
    int control=1;
    int flag = 0;
    FILE*archi = NULL;
    archi = fopen(file,"rb");
    if(archi!=NULL){
        while(flag == 0 && control >0){
            control = fread(&aux,sizeof(pelicula),1,archi);
            if(aux.idPelicula == id){
                mostrarPelicula(aux);
                flag = 1;
            }
        }
    }
    fclose(archi);
}

void mostrarArchivoPeliculas(char file[]){ ///Muestra todas las peliculas de un archivo
    pelicula aux;
    FILE*archi=NULL;
    archi=fopen(file,"rb");
    if(archi!=NULL){
        while(fread(&aux,sizeof(pelicula),1,archi)>0){
            mostrarPelicula(aux);
        }
    }
    fclose(archi);
}

void consulaTitulo(char file[],char titulo[]){ ///Busca una pelicula por titulo y la muestra
    int flag = 0;
    int control=1;
    pelicula aux;
    FILE*archi = NULL;
    archi = fopen(file,"rb");
    if(archi != NULL){
        while(flag == 0 && control>0){
            control = fread(&aux,sizeof(pelicula),1,archi);
            if(strcmpi(aux.nombrePelicula,titulo)==0){
                mostrarPelicula(aux);
                flag = 1;
            }
        }
        if(flag==0)
            printf("PELICULA NO ENCONTRADA\n");
    }
    fclose(archi);
}

void consultaGenero(char file[], char genero[]){ ///Busca todas las peliculas de un genero dentro del archivo y las muestra
    pelicula aux;
    int control = 1;
    FILE*archi = NULL;
    archi = fopen(file,"rb");
    if(archi!=NULL){
        while(control > 0){
            control = fread(&aux,sizeof(pelicula),1,archi);
            if(strcmpi(aux.genero,genero)==0){
                printf("* %s    ID:%i\n",aux.nombrePelicula,aux.idPelicula);
            }
        }
       /// if control() ARREGLAR ESTO***************************************************


    }
    fclose(archi);
}


int archivoToArray(char file[],pelicula lista[], int dim){ ///Pasa el contenido de un archivo de peliculas a un arreglo
    int i=0;
    int control = 1;
    pelicula aux;
    FILE*archi = NULL;
    archi = fopen(file,"rb");
    if(archi != NULL){
        while(i < dim && control > 0){
            control = fread(&aux,sizeof(pelicula),1,archi);
            lista[i]=aux;
            i++;
        }
    }
    fclose(archi);
    return i;
}


///Ordenacion de peliculas por insercion (segun genero):
void insertarPelicula(pelicula lista[],int i, pelicula p){
    while(i>=0 && strcmpi(p.genero,lista[i].genero) < 0){
        lista[i+1]=lista[i];
        i--;
    }
    lista[i+1] = p;
}
void ordenarPeliculasPorGenero(pelicula lista[],int validos){
    pelicula p;
    int i=0;
    while(i<validos-1){
        p = lista[i+1];
        insertarPelicula(lista,i,p);
        i++;
    }
}

///Ordenacion de peliculas por seleccion(segun titulo):
int posMenorPelicula(pelicula lista[],int validos, int pos){
    pelicula menor = lista[pos];
    int posMenor = pos;
    int i = pos+1;
    while(i<validos){
        if(strcmpi(menor.nombrePelicula,lista[i].nombrePelicula)>0){
            menor = lista[i];
            posMenor = i;
        }
        i++;
    }
    return posMenor;
}
void ordenarPeliculasPorTitulo(pelicula lista[],int validos){
    pelicula menor;
    int posMenor;
    int i = 0;
    while(i<validos-1){
        posMenor = posMenorPelicula(lista,validos,i);
        menor = lista[posMenor];
        lista[posMenor] = lista[i];
        lista[i] = menor;
        i++;
    }
}


void mostrarArregloPeliculas(pelicula lista[],int validos){///Muestra un arreglo de peliculas
    int i = 0;
    while(i<validos){
        mostrarPelicula(lista[i]);
        printf("\n");
        i++;
    }
}

void listadoPeliculasGenero(char file[]){ ///Muestra un listado de peliculas odenadas por genero
    int dim = 1000;
    pelicula lista[dim];
    int validos = archivoToArray(file,lista,dim);
    ordenarPeliculasPorGenero(lista,validos);
    mostrarArregloPeliculas(lista,validos);
}

void listadoPeliculasTitulo(char file[]){///Muestra un listado de peliculas ordenadas por titulo
    int dim = 1000;
    pelicula lista[dim];
    int validos = archivoToArray(file,lista,dim);
    ordenarPeliculasPorTitulo(lista,validos);
    mostrarArregloPeliculas(lista,validos);
}

pelicula buscarPeliculaID(char fileP[], int id){ ///BUsca una pelicula en el archivo por su ID y la retorna
    int flag = 0;
    pelicula aux;
    FILE*archi = NULL;
    archi = fopen(fileP,"rb");
    if(archi != NULL){
        while(fread(&aux,sizeof(pelicula),1,archi)>0 && flag == 0){
            if(aux.idPelicula == id){
                flag = 1;
            }
        }
    }
    fclose(archi);
    return aux; ///OJO ACA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

int verPelicula(char fileP[], int id){
    int idP = id;
    pelicula aux;
    FILE*archi = NULL;
    archi = fopen(fileP,"rb");
    if(archi != NULL){
        aux = buscarPeliculaID(fileP,idP);
            if(existePelicula(fileP,aux)==1){
                printf("\nViendo "" %s "" \n",aux.nombrePelicula);
                id = aux.idPelicula;
            } else {
                idP = -1;
            }
    }
    fclose(archi);
    return id;
}

///=====================   FUNCIONES USUARIO    ================================///

usuario cargarUsuario(){///genera un usuario, lo carga y lo retorna
    usuario user;
    char temp[10];
    int auxMatrix[2][5];

    printf("Nombre y Apellido: ");
    fflush(stdin);
    gets(&user.nombreUsuario);
    printf("Password (10 caracteres): ");
    fflush(stdin);
    gets(&temp);
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
    ///user.peliculasVistas;
    user.cantVistas = 0;
    user.eliminado = 0;

    return user;
}

int existeUsuario(char fileU[], usuario user){///determina si un usuario se encuentra ya cargado en un archivo
    int existe = 0;
    int control = 1;
    usuario aux;
    FILE*archi = NULL;
    archi = fopen(fileU,"rb");
    if(archi != NULL){
        while(control>0 && existe == 0){
            control = fread(&aux,sizeof(usuario),1,archi);
            if(strcmpi(aux.nombreUsuario,user.nombreUsuario)==0){
                existe = 1;
            }
        }
    }
    fclose(archi);
    return existe;
}

int altaUsuarios(char fileU[]){///Permite cargar usuarios en un archivo indeterminadamente
    usuario user;
    usuario userAux;
    int id = 0;
    int i = 0;
    char continuar = 's';
    FILE*archi = NULL;

    archi = fopen(fileU,"rb");
    if(archi == NULL){
        archi = fopen(fileU,"wb");
       // while(continuar == 's'){
            user = cargarUsuario();
            if(existeUsuario(archi,user)==0){
                user.idUsuario = id++;
                fwrite(&user,sizeof(usuario),1,archi);
            } else {
                printf("USUARIO EXISTENTE\n");
            }
           /* printf("Cargar otro usuario s/n"); ///Modificar para la funcion de REGISTRARSE
            fflush(stdin);
            scanf("%c",&continuar);
            system("cls");*/
        //}
        fclose(archi);
    }else{
        archi = fopen(fileU,"r+b");
        //while(continuar == 's'){
            user = cargarUsuario();
            if(existeUsuario(fileU,user)==0){
                fseek(archi, (-1)*sizeof(usuario),SEEK_END);
                fread(&userAux, sizeof(usuario),1,archi);
                id = userAux.idUsuario +1;
                ///user.idUsuario = userAux.idUsuario + 1;
                user.idUsuario = id;
                fseek(archi,0*sizeof(usuario),SEEK_END);
                fwrite(&user,sizeof(usuario),1,archi);
            } else {
                printf("USUARIO EXISTENTE\n");
            }
               /* printf("Cargar otro usuario s/n"); ///Modificar para la funcion de REGISTRARSE
                fflush(stdin);
                scanf("%c",&continuar);
                system("cls");*/
        //}
        fclose(archi);
    }
    return id;
    //fclose(archi);
}

void mostrarUsuario(usuario user){ ///recibe un usuario y muestra su contenido
    char pass[11];
    int aux[2][5];
    desencriptarContrasenia(user.pass,aux);
    pasarMatrixAString(pass,aux);
    printf("ID: %i\n",user.idUsuario);
    printf("Nombre: %s\n",user.nombreUsuario);
    printf("Pass: %s\n",pass);
    printf("Nacimiento: %i\n",user.anioNacimiento);
    printf("Pais: %s\n",user.pais);
    printf("Peliculas vistas: \n");
    printf("Cantidad vistas: \n");
    printf("Eliminado: %i\n\n",user.eliminado);
}

void mostrarArchivoUsuarios(char fileU[]){ ///Muestra el contenido de un archivo de usuarios
    usuario user;
    FILE*archi = NULL;
    archi = fopen(fileU,"rb");
    if(archi != NULL){
        while(fread(&user,sizeof(usuario),1,archi)>0){
            mostrarUsuario(user);
        }
    }
    fclose(archi);
}

void mostrarUsuarioEnArchivo(char fileU[], int id){///Muestra el contenido de un determinado usuario en un archivo
    usuario aux;
    int control=1;
    int flag = 0;
    FILE*archi = NULL;
    archi = fopen(fileU,"rb");
    if(archi!=NULL){
        while(flag == 0 && control >0){
            control = fread(&aux,sizeof(usuario),1,archi);
            if(aux.idUsuario == id){
                mostrarUsuario(aux);
                flag = 1;
            }
        }
    }
    fclose(archi);
}

usuario devolverUsuarioEnArchivo(char fileU[], int id){///Muestra el contenido de un determinado usuario en un archivo
    usuario aux;
    int control=1;
    int flag = 0;
    FILE*archi = NULL;
    archi = fopen(fileU,"rb");
    if(archi!=NULL){
        while(flag == 0 && control >0){
            control = fread(&aux,sizeof(usuario),1,archi);
            if(aux.idUsuario == id){
                flag = 1;
            }
        }
    }
    fclose(archi);
    return aux;
}

void mostrarUsuarioConNumeros(usuario aux){ ///Muestra el contenido de un usuario listado por numeros
    printf("1 Nombre:     %s \n",aux.nombreUsuario);
    printf("2 Pass:       %s \n",aux.pass);
    printf("3 Genero:     %c   \n",aux.genero);
    printf("4 Nacimiento: %i   \n",aux.anioNacimiento);
    printf("5 Pais:       %s   \n",aux.pais);
    printf("6 Estado:     %i   \n\n",aux.eliminado);
}


void cambiarEstadoUsuario(char fileU[], int id){///Permite cambiar el estado "eliminado" de un usuario de 0 a 1 o visceversa
    int flag = 0;
    int control = 1;
    usuario user;
    FILE*archi=NULL;
    archi = fopen(fileU,"r+b");
    if(archi != NULL){
        while(flag==0&&control>0){
            control = fread(&user,sizeof(usuario),1,archi);
            if(user.idUsuario == id && user.eliminado == 0){
                user.eliminado = 1;
                fseek(archi,sizeof(usuario)*(-1),SEEK_CUR);
                fwrite(&user,sizeof(usuario),1,archi);
                flag = 1;
            } else if(user.idUsuario == id && user.eliminado !=0){
                user.eliminado = 0;
                fseek(archi,sizeof(usuario)*(-1),SEEK_CUR);
                fwrite(&user,sizeof(usuario),1,archi);
                flag = 1;
            }
        }
    }
    fclose(archi);
}

void modificarUsuario(char fileU[],int id){///Permite modificar el contenido de cada campo del usuario
    int flag = 0;
    int opcion;
    char continuar = 's';
    usuario aux;
    FILE*archi = NULL;
    archi = fopen(fileU,"r+b");
    if(archi!=NULL){
        while(flag == 0){
            if(fread(&aux,sizeof(usuario),1,archi)>0 && aux.idUsuario == id){
                flag = 1;
                while(continuar == 's'){
                    printf("= Modificar Usuario =\n\n");
                    mostrarUsuarioConNumeros(aux); ///PENDIENTE
                    printf("Opcion: ");
                    scanf("%i",&opcion);

                    switch(opcion){
                    case 1:
                        printf("Nombre: ");
                        fflush(stdin);
                        gets(&aux.nombreUsuario);
                    break;
                    case 2:
                        printf("Pass: "); ///PENDIENTE
                        fflush(stdin);
                        //gets(&aux.director);
                    break;
                    case 3:
                        printf("Genero: ");
                        fflush(stdin);
                        gets(&aux.genero);
                    break;
                    case 4:
                        printf("Nacimiento: ");
                        scanf("%i",&aux.anioNacimiento);
                    break;
                    case 5:
                        printf("Pais: ");
                        fflush(stdin);
                        gets(&aux.pais);
                    break;
                    case 6: ///Estado
                    break;
                }
                printf("Modificar otro campo? s/n ");
                fflush(stdin);
                scanf("%c",&continuar);
                system("cls");
                }
            fseek(archi,(-1)*sizeof(usuario),SEEK_CUR);
            fwrite(&aux,sizeof(usuario),1,archi);
        }
      }
    }
    fclose(archi);
}

void consulaID(char fileU[],int id){ ///Busca un usuario por su ID y lo muestra
    int flag = 0;
    int control=1;
    usuario aux;
    FILE*archi = NULL;
    archi = fopen(fileU,"rb");
    if(archi != NULL){
        while(flag == 0 && control>0){
            control = fread(&aux,sizeof(usuario),1,archi);
            if(aux.idUsuario == id){
                flag = 1;
            }
        }
        if(flag==1){
            mostrarUsuario(aux);
        } else {
            printf("USUARIO NO EXISTE\n");
        }
    }
    fclose(archi);
}

///Consulta por Nombre

void consulaNombre(char fileU[],char name[30]){ ///Busca un usuario por su nombre y lo muestra
    int flag = 0;
    int control=1;
    usuario aux;
    FILE*archi = NULL;
    archi = fopen(fileU,"rb");
    if(archi != NULL){
        while(flag == 0 && control>0){
            control = fread(&aux,sizeof(usuario),1,archi);
            if(strcmpi(name,aux.nombreUsuario)==0){
                flag = 1;
            }
        }
        if(flag==1){
            mostrarUsuario(aux);
        } else {
            printf("USUARIO NO EXISTE\n");
        }
    }
    fclose(archi);
}

///Consulta por g�nero
void consulaGenero(char fileU[],char genero){ ///Busca un usuario por su genero y lo muestra
    ///int control=1;
    usuario aux;
    FILE*archi = NULL;
    archi = fopen(fileU,"rb");
    if(archi != NULL){
        while(fread(&aux,sizeof(usuario),1,archi)>0){
            if(aux.genero == genero){
                mostrarUsuario(aux);
            }
        }
    }
    fclose(archi);
}

///Consulta por anio
void consultaAnio(char fileU[],int anio){ ///Busca un usuario por su anio y lo muestra
    int flag = 0;
    usuario aux;
    FILE*archi = NULL;
    archi = fopen(fileU,"rb");
    if(archi != NULL){
        while(fread(&aux,sizeof(usuario),1,archi)>0){
            if(aux.anioNacimiento == anio){
                mostrarUsuario(aux);
                flag = 1;
            }
        }
        if(flag==0){
            printf("\nNo hay usuarios de %i \n\n",anio);
        }
    }
    fclose(archi);
}


///Consulta por pais
void consultaPais(char fileU[],char pais[20]){ ///Busca un usuario por su pais y lo muestra
    int flag = 0;
    usuario aux;
    FILE*archi = NULL;
    archi = fopen(fileU,"rb");
    if(archi != NULL){
        while(fread(&aux,sizeof(usuario),1,archi)>0){
            if(strcmpi(pais,aux.pais)==0){
                mostrarUsuario(aux);
                flag = 1;
            }
        }
        if(flag==0){
            printf("\nNo hay usuarios de %s \n\n",pais);
        }
    }
    fclose(archi);
}



///Consulta por estado
void consultaEstado(char fileU[],int estado){ ///Busca un usuario por su estado y lo muestra
    usuario aux;
    FILE*archi = NULL;
    archi = fopen(fileU,"rb");
    if(archi != NULL){
        while(fread(&aux,sizeof(usuario),1,archi)>0){
            if(aux.eliminado == estado){
                mostrarUsuario(aux);
            }
        }
    }
    fclose(archi);
}

///listados============

int archivoUsuariosToArray(char file[],usuario A[], int dim){ ///Pasa el contenido de un archivo de usuarios a un arreglo
    int i=0;
    int control = 1;
    usuario aux;
    FILE*archi = NULL;
    archi = fopen(file,"rb");
    if(archi != NULL){
        while(i < dim && control > 0){
            control = fread(&aux,sizeof(usuario),1,archi);
            A[i]=aux;
            i++;
        }
    }
    fclose(archi);
    return i;
}

int posMenorNombre(usuario A[],int validos, int pos){
    usuario menor = A[pos];
    int posMenor = pos;
    int i = pos+1;
    while(i<validos){
        if(strcmpi(menor.nombreUsuario,A[i].nombreUsuario)==1){
            menor = A[i];
            posMenor = i;
        }
        i++;
    }
    return posMenor;
}

void ordenarUsuariosPorNombre(usuario A[],int validos){
    int i=0;
    usuario menor;
    int posMenor;
    while(i<validos-1){
        posMenor = posMenorNombre(A,validos,i);
        menor = A[posMenor];
        A[posMenor] = A[i];
        A[i] = menor;
        i++;
    }
}

void listadoUsuariosNombre(char fileU[]){ ///Muestra un listado de peliculas odenadas por genero
    int dim = 1000;
    usuario arregloU[dim];
    int validos = archivoUsuariosToArray(fileU,arregloU,dim);
    ordenarUsuariosPorNombre(arregloU,validos);
    mostrarArregloUsuarios(arregloU,validos);
}

void mostrarArregloUsuarios(usuario A[],int validos){///Muestra un arreglo de usuarios
    int i = 0;
    while(i<validos){
        mostrarUsuario(A[i]);
        printf("\n");
        i++;
    }
}


///=====================   FUNCIONES DE MENUES    ==============================///

void menuPrincipal(char fileP[], char fileU[]){ ///Imprime el menu principal y redirige a los sub-menues
    int opcion=0;
    int valido = -1;
    int id;
    ///usuario user;

    printf("= Bienvenido a NerdFlix = \n\n");

    printf("1. ENTRAR \n");
    printf("2. ADMIN \n");
    printf("3. SIGN UP \n\n");
    printf("ELIJA OPCION: ");
    scanf("%i",&opcion);
    if(opcion>0 && opcion<4){
        system("cls");
        switch(opcion){
        case 1: /// Redirige a Menu Usuario
            while(valido<0){

                valido=validacionUser(fileU);
                if(valido<0){
                    printf("USERNAME / PASSWORD Incorrectos");
                }else{
                    system("cls");
                    menuUsuario(fileP,fileU,valido);
                }

            }

            ///user = cargarUsuario();

        break;
        case 2: /// Redirige a Menu Administrador
            ///menuValidacion(2);
            menuAdmin(fileP,fileU);
        break;
        case 3: ///Redirige a Alta de usuario
            printf("= REGISTRARSE =\n\n");
            id = altaUsuarios(fileU);
            system("cls");
            menuUsuario(fileP,fileU,id);
        break;
        }
    }else{
        system("cls");
        menuPrincipal(fileP,fileU);
    }

}
void menuValidacion(); ///Pendiente


void menuAdmin(char fileP[], char fileU[]){///Muestra el Menu de Administrador y sus opciones, y redirige a los sub-menues
    int opcion;
    printf("= Administrador = \n\n");
    printf("1. Peliculas\n");
    printf("2. Usuarios\n");
    printf("3. Salir\n\n");
    printf("Opcion: ");
    scanf("%i",&opcion);
    if(opcion>0 && opcion<3){
        system("cls");
        switch(opcion){
        case 1:///Redirige al sub-menu "Administrar Peliculas"
            menuAdminPelis(fileP,fileU);
        break;
        case 2:///Redirige al sub-menu "Administrar Usuarios"
            menuAdminUsers(fileP,fileU);
        break;
        }
    }else if(opcion == 3){
        system("cls");
        menuPrincipal(fileP,fileU); ///Redirige al Menu Princial
    } else{
        system("cls");
        menuAdmin(fileP,fileU); ///Redirige al Menu Administrador
    }

}
void menuAdminPelis(char fileP[], char fileU[]){ ///Muestra el sub-menu "Administrar Peliculas" y sus opciones
    int opcion;
    int id;
    char titulo[30];
    char control = 's';
    char genero[30];
    int dim = 1000;     ///Cambiar esta pedorrada
    pelicula listadoP[dim];
    while(control == 's'){
        printf("= Administrar Peliculas =\n\n");
        printf("1. Alta Peliculas\n");
        printf("2. Cambiar Estado Pelicula\n");
        printf("3. Modificar Pelicula\n");
        printf("4. Consulta Pelicula\n");
        printf("5. Listados\n\n");
        printf("6. Atras\n\n");
        printf("Opcion: ");

        scanf("%i",&opcion);
        system("cls");
        switch(opcion){
        case 1: ///Alta de peliculas
            printf("= Alta Peliculas =\n\n");
            altaPeliculas(fileP);
            printf("Ver archivo: s/n ");
            fflush(stdin);
            scanf("%c",&control);
            if(control=='s')
            mostrarArchivoPeliculas(fileP);
            printf("Menu Peliculas: ");
            system("pause");

        break;

        case 2: ///Cambiar estado de pelicula
            while(control == 's'){
                printf("= Cambiar Estado =\n\n");
                printf("ID Pelicula: ");
                scanf("%i",&id);
                printf("\n");
                cambiarEstadoPelicula(fileP,id);
                mostrarPeliculaEnArchivo(fileP,id);
                printf("\nCambiar estado de otra pelicula s/n: ");
                fflush(stdin);
                scanf("%c",&control);
                system("cls");
            }
        break;

        case 3: ///Modificar Peliculas
            while(control == 's'){
                printf("= Modificar Pelicula =\n\n");
                printf("ID Pelicula: ");
                scanf("%i",&id);
                system("cls");
                modificarPeliculas(fileP,id);
                printf("= Modificar Pelicula =\n\n");
                mostrarPeliculaEnArchivo(fileP,id);
                printf("Modificar otra pelicula s/n: ");
                fflush(stdin);
                scanf("%c",&control);
                system("cls");
            }
        break;

        case 4: ///Consulta
            while(opcion != 3){
                system("cls");
                printf("= Consulta =\n\n");
                printf("1. Por titulo\n");
                printf("2. Por genero\n");
                printf("3. Atras\n\n");
                printf("Opcion: ");
                scanf("%i",&opcion);
                switch(opcion){
                case 1:///Por titulo
                    while(control == 's'){
                        system("cls");
                        printf("= Consulta por titulo =\n\n");
                        printf("Titulo: ");
                        fflush(stdin);
                        gets(&titulo);
                        consulaTitulo(fileP,titulo);
                        printf("Buscar otro titulo s/n: ");
                        fflush(stdin);
                        scanf("%c",&control);
                    }
                break;
                case 2:///por genero
                    while(control == 's'){
                        system("cls");
                        printf("= Consulta por genero =\n\n");
                        printf("Genero: ");
                        fflush(stdin);
                        gets(&genero);
                        consultaGenero(fileP,genero);
                        printf("\nBuscar otro genero s/n: ");
                        fflush(stdin);
                        scanf("%c",&control);
                    }
                break;
                }
                control = 's';
            }
        break;

        case 5: ///Listados de peliculas
            while(control == 's'){
                printf("= Listados =\n\n");
                printf("1. Por genero\n");
                printf("2. Por titulo\n");
                printf("3. Atras\n\n");
                printf("Opcion: ");
                fflush(stdin);
                scanf("%i",&opcion);
                if(opcion == 1){
                    system("cls");
                    printf("= Por genero = \n\n");
                    listadoPeliculasGenero(fileP);


                }else if(opcion == 2){
                    system("cls");
                    printf("= Por titulo =\n\n");
                    listadoPeliculasTitulo(fileP);
                }
            }
        break;

        case 6: ///Atras
            menuAdmin(fileP,fileU);
        break;
        }
        control = 's';
        system("cls");
    }
}

void menuAdminUsers(char fileP[], char fileU[]){///Muestra el sub-menu "Administrar Usuarios" y sus opciones
    int opcion = 0;
    usuario aux;
    int id = 0;
    char nombre[30];
    int anio;
    char genero;
    char pais[20];
    int estado;
    int dim = 1000; //cambiar esta pedorrada
    usuario arregloU[dim];
    char control = 's';
    //int dim = 1000;     ///Cambiar esta pedorrada
    //pelicula listado[dim];
    while(opcion != 6){
        system("cls");
        printf("= Administrar Usuarios =\n\n");
        printf("1. Alta Usuarios\n");
        printf("2. Cambiar Estado\n");
        printf("3. Modificar Usuarios\n");
        printf("4. Consulta Usuarios\n");
        printf("5. Listados\n\n");
        printf("6. Atras\n\n");
        printf("Opcion: ");

        scanf("%i",&opcion);
        system("cls");
        control = 's';
        switch(opcion){
        case 1:///Alta de usuarios
            while(control == 's'){
                printf("= Alta Usuarios =\n\n");
                altaUsuarios(fileU);
                printf("Cargar nuevo usuario? s/n");
                fflush(stdin);
                scanf("%c",&control);
                system("cls");
            }
            printf("Ver archivo: s/n "); ///Da la opcion de ver el archivo
            fflush(stdin);
            scanf("%c",&control);
            if(control=='s'){
                system("cls");
                mostrarArchivoUsuarios(fileU);
            }
            printf("Menu Usuarios: ");
            /*aux = cargarUsuario();
            mostrarUsuario(aux);*/
            system("pause");
            system("cls");
        break;

        case 2: ///Cambiar estado elimnado
            while(control == 's'){
                printf("= Cambiar Estado =\n\n");
                printf("ID Usuario: ");
                scanf("%i",&id);
                printf("\n");
                cambiarEstadoUsuario(fileU,id);
                mostrarUsuarioEnArchivo(fileU,id);
                printf("\nCambiar estado de otro usuario s/n: ");
                fflush(stdin);
                scanf("%c",&control);
                system("cls");
            }
        break;

        case 3: ///Modificar Usuarios
            while(control == 's'){
                printf("= Modificar Usuario =\n\n");
                printf("ID Usuario: ");
                scanf("%i",&id);
                system("cls");
                modificarUsuario(fileU,id);
                printf("= Modificar Usuario =\n\n");
                mostrarUsuarioEnArchivo(fileU,id);
                printf("Modificar otro usuario s/n: ");
                fflush(stdin);
                scanf("%c",&control);
                system("cls");
            }
        break;

        case 4: ///Consulta
            while(opcion != 7){
                system("cls");
                printf("= Consulta =\n\n");
                printf("1. Por ID\n");
                printf("2. Por nombre\n");
                printf("3. Por anio\n");
                printf("4. Por genero\n");
                printf("5. Por pais\n");
                printf("6. Por estado\n");
                printf("7. Atras\n\n");
                printf("Opcion: ");
                scanf("%i",&opcion);
                control = 's';
                system("cls");

                switch(opcion){
                case 1: ///consulta usuario por su ID
                    while(control == 's'){
                        printf("= Consulta por ID =\n\n");
                        printf("ID: ");
                        scanf("%i",&id);
                        system("cls");
                        printf("= Consulta por ID =\n\n");
                        consulaID(fileU,id);
                        printf("Buscar otro ID s/n: ");
                        fflush(stdin);
                        scanf("%c",&control);
                        system("cls");
                    }
                break;

                case 2:
                    while(control == 's'){
                    printf("= Consulta por Nombre =\n\n");
                    printf("Ingrese nombre: ");
                    fflush(stdin);
                    gets(&nombre);
                    consulaNombre(fileU,nombre);
                    printf("Buscar otro nombre s/n: ");
                    fflush(stdin);
                    scanf("%c",&control);
                    system("cls");
                    }
                break;

                case 3:
                    while(control == 's'){
                    printf("= Consulta por Anio =\n\n");
                    printf("Ingrese anio: ");
                    scanf("%i",&anio);
                    consultaAnio(fileU,anio);
                    printf("Buscar otro anio s/n: ");
                    fflush(stdin);
                    scanf("%c",&control);
                    system("cls");
                    }
                break;

                case 4:
                    while(control == 's'){
                    printf("= Consulta por Genero =\n\n");
                    printf("Ingrese genero (m/f): ");
                    fflush(stdin);
                    scanf("%c",&genero);
                    consulaGenero(fileU,genero);
                    printf("Buscar otro genero s/n: ");
                    fflush(stdin);
                    scanf("%c",&control);
                    system("cls");
                    }
                break;

                case 5:
                    while(control == 's'){
                    printf("= Consulta por Pais =\n\n");
                    printf("Ingrese pais: ");
                    fflush(stdin);
                    gets(&pais);
                    consultaPais(fileU,pais);
                    printf("Buscar otro pais s/n: ");
                    fflush(stdin);
                    scanf("%c",&control);
                    system("cls");
                    }
                break;

                case 6:
                    while(control == 's'){
                    printf("= Consulta por Estado =\n\n");
                    printf("Activo: 0\n");
                    printf("Eliminado: 1\n\n");
                    printf("Estado(0/1): ");
                    scanf("%i",&estado);
                    consultaEstado(fileU,estado);
                    printf("Buscar otro estado s/n: ");
                    fflush(stdin);
                    scanf("%c",&control);
                    system("cls");
                    }
                break;

                case 7:///Redirige al menu "Administrar Usuarios"
                    menuAdminUsers(fileP,fileU);
                break;
                }
                control = 's';
            }
        break;

        case 5:
            while(control == 's'){
                printf("= Listados =\n\n");
                printf("1. Por nombre\n");
                printf("2. Por algo\n");
                printf("3. Atras\n\n");
                printf("Opcion: ");
                fflush(stdin);
                scanf("%i",&opcion);
                if(opcion == 1){
                    system("cls");
                    printf("= Por nombre = \n\n");
                    listadoUsuariosNombre(fileU);

                }else if(opcion == 2){
                    printf("No se que poner aca\n");///COMPLETAR
                } else if(opcion == 3){
                    menuAdminUsers(fileP,fileU);
                } else{

                }
                printf("Continuar s/n ");
                fflush(stdin);
                scanf("%c",&control);
                system("cls");
            }
        break;

        case 6:///Redirige al Menu Administrador
            menuAdmin(fileP,fileU);
        break;


        }
        ///opcion = 0;
    }

    control = 's';
    system("cls");
}



///=================== MENU USUARIO ================================///

///=======  Menu usuarios ================///

void menuUsuario(char fileP[],char fileU[],int id){///Muestra el menu de usuario y sus opciones
    int opcion;
    int idP;
    char continuar = 'n';
    char titulo[30];
    char genero[20];
    usuario aux;
    aux = devolverUsuarioEnArchivo(fileU,id);
    printf("= Bienvenido, %s =\n\n",aux.nombreUsuario);
    printf("1. Perfil\n");
    printf("2. Peliculas\n");
    printf("3. Ver pelicula\n");
    printf("4. Recomendadas\n");
    printf("5. Historial\n");
    printf("6. Salir\n\n");
    printf("Opcion: ");
    scanf("%i",&opcion);
    system("cls");
    switch(opcion){
    case 1: ///Mostrar perfil del usuario
        while(continuar == 'n'){
            printf("= Perfil =\n\n");
            mostrarUsuario(aux);
            printf("Menu usuario s/n: ");
            fflush(stdin);
            scanf("%c",&continuar);
            system("cls");
        }
    break;
    case 2:///mostrar listados
        continuar = 's';
        while(opcion<5 && opcion >0){
            printf("= Peliculas =\n\n");
            printf("1. Listado por titulo\n");
            printf("2. Listado por genero\n");
            printf("3. Buscar por titulo\n");
            printf("4. Buscar por genero\n");
            printf("5. Atras\n\n");
            printf("Opcion: ");
            scanf("%i",&opcion);
            system("cls");
            switch(opcion){
            case 1:
                continuar = 'n';
                while(continuar == 'n'){
                system("cls");
                printf("= Listado por Titulo =\n\n");
                listadoPeliculasTitulo(fileP);
                printf("\nAtras s/n: ");
                fflush(stdin);
                scanf("%c",&continuar);
                }
                system("cls");
            break;

            case 2:
                continuar = 'n';
                while(continuar == 'n'){
                system("cls");
                printf("= Listado por Genero =\n\n");
                listadoPeliculasGenero(fileP);
                printf("\nAtras s/n: ");
                fflush(stdin);
                scanf("%c",&continuar);
                }
                system("cls");
            break;

            case 3:
                continuar = 'n';
                while(continuar == 'n'){
                    continuar = 's';
                    while(continuar == 's'){
                        system("cls");
                        printf("= Buscar por Titulo = \n\n");
                        printf("Titulo: ");
                        fflush(stdin);
                        gets(&titulo);
                        consulaTitulo(fileP,titulo);
                        printf("\nBuscar otro titulo s/n: ");
                        fflush(stdin);
                        scanf("%c",&continuar);
                    }
                    printf("Atras s/n: ");
                    fflush(stdin);
                    scanf("%c",&continuar);
                }
                system("cls");
            break;

            case 4:
                continuar = 'n';
                while(continuar == 'n'){
                    continuar = 's';
                    while(continuar == 's'){
                        system("cls");
                        printf("= Buscar por Genero = \n\n");
                        printf("Genero: ");
                        fflush(stdin);
                        gets(&genero);
                        consultaGenero(fileP,genero);
                        printf("\nBuscar otro genero s/n: ");
                        fflush(stdin);
                        scanf("%c",&continuar);
                    }
                    printf("Atras s/n: ");
                    fflush(stdin);
                    scanf("%c",&continuar);
                }
                system("cls");
            break;

            case 5:
                opcion = 5;
            break;

            default:
                opcion = 1;

            }

        }
    break;
    case 3:///Ver Pelicula
        continuar = 's';
        while(continuar=='s'){
        system("cls");
        printf("= Ver Pelicula = \n\n");
        printf("Ingrese ID: ");
        scanf("%i",&idP);
        if(verPelicula(fileP,idP)> -1){
            aux.peliculasVistas[0] = idP;
        } else {
            printf("Pelicula no disponible\n");
        }
        printf("\nVer otra pelicula s/n: ");
        fflush(stdin);
        scanf("%c",&continuar);
        }
        system("cls");

    break;
    case 4:
        ///recomendaciones
    break;
    case 5:
        ///mostrar historial
    break;
    case 6:///Redirige al Menu Principal
        system("cls");
        menuPrincipal(fileP,fileU);
    break;
    default:///Redirige al Menu de Usuario
        menuUsuario(fileP,fileU,id);
    }
    menuUsuario(fileP,fileU,id);
} ///Completar


///================== FUNCIONES CONTRASE�A ==========================///


///
void pasarContraseniaAMatrix(char contrasenia[11],int contraseniaMatrix[2][5]){
    int fila;
    int columna;
    int i = 0;

    for(columna=0;columna<5;columna++){
        for(fila=0;fila<2;fila++){
            contraseniaMatrix[fila][columna] = contrasenia [i];
            i++;
        }
    }
}

///
void pasarMatrixAString(char contrasenia[11],int contraseniaMatrix[2][5]){
    int fila;
    int columna;
    int i = 0;
    contrasenia[10]='\0';
    for(columna=0;columna<5;columna++){
        for(fila=0;fila<2;fila++){
           contrasenia [i] = contraseniaMatrix[fila][columna];
            i++;
        }
    }
}

///
void encriptarContrasenia(int contraseniaMatrix[2][5],int pass[2][5]){
    int testigo[2][2];
    int row,col;
    int i;

    testigo[0][0]=1;
    testigo[0][1]=0;
    testigo[1][0]=2;
    testigo[1][1]=1;

    for(row=0;row<2;row++){
        for(col=0;col<5;col++){
            pass[row][col] = testigo[row][0]*contraseniaMatrix[0][col]+testigo[row][1]*contraseniaMatrix[1][col];
        }
    }
}


///
void desencriptarContrasenia(int contraseniaMatrix[2][5],int pass[2][5]){
    int testigo[2][2];
    int row,col;
    int i;

    testigo[0][0]=1;
    testigo[0][1]=0;
    testigo[1][0]=-2;
    testigo[1][1]=1;

    for(row=0;row<2;row++){
        for(col=0;col<5;col++){
            pass[row][col] = testigo[row][0]*contraseniaMatrix[0][col]+testigo[row][1]*contraseniaMatrix[1][col];
        }
    }
}


///=================================================================///

void mostrarMatrix(int rows, int cols, int matrix[rows][cols]){
    int i,j;
    for(i=0;i<rows;i++){
        for(j=0;j<cols;j++){
            if(matrix[i][j]<10){
                printf("[0%i]",matrix[i][j]);
            } else {
                printf("[%i]",matrix[i][j]);
            }
        }
        printf("\n");
    }
}





///================ Validacion Usuario ========================///


int validacionUser(char fileU[]){
    char username[30];
    char contrasenia[11];
    int valido = -1;
    char pass[11];
    int passMatrix[2][5];
    int control = 1;
    usuario aux;

    system("cls");
    printf("\n USERNAME: ");
    fflush(stdin);
    gets(&username);
    printf(" PASSWORD: ");
    fflush(stdin);
    gets(&contrasenia);

    FILE*archi = NULL;
    archi = fopen(fileU,"rb");
    if(archi != NULL){
        while(control>0 && valido<0){
            control = fread(&aux,sizeof(usuario),1,archi);
            if(strcmpi(aux.nombreUsuario,username)==0){
                desencriptarContrasenia(aux.pass,passMatrix);
                pasarMatrixAString(pass,passMatrix);
                if (strcmpi(pass,contrasenia)==0){
                    valido=aux.idUsuario;
                }
            }
        }
    }
    fclose(archi);
    return valido;
}





///================= MAIN ==========================================///
int main(){
    char archivoPeliculas[] = "peliculas.dat";
    char archivoUsuarios[] = "usuarios.dat";
    FILE*archiPeliculas = NULL;
    FILE*archiUsuarios = NULL;
    archiPeliculas = archivoPeliculas;
    archiUsuarios = archivoUsuarios;

    menuPrincipal(archiPeliculas,archiUsuarios);

    char pass[11];
    char pass2[11];
    int matrixPass[2][5];
    int passEncriptada[2][5];
    int matrixDes[2][5];
    int i;

    /*printf("Ingrese pass: ");
    fflush(stdin);
    gets(&pass);*/
    /*
    for(i=0;i<10;i++){
        scanf("%i",&pass[i]);
    }*/

    /*
    pasarContraseniaAMatrix(pass,matrixPass);
    printf("Pass en ASCII\n");
    mostrarMatrix(2,5,matrixPass);
    encriptarContrasenia(matrixPass,passEncriptada);
    printf("Pass encriptada\n");
    mostrarMatrix(2,5,passEncriptada);
    printf("Pass original: \n");
    desencriptarContrasenia(passEncriptada,matrixDes);
    mostrarMatrix(2,5,matrixDes);
    pasarMatrixAString(pass2,matrixDes);
    printf("Pass: %s",pass2);*/




    return 0;
}
///========================================================///









