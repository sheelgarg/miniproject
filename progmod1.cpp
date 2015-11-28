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
