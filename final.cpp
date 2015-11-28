#include<cstdlib>     
#include<fstream>
#include<iomanip>      
#include<cstring>      
#include<iostream>
using namespace std;          
void text();
void tolength(int);
void tofilesymtab();
void tofileoptab();
void spacing();
void cmdmtrx();
int display();
void filewt();
void ipfilerd();
void prompt();
void preload();               
void pass1();//module complete
void assemble();
void cpass2(int);
void head(int sizepg);     
struct obj{
int add;
string label;
string command;               //object file processing
string	operand;
string objcode;
}obj1[100];
struct optab{
	string cmd;                   
    char opcode[2];             //optab         
}arr[26];
int symtabsize=0;
struct symtab{
	string label;          //symtab
	int add;
}label1[20];
void prompt()
{
	cout<<">> ";           //prompt for display
}
void tofilesymtab()
{
	ofstream of;
	of<<uppercase<<setbase(16);               //converts symtab to file
	of.open("symtab.txt");
	if(!of.is_open())
	cout<<"EXCEPTION,oopsie:there appears to be some problem with the "<<endl;
	else
	{
		cout<<"TRANSFERRING SYMTAB TO A FILE FOR TEXT RECORD PROCESSING"<<endl;
		for(int i=0;i<symtabsize;i++)
		of<<label1[i].label<<" "<<label1[i].add<<endl;
	}
	of.close();
}
void tofileoptab()
{
	ofstream of;
	of<<uppercase<<setbase(16);       //converts optab to file
	of.open("optab.txt");
	if(!of.is_open())
	cout<<"EXCEPTION,oopsie:there appears to be some problem with the "<<endl;
	else
	{
		cout<<"TRANSFERRING OPTAB TO A FILE FOR TEXT RECORD PROCESSING"<<endl;
		for(int i=0;i<26;i++)
		of<<arr[i].cmd<<" "<<arr[i].opcode<<endl;
	}
	of.close();
}
void tolength(int size)
{
	
	ofstream of;
	of<<uppercase<<setbase(16);         //converts length of programme to file
	of.open("length.txt");
	if(!of.is_open())
	cout<<"EXCEPTION,oopsie:there appears to be some problem with the "<<endl;
	else
	{
		cout<<"TRANSFERRING OPMTAB TO A FILE FOR TEXT RECORD PROCESSING"<<endl;
		of<<size<<endl;
	of.close();
}
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
		  cmdmtrx();        //switch case functions for menu 
		  break;
		case 2:
		  filewt();
		  break;
		case 3:
			ipfilerd();
			break;
		case 4:
		  assemble();  //integration label

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
void cpass2(int size)    //pass2 function
{
	tofilesymtab();
	tofileoptab();
	int i;
	for(i=0;i<80;i++)
	cout<<"_";
	cout<<endl;
	cout<<"PASS 2"<<endl;
	for(i=0;i<80;i++)
	cout<<"_";
	cout<<endl;
	head(size);   //header 
	text();
	//void end(size); //not feasable needs to be incorporated with text function only;
}
void text()         
{
	ofstream objf,processed;
	objf<<uppercase<<setbase(16);
	processed<<uppercase<<setbase(16);
	objf.open("object_file.txt",ios::app);
	if(!objf.is_open())
	{
	cout<<"EXCEPTION:oopsie,something went wrong with the object file"<<endl;
    }
    processed.open("processed.txt");
    if(!processed.is_open())
    cout<<"EXCEPTION,oopsie something went wrong with the processed text file"<<endl;
	objf<<endl;
	int add;
	string op,end="END",resb="RESB",resw="RESW",byte="BYTE",word="WORD",cmnt=".",strt="START",empty="^";
	char ch,label[20],command[20],operand[80];
	FILE *fp;
	fp=fopen("intermediate_file.txt","r");
	if(fp==NULL)
	cout<<"EXCEPTION:oopsie,something went wrong with the intermediate file"<<endl;
	fscanf(fp,"%s%s%s",label,command,operand);
	//for ignoring purposes of the header record
	cout<<endl<<"TEXT RECORD:"<<endl;
	cout<<"text record formation in progress"<<endl;
	int i=0;
	while(command!=end)
	{
		fscanf(fp,"%X%s%s%s",&add,label,command,operand);
		obj1[i].add=add;
		obj1[i].label=label;
		obj1[i].command=command;
		obj1[i].operand=operand;
		if(command==end)
		goto p;
		else if(command==cmnt)
		continue;
		else if(command==byte || command==word)
		{
			if(command==byte)         //resb
			{
				if(operand[0]=='+')
				{
					for(int k=1;k<3;k++)
					{
						obj1[i].objcode+=operand[k];       //2 byte number
					}
				}
				else if(operand=="EOF")
				{
					obj1[i].objcode="454F46";          //for eof
				}
				else
				{
						ofstream of;
						of<<uppercase<<setbase(16);
	                    ifstream iff;
	                    of.open("temp.txt");						
					int l=0,ascii;
					while(operand[l]!='\0')
					{
					  ascii=operand[l];                  //for characters
					  of<<ascii;
					  l++;
					}
					of.close();
					iff.open("temp.txt");
				string str1;
				iff>>str1;
				obj1[i].objcode=str1;
				iff.close();
				}
			}
			else //if command ==word   (module debugged and complete)
			{
				char convert[6];
				int flage=0;
				int temp2,temp1;
				temp1=atoi(operand);
				temp2=temp1;
				if(temp1==0)
				{
					flage++;
				}
				int count=0;
				while(temp2!=0)
				{
					temp2/=10;
					count++;
				}
			 if(count>6)
			 cout<<"size of word exceeded at address : "<<add<<" "<<endl;
             else
             {
             	if(flage==1)
             	{
             	for(int klm=0;klm<6;klm++)
				 obj1[i].objcode+="0";
				 flage=0;	
			 }
			
				else
				{
				 int diff,zero=0;
             	diff=6-count;
				 for(int km=0;km<diff;km++)
             	obj1[i].objcode+="0";
             	itoa(temp1,convert,16);
				 obj1[i].objcode+=convert;
		       }
			 } 
			}
			
		}
		else if(command==resb || command==resw )
		continue;
		else //for normal command
		{
		   int flag=0,lab;
		   for(lab=0;lab<26;lab++)
		   {
		   	if(arr[lab].cmd==command)
		   	{
			   obj1[i].objcode=arr[lab].opcode;
			flag++;
			}
		   }
		   if(flag==0)
		   {
		   	cout<<"exception:command not found at address: "<<add<<endl;
		   }
		   if(operand!=empty)    //cap bug resolved
		   {
		   int countm=0,something,something1;
		   string str;
		   for(int lab1=0;lab1<symtabsize;lab1++)
		   {
		      if(label1[lab1].label==operand)
		      {
		      	    int countrr=0;
					  ofstream of;
					of.open("temp.txt");
		      	    of<<uppercase<<setbase(16);
					something=label1[lab1].add;
					something1=something;
					while(something1!=0)
					{
						something1/=10;
						countm++;
					}
					if(countm>5)
					cout<<"address out of bound"<<endl;
				
					else                                       //size bug solved every opcode is now of 3 bytes if applicable
					{
					char temp50[20];
					of<<something;
					of.close();
					ifstream iff;
					iff.open("temp.txt");
					iff>>str;
				    int manu=0;
    while(str[manu]!='\0')
    {
    	temp50[manu]=str[manu];
    	manu++;
	}
	temp50[manu]='\0';
					countrr=strlen(temp50);
				    int diffr=4-countrr;
				    if(diffr>0)
				    {
					  obj1[i].objcode+="0";
					  obj1[i].objcode+=str;
					}
					else
				   obj1[i].objcode+=str;
			      }
			  }
		   }
	       }
	       else
	       {
	       	obj1[i].objcode+="0000";
		   }
		}
i++;		
}
	p:
		cout<<"processed intermediate file with opcodes is"<<endl<<endl;
		//int diff80,kmp,temp22;
		for(int kp=0;kp<i;kp++)
		{
		cout<<obj1[kp].add<<" "<<obj1[kp].label<<" "<<obj1[kp].command<<" "<<obj1[kp].operand<<" "<<obj1[kp].objcode<<endl;
	    processed<<obj1[kp].add<<" "<<obj1[kp].label<<" "<<obj1[kp].command<<" "<<obj1[kp].operand<<" "<<obj1[kp].objcode<<endl;
		}
		processed.close();
		//text record
		cout<<endl<<"TEST RECORD :"<<endl<<endl;
		string stringz;
		int localstart,ip=0,insize,startlabel=1,localsize=0;
		int jp=0;
		back:
		localsize=0;
		while(jp<i)
		{
			
			if(localsize+(obj1[jp].operand.size()/2)>30)
			goto bunny;
			if(startlabel==1)
			{
				localstart=obj1[jp].add;
				startlabel=0;
			}
			if(obj1[jp].command==resb || obj1[jp].command==resw)
			break;
			else
			{
			stringz+=obj1[jp].objcode;
			stringz+="^";
		    localsize+=obj1[jp].operand.size()/2;          
			}
			jp++;
		}
		bunny:
		cout<<"T^"<<localsize<<"^"<<localstart<<"^"<<stringz<<endl;
		objf<<"T^"<<localsize<<"^"<<localstart<<"^"<<stringz<<endl;
		stringz.clear();
		if(jp==i)
		goto end19;
		else
		{
		startlabel=1;
		localsize=0;
		goto back;
	    }
		end19:
		//END RECORD
	cout<<endl<<"END RECORD : "<<endl<<endl;
	cout<<"E^";
	objf<<endl<<"E^";
	int backop;
	int blob,caution=0;
	if(operand==empty)
	{
	cout<<backop;
    objf<<backop;
	}
	else
	{
		for(blob=0;blob<symtabsize;blob++)
		{
			if(operand==label1[blob].label)
			{
				cout<<"000"<<label1[blob].add<<endl;
				objf<<"000"<<label1[blob].add<<endl;
				caution++;
			}
        }
        if(caution==0)
        cout<<"invalid label"<<endl;
	}
objf.close();
}
void head(int sizepg)
{
   	cout<<uppercase<<setbase(16);
	int i=0,size,diff,count,operand1,check,temp2,ctr,temp3;
	string cap="^",end="END",resb="RESB",resw="RESW",byte="BYTE",word="WORD",cmnt=".",strt="START",empty="^",eof="EOF";
	int temp;
	char ch,label[20],command[20],operand[20];
   ofstream of,objof;
   //var dec section uphead
   objof.open("object_file.txt");
   if(!objof.is_open())
   {
   	cout<<"EXCEPTION:oopsie,something went wrong with the object file"<<endl;
   	of<<"EXCEPTION:oopsie,something went wrong with the object file"<<endl;
   	return;
   }
   of.open("error_record.txt");
   if(!of.is_open())
   cout<<"EXCEPTION:oopsie,something went wrong with the error record,error facilities are now constrained"<<endl;
    objof<<uppercase<<setbase(16);
	cout<<"HEADER RECORD : "<<endl;
	FILE *fp;
	fp=fopen("intermediate_file.txt","r");
	if(fp==NULL)
	{
	cout<<"EXCEPTION:oopsie,something went wrong with the intermediate file"<<endl;
	of<<"EXCEPTION:oopsie,something went wrong with the intermediate file"<<endl;
    return ;
	}
	else
	{
		fscanf(fp,"%s%s%s",label,command,operand);
		if(command==strt)
		{
			size=0;
			i=0;
			while(label[i]!='\0')
			{
				size++;
				i++;
			}
			if(size>6)
			{
				cout<<"label size exceeding the prescribed limits"<<endl;
		        of<<"label size exceeding the prescribed limits"<<endl;
			}
			diff=6-size;                                              //header^name
			if(label==cap)
			{
			cout<<"H^";
			objof<<"H^";
			for(int i=0;i<diff+1;i++)
			{
			cout<<" ";
			objof<<" ";
		    }
			cout<<"^";
			objof<<"^";
		    }
			else
			{
			cout<<"H^"<<label;
			objof<<"H^"<<label;
			for(int i=0;i<diff;i++)
			{
			cout<<" ";
			objof<<" ";
		    }
			cout<<"^";
	        objof<<"^";
			}
		//^starting add
		count=0;
		i=0;
		operand1=atoi(operand);
		temp=operand1;
		while(temp!=0)
		{
			temp/=10;
			count++;
		}
		if(count>6 || operand=="^")
		{
			cout<<"invalid format of the operand field for the header record"<<endl;
			of<<"invalid format of the operand field for the header record"<<endl;
			return ;
		}
		else
		{
			diff=6-count;
			for(i=0;i<diff+1;i++)           
			{
			cout<<"0";
			objof<<"0";
		   }
			cout<<operand1<<"^";
		    objof<<operand1<<"^";
		}
		//size
			size=0;
		    temp=sizepg;
			while(temp!=0)                                               //header record module complete
			{
				temp=temp/10;
				size++;
			}
		    if(size>6)
		    {
		    	cout<<"programme too long"<<endl;
		    	of<<"programme too long"<<endl;
		    	return ;
			}
			else
			{
				diff=6-size;
				for(i=0;i<diff;i++)
				{
				cout<<0;
				objof<<0;
				}	
	    		cout<<sizepg;                 //size format exception
	    		objof<<sizepg;
			}
		cout<<endl;
		objof<<endl;
		}
}
objof.close();
of.close();
fclose(fp);
}
