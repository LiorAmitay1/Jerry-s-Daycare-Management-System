#include <stdio.h>
#include <stdlib.h>
#include "Jerry.h"
#include "Defs.h"
//creat jerry with given id, joy, planet and name.
Jerry* createJerry (char * id, int joy, Planet * planet, char * name){
	if (id == NULL || planet == NULL || name == NULL)
	{
		return NULL;
	}
	Jerry * jerry = (Jerry *)malloc(sizeof(Jerry));
	if (jerry == NULL)
	{
		return NULL;
	}
	jerry->ID = (char*)malloc(strlen(id) +1);
	if (jerry->ID == NULL){
		free(jerry);
		return NULL;
	}
	//copy the name to jerry
	strcpy(jerry->ID, id);
	jerry->Joy = joy;
	jerry->j_origin = createOrigin(planet, name);
	//initialize the parameters that didn't get here.
	jerry->physical_chr = NULL;
	jerry->numPhysical = 0;
	return jerry;
}

/*this function creat planet and return planet*/
Planet* createPlanet (char * name, float x, float y, float z){
	if (name == NULL){
		return NULL;
	}
	Planet * planet = (Planet*)malloc(sizeof(Planet));
	if (planet == NULL){
		return NULL;
	}
	planet->name = (char*)malloc(strlen(name) +1);

	if (planet->name == NULL){
		free(planet);
		return NULL;
	}
	strcpy(planet->name, name);
	planet->x = x;
	planet->y = y;
	planet->z = z;
	return planet;
}


/*this function creat physical Characteristics and return it*/
Physical_chr* createPhysical (char *name, float value){
	if (name == NULL){
		return NULL;
	}
	Physical_chr * physical_chr = (Physical_chr*)malloc(sizeof(Physical_chr));
	if (physical_chr ==NULL)
	{
		return NULL;
	}
	physical_chr->name = (char*)malloc(strlen(name) +1);
	if (physical_chr->name == NULL){
		free(physical_chr->name);
		free(physical_chr);
		return NULL;
	}
	strcpy(physical_chr->name,name);
	physical_chr->value = value;
	return physical_chr;
}

/*this function creat origin and return it */
Origin* createOrigin (Planet *planet, char* name){
	if (planet == NULL || name == NULL)
	{
		return NULL;
	}
	Origin * origin = (Origin*)malloc(sizeof(Origin));
	if (origin == NULL)
	{
		free(origin);
		return NULL;
	}
	origin->name = (char*)malloc(strlen(name) +1);
	if (origin->name == NULL){
		free(origin->name);
		free(origin);
		return NULL;
	}
	origin->o_planet = planet;
	strcpy(origin->name, name);
	return origin;
}

/*this function check if jerry has a specific Physical and return true and false according if succeeded or not*/
bool chackPhysical (Jerry* jerr, char* name){
	if (jerr == NULL || name == NULL)
	{
		return false;
	}
	for (int i = 0;i< jerr->numPhysical ;i++)
	{
		Physical_chr* curr = jerr->physical_chr[i];
			if (strcmp(curr->name, name) == 0)
			{
				return true;
			}
	}
	return false;
}

/*this function add to jerry a specific Physical and return jerry*/
Jerry* addPhysical (Jerry* jerr, Physical_chr * p_c){
	if (jerr == NULL || p_c == NULL)
	{
		return NULL;
	}
	// if num == 0 there is no physical_chr so initialize space for it and update.
	if (jerr->numPhysical == 0){
		jerr->physical_chr = (Physical_chr**)malloc(sizeof(Physical_chr *));
		if (jerr->physical_chr == NULL)
		{
			return NULL;
		}
		jerr->physical_chr[0] = p_c;
		jerr->numPhysical = (jerr->numPhysical+1);
	}
	else{
		//change size of space in heap
		jerr->physical_chr = (Physical_chr**)realloc(jerr->physical_chr, (sizeof(Physical_chr *))*(jerr->numPhysical+1));
		if (jerr->physical_chr == NULL)
		{
			return NULL;
		}
		jerr->physical_chr[jerr->numPhysical] = p_c;
		jerr->numPhysical = (jerr->numPhysical + 1);
	}
	return jerr;
}


/*this function delete to jerry a specific Physical and return if succeeded or not*/
status removePhysical (Jerry* jerr, char* name){
	if (jerr == NULL || name == NULL)
	{
		return failure;
	}
	if (jerr->numPhysical == 0)
	{
		return failure;
	}
	//if i have only one
	if (jerr->numPhysical == 1 && (strcmp(jerr->physical_chr[0]->name, name) == 0))
	{
		deletePhysical(jerr->physical_chr[0]);
		free(jerr->physical_chr);
		jerr->physical_chr = NULL;
		jerr->numPhysical = 0;
	}
	else{
		//to keep the physical_cha that i need to remove.
	Physical_chr* to_remove;
	int count_removes = 0;

	for (int i = 0; i< jerr->numPhysical; i++){
			if (strcmp(jerr->physical_chr[i]->name, name) == 0){
				count_removes++;
				to_remove = jerr->physical_chr[i];
				for (int y = i; y< jerr->numPhysical-1;y++)
				{
					jerr->physical_chr[y] = jerr->physical_chr[y+1];
				}
			break;
			}
	}
	deletePhysical(to_remove);
	if (count_removes != 0){
		jerr->numPhysical= (jerr->numPhysical -1);
		//change the size after remove
		jerr->physical_chr = (Physical_chr**)realloc(jerr->physical_chr,(sizeof(Physical_chr *))* (jerr->numPhysical));
	}
	else{ return failure;}
	}
	return success;
}


/*this function print jerry and return if succeeded or not*/
status printJerry (Jerry* jerr){
	if (jerr == NULL)
	{
		return failure;
	}
	printf("Jerry , ID - %s : \n", jerr->ID);
	printf("Happiness level : %d \n", jerr->Joy);
	printf("Origin : %s \n", jerr->j_origin->name);
	printf("Planet : %s (%.2f,%.2f,%.2f) \n", jerr->j_origin->o_planet->name, jerr->j_origin->o_planet->x, jerr->j_origin->o_planet->y,jerr->j_origin->o_planet->z);
	if (jerr->numPhysical != 0)
	{
		printf("Jerry's physical Characteristics available : \n");
		for (int i = 0 ; i<jerr->numPhysical; i++)
		{
			if (i == (jerr->numPhysical -1) && i==0)
			{
				printf("\t%s : %.2f \n", jerr->physical_chr[i]->name, jerr->physical_chr[i]->value);
			}
			else if (i == 0)
			{
				printf("\t%s : %.2f , ", jerr->physical_chr[i]->name, jerr->physical_chr[i]->value);
			}
			else if (i == (jerr->numPhysical -1))
			{
				printf("%s : %.2f \n", jerr->physical_chr[i]->name, jerr->physical_chr[i]->value);
			}
			else
			{
				printf("%s : %.2f , ", jerr->physical_chr[i]->name, jerr->physical_chr[i]->value);
			}
		}
	}
	return success;
}

/*this function print planet and return if succeeded or not*/
status printPlanet (Planet* planet){
	if(planet == NULL){
		return failure;
	}
	printf("Planet : %s (%.2f,%.2f,%.2f) \n", planet->name, planet->x, planet->y, planet->z);
	return success;
	}


/*this function delet origin*/
void deleteOrigin(Origin * origin){
	if(origin != NULL){
		free(origin->name);
		free(origin);
	}
}

/*this function delet planet*/
void deletePlanet(Planet * planet){
	if (planet != NULL){
	free(planet->name);
	free(planet);
	}
}

/*this function delet PhysicalCharacteristics*/
void deletePhysical(Physical_chr* physical){
	if (physical != NULL){
	free(physical->name);
	free(physical);
	}
}

/*this function delet jerry*/
void deleteJerry(Jerry * jerr){
	if (jerr != NULL){
	free(jerr->ID);
	if(jerr->j_origin != NULL){
		deleteOrigin(jerr->j_origin);
	}
	for (int i =0 ; i<jerr->numPhysical;i++){
		deletePhysical(jerr->physical_chr[i]);
	}
	free(jerr->physical_chr);
	free(jerr);
	}
}
