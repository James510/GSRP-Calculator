#include<iostream>
#include<time.h>
#include<fstream>
#include <stdlib.h>
#include <math.h>
using namespace std;
void declareShips (int[],int,int[],int);
void importShips (int[],int&,int[],int&);
void declareEconomy(int[]);
void importEconomy(int[]);
void attackRoller();
void economyCalc();
void errorCheck(int&);
void errorCheck(char&,char,char);
void exitProg();
void firstTimeInstallation();
int main()
{
	int ch;
	firstTimeInstallation();
	while(true)
	{
		cout << "\n------------------------------------"	
			 << "\nGalactic Nations RP Calculators V0.4"
			 << "\n1) Economy Calculator"
			 << "\n2) Battle Calculator"
			 << "\n3) Exit"
			 << "\n\nPlease Make Your Selection :: ";
		cin >> ch;
		if(cin.fail())
			errorCheck(ch);
		if(ch == 1)
			economyCalc();
		else if (ch == 2)
			attackRoller();
		else if (ch == 3)
			exitProg();
		else
			cout << "Not a Valid Choice";
	}
    return 0;
}

void economyCalc()
{
	int ch;
	double pp, gs, pop,mod,cur,conv;
	ofstream outEconomy;
	ifstream inEconomy;
	outEconomy.open("EconomyLog.txt",ios::app);
	while(true)
	{
		cout << "\n------------------------------------"
			 << "\n1) Project Points Calculator"
			 << "\n2) Tax Calculator"
		   	 << "\n3) Currency Conversion"
			 << "\n4) Exit"
			 << "\n\nPlease Make Your Selection :: ";
		cin >> ch;
		if(ch == 1)
		{
			cout << "Enter Your Current Population (Billions) :: ";
			cin >> pop;
			cout << "Enter your modifier (Default is 10) :: ";
			cin >> mod;
			pp = pop * mod;
			cout << "You have " << pp << " Project Points"<<endl;
		}
		else if (ch == 2)
		{
			cout << "Enter Your Current Population (Billions) :: ";
			cin >> pop;
			pp = (round(pop) * 10) / 2;
			cout << "You have " << pp << " Galactic Standard"<<endl;
		}
		else if (ch == 3)
		{
			cout << "Enter how many GS you have :: ";
			cin >> gs;
			cout << "Enter how many GS = one of your race's currency :: ";
			cin >> cur;
			conv = gs * cur;
			cout << "Your " << gs << " Galactic Standard converts to " << conv << "Local Currency.";
		}
		else if (ch == 4)
		{
			break;
		}
		else
		{
			cout << "Not a Valid Choice";
		}
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
    srand(time(NULL));
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
         cout << "\n----------------------";
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

void firstTimeInstallation()
{
 	ofstream outLog,outRedShips,outBlueShips,outEconomy;
    ifstream inLog,inRedShips,inBlueShips,inEconomy;
    
	inLog.open("BattleLog.txt");
    if(inLog.fail())
    {
        outLog.open("BattleLog.txt");
        //outLog.close();
	}
    inRedShips.open("RedList.txt");
    if(inRedShips.fail())
    {
        outRedShips.open("RedList.txt");
        //outRedShips.close();
	}
    inBlueShips.open("BlueList.txt");
    if(inBlueShips.fail())
    {
        outBlueShips.open("BlueList.txt");
        //outBlueShips.close();
	}
    inEconomy.open("EconomyLog.txt");
    if(inEconomy.fail())
    {
        outEconomy.open("EconomyLog.txt");
        //outEconomy.close();
	}
	    
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

void declareEconomy(int temp[])
{

}
void importEconomy(int temp[])
{

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

void exitProg()
{
	cout << "Exiting";
	for(int x=0;x<5;x++)
	{
		for (int i=0;i<100000000;i++);
		cout << ".";
	}
	exit(1);
}
/*pseudocode
Code remembers what ships were involved, adds to array, updates file at end of execution? Done V0.3
Code reads and writes economy to a master file for record keeping.
*/

//Copyright 2015 Auragon Studios
//James Lee
