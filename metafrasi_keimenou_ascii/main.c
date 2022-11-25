/*Translate.c 
Vasileiadis Georgios
csd3918 */ 

#include <stdio.h>
#include <stdlib.h>


/*A function to print the chatacters in greeklish*/
void chartoprint(char *letter){
	while(*letter) {
    	putchar(*letter);
     	letter++;
  	}
}
/*Creates a self-made map in order to match it to the iso system for the characters*/
void charmap(char* letters[]){

	letters[0]= "A"; /*193 - 209*/
	letters[1]= "V";
	letters[2]= "G";
	letters[3]= "D";
	letters[4]= "E";
	letters[5]= "Z";
	letters[6]= "H";
	letters[7]= "8";
	letters[8]= "I";
	letters[9]= "K";
	letters[10]= "L";
	letters[11]= "M"; /*204change state to B*/
	letters[12]= "N"; /*205change state to D*/
	letters[13]= "KS";
	letters[14]= "O";
	letters[15]= "P";
	letters[16]= "R";	/*209*/
	letters[17]= "S";	/*211*/
	letters[18]= "T";
	letters[19]= "Y";
	letters[20]= "F";
	letters[21]= "X";
	letters[22]= "PS";
	letters[23] = "W"; /*217*/
	letters[24]= "a"; /*225 - 249*/
	letters[25]= "v";
	letters[26]= "g";
	letters[27]= "d";
	letters[28]= "e";
	letters[29]= "z";
	letters[30]= "h";
	letters[31]= "8";
	letters[32]= "i";
	letters[33]= "k";
	letters[34]= "l";
	letters[35]= "m"; /* change state to b*/
	letters[36]= "n"; /*change state to d*/
	letters[37]= "ks";
	letters[38]= "o";
	letters[39]= "p";
	letters[40]= "r";
	letters[41]= "s";
	letters[42] = "s";
	letters[43]= "t";
	letters[44]= "y";
	letters[45]= "f";
	letters[46]= "x";
	letters[47]= "ps";
	letters[48] = "w";
	letters[49] = "'A";
	letters[50] = "'E";
	letters[51]= "'H";
	letters[52]= "'I";
	letters[53]= "'O";
	letters[54] = "'W";
	letters[55]= "'Y";
	letters[56] = "a'";
	letters[57] = "e'";
	letters[58] = "h'";
	letters[59] = "i'";
	letters[60] =  "o'";
	letters[61] = "w'";
	letters[62] = "y'";
	letters[63]="i\"";
	letters[64]= "y\"";
	letters[65]= "i'\"";
	letters[66]= "y'\"";
}

/*
	 it is the ascii code for the letter we refer to
	and returns the position of the table the character will be translated to
	or -1 if it does not need translation
*/
int findChar(int i){
	if(i>=193 && i<=209)
	{ /* first 17 capital letters*/
		return i-193 ;
	}
	else if(i>=211 && i<=217)
	{ /*rest capital letters*/
		return i-194;
	}
	else if(i>=225 && i<=249)
	{ /*peza*/
		return i-201;
	}
	else if(i>=220 && i<=223)
	{ /*tonismena peza*/
		return i-164;
	}
	else
	{
		switch(i) /*random ascii*/
		{
			case 182:
				return 49;
				break;
			case 184:
				return 50;
				break;
			case 185:
				return 51;
				break;
			case 186:
				return 52;
				break;
			case 188:
				return 53;
				break;
			case 191:
				return 54;
				break;
			case 190:
				return 55;
				break;
				
			case 252:
			 	return 60;
				break;
			case 254:
				return 61;
				break;
			case 253:
				return 62;
				break;
			case 250:
				return 63;
				break;
			case 251:
				return 64;
				break;
			case 192:
			 	return 65;
				break;
			case 224:
				return 66;
				break;
			default:
				return -1; /* not to be changed */
		}
	}
	return 0;
}


/*Main method */

int main()
{
	enum State {dflt,b,B,d,D};
	enum State state;
	char * array[67];
	int c;

	state =dflt;

	charmap(array);

	while((c=getchar()) != EOF)
	{
		char* toprint;

		if(c<32) continue;/*Prin apo to 32 den exei kati sto iso*/


		if(findChar(c)!= -1)
			{
				toprint = array[findChar(c)];
			}
		else
		  {
				toprint =(char*) malloc(sizeof(char));
				*toprint = c;
			}

		/*Special cases*/
		switch(state)
			{
				case b:
					/* P_greek or p_greek */
					if((c==240 || c==208))
						{
							toprint = "b";
						}
					else
						{
							chartoprint("m");
						}
					break;
				case B:
					/* P_greek or p_greek*/
					if((c==240 || c==208))
						{
							toprint = "B";
						}
					else
						{
							 chartoprint("M");
						}
					break;

	 			case d:
				    /* T_greek or t_greek*/
					if((c==244 || c==212))
						{
							toprint = "d";
						}
					else
						{
						 chartoprint("n");
					 	}
					break;
				case D:
				 	/* T_greek or t_greek*/
					if((c==244) || (c==212))
						{
							toprint = "D";
						}
					else
						{
							chartoprint("N");
						}
					break;
				case dflt:
					break;
			}

		state = dflt;

		switch(c)
			{
				case 204:
					state = B;
					continue;
				case 205:
					state = D;
					continue;
				case 236:
					state = b;
					continue;
				case 237:
					state = d;
					continue;
			}

			chartoprint(toprint);
	}
	return 0;
}
