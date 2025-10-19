#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

/* definition of a data node for holding student information */
/* definition of a planet for holding planet information  as name and coordinates*/
typedef struct Planet_t
{
   char *name;
   float x, y, z;
}Planet;

/* definition of a origin for holding origin information  as name and planet*/
typedef struct Origin_t{
	Planet *o_planet;
	char *name;
}Origin;

/* definition of a PhysicalCharacteristics for holding PhysicalCharacteristics information as name and value*/
typedef struct PhysicalCharacteristics_t{
	char *name;
	float value;
}Physical_chr;

/* definition of a Jarry for holding Jarry information  as  id, joy, origin, physical Characteristics and num of physical Characteristics*/
typedef struct Jerry_t{
	char *ID;
	int Joy;
	Origin *j_origin;
	Physical_chr **physical_chr;
	int numPhysical;
}Jerry;


/*this function creat jerry and return jerr */
Jerry* createJerry (char * id, int joy, Planet * planet, char * name);
/*this function creat planet and return planet*/
Planet* createPlanet (char * name, float x, float y, float z);
/*this function creat physical Characteristics and return it*/
Physical_chr* createPhysical (char *name, float value);
/*this function creat origin and return it */
Origin* createOrigin (Planet *planet, char* name);
/*this function check if jerry has a specific Physical and return true and false according if succeeded or not*/
bool chackPhysical (Jerry* jerr, char* name);
/*this function add to jerry a specific Physical and return jerry*/
Jerry* addPhysical (Jerry* jerr, Physical_chr * p_c);
/*this function delete to jerry a specific Physical and return if succeeded or not*/
status removePhysical (Jerry* jerr, char* name);
/*this function print jerry and return if succeeded or not*/
status printJerry (Jerry* jerr);
/*this function print planet and return if succeeded or not*/
status printPlanet (Planet* planet);

//Jerry* sadsestJerry()

/*this function delet jerry*/
void deleteJerry(Jerry * jerr);
/*this function delet PhysicalCharacteristics*/
void deletePhysical(Physical_chr* physical);
/*this function delet planet*/
void deletePlanet(Planet * planet);
/*this function delet origin*/
void deleteOrigin(Origin * origin);

