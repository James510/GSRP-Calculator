#include<iostream>
#include<time.h>
#include<fstream>
#include<stdlib.h>
#include<math.h>
#include <sstream>

using namespace std;

void economyCalc();
void declareEconomy(double[],double,double);
void importEconomy(double[]);
void attackRoller();
void declareShips (int[],int,int[],int);
void importShips (int[],int&,int[],int&);
void systemGen();
string nameGen(bool);
void planetGen();
void firstTimeInstallation();
void errorCheck(int&);
void errorCheck(char&,char,char);
void exitProg();

void resetAll();


int main()
{
	int ch;
	firstTimeInstallation();
	srand(time(NULL));
	while(true)
	{
		cout << "\n------------------------------------"	
			 << "\nGalactic Nations RP Calculators V0.8"
			 << "\n1) Economy Calculator"
			 << "\n2) Battle Calculator"
			 << "\n3) System Generator"
			 << "\n4) Reset All Data"
			 << "\n5) Exit"
			 << "\n\nPlease Make Your Selection :: ";
		cin >> ch;
		cout << "\n------------------------------------";
		if(cin.fail())
			errorCheck(ch);
		if(ch == 1)
			economyCalc();
		else if (ch == 2)
			attackRoller();
		else if (ch == 3)
			systemGen();
		else if (ch == 4)
			resetAll();
		else if (ch == 5)
			exitProg();
		else
			cout << "Not a Valid Choice";
	}
    return 0;
}

void economyCalc()
{
	int ch;
	double economy[2];
	double pp, gs, pop,mod,cur,conv;
	ofstream outEconomy;
	ifstream inEconomy;
	outEconomy.open("EconomyLog.txt",ios::app);
	importEconomy(economy);
	while(true)
	{
		cout << "\n1) Economy Calculator"
			 << "\n2) Manage Balance"
			 << "\n3) Show Balance"
		   	 << "\n4) Currency Conversion"
			 << "\n5) Exit"
			 << "\n\nPlease Make Your Selection :: ";
		cin >> ch;
		cout << "\n------------------------------------";
		if(ch == 1)
		{
			cout << "Enter Your Current Population (Billions) :: ";
			cin >> pop;
			cout << "Enter your modifier (Default is 10) :: ";
			cin >> mod;
			pp = (pop * mod) + economy[0];
			cout << "You have " << pp << " Project Points this cycle"<<endl;
			gs = ((pop * 10) / 2) + economy[1];
			cout << "You have " << gs << " Galactic Standard this cycle"<<endl;
			declareEconomy(economy,pp,gs);
			importEconomy(economy);
		}
		else if (ch == 2)
		{
			cout << "Change PP by :: ";
			cin >> pp;
			cout << "Change GS by :: ";
			cin >> gs;
			pp += economy[0];
			gs += economy[1];
			declareEconomy(economy,pp,gs);
			importEconomy(economy);
		}
		else if (ch == 3)
		{
			cout << "\nYou have " << economy [0] << " Project Points."
				 << "\nYou have " << economy [1] << " Galactic Standard.";
		}
		else if (ch == 4)
		{
			cout << "Enter how many GS you have :: ";
			cin >> gs;
			cout << "Enter how many GS = one of your race's currency :: ";
			cin >> cur;
			conv = gs * cur;
			cout << "Your " << gs << " Galactic Standard converts to " << conv << "Local Currency.";
		}
		else if (ch == 5)
		{
			break;
		}
		else
		{
			cout << "Not a Valid Choice";
		}
	}
}

void declareEconomy(double ecoList[],double pp, double gs)
{
	ofstream outEco;
	outEco.open("EconomyLog.txt");
	outEco << pp << " " << gs;
}

void importEconomy(double ecoList[])
{
    double num = 0;
	int i = 0;
	ifstream inEco;
	inEco.open("EconomyLog.txt");
	while(!inEco.eof())
	{
		inEco >> num;
		ecoList[i] = num;
		i++;
	}
}

void attackRoller()
{
	int acc,dmg,eva,def,accroll,dmgroll,evaroll,defroll,shp1,shp2,hp,redShipDec,blueShipDec,shpHp,shpPtr,redNum,blueNum;
    int redList[100],blueList[100];
    char ans,ship,att;
    for(int i =0;i<100;i++)
		redList[i] = 0;
	for(int i =0;i<100;i++)
		blueList[i] = 0;
    ofstream outLog,outRedShips,outBlueShips;
    ifstream inLog,inRedShips,inBlueShips;
    
	cout << "Input New Ships?(Y/N)";
    cin >> ans;
    if(ans == 'Y'||ans == 'y')
    {
    	outRedShips.open("RedList.txt");
    	outBlueShips.open("BlueList.txt");
    	inRedShips.open("RedList.txt");
    	inBlueShips.open("BlueList.txt");
    	
        cout << "\nInputting Ships";
        redNum = 0;
        blueNum = 0;
        redShipDec = 0;
        blueShipDec = 0;
        do
        {
        	do
         	{
             cout << "\nRed or Blue Ship (r/b):: ";
             cin >> ship;
             if(ship != 'r'&&ship != 'b')
				 cout << "\nNot valid.";
		 	}while(ship != 'r'&&ship != 'b');
		 	cout << "\nShip HP :: ";
		 	cin >> hp;
		 	if(ship == 'r')
		 	{
		 		redShipDec++;
		 		redList[redShipDec-1]=hp;
		 		redNum++;
		 	}
         	if(ship == 'b')
         	{
         		blueShipDec++;
         		blueList[blueShipDec-1]=hp;
         		blueNum++;
		 	}
		 	cout << "Would you like to add another ship :: ";
		 	cin >> ans;
		}while(ans == 'Y'||ans == 'y');     
		declareShips(redList,redNum,blueList,blueNum);
	}
	cout << "Import existing ship file?(Y/N) :: ";
	cin >> ans;
	if(ans=='Y'||ans=='y')
	{
		importShips(redList,redNum,blueList,blueNum);
	}
	//cout << endl;//debug
	//for(int i =0;i<100;i++)//debug
		//cout << redList[i] << " ";//debug

    do
    {
		 outLog.open("BattleLog.txt",ios::app);
         cout << "\nRed or Blue Ship (r/b):: ";
     	 cin >> ship;
         if(ship != 'r'&&ship != 'b')
         	errorCheck(ship,'r','b');
		 cout << "\nNumber of Attacking Ship :: ";
		 cin >> shp1;
		 if(cin.fail())
			errorCheck(shp1);
         cout << "\nAttack or Retaliates (a/r):: ";
         cin >> att;
		 if(att != 'a'&&att != 'r')
         	errorCheck(att,'a','r');
         cout << "\nNumber of Defending Ship :: ";
		 cin >> shp2;
		 if(cin.fail())
			errorCheck(shp2);
         cout << "\nAttacking Accuracy Mod :: ";
         cin >> acc;
         if(cin.fail())
			errorCheck(acc);
         cout << "\nAttacking Damage Mod :: ";
         cin >> dmg;
         if(cin.fail())
			errorCheck(dmg);
         cout << "\nDefending Evasion Mod :: ";
         cin >> eva;
         if(cin.fail())
			errorCheck(eva);
         cout << "\nDefending Defense Mod :: ";
         cin >> def;
         if(cin.fail())
			errorCheck(def);
			
         accroll = rand()%20+acc;
         if(accroll<0)
			accroll = 0;
         dmgroll = rand()%20+dmg+1;
		 if(dmgroll<0)
			dmgroll = 0;
         evaroll = rand()%20+eva+1;
         if(evaroll<0)
			evaroll = 0;
         defroll = rand()%20+def+1;
         if(defroll<0)
			defroll = 0;
         
         outLog << "\n----------------------";
         if(ship == 'r')
         {
             outLog << "\nRed Ship " << shp1;
             if(att == 'a')
				 outLog << " Attacks Blue Ship "<< shp2;
 			 else
				 outLog << " Retaliates At Blue Ship "<< shp2;
		 }
		 else
		 {
			 outLog << "\nBlue Ship " << shp1;
			 if(att == 'a')
				 outLog << " Attacks Red Ship "<< shp2;
 			 else
				 outLog << " Retaliates At Red Ship "<< shp2;
		 }
             
         outLog << "\nAccuracy Roll : " << accroll;
         outLog << "\nEvasion Roll : " << evaroll;
         outLog << "\nDamage Roll : " << dmgroll;
         outLog << "\nDefense Roll : " << defroll;
         
         cout << "\nAccuracy roll was " << accroll << ", Evasion roll was " << evaroll;
         if(accroll > evaroll)
         {
			cout << "\nAccuracy Roll Successful";
			cout << "\nAttack roll was " << dmgroll << ", Defense roll was " << defroll;
			if(dmgroll>defroll)
			{
                cout << "\nThe amount of damage inflicted was :: " << dmgroll - defroll;
                outLog << "\nDamage Inflicted : " << dmgroll - defroll;
                if(ship == 'r')
                {
                	blueList[shp2-1] = dmgroll - defroll;
                	cout << "\nBlue Ship " << shp2 << "'s HP is " << blueList[shp2-1] << " ";
                	declareShips(redList,redNum,blueList,blueNum);
				}
				else
				{
					redList[shp1-1] = dmgroll - defroll;
                	cout << "Red Ship " << shp1 << "'s HP is " << redList[shp1-1] << " ";
                	declareShips(redList,redNum,blueList,blueNum);
				}
			}
			else
			{
                cout << "\nThe amount of damage inflicted was :: 1";
                outLog << "\nThe amount of damage inflicted was : 1";
                if(ship == 'r')
                {
                	blueList[shp2-1]--;
                	cout << "\nBlue Ship " << shp2 << "'s HP is " << blueList[shp2-1] << " ";
                	declareShips(redList,redNum,blueList,blueNum);
				}
				else
				{
					redList[shp1-1]--;
                	cout << "Red Ship " << shp1 << "'s HP is " << redList[shp1-1] << " ";
                	declareShips(redList,redNum,blueList,blueNum);
				}
			}
         }
         else
         {
            cout << "\nAccuracy Roll Failed";
            outLog << "\nAccuracy Roll Failed";
		 }
		 outLog.close();
   	     cout << "\nReroll?(Y/N) :: ";
		 cin >> ans;
    }while(ans =='y'||ans=='Y');
}

void declareShips(int redShips[],int redNum, int blueShips[],int blueNum)
{
	ofstream outRedShips,outBlueShips;

    outRedShips.open("RedList.txt");
    outBlueShips.open("BlueList.txt");

	for(int i=1;i<=redNum;i++)
		outRedShips << i << " "<< redShips[i-1] << " ";
	for(int i=1;i<=blueNum;i++)
		outBlueShips << i << " "<< blueShips[i-1] << " ";

}

void importShips (int redShips[],int &redNum,int blueShips[],int &blueNum)
{
	int num = 0;
	int i = 0;
    ifstream inRedShips,inBlueShips;
    inRedShips.open("RedList.txt");
    inBlueShips.open("BlueList.txt");
    while(!inRedShips.eof())
    {
    	inRedShips >> num;
    	inRedShips >> num;
    	//cout << num << " ";//debug
    	redShips[i] = num;
    	//cout << "|"<<redShips[i]<<"|"; //debug
    	i++;
    	redNum++;

	}
	i = 0;
	while(!inBlueShips.eof())
    {
    	inBlueShips >> num;
    	inBlueShips >> num;
    	//cout << num << " ";//debug
    	blueShips[i] = num;
    	//cout << "|"<<blueShips[i]<<"|"; //debug
    	i++;
    	blueNum++;
	}
}

void systemGen()
{
	int miningCoeff,habitCoeff,planets,habitRoll,habitLimit,planet,gasRoll,moons;
	double planetMass,gasMax,r;
	string name;
	habitLimit = 9;
	gasMax = 1000;
	ofstream outSys;
	outSys.open("SystemGen.txt");
	name = nameGen(true);
	cout << "\nGenerating a system"
		 << "\nThe System of " << name;
	outSys << "\nThe System of " << name;
	planets = rand()%9+3;
	cout << "\nThere are " << planets << " planets in this system"<<endl;
	outSys << "There are " << planets << " planets in this system";
	for(int i=1;i<=planets;i++)
	{
		habitRoll = rand()%planets+1;
		miningCoeff = rand()%10;
		gasRoll = rand()%4;
		if(habitRoll == 1 && habitLimit > 0)
		{
            habitCoeff = rand()%habitLimit+1;
            planetMass = rand()%2+0.5;
            moons = rand()%2;
            cout << "\nPlanet " << i << ", " << nameGen(false)<< ", is a habitable planet"
				 << "\nThe Habitable Coefficient is " << habitCoeff
				 << "\nThe Mining Coefficient is " << miningCoeff
				 << "\nThe Mass is " << planetMass << " Earths"
				 << "\nThere are " << moons << " moon(s) of interest." << endl;
    		outSys << "\nPlanet " << i << " is a habitable planet"
				 << "\nThe Habitable Coefficient is " << habitCoeff
				 << "\nThe Mining Coefficient is " << miningCoeff
				 << "\nThe Mass is " << planetMass << " Earths"
				 << "\nThere are " << moons << " moon(s) of interest." << endl;
			planetGen();
			habitLimit -= habitCoeff;
		}
		else if (gasRoll == 1)
		{
            r = ((double)(rand()%101) / 100);
            planetMass = 8 * (exp (r * (log (gasMax / 8))));
            moons = rand()%10 + (int)(planetMass / 100);
            cout << "\nPlanet " << i << " is a uninhabitable gas planet"
				 << "\nThe Mining Coefficient is " << miningCoeff
				 << "\nThe Mass is " << planetMass << " Earths"
				 << "\nThere are " << moons << " moon(s) of interest." << endl;
			outSys << "\nPlanet " << i << " is a uninhabitable gas planet"
				   << "\nThe Mining Coefficient is " << miningCoeff
				   << "\nThe Mass is " << planetMass << " Earths"
				   << "\nThere are " << moons << " moon(s) of interest." << endl;
		}
		else
		{
            moons = rand()%2;
            planetMass = rand()%10+0.1;
            cout << "\nPlanet " << i << " is a uninhabitable rocky planet"
				 << "\nThe Mining Coefficient is " << miningCoeff
				 << "\nThe Mass is " << planetMass << " Earths"
				 << "\nThere are " << moons << " moon(s) of interest." << endl;
			outSys << "\nPlanet " << i << " is a uninhabitable rocky planet"
				   << "\nThe Mining Coefficient is " << miningCoeff
				   << "\nThe Mass is " << planetMass << " Earths"
				   << "\nThere are " << moons << " moon(s) of interest." << endl;
		}
	}
}

string nameGen(bool numeral)
{
	int rand1,randRun;
	char randFirst,randLet;
	string name;
	stringstream ss;
	randRun = rand()%5+2;
	randFirst = rand()%25+65;
	ss << randFirst;
	ss >> name;
	for(int i=0;i<randRun;i++)
	{
		
        rand1= rand()%6;
        if(rand1==0)
            name.append("a");
        else if(rand1==1)
            name.append("e");
        else if(rand1==2)
            name.append("i");
        else if(rand1==3)
            name.append("o");
        else if(rand1==4)
            name.append("u");
		else
		{
            randLet = rand()%25+97;
            name.append(1,randLet);
		}
	}
	if(numeral)
	{
        rand1= rand()%10;
    	if(rand1==0)
        name.append(" I ");
    	if(rand1==1)
        name.append(" II ");
    	if(rand1==2)
        name.append(" III ");
    	if(rand1==3)
        name.append(" IV ");
    	if(rand1==4)
        name.append(" V ");
	}
	//cout << name;//debug
	return name;
}

void planetGen()
{
	int rand1,rand2,rand3;
    ofstream outSys;
	outSys.open("SystemGen.txt",ios::app);
	cout << "This planet ";
	rand1 = rand()% 12;//terrain
	rand2 = rand()% 12;//population
	rand3 = rand()% 16;//environment
	if(rand1==0)
	{
		cout << "is barren, ";
		outSys << "is barren, ";
	}
	else if(rand1==1)
	{
		cout << "is aquatic, ";
		outSys << "is aquatic, ";
	}
	else if(rand1==2)
	{
		cout << "is volcanic, ";
		outSys << "is volcanic, ";
	}
	else if(rand1==3)
	{
		cout << "is covered in forests, ";
		outSys << "is covered in forests, ";
	}
	else if(rand1==4)
	{
		cout << "is covered in plains, ";
		outSys << "is covered in plains, ";
	}
	else if(rand1==5)
	{
		cout << "is covered in snow, ";
		outSys << "is covered in snow, ";
	}
	else if(rand1==6)
	{
		cout << "is a tundra, ";
		outSys << "is a tundra, ";
	}
	else if(rand1==7)
	{
		cout << "is an artificial planet, ";
		outSys << "is an artificial planet, ";
	}
	else if(rand1==8)
	{
		cout << "is radioactive, ";
		outSys << "is radioactive, ";
	}
	else if(rand1==9)
	{
		cout << "is covered in archipelagos, ";
		outSys << "is covered in archipelagos, ";
	}
	else if (rand1==10)
	{
        cout << "is covered in jungles, ";
		outSys << "is covered in jungles, ";
	}
	else if (rand1==11)
	{
        cout << "has massive continents, ";
		outSys << "has massive continents, ";
	}
	////
	if(rand2==0)
	{
		cout << "populated by giant man eating arachnids, ";
		outSys << "populated by giant man eating arachnids, ";
	}
	else if(rand2==1)
	{
		cout << "populated by giant man eating insects, ";
		outSys << "populated by giant man eating insects, ";
	}
	else if(rand2==2)
	{
		cout << "populated by voracious man eating plants, ";
		outSys << "populated by voracious man eating plants, ";
	}
	else if(rand2==3)
	{
		cout << "populated by various plant life, ";
		outSys << "populated by various plant life, ";
	}
	else if(rand2==4)
	{
		cout << "populated heavily by microbial life, ";
		outSys << "populated heavily by microbial life, ";
	}
	else if(rand2==5)
	{
		cout << "populated by simple land creatures, ";
		outSys << "populated by simple land creatures, ";
	}
	else if(rand2==6)
	{
		cout << "populated by archaic cave-dwelling bi-pedals, ";
		outSys << "populated by archaic cave-dwelling bi-pedals, ";
	}
	else if(rand2==7)
	{
		cout << "populated by industrial era intellectuals, ";
		outSys << "populated by industrial era intellectuals, ";
	}
	else if(rand2==8)
	{
		cout << "populated by fungi, ";
		outSys << "populated by fungi, ";
	}
	else if(rand2==9)
	{
		cout << "populated with self-replicating nano-machines, ";
		outSys << "populated with self-replicating nano-machines, ";
	}
	else if(rand2==10)
	{
		cout << "populated with interstellar space pirates, ";
		outSys << "populated with interstellar space pirates, ";
	}
    else if(rand2==11)
	{
		cout << "populated by flying creatuers, ";
		outSys << "populated by flying creatuers, ";
	}
	////
	if(rand3==0)
	{
		cout << "and experiences fierce storms." << endl;
		outSys << "and experiences fierce storms." << endl;
	}
	else if(rand3==1)
	{
		cout << "and experiences infrequent asteroid bombardment." << endl;
		outSys << "and experiences infrequent asteroid bombardment." << endl;
	}
	else if(rand3==2)
	{
		cout << "and experiences a short day cycle." << endl;
		outSys << "and experiences a short day cycle." << endl;
	}
	else if(rand3==3)
	{
		cout << "and experiences a long day cycle." << endl;
		outSys << "and experiences a long day cycle." << endl;
	}
	else if(rand3==4)
	{
		cout << "and has mind-altering chemicals in the air." << endl;
		outSys << "and has mind-altering chemicals in the air." << endl;
	}
	else if(rand3==5)
	{
		cout << "and has mild seasons." << endl;
		outSys << "and has mild seasons." << endl;
	}
	else if(rand3==6)
	{
		cout << "and experiences large tsunamis." << endl;
		outSys << "and experiences large tsunamis." << endl;
	}
	else if(rand3==7)
	{
		cout << "and has an altar to the precursors." << endl;
		outSys << "and has an altar to the precursors." << endl;
	}
	else if(rand3==8)
	{
		cout << "and has ruins of a great civilization." << endl;
		outSys << "and has ruins of a great civilization." << endl;
	}
	else if(rand3==9)
	{
		cout << "and has an automated self defense network." << endl;
		outSys << "and has an automated self defense network." << endl;
	}
	else if(rand3==10)
	{
		cout << "and has unusually low gravity." << endl;
		outSys << "and has unusually low gravity." << endl;
	}
	else if(rand3==11)
	{
		cout << "and has unusually high gravity." << endl;
		outSys << "and has unusually high gravity." << endl;
	}
	else if(rand3==12)
	{
		cout << "and is fairly normal." << endl;
		outSys << "and is fairly normal." << endl;
	}
	else if(rand3==12)
	{
		cout << "and gives you an uneasy feeling." << endl;
		outSys << "and gives you an uneasy feeling." << endl;
	}
	else if(rand3==13)
	{
		cout << "and experiences heavy seismic activity." << endl;
		outSys << "and experiences heavy seismic activity." << endl;
	}
	else if(rand3==14)
	{
		cout << "and shows signs of a massive battle on the surface." << endl;
		outSys << "and shows signs of a massive battle on the surface." << endl;
	}
	else if(rand3==15)
	{
		cout << "and gives you an extremely uneasy feeling. A feeling like you should leave immediately. You can feel your sins weighing you down, almost crushing you into sub-atomic particles. You try to scream but you can't." << endl;
		outSys << "and gives you an extremely uneasy feeling. A feeling like you should leave immediately. You can feel your sins weighing you down, almost crushing you into sub-atomic particles. You try to scream but you can't." << endl;
		rand1 = rand()%10000; //roll every day that someone is on this planet
		if(rand1==1)
		{
			cout << "\n A tear in the fabric of reality opens a gate to a parallel universe. The forerunners have come. Giant beasts made from pure anti-matter claw their way out of the gate and streak towards your ship. Fortunately, since they are made of anti-matter, they disentegrate immediately upon entering our reality. Unfortunately, this results in a massive explosion that sends a shockwave throughout all known space, destroying everything in the system, as well as the fact that all planets lose 1 habitability and 1 mining coefficient. If a rocky or habital planet's mining coefficient goes to -1, it explodes violently, as well as if a habital planet's habitability goes down to 0.";
			outSys << "\n A tear in the fabric of reality opens a gate to a parallel universe. The forerunners have come. Giant beasts made from pure anti-matter claw their way out of the gate and streak towards your ship. Fortunately, since they are made of anti-matter, they disentegrate immediately upon entering our reality. Unfortunately, this results in a massive explosion that sends a shockwave throughout all known space, destroying everything in the system, as well as the fact that all planets lose 1 habitability and 1 mining coefficient. If a rocky or habital planet's mining coefficient goes to -1, it explodes violently, as well as if a habital planet's habitability goes down to 0.";
		}
	}
}

void firstTimeInstallation()
{
 	ofstream outLog,outRedShips,outBlueShips,outEconomy,outSystem;
    ifstream inLog,inRedShips,inBlueShips,inEconomy,inSystem;
    
	inLog.open("BattleLog.txt");
    if(inLog.fail())
        outLog.open("BattleLog.txt");
    inRedShips.open("RedList.txt");
    if(inRedShips.fail())
        outRedShips.open("RedList.txt");
    inBlueShips.open("BlueList.txt");
    if(inBlueShips.fail())
        outBlueShips.open("BlueList.txt");
    inEconomy.open("EconomyLog.txt");
    if(inEconomy.fail())
        outEconomy.open("EconomyLog.txt");
    inSystem.open("SystemGen.txt");
    if(inSystem.fail())
        outSystem.open("SystemGen.txt");
}

void errorCheck(int & input)
{
	while(cin.fail())
	{
		cin.clear();
		cin.ignore(256,'\n');
		cout << "Not a Number :: ";
		cin >> input;
	}
}

void errorCheck(char &input,char l1,char l2)
{
	do
	{
	if(input != l1&&input != l2)
		cout << "\nNot valid. :: ";
	cin >> input;
	}while(input != l1&&input != l2);
}

void resetAll()
{
    ofstream outLog,outRedShips,outBlueShips,outEconomy,outSystem;
	char ans;

	cout << "Are you sure?(Y/N) :: ";
	cin >> ans;
	if(ans == 'Y' || ans == 'y')
	{
        outLog.open("BattleLog.txt");
    	outRedShips.open("RedList.txt");
    	outBlueShips.open("BlueList.txt");
    	outEconomy.open("EconomyLog.txt");
    	outSystem.open("SystemGen.txt");
	}
}

void exitProg()
{
	cout << "\nExiting";
	for(int x=0;x<5;x++)
	{
		for (int i=0;i<100000000;i++);
		cout << ".";
	}
	exit(1);
}
/*pseudocode
Code remembers what ships were involved, adds to array, updates file at end of execution? Done V0.3
Code reads and writes economy to a master file for record keeping. Done Vol 0.7
*/

//Copyright 2015 Auragon Studios
//James Lee
