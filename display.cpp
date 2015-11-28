#include<iomanip>
#include<iostream>
using namespace std;
int main()
{
	int ch;
  char ch1;	
  cout<<setbase(16);
  preload();
  while(1)
  {
	p:
	ch=display(); //menu display function
	switch(ch)
	{
		case 1: 
		  //cmdmtrx();        //switch case functions for menu 
		  break;
		case 2:
		  //filewt();
		  break;
		case 3:
			//ipfilerd();
			break;
		case 4:
		  //assemble();  //integration label

		  break;  	
		case 5:
			exit(0);
			break;
		default:
	    cout<<"oopsie,appears to be a invalid choice,pleaser try again"<<endl;
	    goto p;
	}
  }
	return 0;
}
void spacing()        //spacing for disp indentation
{
	int i;                   //MODULE COMPLETE
	for(i=0;i<30;i++)
	cout<<" ";
}
int display()      //display function for menu 
{
  int i;
  for(i=0;i<80;i++)
  cout<<"_";
  cout<<endl;
  spacing();   //commented for the time being for testing purposes
  system("COLOR 02");
  
  cout<<"ASSEMBLER"<<endl;    
  for(i=0;i<3;i++)           
  cout<<endl;
  spacing();
  system("COLOR 0B");           
  cout<<"MENU"<<endl;
  spacing();
  system("COLOR 02");
  cout<<"1.COMMAND MATRIX"<<endl;                            
  spacing();
  cout<<"2.WRITING A INPUT FILE"<<endl;                     
  spacing();
  cout<<"3.READING A INPUT FILE"<<endl;
  spacing();
  cout<<"4.ASSEMBLING"<<endl;
  spacing();
  cout<<"5.TERMINATE"<<endl;
for(i=0;i<3;i++)
cout<<endl;
cout<<"enter your choice : ";
int ch;
cin>>ch;
return ch;
}
