
/* 
 * File:   main.cpp
 * Author: Julian Eastman
 *
 * Created on January 23, 2023, 3:03 AM
 * Purpose: This is my Project 2. It is a combat simulator for Dungeons and Dragons
 * Fifth Edition, and in its full version (project 2) is intended to run a small dungeon.
 * You can choose one of two classes, and can fight three monsters.
 * The classes come pre-made, and are level five,
 * with randomized stats each time. The monsters are Challenge
 * Rating 2, since they are fighting a single level 5 character.
 */

//system libraries
#include <cstdlib>  //uses random number seed.
#include <iostream> //io library
#include <iomanip>  //format library
#include <string>   //string library                 Use all included libraries!
#include <fstream>  //file library
#include <ctime>    //time library, for random numbers.
#include <cmath>    //math library, for nerfing the Fireball spell. //format library
#include <vector>
//user libraries

//global constants, not variables. Don't use global variables.
//science, math, conversions, dimensions.

//Function prototypes


using namespace std;

void sSrtVec(vector<int>&);


void selSort(unsigned short [], int);//A selection sorter.
void bubSort(unsigned short [], int);//A bubble sorter.
void linSrch(unsigned short [], int, int=18);//A linear search function, to check if they rolled an 18 for any stats.
unsigned short d20();
unsigned short d20(char); //an overloaded d20 function where you can apply advantage or disadvantage with a char.
unsigned short d12();
unsigned short d10();
unsigned short d8(); //our six die types for the game.
unsigned short d6();
unsigned short d4();
bool prob(); //coin flip probability

void zombie(float &, short, short, short, short, short, short, string, string, string,short &,short &,short &,short &,unsigned short, unsigned short,short &,bool &); //the fight with the zombie. Intakes quite a bunch of things. But hey, it runs with no errors!
void chestRm(unsigned short, short &, short &, short &, short &); //the function for opening a chest.
void mimic(float &, short, short, short, short, short, short, string, string, string,short &,short &,short &,short &,unsigned short, unsigned short,short &,bool &); //the fight with the Mimic.
void archer(float &, short, short, short, short, short, short, string, string, string,short &,short &,short &,short &,unsigned short, unsigned short,short &,bool &);

int main(int argc, char** argv) {
    //set random number seed*****************************
    srand(static_cast<unsigned int>(time(0)));        //*
    //Now, we can't use time as a variable anymore.******
    //Begin the game.***********************************************
    cout << "Dungeons & Dragons 5th Edition: Combat Simulator\n";//*
    cout << "Programmed by Julian Eastman.\n";                   //*
    //**************************************************************
    /*declare integer variables: player health, monster health, 
    player strength, constitution, dexterity, wisdom, intelligence, charisma*/
    float pHlth, mHlth; //player and monster health.
    unsigned short str, con, dex, wis, intl, cha, Ac, Dc; //player scores and armor class, and spell save dc if needed. 
    short strSc, conSc, dexSc, wisSc, intlSc, chaSc; //ability modifiers.
    
    //unsigned short d4, d6, d8, d10, d12, d20; //our dice set. In the future, these can be functions.
    const short RSIZ = 4;
    unsigned short r[RSIZ];//The stat roller array
    unsigned short temp; //temporary variable, for number sorting.
    char choice; //temporary choice string.
    short monAc; //monster armor class.
    string clsNm, pName, monNm, race, word; //the name of your class, the name you give your character,
    short sp1=4,sp2=3,sp3=2, abj=0; //Declare first, second, and third level spell slots, for wizards. Also see how many abjuration spells have been cast.
    short arrow=20; //number of arrows, for Fighter.
    //the name of the monster you'll be fighting, and your character's race. Also, the
    //variable for inputting words from files.
    
    
    //Begin the game. Ask player for name and then roll their stats.
    cout << "Input a name for your character: \n";
    getline(cin,pName);
    cout << "Rolling stats for " << pName << "...\n";
    //For each stat, roll 4 d6 and remove the lowest roll. Then add them.
    //So, I need to get the rolls in desc. order and add the highest three.
    //Also, set the ability modifiers for each one.
    //Strength: ****************************************************************
    for(int x=0;x<RSIZ;x++){                                                 //*
        r[x] = d6();                                                         //*
    }                                                                        //*                  
    bubSort(r,RSIZ);   //We will bubble sort strength.                       //*
    str=r[RSIZ-1]+r[RSIZ-2]+r[RSIZ-3];                                       //*
    //**************************************************************************
    
    //Constitution: ************************************************************
    for(int x=0;x<RSIZ;x++){                                                 //*
        r[x] = d6();                                                         //*
    }                                                                        //*                     
    selSort(r,RSIZ);   //We will selection sort constitution.                //*
    con=r[RSIZ-1]+r[RSIZ-2]+r[RSIZ-3];                                       //*
    //**************************************************************************
    
    //Dexterity:    ************************************************************
    vector<int> ro(RSIZ); //This is to include vectors in the project        //*
    for(int x=0;x<RSIZ;x++){                                                 //*
        ro[x] = d6();                                                        //*
    }                                                                        //*                     
    sSrtVec(ro);   //We will selection sort dexterity.                       //*
    dex=ro[0]+ro[1]+ro[2];                                                   //*
    //**************************************************************************
    //Wisdom:   ****************************************************************
    for(int x=0;x<RSIZ;x++){                                                 //*
        r[x] = d6();                                                         //*
    }                                                                        //*                     
    selSort(r,RSIZ);   //We will selection sort wisdom.                      //*
    wis=r[RSIZ-1]+r[RSIZ-2]+r[RSIZ-3];                                       //*
    //**************************************************************************
    
    //Intelligence: ************************************************************
    for(int x=0;x<RSIZ;x++){                                                 //*
        r[x] = d6();                                                         //*
    }                                                                        //*                     
    selSort(r,RSIZ);   //We will selection sort intelligence.                //*
    intl=r[RSIZ-1]+r[RSIZ-2]+r[RSIZ-3];                                      //*
    //**************************************************************************
    
    //Charisma:     ************************************************************
    for(int x=0;x<RSIZ;x++){                                                 //*
        r[x] = d6();                                                         //*
    }                                                                        //*                     
    selSort(r,RSIZ);   //We will selection sort charisma.                    //*
    cha=r[RSIZ-1]+r[RSIZ-2]+r[RSIZ-3];                                       //*
    //**************************************************************************
    
    
    //Display stats, so player can decide what to do with them.
    cout << pName << "'s base stats are:" << endl;  
    cout << str << ", ";
    cout << con << ", ";
    cout << dex << ", ";
    cout << intl<< ", ";
    cout << wis << ", ";
    cout << cha << endl << endl;
    
    const int SSIZ=6;
    unsigned short s[SSIZ]; //temporary container for moving our scores.
    unsigned short sd[SSIZ]; //A parallel array, for putting the scores in descending order.
    s[0]=str;
    s[1]=con;
    s[2]=dex;
    s[3]=wis; 
    s[4]=intl;
    s[5]=cha;
    
    linSrch(s,SSIZ); //we will let this function use the default parameter to search.
    
    //Have player choose a race and class.  Remember to validate input with default
    //in switch case.
    do{
        cout << "Pick a race. Choose from \n";
        cout << "1: Human\n";
        cout << "2: Elf\n"; //For Elf, make them pick where to apply score increases.
        cout << "3: Dwarf\n"; //For all races, make sure the increases come in
        cout << "4: Orc\n";   //after you pick where your scores are going.
        cout << "5: See race features\n\n"; //With 5, intake the features from a file and show them.
                          //This is best done with a switch(race) set after
                          //the scores are moved around, that adds in the increases.
        cin >> choice;
        ifstream raceDsc; //race description file.
        
        switch(choice){ //take in the choice as a character, act on the choice.
            case'1':
                race = "Human";
                choice='1';
                break;
                
            case'2':
                race = "Elf";
                choice='1';
                break;
                
            case'3':
                race = "Dwarf";
                choice='1';
                break;
                
            case'4':
                race = "Orc";
                choice='1';
                break;
                
            case'5':
                raceDsc.open("Race_Desc.txt"); //open the race description file.
                if(raceDsc){ //Reads file, if it can be opened.
                    while(raceDsc >> word){
                        if(word == "endl"){ //This is so I can end lines more cleanly
                            cout << endl;   //while reading from files.
                        }
                        else{
                            cout << word << " ";
                        }
                    }
                    raceDsc.close(); //close file to avoid corruption.
                    cout << "Press Enter to continue.\n"; 
                    cin.ignore(); //ignore the last buffer character.(\n) 
                    cin.get();//pause so they can read.
                }
                else{
                    cout << "Race description file failed to open.";
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                cout << "Invalid choice. Write choice as a number from 1 to 5.\n\n";
                
                
                
        }
        
        
    }while(choice!='1');
    cout << "You chose: " << race << endl << endl; //display their choice.
    
    //Now that race is chosen, do the same for class.
    
    
    ifstream clsDsc; //class description file.
    do{
        cout << "Pick a class. Choose from \n";
        cout << "1: Fighter\n";
        cout << "2: Wizard\n";
        cout << "3: See class features\n\n";
    
        cin >> choice;
        
        switch(choice){
            case'1':
                clsNm="Fighter";
                choice='1';
                break;
            
            case'2':
                clsNm="Wizard";
                choice='1';
                break;
        
            case'3':
                clsDsc.open("Class_Desc.txt"); //open the class description file.
                    if(clsDsc){ //Reads file, if it can be opened.
                        while(clsDsc >> word){
                            if(word == "endl"){ //This is so I can end lines more cleanly
                                cout << endl;   //while reading from files.
                            }
                            else{
                                cout << word << " ";
                            }
                        }
                        clsDsc.close(); //close file to avoid corruption.
                        cout << "Press Enter to continue.\n"; 
                        cin.ignore(); //ignore the last buffer character.(\n) 
                        cin.get();//pause so they can read.
                    }
                    else{
                        cout << "Class description file failed to open.";
                        exit(EXIT_FAILURE);
                    }
                break;
            default:
                cout << "Invalid choice. Write choice as a number from 1 to 3.\n\n";
        }
    }while(choice!='1');
    cout << "You chose: " << clsNm << endl;
    
     //Now, the player has selected their race and class. So, now we need to
     //optimize the rolled scores for the class, and add racial bonuses.  
    cout << "Optimizing scores...\n\n";
    
    
    
    selSort(s,SSIZ); //this will arrange s[] in ascending order. So, do this:
    for(int i=0;i<SSIZ;i++){
        sd[i]=s[SSIZ-1-i]; //sd[0]=s[5], sd[1]=s[4], and so on until the values are reversed.
    }
    //add racial bonuses. First do Human and Elf, then assign scores to abilities,
    //then do Dwarf and Orc. (these last 2 add to specific abilities.)
    
    
    if(race=="Human"){
        sd[0]++; //add 2 to top attribute, then 1 to others.
        sd[0]++;
        sd[1]++;
        sd[2]++;
        sd[3]++;
        sd[4]++;
        sd[5]++;
        
    }
    else if(race=="Elf"){
        sd[0]++;
        sd[0]++;
        
    }
    //Sort for classes.
    if(clsNm=="Fighter"){ //optimizes stats for Fighter.
        str=sd[0];
        con=sd[1];
        dex=sd[2];
        cha=sd[3];
        wis=sd[4];
        intl=sd[5];   
    }
    else{ //optimizes stats for Wizard.
        intl=sd[0];
        dex=sd[1];
        con=sd[2];
        wis=sd[3];
        str=sd[4];
        cha=sd[5];
    }
    //Add Dwarf and Orc scores.
    if(race=="Dwarf"){
        con++;
        con++;
        
    }
    else if(race=="Orc"){
        str++;
        str++;
        con++;
        
    }
    //calculate ability score modifiers.
    strSc=-5+(str/2); //we want integer division for ability scores.
    conSc=-5+(con/2); 
    dexSc=-5+(dex/2); 
    wisSc=-5+(wis/2); 
    intlSc=-5+(intl/2); 
    chaSc=-5+(cha/2); 
    if(clsNm=="Fighter"){ //optimizes stats for Fighter.  
        pHlth=(10+static_cast<float>(conSc))+((6+static_cast<float>(conSc))*4); //base health, for level 5.
        Ac=18;
        Dc=0;
    }
    else{ //optimizes stats for Wizard.
        pHlth=(6+static_cast<float>(conSc))+((4+static_cast<float>(conSc))*4); //base health, for level 5.
        Ac=10+dexSc;
        Dc=11+intlSc;
    }
    
    
    //At long last, display their name, race, class, scores, and ability mods.
    cout << pName << ": " << race << " " << clsNm << endl << endl;
    cout << "Abilities:\n";
    cout << "STR: " << setw(2) << str << ", Modifier: " << setw(2) << strSc << endl;
    cout << "CON: " << setw(2) << con << ", Modifier: " << setw(2) << conSc << endl;
    cout << "DEX: " << setw(2) << dex << ", Modifier: " << setw(2) << dexSc << endl;
    cout << "WIS: " << setw(2) << wis << ", Modifier: " << setw(2) << wisSc << endl;
    cout << "INT: " << setw(2) << intl<< ", Modifier: " << setw(2) << intlSc<< endl;
    cout << "CHA: " << setw(2) << cha << ", Modifier: " << setw(2) << chaSc << endl << endl;
    cout << "Health: " << pHlth << endl;
    cout << "Armor Class: " << Ac << endl;
    (clsNm=="Wizard")?
        cout << "Spell Save DC: " << Dc << endl << endl: //I added this ternary operator for Version 6. 
        cout << endl;
        
    
    cout << "Press Enter to continue.\n"; 
    cin.ignore(); //ignore the last buffer character.(\n) 
    cin.get();//pause so they can read.
    
    //********************************************************************************This is the beginning of the combat*****************
    
    //Now, enter the dungeon.
    //In part 2, I will make more monsters and more rooms, but this is it for now.
    //Also, once monsters exist that deal damage types that players can resist,
    //the resistances will be accounted for.
    cout << "Trudging up the freezing mountain pass, you find to your left a crumbling stone entryway.\n";
    cout << "To escape the icy gale, you decide to enter the dungeon.\n";
    bool orc=true; //relentless endurance, for orcs.
    
    zombie(pHlth,strSc,conSc,dexSc,wisSc,intlSc,chaSc,pName,clsNm,race,sp1,sp2,sp3,abj,Ac,Dc,arrow,orc);///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    //Now, have them go in, and get to a room with four chests. They get to choose one.
    //Randomize them with a 2x2 array where each entry is a d4 roll. If the chest they choose rolled a 4, it is a mimic and they fight.
    if(pHlth>0){
        const short DIMXY=2; //constant for a 2x2 array, in x and y direction.
        unsigned short chest[DIMXY][DIMXY];
        for(int i=0; i<DIMXY; i++){ //dimension one loop
            for(int j=0; j<DIMXY; j++){ //dimension two loop
                chest[i][j]=d4(); //roll for each entry.
            }
        }
        cout << "You enter a room which has four chests. For the most part, they look identical.\n";
        cout << "You only have time to loot one of them. Make a choice.\n";
        cout << "1: open chest A\n";
        cout << "2: open chest B\n";
        cout << "3: open chest C\n";
        cout << "4: open chest D\n";
        cout << "Any other key: leave the room\n\n";
        cin >> choice;

        switch(choice){
            case '1':
                cout << "You choose chest A.\n";
                chestRm(chest[0][0],sp1,sp2,sp3,arrow);
                if(chest[0][0]==4)mimic(pHlth,strSc,conSc,dexSc,wisSc,intlSc,chaSc,pName,clsNm,race,sp1,sp2,sp3,abj,Ac,Dc,arrow,orc);
                break;
            case '2':
                cout << "You choose chest B.\n";
                chestRm(chest[0][1],sp1,sp2,sp3,arrow);
                if(chest[0][1]==4)mimic(pHlth,strSc,conSc,dexSc,wisSc,intlSc,chaSc,pName,clsNm,race,sp1,sp2,sp3,abj,Ac,Dc,arrow,orc);
                break;
            case '3':
                cout << "You choose chest C.\n";
                chestRm(chest[1][0],sp1,sp2,sp3,arrow);
                if(chest[1][0]==4)mimic(pHlth,strSc,conSc,dexSc,wisSc,intlSc,chaSc,pName,clsNm,race,sp1,sp2,sp3,abj,Ac,Dc,arrow,orc);
                break;
            case '4':
                cout << "You choose chest D.\n";
                chestRm(chest[1][1],sp1,sp2,sp3,arrow);
                if(chest[1][1]==4)mimic(pHlth,strSc,conSc,dexSc,wisSc,intlSc,chaSc,pName,clsNm,race,sp1,sp2,sp3,abj,Ac,Dc,arrow,orc);            
                break;
            default:
                cout << "You proceed down the corridor.\n";
        }
        cout << endl;
    }
    
    
    //Bossfight against the Archer. Cannot be hit with a melee attack. Is also a construct, so rolls against Shatter with disadvantage.
    //Also forces a con save sometimes, for the Dwarves.
    if(pHlth>0){
        archer(pHlth,strSc,conSc,dexSc,wisSc,intlSc,chaSc,pName,clsNm,race,sp1,sp2,sp3,abj,Ac,Dc,arrow,orc);
    }
    
    
    
    
    
    //clean up memory and files.
    //Add the latest high score (hit points remaining) to the HighScore.txt file.
    if(pHlth>0)cout << "Congratulations. You have won the game.\n";
    cout << "You ended with " << pHlth << " hit points remaining.\n";
    
    
    ifstream hiScIp; //high score (input)
    float score; //reader.
    bool hScr=true; //whether or not we have a high score.
    hiScIp.open("HighScore.txt");
    if(hiScIp){//checks if our file opened.
        while(hiScIp >> score){
            if(score>pHlth){
                hScr=false;
            }
        }
    }
    else{//if file doesnt open:
        cout << "The high score file could not be opened.";
        exit(EXIT_FAILURE);//fail the program.
    }
    hiScIp.close();//close file to avoid corruption.
    if(hScr==true){
        cout << "You scored higher than last time!";
    }
    
    ofstream hiScOp; //high score (output)
    hiScOp.open("HighScore.txt");
    hiScOp << pHlth << endl; //write the high score to the file.
    hiScOp.close();//close file to avoid corruption.
    
    //exit program.

    return 0;
}

void linSrch(unsigned short a[], int size, int val){ //This function is defaulted.
    int ind=0;
    bool found=false;
    while(ind<size && !found){
        if(a[ind]==val){
            found=true;
            cout << "Congratulations. You rolled an 18 (max score) for one of your base stats!" << endl << endl;
        }
        ind++;
    }
}
void sSrtVec(vector<int> &a){
    int minDex, minVal;
    for(int s=0;s<(a.size()-1);s++){
        minDex=s;
        minVal=a[s];
        for(int i=s+1;i<a.size();i++){
            if(a[i]<minVal){
                minVal=a[i];
                minDex=i;
            }
        }
        int temp=a[minDex];
        a[minDex]=a[s];
        a[s]=temp;
    }
    int strt=0, end=a.size()-1;
    while(strt<end){
        int temp=a[strt];
        a[strt]=a[end];
        a[end]=temp;
        strt++;
        end--;
    }
}
    


void selSort(unsigned short a[], int size){ // the selection sorter (ascending order)
    int minDex, minVal;
    for(int s=0;s<(size-1);s++){
        minDex=s;
        minVal=a[s];
        for(int i=s+1;i<size;i++){
            if(a[i]<minVal){
                minVal=a[i];
                minDex=i;
            }
        }
        int temp=a[minDex];
        a[minDex]=a[s];
        a[s]=temp;
    }
}

void bubSort(unsigned short a[], int size){ // the bubble sorter (ascending order)
    for(int maxEl=size-1;maxEl>0;maxEl--){
        for(int index=0;index<maxEl;index++){
            if(a[index]>a[index+1]){
                int temp=a[index];
                a[index]=a[index+1];
                a[index+1]=temp;
            }
        }
    }
}

unsigned short d20(){
    return (rand()%20)+1;
}
unsigned short d20(char a){ //the overloaded d20 function, which receives a char to roll at advantage or disadvantage.
    unsigned short rollH = (rand()%20)+1; //high roll
    unsigned short rollL = (rand()%20)+1; //low roll
    if(rollH<rollL){ //if the rolls are in the wrong place:
        int temp=rollH; //switch the rolls to reflect their names.
        rollH=rollL;
        rollL=temp;
    }
    if(a=='a'){ //roll at advantage
        return rollH;
    }
    else if(a=='d'){ //roll at disadvantage
        return rollL;
    }
    else{
        return (rand()%20)+1;
    }
}

unsigned short d12(){
    return (rand()%12)+1;
}
unsigned short d10(){
    return (rand()%10)+1;
}
unsigned short d8(){
    return (rand()%8)+1;
}
unsigned short d6(){
    return (rand()%6)+1;
}
unsigned short d4(){
    return (rand()%4)+1;
}
bool prob(){
    return (rand()%2); //the function for flipping a coin, or randomly choosing between two options.
}

void zombie(float &pHlth, short strSc, short conSc, short dexSc, short wisSc, short intlSc, short chaSc, string pName, string clsNm, string race,short &sp1, short &sp2, short &sp3, short &abj,unsigned short Ac, unsigned short Dc,short &arrow, bool &orc){ //the fight with the zombie.
    
    cout << "Shambling from the darkness below, a Frost Zombie appears!\n";
    //Initialize zombie stats.
    short zStr=3,zCon=4,zDex=-2,zWis=-2,zInt=-4,zCha=-3;//zombie modifiers
    int hit; //the zombie's rolls to hit, and also, your rolls to hit. Depends on who's currently doing their turn.
    string monNm="Frost Zombie";
    short monAc=8;
    short mHlth=42; // the zombie starts with 42 hit points.
    
    
    cout << "The zombie approaches, snarling in anticipation.\n";
    cout << "In its cold, dead hand, the zombie wields a wooden club frozen over with sharpened ice.\n\n";
    cout << "Press Enter to roll initiative.\n"; 
    //cin.ignore(); //ignore the last buffer character.(\n) 
    cin.get();//pause so they can read.
    cout << "Rolling initiative...\n";
    int pInit, mInit; //player and monster initiative.
    
    pInit=d20()+dexSc; //player initiative
    mInit=d20()+zDex; //monster initiative
    
    cout << pName << "'s Initiative: " << pInit << endl;
    cout << monNm << "'s Initiative: " << mInit << endl;
    
    
    if(mInit>pInit){ //display who wins.**********
        cout << monNm << " attacks first.\n\n";//*
    }//                                          *
    else{//                                      *
        cout << pName << " attacks first.\n\n";//*
    }//                                          *
    //********************************************
    cout << "Press Enter to continue.\n";
    cin.get();//pause them here so they have time to read.
    
    
    //begin combat!
    char choice;
    bool cursed=false; //if the enemy is cursed, this is true.
    short feeble=0; //if monster is enfeebled.
    short blind=0; //if monster is blinded.
    short heal=1; //number of times fighter can heal.
    //Orcs have one charge of Relentless Endurance.
    bool fail=false; //If the zombie fails its save.
    do{ 
        if(mInit>pInit&&(mHlth>0&&cursed==false)){ //Monster attack, provided it has HP left and isn't cursed.
            cout << "Zombie's turn:\n";
            short x=0;//ice breath cooldown counter
            if(prob()&&x<=0){ //ice breath weapon. (six round cooldown.)
                x=6;
                cout << "The zombie attacks with ice breath.\nPress Enter to roll a DEX save, DC 13.\n";
                cin.get();//pause so they can read.
                cout << "Rolling DEX save: ";
                short save=d20()+dexSc;
                if(race=="Elf"){ //If our player is an Elf, apply the dex advantage.
                    save=d20('a')+dexSc;
                }
                cout << save << endl;
                if(save<13){ //***************************failed save
                    int dmg =d6()+d6()+d6();
                    if(feeble>0){ //if monster is enfeebled
                        pHlth=pHlth-(static_cast<float>(dmg)/2);
                        cout << "You failed your DEX save.\n";
                        cout << "The " << monNm << " is enfeebled.\n";
                        cout << "You take " << setprecision(1) << fixed << static_cast<float>(dmg)/2 << " cold damage.\n\n";
                    }
                    else{
                        pHlth=pHlth-(dmg);
                        cout << "You failed your DEX save.\n";
                        cout << "You take " << dmg << " cold damage.\n\n";
                    }
                }
                else{//***********************************succeeded save
                    int dmg =d6()+d6()+d6();
                    if(feeble>0){ //if monster is enfeebled:
                        pHlth=pHlth-(static_cast<float>(dmg)/4);
                        cout << "You succeeded in your DEX save.\n";
                        cout << "The " << monNm << " is enfeebled.\n";
                        cout << "You take half damage: " << setprecision(1) << fixed << (static_cast<float>(dmg)/4) << " cold damage.\n\n";
                    }
                    else{
                        pHlth=pHlth-(static_cast<float>(dmg)/2);
                        cout << "You succeeded in your DEX save.\n";
                        cout << "You take half damage: " << setprecision(1) << fixed << (static_cast<float>(dmg)/2) << " cold damage.\n\n";
                    }
                    
                }
                
            }   
            else{ //club attack.
                cout << "The zombie swings its club at you. Rolling to hit.\n";\
                hit = d20()+5; //the zombie has a +5 to hit.
                if(blind>0){//if zombie is blinded
                    cout << "Zombie is blinded. It must roll at disadvantage.\n";
                    blind--;
                    hit=d20('d')+5;
                }
                
                if(hit>=Ac){//if the hit hits the player:
                    if(clsNm=="Wizard"&&(sp1>0&&hit<=Ac+5)){ //Wizards have shields, if their spell slots are unused.
                        cout << "You have been hit. Would you like to cast Shield as a first-level spell?\n";
                        cout << "Press 'y' for yes, 'n' for no.";
                        cin >> choice;
                        cin.ignore(); //soaks up the "enter" character you put there after.
                        if(choice=='y'||choice=='Y'){ //if they chose to block attack
                            cout << "You block the attack.\n";
                            sp1--;
                            abj++;
                            if(abj==1){//**************************************************Abjuration health boost.
                                cout << "You have cast your first Abjuration spell. ";
                                pHlth+=(10+intlSc);
                                cout << "You have regained " << 10+intlSc << " hit points.\n\n";
                            }
                            else{
                                cout << "You have cast a first-level Abjuration spell. ";
                                pHlth+=2;
                                cout << "You have regained 2 hit points.\n\n";
                            }
                        }
                        else{//if they didnt choose to block the attack.
                            cout << "You allow the attack to hit.\n";
                            int dmg1 = d4()+3; //the bludgeoning damage
                            int dmg2 = d6()+d6(); //the cold damage
                            if(feeble>0){ //if monster is enfeebled:
                                pHlth-=(static_cast<float>(dmg1+dmg2)/2);
                                cout << "The " << monNm << " is enfeebled.\n";
                                cout << "You take " << (dmg1)/2 << " bludgeoning damage and " << (dmg2)/2 << " cold damage.\n\n";
                                feeble--;
                            }
                            else{
                                pHlth-=(dmg1+dmg2);
                                cout << "You have been hit.\n";
                                cout << "You take " << dmg1 << " bludgeoning damage and " << dmg2 << " cold damage.\n\n";
                            }

                        }
                    }
                    else{
                        int dmg1 = d4()+3; //the bludgeoning damage
                        int dmg2 = d6()+d6(); //the cold damage
                        if(feeble>0){ //if monster is enfeebled:
                            pHlth-=(static_cast<float>(dmg1+dmg2)/2);
                            cout << "The " << monNm << " is enfeebled.\n";
                            cout << "You take " << (dmg1)/2 << " bludgeoning damage and " << (dmg2)/2 << " cold damage.\n\n";
                            feeble--;
                        }
                        else{
                            pHlth-=(dmg1+dmg2);
                            cout << "You have been hit.\n";
                            cout << "You take " << dmg1 << " bludgeoning damage and " << dmg2 << " cold damage.\n\n";
                        }
                    }
                }
                else{
                    cout << "The attack misses you.\n\n";
                }
            }
            
            
            cout << "Press Enter to continue.\n";
            
            cin.get();//pause them here so they have time to read.
            x--; //count down cooldown for ice breath.
        }
        else if((cursed==true&&mHlth>0)&&mInit>pInit){ //if the monster is cursed and is still alive, and has higher initiative.
            cout << "The " << monNm << " is cursed. It will attempt a WIS save.\n";
            short Zsave=d20()+zWis; //make the save.
            if(Zsave>=Dc){//If it's success
                cout << "The " << monNm << " has broken your curse. It can now take turns normally.\n\n";
                cursed=false;
            }
            else{
                cout << "The " << monNm << " has failed to remove your curse.\n\n";
            }
        }
        
        if(pHlth<=0&&(orc==true&&race=="Orc")){//Apply Relentless Endurance, if the player is an Orc.
            orc=false;
            cout << "You have sustained fatal injuries, but as an Orc, you can keep fighting.\n\n";
            pHlth=1;//put their health back at one hit point.
        }

        if(pHlth>0){ //Player attack, if player has HP left.
            cout << pName << "'s turn.\n";
            int choInt;//choice integer, because this menu has double digits.
            if(clsNm=="Wizard"){//the menu for a wizard. 12 spells (13th is shield, which is a reaction.)
                cout << "Your HP: " << setprecision(1) << fixed << pHlth << endl;
                cout << "Spell Slots: " << sp1 << " 1st, " << sp2 << " 2nd, " << sp3 << " 3rd.\n\n";
                cout << "Choose an option: \n";
                cout << "1: Attack with Dagger\n\n";
                cout << "Cantrips (no spell slot needed): \n";
                cout << "2: Fire Bolt (ranged attack, 2d10 fire damage)\n";
                cout << "3: Frostbite (CON save, 2d6+INT cold damage)\n";
                cout << "4: Mind Sliver (INT save, 3d6 psychic damage)\n\n";
                cout << "First Level Spells: \n";
                cout << "5: Burning Hands (DEX save, 3d6 fire damage or half on a successful save)\n";
                cout << "6: Chromatic Orb (ranged attack, 3d8 radiant damage.)\n";
                cout << "7: Witch Bolt (ranged attack, 2d12 lightning damage)\n\n";
                cout << "Second Level Spells:\n";
                cout << "8: Blindness (CON save, enemy spends next 3 rounds with disadvantage on attacks)\n";
                cout << "9: Ray of Enfeeblement (Abjuration, ranged attack, enemy spends 3 turns doing 1/2 damage.)\n";
                cout << "10: Shatter (CON save, 3d8 thunder damage or half with save, constructs roll with disadvantage.)\n";
                cout << "11: Dragon Breath (DEX save, 3d6 fire damage or half on save.)\n\n";
                cout << "Third Level Spells:\n";
                cout << "12: Bestow Curse (WIS save, or enemy loses turns until it succeeds on the save.)\n";
                cout << "13: Fireball (Dex save, 8d6 fire damage or the square root of that on a save.)\n\n";
                
                do{
                    cin >> choInt;
                    switch(choInt){
                        case 1: //dagger
                            { //parentheses are here to fix the case label error that happens if you
                                      //declare variables within cases without parentheses. 
                                cout << "You attempt to stab the " << monNm << " with your dagger.\n";
                                int roll = d20();
                                hit = roll + 3 + dexSc; //add modifiers.
                                if(hit>=monAc){//if attack hits:
                                    cout << "You rolled a " << hit << " and successfully hit.\n";
                                    int dmg=d4()+dexSc; //1d4+DEX damage.
                                    if(roll==20){
                                        cout << "You have rolled at maximum, and have scored a critical hit.\n";
                                        dmg*=2; //multiply damage by 2.
                                    }
                                    mHlth-=(dmg);
                                    cout << "The " << monNm << " takes " << dmg << " piercing damage.\n\n";

                                }
                                else{//if attack misses:
                                    cout << "Your strike misses the " << monNm << "." << endl << endl;
                                }
                            }
                            break; //I left off here. Fix the case label errors********************************
                        case 2: //fire bolt
                            { //parentheses are here to fix the case label error that happens if you
                                      //declare variables within cases without parentheses. 
                                cout << "You cast Fire Bolt as a cantrip.\n";
                                hit = d20() + 3 + intlSc; //add modifiers.
                                if(hit>=monAc){//if attack hits:
                                    cout << "You rolled a " << hit << " and successfully hit.\n";
                                    int dmg=d10()+d10(); //2d10 damage.
                                    mHlth-=(dmg*2);
                                    cout << "The " << monNm << " takes " << dmg*2 << " fire damage.\n\n";

                                }
                                else{//if attack misses:
                                    cout << "Your Fire Bolt misses the " << monNm << "." << endl << endl;
                                }
                            }
                            
                            break;
                        case 3: //frostbite ***Make this actually work once non ice-type enemies are introduced in proj2.
                            cout << "You cast your spell, only to find that the " << monNm << " is immune to cold damage.\n\n";
                            break;
                        case 4: //mind sliver
                            {
                                cout << "You cast Mind Sliver as a cantrip. The " << monNm << " must make an INT save.\n";
                                short Zsave=d20()+zInt; //make the save.
                                if(Zsave>=Dc){//if the save succeeds:
                                    cout << "The " << monNm << " succeeds on its save and takes no damage.\n";
                                }
                                else{ //if save fails:
                                    int dmg = d6()+d6()+d6(); //3d6 damage
                                    cout << "The " << monNm << " fails on its save and takes " << dmg << " psychic damage.\n\n";
                                    mHlth-=dmg; 
                                }
                            }
                            
                            break;
                        case 5: //burning hands (1)
                            if(sp1<1){ //if they're out of slots
                                cout << "You are out of first level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{//if they have slots.
                                sp1--;
                                cout << "You cast Burning Hands at the first level. The " << monNm << " must make a DEX save.\n";
                                short Zsave=d20()+zDex; //make the save.
                                if(Zsave>=Dc){//if the save succeeds:
                                    int dmg = d6()+d6()+d6(); 
                                    cout << "The " << monNm << " succeeds on its save and takes " << dmg << " fire damage.\n\n";
                                    mHlth-=dmg; //not *2 here because a successful save halves damage.
                                }
                                else{ //if save fails:
                                    int dmg = d6()+d6()+d6(); 
                                    //d6 rolls:      1              2              3              4              5             6             7                8
                                    cout << "The "<< monNm <<" fails on its save and takes " << dmg*2 << " fire damage.\n\n";
                                    mHlth-=(dmg*2); //zombie takes double damage because fire.
                                }
                            }
                            break;
                        case 6: //chromatic orb (1)
                            if(sp1<1){
                                cout << "You are out of first level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{
                                sp1--;
                                cout << "You cast Chromatic Orb at the first level.\n";
                                hit = d20() + 3 + intlSc; //add modifiers.
                                if(hit>=monAc){//if attack hits:
                                    cout << "You rolled a " << hit << " and successfully hit.\n";
                                    int dmg=d8()+d8()+d8(); //3d8 damage.
                                    mHlth-=dmg;
                                    cout << "The " << monNm << " takes " << dmg << " radiant damage.\n\n";
                                    
                                }
                                else{//if attack misses:
                                    cout << "Your Chromatic Orb misses the " << monNm << "." << endl << endl;
                                }

                            }
                            break;
                        case 7: //witch bolt    (1)
                            if(sp1<1){
                                cout << "You are out of first level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{
                                sp1--;
                                cout << "You cast Witch Bolt at the first level.\n";
                                hit = d20() + 3 + intlSc; //add modifiers.
                                if(hit>=monAc){//if attack hits:
                                    cout << "You rolled a " << hit << " and successfully hit.\n";
                                    int dmg=d12()+d12(); //2d12 damage.
                                    mHlth-=dmg;
                                    cout << "The " << monNm << " takes " << dmg << " lightning damage.\n\n";
                                    
                                }
                                else{//if attack misses:
                                    cout << "Your Witch Bolt misses the " << monNm << "." << endl << endl;
                                }

                            }
                            break;
                        case 8: //blindness     (2)
                            if(sp2<1){
                                cout << "You are out of second level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{
                                sp2--;
                                cout << "You cast Blindness at the second level. The " << monNm << " must make a CON save.\n";
                                int save = d20()+zCon; //add modifiers.
                                if(save>=Dc){//if save succeeds
                                    cout << "The " << monNm << " succeeded on its save and is not blinded.\n\n";
                                }
                                else{//if save fails
                                    cout << "The " << monNm << " failed its save and is blinded for 3 turns.\n\n";
                                    blind=2; //put the blindness on.
                                    
                                }
                            }
                            break;
                        case 9: //enfeeblement  (2)
                            if(sp2<1){
                                cout << "You are out of second level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{
                                sp2--;
                                abj++;
                                if(abj==1){//**************************************************Abjuration health boost.
                                    cout << "You have cast your first Abjuration spell. ";
                                    pHlth+=(10+intlSc);
                                    cout << "You have regained " << 10+intlSc << " hit points.\n\n";
                                }
                                else{
                                    cout << "You have cast a second-level Abjuration spell. ";
                                    pHlth+=4;
                                    cout << "You have regained 4 hit points.\n\n";
                                }
                                cout << "You cast Ray of Enfeeblement at the second level. ";
                                int atk = d20() + 3 + intlSc; //add modifiers.
                                if(atk>=monAc){//if attack hits:
                                    cout << "You rolled a " << atk << " and successfully hit. The " << monNm <<" is now Enfeebled for 3 turns.\n";
                                    feeble=3;
                                    //I left off here. Make sure "feeble" goes into monster attacks and reduces them.
                                }
                                else{//if attack misses:
                                    cout << "Your Ray of Enfeeblement misses the " << monNm << endl << endl;
                                }
                                
                            }
                            break;
                        case 10://shatter       (2)
                            if(sp2<1){
                                cout << "You are out of second level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{
                                sp2--;
                                cout << "You cast Shatter at the second level. The " << monNm << " must make a CON save.\n";
                                cout << "Press Enter to continue.\n";
                                cin.ignore();
                                cin.get(); //pause to let them read.
                                short Zsave=d20()+zCon; //make the dexterity save.
                                if(Zsave>=Dc){//if the save succeeds:
                                    int dmg = d8()+d8()+d8(); 
                                    float hfDmg = static_cast<float>(dmg)/2;
                                    //d8 rolls:      1              2              3        
                                    cout << "The " << monNm << " succeeds on its save and takes " << hfDmg << " thunder damage.\n\n";
                                    mHlth-=hfDmg; 
                                }
                                else{ //if save fails:
                                    int dmg = d8()+d8()+d8(); 
                                    //d8 rolls:      1              2              3            
                                    cout << "The "<< monNm <<" fails on its save and takes " << dmg << " thunder damage.\n\n";
                                    mHlth-=dmg; 
                                }
                            }
                            break;
                        case 11://dragon breath (2) //frost zombies take 2x damage from fire.
                            if(sp2<1){
                                cout << "You are out of second level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{
                                sp2--;
                                cout << "You cast Dragon Breath at the second level. The " << monNm << " must make a DEX save.\n";
                                cout << "Press Enter to continue.\n";
                                cin.ignore();
                                cin.get(); //pause to let them read.
                                short Zsave=d20()+zDex; //make the dexterity save.
                                if(Zsave>=Dc){//if the save succeeds:
                                    int dmg = d6()+d6()+d6(); 
                                    //d6 rolls:      1              2              3        
                                    cout << "The " << monNm << " succeeds on its save and takes " << dmg << " fire damage.\n\n";
                                    mHlth-=dmg; //not *2 here because a successful save halves damage.
                                }
                                else{ //if save fails:
                                    int dmg = d6()+d6()+d6(); 
                                    //d6 rolls:      1              2              3            
                                    cout << "The "<< monNm <<" fails on its save and takes " << dmg*2 << " fire damage.\n\n";
                                    mHlth-=(dmg*2); //zombie takes double damage because fire.
                                }
                            }
                            break;
                        case 12://bestow curse  (3)
                            if(sp3<1){ //if they're out of slots
                                cout << "You are out of third level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{//if they have slots.
                                sp3--;
                                cout << "You cast Bestow Curse at the third level. The " << monNm << " must make a WIS save.\n";
                                cout << "Press Enter to continue.\n";
                                cin.ignore();
                                cin.get(); //pause to let them read.
                                short Zsave=d20()+zWis; //make the wisdom save.
                                if(Zsave>=Dc){//if save succeeds
                                    cout << "The "  << monNm << " has successfully made the save. No effect is had.\n\n";
                                }
                                else{
                                    cout << "The "  << monNm << " has failed the save. It will lose turns until it can make the save.\n\n";
                                    cursed = true;
                                }
                            }
                            break;
                        case 13://fireball      (3) //frost zombies take 2x damage from fire.
                            if(sp3<1){ //if they're out of slots
                                cout << "You are out of third level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{//if they have slots.
                                sp3--;
                                cout << "You cast Fireball at the third level. The " << monNm << " must make a DEX save.\n";
                                short Zsave=d20()+zDex; //make the save.
                                if(Zsave>=Dc){//if the save succeeds:
                                    int dmg = d6()+d6()+d6()+d6()+d6()+d6()+ d6()+d6(); 
                                    cout << "The " << monNm << " succeeds on its save and takes " << sqrt(static_cast<float>(dmg))*2 << " fire damage.\n\n";
                                    mHlth-=sqrt(static_cast<float>(dmg))*2; //the x2 is for the fire vulnerability.
                                }
                                else{ //if save fails:
                                    int dmg = d6()+d6()+d6()+d6()+d6()+d6()+ d6()+d6(); 
                                    cout << "The "<< monNm <<" fails on its save and takes " << dmg*2 << " fire damage.\n\n";
                                    mHlth-=(dmg*2); //zombie takes double damage because fire.
                                }
                            }
                            break;
                        default:
                            cout << "Invalid choice. Please choose a number from 1 to 13.\n\n";
                    }
                }while(choInt>13||choInt<1);//keep repeating until they get the hint and choose a better number.
                cout << "Press enter to continue.\n";
                cin.ignore();
                cin.get(); //pause to let them read.
                
            }
            else{//the menu for a fighter.
                for(int i=2;i>0;i--){//repeats 2 times, for the fighter's 2 attacks.
                    if(i==1){//if this is the second attack:
                        cout << "You can attack again.\n";
                    }
                    
                    //Fighter Menu:
                    cout << "Your HP: " << setprecision(1) << fixed << pHlth << endl;
                    cout << "You have " << heal << " health packs left.\n\n";
                    cout << "Choose an option: \n";
                    cout << "1: Attack with Longsword\n";
                    cout << "2: Attack with Crossbow\n";
                    cout << "3: Heal 1d10+5 hit points;\n\n";
                    do{
                        cin >> choInt;
                        switch(choInt){
                            case 1: //sword
                                cout << "You take a swing at the " << monNm << ".\n";
                                hit = d20() + 3 + strSc; //add modifiers.
                                if(hit>=monAc){//if attack hits:
                                    cout << "You rolled a " << hit << " and successfully hit.\n";
                                    int dmg=d8()+strSc; //1d8+STR damage.
                                    mHlth-=dmg;
                                    cout << "The " << monNm << " takes " << dmg << " slashing damage.\n\n";
                                }
                                else{//if attack misses:
                                    cout << "Your sword misses the " << monNm << "." << endl << endl;
                                }
                                break;
                            case 2: //bow
                                if(arrow<=0){//if they have no more arrows
                                    cout << "Your quiver is empty. Choose another option.\n";
                                    choInt=5;//repeat the loop.
                                }
                                else{
                                    arrow--;//remove an arrow from the quiver.
                                    cout << "You take a shot at the " << monNm << ".\n";
                                    hit = d20() + 3 + dexSc; //add modifiers.
                                    if(hit>=monAc){//if attack hits:
                                        cout << "You rolled a " << hit << " and successfully hit.\n";
                                        int dmg=d6()+dexSc; //1d6+DEX damage.
                                        mHlth-=dmg;
                                        cout << "The " << monNm << " takes " << dmg << " piercing damage.\n\n";

                                    }
                                    else{//if attack misses:
                                        cout << "Your arrow misses the " << monNm << "." << endl << endl;
                                    }
                                }
                                break;
                            case 3:
                                if(heal<1){
                                    cout << "You have already used your healing. Choose another option.\n";
                                }
                                else{
                                    heal--;
                                    int dmgNg=d10()+5;//healing, or "negative damage"
                                    pHlth+=dmgNg; //1d10+5 healing.
                                    cout << "You heal for " << dmgNg << " hit points. Now, choose an attack, or you can heal again if you have any health packs.\n\n";
                                }
                                break;
                            default:
                                cout << "Invalid choice. Please choose a number from 1 to 3.\n\n";
                        }
                        
                    }while(choInt<1||choInt>2); //keep repeating if they choose an invalid option, or if they heal.
                    
                }
                cout << "Press enter to continue.\n";
                cin.ignore();
                cin.get(); //pause to let them read.
            }
            
        }
        
        if(mHlth<=0&&fail==false){//if the Frost Zombie is brought to 0 HP and has not failed its save yet, apply the undead fortitude.
            cout << "You have critically injured the Frost Zombie, but as an Undead, it can cheat death with a DC 16 CON save.\n";
            cout << "Rolling Constitution save...\n";
            int conSv=d20()+zCon;
            if(conSv>=16){
                cout << "The zombie lives on. Press Enter to continue.\n";
                cin.get();//pause them here so they have time to read.
                mHlth=1;//heal monster to 1 HP.
            }
            else{
                cout << "The zombie has failed the save.\n\n";
                fail=true;
            }
            
        }
        
        //Monster's attack, if it rolled less initiative.
        if(mInit<pInit&&(mHlth>0&&cursed==false)){ //Monster attack, provided it has HP left and isn't cursed.
            cout << "Zombie's turn:\n";
            short x=0;//ice breath cooldown counter
            if(prob()&&x<=0){ //ice breath weapon. (six round cooldown.)
                x=6;
                cout << "The zombie attacks with ice breath.\nPress Enter to roll a DEX save, DC 13.\n";
                cin.get();//pause so they can read.
                cout << "Rolling DEX save: ";
                short save=d20()+dexSc;
                if(race=="Elf"){ //If our player is an Elf, apply the dex advantage.
                    save=d20('a')+dexSc;
                }
                cout << save << endl;
                if(save<13){ //***************************failed save
                    int dmg =d6()+d6()+d6();
                    if(feeble>0){ //if monster is enfeebled
                        pHlth=pHlth-(static_cast<float>(dmg)/2);
                        cout << "You failed your DEX save.\n";
                        cout << "The " << monNm << " is enfeebled.\n";
                        cout << "You take " << setprecision(1) << fixed << static_cast<float>(dmg)/2 << " cold damage.\n\n";
                    }
                    else{
                        pHlth=pHlth-(dmg);
                        cout << "You failed your DEX save.\n";
                        cout << "You take " << dmg << " cold damage.\n\n";
                    }
                }
                else{//***********************************succeeded save
                    int dmg =d6()+d6()+d6();
                    if(feeble>0){ //if monster is enfeebled:
                        pHlth=pHlth-(static_cast<float>(dmg)/4);
                        cout << "You succeeded in your DEX save.\n";
                        cout << "The " << monNm << " is enfeebled.\n";
                        cout << "You take half damage: " << setprecision(1) << fixed << (static_cast<float>(dmg)/4) << " cold damage.\n\n";
                    }
                    else{
                        pHlth=pHlth-(static_cast<float>(dmg)/2);
                        cout << "You succeeded in your DEX save.\n";
                        cout << "You take half damage: " << setprecision(1) << fixed << (static_cast<float>(dmg)/2) << " cold damage.\n\n";
                    }
                    
                }
                
            }   
            else{ //club attack.
                cout << "The zombie swings its club at you. Rolling to hit.\n";\
                hit = d20()+5; //the zombie has a +5 to hit.
                if(blind>0){//if zombie is blinded
                    cout << "Zombie is blinded. It must roll at disadvantage.\n";
                    blind--;
                    hit=d20('d')+5;
                }
                
                if(hit>=Ac){//if the hit hits the player:
                    if(clsNm=="Wizard"&&(sp1>0&&hit<=Ac+5)){ //Wizards have shields, if their spell slots are unused.
                        cout << "You have been hit. Would you like to cast Shield as a first-level spell?\n";
                        cout << "Press 'y' for yes, 'n' for no.";
                        cin >> choice;
                        cin.ignore(); //soaks up the "enter" character you put there after.
                        if(choice=='y'||choice=='Y'){ //if they chose to block attack
                            cout << "You block the attack.\n";
                            sp1--;
                            abj++;
                            if(abj==1){//**************************************************Abjuration health boost.
                                cout << "You have cast your first Abjuration spell. ";
                                pHlth+=(10+intlSc);
                                cout << "You have regained " << 10+intlSc << " hit points.\n\n";
                            }
                            else{
                                cout << "You have cast a first-level Abjuration spell. ";
                                pHlth+=2;
                                cout << "You have regained 2 hit points.\n\n";
                            }
                        }
                        else{//if they didnt choose to block the attack.
                            cout << "You allow the attack to hit.\n";
                            int dmg1 = d4()+3; //the bludgeoning damage
                            int dmg2 = d6()+d6(); //the cold damage
                            if(feeble>0){ //if monster is enfeebled:
                                pHlth-=(static_cast<float>(dmg1+dmg2)/2);
                                cout << "The " << monNm << " is enfeebled.\n";
                                cout << "You take " << (dmg1)/2 << " bludgeoning damage and " << (dmg2)/2 << " cold damage.\n\n";
                                feeble--;
                            }
                            else{
                                pHlth-=(dmg1+dmg2);
                                cout << "You have been hit.\n";
                                cout << "You take " << dmg1 << " bludgeoning damage and " << dmg2 << " cold damage.\n\n";
                            }

                        }
                    }
                    else{
                        int dmg1 = d4()+3; //the bludgeoning damage
                        int dmg2 = d6()+d6(); //the cold damage
                        if(feeble>0){ //if monster is enfeebled:
                            pHlth-=(static_cast<float>(dmg1+dmg2)/2);
                            cout << "The " << monNm << " is enfeebled.\n";
                            cout << "You take " << (dmg1)/2 << " bludgeoning damage and " << (dmg2)/2 << " cold damage.\n\n";
                            feeble--;
                        }
                        else{
                            pHlth-=(dmg1+dmg2);
                            cout << "You have been hit.\n";
                            cout << "You take " << dmg1 << " bludgeoning damage and " << dmg2 << " cold damage.\n\n";
                        }
                    }
                }
                else{
                    cout << "The attack misses you.\n\n";
                }
            }
            
            
            cout << "Press Enter to continue.\n";
            
            cin.get();//pause them here so they have time to read.
            x--; //count down cooldown for ice breath.
        }
        else if((cursed==true&&mHlth>0)&&mInit<pInit){ //if the monster is cursed and is still alive, and has lower initiative.
            cout << "The " << monNm << " is cursed. It will attempt a WIS save.\n";
            short Zsave=d20()+zWis; //make the save.
            if(Zsave>=Dc){//If it's success
                cout << "The " << monNm << " has broken your curse. It can now take turns normally.\n\n";
                cursed=false;
            }
            else{
                cout << "The " << monNm << " has failed to remove your curse.\n\n";
            }
        }
        
        if(pHlth<=0&&(orc==true&&race=="Orc")){//Apply Relentless Endurance, if the player is an Orc.
            orc=false;
            cout << "You have sustained fatal injuries, but as an Orc, you can keep fighting.\n\n";
            pHlth=1;//put their health back at one hit point.
        }
        
        if(mHlth<=0&&fail==false){//if the Frost Zombie is brought to 0 HP, apply the undead fortitude.
            cout << "You have critically injured the Frost Zombie, but as an Undead, it can cheat death with a DC 16 CON save.\n";
            cout << "Rolling Constitution save...\n";
            int conSv=d20()+zCon;
            if(conSv>=16){
                cout << "The zombie lives on. Press Enter to continue.\n";
                cin.get();//pause them here so they have time to read.
                mHlth=1;//heal monster to 1 HP.
            }
            else{
                cout << "The zombie has failed the save.\n\n";
                fail=true;
            }
            
        }
        
    }while(pHlth>0&&mHlth>0); //keep fighting, to the death.
    
    if(pHlth<=0){//if the player has died:
        cout << "You have been slain by the " << monNm << ". Game over.\n";
    }
    else if(mHlth<=0){
        cout << "You have slain the " << monNm << ". You proceed further into the dungeon.\n";
    }
    
    
}

void chestRm(unsigned short x,short &sp1, short &sp2, short &sp3, short &arrow){
    if(x==4){ //a roll of 4 creates a Mimic.
        cout << "As you attempt to lift the lid, the chest jerks itself open to reveal a mouthful of serrated teeth.\n";
    }
    else{
        cout << "You open the chest.\n";
        if(x==1){
            cout << "You find a level one magic crystal, which is good for two spell slots.\n";
            cout << "You also find five arrows.\n";
            sp1+=2;
            arrow+=5;
        }
        else if(x==2){
            cout << "You find a level two magic crystal, which is good for two spell slots.\n";
            cout << "You also find ten arrows.\n";
            sp2+=2;
            arrow+=10;
        }
        else{
            cout << "You find a level three magic crystal, which is good for one spell slot.\n";
            cout << "You also find twenty arrows.\n";
            sp3++;
            arrow+=20;
        }
    }
}

void mimic(float &pHlth, short strSc, short conSc, short dexSc, short wisSc, short intlSc, short chaSc, string pName, string clsNm, string race,short &sp1, short &sp2, short &sp3, short &abj,unsigned short Ac, unsigned short Dc,short &arrow, bool &orc){ //the fight with the zombie.
    
    cout << "Hissing at you with its forked tongue, the Mimic gets up from its spot to run at you with its thorned tentacles.\n";
    //Initialize mimic stats.
    short zStr=3,zCon=2,zDex=1,zWis=1,zInt=-3,zCha=-1;//mimic modifiers
    int hit; //the mimic's rolls to hit, and also, your rolls to hit. Depends on who's currently doing their turn.
    string monNm="Mimic";
    short monAc=12;
    short mHlth=32; // the mimic starts with 42 hit points.
    
    cout << "Press Enter to roll initiative.\n"; 
    //cin.ignore(); //ignore the last buffer character.(\n) 
    cin.get();//pause so they can read.
    cout << "Rolling initiative...\n";
    int pInit, mInit; //player and monster initiative.
    
    pInit=d20()+dexSc; //player initiative
    mInit=d20()+zDex; //monster initiative
    
    cout << pName << "'s Initiative: " << pInit << endl;
    cout << monNm << "'s Initiative: " << mInit << endl;
    
    
    if(mInit>pInit){ //display who wins.**********
        cout << monNm << " attacks first.\n\n";//*
    }//                                          *
    else{//                                      *
        cout << pName << " attacks first.\n\n";//*
    }//                                          *
    //********************************************
    cout << "Press Enter to continue.\n";
    cin.get();//pause them here so they have time to read.
    
    
    //begin combat!
    char choice;
    bool cursed=false; //if the enemy is cursed, this is true.
    short feeble=0; //if monster is enfeebled.
    short blind=0; //if monster is blinded.
    short heal=1; //number of times fighter can heal.
    //Orcs have one charge of Relentless Endurance.
    do{ 
        if(mInit>pInit&&(mHlth>0&&cursed==false)){ //Monster attack, provided it has HP left and isn't cursed.
            cout << "Mimic's turn:\n";
            short x=0;//ice breath cooldown counter
               
            //unlike the zombie, the mimic only has one attack.
            cout << "The Mimic tries to bite you. Rolling to hit.\n";\
            hit = d20()+5; //the mimic has a +5 to hit.
            if(blind>0){//if mimic is blinded
                cout << "Mimic is blinded. It must roll at disadvantage.\n";
                blind--;
                hit=d20('d')+5;
            }

            if(hit>=Ac){//if the hit hits the player:
                if(clsNm=="Wizard"&&(sp1>0&&hit<=Ac+5)){ //Wizards have shields, if their spell slots are unused.
                    cout << "You have been hit. Would you like to cast Shield as a first-level spell?\n";
                    cout << "Press 'y' for yes, 'n' for no.";
                    cin >> choice;
                    cin.ignore(); //soaks up the "enter" character you put there after.
                    if(choice=='y'||choice=='Y'){ //if they chose to block attack
                        cout << "You block the attack.\n";
                        sp1--;
                        abj++;
                        if(abj==1){//**************************************************Abjuration health boost.
                            cout << "You have cast your first Abjuration spell. ";
                            pHlth+=(10+intlSc);
                            cout << "You have regained " << 10+intlSc << " hit points.\n\n";
                        }
                        else{
                            cout << "You have cast a first-level Abjuration spell. ";
                            pHlth+=2;
                            cout << "You have regained 2 hit points.\n\n";
                        }
                    }
                    else{//if they didnt choose to block the attack.
                        cout << "You allow the attack to hit.\n";
                        unsigned short dmg1 = d4()+3; //the piercing damage
                        unsigned short dmg2 = d4(); //the acid damage
                        if(feeble>0){ //if monster is enfeebled:
                            pHlth-=(static_cast<float>(dmg1+dmg2)/2);
                            cout << "The " << monNm << " is enfeebled.\n";
                            cout << "You take " << (dmg1)/2 << " piercing damage and " << (dmg2)/2 << " acid damage.\n\n";
                            feeble--;
                        }
                        else{
                            pHlth-=(dmg1+dmg2);
                            cout << "You have been hit.\n";
                            cout << "You take " << dmg1 << " piercing damage and " << dmg2 << " acid damage.\n\n";
                        }

                    }
                }
                else{
                    unsigned short dmg1 = d4()+3; //the piercing damage
                    unsigned short dmg2 = d4(); //the acid damage
                    if(feeble>0){ //if monster is enfeebled:
                        pHlth-=(static_cast<float>(dmg1+dmg2)/2);
                        cout << "The " << monNm << " is enfeebled.\n";
                        cout << "You take " << (dmg1)/2 << " piercing damage and " << (dmg2)/2 << " acid damage.\n\n";
                        feeble--;
                    }
                    else{
                        pHlth-=(dmg1+dmg2);
                        cout << "You have been hit.\n";
                        cout << "You take " << dmg1 << " piercing damage and " << dmg2 << " acid damage.\n\n";
                    }
                }
            }
            else{
                cout << "The attack misses you.\n\n";
            }
            
            
            
            cout << "Press Enter to continue.\n";
            
            cin.get();//pause them here so they have time to read.
            x--; //count down cooldown for ice breath.
        }
        else if((cursed==true&&mHlth>0)&&mInit>pInit){ //if the monster is cursed and is still alive, and has higher initiative.
            cout << "The " << monNm << " is cursed. It will attempt a WIS save.\n";
            short Zsave=d20()+zWis; //make the save.
            if(Zsave>=Dc){//If it's success
                cout << "The " << monNm << " has broken your curse. It can now take turns normally.\n\n";
                cursed=false;
            }
            else{
                cout << "The " << monNm << " has failed to remove your curse.\n\n";
            }
        }
        
        if(pHlth<=0&&(orc==true&&race=="Orc")){//Apply Relentless Endurance, if the player is an Orc.
            orc=false;
            cout << "You have sustained fatal injuries, but as an Orc, you can keep fighting.\n\n";
            pHlth=1;//put their health back at one hit point.
        }

        if(pHlth>0){ //Player attack, if player has HP left.
            cout << pName << "'s turn.\n";
            int choInt;//choice integer, because this menu has double digits.
            if(clsNm=="Wizard"){//the menu for a wizard. 12 spells (13th is shield, which is a reaction.)
                cout << "Your HP: " << setprecision(1) << fixed << pHlth << endl;
                cout << "Spell Slots: " << sp1 << " 1st, " << sp2 << " 2nd, " << sp3 << " 3rd.\n\n";
                cout << "Choose an option: \n";
                cout << "1: Attack with Dagger\n\n";
                cout << "Cantrips (no spell slot needed): \n";
                cout << "2: Fire Bolt (ranged attack, 2d10 fire damage)\n";
                cout << "3: Frostbite (CON save, 2d6+INT cold damage)\n";
                cout << "4: Mind Sliver (INT save, 3d6 psychic damage)\n\n";
                cout << "First Level Spells: \n";
                cout << "5: Burning Hands (DEX save, 3d6 fire damage or half on a successful save)\n";
                cout << "6: Chromatic Orb (ranged attack, 3d8 radiant damage.)\n";
                cout << "7: Witch Bolt (ranged attack, 2d12 lightning damage)\n\n";
                cout << "Second Level Spells:\n";
                cout << "8: Blindness (CON save, enemy spends next 3 rounds with disadvantage on attacks)\n";
                cout << "9: Ray of Enfeeblement (Abjuration, ranged attack, enemy spends 3 turns doing 1/2 damage.)\n";
                cout << "10: Shatter (CON save, 3d8 thunder damage or half with save, constructs roll with disadvantage.)\n";
                cout << "11: Dragon Breath (DEX save, 3d6 fire damage or half on save.)\n\n";
                cout << "Third Level Spells:\n";
                cout << "12: Bestow Curse (WIS save, or enemy loses turns until it succeeds on the save.)\n";
                cout << "13: Fireball (Dex save, 8d6 fire damage or the square root of that on a save.)\n\n";
                
                do{
                    cin >> choInt;
                    switch(choInt){
                        case 1: //dagger
                            { //parentheses are here to fix the case label error that happens if you
                                      //declare variables within cases without parentheses. 
                                cout << "You attempt to stab the " << monNm << " with your dagger.\n";
                                int roll = d20();
                                hit = roll + 3 + dexSc; //add modifiers.
                                if(hit>=monAc){//if attack hits:
                                    cout << "You rolled a " << hit << " and successfully hit.\n";
                                    int dmg=d4()+dexSc; //1d4+DEX damage.
                                    if(roll==20){
                                        cout << "You have rolled at maximum, and have scored a critical hit.\n";
                                        dmg*=2; //multiply damage by 2.
                                    }
                                    mHlth-=(dmg);
                                    cout << "The " << monNm << " takes " << dmg << " piercing damage.\n\n";

                                }
                                else{//if attack misses:
                                    cout << "Your strike misses the " << monNm << "." << endl << endl;
                                }
                            }
                            break; //I left off here. Fix the case label errors********************************
                        case 2: //fire bolt
                            { //parentheses are here to fix the case label error that happens if you
                                      //declare variables within cases without parentheses. 
                                cout << "You cast Fire Bolt as a cantrip.\n";
                                hit = d20() + 3 + intlSc; //add modifiers.
                                if(hit>=monAc){//if attack hits:
                                    cout << "You rolled a " << hit << " and successfully hit.\n";
                                    int dmg=d10()+d10(); //2d10 damage.
                                    mHlth-=(dmg);
                                    cout << "The " << monNm << " takes " << dmg << " fire damage.\n\n";

                                }
                                else{//if attack misses:
                                    cout << "Your Fire Bolt misses the " << monNm << "." << endl << endl;
                                }
                            }
                            
                            break;
                        case 3: //frostbite ***Make this actually work once non ice-type enemies are introduced in proj2.
                            {
                                cout << "You cast Frostbite as a cantrip. The " << monNm << " must make a CON save.\n";
                                short Zsave=d20()+zCon; //make the save.
                                if(Zsave>=Dc){//if the save succeeds:
                                    cout << "The " << monNm << " succeeds on its save and takes no damage.\n";
                                }
                                else{ //if save fails:
                                    int dmg = d6()+d6()+intlSc; //3d6 damage
                                    cout << "The " << monNm << " fails on its save and takes " << dmg << " cold damage.\n\n";
                                    mHlth-=dmg; 
                                }
                            }
                            break;
                        case 4: //mind sliver
                            {
                                cout << "You cast Mind Sliver as a cantrip. The " << monNm << " must make an INT save.\n";
                                short Zsave=d20()+zInt; //make the save.
                                if(Zsave>=Dc){//if the save succeeds:
                                    cout << "The " << monNm << " succeeds on its save and takes no damage.\n";
                                }
                                else{ //if save fails:
                                    int dmg = d6()+d6()+d6(); //3d6 damage
                                    cout << "The " << monNm << " fails on its save and takes " << dmg << " psychic damage.\n\n";
                                    mHlth-=dmg; 
                                }
                            }
                            
                            break;
                        case 5: //burning hands (1)
                            if(sp1<1){ //if they're out of slots
                                cout << "You are out of first level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{//if they have slots.
                                sp1--;
                                cout << "You cast Burning Hands at the first level. The " << monNm << " must make a DEX save.\n";
                                short Zsave=d20()+zDex; //make the save.
                                if(Zsave>=Dc){//if the save succeeds:
                                    int dmg = d6()+d6()+d6(); 
                                    cout << "The " << monNm << " succeeds on its save and takes " << static_cast<float>(dmg)/2 << " fire damage.\n\n";
                                    mHlth-=static_cast<float>(dmg)/2; //not *2 here because a successful save halves damage.
                                }
                                else{ //if save fails:
                                    int dmg = d6()+d6()+d6(); 
                                    //d6 rolls:      1              2              3              4              5             6             7                8
                                    cout << "The "<< monNm <<" fails on its save and takes " << dmg << " fire damage.\n\n";
                                    mHlth-=(dmg); //zombie takes double damage because fire.
                                }
                            }
                            break;
                        case 6: //chromatic orb (1)
                            if(sp1<1){
                                cout << "You are out of first level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{
                                sp1--;
                                cout << "You cast Chromatic Orb at the first level.\n";
                                hit = d20() + 3 + intlSc; //add modifiers.
                                if(hit>=monAc){//if attack hits:
                                    cout << "You rolled a " << hit << " and successfully hit.\n";
                                    int dmg=d8()+d8()+d8(); //3d8 damage.
                                    mHlth-=dmg;
                                    cout << "The " << monNm << " takes " << dmg << " radiant damage.\n\n";
                                    
                                }
                                else{//if attack misses:
                                    cout << "Your Chromatic Orb misses the " << monNm << "." << endl << endl;
                                }

                            }
                            break;
                        case 7: //witch bolt    (1)
                            if(sp1<1){
                                cout << "You are out of first level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{
                                sp1--;
                                cout << "You cast Witch Bolt at the first level.\n";
                                hit = d20() + 3 + intlSc; //add modifiers.
                                if(hit>=monAc){//if attack hits:
                                    cout << "You rolled a " << hit << " and successfully hit.\n";
                                    int dmg=d12()+d12(); //2d12 damage.
                                    mHlth-=dmg;
                                    cout << "The " << monNm << " takes " << dmg << " lightning damage.\n\n";
                                    
                                }
                                else{//if attack misses:
                                    cout << "Your Witch Bolt misses the " << monNm << "." << endl << endl;
                                }

                            }
                            break;
                        case 8: //blindness     (2)
                            if(sp2<1){
                                cout << "You are out of second level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{
                                sp2--;
                                cout << "You cast Blindness at the second level. The " << monNm << " must make a CON save.\n";
                                int save = d20()+zCon; //add modifiers.
                                if(save>=Dc){//if save succeeds
                                    cout << "The " << monNm << " succeeded on its save and is not blinded.\n\n";
                                }
                                else{//if save fails
                                    cout << "The " << monNm << " failed its save and is blinded for 3 turns.\n\n";
                                    blind=2; //put the blindness on.
                                    
                                }
                            }
                            break;
                        case 9: //enfeeblement  (2)
                            if(sp2<1){
                                cout << "You are out of second level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{
                                sp2--;
                                abj++;
                                if(abj==1){//**************************************************Abjuration health boost.
                                    cout << "You have cast your first Abjuration spell. ";
                                    pHlth+=(10+intlSc);
                                    cout << "You have regained " << 10+intlSc << " hit points.\n\n";
                                }
                                else{
                                    cout << "You have cast a second-level Abjuration spell. ";
                                    pHlth+=4;
                                    cout << "You have regained 4 hit points.\n\n";
                                }
                                cout << "You cast Ray of Enfeeblement at the second level. ";
                                int atk = d20() + 3 + intlSc; //add modifiers.
                                if(atk>=monAc){//if attack hits:
                                    cout << "You rolled a " << atk << " and successfully hit. The " << monNm <<" is now Enfeebled for 3 turns.\n";
                                    feeble=3;
                                    //I left off here. Make sure "feeble" goes into monster attacks and reduces them.
                                }
                                else{//if attack misses:
                                    cout << "Your Ray of Enfeeblement misses the " << monNm << endl << endl;
                                }
                                
                            }
                            break;
                        case 10://shatter       (2)
                            if(sp2<1){
                                cout << "You are out of second level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{
                                sp2--;
                                cout << "You cast Shatter at the second level. The " << monNm << " must make a CON save.\n";
                                cout << "Press Enter to continue.\n";
                                cin.ignore();
                                cin.get(); //pause to let them read.
                                short Zsave=d20()+zCon; //make the dexterity save.
                                if(Zsave>=Dc){//if the save succeeds:
                                    int dmg = d8()+d8()+d8(); 
                                    float hfDmg = static_cast<float>(dmg)/2;
                                    //d8 rolls:      1              2              3        
                                    cout << "The " << monNm << " succeeds on its save and takes " << hfDmg << " thunder damage.\n\n";
                                    mHlth-=hfDmg; 
                                }
                                else{ //if save fails:
                                    int dmg = d8()+d8()+d8(); 
                                    //d8 rolls:      1              2              3            
                                    cout << "The "<< monNm <<" fails on its save and takes " << dmg << " thunder damage.\n\n";
                                    mHlth-=dmg; 
                                }
                            }
                            break;
                        case 11://dragon breath (2) 
                            if(sp2<1){
                                cout << "You are out of second level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{
                                sp2--;
                                cout << "You cast Dragon Breath at the second level. The " << monNm << " must make a DEX save.\n";
                                cout << "Press Enter to continue.\n";
                                cin.ignore();
                                cin.get(); //pause to let them read.
                                short Zsave=d20()+zDex; //make the dexterity save.
                                if(Zsave>=Dc){//if the save succeeds:
                                    int dmg = d6()+d6()+d6(); 
                                    //d6 rolls:      1              2              3        
                                    cout << "The " << monNm << " succeeds on its save and takes " << static_cast<float>(dmg)/2 << " fire damage.\n\n";
                                    mHlth-=(static_cast<float>(dmg)/2); //not *2 here because a successful save halves damage.
                                }
                                else{ //if save fails:
                                    int dmg = d6()+d6()+d6(); 
                                    //d6 rolls:      1              2              3            
                                    cout << "The "<< monNm <<" fails on its save and takes " << dmg << " fire damage.\n\n";
                                    mHlth-=(dmg); //zombie takes double damage because fire.
                                }
                            }
                            break;
                        case 12://bestow curse  (3)
                            if(sp3<1){ //if they're out of slots
                                cout << "You are out of third level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{//if they have slots.
                                sp3--;
                                cout << "You cast Bestow Curse at the third level. The " << monNm << " must make a WIS save.\n";
                                cout << "Press Enter to continue.\n";
                                cin.ignore();
                                cin.get(); //pause to let them read.
                                short Zsave=d20()+zWis; //make the wisdom save.
                                if(Zsave>=Dc){//if save succeeds
                                    cout << "The "  << monNm << " has successfully made the save. No effect is had.\n\n";
                                }
                                else{
                                    cout << "The "  << monNm << " has failed the save. It will lose turns until it can make the save.\n\n";
                                    cursed = true;
                                }
                            }
                            break;
                        case 13://fireball      (3) //frost zombies take 2x damage from fire.
                            if(sp3<1){ //if they're out of slots
                                cout << "You are out of third level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{//if they have slots.
                                sp3--;
                                cout << "You cast Fireball at the third level. The " << monNm << " must make a DEX save.\n";
                                short Zsave=d20()+zDex; //make the save.
                                if(Zsave>=Dc){//if the save succeeds:
                                    int dmg = d6()+d6()+d6()+d6()+d6()+d6()+ d6()+d6(); 
                                    cout << "The " << monNm << " succeeds on its save and takes " << sqrt(static_cast<float>(dmg)) << " fire damage.\n\n";
                                    mHlth-=sqrt(static_cast<float>(dmg)); //the x2 is for the fire vulnerability.
                                }
                                else{ //if save fails:
                                    int dmg = d6()+d6()+d6()+d6()+d6()+d6()+ d6()+d6(); 
                                    cout << "The "<< monNm <<" fails on its save and takes " << dmg << " fire damage.\n\n";
                                    mHlth-=(dmg); //zombie takes double damage because fire.
                                }
                            }
                            break;
                        default:
                            cout << "Invalid choice. Please choose a number from 1 to 13.\n\n";
                    }
                }while(choInt>13||choInt<1);//keep repeating until they get the hint and choose a better number.
                cout << "Press enter to continue.\n";
                cin.ignore();
                cin.get(); //pause to let them read.
                
            }
            else{//the menu for a fighter.
                for(int i=2;i>0;i--){//repeats 2 times, for the fighter's 2 attacks.
                    if(i==1){//if this is the second attack:
                        cout << "You can attack again.\n";
                    }
                    
                    //Fighter Menu:
                    cout << "Your HP: " << setprecision(1) << fixed << pHlth << endl;
                    cout << "You have " << heal << " health packs left.\n\n";
                    cout << "Choose an option: \n";
                    cout << "1: Attack with Longsword\n";
                    cout << "2: Attack with Crossbow\n";
                    cout << "3: Heal 1d10+5 hit points;\n\n";
                    do{
                        cin >> choInt;
                        switch(choInt){
                            case 1: //sword
                                cout << "You take a swing at the " << monNm << ".\n";
                                hit = d20() + 3 + strSc; //add modifiers.
                                if(hit>=monAc){//if attack hits:
                                    cout << "You rolled a " << hit << " and successfully hit.\n";
                                    int dmg=d8()+strSc; //1d8+STR damage.
                                    mHlth-=dmg;
                                    cout << "The " << monNm << " takes " << dmg << " slashing damage.\n\n";
                                }
                                else{//if attack misses:
                                    cout << "Your sword misses the " << monNm << "." << endl << endl;
                                }
                                break;
                            case 2: //bow
                                if(arrow<=0){//if they have no more arrows
                                    cout << "Your quiver is empty. Choose another option.\n";
                                    choInt=5;//repeat the loop.
                                }
                                else{
                                    arrow--;//remove an arrow from the quiver.
                                    cout << "You take a shot at the " << monNm << ".\n";
                                    hit = d20() + 3 + dexSc; //add modifiers.
                                    if(hit>=monAc){//if attack hits:
                                        cout << "You rolled a " << hit << " and successfully hit.\n";
                                        int dmg=d6()+dexSc; //1d6+DEX damage.
                                        mHlth-=dmg;
                                        cout << "The " << monNm << " takes " << dmg << " piercing damage.\n\n";

                                    }
                                    else{//if attack misses:
                                        cout << "Your arrow misses the " << monNm << "." << endl << endl;
                                    }
                                }
                                break;
                            case 3:
                                if(heal<1){
                                    cout << "You have already used your healing. Choose another option.\n";
                                }
                                else{
                                    heal--;
                                    int dmgNg=d10()+5;//healing, or "negative damage"
                                    pHlth+=dmgNg; //1d10+5 healing.
                                    cout << "You heal for " << dmgNg << " hit points. Now, choose an attack, or you can heal again if you have any health packs.\n\n";
                                }
                                break;
                            default:
                                cout << "Invalid choice. Please choose a number from 1 to 3.\n\n";
                        }
                        
                    }while(choInt<1||choInt>2); //keep repeating if they choose an invalid option, or if they heal.
                    
                }
                cout << "Press enter to continue.\n";
                cin.ignore();
                cin.get(); //pause to let them read.
            }
            
        }
        
        
        
        //Monster's attack, if it rolled less initiative.
        if(mInit<pInit&&(mHlth>0&&cursed==false)){ //Monster attack, provided it has HP left and isn't cursed.
            cout << "Mimic's turn:\n";
            short x=0;//ice breath cooldown counter
               
            //unlike the zombie, the mimic only has one attack.
            cout << "The Mimic tries to bite you. Rolling to hit.\n";\
            hit = d20()+5; //the mimic has a +5 to hit.
            if(blind>0){//if mimic is blinded
                cout << "Mimic is blinded. It must roll at disadvantage.\n";
                blind--;
                hit=d20('d')+5;
            }

            if(hit>=Ac){//if the hit hits the player:
                if(clsNm=="Wizard"&&(sp1>0&&hit<=Ac+5)){ //Wizards have shields, if their spell slots are unused.
                    cout << "You have been hit. Would you like to cast Shield as a first-level spell?\n";
                    cout << "Press 'y' for yes, 'n' for no.";
                    cin >> choice;
                    cin.ignore(); //soaks up the "enter" character you put there after.
                    if(choice=='y'||choice=='Y'){ //if they chose to block attack
                        cout << "You block the attack.\n";
                        sp1--;
                        abj++;
                        if(abj==1){//**************************************************Abjuration health boost.
                            cout << "You have cast your first Abjuration spell. ";
                            pHlth+=(10+intlSc);
                            cout << "You have regained " << 10+intlSc << " hit points.\n\n";
                        }
                        else{
                            cout << "You have cast a first-level Abjuration spell. ";
                            pHlth+=2;
                            cout << "You have regained 2 hit points.\n\n";
                        }
                    }
                    else{//if they didnt choose to block the attack.
                        cout << "You allow the attack to hit.\n";
                        unsigned short dmg1 = d4()+3; //the piercing damage
                        unsigned short dmg2 = d4(); //the acid damage
                        if(feeble>0){ //if monster is enfeebled:
                            pHlth-=(static_cast<float>(dmg1+dmg2)/2);
                            cout << "The " << monNm << " is enfeebled.\n";
                            cout << "You take " << (dmg1)/2 << " piercing damage and " << (dmg2)/2 << " acid damage.\n\n";
                            feeble--;
                        }
                        else{
                            pHlth-=(dmg1+dmg2);
                            cout << "You have been hit.\n";
                            cout << "You take " << dmg1 << " piercing damage and " << dmg2 << " acid damage.\n\n";
                        }

                    }
                }
                else{
                    unsigned short dmg1 = d4()+3; //the piercing damage
                    unsigned short dmg2 = d4(); //the acid damage
                    if(feeble>0){ //if monster is enfeebled:
                        pHlth-=(static_cast<float>(dmg1+dmg2)/2);
                        cout << "The " << monNm << " is enfeebled.\n";
                        cout << "You take " << (dmg1)/2 << " piercing damage and " << (dmg2)/2 << " acid damage.\n\n";
                        feeble--;
                    }
                    else{
                        pHlth-=(dmg1+dmg2);
                        cout << "You have been hit.\n";
                        cout << "You take " << dmg1 << " piercing damage and " << dmg2 << " acid damage.\n\n";
                    }
                }
            }
            else{
                cout << "The attack misses you.\n\n";
            }
            
            
            
            cout << "Press Enter to continue.\n";
            
            cin.get();//pause them here so they have time to read.
            x--; //count down cooldown for ice breath.
        }
        else if((cursed==true&&mHlth>0)&&mInit<pInit){ //if the monster is cursed and is still alive, and has lower initiative.
            cout << "The " << monNm << " is cursed. It will attempt a WIS save.\n";
            short Zsave=d20()+zWis; //make the save.
            if(Zsave>=Dc){//If it's success
                cout << "The " << monNm << " has broken your curse. It can now take turns normally.\n\n";
                cursed=false;
            }
            else{
                cout << "The " << monNm << " has failed to remove your curse.\n\n";
            }
        }
        
        if(pHlth<=0&&(orc==true&&race=="Orc")){//Apply Relentless Endurance, if the player is an Orc.
            orc=false;
            cout << "You have sustained fatal injuries, but as an Orc, you can keep fighting.\n\n";
            pHlth=1;//put their health back at one hit point.
        }
        
        
        
    }while(pHlth>0&&mHlth>0); //keep fighting, to the death.
    
    if(pHlth<=0){//if the player has died:
        cout << "You have been slain by the " << monNm << ". Game over.\n";
    }
    else if(mHlth<=0){
        cout << "You have slain the " << monNm << ". You proceed further into the dungeon.\n";
    }
    
    
}

void archer(float &pHlth, short strSc, short conSc, short dexSc, short wisSc, short intlSc, short chaSc, string pName, string clsNm, string race,short &sp1, short &sp2, short &sp3, short &abj,unsigned short Ac, unsigned short Dc,short &arrow, bool &orc){ //the fight with the zombie.
    
    cout << "You walk into a large empty arena. Across a large chasm in the floor, there stands what appears to be a slender metal statue.\n";
    //Initialize archer stats.
    short zStr=0,zCon=3,zDex=5,zWis=3,zInt=3,zCha=0;//zombie modifiers
    int hit; //the archer's rolls to hit, and also, your rolls to hit. Depends on who's currently doing their turn.
    string monNm="Archer";
    short monAc=15;
    short mHlth=70; // the archer starts with 70 hit points.
    
    
    cout << "You take a good look at the thing. At its side, it holds a steel longbow, and over its shoulder is a leather quiver.\n";
    cout << "But it is the statue's face that draws your attention. An uncanny thing, the face has no eyes, possessing\n";
    cout << "only a sharp metal nose above its thin, villainous lips, which are twisted into a wicked smile.\n";
    cout << "In your admiration of the statue, you fail to recognize a stone pressure plate on the ground.\n";
    cout << "As you step forth, you hear the abrasive grind of metal against metal, and the statue\n";
    cout << "darts into action, notching an arrow and taking aim.\n\n";
    if(clsNm=="Fighter"){
        cout << "In observing the Archer's catlike grace, you become inspired. Simply by watching the thing, you yourself can now shoot a little better.\n\n";
    }
    cout << "Press Enter to roll initiative.\n"; 
    //cin.ignore(); //ignore the last buffer character.(\n) 
    cin.get();//pause so they can read.
    cout << "Rolling initiative...\n";
    int pInit, mInit; //player and monster initiative.
    
    pInit=d20()+dexSc; //player initiative
    mInit=d20()+zDex; //monster initiative
    
    cout << pName << "'s Initiative: " << pInit << endl;
    cout << monNm << "'s Initiative: " << mInit << endl;
    
    
    if(mInit>pInit){ //display who wins.**********
        cout << monNm << " attacks first.\n\n";//*
    }//                                          *
    else{//                                      *
        cout << pName << " attacks first.\n\n";//*
    }//                                          *
    //********************************************
    cout << "Press Enter to continue.\n";
    cin.get();//pause them here so they have time to read.
    
    
    //begin combat!
    char choice;
    bool cursed=false; //if the enemy is cursed, this is true.
    short feeble=0; //if monster is enfeebled.
    short blind=0; //if monster is blinded.
    short heal=1; //number of times fighter can heal.
    //Orcs have one charge of Relentless Endurance.
    do{ 
        if(mInit>pInit&&(mHlth>0&&cursed==false)){ //Monster attack, provided it has HP left and isn't cursed.
            cout << "Archer's turn:\n";
            short x=0;//cooldown counter
            if(prob()&&x<=0){ //bomb weapon. (six round cooldown.)
                x=6;
                cout << "The Archer attacks with a bomb arrow.\nPress Enter to roll a CON save, DC 13.\n";
                cin.get();//pause so they can read.
                cout << "Rolling CON save: ";
                short save=d20()+conSc;
                if(race=="Dwarf"){ //If our player is a Dwarf, apply the con advantage.
                    save=d20('a')+conSc;
                }
                cout << save << endl;
                if(save<13){ //***************************failed save
                    int dmg =d6()+d6()+d6()+d6();
                    if(feeble>0){ //if monster is enfeebled
                        pHlth=pHlth-(static_cast<float>(dmg)/2);
                        cout << "You failed your CON save.\n";
                        cout << "The " << monNm << " is enfeebled.\n";
                        cout << "You take " << setprecision(1) << fixed << static_cast<float>(dmg)/2 << " explosive damage.\n\n";
                    }
                    else{
                        pHlth=pHlth-(dmg);
                        cout << "You failed your CON save.\n";
                        cout << "You take " << dmg << " explosive damage.\n\n";
                    }
                }
                else{//***********************************succeeded save
                    int dmg =d6()+d6()+d6()+d6();
                    if(feeble>0){ //if monster is enfeebled:
                        pHlth=pHlth-(static_cast<float>(dmg)/4);
                        cout << "You succeeded in your CON save.\n";
                        cout << "The " << monNm << " is enfeebled.\n";
                        cout << "You take half damage: " << setprecision(1) << fixed << (static_cast<float>(dmg)/4) << " explosive damage.\n\n";
                    }
                    else{
                        pHlth=pHlth-(static_cast<float>(dmg)/2);
                        cout << "You succeeded in your CON save.\n";
                        cout << "You take half damage: " << setprecision(1) << fixed << (static_cast<float>(dmg)/2) << " explosive damage.\n\n";
                    }
                    
                }
                
            }   
            else{ //club attack.
                cout << "The Archer tries to shoot you. Rolling to hit.\n";\
                hit = d20()+5; //the zombie has a +5 to hit.
                if(blind>0){//if zombie is blinded
                    cout << "The Archer is blinded. It must roll at disadvantage.\n";
                    blind--;
                    hit=d20('d')+5;
                }
                
                if(hit>=Ac){//if the hit hits the player:
                    if(clsNm=="Wizard"&&(sp1>0&&hit<=Ac+5)){ //Wizards have shields, if their spell slots are unused.
                        cout << "You have been hit. Would you like to cast Shield as a first-level spell?\n";
                        cout << "Press 'y' for yes, 'n' for no.";
                        cin >> choice;
                        cin.ignore(); //soaks up the "enter" character you put there after.
                        if(choice=='y'||choice=='Y'){ //if they chose to block attack
                            cout << "You block the attack.\n";
                            sp1--;
                            abj++;
                            if(abj==1){//**************************************************Abjuration health boost.
                                cout << "You have cast your first Abjuration spell. ";
                                pHlth+=(10+intlSc);
                                cout << "You have regained " << 10+intlSc << " hit points.\n\n";
                            }
                            else{
                                cout << "You have cast a first-level Abjuration spell. ";
                                pHlth+=2;
                                cout << "You have regained 2 hit points.\n\n";
                            }
                        }
                        else{//if they didnt choose to block the attack.
                            cout << "You allow the attack to hit.\n";
                            int dmg1 = d8()+3; //the piercing damage
                            int dmg2 = d12(); //the poison damage
                            if(race=="Dwarf"){
                                int dmg2 = d6(); //the poison damage (dwarves take less of it)
                            }
                            if(feeble>0){ //if monster is enfeebled:
                                pHlth-=(static_cast<float>(dmg1+dmg2)/2);
                                cout << "The " << monNm << " is enfeebled.\n";
                                cout << "You take " << (dmg1)/2 << " piercing damage and " << (dmg2)/2 << " poison damage.\n\n";
                                feeble--;
                            }
                            else{
                                pHlth-=(dmg1+dmg2);
                                cout << "You have been hit.\n";
                                cout << "You take " << dmg1 << " piercing damage and " << dmg2 << " poison damage.\n\n";
                            }

                        }
                    }
                    else{
                        cout << "The attack hits.\n";
                        int dmg1 = d8()+3; //the piercing damage
                        int dmg2 = d12(); //the poison damage
                        if(race=="Dwarf"){
                            int dmg2 = d6(); //the poison damage (dwarves take less of it)
                        }
                        if(feeble>0){ //if monster is enfeebled:
                            pHlth-=(static_cast<float>(dmg1+dmg2)/2);
                            cout << "The " << monNm << " is enfeebled.\n";
                            cout << "You take " << (dmg1)/2 << " piercing damage and " << (dmg2)/2 << " poison damage.\n\n";
                            feeble--;
                        }
                        else{
                            pHlth-=(dmg1+dmg2);
                            cout << "You have been hit.\n";
                            cout << "You take " << dmg1 << " piercing damage and " << dmg2 << " poison damage.\n\n";
                        }
                    }
                }
                else{
                    cout << "The attack misses you.\n\n";
                }
            }
            
            
            cout << "Press Enter to continue.\n";
            
            cin.get();//pause them here so they have time to read.
            x--; //count down cooldown for ice breath.
        }
        else if((cursed==true&&mHlth>0)&&mInit>pInit){ //if the monster is cursed and is still alive, and has higher initiative.
            cout << "The " << monNm << " is cursed. It will attempt a WIS save.\n";
            short Zsave=d20()+zWis; //make the save.
            if(Zsave>=Dc){//If it's success
                cout << "The " << monNm << " has broken your curse. It can now take turns normally.\n\n";
                cursed=false;
            }
            else{
                cout << "The " << monNm << " has failed to remove your curse.\n\n";
            }
        }
        
        if(pHlth<=0&&(orc==true&&race=="Orc")){//Apply Relentless Endurance, if the player is an Orc.
            orc=false;
            cout << "You have sustained fatal injuries, but as an Orc, you can keep fighting.\n\n";
            pHlth=1;//put their health back at one hit point.
        }

        if(pHlth>0){ //Player attack, if player has HP left.
            cout << pName << "'s turn.\n";
            int choInt;//choice integer, because this menu has double digits.
            if(clsNm=="Wizard"){//the menu for a wizard. 12 spells (13th is shield, which is a reaction.)
                cout << "Your HP: " << setprecision(1) << fixed << pHlth << endl;
                cout << "Spell Slots: " << sp1 << " 1st, " << sp2 << " 2nd, " << sp3 << " 3rd.\n\n";
                cout << "Choose an option: \n";
                cout << "1: Attack with Dagger\n\n";
                cout << "Cantrips (no spell slot needed): \n";
                cout << "2: Fire Bolt (ranged attack, 2d10 fire damage)\n";
                cout << "3: Frostbite (CON save, 2d6+INT cold damage)\n";
                cout << "4: Mind Sliver (INT save, 3d6 psychic damage)\n\n";
                cout << "First Level Spells: \n";
                cout << "5: Burning Hands (DEX save, 3d6 fire damage or half on a successful save)\n";
                cout << "6: Chromatic Orb (ranged attack, 3d8 radiant damage.)\n";
                cout << "7: Witch Bolt (ranged attack, 2d12 lightning damage)\n\n";
                cout << "Second Level Spells:\n";
                cout << "8: Blindness (CON save, enemy spends next 3 rounds with disadvantage on attacks)\n";
                cout << "9: Ray of Enfeeblement (Abjuration, ranged attack, enemy spends 3 turns doing 1/2 damage.)\n";
                cout << "10: Shatter (CON save, 3d8 thunder damage or half with save, constructs roll with disadvantage.)\n";
                cout << "11: Dragon Breath (DEX save, 3d6 fire damage or half on save.)\n\n";
                cout << "Third Level Spells:\n";
                cout << "12: Bestow Curse (WIS save, or enemy loses turns until it succeeds on the save.)\n";
                cout << "13: Fireball (Dex save, 8d6 fire damage or the square root of that on a save.)\n\n";
                
                do{
                    cin >> choInt;
                    switch(choInt){
                        case 1: //dagger
                            cout << "The Archer is too far away to be stabbed. Choose something else.\n";
                            choInt=15;
                            break; //I left off here. Fix the case label errors********************************
                        case 2: //fire bolt
                            { //parentheses are here to fix the case label error that happens if you
                                      //declare variables within cases without parentheses. 
                                cout << "You cast Fire Bolt as a cantrip.\n";
                                hit = d20() + 3 + intlSc; //add modifiers.
                                if(hit>=monAc){//if attack hits:
                                    cout << "You rolled a " << hit << " and successfully hit.\n";
                                    int dmg=d10()+d10(); //2d10 damage.
                                    mHlth-=(dmg);
                                    cout << "The " << monNm << " takes " << dmg << " fire damage.\n\n";

                                }
                                else{//if attack misses:
                                    cout << "Your Fire Bolt misses the " << monNm << "." << endl << endl;
                                }
                            }
                            
                            break;
                        case 3: //frostbite ***Make this actually work once non ice-type enemies are introduced in proj2.
                            {
                                cout << "You cast Frostbite as a cantrip. The " << monNm << " must make a CON save.\n";
                                short Zsave=d20()+zCon; //make the save.
                                if(Zsave>=Dc){//if the save succeeds:
                                    cout << "The " << monNm << " succeeds on its save and takes no damage.\n";
                                }
                                else{ //if save fails:
                                    int dmg = d6()+d6()+intlSc; //3d6 damage
                                    cout << "The " << monNm << " fails on its save and takes " << dmg << " cold damage.\n\n";
                                    mHlth-=dmg; 
                                }
                            }
                            break;
                        case 4: //mind sliver
                            {
                                cout << "You cast Mind Sliver as a cantrip. The " << monNm << " must make an INT save.\n";
                                short Zsave=d20()+zInt; //make the save.
                                if(Zsave>=Dc){//if the save succeeds:
                                    cout << "The " << monNm << " succeeds on its save and takes no damage.\n";
                                }
                                else{ //if save fails:
                                    int dmg = d6()+d6()+d6(); //3d6 damage
                                    cout << "The " << monNm << " fails on its save and takes " << dmg << " psychic damage.\n\n";
                                    mHlth-=dmg; 
                                }
                            }
                            
                            break;
                        case 5: //burning hands (1)
                            if(sp1<1){ //if they're out of slots
                                cout << "You are out of first level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{//if they have slots.
                                sp1--;
                                cout << "You cast Burning Hands at the first level. The " << monNm << " must make a DEX save.\n";
                                short Zsave=d20()+zDex; //make the save.
                                if(Zsave>=Dc){//if the save succeeds:
                                    int dmg = d6()+d6()+d6(); 
                                    cout << "The " << monNm << " succeeds on its save and takes " << static_cast<float>(dmg)/2 << " fire damage.\n\n";
                                    mHlth-=static_cast<float>(dmg)/2; //not *2 here because a successful save halves damage.
                                }
                                else{ //if save fails:
                                    int dmg = d6()+d6()+d6(); 
                                    //d6 rolls:      1              2              3              4              5             6             7                8
                                    cout << "The "<< monNm <<" fails on its save and takes " << dmg << " fire damage.\n\n";
                                    mHlth-=(dmg); //zombie takes double damage because fire.
                                }
                            }
                            break;
                        case 6: //chromatic orb (1)
                            if(sp1<1){
                                cout << "You are out of first level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{
                                sp1--;
                                cout << "You cast Chromatic Orb at the first level.\n";
                                hit = d20() + 3 + intlSc; //add modifiers.
                                if(hit>=monAc){//if attack hits:
                                    cout << "You rolled a " << hit << " and successfully hit.\n";
                                    int dmg=d8()+d8()+d8(); //3d8 damage.
                                    mHlth-=dmg;
                                    cout << "The " << monNm << " takes " << dmg << " radiant damage.\n\n";
                                    
                                }
                                else{//if attack misses:
                                    cout << "Your Chromatic Orb misses the " << monNm << "." << endl << endl;
                                }

                            }
                            break;
                        case 7: //witch bolt    (1)
                            if(sp1<1){
                                cout << "You are out of first level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{
                                sp1--;
                                cout << "You cast Witch Bolt at the first level.\n";
                                hit = d20() + 3 + intlSc; //add modifiers.
                                if(hit>=monAc){//if attack hits:
                                    cout << "You rolled a " << hit << " and successfully hit.\n";
                                    int dmg=d12()+d12(); //2d12 damage.
                                    mHlth-=dmg;
                                    cout << "The " << monNm << " takes " << dmg << " lightning damage.\n\n";
                                    
                                }
                                else{//if attack misses:
                                    cout << "Your Witch Bolt misses the " << monNm << "." << endl << endl;
                                }

                            }
                            break;
                        case 8: //blindness     (2)
                            if(sp2<1){
                                cout << "You are out of second level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{
                                sp2--;
                                cout << "You cast Blindness at the second level. The " << monNm << " must make a CON save.\n";
                                int save = d20()+zCon; //add modifiers.
                                if(save>=Dc){//if save succeeds
                                    cout << "The " << monNm << " succeeded on its save and is not blinded.\n\n";
                                }
                                else{//if save fails
                                    cout << "The " << monNm << " failed its save and is blinded for 3 turns.\n\n";
                                    blind=2; //put the blindness on.
                                    
                                }
                            }
                            break;
                        case 9: //enfeeblement  (2)
                            if(sp2<1){
                                cout << "You are out of second level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{
                                sp2--;
                                abj++;
                                if(abj==1){//**************************************************Abjuration health boost.
                                    cout << "You have cast your first Abjuration spell. ";
                                    pHlth+=(10+intlSc);
                                    cout << "You have regained " << 10+intlSc << " hit points.\n\n";
                                }
                                else{
                                    cout << "You have cast a second-level Abjuration spell. ";
                                    pHlth+=4;
                                    cout << "You have regained 4 hit points.\n\n";
                                }
                                cout << "You cast Ray of Enfeeblement at the second level. ";
                                int atk = d20() + 3 + intlSc; //add modifiers.
                                if(atk>=monAc){//if attack hits:
                                    cout << "You rolled a " << atk << " and successfully hit. The " << monNm <<" is now Enfeebled for 3 turns.\n";
                                    feeble=3;
                                    //I left off here. Make sure "feeble" goes into monster attacks and reduces them.
                                }
                                else{//if attack misses:
                                    cout << "Your Ray of Enfeeblement misses the " << monNm << endl << endl;
                                }
                                
                            }
                            break;
                        case 10://shatter       (2)
                            if(sp2<1){
                                cout << "You are out of second level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{
                                sp2--;
                                cout << "You cast Shatter at the second level. The " << monNm << " must make a CON save.\n";
                                cout << "Press Enter to continue.\n";
                                cin.ignore();
                                cin.get(); //pause to let them read.
                                short Zsave=d20('d')+zCon; //make the dexterity save.
                                if(Zsave>=Dc){//if the save succeeds:
                                    int dmg = d8()+d8()+d8(); 
                                    float hfDmg = static_cast<float>(dmg)/2;
                                    //d8 rolls:      1              2              3        
                                    cout << "The " << monNm << " succeeds on its save and takes " << hfDmg << " thunder damage.\n\n";
                                    mHlth-=hfDmg; 
                                }
                                else{ //if save fails:
                                    int dmg = d8()+d8()+d8(); 
                                    //d8 rolls:      1              2              3            
                                    cout << "The "<< monNm <<" fails on its save and takes " << dmg << " thunder damage.\n\n";
                                    mHlth-=dmg; 
                                }
                            }
                            break;
                        case 11://dragon breath (2) //frost zombies take 2x damage from fire.
                            if(sp2<1){
                                cout << "You are out of second level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{
                                sp2--;
                                cout << "You cast Dragon Breath at the second level. The " << monNm << " must make a DEX save.\n";
                                cout << "Press Enter to continue.\n";
                                cin.ignore();
                                cin.get(); //pause to let them read.
                                short Zsave=d20()+zDex; //make the dexterity save.
                                if(Zsave>=Dc){//if the save succeeds:
                                    int dmg = d6()+d6()+d6(); 
                                    //d6 rolls:      1              2              3        
                                    cout << "The " << monNm << " succeeds on its save and takes " << static_cast<float>(dmg)/2 << " fire damage.\n\n";
                                    mHlth-=static_cast<float>(dmg)/2; //not *2 here because a successful save halves damage.
                                }
                                else{ //if save fails:
                                    int dmg = d6()+d6()+d6(); 
                                    //d6 rolls:      1              2              3            
                                    cout << "The "<< monNm <<" fails on its save and takes " << dmg << " fire damage.\n\n";
                                    mHlth-=(dmg); //zombie takes double damage because fire.
                                }
                            }
                            break;
                        case 12://bestow curse  (3)
                            if(sp3<1){ //if they're out of slots
                                cout << "You are out of third level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{//if they have slots.
                                sp3--;
                                cout << "You cast Bestow Curse at the third level. The " << monNm << " must make a WIS save.\n";
                                cout << "Press Enter to continue.\n";
                                cin.ignore();
                                cin.get(); //pause to let them read.
                                short Zsave=d20()+zWis; //make the wisdom save.
                                if(Zsave>=Dc){//if save succeeds
                                    cout << "The "  << monNm << " has successfully made the save. No effect is had.\n\n";
                                }
                                else{
                                    cout << "The "  << monNm << " has failed the save. It will lose turns until it can make the save.\n\n";
                                    cursed = true;
                                }
                            }
                            break;
                        case 13://fireball      (3) //frost zombies take 2x damage from fire.
                            if(sp3<1){ //if they're out of slots
                                cout << "You are out of third level spell slots! Choose another spell.\n\n";
                                choInt=15;//repeat the loop.
                            }
                            else{//if they have slots.
                                sp3--;
                                cout << "You cast Fireball at the third level. The " << monNm << " must make a DEX save.\n";
                                short Zsave=d20()+zDex; //make the save.
                                if(Zsave>=Dc){//if the save succeeds:
                                    int dmg = d6()+d6()+d6()+d6()+d6()+d6()+ d6()+d6(); 
                                    cout << "The " << monNm << " succeeds on its save and takes " << sqrt(static_cast<float>(dmg)) << " fire damage.\n\n";
                                    mHlth-=sqrt(static_cast<float>(dmg)); //the x2 is for the fire vulnerability.
                                }
                                else{ //if save fails:
                                    int dmg = d6()+d6()+d6()+d6()+d6()+d6()+ d6()+d6(); 
                                    cout << "The "<< monNm <<" fails on its save and takes " << dmg << " fire damage.\n\n";
                                    mHlth-=(dmg); //zombie takes double damage because fire.
                                }
                            }
                            break;
                        default:
                            cout << "Invalid choice. Please choose a number from 1 to 13.\n\n";
                    }
                }while(choInt>13||choInt<1);//keep repeating until they get the hint and choose a better number.
                cout << "Press enter to continue.\n";
                cin.ignore();
                cin.get(); //pause to let them read.
                
            }
            else{//the menu for a fighter.
                for(int i=2;i>0;i--){//repeats 2 times, for the fighter's 2 attacks.
                    if(i==1){//if this is the second attack:
                        cout << "You can attack again.\n";
                    }
                    
                    //Fighter Menu:
                    cout << "Your HP: " << setprecision(1) << fixed << pHlth << endl;
                    cout << "You have " << heal << " health packs left.\n\n";
                    cout << "Choose an option: \n";
                    cout << "1: Attack with Longsword\n";
                    cout << "2: Attack with Crossbow\n";
                    cout << "3: Heal 1d10+5 hit points;\n\n";
                    do{
                        cin >> choInt;
                        switch(choInt){
                            case 1: //sword
                                cout << "The Archer is too far away to fight with a sword. Choose something else.\n";
                                choInt=4;
                                break;
                            case 2: //bow
                                if(arrow<=0){//if they have no more arrows
                                    cout << "Your quiver is empty. You cannot keep fighting the Archer, so you flee, leaving you\n";
                                    cout << "to the mercy of the bitter cold. You do not survive much longer.";
                                    pHlth=0;
                                }
                                else{
                                    arrow--;//remove an arrow from the quiver.
                                    cout << "You take a shot at the " << monNm << ".\n";
                                    hit = d20() + 3 + dexSc; //add modifiers.
                                    if(hit>=monAc){//if attack hits:
                                        cout << "You rolled a " << hit << " and successfully hit.\n";
                                        int dmg=d20()+dexSc; //1d6+DEX damage.
                                        mHlth-=dmg;
                                        cout << "The " << monNm << " takes " << dmg << " piercing damage.\n\n";

                                    }
                                    else{//if attack misses:
                                        cout << "Your arrow misses the " << monNm << "." << endl << endl;
                                    }
                                }
                                break;
                            case 3:
                                if(heal<1){
                                    cout << "You have already used your healing. Choose another option.\n";
                                }
                                else{
                                    heal--;
                                    int dmgNg=d10()+5;//healing, or "negative damage"
                                    pHlth+=dmgNg; //1d10+5 healing.
                                    cout << "You heal for " << dmgNg << " hit points. Now, choose an attack, or you can heal again if you have any health packs.\n\n";
                                }
                                break;
                            default:
                                cout << "Invalid choice. Please choose a number from 1 to 3.\n\n";
                        }
                        
                    }while(choInt<1||choInt>2); //keep repeating if they choose an invalid option, or if they heal.
                    
                }
                cout << "Press enter to continue.\n";
                cin.ignore();
                cin.get(); //pause to let them read.
            }
            
        }
        
        
        
        //Monster's attack, if it rolled less initiative.
        if(mInit<pInit&&(mHlth>0&&cursed==false)){ //Monster attack, provided it has HP left and isn't cursed.
            cout << "Archer's turn:\n";
            short x=0;//cooldown counter
            if(prob()&&x<=0){ //bomb weapon. (six round cooldown.)
                x=6;
                cout << "The Archer attacks with a bomb arrow.\nPress Enter to roll a CON save, DC 13.\n";
                cin.get();//pause so they can read.
                cout << "Rolling CON save: ";
                short save=d20()+conSc;
                if(race=="Dwarf"){ //If our player is a Dwarf, apply the con advantage.
                    save=d20('a')+conSc;
                }
                cout << save << endl;
                if(save<13){ //***************************failed save
                    int dmg =d6()+d6()+d6()+d6();
                    if(feeble>0){ //if monster is enfeebled
                        pHlth=pHlth-(static_cast<float>(dmg)/2);
                        cout << "You failed your CON save.\n";
                        cout << "The " << monNm << " is enfeebled.\n";
                        cout << "You take " << setprecision(1) << fixed << static_cast<float>(dmg)/2 << " explosive damage.\n\n";
                    }
                    else{
                        pHlth=pHlth-(dmg);
                        cout << "You failed your CON save.\n";
                        cout << "You take " << dmg << " explosive damage.\n\n";
                    }
                }
                else{//***********************************succeeded save
                    int dmg =d6()+d6()+d6()+d6();
                    if(feeble>0){ //if monster is enfeebled:
                        pHlth=pHlth-(static_cast<float>(dmg)/4);
                        cout << "You succeeded in your CON save.\n";
                        cout << "The " << monNm << " is enfeebled.\n";
                        cout << "You take half damage: " << setprecision(1) << fixed << (static_cast<float>(dmg)/4) << " explosive damage.\n\n";
                    }
                    else{
                        pHlth=pHlth-(static_cast<float>(dmg)/2);
                        cout << "You succeeded in your CON save.\n";
                        cout << "You take half damage: " << setprecision(1) << fixed << (static_cast<float>(dmg)/2) << " explosive damage.\n\n";
                    }
                    
                }
                
            }   
            else{ //club attack.
                cout << "The Archer tries to shoot you. Rolling to hit.\n";\
                hit = d20()+5; //the zombie has a +5 to hit.
                if(blind>0){//if zombie is blinded
                    cout << "The Archer is blinded. It must roll at disadvantage.\n";
                    blind--;
                    hit=d20('d')+5;
                }
                
                if(hit>=Ac){//if the hit hits the player:
                    if(clsNm=="Wizard"&&(sp1>0&&hit<=Ac+5)){ //Wizards have shields, if their spell slots are unused.
                        cout << "You have been hit. Would you like to cast Shield as a first-level spell?\n";
                        cout << "Press 'y' for yes, 'n' for no.";
                        cin >> choice;
                        cin.ignore(); //soaks up the "enter" character you put there after.
                        if(choice=='y'||choice=='Y'){ //if they chose to block attack
                            cout << "You block the attack.\n";
                            sp1--;
                            abj++;
                            if(abj==1){//**************************************************Abjuration health boost.
                                cout << "You have cast your first Abjuration spell. ";
                                pHlth+=(10+intlSc);
                                cout << "You have regained " << 10+intlSc << " hit points.\n\n";
                            }
                            else{
                                cout << "You have cast a first-level Abjuration spell. ";
                                pHlth+=2;
                                cout << "You have regained 2 hit points.\n\n";
                            }
                        }
                        else{//if they didnt choose to block the attack.
                            cout << "You allow the attack to hit.\n";
                            int dmg1 = d8()+3; //the piercing damage
                            int dmg2 = d12(); //the poison damage
                            if(race=="Dwarf"){
                                int dmg2 = d6(); //the poison damage (dwarves take less of it)
                            }
                            if(feeble>0){ //if monster is enfeebled:
                                pHlth-=(static_cast<float>(dmg1+dmg2)/2);
                                cout << "The " << monNm << " is enfeebled.\n";
                                cout << "You take " << (dmg1)/2 << " piercing damage and " << (dmg2)/2 << " poison damage.\n\n";
                                feeble--;
                            }
                            else{
                                pHlth-=(dmg1+dmg2);
                                cout << "You have been hit.\n";
                                cout << "You take " << dmg1 << " piercing damage and " << dmg2 << " poison damage.\n\n";
                            }

                        }
                    }
                    else{
                        cout << "The attack hits.\n";
                        int dmg1 = d8()+3; //the piercing damage
                        int dmg2 = d12(); //the poison damage
                        if(race=="Dwarf"){
                            int dmg2 = d6(); //the poison damage (dwarves take less of it)
                        }
                        if(feeble>0){ //if monster is enfeebled:
                            pHlth-=(static_cast<float>(dmg1+dmg2)/2);
                            cout << "The " << monNm << " is enfeebled.\n";
                            cout << "You take " << (dmg1)/2 << " piercing damage and " << (dmg2)/2 << " poison damage.\n\n";
                            feeble--;
                        }
                        else{
                            pHlth-=(dmg1+dmg2);
                            cout << "You have been hit.\n";
                            cout << "You take " << dmg1 << " piercing damage and " << dmg2 << " poison damage.\n\n";
                        }
                    }
                }
                else{
                    cout << "The attack misses you.\n\n";
                }
            }
            
            
            cout << "Press Enter to continue.\n";
            
            cin.get();//pause them here so they have time to read.
            x--; //count down cooldown for ice breath.
        }
        else if((cursed==true&&mHlth>0)&&mInit<pInit){ //if the monster is cursed and is still alive, and has lower initiative.
            cout << "The " << monNm << " is cursed. It will attempt a WIS save.\n";
            short Zsave=d20()+zWis; //make the save.
            if(Zsave>=Dc){//If it's success
                cout << "The " << monNm << " has broken your curse. It can now take turns normally.\n\n";
                cursed=false;
            }
            else{
                cout << "The " << monNm << " has failed to remove your curse.\n\n";
            }
        }
        
        if(pHlth<=0&&(orc==true&&race=="Orc")){//Apply Relentless Endurance, if the player is an Orc.
            orc=false;
            cout << "You have sustained fatal injuries, but as an Orc, you can keep fighting.\n\n";
            pHlth=1;//put their health back at one hit point.
        }
        
        
    }while(pHlth>0&&mHlth>0); //keep fighting, to the death.
    
    if(pHlth<=0){//if the player has died:
        cout << "You have been slain by the " << monNm << ". Game over.\n";
    }
    else if(mHlth<=0){
        cout << "You have slain the " << monNm << ". You set up camp and are safe for the night.\n";
    } 
}