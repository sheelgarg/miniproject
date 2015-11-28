#include<iomanip>
#include<iostream>
#include<cstdlib>     
#include<fstream>
#include<cstring>      
#include<iostream>
using namespace std;
void prompt();
void preload();
int display();
void spacing();
void prompt()
{
	cout<<">> ";           //prompt for display
}

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
void preload() //preloads optab to a structure
{
	FILE *fp;
	string str;
	char ch;
	int j=0,i,p,a[2];
	fp=fopen("manumtrx.txt","r");
	while(!feof(fp))
	{
		while((ch=fgetc(fp))!='|')
		{
		if(ch=='\n')
		continue;
		if(ch==' ')
		continue;
		str+=ch;
	    }
	    i=0;
		while((ch=fgetc(fp))!='|')
	    {
	   	a[i]=ch;
	   	                   
			i++;
		}
	arr[j].cmd=str;
	str.erase(str.begin(),str.end());
	copy(a,a+2,arr[j].opcode);
	j++;
	if(j==26)
	break;
	}
	cout<<"preload complete"<<endl;
	fclose(fp);
}
void filewt()                //function for writing input file dynamically at run time
{
    char fname[20],label[20],command[20],operand[20];
	string end="END",resb="RESB",resw="RESW",byte="BYTE",word="WORD",cmnt=".",strt="START",empty="^";
    int i,count=1;
	cout<<"enter the name of the file to be created"<<endl;
    cin>>fname;
    ofstream of;
    of<<uppercase<<setbase(16);
    cout<<uppercase<<setbase(16);
    of.open(fname);
	if(!of.is_open())
    {
	cout<<"EXCEPTION:oopsie,something went wrong with the file to be created"<<endl;
	return;
    }
	int crraddr;
	cout<<setbase(16);
	cout<<"FILE WRITING MODULE"<<endl;
	cout<<"NOTE: please follow the following directives before entering input in the file so concerned"<<endl;
	cout<<"1.all command directives should be in accordance with the command matrix"<<endl;
	cout<<"2.all commands should be in capital"<<endl;                                 //format instructions to the user
	cout<<"3.user should insert '|' as delimeter to seperate columns"<<endl;
	cout<<"4.there can be atmost 3 columns in a line at a time i.e.3 delimeters"<<endl;	
	cout<<"5.comments start with a . in the command field with _ instead of space"<<endl;
	cout<<"6.if something needs to be left blank please enter '^'. "<<endl;                                 //cap is blank field
	cout<<"7. the format of the command should be as described in the assembler documentation"<<endl;  
    for(int k=0;k<80;k++)
    cout<<"_";
    cout<<endl;
    cout<<"enter the starting address"<<endl;
    cin>>crraddr;
    while(command!=end)
    {
	prompt();
    cin>>label;
    prompt();
    cin>>command;
    prompt();
    cin>>operand;
of<<crraddr<<" "<<label<<" "<<command<<" "<<operand<<endl;
if(command==byte)
	{
		if(operand[0]=='+')
		{
		crraddr+=2;
	   }
	   else
	   {
	   	int temp;
        i=0;
		while(operand[i]!='\0')
        {
          if(operand[i]=='\0')
        	break;
           temp++;
			i++;
		}
        crraddr+=temp;
	   }
   }
   else if(command==resb)
   {
   	int temp;
   	temp=atoi(operand);
   	crraddr+=temp;
   }
   else if(command==resw)
   {
   	int temp;
   	temp=atoi(operand);
   	crraddr+=(temp*3);
   }
	else if(command==strt || command==cmnt || command==end || command==empty)
	{
	crraddr=crraddr;
	}
	else
	{
	crraddr+=3;
	}
cout<<"LINE : "<<count<<" "<<crraddr<<" "<<label<<" "<<command<<" "<<operand<<endl;
count++;
}
of.close();
}
