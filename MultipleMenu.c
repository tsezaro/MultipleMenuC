#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define N 10
#define ARCHIVO "empleados.dat"
#define BAJA_FISICA "empleado_baja_fisica.dat"


struct empleado
{
    int id_legajo;
    char nombre[30];
    char categoria;
    float sueldo;
    int activo;

};
//==================================================================================================
//Funciones principales que cumplen con lo solicitado
void crear_archivo(FILE *archivo);
void agregar_empleado(FILE *archivo);
void listar(FILE *archivo, char* n_archivo);
struct empleado buscar(FILE *archivo,int flag,int id,char *nombre);
void modificar(FILE *archivo);
void actualizar(FILE *archivo,char categoria[1][3],float porcentaje[3]);
void baja_logica(FILE *archivo);
void baja_fisica(FILE *archivo);
//==================================================================================================
//==================================================================================================
//Funciones de carga de datos
int carga_lejago();
char *carga_nombre();
char carga_categoria();
float carga_flotante(char mensaje[30]);
int carga_activo();
//==================================================================================================
//==================================================================================================
//Funciones secundarias para validar datos y corregir texto
int  valida_cadena(char cadena[30]);
int valida_numero(char numero[30],int punt);
int valida_flag(char activo[30],int verdadero,int falso);
void correcto_texto(char *nombre_persona);

//=========================================================================================== MAIN =============================================================================================================
int main(){
// DECALRO LAS VARIABLES DEL MAIN
system("cls");
int flag=0;
char opcion;
char aux_opcion[30];
int id=0;
char nombre[30];
char caregorias[1][3];
float porcentaje[3];
FILE *archivo;
struct empleado d_empleado;

//COMIENZA EL MENU
do
{
   printf("1)  Crear Archivo\n");
   printf("2)  Dar de alta a un empleado\n");
   printf("3)  Listar los empleados\n");
   printf("4)  Buscar registro\n");
   printf("5)  Modificar registro\n");
   printf("6)  Actualizar sueldos por paritarias\n");
   printf("7)  Baja logica\n");
   printf("8)  Baja fisica\n");
   printf("9)  Listar baja fisica\n");
   printf("10) Salir del programa\n");
   scanf("%d",&opcion);
   fflush(stdin);
    switch (opcion)
    {
    case 1:
        crear_archivo(archivo);
        system("pause");
        break;
    case 2:

        agregar_empleado(archivo);
        system("pause");
        break;
    case 3:
        listar(archivo,ARCHIVO);
        system("pause");
        break;
    case 4:
        system("cls");
        printf("1) Buscar por registro\n");
        printf("2) Buscar por nombre\n");
        scanf("%c",aux_opcion);
        fflush(stdin);
        while (!valida_flag(aux_opcion,49,50))
        {
        system("cls");
        printf("Porfavor ingrese una opcion valida:\n");
        printf("1) Buscar por registro\n");
        printf("2) Buscar por nombre\n");
        scanf("%c",aux_opcion);
        fflush(stdin);
        };
        flag=atof(aux_opcion);
        if (flag==1)
        {
            id=carga_lejago();
            d_empleado=buscar(archivo,flag,id,nombre);
        }
        else
        {
            strcpy(nombre,carga_nombre());
            d_empleado=buscar(archivo,flag,id,nombre);
        }
        switch (d_empleado.activo)
        {
        case 404:
            system("cls");
            printf("No se encontro el registro buscado.\n");
            break;

        default:
            system("cls");
            printf("%s\t%-30s\t%s\t%10s\t%s\n","LEG","NOMBRE","CATEGORIA","SUELDO","ACTIVO");
            printf("%d\t%-30s\t%5c\t\t%10.2f\t%3d\n",d_empleado.id_legajo,d_empleado.nombre,d_empleado.categoria,d_empleado.sueldo,d_empleado.activo);

            break;
        }
        system("pause");
        break;
    case 5:
        modificar(archivo);
        system("pause");
        break;
    case 6:
        for (int i = 0; i < 3; i++)
        {
            system("sys");
            caregorias[1][i]=carga_categoria();
            porcentaje[i]=carga_flotante("Porcentaje");
            system("pause");
        };

        actualizar(archivo,caregorias,porcentaje);
        system("pause");
        break;
    case 7:
        baja_logica(archivo);
        system("pause");
        break;
    case 8:
        baja_fisica(archivo);
        system("pause");
        break;
    case 9:
        listar(archivo,BAJA_FISICA);
        system("pause");
        break;
    default:
        break;
    };
system("cls");
} while (opcion!=10);
return 0;
}
;


void agregar_empleado(FILE *archivo){
    /*
    ESTA FUNCION SERA UTILIZADA PARA AGREGAR EMPLEADOS A LA NOMINA RESPETANTO EL NUMERO DE LEGAGO COMO POSICION EN LA TABLA
    FUNCIONES AUXILIARES:
    --  buscar()
    --  carga_nombre()
    --  arga_categoria();
    --  carga_flotante("sueldo");
    --  carga_activo();
    */
    struct empleado emp;
    int id;
    int flag=1;
    char cmp_number[30];


    archivo=fopen(ARCHIVO,"r+b");
    if (archivo==NULL)
    {
           printf("Error en la apertura del archivo\n");
    }
    else{
        while (!feof(archivo)&&(flag==1)){


                id=carga_lejago();
                emp=buscar(archivo,1,id,"");
                system("cls");
                if (id==emp.id_legajo)
                {
                    rewind(archivo);
                    printf("Ya existe el numero de lejago, vuelva a intentarlo\n");
                    system("pause");
                    }
                else
                {
                emp.id_legajo=id;

                strcpy(emp.nombre,carga_nombre());
                emp.categoria=carga_categoria();
                emp.sueldo=carga_flotante("sueldo");
                emp.activo=carga_activo();
                system("cls");
                fseek(archivo, sizeof(struct empleado)*emp.id_legajo, SEEK_CUR);
                fwrite(&emp,sizeof(struct empleado),1,archivo);
                rewind(archivo);
                fflush(archivo);
                system("cls");
                printf("Desea continuar agregando empleados? Precione: 1 para continuar 0 salir de la carga\n");
                gets(cmp_number);
                fflush(stdin);
                while (!valida_flag(cmp_number,49,48))
                {
                    printf("Porfavor ingrese una opcion valida\n1) continuar\n0) salir\n");
                    gets(cmp_number);
                    fflush(stdin);
                }
                flag=atof(cmp_number);
                };
        };
    };
   fclose(archivo);
};

void listar(FILE *archivo, char* n_archivo){
    /*
    Esta funcion dependiendo la opcion que se escoja listara los empleados recorriendo todo el archivo.
    --  Lista todos los empleados
    --  Lista solo los activos
    */
    struct empleado emp;
    int flag;
    char aux[1];
    archivo=fopen(n_archivo,"rb");
    if (archivo==NULL)
    {
        printf("Error en la apertura del archivo");
    }
    else
    {
        system("cls");
        printf("1) Listar todos los empleados\n");
        printf("2) Listar todos los empleados activos\n");
        scanf("%c",aux);
        fflush(stdin);
        while (!valida_flag(aux,49,50)){
        system("cls");
        printf("Porfavor ingrese una opcion valida:\n");
        printf("1) Listar todos los empleados\n");
        printf("2) Listar todos los empleados activos\n");
        scanf("%c",aux);
        fflush(stdin);
        }
        flag=atof(aux);
        fread(&emp,sizeof(struct empleado),1,archivo);
        system("cls");
        printf("%s\t%-30s\t%s\t%10s\t%s\n","LEG","NOMBRE","CATEGORIA","SUELDO","ACTIVO");
        while(!feof(archivo)){
            if (flag==1)
            {
                printf("%d\t%-30s\t%5c\t\t%10.2f\t%3d\n",emp.id_legajo,emp.nombre,emp.categoria,emp.sueldo,emp.activo);
                fread(&emp,sizeof(struct empleado),1,archivo);
            }
            else if (flag==2)
            {
                switch (emp.activo)
                {
                case 1:
                    printf("%d\t%-30s\t%5c\t\t%10.2f\t%3d\n",emp.id_legajo,emp.nombre,emp.categoria,emp.sueldo,emp.activo);
                    fread(&emp,sizeof(struct empleado),1,archivo);
                    break;
                default:
                    fread(&emp,sizeof(struct empleado),1,archivo);
                    break;
                }
            }

        };
    }
    fclose(archivo);
};

void crear_archivo(FILE *archivo){
    /*
    Funcion que crea archivo con 10 datos por defecto.
    En el momento de la carga se deja la posicion 0 del archivo sin datos.
    */
    struct empleado emp;
    char *v_nombre[N]={"Martin Ferreyra","Alberto Paez","Sebastian Melo","Carlos Perez","Lautaro Martinez","Ernesto Roa","Esteban Lopez","Adrian Gomez","Cristian Miranda","Andres Lizarreaga"};
    char v_categoria[1][N]={'A','B','B','C','A','C','B','A','C','C'};
    float sueldo[N]={90000.00,50000.00,60000.00,45000.00,150500.00,40000.00,68000.00,120000.00,42000.00,47000.00};
    int activo[N]={1,1,0,1,1,0,1,0,1,1};
archivo=fopen(ARCHIVO,"rb");
if(archivo==NULL){
archivo=fopen(ARCHIVO,"w+b");
for (int i = 0; i < N; i++)
{
    emp.id_legajo=i+1;
    strcpy(emp.nombre,v_nombre[i]);
    emp.categoria=v_categoria[0][i];
    emp.sueldo=sueldo[i];
    emp.activo=activo[i];
    fseek(archivo,sizeof(struct empleado)*(i+1),SEEK_CUR);
    fwrite(&emp,sizeof(struct empleado),1,archivo);
    rewind(archivo);
    fflush(archivo);
}
    fclose(archivo);
}
else
{
    printf("El archivo ya existe\n");
}
};

struct empleado buscar(FILE *archivo,int flag,int id,char *nombre){
    /*
    ESTA FUNCION BUSCARA UN EMPLEADO DEPENDIENDO SI SE DESEA BUSCAR POR NOMBRE O POR LEGAJO
    --  POR LEGAJO UTILIZA LA FORMA DIRECTO
    --  POR NOMBRE UTILIZA LA FORMA SECUENCIAL

    LA FORMULA DEVUELVE UNA ESTRUCTURA PARA SER UTILIZADA EN EL MAIN Y EN EL RESTO DE LAS FUNCIONES.
    */
    struct empleado emp;
    archivo=fopen(ARCHIVO,"rb");
    if (archivo==NULL)
    {
           printf("Error en la apertura del archivo\n");
    }
    else
    {
        switch (flag)
        {
        case 1:
            fseek(archivo,sizeof(struct empleado)*id, SEEK_CUR);
            fread(&emp,sizeof(struct empleado),1,archivo);
            if (id==emp.id_legajo)
            {
            system("cls");
            fclose(archivo);
            return emp;
            };
            break;
        case 2:
            system("cls");
            while (!feof(archivo))
            {
                fread(&emp,sizeof(struct empleado),1,archivo);
                if (strstr(nombre,emp.nombre)!=NULL&&emp.id_legajo!=0)
                {
                    return emp;
                    fclose(archivo);

                }
            }
            break;
        default:
            break;
        }

    }
emp.activo=404;
return emp;
};


void modificar(FILE *archivo){
    /*
    ESTA FUNCION BUSCARA EL EMPLEADO QUE SE DESEA MODIFICAR Y LE APLICARA EL CAMBIO CORRESPONDIENTE A LA CATEGORIA Y AL SUELDO
    FUNCIONES AUXILIARES:
    --  buscar()
    --  arga_categoria();
    --  carga_flotante("sueldo");
    */
    struct empleado emp;
    char cmp_number[30];
    char nombre[30];
    int flag;
    int id;
    int confirmar;
    archivo=fopen(ARCHIVO,"r+b");
    if (archivo==NULL)
    {
           printf("Error en la apertura del archivo\n");
    }
    else
    {
//============== MENU DE OPCIONES PARA MODIFICAR REGISTOS ========================
//AQUI INSERTAMOS Y VALIDAMOS QUE LAS OPCIONES SEAN LAS QUE SE MUESTRAN EN LA PANTALLA
        system("cls");
        printf("1) Modificar por registro\n");
        printf("2) Modificar por nombre\n");
        gets(cmp_number);
        fflush(stdin);
        while (!valida_flag(cmp_number,49,50))
        {
        system("cls");
        printf("Porfavor ingrese una opcion valida:\n");
        printf("1) Modificar por registro\n");
        printf("2) Modificar por nombre\n");
        gets(cmp_number);
        fflush(stdin);
        };
        flag=atof(cmp_number);

//=============================================================================================================================
//============ EN BASE A LA OPCION SE OBTIENE LA POSICION DEL CURSOR DEL ARCHIVO PARA ACCEDER AL REGISTRO =====================
        switch (flag)
        {
        case 1:
            system("cls");
            id=carga_lejago();
            emp=buscar(archivo,flag,id,"");
            if (emp.activo==404)
            {
                system("cls");
                printf("No se encontro el registro para modificar\n");
                break;
            }

            // printf("%d",emp.id_legajo);
// =============================================== CARGA DE DATOS ==========================================================================
                system("cls");
                emp.categoria=carga_categoria();
                emp.sueldo=carga_flotante("sueldo");
//============================================== FIN CARGA DE DATOS ================================================

//============================================== CONFIRMACION DE MODIFICACION ============================================
                system("cls");

                printf("Esta seguro que quiere modificar los datos de: \t%s\n",emp.nombre);
                printf("\t1) CONFIRMAR\n");
                printf("\t2) RECHAZAR\n");
                gets(cmp_number);
                fflush(stdin);
                while (!valida_flag(cmp_number,49,50))
                {
                    printf("Porfavor ingrese una opcion valida\n");
                    printf("\t1) CONFIRMAR\n");
                    printf("\t2) RECHAZAR\n");
                    gets(cmp_number);
                    fflush(stdin);
                };
                flag=atof(cmp_number);
                system("cls");
                switch (flag)
                {
                case 1:
                    fseek(archivo,sizeof(struct empleado)*emp.id_legajo,SEEK_CUR);
                    fwrite(&emp,sizeof(struct empleado),1,archivo);
                    fflush(archivo);
                    fclose(archivo);
                    printf("se modifico\n");
                    break;
                case 2:
                    fclose(archivo);
                    break;
                default:
                    break;
                };
            system("cls");

            break;
//=================================================================================================================================================================
        case 2:
            if (emp.activo==404)
            {
                system("cls");
                printf("No se encontro el registro para modificar\n");
                break;
            }
            system("cls");
            strcpy(nombre,carga_nombre());
            emp=buscar(archivo,flag,0,nombre);

// =============================================== CARGA DE DATOS ==========================================================================
            emp.categoria=carga_categoria();
            emp.sueldo=carga_flotante("sueldo");
//============================================== FIN CARGA DE DATOS ======================================================
//============================================== CONFIRMACION DE MODIFICACION ============================================
                system("cls");

                printf("Esta seguro que quiere modificar los datos de: \t%s\n",nombre);
                printf("\t1) CONFIRMAR\n");
                printf("\t2) RECHAZAR\n");
                gets(cmp_number);
                fflush(stdin);
                while (!valida_flag(cmp_number,49,50))
                {
                    printf("Porfavor ingrese una opcion valida\n");
                    printf("\t1) CONFIRMAR\n");
                    printf("\t2) RECHAZAR\n");
                    gets(cmp_number);
                    fflush(stdin);
                }
                flag=atof(cmp_number);
                system("cls");
                switch (flag)
                {
                case 1:
                    system("cls");
                    fseek(archivo,sizeof(struct empleado)*emp.id_legajo,SEEK_CUR);
                    fwrite(&emp,sizeof(struct empleado),1,archivo);
                    fflush(archivo);
                    fclose(archivo);
                    printf("se modifico\n");

                    break;
                case 2:
                    fclose(archivo);
                    break;
                default:
                    break;
                }
                 break;
        default:
            break;
        };


    } ;
};

void baja_logica(FILE *archivo){
    /*
    ESTA FUNCION SE UTILIZARA PARA CAMBIARLE EL FLAG DE ACTIVO A UN EMPLEADO.
    -- PRIMERO MOSTRARA LA LISTA DE TODOS LOS EMPLEADOS PARA QUE PUEDA VISUALIZAR Y ESCOJER UN LEGAJO
    -- LUEGO PEDIRA CONFIRMACION MOSTRANDO EL NOMBRE DE QUIEN SE DESEA DAR DE BAJA
    */
    struct empleado emp;
    int id, flag=0;
    int aux;
    archivo = fopen(ARCHIVO, "r+b");
    if(archivo==NULL){
        printf("Error en la apertura del archivo\n");
    }
    else{
        system("cls");
        printf("Se mostrara los datos para que observe que legajo quiere dar de baja\n");
        fread(&emp,sizeof(struct empleado),1,archivo);
        printf("%s\t%-30s\t%s\t%10s\t%s\n","LEG","NOMBRE","CATEGORIA","SUELDO","ACTIVO");
        while(!feof(archivo)){
        printf("%d\t%-30s\t%5c\t\t%10.2f\t%3d\n",emp.id_legajo,emp.nombre,emp.categoria,emp.sueldo,emp.activo);
        fread(&emp,sizeof(struct empleado),1,archivo);
            }
        printf("\nAprete una tecla para continuar y escojer un legajo\n");
        system("pause");
        id=carga_lejago();
        fseek(archivo,id*sizeof(struct empleado),SEEK_SET);
        fread(&emp,sizeof(struct empleado),1,archivo);
        if(emp.id_legajo==id  && emp.activo==1){
            emp.activo=0;
            fseek(archivo,-sizeof(struct empleado),SEEK_CUR);
            fwrite(&emp,sizeof(struct empleado),1,archivo);
            rewind(archivo);
            printf("Empleado dado de baja exitosamente\n");
            printf("%s\t%-30s\t%s\t%10s\t%s\n","LEG","NOMBRE","CATEGORIA","SUELDO","ACTIVO");
            while(!feof(archivo)){
                    switch (emp.activo)
                    {
                    case 1:
                        printf("%d\t%-30s\t%5c\t\t%10.2f\t%3d\n",emp.id_legajo,emp.nombre,emp.categoria,emp.sueldo,emp.activo);
                        fread(&emp,sizeof(struct empleado),1,archivo);
                        break;
                    default:
                        fread(&emp,sizeof(struct empleado),1,archivo);
                        break;
                    };
                                }
            }
        else{
            switch (emp.activo)
            {
            case 0:
                system("cls");
                printf("El cliente ya se encuentra inactivo\n");
                break;
            default:
                system("cls");
                printf("El cliente no existe\n");
                break;
            }
        }
    }
    fclose(archivo);
};

void baja_fisica(FILE *archivo){
    system("cls");
    remove(BAJA_FISICA);
    struct empleado emp;
    archivo=fopen(ARCHIVO,"r+b");
    FILE *aux = fopen(BAJA_FISICA,"w+b");
    if(archivo==NULL){
        printf("Error en la apertura del archivo");
    }else{
        fread(&emp,sizeof(struct empleado),1,archivo);
        while(!feof(archivo)){
            if(emp.activo==1){
                fseek(aux,sizeof(struct empleado)*emp.id_legajo, SEEK_CUR);
                fwrite(&emp, sizeof(struct empleado),1,aux);
                rewind(aux);
                fflush(aux);
            }
            fread(&emp,sizeof(struct empleado),1,archivo);
        }
    }
    fclose(archivo);
    fclose(aux);
    printf("Bajas exitosas\n");
};

void actualizar(FILE *archivo,char categoria[1][3],float porcentaje[3]){
    /*
    ESTA FUNCION RECIBE COMO PARAMETRO DOS ARRAYS, UNO CON LAS CATEGORIAS INGRESADAS Y OTRA CON LOS PORCENTAJES
    --  LA FUNCION RECORRE LA LISTA DE CATEGORIAS CON SU RESPECTIVO PORCENTAJES Y COMIENZA A BUSCAR Y APLICAR EL CAMBIO A TODOS LOS EMPLEADOS
    --  EL PORCENTAJE REALIZARA LA ECUACION (1+PORCENTAJE) CON EL FIN DE DEJAR EL INCREMNTE APLICADO AL SUELDO.
    */
    struct empleado emp;
    archivo=fopen(ARCHIVO,"r+b");
    if(archivo==NULL){
        printf("Error en la apertura del archivo");
    }
    else{


    for (int i = 0; i < sizeof(categoria[1]); i++)
    {
        fread(&emp,sizeof(struct empleado),1,archivo);
        while(!feof(archivo)){

            emp.sueldo*=(1+(porcentaje[i]/100));
                if (emp.categoria==categoria[1][i])
                {
                fseek(archivo,-sizeof(struct empleado),SEEK_CUR);
                fwrite(&emp,sizeof(struct empleado),1,archivo);

                fseek(archivo,-sizeof(struct empleado),SEEK_CUR);
                fread(&emp,sizeof(struct empleado),1,archivo);

                fread(&emp,sizeof(struct empleado),1,archivo);
                }
            fread(&emp,sizeof(struct empleado),1,archivo);
            }
        rewind(archivo);
        }
    }
    fclose(archivo);
    system("cls");
    printf("Se actualizaron los sueldos\n");

};

int valida_cadena(char cadena[30]){
    /*
    ESTA FUNCION RECIBE COMO PARAMETRO UNA CADENA DE TEXTO
    --  VA A IR RECORRIENDO LETRA POR LETRA Y COMPARANDO SI ES UN CARACTER
    --  SE TIENE ENCUENTA EL ESPACIO
    --  LA FUNCION DEVUELVE UN INT COMO BANDERA.
    */
    int i=0,flag=0,cant_letras;
    cant_letras=strlen(cadena);
    while(i<cant_letras && flag==0){
        if (isalpha(cadena[i])!=0)
        {
            i+=1;
        }
        else if (cadena[i]==32)
        {
            i+=1;
        }
        else
        {
            flag=1;
        }
    }
return flag;

};
int valida_numero(char numero[30],int punt){
    /*
    ESTA FUNCION RECIBE DOS PARAMETROS, EL NUMERO QUE LO VA A RECIBIR COMO UNA CADENA Y UN INT QUE SERA EL CARACTER QUE DESEAMOS COMPLEMENTE AL NUMERO
    --  EL NUMERO COMO CHAR SERA UTILIZADO PARA RECORRER CARACTER POR CARACTER Y CORROBORAR QUE SEA UN DIGITO
    --  EL ENTERO QUE SE LE COLOCA SERA UN NUMERO ASCCII CON EL FIN DE VALIDAR SI UN CARACTER ES UN SIMBOLO ESPECIAL.
    --  POR EJEMPLO INSERTAMOS UN . (46) VA A VALIDAR QUE SOLO EXISTA UN PUNTO, EN CASO DE EXISTIR 2 NO VALIDARA QUE SEA UN NUMERO
    -- DEVUELVE UN ENTERO COMO BANDERA.
    */
    int i=0,flag=0,cant_letras,flag_puntos=1;
    cant_letras=strlen(numero);
    while(i<cant_letras && flag==0){
        if (isdigit(numero[i])!=0)
        {
            i+=1;
        }
        else if (numero[i]==punt)
        {
            switch (flag_puntos)
            {
            case 1:
                i+=1;
                flag_puntos=0;
                break;

            default:
                flag=1;
                break;
            };
        }
        else
        {
            flag=1;
        }
    }
return flag;
};
void correcto_texto(char *nombre_persona){
    /*
    ESTA FUNCION RECIBE UNA CADENA Y RECORRERA LETRA POR LETRA REALIZANDO LOS SIGUIENTES PASO:
    --  CAMBIARA A MAYUSCULAS LA PRIMERA LETRA DE CADA PALABRA SEPARADA POR UN ESPACIO
    --  CAMBIARA A MINUSCULAS LAS PALABRAS RESTANTES.
    */
    char tmp[30];
    int flag=0;
    strcpy(tmp,nombre_persona);
    nombre_persona[0]=toupper(tmp[0]);
    for (int i = 1; i < strlen(nombre_persona)  ; i++)
    {

        if ((flag==1))
        {
            nombre_persona[i]=toupper(tmp[i]);
        }
        else
        {
             nombre_persona[i]=tolower(tmp[i]);
        };
        switch (nombre_persona[i])
        {
        case 32:
            flag=1;
            break;
        default:
            flag=0;
            break;
        };
    };

};
int valida_flag(char activo[30],int verdadero,int falso){
    /*
    ESTA FUNCION LA UTILIZO PARA VALIDAR LOS FLAGS DE LOS MENUS DE OPCIONES
    CON EL FIN DE QUE SOLO SE ESCOJA LA OPCION QUE SE MUESTRA.
    */
    int flag=0;
    if(isdigit(activo[0])!=0 ){
        if (activo[0]==verdadero||activo[0]==falso)
        {
            flag=1;
        }
        else
        {
            flag=0;
        }
    }
    else
    {
        flag=0;
    };
return flag;
};
int carga_lejago(){
system("cls");
struct empleado emp;
int id;
int cont=1;
int flag=1;
int aux;
char cmp_number[30];
printf("Ingrese el numero de legajo:\n");
gets(cmp_number);
fflush(stdin);
aux=valida_numero(cmp_number,0);
while (aux)
{
    printf("No se admite caracteres ni numeros negativos, Intente nuevamente\n");
    gets(cmp_number);
    fflush(stdin);
    aux=valida_numero(cmp_number,0);
};
id=atof(cmp_number);
return id;
};
char *carga_nombre(){
system("cls");
int aux;
static char nombre[30];
    printf("Ingrese el nombre del empleado\n");
    gets(nombre);
    fflush(stdin);
    aux=valida_cadena(nombre);
    while (aux)
    {
    printf("No se admite nuemeros, Intente nuevamente\n");
    gets(nombre);
    fflush(stdin);
    aux=valida_cadena(nombre);
    }
    correcto_texto(nombre);
    system("cls");
return nombre;
};
char carga_categoria(){
    system("cls");
    int aux;
    char categ;
    printf("Ingrese la categoria al a que pertenece(A,B,C)\nSi inserta una minuscula sera cambiada por una mayuscula\n");
    scanf("%c",&categ);
    fflush(stdin);
    aux=1;
    while (aux)
    {
        switch (categ)
        {
        case 'A':
        case 'a':
            categ=toupper(categ);
            aux=0;
            break;
        case 'B':
        case 'b':
            categ=toupper(categ);
            aux=0;
            break;
        case 'C':
        case 'c':
            categ=toupper(categ);
            aux=0;
            break;
        default:
            printf("Ingrese una categoria admitida: A, B, C\n");
            scanf("%c",&categ);
            fflush(stdin);
            break;
        }
    }
    return categ;
};
float carga_flotante(char mensaje[30]){
    system("cls");
    char cmp_number[30];
    int aux;
    float sueldo;
    printf("Ingrese el %s correspondiente\n",mensaje);
    gets(cmp_number);
    fflush(stdin);
    aux=valida_numero(cmp_number,46);
    while (aux)
    {
        printf("No se admite caracteres ni numeros negativos, Intente nuevamente\n");
        gets(cmp_number);
        fflush(stdin);
        aux=valida_numero(cmp_number,46);
    };
    sueldo=atof(cmp_number);
    return sueldo;
};
int carga_activo(){
    system("cls");
    char cmp_number[30];
    int activo;
    printf("Es un empleado activo? 1 para si, 0 para no\n");
    gets(cmp_number);
    fflush(stdin);
    while (!valida_flag(cmp_number,49,48))
    {
        printf("Porfavor ingrese una opcion valida (1 para si, 0 para no)\n");
        gets(cmp_number);
        fflush(stdin);
    }
    activo=atof(cmp_number);
    return activo;
};
