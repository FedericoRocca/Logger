/** ---------------------------------- Definicion de documentado ---------------------------------- **/
/**

    * Los comentarios multilinea comienzan con **/ /** y se hacen en la linea anterior a lo involucrado en el comentario

    * Los comentarios simples comienzan con /// y se hacen en la linea anterior a lo involucrado en el comentario

    * Todas las funciones debe ser comentadas en la linea anterior a la definicion de la función:

        Nombre funcion:
        Utilidad:
        Parametros de entrada:
        -
        Parametros de salida:
        -


    Versionado:
    Para versionar se sigue el siguiente esquema:

        x     .        x        .   x
    Numero de   Subindice         Subindice de mejoras
    version     de correciones
                de bugs

        Numero de version:                  Se aumenta cada vez que se hacen cambios importantes (Mejoras o correcciones de bugs)
        Subindice de correcciones de bugs:  Se aumenta cada vez que se hace una correccion de algun tipo de bug en el codigo fuente.
        Subindice de mejoras:               se aumenta cada vez que se hace una mejora, tanto a nivel programa, como documentación.

    Cada vez que se aumenta el numero de version, se vuelven a 0 ambos subindices.

*/

/** ---------------------------------- Inclusion de librerias ---------------------------------- **/

#define VERSION "2.1.8"

#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <windows.h> /// bool CreateDirectory(LPCTSTR,LPSECURITY_ATTRIBUTES);
#include <winerror.h> /// Libreria de errores std de windows.h

/** ---------------------------------- Declaracion de defines (errors) ---------------------------------- **/
#define OPEN_TRACE_ERR 1

using namespace std;

/** ---------------------------------- Declaracion de variables globales ---------------------------------- **/
/// Variable File, que es la referencia al abrir el archivo de Logs
ofstream File;

/// Variable bool, para saber si el archivo fue abierto correctamente (Por inicializado)
bool Is_Open = false;

/** ---------------------------------- Declaracion de structs, clases, etc... ---------------------------------- **/
typedef struct DateAndTime
{
    int year;
    int month;
    int day;
    int hour;
    int minutes;
    int seconds;
    int msec;
}DateAndTime;

/** ---------------------------------- Declaraciones de funciones ---------------------------------- **/

bool CreateDir();
const string currentDateTime();
void ExitError();
void Log(const int&);
void Log(const string&);
void Log(const string&, const short&);
void Log(const string&, const float&);
void Log(const string&, const unsigned short int&);
void Log(const string&, const int&);
void Log(const string&, const int&, const string&);
void Log(const string&, const unsigned int&);
void Log(const string&, const long int&);
void Log(const string&, const unsigned long int&);
void Log(const string&, const long long int&);
void Log(const string&, const unsigned long long int&);
void Log(const string&, const char&);
void Log(const string&, const string&, const int&, const int&, const int&, const int&);
void Log(const string&, const string&);
void Log(const string&, const SDL_Surface*);
void InitLogger();

/** ---------------------------------- Definiciones de funciones ---------------------------------- **/

bool CreateDir( string Directory )
{
    CreateDirectory( Directory.c_str() , NULL );

    DWORD dwAttrib = GetFileAttributes( Directory.c_str() );

    return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));

}

const string currentDateTime()
{

    DateAndTime date_and_time;
    struct timeval tv;
    struct tm *tm;

    gettimeofday(&tv, NULL);

    tm = localtime(&tv.tv_sec);

    date_and_time.year = tm->tm_year + 1900;
    date_and_time.month = tm->tm_mon + 1;
    date_and_time.day = tm->tm_mday;
    date_and_time.hour = tm->tm_hour;
    date_and_time.minutes = tm->tm_min;
    date_and_time.seconds = tm->tm_sec;
    date_and_time.msec = (int) (tv.tv_usec / 1000);

    stringstream Buff;

    /**
        Para la fecha se mantiene el siguiente formato
        DD/MM/AAAA_HH:mm:SS.sss
        IE: 19/10/2016_16:17:30.742
    **/

    if( date_and_time.day < 10 )
    {
        Buff << "0";
        Buff << date_and_time.day;
        Buff << "/";
    }
    else
    {
        Buff << date_and_time.day;
        Buff << "/";
    }

    if( date_and_time.month < 10 )
    {
        Buff << "0";
        Buff << date_and_time.month;
        Buff << "/";
    }
    else
    {
        Buff << date_and_time.month;
        Buff << "/";
    }

    Buff << date_and_time.year;
    Buff << "_";

    if( date_and_time.hour < 10 )
    {
        Buff << "0";
        Buff << date_and_time.hour;
        Buff << ":";
    }
    else
    {
        Buff << date_and_time.hour;
        Buff << ":";
    }
    if( date_and_time.minutes < 10 )
    {
        Buff << "0";
        Buff << date_and_time.minutes;
        Buff << ":";
    }
    else
    {
        Buff << date_and_time.minutes;
        Buff << ":";
    }

    if( date_and_time.seconds < 10 )
    {
        Buff << "0";
        Buff << date_and_time.seconds;
        Buff << ":";
    }
    else
    {
        Buff << date_and_time.seconds;
        Buff << ".";
    }

    if( date_and_time.msec <= 99 && date_and_time.msec >= 10)
    {
        Buff << "0";
        Buff << date_and_time.msec;
    } else if( date_and_time.msec < 10 )
    {
        Buff << "00";
        Buff << date_and_time.msec;
    } else Buff << date_and_time.msec;

    string Leyenda;
    Buff >> Leyenda;

    return Leyenda;
}

void ExitError()
{
    cout << "Problemas al crear el directorio de almacenamiento de logs" << endl;
    cout << "Error detectado: " << GetLastError() << endl;
    cout << "Presione cualquier tecla para salir del programa" << endl;
    system("pause");
    exit(OPEN_TRACE_ERR);
}

void Log( const int& Message )
{
    File << "[ " << currentDateTime() << " ] - " << Message << endl;
}

void Log( const string& Message )
{
    File << "[ " << currentDateTime() << " ] - " << Message << endl;
}

void Log( const string& Message, const short& Var )
{
    File << "[ " << currentDateTime() << " ] - " << Message << ": " << Var << endl;
}

void Log( const string& Message, const float& Var )
{
    File << "[ " << currentDateTime() << " ] - " << Message << ": " << Var << endl;
}

void Log( const string& Message, const unsigned short int& Var )
{
    File << "[ " << currentDateTime() << " ] - " << Message << ": " << Var << endl;
}

void Log( const string& Message, const int& Var )
{
    File << "[ " << currentDateTime() << " ] - " << Message << ": " << Var << endl;
}

void Log( const string& Message, const int& Var, const string& SecondMessage )
{
    File << "[ " << currentDateTime() << " ] - " << Message << ": " << Var << " " << SecondMessage << endl;
}

void Log( const string& Message, const unsigned int& Var )
{
    File << "[ " << currentDateTime() << " ] - " << Message << ": " << Var << endl;
}

void Log( const string& Message, const long int& Var )
{
    File << "[ " << currentDateTime() << " ] - " << Message << ": " << Var << endl;
}

void Log( const string& Message, const unsigned long int& Var )
{
    File << "[ " << currentDateTime() << " ] - " << Message << ": " << Var << endl;
}

void Log( const string& Message, const long long int& Var )
{
    File << "[ " << currentDateTime() << " ] - " << Message << ": " << Var << endl;
}

void Log( const string& Message, const unsigned long long int& Var )
{
    File << "[ " << currentDateTime() << " ] - " << Message << ": " << Var << endl;
}

void Log( const string& Message, const char& Var)
{
    File << "[ " << currentDateTime() << " ] - " << Message << ": " << Var << endl;
}

void Log( const string& Message, const string& Var)
{
    File << "[ " << currentDateTime() << " ] - " << Message << ": " << Var << endl;
}

void Log( const string& Message, const SDL_Surface* Var)
{
    File << "[ " << currentDateTime() << " ] - " << Message << ": " << Var << endl;
}

void Log( const string& Message, const string& Var1, const int& Var2, const int& Var3, const int& Var4, const int& Var5)
{
    File << "[ " << currentDateTime() << " ] - " << Message << ": " << hex << Var1 << "," << Var2 << "," << dec <<Var3 << "," << Var4 << "," << Var5 << endl;
}

void InitLogger(string ProgName)
{

    string Dir;
    Dir = "Logs/";

    if( CreateDir( Dir ) == false )
    {
        ExitError();
    }

    string ProcessName = ProgName.substr(ProgName.find_last_of("\\")+1);

    string Path;
    Path = Dir + ProcessName;

    Path = Path.replace( Path.find_last_of ("."), Path.length() - Path.find_last_of ("."), ".log" );

    File.open( Path.c_str() , ios::app );

    if( !File.is_open() )
    {
        Is_Open = false;
        ExitError();
    }

    Is_Open = true;
    if(Is_Open) { Log("--------------------------------------------------------"); }
    if(Is_Open) { Log("Logpath", Path); }
}

/** ---------------------------------- Versionado ---------------------------------- **/

/**

+***********************************************************************************************************************+
|                                                  Registro de cambios                                                  |
+***********************************************************************************************************************+
| Fecha       | Hora  | Version Number | Autor de los cambios | Cambios introducidos                                    |
+-------------+-------+----------------+----------------------+---------------------------------------------------------+
| 19/10/2016  | 16:43 | 1.0.0          | Federico Rocca       | Creacion del versionado del archivo                     |
+-------------------------------------------------------------+ Comentado de codigo fuente                              |
|                                                             | Cambio principal:                                       |
|                                                             |                  Apertura unica de archivo de Logs      |
|                                                             | mediante funcion de inicializacion y cierre de dicho    |
|                                                             | archivo mediante funcion de cierre                      |
+-------------+-------+----------------+----------------------+---------------------------------------------------------+
| 19/10/2016  | 17:41 | 1.1.1          | Federico Rocca       | Correcciones varias                                     |
+-------------------------------------------------------------+ Mejoras de logeo                                        |
|                                                             |                  Ahora se abre una sola vez el archivo  |
|                                                             | de logeo, por lo que no hace un uso tan intensivo de    |
|                                                             | disco, abriendo y cerrando el archivo por cada vez que  |
|                                                             | se logeaba una leyenda, mejorando la performance por    |
|                                                             | aproximadamente un %1400 (De aprox 2 a 3 logeos por     |
|                                                             | milisegundo, a aprox 43 veces por milisegundo           |
+-------------+-------+----------------+----------------------+---------------------------------------------------------+
| 20/10/2016  | 10:58 | 1.1.2          | Federico Rocca       | Se eliminan las funciones de cierre de archivo, ya que  |
+-------------------------------------------------------------+ al abrir el archivo mediante ostream, al terminar el    |
|                                                             | scope en el cual fue abierto, se cierra el archivo      |
|                                                             | automaticamente (Testeado)                              |
+-------------+-------+----------------+----------------------+---------------------------------------------------------+
| 21/10/2016  | 11:45 | 1.1.3          | Federico Rocca       |Modificacion                                             |
+-------------------------------------------------------------+            Ahora creo la carpeta automaticamente antes  |
|                                                             | de escribir la primera linea de log. Se intenta crear   |
|                                                             | no mas de 1000 veces, si falla sale del programa        |
|                                                             | (Antes se creaba, pero la primera ejecucion que creaba  |
|                                                             | el directorio, fallaba, debido a que intentaba escribir |
|                                                             | en el directorio que aun no existia.)                   |
|                                                             | * Nuevas pruebas mostraron alrededor de 70 lineas x ms  |
+-------------+-------+----------------+----------------------+---------------------------------------------------------+
| 21/10/2016  | 16:03 | 1.2.3          | Federico Rocca       |Correccion                                               |
+-------------------------------------------------------------+           Se corrije logeo de la función                |
|                                                             | int Log(string Message, int Var, string SecondMessage)  |
+-------------+-------+----------------+----------------------+---------------------------------------------------------+
| 21/10/2016  | 16:38 | 1.3.3          | Federico Rocca       |BugFix                                                   |
+-------------------------------------------------------------+      Se corrije bug, de que cuando no existia el path   |
|                                                             | de logs, lo creaba correctamente, pero en el caso de    |
|                                                             | que existiera, arrojaba error 0xB7                      |
|                                                             | (183 - ERROR_ALREADY_EXISTS), haciendo que salga el     |
|                                                             | programa por error. Ahora se controla esa situacion,    |
|                                                             | haciendo que en el caso de que el path exista, lo tome  |
|                                                             | por valido.                                             |
+-------------+-------+----------------+----------------------+---------------------------------------------------------+
| 21/10/2016  | 16:40 | 1.3.4          | Federico Rocca       |Mejora                                                   |
+-------------------------------------------------------------+      Se mejora funcion de salida en error, mostrando    |
|                                                             | mejor el error por el cual se exitea.                   |
+-------------------------------------------------------------+---------------------------------------------------------+
| 24/10/2016  | 11:30 | 2.0.0          | Federico Rocca       |BugFix                                                   |
+-------------------------------------------------------------+      Se corrije bug, de que cuando no se inicializaba   |
|                                                             | el logger, y se intentaba escribir el log, no daba      |
|                                                             | error alguno, pero tampoco se escribia en el log        |
|                                                             |                                                         |
|                                                             |Mejora                                                   |
|                                                             |      Cambios importantes                                |
|                                                             | * Variable global de inicializacion de archivo          |
|                                                             | * Se mejora el documentado en el archivo fuente,        |
|                                                             | siguiendo un STD para poder asi documentar con eficacia |
|                                                             | * Se modulariza el codigo fuente para dejarlo ordenado  |
|                                                             | * Ahora las funciones de logeo retornan INT, haciendo   |
|                                                             | posible el manejo de errores                            |
|                                                             | * Se agregan nuevos DEFINE, devueltos por las funciones |
|                                                             | de logeo                                                |
+-------------+-------+----------------+----------------------+---------------------------------------------------------+
| 26/10/2016  | 11:24 | 2.0.1          | Federico Rocca       |Mejora                                                   |
+-------------------------------------------------------------+       Se documenta el esquema de versionado a usar      |
|                                                             |                                                         |
|                                                             | Mejora                                                  |
|                                                             |       Las funciones nuevamente devuelven VOID ya que,   |
|                                                             | es mas sencillo verificar el estado de la variable      |
|                                                             | LOG_NOOK y LOG_OK para saber si se puede escribir en el |
|                                                             | archivo, debide a que el stream ostream no devuelve     |
|                                                             | nada pueda o no escribir en el archivo.                 |
|                                                             |                                                         |
|                                                             | El uso de las funciones de logeo deberian ser el        |
|                                                             | siguiente:                                              |
|                                                             | if(Is_Open)                                             |
|                                                             | {                                                       |
|                                                             |      Log("Leyenda...", VariableEjemplo);                |
|                                                             | }                                                       |
+-------------+-------+----------------+----------------------+---------------------------------------------------------+
| 26/10/2016  | 12:20 | 2.1.2          | Federico Rocca       | Mejora                                                  |
+-------------------------------------------------------------+       Se cambia la funcion CreateDir(), que ahora       |
|                                                             | devuelve un bool, para saber si el directorio de logs   |
|                                                             | se pudo crear correctamente.                            |
|                                                             |                                                         |
|                                                             | BugFIX                                                  |
|                                                             | Se modifican los defines LOG_NOOK y LOG_OK, ahora valen |
|                                                             | 0 y 1 respectivamente, para asi poder logear en funcion |
|                                                             | de si el directorio y el archivo fue creado             |
|                                                             | correctamente.                                          |
+-------------+-------+----------------+----------------------+---------------------------------------------------------+
| 21/11/2016  | 16:20 | 2.1.3          | Federico Rocca       | Mejora                                                  |
+-------------------------------------------------------------+       Se agrega funcion de logeo de variable            |
|                                                             | tipo SDL_Surface*                                       |
+-------------+-------+----------------+----------------------+---------------------------------------------------------+
| 30/01/2017  | 16:35 | 2.1.4          | Federico Rocca       | Mejora                                                  |
+-------------------------------------------------------------+       Se agrega logeo de linea punteada al              |
|                                                             | inicializar correctamente el logeo                      |
+-------------+-------+----------------+----------------------+---------------------------------------------------------+
| 02/03/2017  | 15:24 | 2.1.5          | Federico Rocca       | Mejora                                                  |
+-------------------------------------------------------------+       En funcion de logeo, se mejora la creacion de     |
|                                                             | path y archivo de logs. Ahora, se toma el nombre del    |
|                                                             | proceso que se ejecutó para darle el nombre al archivo  |
|                                                             | de log.                                                 |
+-------------+-------+----------------+----------------------+---------------------------------------------------------+
| 02/04/2017  | 19:09 | 2.1.6          | Federico Rocca       | Mejora                                                  |
+-------------------------------------------------------------+        Todos los parametros son ahora const, por lo que |
|                                                             | se mejora la seguridad, ya que no podran ser            |
|                                                             | modificados en ningun aspecto                           |
+-------------+-------+----------------+----------------------+---------------------------------------------------------+
| 02/04/2017  | 19:20 | 2.1.7          | Federico Rocca       | Mejora                                                  |
+-------------------------------------------------------------+        Todos los parametros son ahora const&, por lo    |
|                                                             | que al ser pasados por referencia se mejora la          |
|                                                             | performance y uso de memoria                            |
+-------------+-------+----------------+----------------------+---------------------------------------------------------+
| 16/05/2017  | 12:50 | 2.1.8          | Federico Rocca       | Mejora                                                  |
+-------------------------------------------------------------+        Se eliminan los defines LOG_OK y LOG_NOOK, ya    |
|                                                             | que no estaban siendo implementados                     |
+-------------+-------+----------------+----------------------+---------------------------------------------------------+
/// Devoluciones de funciones de logeo
#define LOG_OK 1
#define LOG_NOOK 0
*/

/** ---------------------------------- Implementaciones a futuro ---------------------------------- **/

/**

    A implementar:
                    -Rotaciones de logs

*/

/** ---------------------------------- Comentarios importantes ---------------------------------- **/



/** ---------------------------------- Licencia ---------------------------------- **/
