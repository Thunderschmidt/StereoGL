#ifndef INPUT3DO
#define INPUT3DO

class O3D  //Unterobjekt, Teil der Model-Datenstruktur
{
   public:
   ~O3D(){delete n, vert, color, line, i, c;}
   char name[32];   //Name (aus 3do-File)
   int vert_total;  //wieviel Koordinatenpunkte?
   int poly_total;  //wieviel Flächen?
   int line_total;   //wieviel Linien (f. Outlines)
   int sibl_o;	     //Schwesterobjekt
   int child_o;   //Tochterobjekt
   VECTOR pos;      //Offset
   VECTOR *n;       //Zeiger auf Normalvektoren
   VECTOR *vert;    //Zeiger auf Koordinatenpunkte
   char *ind_total;   //Zeiger auf Datenfeld mit der Anzahl der Indizes zum Inhalt
   char *color;     //Zeiger auf Farbinformationen
   short *line;     //Zeiger auf Linien
   short *i;        //Zeiger auf Indizes
   char *c;         //
   bool single_colored; //ist das Objekt einfarbig?
};

class MODEL
{
   public:
   ~MODEL(){delete o3d;}
   int obj_total;               //Anzahl der Objekte (O3D)
   O3D  *o3d;                  //Zeiger auf Unterobjekte
   float size;                 //
   float radius;               //Größter Abstand vom Mittelpunkt
   VECTOR min;                 //der kleinste x, y und z-Wert des Modells
   VECTOR max;                 //der größte x, y und z-Wert des Modells
   const char *name;           //filename des 3dos
};

int lese_3do(MODEL *model, const char datei[]);
#endif
