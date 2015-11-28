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
void ipfilerd();
void cmdmtrx();
void assemble();
void pass1();
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
void ipfilerd()
{                           //reading input file
	string end="END";
	FILE *fp;
	cout<<uppercase<<setbase(16);
	char label[20],command[20],operand[20];
	int add;
	ofstream of;
	of.open("error_record.txt");
	if(!of.is_open())
	{
		cout<<"EXCEPTION:oopsie,something went wrong with the error record.error recording capabilties are now revoked"<<endl;
	}
	char fname[20];
	cout<<"enter the name of the file to be displayed"<<endl;
	cin>>fname;
	fp=fopen(fname,"r");
	if(fp==NULL)
	{
		cout<<"OOPSIE,some exception occoured in the user generated file at the time of reading"<<endl;
		of<<"OOPSIE,some exception occoured in the user generated file at the time of reading"<<endl;
		return;
	}
while(!feof(fp))
{
	fscanf(fp,"%s %s %s",label,command,operand);
	cout<<label<<" "<<command<<" "<<operand<<endl;
if(command==end)
break;
}
fclose(fp);
of.close();
}
void cmdmtrx()          //displaying command matrix
{
	int i=0;
	cout<<"the command matrix displayed along with their respective opcodes is as follows"<<endl;
	for(i=0;i<26;i++)
	{
		cout<<arr[i].cmd<<" | ";
		cout<<arr[i].opcode[0]<<arr[i].opcode[1]<<endl;       //MODULE COMPLETE AND INTEGRATED exception:ONLY PROBLEM WITH SPACING IN THE DISPLAY AT STANDARD I/O
	}
}
void assemble()    //assemble
{
  pass1();
}
void pass1()       //pass1
{
    //preload();
	int size,a1;
	int crraddr;
	ofstream of,iof;
	iof<<uppercase<<setbase(16);
	of.open("error_record.txt");
	if(!of.is_open())
	cout<<"EXCEPTION:oopsie,there seems to be some problem with the error file"<<endl;
	iof.open("intermediate_file.txt");
	if(!iof.is_open())
	cout<<"EXCEPTION:oopsie,there seems to be some problem with the intermediate file"<<endl;
	cout<<uppercase<<setbase(16);
	int add,i,count,count1=0;
    string end="END",resb="RESB",resw="RESW",byte="BYTE",word="WORD",cmnt=".",strt="START",empty="^";
	char ch,label[20],command[20],operand[80];
	char fname[20];
	FILE *fp;                                        //to make errors to be thrown in the error file too
	printf("enter file name to be read\n");
	scanf("%s",&fname);
	fp=fopen(fname,"r");
	if(fp!=NULL)
	{
	fscanf(fp,"%s%s%s",label,command,operand);
	cout<<"as seen in the input file : ";
	cout<<label<<" "<<command<<" "<<operand<<endl;
	if(command==strt)                               
	{
	if(operand==empty)
	crraddr=0;
	else
	{
	crraddr=atoi(operand);
	iof<<label<<" "<<command<<" "<<operand<<endl;
    }
	}
	a1=crraddr;
while(!feof(fp))
{
fscanf(fp,"%s%s%s",label,command,operand);
iof<<"0"<<crraddr<<" "<<label<<" "<<command<<" "<<operand<<endl;
cout<<"0"<<crraddr<<" "<<label<<" "<<command<<" "<<operand<<endl;
if(command==byte)
	{
		if(operand[0]=='+')
		{
		crraddr+=2;
	   }
	   else
	   {
	   	int temp=0;
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
}
size=crraddr-a1;
tolength(size);
cout<<"the size of the programme is : "<<size<<endl;
cout<<"intermediate file prepared"<<endl;
fclose(fp);
}
else
	{
		printf("EXCEPTION:oopsie, something went wrong\n");
	}
fp=fopen("intermediate_file.txt","r");
if(fp==NULL)
{
cout<<"EXCEPTION:oopsie,something went wrong with the intermediate file so prepared"<<endl;
of<<"EXCEPTION:oopsie,something went wrong with the intermediate file so prepared"<<endl;
return ;
}
cout<<"scanning data for further processing from the intermediate file"<<endl;
int init=0;
while(!feof(fp))
{
	//for start
	if(init==0)
	{
	init=1;
	fscanf(fp,"%s%s%s",label,command,operand);
	continue;
	}
	
	fscanf(fp,"%X%s%s%s",&add,label,command,operand);
	cout<<add<<" "<<label<<" "<<command<<" "<<operand<<endl;
	//everything else
	//command validation
	count=0;
		for(i=0;i<26;i++)
	{
			if(arr[i].cmd==command)
	    {
		count++;
	    break;
	   }
	}
	if(command==strt || command==end || command==resb || command==resw || command==byte || command==word || command==cmnt)
	count++;
	if(count==0)
	{
	cout<<"command not found at address : "<<add<<" the programme will terminate now "<<endl;
	of<<"command not found at address : "<<add<<" the programme will terminate now "<<endl;
	break;
	}
    if(command==end)
    break;
	int res;
	//symtab prepration
    if(label!=empty)
    {
		{
			count1=0;
			for(i=0;i<symtabsize;i++)
			{
				if(label==label1[i].label)
				count1++;
		    }
			    if(count1>0)         
				{
				cout<<"label with a duplicate name is used producing ambiguity at address : "<<add<<" the programme will now terminate"<<endl;
				of<<"label with a duplicate name is used producing ambiguity at address : "<<add<<" the programme will now terminate"<<endl;
				break;
			    }
			 else
			 {   
			label1[symtabsize].label=label;
			label1[symtabsize].add=add;
		symtabsize++;
	         }
		}
	}
	}
    cout<<"do you want to view symtab Y/N : ";
    cin>>ch;
    cout<<endl;
    if(ch=='y' || ch=='Y')     //symtab display function
	{
	cout<<endl<<"SYMTAB:";
	cout<<endl<<endl;
	for(i=0;i<symtabsize;i++)
    cout<<label1[i].label<<" | "<<label1[i].add<<endl;
    }
	fclose(fp);
	of.close();
//calling cpass2 from this only for testing purposes
	cpass2(size);
   //incorporating cpass2 in this 
return ;
}
