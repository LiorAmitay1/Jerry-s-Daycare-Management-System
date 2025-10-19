/*
 * JerryBoreeMain.c
 *
 *  Created on: 22 Dec 2022
 *      Author: lior
 */
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "Defs.h"
#include "HashTable.h"
#include "KeyValuePair.h"
#include "LinkedList.h"
#include "MultiValueHashTable.h"
#include "Jerry.h"


/*this functions is for linked list of 	jerries*/
Element copy_LinkedList(Element elem){
	if(elem == NULL){
		return NULL;
	}
	return (LinkedList)elem;

}

status free_LinkedList(Element elem){
	if(elem == NULL){
		return failure;
	}
	deleteJerry((Jerry*)elem);
	return success;
}

status print_LinkedList(Element elem){
	if(elem == NULL){
		return failure;
	}
	printJerry((Jerry*) elem);
	return success;
}

bool equal1_LinkedList(Element elem1, Element elem2){
	if(elem1 == NULL || elem2 == NULL){
		return false;
	}
	Jerry* jerr1 = (Jerry*)elem1;
	Jerry* jerr2 = (Jerry*)elem2;

	if(strcmp(jerr1->ID, jerr2->ID) == 0){
		return true;
	}
	return false;
}

bool equal2_LinkedList(Element elem1, Element elem2){
	if(elem1 == NULL || elem2 == NULL){
		return false;
	}
	char* id1 = (char*) elem2;
	Jerry* j = (Jerry*) elem1;
	if(strcmp(j->ID, id1) == 0){
		return true;
	}
	return false;
}



/*this functions is for hash table*/

Element copykey_hashTable(Element elem){
	if(elem == NULL){
		return NULL;
	}
	return (char*)elem;
}

status freekey_hashTable(Element elem){
	if(elem == NULL){
		return failure;
	}
	return success;
}

status printkey_hashTable(Element elem){
	if(elem == NULL){
		return failure;
	}
	char* s1 = (char*)elem;
	char * new_id = (char*)malloc(strlen(s1)+1);
	if(new_id == NULL){
		return failure;
	}
	strcpy(new_id, s1);
	printf("%s \n", new_id);
	free(new_id);
	return success;
}

Element copyValue_hashTable(Element elem){
	if(elem == NULL){
		return NULL;
	}
	return elem;
}

status freeValue_hashTable(Element elem){
	if(elem == NULL){
		return failure;
	}
	return success;
}

status printValue_hashTable(Element elem){
	if(elem == NULL){
		return failure;
	}
	printJerry((Jerry*) elem);
	return success;
}

bool equalkey_hashTable(Element elem1, Element elem2){
	if(elem1 == NULL || elem2 == NULL){
		return failure;
	}
	char * s1 = (char*)elem1;
	char* s2 = (char*)elem2;
	if (strcmp(s1,s2) == 0)
		return true;
	return false;
}

int transform_hashTable(Element elem){
	const char* new = (char*)elem;
	int sum = 0;
	int i;
	for (i=0;i<strlen(new);i++)
	{
		sum+=(int)new[i];
	}
	return sum;
}


int check_prim(int num){
	int i,m = 0;
	m = num/2;
	for(i = 2 ;i <= m ;i++){
		if(num%i == 0){
			return -1;
		}
	}
	return num;
}

int int_hash(int num_jerries){
	if (num_jerries == 0){
		return 0;
	}
	if (check_prim(num_jerries) == -1){
		for (int i = 0; i< num_jerries; i++){
			if(check_prim(num_jerries +i) != -1){
				return num_jerries+i;
			}
		}
	}
	return 0;
}


/*functions for multihash*/

Element copy_keyMulti(Element name){
	if(name == NULL){
		return NULL;
	}
	char* temp = (char*)name;
	char* new = (char*)malloc(strlen(temp)+1);
	strcpy(new, temp);
	return new;
}

bool equalkey_multiHash(Element elem1, Element elem2){
	if(elem1 == NULL || elem2 == NULL){
		return false;
	}

	char * s1 = (char*)elem1;
	char* s2 = (char*)elem2;
	if (strcmp(s1,s2) == 0){
		return true;
	}
	return false;
}

bool equalvalue_multiHash(Element elem1, Element elem2){
	if(elem1 == NULL || elem2 == NULL){
		return false;
	}
	Jerry* jerr1 = (Jerry*)elem1;
	Jerry* jerr2 = (Jerry*)elem2;

	if(strcmp(jerr1->ID, jerr2->ID) == 0){
		return true;
	}
	return false;
}
//to do deep free for key because was allocated by me
status freeKey_multiHash(Element elem){
	if(elem == NULL){
		return failure;
	}
	free((char*)elem);
	return success;
}
status freeValue_multiHash(Element elem){
	if(elem == NULL){
		return failure;
	}
	return success;
}

status printKey_multiHash(Element elem){
	if(elem == NULL){
		return failure;
	}
	printf("%s : \n", (char*)elem);
	return success;
}


/*this function delete all program if there is problem reading file and create planet*/
void problem_read_planets(Planet ** planetot, int count){
	for(int i =0; i<count;i++){
		deletePlanet(planetot[i]);
	}
}

/*this function delete all the structs*/
void destroy(Planet ** planet_list, int num_planet,hashTable hash_of_jerr,LinkedList linkedlist_of_jerr, MultiValueHashTable multihash_physics_jerry){
	for (int i = 0; i < num_planet; i++){
		deletePlanet(planet_list[i]);
	}
	free(planet_list);
	destroyMultiValueHashTable(multihash_physics_jerry);
	destroyHashTable(hash_of_jerr);
	destroyList(linkedlist_of_jerr);
}



//delete only specific jerry from the system
void deleteJerryFromSystem(Jerry* jerr, hashTable hash, LinkedList linkedlist){
	removeFromHashTable(hash, jerr->ID);
	deleteNode(linkedlist, jerr);
}
//delete jerry from multihash by the specific physical name
void deleteJerryFromMultiHashOnly(Jerry* jerr, MultiValueHashTable multiHash ,char* name_of_physics){
	removeFromMultiValueHashTable(multiHash,name_of_physics, jerr);

}

int main(int argc, char* argv[]){
	int num_planet = atoi(argv[1]);
	//create planet list
	Planet ** list_planet = (Planet **)malloc(sizeof(Planet *)* num_planet);
	if (list_planet == NULL){
		free(list_planet);
		printf("Problem Memory \n");
		exit(1);
	}
	Physical_chr** list_physicsonly;
	hashTable hash_of_jerr;
	LinkedList linkedlist_of_jerr = createLinkedList(copy_LinkedList, free_LinkedList, print_LinkedList,equal1_LinkedList, equal1_LinkedList);
	MultiValueHashTable multihash_physics_jerry = createMultiValueHashTable(copy_keyMulti, freeKey_multiHash, printKey_multiHash, copyValue_hashTable, freeValue_multiHash, printValue_hashTable, equalkey_multiHash, equalvalue_multiHash, transform_hashTable,11);
	FILE* ptr = fopen(argv[2], "r");
	if (ptr == NULL){
		free(list_planet);
		printf("Problem Memory \n");
		exit(1);
	}
	int counter = 0;
	int counter1 = 0;
	int counter2 = 0;
	int countphysic = 0;
	//buffer to read lines.
	char buffer[300];
	char* ch;
	ch = buffer;

	char* planetot[5];
	char * jerr_values[5];
	int num = 0;
	int i = 0;
	int j=0;
	int indx = 0;
	int indx2 = 0;
	//over the file line by line.
	while (fgets(buffer, sizeof(buffer), ptr)){
		char* token = strtok(ch, ",");
		if (counter == 0){
			token = strtok(NULL, ",");
			counter ++;
			continue;
		}
		while (counter >= 1 && counter <= atoi(argv[1])){
			if(token == NULL ){
				token = strtok(NULL, ",");
				break;
			}
			if (num <= 3){
				planetot[i] = token;
				i++;
				num++;
			}
			if (num==4){
				//creating the planets.
				Planet * planet1= createPlanet(planetot[0], atof(planetot[1]), atof(planetot[2]), atof(planetot[3]));
				//if create was not success delete all items and get off the work.
				if(planet1 == NULL){
					printf("Problem Memory \n");
					problem_read_planets(list_planet, counter1);
					free(list_planet);
					exit(1);
				}
				counter1++;
				//add planet to list.
				list_planet[j] = planet1;
				num = 0;
				i = 0;
				j++;
				counter ++;
			}
			token = strtok(NULL, ",");
		}


		if (counter == atoi(argv[1])+1 && token != NULL){
			token = strtok(NULL, ",");
			counter ++;
			continue;
		}

		while (counter > atoi(argv[1])+1 && token != NULL)
		{
			//if its not \t so its jerry , create new one by initialize all the things that builds jerry.
			if (token[0] != 9 && indx < 4){
				jerr_values[indx] = token;
				indx++;
			}
			//creating jerry and put him in the list.
			if (indx == 4){
				for (int x =0 ; x< atoi(argv[1]); x++){
					if (strcmp(list_planet[x]->name, jerr_values[2]) == 0){
						Jerry* new_jerr = createJerry(jerr_values[0], atoi(jerr_values[3]), list_planet[x] , jerr_values[1]);
						if (appendNode(linkedlist_of_jerr, new_jerr) == 1){
							printf("Problem Memory \n");
//							problem_read_jerry(arr_jerr, list_planet, counter2,  num_planet);
							deleteJerry(new_jerr);
							free(list_planet);
							destroyList(linkedlist_of_jerr);
							exit(1);
						}
						indx = 0;
						indx2++;
						counter2++;
					break;}
				}
			}
			//initialize physical characters.
			if (token[0] == 9 && indx <= 4){
				char* small_token = strtok(token, "	:");
				float small_token1 = atof(strtok(NULL, ":"));
				Physical_chr* new_physics = createPhysical(small_token, small_token1);
				countphysic++;

				if (new_physics == NULL)
				{
					printf("Problem Memory \n");
					free(list_planet);
					destroyList(linkedlist_of_jerr);
					exit(1);
				}
				//create physical name list to update the multihash
				if (countphysic == 1){
					list_physicsonly = (Physical_chr**)malloc(sizeof(Physical_chr*));
					list_physicsonly[0] = new_physics;
				}
				else{
					list_physicsonly = (Physical_chr**)realloc(list_physicsonly, sizeof(Physical_chr*)*(countphysic));
					list_physicsonly[countphysic-1] = new_physics;
				}
				//add to jerry
				Jerry* jerry_found = getDataByIndex(linkedlist_of_jerr, indx2);
				addPhysical(jerry_found, new_physics);
				//add to nultuValueHashTable
				addToMultiValueHashTable(multihash_physics_jerry, new_physics->name, jerry_found);
			}
			token = strtok(NULL, ",");
			counter++;
		}
	}
	//create the hash of jerries
	hash_of_jerr = createHashTable(copykey_hashTable, freekey_hashTable, printkey_hashTable, copyValue_hashTable, freeValue_hashTable, printValue_hashTable, equalkey_hashTable, transform_hashTable, 11);
	fclose(ptr);
	for (int a = 1; a<indx2+1; a++){
		Jerry* new_append_hash = (Jerry*) getDataByIndex(linkedlist_of_jerr, a);
		addToHashTable(hash_of_jerr, new_append_hash->ID, new_append_hash);
	}
	//free the list we have created
	free(list_physicsonly);


	int condition =1;

		//starting menu
		while(condition == 1){
			char buffer[200];
		int number;

		printf("Welcome Rick, what are your Jerry's needs today ? \n");
		printf("1 : Take this Jerry away from me \n");
		printf("2 : I think I remember something about my Jerry \n");
		printf("3 : Oh wait. That can't be right \n");
		printf("4 : I guess I will take back my Jerry now \n");
		printf("5 : I can't find my Jerry. Just give me a similar one \n");
		printf("6 : I lost a bet. Give me your saddest Jerry \n");
		printf("7 : Show me what you got \n");
		printf("8 : Let the Jerries play \n");
		printf("9 : I had enough. Close this place \n");
		scanf("%s", buffer);
		number = atoi(buffer);

		if ( number>0 && number <=9){
			switch (number){
			//add new jerry to system
				case 1:;
					printf("What is your Jerry's ID ? \n");
					char  str_from_user[200];
					scanf("%s", str_from_user);
					Jerry* elem = NULL;
					elem = (Jerry*)lookupInHashTable(hash_of_jerr, str_from_user);
					if (elem != NULL){
						printf("Rick did you forgot ? you already left him here ! \n");
						break;
					}
					printf("What planet is your Jerry from ? \n");
					char * str_from_user2;
					scanf("%s", buffer);
					str_from_user2 = buffer;
					Planet* his_planet = NULL;
					for (int i = 0; i< num_planet; i++){
						//if planet exist
						if (strcmp(list_planet[i]->name, str_from_user2) == 0){
							his_planet = list_planet[i];
						}
					}
					if (his_planet == NULL){
						printf("%s is not a known planet ! \n", str_from_user2);
						break;
					}
					printf("What is your Jerry's dimension ? \n");
					char * str_from_user3;
					scanf("%s", buffer);
					str_from_user3 = buffer;

					printf("How happy is your Jerry now ? \n");
					int new_happy;
					scanf("%d", &new_happy);
					Jerry* new_jerry_daycare = createJerry(str_from_user, new_happy, his_planet, str_from_user3);
					if(new_jerry_daycare ==NULL){
						printf("Problem Memory \n");
						destroy(list_planet, num_planet,hash_of_jerr, linkedlist_of_jerr, multihash_physics_jerry);
						break;
					}
					//add to hash of jerry and to the linkedlist
					if (appendNode(linkedlist_of_jerr, new_jerry_daycare) == failure || addToHashTable(hash_of_jerr, new_jerry_daycare->ID, new_jerry_daycare) == failure){
						printf("Problem Memory \n");
						destroy(list_planet, num_planet,hash_of_jerr, linkedlist_of_jerr, multihash_physics_jerry);
						deleteJerry(new_jerry_daycare);
						break;
					}
					printJerry(new_jerry_daycare);
					break;
				//add physical char to the specific jerry
				case 2:;
					printf("What is your Jerry's ID ? \n");
					char * str_from_user4;
					scanf("%s", buffer);
					str_from_user4 = buffer;
					Jerry* jerr_found = (Jerry*)lookupInHashTable(hash_of_jerr, str_from_user4);
					if (jerr_found == NULL){
						printf("Rick this Jerry is not in the daycare ! \n");
						break;
					}
					printf("What physical characteristic can you add to Jerry - %s ? \n", str_from_user4);
					char* given_pc_name;
					scanf("%s", buffer);
					given_pc_name = buffer;

					if(chackPhysical(jerr_found, given_pc_name) == true){
						//if physical chr exist then tell the user
						printf("The information about his %s already available to the daycare ! \n", given_pc_name);
						break;
					}
					//if physical chr not exist then add
					printf("What is the value of his %s ? \n", given_pc_name);
					float new_val;
					scanf("%f", &new_val);
					Physical_chr* new_phy = createPhysical(given_pc_name, new_val);
					if(new_phy == NULL){
						printf("Problem Memory \n");
						destroy(list_planet, num_planet,hash_of_jerr, linkedlist_of_jerr, multihash_physics_jerry);
						break;
					}
					addPhysical(jerr_found, new_phy);
					if(addToMultiValueHashTable(multihash_physics_jerry, given_pc_name, jerr_found) == failure){
						printf("Problem Memory \n");
						destroy(list_planet, num_planet,hash_of_jerr, linkedlist_of_jerr, multihash_physics_jerry);
						break;
					}
					if (displayMultiValueHashElementsByKey(multihash_physics_jerry, given_pc_name) == failure){
						printf("Problem Memory \n");
						destroy(list_planet, num_planet,hash_of_jerr, linkedlist_of_jerr, multihash_physics_jerry);
						break;
					}
					break;

				//delete physical characteristic from Jerry
				case 3:;
					printf("What is your Jerry's ID ? \n");
					char * str_from_user5;
					scanf("%s", buffer);
					str_from_user5 = buffer;
					Jerry* jerr_found1 = lookupInHashTable(hash_of_jerr, str_from_user5);
					if (jerr_found1  == NULL){
						printf("Rick this Jerry is not in the daycare ! \n");
						break;
					}
					printf("What physical characteristic do you want to remove from Jerry - %s ? \n", str_from_user5);
					scanf("%s", buffer);
					char* given_pc_name1 = buffer;
					if(chackPhysical(jerr_found1, given_pc_name1) == true){
						//remove the physical chr
						if(removeFromMultiValueHashTable(multihash_physics_jerry, given_pc_name1, jerr_found1) == failure){
							printf("Problem Memory \n");
							destroy(list_planet, num_planet,hash_of_jerr, linkedlist_of_jerr, multihash_physics_jerry);
							break;
						}
						if(removePhysical(jerr_found1, given_pc_name1) == failure ){
							printf("Problem Memory \n");
							destroy(list_planet, num_planet,hash_of_jerr, linkedlist_of_jerr, multihash_physics_jerry);
							break;
						}

						else{
						printJerry(jerr_found1);
						break;
						}
					}
					else{
						printf("The information about his %s not available to the daycare ! \n", given_pc_name1);
						break;
					}
					break;

				//Remove Jerry from daycare system
				case 4:;
					printf("What is your Jerry's ID ? \n");
					char * str_from_user6;
					scanf("%s", buffer);
					str_from_user6 = buffer;
					Jerry* jerr_found2 = lookupInHashTable(hash_of_jerr, str_from_user6);
					if (jerr_found2 == NULL){
						printf("Rick this Jerry is not in the daycare ! \n");
						break;
					}
					for(int i = 0; i< jerr_found2->numPhysical; i++){
						deleteJerryFromMultiHashOnly(jerr_found2, multihash_physics_jerry, jerr_found2->physical_chr[i]->name);
					}
					deleteJerryFromSystem(jerr_found2, hash_of_jerr, linkedlist_of_jerr);
					printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
					break;


				//Finds similar jerry by physical chr name
				case 5:;
					printf("What do you remember about your Jerry ? \n");
					char * str_from_user7;
					scanf("%s", buffer);
					str_from_user7 = buffer;
					LinkedList list_found = lookupInMultiValueHashTable(multihash_physics_jerry, str_from_user7);
					int num_of_linkedlist = getLengthList(list_found);
					if (num_of_linkedlist == 0){
						printf("Rick we can not help you - we do not know any Jerry's %s ! \n", str_from_user7);
						break;
					}
					printf("What do you remember about the value of his %s ? \n", str_from_user7);
					float given_pc_value3;
					scanf("%f", &given_pc_value3);
					Jerry * jerr;
					Jerry* to_return_currect;
					float num_to_check = 100000;
					for (int i = 1; i <= num_of_linkedlist; i++){
						jerr = getDataByIndex(list_found, i);
						if (jerr == NULL){
							printf("Problem Memory \n");
							destroy(list_planet, num_planet,hash_of_jerr, linkedlist_of_jerr, multihash_physics_jerry);
							break;
						}
						for(int j = 0; j< jerr->numPhysical; j++){
							if(strcmp(jerr->physical_chr[j]->name, str_from_user7) == 0){
								if(fabs(jerr->physical_chr[j]->value - given_pc_value3) < num_to_check){
									num_to_check = jerr->physical_chr[j]->value;
									to_return_currect = jerr;
								}
							}
						}
					}
					printf("Rick this is the most suitable Jerry we found : \n");
					printJerry(to_return_currect);
					for(int i = 0; i< to_return_currect->numPhysical; i++){
						deleteJerryFromMultiHashOnly(to_return_currect, multihash_physics_jerry, to_return_currect->physical_chr[i]->name);
					}
					deleteJerryFromSystem(to_return_currect, hash_of_jerr, linkedlist_of_jerr);
					printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
					break;
					//returns the saddest jerry from he system and delete him
				case 6:;
					int length = getLengthList(linkedlist_of_jerr);
					if (length == 0){
						printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
						break;
					}
					int min = 101;
					Jerry* curr_jerr;
					Jerry* saddest_jerr;
					for(int i = 1; i< length+1;i++){
						curr_jerr = getDataByIndex(linkedlist_of_jerr, i);
						if (curr_jerr->Joy < min){
							min = curr_jerr->Joy;
							saddest_jerr = curr_jerr;
						}
					}
					printf("Rick this is the most suitable Jerry we found : \n");
					printJerry(saddest_jerr);
					//delete jerr from system
					for(int i = 0; i< saddest_jerr->numPhysical; i++){
						deleteJerryFromMultiHashOnly(saddest_jerr, multihash_physics_jerry, saddest_jerr->physical_chr[i]->name);
					}
					deleteJerryFromSystem(saddest_jerr, hash_of_jerr, linkedlist_of_jerr);
					printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
					break;
				//get information about the existing jerries
				case 7:;
					char buffer[300];
					int number_small_switch;

					printf("What information do you want to know ? \n");
					printf("1 : All Jerries \n");
					printf("2 : All Jerries by physical characteristics \n");
					printf("3 : All known planets \n");
					scanf("%s", buffer);
					number_small_switch = atoi(buffer);

					if ( number_small_switch>0 && number_small_switch <=3){
						switch (number_small_switch){
						//all jerries
						case 1:;
							int length = getLengthList(linkedlist_of_jerr);
							if (length == 0){
								printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
								break;
							}
							displayList(linkedlist_of_jerr);
							break;
							//all jerries with ths given physical chr
						case 2:;
							printf("What physical characteristics ? \n");
							char buffer[300];
							char * str_from_user;
							scanf("%s", buffer);
							str_from_user = buffer;
							LinkedList list_phy_jerr = lookupInMultiValueHashTable(multihash_physics_jerry, str_from_user);
							if (list_phy_jerr == NULL){
								printf("Rick we can not help you - we do not know any Jerry's %s ! \n", str_from_user);
								break;
							}
							printf("%s : \n", str_from_user);
							if(displayList(list_phy_jerr) == failure){
								printf("Memory Problem");
								destroy(list_planet, num_planet,hash_of_jerr, linkedlist_of_jerr, multihash_physics_jerry);
								break;

							}break;

						case 3:;
							//print all the planets
							for (int y = 0 ;  y < atoi(argv[1]); y++){
								printPlanet(list_planet[y]);
							}
							break;
						}
						break;
					}
					else{
						printf("Rick this option is not known to the daycare ! \n");
						break;
					}
					//raise / decrease the happy of jerries
				case 8:;
					int length1 = getLengthList(linkedlist_of_jerr);
					if (length1 == 0){
						printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
						break;
					}
					else{
						char buffer[300];
						int number_small_switch;

						printf("What activity do you want the Jerries to partake in ? \n");
						printf("1 : Interact with fake Beth \n");
						printf("2 : Play golf \n");
						printf("3 : Adjust the picture settings on the TV \n");
						scanf("%s", buffer);
						number_small_switch = atoi(buffer);

						if ( number_small_switch>0 && number_small_switch <=3){
							switch (number_small_switch){
							case 1:;
								for(int i = 1; i< length1+1;i++){
									curr_jerr = getDataByIndex(linkedlist_of_jerr, i);
									if (curr_jerr->Joy >=20 && curr_jerr->Joy <=85){
										curr_jerr->Joy = curr_jerr->Joy + 15;
									}
									else if (curr_jerr->Joy >=20 && curr_jerr->Joy >85){
										curr_jerr->Joy = 100;
									}
									else if (curr_jerr->Joy <20 && curr_jerr->Joy >5){
										curr_jerr->Joy = curr_jerr->Joy - 5;
									}
									else{
										curr_jerr->Joy = 0;
									}
								}
								printf("The activity is now over ! \n");
								displayList(linkedlist_of_jerr);
								break;
							case 2:;
								for(int i = 1; i< length1+1;i++){
									curr_jerr = getDataByIndex(linkedlist_of_jerr, i);
									if (curr_jerr->Joy >=50 && curr_jerr->Joy <=90){
										curr_jerr->Joy = curr_jerr->Joy + 10;
									}
									else if (curr_jerr->Joy >=50 && curr_jerr->Joy >90){
										curr_jerr->Joy = 100;
									}
									else if (curr_jerr->Joy <50 && curr_jerr->Joy >=10){
										curr_jerr->Joy = curr_jerr->Joy - 10;
									}
									else{
										curr_jerr->Joy = 0;
									}
								}
								printf("The activity is now over ! \n");
								displayList(linkedlist_of_jerr);
								break;
							case 3:;
								for(int i = 1; i< length1+1;i++){
									curr_jerr = getDataByIndex(linkedlist_of_jerr, i);
									if (curr_jerr->Joy <=80){
										curr_jerr->Joy = curr_jerr->Joy + 20;
									}
									else if (curr_jerr->Joy >80){
										curr_jerr->Joy = 100;
									}
								}
								printf("The activity is now over ! \n");
								displayList(linkedlist_of_jerr);
								break;
							}
						}
						else{
							printf("Rick this option is not known to the daycare ! \n");
							break;
						}

						}
						break;
				//delete all system
				case 9:;
					destroy(list_planet, num_planet,hash_of_jerr, linkedlist_of_jerr, multihash_physics_jerry);
					printf("The daycare is now clean and close ! \n");
					condition ++;
					break;
			}
		}

		else{
			printf("Rick this option is not known to the daycare ! \n");
		}
	}
}

