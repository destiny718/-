#include<iostream>
#include<cstring>
#include<fstream>
#include<string>
#include<sstream>
#include<stdlib.h>
#include<stdio.h>
#define MAXLINE 1000
#define MAXFILE 2000
using namespace std;

struct Terminal {
    char user[MAXLINE]; // user name
    char mach[MAXLINE]; // machine name
    char root[MAXLINE]; // root dictionary
    char wdir[MAXLINE]; // working dictionary
    char strin[MAXFILE]; // redirected standard input
    char strout[MAXFILE]; // redirected standard output
};
Terminal gTerm;

const int arrsize =5000;
string bcmp(string aline){//function for -b
	string atmp;
	if(aline[0]==' '||aline[0]=='\t')atmp=' ';
	else atmp=aline[0];
	for(int i=1;i<aline.size();i++){
		if(aline[i]!=' '&&aline[i]!='\t'){
			atmp+=aline[i];
		}
		else{
			if(aline[i-1]!=' '&&aline[i-1]!='\t'){
				atmp+=' ';
			}
			else continue;
		}	
	}
	return atmp;	
} 
string icmp(string aline){
	string atmp;
	char tmp;
	for(int i=0;i<aline.size();i++){
		if(aline[i]>=65&&aline[i]<=90){
			tmp=aline[i]+32;
			atmp+=tmp;
		}
		else{
			atmp+=aline[i];
		}
	}
	return atmp;
} 
string wcmp(string aline){//function for -w
	string atmp;
	
	for(int i=0;i<aline.size();i++){
		if(aline[i]!=' '&&aline[i]!='\t'){
			atmp+=aline[i];
		}
	}
	return atmp;
}
void doDiff(int argc,char*argv[]){
	string s1;
	if(argc>=2)s1=argv[1];
	for(int i=0;i<argc;i++){
		string ss=argv[i];
		if(ss=="--help"){
		strcpy(gTerm.strout,"-b:ignore changes in the amount of white space.\n-B:ignore changes where lines are all blank.\n-i:ignore case differences in file contents.\n-q: report only when files differ.\n-w:ignore all white space.\n-I[RE]:ignore changes where all lines match RE.\n"); 
		return;
		}
	} 
	if(argc==2&&s1!="--help"){
		string tmp=s1;
		tmp="missing operand after "+tmp;
		tmp+=",try diff --help for more\n";
		cerr<<tmp;
		return;
	}
	if(argc==1){
		cerr<<"missing operand after diff,try diff --help for more\n";
		return;
	} 
	if(argc>=2&&s1=="--help"){
		strcpy(gTerm.strout,"-b:ignore changes in the amount of white space.\n-B:ignore changes where lines are all blank.\n-i:ignore case differences in file contents.\n-q: report only when files differ.\n-w:ignore all white space.\n-I[RE]:ignore changes where all lines match RE.\n"); 
		return;
	}
	if(argc==1){
	cerr<<"missing operand after diff,try diff --help for more\n";
	return;
	}
	if(argc>3){
		
		for(int i=1;i<argc-2;i++){
			string tmp=argv[i];
			if(tmp!="-b"&&tmp!="-B"&&tmp!="-q"&&tmp!="-i"&&tmp!="-w"){
				if(tmp=="-I"){
					if(i==argc-3){
						cerr<<"missing operand after -I,try diff --help for more"<<endl;
						return;
					}
				}
				else{string tp=argv[i-1];
					if(tp!="-I"){
						cerr<<"no such command in dictionary,try diff --help for more"<<endl;return;
					}
				}
			}
		}
	}
	string tmpa,tmpb;
	string s;
	string s2=argv[argc-2];//get the filename
	string s3=argv[argc-1];
	int t=0;
	int count_a=0;int count_b=0;//the numbers of lines of file1 and file2
	int a=0;int b=0; int lena=0;int lenb=0;
	string aline[arrsize+1];
	string bline[arrsize+1];
	string ap[arrsize+1],bp[arrsize+1];//this is a copy for file1 and file2
	bool is=false;
	string sp; 
	
	
	if(s2[0]=='-'){//if the file is to be read from strin
		for(int i=0;i<MAXFILE;i++){
			if(gTerm.strin[i]=='\n'){
				a++;
				continue;
			}
			else if(gTerm.strin[i]=='\0'){
				
				break;
			}
			else{
				aline[a+1]+=gTerm.strin[i];
				ap[a+1]+=gTerm.strin[i];
				continue;
			}
		} 
	}
	else if(s2[0]=='/'){
		tmpa=gTerm.root;
		int tmp=tmpa.back();
		if(tmp!=47&&tmp!=92)tmpa+="//";
	  	s2.erase(0,1);
	  	tmpa+=s2;
	}
	else{
		tmpa=gTerm.root;
	  	string gz=gTerm.wdir;
		int tmp=tmpa.back();
		if(tmp!=47&&tmp!=92)tmpa+="/";
		tmpa+=gz;
		tmpa+="//";
		tmpa+=s2;
	}
	if(s3[0]=='-'){
		for(int i=0;i<MAXLINE;i++){
			if(gTerm.strin[i]=='\n'){//
				b++;
				continue;
			}
			else if(gTerm.strin[i]=='\0'){
				
				break;
			}
			else{
				bline[b+1]+=gTerm.strin[i];
				bp[b+1]+=gTerm.strin[i];
				continue;
			}
		} 
	} 
	//get the file's content from strin
	else if(s3[0]=='/'){
		tmpb=gTerm.root;
		int tmp=tmpb.back();
		if(tmp!=47&&tmp!=92)tmpb+="//";
	  	s3.erase(0,1);
	  	tmpb+=s3;
	}
	else{
		tmpb=gTerm.root;
	  	string gz=gTerm.wdir;
		int tmp=tmpb.back();
		if(tmp!=47&&tmp!=92)tmpb+="/";
		tmpb+=gz;
		tmpb+="//";
		tmpb+=s3;
	}
	if(s2[0]!='-'){
		const char *pa=tmpa.c_str();
		
		ifstream fin1;
		fin1.open(pa);
		if(!fin1){
			cerr<<"could not find ";
			cerr<<s2+"\n";
			cerr<<"please check the path."<<endl; 
			return;
		}
		while(getline(fin1,aline[lena+1])&&lena<arrsize){
			lena++;
		}
		fin1.close();//or we read the file that already exist 
		for(int i=1;i<=lena;i++){
		ap[i]=aline[i];
	} 
	}
	if(s3[0]!='-'){
		const char *pb=tmpb.c_str();
		ifstream fin2;
		fin2.open(pb);
		if(!fin2){
			cerr<<"could not find ";
			cerr<<s3+"\n";
			cerr<<"please check the path."<<endl;
			return;
		}
		while(getline(fin2,bline[lenb+1])&&lenb<arrsize){
			lenb++;
		}
		fin2.close();
		for(int i=1;i<=lenb;i++){
		bp[i]=bline[i];
	}
	} 
	lena=max(a,lena);lenb=max(b,lenb);//determine the numbers of lines of file1 and file2
	
	if(s2=="-"&&s3=="-")return;//compare strin with itself
	/*according to our teacher's hint,diff - -equals 
	to comparing strin with itself,then nothing should be output.*/
	for(int i=1;i<argc;i++){
		string x;
		x=argv[i];
		if(x=="-b"){
			for(int j=1;j<=lena;j++){
				ap[j]=bcmp(ap[j]);
			}
			for(int j=1;j<=lenb;j++){
				bp[j]=bcmp(bp[j]);
			}
		}
		if(x=="-i"){
			for(int j=1;j<=lena;j++){
				ap[j]=icmp(ap[j]);
			}
			for(int j=1;j<=lenb;j++){
				bp[j]=icmp(bp[j]);
			}
			is=true;
		}
		if(x=="-w"){
			for(int j=1;j<=lena;j++){
				ap[j]=wcmp(ap[j]);
			}
			for(int j=1;j<=lenb;j++){
				bp[j]=wcmp(bp[j]);
			}
		}	
	} 
	bool bi[2];bi[0]=false;bi[1]=false;bool q=false;
	for(int i=0;i<argc;i++){
		string x;
		x=argv[i];
		if(x=="-B"){
			bi[0]=true;
		}
		if(x=="-I"){
			bi[1]=true;
			sp=argv[i+1];
		}
		if(x=="-q")
			q=true;
	}
	if(bi[0]==false&&bi[1]==false&&q==true){
		if(lena!=lenb){
			string tmp1=argv[argc-2];string tmp2=argv[argc-1];
			string ss="file "+tmp1+" and "+tmp2+" differ\n";
			const char*p=ss.c_str(); 
			strcpy(gTerm.strout,p);
			return;
		}
		else{
			for(int i=1;i<=lena;i++){
				if(ap[i]!=bp[i]){
			string tmp1=argv[argc-2];string tmp2=argv[argc-1];
			string ss="file "+tmp1+" and "+tmp2+" differ\n";
			const char*p=ss.c_str(); 
			strcpy(gTerm.strout,p);
					return;
				}
			}
			return;
		}
	}
	if(bi[0]==true&&bi[1]==false&&q==true){
		int an=0;int bn=0;
		string al[arrsize+1],bl[arrsize+1];
		for(int i=1;i<=lena;i++){
			if(ap[i]!=""){
				an++;
				al[an]=ap[i];
			}
		}
		for(int i=1;i<=lenb;i++){
			if(bp[i]!=""){
				bn++; 
				bl[bn]=bp[i];
			}
		}
		if(an!=bn){
			string tmp1=argv[argc-2];string tmp2=argv[argc-1];
			string ss="file "+tmp1+" and "+tmp2+" differ\n";
			const char*p=ss.c_str(); 
			strcpy(gTerm.strout,p);
			return;
		}
		else{
			for(int i=1;i<=an;i++){
				if(al[i]!=bl[i]){
			string tmp1=argv[argc-2];string tmp2=argv[argc-1];
			string ss="file "+tmp1+" and "+tmp2+" differ\n";
			const char*p=ss.c_str(); 
			strcpy(gTerm.strout,p);
					return;
				}
			}
		}
		return;
	}
	if(bi[0]==false&&bi[1]==true&&q==true){
		if(is==true){
			sp=icmp(sp);
		}
		int point1=0,point2=0;
		/*p1 is the number of the lines that are different but both contain the string that pointed by -I 
		p2 is the number of the lines that are exactly the same*/ 
		if(lena==lenb){
			for(int n=1;n<=lena;n++){
				if(ap[n]!=bp[n]&&bp[n].find(sp)!=-1&&ap[n].find(sp)!=-1){ 
				// 18446744073709551615=-1
					point1++; 
				}
				if(bp[n]==ap[n])point2++;
			}
		} 
		
		if(point1+point2==lena)return ;
		else {
		string tmp1=argv[argc-2];string tmp2=argv[argc-1];
		string ss="file "+tmp1+" and "+tmp2+" differ\n";
		const char*p=ss.c_str(); 
		strcpy(gTerm.strout,p);
		return;
		}
	}
	if(bi[0]==true&&bi[1]==true&&q==true){
		if(is){
			sp=icmp(sp);
		}
		int an=0;int bn=0;
		string al[arrsize+1],bl[arrsize+1];
		for(int i=1;i<=lena;i++){
			if(ap[i]!=""){
				an++;
				al[an]=ap[i];
			}
		}
		for(int i=1;i<=lenb;i++){
			if(bp[i]!=""){
				bn++; 
				bl[bn]=bp[i];
			}
		}
		if(an!=bn){
			string tmp1=argv[argc-2];string tmp2=argv[argc-1];
			string ss="file "+tmp1+" and "+tmp2+" differ\n";
			const char*p=ss.c_str(); 
			strcpy(gTerm.strout,p);
			return;
		}
		else{
			for(int i=1;i<=an;i++){
				if(al[i]==bl[i])continue;
				else if(al[i]!=bl[i]&&bl[i].find(sp)!=-1&&al[i].find(sp)!=-1)continue;
				else{
			string tmp1=argv[argc-2];string tmp2=argv[argc-1];
			string ss="file "+tmp1+" and "+tmp2+" differ\n";
			const char*p=ss.c_str(); 
			strcpy(gTerm.strout,p);
					return;	
					}
				}
				return;
			}	
		}
	if(bi[0]==false&&bi[1]==false&&q==false){
	
			int count=0;
			int index=1;
		int flag[1001];
		for(int k=0;k<=1000;k++)
			flag[k]=0;//flag records the lines that match in file1 and file2
	
	for(int n=1;n<=lena;n++){
		for(int j=index;j<=lenb;j++){
			if(bp[j]==ap[n]){
				index=j+1;//if the jth line of file b matches the nth line of file a,update index 
				flag[n]=j;
				count++;//record the number of the line that are the same
				break; 
			}
		}	//if no one matches the nth line of file a,let n+1
	}
	
	
	
	int atmp=0;
	int btmp=0;//these two virables record the process
	
	if(count==0){
		s+="1c1\n";
		for(int i=1;i<=lena;i++) {
			
			s+="<"+aline[i]+"\n";
		}
		s+="- - -\n";
		for(int i=1;i<=lenb;i++) {
			
			s+=">"+bline[i]+"\n";
		}
		
		const char*p=s.c_str();
		strcpy(gTerm.strout,p);
		return ;//if the two files are totally different
	} 
	
	if(flag[1]>1){
		s+="0a1\n";
		for(int i=1;i<flag[1];i++){
			
			s+=">"+bline[i]+"\n";
		}
			
			atmp=1;btmp=flag[1];
			count--; 
	}
	if(flag[1]==1) {
		atmp=1;btmp=1;count--;//see if any line in file b matches the first line of file a
		
	}
	for(int i=2;i<=lena&&count>=0;i++){
		if(flag[i]==1){
			s+="1d0\n";
			for(int j=0;j<flag[i];j++){
				
				s+="<"+aline[j]+"\n";
			}
				
		atmp=i;btmp=flag[i];
		count--;
		continue;
		}
		if(flag[i]>1){
			if(i-atmp==1&&flag[i]-btmp==1){
				atmp=i;btmp=flag[i];count--;
				continue;//if the two matched lines are adjacent,nothing should be output
			}
			if(i-atmp==1&&flag[i]-btmp>1) { 
				
				s+=to_string(atmp)+"a"+to_string(btmp+1)+"\n"; 
				for(int j=btmp+1;j<flag[i];j++){
					
					s+=">"+bline[j]+"\n";
				} 
				atmp=i;btmp=flag[i];count--;//update the state
				continue;
			}
			if(i-atmp>1&&flag[i]-btmp==1){
				
				s+=to_string(atmp+1)+"d"+to_string(flag[i])+"\n";
				for(int j=atmp+1;j<i;j++){
					
					s+="<"+aline[j]+"\n"; 
				}
				atmp=i;btmp=flag[i];count--;
				continue;
			}
			if(i-atmp>1&&flag[i]-btmp>1){
				
				s+=to_string(atmp+1)+"c"+to_string(btmp+1)+"\n";
				for(int j=atmp+1;j<i;j++){
					
					s+="<"+aline[j]+"\n";
				}
				s+="- - -\n";
				for(int j=btmp+1;j<flag[i];j++){
					
					s+=">"+bline[j]+"\n";
				}
				atmp=i;btmp=flag[i];count--;
				continue;
			} 
		} 
	} 
	if(atmp==lena&&btmp<lenb){
		s+=to_string(atmp+1)+"a"+to_string(btmp+1)+"\n";
		for(int j=btmp+1;j<=lenb;j++){
			s+=">"+bline[j]+"\n";
		}
			
	}
	if(atmp<lena&&btmp==lenb){
		s+=to_string(atmp+1)+"d"+to_string(btmp)+"\n";
		for(int j=atmp+1;j<=lena;j++){
			s+="<"+aline[j]+"\n";
		}
			
	}
	if(atmp<lena&&btmp<lenb){
		s+=to_string(atmp+1)+"c"+to_string(btmp+1)+"\n";
		for(int j=atmp+1;j<=lena;j++){
			
			s+="<"+aline[j]+"\n";
		}
			
		s+="- - -\n";
		for(int j=btmp+1;j<=lenb;j++){
			
			s+=">"+bline[j]+"\n";
		}
			
	} 
	const char*p=s.c_str();
	strcpy(gTerm.strout,p);
		}
	if(bi[0]==false&&bi[1]==true&&q==false){
		bool match=false;//to see if the condition of -I is satisfied
		if(is==true) sp=icmp(sp);
		int point1 =0;int point2=0;
		/*p1 represents the nmuber of lines that are different but contain the pointed string,
		while p2 represents the number of lines that are exactly the same*/
		if(lena==lenb){
			for(int n=1;n<=lena;n++){
				if(bp[n]!=ap[n]&&bp[n].find(sp)!=-1&&ap[n].find(sp)!=-1){ //if the line in file a and in file b both contains the pointed string 
					point1++; 
				}
				if(bp[n]==ap[n])point2++;
			}
		if(point1+point2==lena)return ;//if the condition of -I is satisfied,our process should exit here
		} 
			
			int count=0;
			int index=1;
		int flag[1001];
		for(int k=0;k<=1000;k++)
			flag[k]=0;
	
	for(int n=1;n<=lena;n++){
		for(int j=index;j<=lenb;j++){
			if(bp[j]==ap[n]){
				index=j+1;
				flag[n]=j;
				count++;
				break; 
			}
		}	 
	}
	
	
	
	int atmp=0;
	int btmp=0;
	
	
	if(count==0){
		 s+="1c1\n";
		for(int i=1;i<=lena;i++) {
			
			s+="<"+aline[i]+"\n";
		}
		s+="- - -\n";
		for(int i=1;i<=lenb;i++) {
			
			s+=">"+bline[i]+"\n";
		}
		
		const char*p=s.c_str();
	    strcpy(gTerm.strout,p);
		return ;
	} 
	
	if(flag[1]>1){
		s+="0a1\n";
		for(int i=1;i<flag[1];i++){
			
			s+=">"+bline[i]+"\n";
		}
			
			atmp=1;btmp=flag[1];
			count--; 
	}
	if(flag[1]==1) {
		atmp=1;btmp=1;count--;
		
	}
	 
	 
	for(int i=2;i<=lena&&count>=0;i++){
		if(flag[i]==1){
			s+="1d0\n";
			for(int j=0;j<flag[i];j++){
				
				s+="<"+aline[j]+"\n";
			}
				
		atmp=i;btmp=flag[i];
		count--;
		continue;
		}
		if(flag[i]>1){
			if(i-atmp==1&&flag[i]-btmp==1){
				atmp=i;btmp=flag[i];count--;
				continue; 
			}
			if(i-atmp==1&&flag[i]-btmp>1) { 
				
				s+=to_string(atmp)+"a"+to_string(btmp+1)+"\n"; 
				for(int j=btmp+1;j<flag[i];j++){
					
					s+=">"+bline[j]+"\n";
				} 
				atmp=i;btmp=flag[i];count--;
				continue;
			}
			if(i-atmp>1&&flag[i]-btmp==1){
				
				s+=to_string(atmp+1)+"d"+to_string(flag[i])+"\n";
				for(int j=atmp+1;j<i;j++){
					
					s+="<"+aline[j]+"\n"; 
				}
				atmp=i;btmp=flag[i];count--;
				continue;
			}
			if(i-atmp>1&&flag[i]-btmp>1){
				
				s+=to_string(atmp+1)+"c"+to_string(btmp+1)+"\n";
				for(int j=atmp+1;j<i;j++){
					
					s+="<"+aline[j]+"\n";
				}
				s+="- - -\n";
				for(int j=btmp+1;j<flag[i];j++){
					
					s+=">"+bline[j]+"\n";
				}
				atmp=i;btmp=flag[i];count--;
				continue;
			} 
		} 
	} 
	if(atmp==lena&&btmp<lenb){
		s+=to_string(atmp+1)+"a"+to_string(btmp+1)+"\n";
		for(int j=btmp+1;j<=lenb;j++){
			s+=">"+bline[j]+"\n";
		}
			
	}
	if(atmp<lena&&btmp==lenb){
		s+=to_string(atmp+1)+"d"+to_string(btmp)+"\n";
		for(int j=atmp+1;j<=lena;j++){
			s+="<"+aline[j]+"\n";
		}
			
	}
	if(atmp<lena&&btmp<lenb){
		s+=to_string(atmp+1)+"c"+to_string(btmp+1)+"\n";
		for(int j=atmp+1;j<=lena;j++){
			
			s+="<"+aline[j]+"\n";
		}
			
		s+="- - -\n";
		for(int j=btmp+1;j<=lenb;j++){
			
			s+=">"+bline[j]+"\n";
		}
			
	} 
	const char*p=s.c_str();
	strcpy(gTerm.strout,p);
	}
	if(bi[0]==true&&q==false){
		if(bi[1]==true){
			int ida=0;int idb=0;
			if(is==true){
				sp=icmp(sp);
			}
			string *af=new string[lena+1]();
			string *bf=new string[lenb+1]();
			for(int i=1;i<=lena;i++){
				if(ap[i]!=""){
					ida++;
					af[ida]=ap[i];
				}
			}
			for(int i=1;i<=lenb;i++){
				if(bp[i]!=""){
					idb++;
					bf[idb]=bp[i];
				}
			}
			if(ida==idb){
				int p1=0;int p2=0;
				for(int i=1;i<=ida;i++){
					if(af[i]!=bf[i]&&af[i].find(sp)!=-1&&bf[i].find(sp)!=-1){
						p1++;
					}
					if(af[i]==bf[i])p2++;
				}
				if(p1+p2==ida){
					delete [] af;
					delete [] bf;
					return;	
				}
			}
			delete [] af;
			delete [] bf;	
		}
		int count=0;
		int index=1;
		int flag[1001];
		for(int k=0;k<=lena;k++)
			flag[k]=0;
	
	for(int n=1;n<=lena;n++){
		for(int j=index;j<=lenb;j++){
			if(bp[j]!=""&&ap[n]!=""&&bp[j]==ap[n]){
				index=j+1;
				flag[n]=j;
				count++;
				break; 
			}
			
		}	 
	}
	
	
	
	int atmp=0;
	int btmp=0;
	
	if(count==0){
		int ak=0;int bk=0;//record the number of blank lines in file a and file b
		int b_not=10000000;int a_not=10000000;
		for(int i=1;i<=lena;i++){
			if(ap[i]=="")ak++;
			else a_not=min(a_not,i);//a_not records the first non-blank line of file a
		}  
		for(int i=1;i<=lenb;i++){
			if(bp[i]=="")bk++;
			else b_not=min(b_not,i);
		}
		if(ak==lena&&bk<lenb){//if file a only has blank lines
			s+="1a"+to_string(b_not)+"\n";
			for(int i=b_not;i<=lenb;i++){
				if(bp[i]!="")
				s+=">"+bline[i]+"\n";
			}
		}
		if(ak<lena&&bk==lenb){
			s+=to_string(a_not)+"d1\n";
			for(int i=a_not;i<=lena;i++){
				if(ap[i]!="")
				s+="<"+aline[i]+"\n";
			}
		}
		if(ak<lena&&bk<lenb){
			s+=to_string(a_not)+"c"+to_string(b_not)+"\n";
			for(int i=a_not;i<=lena;i++){
				if(ap[i]!=""){
					s+="<"+aline[i]+"\n"; 
				}
			}
			s+="- - -\n";
			for(int i=b_not;i<=lenb;i++){
				if(bp[i]!=""){
					s+=">"+bline[i]+"\n";
				}
			}
		}
		const char*p=s.c_str();
		strcpy(gTerm.strout,p);
	    return;
	} 
	
	if(flag[1]>1){
		int b_not=0;
		for(int i=1;i<flag[1];i++){
			if(bp[i]!=""){
				b_not=i;
				break;
			}
		}
		if(b_not>0){
			s+="0a"+to_string(b_not)+"\n";
			for(int i=b_not;i<flag[1];i++){
				if(bp[i]!=""){
					s+=">"+bline[i]+"\n";
				}
			}
		}
		atmp=1;btmp=flag[1];count--;
	}
	if(flag[1]==1) {
		atmp=1;btmp=1;count--;
		
	} 
	for(int i=2;i<=lena&&count>=0;i++){
		if(flag[i]==1){
			int a_not=0;
			for(int j=1;j<i;j++){
				if(ap[j]!=""){
					a_not=j;
					break;
				}
			}
			if(a_not>0){
				s+=to_string(a_not)+"d0\n";
				for(int j=a_not;j<i;j++){
					if(ap[j]!=""){
						s+="<"+aline[j]+"\n";
					}
				}
			}
			atmp=i;btmp=flag[i];
			count--;
			continue;
		}
		if(flag[i]>1){
			if(i-atmp==1&&flag[i]-btmp==1){
				atmp=i;btmp=flag[i];count--;
				continue;
			}
			if(i-atmp==1&&flag[i]-btmp>1) { 
				int b_not=0;
				for(int j=btmp+1;j<flag[i];j++){
					if(bp[j]!=""){
						b_not=j;
						break;
					}	
				}
				if(b_not>0){
					s+=atmp+"a"+to_string(b_not)+"\n";
					for(int j=b_not;j<flag[i];j++){
						if(bp[j]!=""){
							s+=">"+bline[j]+"\n";
						}
					}
				}
				atmp=i;btmp=flag[i];count--;
				continue;
			}
			if(i-atmp>1&&flag[i]-btmp==1){
				int a_not=0;
				for(int j=atmp+1;j<i;j++){
					if(ap[j]!=""){
						a_not=j;
						break;
					}
				} 
				if(a_not>0){
					s+=to_string(a_not)+"d"+to_string(flag[i])+"\n";
					for(int j=a_not;j<i;j++){
						if(ap[j]!=""){
							s+="<"+aline[j]+"\n";
						}
					}
				}
				atmp=i;btmp=flag[i];count--;
				continue;
			}
			if(i-atmp>1&&flag[i]-btmp>1){
				int a_not=10000000;int b_not=10000000;
				int ak=0;int bk=0;
				for(int j=atmp+1;j<i;j++){
					if(ap[j]=="")ak++;
					else a_not=min(a_not,j);
				}
				for(int j=btmp+1;j<flag[i];j++){
					if(bp[j]=="")bk++;
					else b_not=min(b_not,j);
				}
				if(ak==i-atmp-1&&bk<flag[i]-btmp-1){//if  between the two lines is empty
					s+=to_string(atmp+1)+"a"+to_string(b_not)+"\n";
					for(int j=b_not;j<flag[i];j++){
						if(bp[j]!=""){
							s+=">"+bline[j]+"\n";
						}
					} 
				}
				if(ak<i-atmp-1&&bk==flag[i]-btmp-1){
					s+=to_string(a_not)+"d"+to_string(btmp+1)+"\n";
					for(int j=a_not;j<i;j++){
						if(ap[j]!=""){
							s+="<"+aline[j]+"\n";
						}
					}
				}
				if(ak<i-atmp-1&&bk<flag[i]-btmp-1){
					s+=to_string(a_not)+"c"+to_string(b_not)+"\n";
					for(int j=a_not;j<i;j++){
						if(ap[j]!=""){
							s+="<"+aline[j]+"\n";
						}
					}
					s+="- - -\n";
					for(int j=b_not;j<flag[i];j++){
						if(bp[j]!=""){
							s+=">"+bline[j]+"\n";
						}
					}
				}
				atmp=i;btmp=flag[i];count--;
				continue;
			} 
		} 
	} 
	if(atmp==lena&&btmp<lenb){
		int b_not=0;
		for(int i=btmp+1;i<=lenb;i++){
			if(bp[i]!=""){
				b_not=i;
				break;
			}
		}
		if(b_not>0){
			s+=to_string(atmp+1)+"a"+to_string(b_not)+"\n";
			for(int i=b_not;i<=lenb;i++){
				if(bp[i]!=""){
					s+=">"+bline[i]+"\n";
				}
			}
		}	
	}
	if(atmp<lena&&btmp==lenb){
		int a_not=0;
		for(int i=atmp+1;i<=lena;i++){
			if(ap[i]!=""){
				a_not=i;
				break;
			}
		}
		if(a_not>0){
			s+=to_string(a_not)+"d"+to_string(btmp)+"\n";
			for(int i=a_not;i<=lena;i++){
				if(ap[i]!=""){
					s+="<"+aline[i]+"\n";
				}
			}
		}	
	}
	if(atmp<lena&&btmp<lenb){
		int a_not=0;int b_not=0;
		for(int i=atmp+1;i<=lena;i++){
			if(ap[i]!=""){
				a_not=i;
				break;
			}
		}
		for(int i=btmp+1;i<=lenb;i++){
			if(bp[i]!=""){
				b_not=i;
				break;
			}
		}
		if(a_not>0&&b_not==0){
			s+=to_string(a_not)+"d"+to_string(btmp+1)+"\n";
			for(int i=a_not;i<=lena;i++){
				if(ap[i]!=""){
					s+="<"+aline[i]+"\n";
				}
			}
		}
		if(a_not==0&&b_not>0){
			s+=to_string(atmp+1)+"a"+to_string(b_not)+"\n"; 
			for(int i=b_not;i<=lenb;i++){
				if(bp[i]!=""){
					s+=">"+bline[i]+"\n";
				}
			}
		}
		if(a_not>0&&b_not>0){
			s+=to_string(a_not)+"c"+to_string(b_not)+"\n";
			for(int i=a_not;i<=lena;i++){
				if(ap[i]!=""){
					s+="<"+aline[i]+"\n";
				}
			}
			s+="- - -\n";
			for(int i=b_not;i<=lenb;i++){
				if(bp[i]!=""){
					s+=">"+bline[i]+"\n";
				}
			} 
		}
	} 
	const char*p=s.c_str();
	strcpy(gTerm.strout,p);
	} 
}

int normalfind(int k,int s,char *p,char *q,bool _i);
int starfind(int k,int s,char *p,char *q,bool _i);

void doGrep(int argc,char * argv[]){
	int pattern = -1;//the position of pattern
	bool _h = 0;
	bool _H = 0;
	bool _i = 0;
	bool _n = 0;
	bool _c = 0;
	bool _A = 0;
	bool _B = 0;//above: if the command is activated
	bool mf = 0;//mutiplied files
	bool ce = 1;//command error
	int A = 0;
	int B = 0;//the line number of -A and -B
	
	for(int i = 1;i < argc;i++){
		if(*(argv[i]) == '-'){
			if(strcmp(argv[i],"--help") == 0){
				strcpy(gTerm.strout,"Usage: grep [OPTION]... PATTERNS [FILE]...\nSearch for PATTERNS in each FILE.\nExample: grep -i 'hello world' menu.h main.c\n\nOptions:\n--help, display this help text and exit\n-h, suppress the file name prefix on output\n-H, print file name with output lines\n-i, ignore case distinctions in patterns and data\n-n, print line number with output lines\n-c, print only a count of selected lines per FILE\n-B[NUM], print NUM lines of leading context\n-A[NUM], print NUM lines of trailing context\n"); 
				return;
			}	//--helpָ
			if((*(argv[i] + 1) == 'h') && (_H != 1)) {
				_h = 1;
				ce = 0;}
			if((*(argv[i] + 1) == 'H') && (_h != 1)) {
				_H = 1;
				ce = 0;}
			if(*(argv[i] + 1) == 'i'){
				_i = 1;
				ce = 0;}
			if(*(argv[i] + 1) == 'n'){
				_n = 1;
				ce = 0;}
			if(*(argv[i] + 1) == 'c'){
				_c = 1;
				ce = 0;}
			if(*(argv[i] + 1) == 'A'){
				_A = 1;
				A = atoi(argv[i] + 2);
				ce = 0;}
			if(*(argv[i] + 1) == 'B'){
				_B = 1;
				B = atoi(argv[i] + 2);
				ce = 0;}
			if(ce){
				cerr << "grep: " << argv[i] << " :invalid command" << endl;
			}//identify the command 
			ce = 1;
		}else{
			pattern = i;
			break;
		}
	}
	
	
	if(pattern < 0){
		cerr << "grep: please input a pattern" << endl;
		return;
	}//cannot find pattern
	
	if(pattern == argc - 1){
		cerr << "grep: please input a file" << endl;
		return;
	}//cannot find file
	
	if((argc - 1 - pattern) > 1) mf = 1;	//if there are mutiplied files
	
	int length = strlen(argv[pattern]);//length of pattern
	
	ifstream fin;
	
	char load[128]; 
	char **bp = new char *[B];
	for(int i = 0;i < B;i++){
		bp[i] = new char[128];
	}//loading part for -B   
	
	//file module
	for(int f = pattern + 1;f < argc;f++){
	char file[128];//file name
	char stin[100];//strin file name
	bool _f = 0;//if the file is found
	if(argv[f][0] == '/'){
		strcpy(file,gTerm.root);
		strcat(file,argv[f]);
	}else{
		if(strcmp(argv[f],"-") == 0){
			strcpy(stin,gTerm.root);
			strcat(stin,gTerm.wdir);
			strcat(stin,"/-");
			ofstream fout(stin);
			fout << gTerm.strin;
			_f = 1;
		}//loaded from strin
			strcpy(file,gTerm.root);
			strcat(file,gTerm.wdir);
			strcat(file,"/");
			strcat(file,argv[f]);
	}
	fin.open(file); //open file
	
	if(!fin){
		cerr << "grep: " << argv[f] << " :No such file or directory" << endl;
		fin.close();
	}//cannot open file 
	else{
	
	//search module
	char *p = load;
	char *q = argv[pattern];
	int lload = 0;//length of load 
	int record = -1;//the left edge of highlighted part
	int end = -1;//the right edge of highlighted part
	int star_number = 0;//star number in pattern 
	int line_number = 0;//the number of matched lines
	int line = 0;//the sequence number of the loading line
	int Aprint = 0;//the number of lines that are waiting to be printed in command -A
	int Bup = -A-1;//last matched line number(used for command -B)
	
	for(int i = 0;i < length;i++){
		if(*(q + i) == '*'){
		star_number++;
		}
	}//caculate the star number
	
	while(!fin.eof()){
		fin.getline(load,128);
		lload = strlen(load);
		line++;
		
		for(int k = 0;k < lload - length + star_number + 1;k++){
			end = normalfind(k,0,p,q,_i);
			if(end >= 0){
				record = k;
				line_number++;
				break;
			}
		}//execute searching(recusion)
		
		//printing module
		if(!_c){
		if(record >= 0){
			char load2[150];
			char load3[150];
			char load4[150];
			char load5[150];
			for(int i = 0;i < 150;i++){
				load2[i] = 0;
				load3[i] = 0;
				load4[i] = 0;
				load5[i] = 0;
			}
			for(int i = 0;i < record;i++){
				load2[i] = load[i];
			}
			for(int i = 0;i < (end - record + 1);i++){
				load5[i] = load[record + i];
			}
			for(int i = 0;i < (lload - end);i++){
				load4[i] = load[end + i + 1];
			}
			//the part of -B command printing
			if(_B){
				for(int s = 0;s < B;s++){
					if((line - B + s > 0) && (Bup + A < line - B + s)){
						if((mf && !_h) ||(!mf && _H)){
						if(!_f)strcat(gTerm.strout,argv[f]);
						else strcat(gTerm.strout,"(standard input)");
						strcat(gTerm.strout,":");}//show or conceal the file name(the same below)
						if(_n){
						char load6[10];
						string load7;
						stringstream ss;
						ss << line - B + s;
						ss >> load7;
						strcpy(load6,load7.c_str());
						strcat(gTerm.strout,"\e[92;1m");
						strcat(gTerm.strout,load6);
						strcat(gTerm.strout,"\e[94;1m-\e[0m");
						}//show the sequence number(the same below)
						strcat(gTerm.strout,bp[((line%B)+s)%B]);
						strcat(gTerm.strout,"\n");
					}
				}
			}
			//the part of normal printing
			if((mf && !_h) ||(!mf && _H)){
			if(!_f)strcat(gTerm.strout,argv[f]);
			else strcat(gTerm.strout,"(standard input)");
			strcat(gTerm.strout,":");}
			if(_n){
				char load6[10];
				string load7;
				stringstream ss;
				ss << line;
				ss >> load7;
				strcpy(load6,load7.c_str());
				strcat(gTerm.strout,"\e[92;1m");
				strcat(gTerm.strout,load6);
				strcat(gTerm.strout,"\e[94;1m:\e[0m");
			}
			strcat(load3,"\e[91;1m");
			strcat(load3,load5);
			strcat(load3,"\e[0m");
			strcat(gTerm.strout,load2);
			strcat(gTerm.strout,load3);
			strcat(gTerm.strout,load4);
			strcat(gTerm.strout,"\n");
			if(_A)Aprint = A;
			if(_B)Bup = line;
		}else{
			//the part of -A command printing
			if(_A && (Aprint > 0)){
				if((mf && !_h) ||(!mf && _H)){
				if(!_f)strcat(gTerm.strout,argv[f]);
				else strcat(gTerm.strout,"(standard input)");
				strcat(gTerm.strout,":");}
				if(_n){
				char load6[10];
				string load7;
				stringstream ss;
				ss << line;
				ss >> load7;
				strcpy(load6,load7.c_str());
				strcat(gTerm.strout,"\e[92;1m");
				strcat(gTerm.strout,load6);
				strcat(gTerm.strout,"\e[94;1m-\e[0m");
				}
				strcat(gTerm.strout,load);
				strcat(gTerm.strout,"\n");
				Aprint--;
			}
		}
		}
		
		//load the unmatched line for -B
		if(_B){
			strcpy(bp[line%B],load);
		}
		
		record = -1;
		end = -1;
		
	}
	
	//the part of -c command printing
	if(_c){
		char load3[10];
		string load2;
		stringstream ss;
		ss << line_number;
		ss >> load2;
		strcpy(load3,load2.c_str());
		if((mf && !_h) ||(!mf && _H)){
		if(!_f)strcat(gTerm.strout,argv[f]);
		else strcat(gTerm.strout,"(standard input)");
		strcat(gTerm.strout,":");}
		strcat(gTerm.strout,load3);
		strcat(gTerm.strout,"\n");
	}
	
	fin.close();
	}
	if(_f)int rm = remove(stin);//remove the file for loading strin
	}
	delete[] bp;
	return;
}

//searching function when no "*"
int normalfind(int u,int s,char *p,char *q,bool _i){
	int lload = strlen(p);
	int length = strlen(q);
	int i = u;
	int j = s;
	for(;(i < lload) && (j < length);i++,j++){
		if(*(q + j) != '*'){
			if(_i){
				if((*(q + j) >= 'a') && (*(q + j) <= 'z')){
					if((*(p + i) != *(q + j)) && (*(p + i) != *(q + j) - 32))return -1;
				}else if((*(q + j) >= 'A') && (*(q + j) <= 'Z')){
					if((*(p + i) != *(q + j)) && (*(p + i) != *(q + j) + 32))return -1;
				}else{
					if((*(p + i) != *(q + j)) && (*(q + j) != '.'))return -1;//ignore the case sensitivity
				}
			}else{
				if((*(p + i) != *(q + j)) && (*(q + j) != '.'))return -1;
			}
		}else{
			if(j == length - 1)return lload - 1;//special case: * in the end of pattern
			else{
				if(*(q + j + 1) == '*')i--;//unvalid continuous stars
				else {
					return starfind(i,j+1,p,q,_i);
				}
			}
		}
	}
	return i-1;
}

//searching function when encountering "*"
int starfind(int u,int s,char *p,char *q,bool _i){
	int lload = strlen(p);
	int length = strlen(q);
	int star_number = 0;
	for(int v = s;v < length;v++){
		if(*(q + v) == '*'){
		star_number++;
		}
	}
	for(int i = lload - length + s + star_number;i >= u;i--){
		if(!_i){
			if((*(p + i) == *(q + s)) || (*(q + s) == '.')){
				int re = normalfind(i,s,p,q,_i);
				if(re > -1)return re;
			}
		}else{//ignore the case sensitivity
			if((*(p + i) == *(q + s)) || (*(q + s) == '.') || ((*(q + s) >= 'A') && (*(q + s) <= 'Z') && (*(p + i) == *(q + s) + 32)) || ((*(q + s) >= 'a') && (*(q + s) <= 'z') && (*(p + i) == *(q + s) - 32))){
				int re = -1;
				re = normalfind(i,s,p,q,_i);
				if(re > -1)return re;
			}
		}
	}
	return -1;//cannot find matched part
}

void doTee(int argc, char *argv[])
{
    if (argv[1][0] == '-' && argv[1][1] == '-' && argv[1][2] == 'h' && argv[1][3] == 'e' && argv[1][4] == 'l' && argv[1][5] == 'p')
    {
        //--help copy into gTerm.strout
        string teeHelp = "Copy standard input to each FILE, and also to standard output.\n  -a, --append\n        append to the given FILEs, do not overwrite\n  --help display this help and exit\n\0";
        for (int i = 0; i <= teeHelp.length() - 1; i++)
            gTerm.strout[i] = teeHelp[i];
		gTerm.strout[teeHelp.length()]='\0';
    }
    else
    {
        int a = 0;//the -a option
        if (argv[1][0] == '-' && argv[1][1] == 'a') a = 1;
        for (int i = 0; i <= int(strlen(gTerm.strin)); i++)
            gTerm.strout[i] = gTerm.strin[i];
        gTerm.strout[strlen(gTerm.strin) + 1] = '\0';
        if (a == 1)//have the -a option
            for (int i = 2; i <= argc - 1; i++)
            {
                char* FileName = new char[50];
                int f1, f2, f3;
                f1 = int(strlen(gTerm.root));
                f2 = int(strlen(gTerm.wdir));
                f3 = int(strlen(argv[i]));
                for (int j = 0; j <= f1 - 1; j++) FileName[j] = gTerm.root[j];
                for (int j = f1; j <= f1 + f2 - 1; j++) FileName[j] = gTerm.wdir[j - f1];
                FileName[f1 + f2] = '/';
                for (int j = f1 + f2 + 1; j <= f1 + f2 + f3; j++) FileName[j] = argv[i][j - f1 - f2-1];
                FileName[f1 + f2 + f3 + 1] = '\0';
                ofstream fout1(FileName, ofstream::app);
                fout1 << gTerm.strout;
				//fout1<<endl;
                fout1.close();
                delete[]FileName;
            }
        else
            for (int i = 1; i <= argc - 1; i++)
            {
                char* FileName = new char[50];
                int f1, f2, f3;
                f1 = int(strlen(gTerm.root));
                f2 = int(strlen(gTerm.wdir));
                f3 = int(strlen(argv[i]));
                for (int j = 0; j <= f1 - 1; j++) FileName[j] = gTerm.root[j];
                for (int j = f1; j <= f1 + f2 - 1; j++) FileName[j] = gTerm.wdir[j - f1];
                FileName[f1 + f2] = '/';
                for (int j = f1 + f2 + 1; j <= f1 + f2 + f3; j++) FileName[j] = argv[i][j - f1 - f2-1];
                FileName[f1 + f2 + f3 + 1] = '\0';
                ofstream fout2(FileName);
                fout2 << gTerm.strout;
				//fout2 << endl;
                fout2.close();
                delete[]FileName;
            }
    }
    return;
}

void doCat(int argc, char* argv[])
{
	gTerm.strout[0]='\0';
	if (argv[1][0] == '-' && argv[1][1] == '-' && argv[1][2] == 'h' && argv[1][3] == 'e' && argv[1][4] == 'l' && argv[1][5] == 'p')
	{
		//--help copy into the gTerm.strout
		string teeHelp = "Concatenate FILE(s) to standard output.\nWith no FILE, or when FILE is -, read standard input.\n  -b, --number-nonblank\n        number nonempty output lines, overrides -n\n  -E, --show-ends\n        display $ at end of each line\n  -n, --number\n        number all output lines\n  -s, --squeeze-blank\n        suppress repeated empty output lines\n  --help display this help and exit\n\0";
		for (int i = 0; i <= teeHelp.length() - 1; i++)
			gTerm.strout[i] = teeHelp[i];
		gTerm.strout[teeHelp.length()]='\0';
	}
	else
	{
		int b=0, e=0, n=0, s=0;//the options
		int p = 1;//the position of argv
		while (argv[p][0] == '-'&&strlen(argv[p])==2)
		{
			if (argv[p][1] == 'b') b = 1;
			else
				if (argv[p][1] == 'E') e = 1;
			    else
					if (argv[p][1] == 'n') n = 1;
			        else
						if (argv[p][1] == 's') s = 1;
			p++;
		}
		int r = 0;//note the number of line
		int NoteS = 0;//note the empty line
		for (int i = p; i <= argc - 1; i++)
		{
			if (strlen(argv[i]) == 1 && argv[i][0] == '-')
			{
				int q = 0;//the position of gTerm.strin
				//cout<<"AAAAAAA"<<endl;
				while (q <= int(strlen(gTerm.strin)) - 1)
				{
					//cout << "q=" << q << endl;
					//cout<<"BBBBBB"<<endl;
					/*cout<<"q="<<q<<" "<<strlen(gTerm.strin)<<" "<<strlen(gTerm.strin)-1<<endl;
					int p;cin>>p;*/

					int l = q;
					while (gTerm.strin[q] != '\n') q++;
					int l1, l2;
					l1 = strlen(gTerm.strout);
					l2 = q-l;
					if (l2 == 0)
					{
						if (s == 0)
						{
							if (n == 1)
							{
								r++;
								int nr = 0, r2 = r;//nr:the position of numbers
								int sr[6];
								while (r2 != 0)
								{
									nr++;
									sr[nr] = r2 % 10;//get the number in one position
									r2 /= 10;
								}
								for (int i = 1; i <= 6 - nr; i++)
									gTerm.strout[l1 + i - 1] = ' ';
								for (int i = nr; i >= 1; i--)
									gTerm.strout[l1 + 6 - i] = char(sr[i] + '0');
								gTerm.strout[l1 + 6] = ' ';
								gTerm.strout[l1 + 7] = ' ';
								l1 = l1 + 8;
							}
							int End = l1 + l2;
							if (e == 1) { gTerm.strout[End] = '$'; End++; }
							gTerm.strout[End] = '\n';
							gTerm.strout[End+1]='\0';
						}
						if (s == 1 && NoteS == 1) {q++; continue;}
						if (s == 1 && NoteS == 0) NoteS = 1;
						if (n == 1)
						{
							r++;
							int nr = 0, r2 = r;//nr:the position of numbers
							int sr[6];
							while (r2 != 0)
							{
								nr++;
								sr[nr] = r2 % 10;//get the number in one position
								r2 /= 10;
							}
							for (int i = 1; i <= 6 - nr; i++)
								gTerm.strout[l1 + i - 1] = ' ';
							for (int i = nr; i >= 1; i--)
								gTerm.strout[l1 + 6 - i] = char(sr[i] + '0');
							gTerm.strout[l1 + 6] = ' ';
							gTerm.strout[l1 + 7] = ' ';
							l1 = l1 + 8;
						}
						int End = l1 ;
						if (e == 1) { gTerm.strout[End] = '$'; End++; }
						gTerm.strout[End] = '\n';
						gTerm.strout[End+1]='\0';
						q++;
						continue;
					}
					if (s == 1 && NoteS == 1) NoteS = 0;
					if (n == 1 || (b == 1 && l2 != 0))
					{
						r++;
						int nr = 0, r2 = r;//nr:the position of numbers
						int sr[6];
						while (r2 != 0)
						{
							nr++;
							sr[nr] = r2 % 10;//get the number in one position
							r2 /= 10;
						}
						for (int i = 1; i <= 6 - nr; i++)
							gTerm.strout[l1 + i - 1] = ' ';
						for (int i = nr; i >= 1; i--)
							gTerm.strout[l1 + 6 - i] = char(sr[i] + '0');
						gTerm.strout[l1 + 6] = ' ';
						gTerm.strout[l1 + 7] = ' ';
						l1 = l1 + 8;
					}
					for (int i = l1; i <= l1 + l2 - 1; i++)
						gTerm.strout[i] = gTerm.strin[i - l1+l];
					int End = l1 + l2;
					if (e == 1) { gTerm.strout[End] = '$'; End++; }
					gTerm.strout[End] = '\n';
					gTerm.strout[End+1]='\0';
					//cout << "q1=" << q << endl;
					q++;
					//cout << "q2=" << q << endl;
				}
				//cout<<"!!!!!!"<<endl;
				continue;
			}
			char* FileName = new char[50];
			int f1, f2, f3;
			f1 = int(strlen(gTerm.root));
			f2 = int(strlen(gTerm.wdir));
			f3 = int(strlen(argv[i]));
			//cout<<argv[i]<<endl;
			
			if (argv[i][0]=='/')
			{
				for (int j=0;j<=f1-1;j++) FileName[j]=gTerm.root[j];
				for (int j=f1;j<=f1+f3-1;j++) FileName[j]=argv[i][j-f1];
				FileName[f1+f3]='\0';
				/*cout<<f3<<endl;
				cout<<argv[i]<<endl;
				cout<<FileName<<endl;*/
			}
			else
			{
				for (int j = 0; j <= f1 - 1; j++) FileName[j] = gTerm.root[j];
			    for (int j = f1; j <= f1 + f2 - 1; j++) FileName[j] = gTerm.wdir[j - f1];
			    FileName[f1 + f2] = '/';
			    for (int j = f1 + f2 + 1; j <= f1 + f2 + f3; j++) FileName[j] = argv[i][j - f1 - f2 - 1];
			    FileName[f1 + f2 + f3 + 1] = '\0';
			}

			ifstream fin(FileName);
			if (!fin)
			{
				cerr << "cat: " << argv[i] << ": No such file or directory"<<endl;
				continue;
			}
			while (!fin.eof())
			{
				char* ch = new char[200];
				fin.getline(ch,200);
				int l1, l2;
				l1= strlen(gTerm.strout);
				l2 = strlen(ch);
				if (s == 1 && l2 == 0 && NoteS == 1) continue;
				if (s == 1 && l2 == 0 && NoteS == 0) NoteS = 1;
				if (s == 1 && l2 != 0 && NoteS == 1) NoteS = 0;
				if (n == 1||(b==1&&l2!=0))
				{
					r++;
					int nr = 0,r2 = r;//nr:the position of numbers
					int sr[6];
					while (r2 != 0)
					{
						nr++;
						sr[nr] = r2 % 10;//get the number in one position
						r2 /= 10;
					}
					for (int i = 1; i <= 6 - nr; i++)
					  gTerm.strout[l1 + i - 1] = ' ';
					for (int i = nr; i >= 1; i--)
						gTerm.strout[l1 + 6 - i] = char(sr[i] + '0');
					gTerm.strout[l1 + 6] = ' ';
					gTerm.strout[l1 + 7] = ' ';
					l1 = l1 + 8;
				}
				for (int i = l1; i <= l1 + l2 - 1; i++)
					gTerm.strout[i] = ch[i - l1];
				int End = l1 + l2;
				if (e == 1) { gTerm.strout[End] = '$'; End++; }
				gTerm.strout[End] = '\n';
				gTerm.strout[End+1]='\0';
				delete[]ch;
			}
			fin.close();
			delete[]FileName;
		}
		int ed=strlen(gTerm.strout);
		gTerm.strout[ed]='\0';
	}
}

void doCp(int argc, char* argv[])
{
	if (argv[1][0] == '-' && argv[1][1] == '-' && argv[1][2] == 'h' && argv[1][3] == 'e' && argv[1][4] == 'l' && argv[1][5] == 'p')
	{
		//--help copy into gTerm.strout
		string cpHelp = "Copy SOURCE to DEST, or multiple SOURCE(s) to DIRECTORY.\n  -n, --no-clobber\n        do not overwrite an existing file\n  --help display this help and exit\n\0";
		for (int i = 0; i <= cpHelp.length() - 1; i++)
			gTerm.strout[i] = cpHelp[i];
		gTerm.strout[cpHelp.length()]='\0';
	}
	else
	{
		int n=0;
		if (argv[1][0] == '-' && argv[1][1] == 'n') n = 1;
		if (n == 0)
		{
			int p1 = 0, p2 = 0;
			if (strlen(argv[1]) == 1 && argv[1][0] == '-') p1 = 1;
			if (strlen(argv[2]) == 1 && argv[2][0] == '-') p2 = 1;
			if (p1 == 1 || p2 == 1)
			{
				if (p1 == 1 && p2 == 0)
				{
					char* FileName2 = new char[50];
					int f1, f2, f31, f32;
					f1 = int(strlen(gTerm.root));
					f2 = int(strlen(gTerm.wdir));
					f32 = int(strlen(argv[2]));
					for (int j = 0; j <= f1 - 1; j++) { FileName2[j] = gTerm.root[j]; }
					for (int j = f1; j <= f1 + f2 - 1; j++) { FileName2[j] = gTerm.wdir[j - f1]; }
					FileName2[f1 + f2] = '/';
					for (int j = f1 + f2 + 1; j <= f1 + f2 + f32; j++) FileName2[j] = argv[2][j - f1 - f2 - 1];
					FileName2[f1 + f2 + f32 + 1] = '\0';
					ofstream fout(FileName2);
					fout << gTerm.strin << endl;
					fout.close();
					delete[]FileName2;
				}
				if (p1 == 0 && p2 == 1)
				{
					char* FileName1 = new char[50];
					int f1, f2, f31, f32;
					f1 = int(strlen(gTerm.root));
					f2 = int(strlen(gTerm.wdir));
					f31 = int(strlen(argv[1]));
					for (int j = 0; j <= f1 - 1; j++) { FileName1[j] = gTerm.root[j]; }
					for (int j = f1; j <= f1 + f2 - 1; j++) { FileName1[j] = gTerm.wdir[j - f1]; }
					FileName1[f1 + f2] = '/';
					for (int j = f1 + f2 + 1; j <= f1 + f2 + f31; j++) FileName1[j] = argv[1][j - f1 - f2 - 1];
					FileName1[f1 + f2 + f31 + 1] = '\0';
					ifstream fin(FileName1);
					if (!fin)
					{
						cerr << "cp: " << argv[2] << ": No such file or directory";
						return;
					}
					int pt = 0;
					while (fin.eof() == 0)
					{
						char* ch = new char[200];
						fin.getline(ch, 200);
						int lch = strlen(ch);
						for (int i = pt; i <= pt+lch - 1; i++)
							gTerm.strout[i] = ch[i-pt];
						gTerm.strout[pt+lch] = '\n';
						pt += lch + 1;
						//cout << pt << endl;
						delete[]ch;
					}
					gTerm.strout[strlen(gTerm.strout)] = '\0';
					cout << gTerm.strout << endl;
					fin.close();
					delete[]FileName1;
				}
				if (p1 == 1 && p2 == 1)
				{
					int lin = strlen(gTerm.strin);
					for (int i = 0; i <= lin - 1; i++)
						gTerm.strout[i] = gTerm.strin[i];
					gTerm.strout[lin] = '\0';
					cout << gTerm.strout << endl;
				}
				return;
			}
			char* FileName1 = new char[50];
			char* FileName2 = new char[50];
			int f1, f2, f31,f32;
			f1 = int(strlen(gTerm.root));
			f2 = int(strlen(gTerm.wdir));
			f31 = int(strlen(argv[1]));
			f32 = int(strlen(argv[2]));
			for (int j = 0; j <= f1 - 1; j++) { FileName1[j] = gTerm.root[j]; FileName2[j] = gTerm.root[j]; }
			for (int j = f1; j <= f1 + f2 - 1; j++) {FileName1[j] = gTerm.wdir[j - f1]; FileName2[j] = gTerm.wdir[j - f1];}
			FileName1[f1 + f2] = '/';
			FileName2[f1 + f2] = '/';
			for (int j = f1 + f2 + 1; j <= f1 + f2 + f31; j++) FileName1[j] = argv[1][j - f1 - f2 - 1];
			FileName1[f1 + f2 + f31 + 1] = '\0';
			for (int j = f1 + f2 + 1; j <= f1 + f2 + f32; j++) FileName2[j] = argv[2][j - f1 - f2 - 1];
			FileName2[f1 + f2 + f32 + 1] = '\0';
			ifstream fin(FileName1);
			if (!fin)
			{
				cerr << "cp: " << argv[2] << ": No such file or directory";
				return;
			}
			ofstream fout(FileName2);
			while (fin.eof() == 0)
			{
				char* ch = new char[200];
				fin.getline(ch, 200);
				fout << ch << endl;
				delete[]ch;
			}
			fin.close();
			fout.close();
			delete[]FileName1;
			delete[]FileName2;
		}
		else
		{
		    int p1 = 0, p2 = 0;
			if (strlen(argv[2]) == 1 && argv[2][0] == '-') p1 = 1;
			if (strlen(argv[3]) == 1 && argv[3][0] == '-') p2 = 1;
			if (p1 == 1 || p2 == 1)
			{
				if (p1 == 1 && p2 == 0)
				{
					char* FileName2 = new char[50];
					int f1, f2, f31, f32;
					f1 = int(strlen(gTerm.root));
					f2 = int(strlen(gTerm.wdir));
					f32 = int(strlen(argv[3]));
					for (int j = 0; j <= f1 - 1; j++) { FileName2[j] = gTerm.root[j]; }
					for (int j = f1; j <= f1 + f2 - 1; j++) { FileName2[j] = gTerm.wdir[j - f1]; }
					FileName2[f1 + f2] = '/';
					for (int j = f1 + f2 + 1; j <= f1 + f2 + f32; j++) FileName2[j] = argv[3][j - f1 - f2 - 1];
					FileName2[f1 + f2 + f32 + 1] = '\0';
					ofstream fout(FileName2,ofstream::app);
					fout << gTerm.strin << endl;
					fout.close();
					delete[]FileName2;
				}
				if (p1 == 0 && p2 == 1)
				{
					char* FileName1 = new char[50];
					int f1, f2, f31, f32;
					f1 = int(strlen(gTerm.root));
					f2 = int(strlen(gTerm.wdir));
					f31 = int(strlen(argv[3]));
					for (int j = 0; j <= f1 - 1; j++) { FileName1[j] = gTerm.root[j]; }
					for (int j = f1; j <= f1 + f2 - 1; j++) { FileName1[j] = gTerm.wdir[j - f1]; }
					FileName1[f1 + f2] = '/';
					for (int j = f1 + f2 + 1; j <= f1 + f2 + f31; j++) FileName1[j] = argv[2][j - f1 - f2 - 1];
					FileName1[f1 + f2 + f31 + 1] = '\0';
					ifstream fin(FileName1);
					if (!fin)
					{
						cerr << "cp: " << argv[3] << ": No such file or directory";
						return;
					}
					int pt = int(strlen(gTerm.strout));
					while (fin.eof() == 0)
					{
						char* ch = new char[200];
						fin.getline(ch, 200);
						int lch = strlen(ch);
						for (int i = pt; i <= pt+lch - 1; i++)
							gTerm.strout[i] = ch[i-pt];
						gTerm.strout[pt+lch] = '\n';
						pt += lch + 1;
						delete[]ch;
					}
					gTerm.strout[strlen(gTerm.strout)] = '\0';
					cout << gTerm.strout << endl;
					fin.close();
					delete[]FileName1;
				}
				if (p1 == 1 && p2 == 1)
				{
					int lin = strlen(gTerm.strin),lout=strlen(gTerm.strout);
					for (int i = 0; i <= lin - 1; i++)
						gTerm.strout[i+lout] = gTerm.strin[i];
					gTerm.strout[lin+lout] = '\0';
					cout << gTerm.strout << endl;
				}
				return;
			}
			char* FileName1 = new char[50];
			char* FileName2 = new char[50];
			int f1, f2, f31, f32;
			f1 = int(strlen(gTerm.root));
			f2 = int(strlen(gTerm.wdir));
			f31 = int(strlen(argv[2]));
			f32 = int(strlen(argv[3]));
			for (int j = 0; j <= f1 - 1; j++) { FileName1[j] = gTerm.root[j]; FileName2[j] = gTerm.root[j]; }
			for (int j = f1; j <= f1 + f2 - 1; j++) { FileName1[j] = gTerm.wdir[j - f1]; FileName2[j] = gTerm.wdir[j - f1]; }
			FileName1[f1 + f2] = '/';
			FileName2[f1 + f2] = '/';
			for (int j = f1 + f2 + 1; j <= f1 + f2 + f31; j++) FileName1[j] = argv[2][j - f1 - f2 - 1];
			FileName1[f1 + f2 + f31 + 1] = '\0';
			for (int j = f1 + f2 + 1; j <= f1 + f2 + f32; j++) FileName2[j] = argv[3][j - f1 - f2 - 1];
			FileName2[f1 + f2 + f32 + 1] = '\0';
			ifstream fin(FileName1);
			if (!fin)
			{
				cerr << "cp: " << argv[2] << ": No such file or directory";
				return;
			}
			ofstream fout(FileName2,ofstream::app);
			while (fin.eof() == 0)
			{
				char* ch = new char[200];
				fin.getline(ch, 200);
				fout << ch << endl;
				delete[]ch;
			}
			fin.close();
			fout.close();
			delete[]FileName1;
			delete[]FileName2;
		}
	}
}

void doCd(int argc,char *argv[])
{
	if (argv[1][0] == '-' && argv[1][1] == '-' && argv[1][2] == 'h' && argv[1][3] == 'e' && argv[1][4] == 'l' && argv[1][5] == 'p')
	{
		//--help copy into gTerm.strout
		string cdHelp = "Copy SOURCE to DEST, or multiple SOURCE(s) to DIRECTORY.\n  --help display this help and exit\n\0";
		for (int i = 0; i <= cdHelp.length() - 1; i++)
			gTerm.strout[i] = cdHelp[i];
		gTerm.strout[cdHelp.length()]='\0';
	}
	else
	{
		int Path = 0;//Path=0 means relative path
		if (argv[1][0] == '/') Path = 1;//Path=1 means absolute path
		if (Path == 1)
		{
			int q = 0;//the position in gTerm.wdir
			gTerm.wdir[q] = '\0';
			int w = 1,l=int(strlen(argv[1]));
			while (w <= l - 1)
			{
				char* ch = new char[20];
				int pch = 0;
				while (argv[1][w] != '/' && w <= l - 1)
				{
					pch++;
					ch[pch] = argv[1][w];
					w++;
				}
				if (pch == 1 && ch[1] == '.') { w++; continue; }
				if (pch == 2 && ch[1] == '.' && ch[2] == '.')
				{
					w++;
					int r = int(strlen(gTerm.wdir)) - 1;
					while (gTerm.wdir[r] != '/' && r >= 0) r--;
					gTerm.wdir[r] = '\0';
					continue;
				}
				int l1 = int(strlen(gTerm.wdir));
				gTerm.wdir[l1] = '/';
				for (int i = l1 + 1; i <= l1 + pch; i++)
					gTerm.wdir[i] = ch[i - l1];
				gTerm.wdir[l1 + pch + 1] = '\0';
				delete[]ch;
				w++;
			}
		}
		else
		{
			int l1,l2=int(strlen(argv[1]));
			int p = 0;
			while (p <= l2 - 1)
			{
				char* ch = new char[20];
				int pch = 0;
				while (argv[1][p] != '/'&&p<=l2-1)
				{
					pch++;
					ch[pch] = argv[1][p];
					p++;
				}
				if (pch == 1 && ch[1] == '.') {p++;continue;}
				if (pch == 2 && ch[1] == '.' && ch[2] == '.')
				{
					p++;
					l1 = int(strlen(gTerm.wdir));
					int r = l1 - 1;
					while (gTerm.wdir[r] != '/' && r >= 0) r--;
					gTerm.wdir[r] = '\0';
					continue;
				}
				l1 = int(strlen(gTerm.wdir));
				if (l1==1&&gTerm.wdir[0]=='/') l1--;
				gTerm.wdir[l1] = '/';
				for (int i = l1 + 1; i <= l1 + pch; i++)
					gTerm.wdir[i] = ch[i - l1];
				gTerm.wdir[l1+pch+1]='\0';
				delete[]ch;
				p++;
			}
		}
		if (strlen(gTerm.wdir) == 0) {gTerm.wdir[0] = '/'; gTerm.wdir[1] = '\0';}
	}

}
void doPwd(int argc, char* argv[])
{
	if (argc==1) cout << gTerm.wdir << endl;
	else
		if (argv[1][0] == '-' && argv[1][1] == '-' && argv[1][2] == 'h' && argv[1][3] == 'e' && argv[1][4] == 'l' && argv[1][5] == 'p')
	    {
			//--help copy into gTerm.strout
			string teeHelp = "Print the full filename of the current working directory.\n  --help display this help and exit\n\0";
			for (int i = 0; i <= teeHelp.length() - 1; i++)
				gTerm.strout[i] = teeHelp[i];
			gTerm.strout[teeHelp.length()]='\0';
	    }
}

void doEcho(int argc, char * argv[]);

void doEcho(int argc,char *argv[]){
    char help[300]=
        "Usage: Echo the input to the standard output.  -n : do not output the trailing newline\n";
    if(strcmp(argv[1],"--help")==0){
        strcpy(gTerm.strout,help);
        return;
    }
    else if(strcmp(argv[1],"-n")==0){
        strcpy(gTerm.strout,argv[2]);
        for(int i=3;i<argc;i++){
            strcat(gTerm.strout," ");
            strcat(gTerm.strout,argv[i]);
        }
        return;
    }
    else if(argc==1){
        return;
    }
    else{
        strcpy(gTerm.strout,argv[1]);
        for(int i=2;i<argc;i++){
            strcat(gTerm.strout," ");
            strcat(gTerm.strout,argv[i]);
        }
        strcat(gTerm.strout,"\n");
        return;
    }
}

int main(){
    int argc;
    char wrong[100]={};
    char wrong1[2]="'";
    cout<<"Machine Name:";
    cin>>gTerm.mach;
    cout<<"Root Directory:";
    cin>>gTerm.root;
    cout<<"Login:";
    cin>>gTerm.user;
    strcpy(gTerm.wdir,"/");
    cout<<"\e[95;1m"<<gTerm.mach<<gTerm.user<<"\e[0m"<<","<<"\e[96;1mWelcome to Tinyshell.\e[0m"<<endl;
    bool check=true;
    while(1){
        char **argv= new char *[50];
        for(int i=0;i<50;i++){
        argv[i]=new char [500]();   //We have to initialize the dynamic array,or it may cause segmentation fault in debug.
        }                           //But when running Tinyshell.exe,it is always good.
        char **memory= new char *[50];
        for(int i=0;i<50;i++){
        memory[i]=new char [500](); //use () to initialize the dynamic variebleas.
        }
        cout<<"\e[92;1m"<<gTerm.user<<"@"<<gTerm.mach<<"\e[0m"<<":"<<"\e[94;1m"<<gTerm.wdir<<"\e[0m"<<"$ ";
        char usercin[2000]={0};
        if(check){
            check=false;
            cin.ignore();
        }
        //check this in order to avoid the situation of double output when first input. 
        cin.getline(usercin,2000);
        if(strcmp(usercin,"exit")==0){
            for(int t=0;t<50;t++){
            delete argv[t];
            }
        delete []argv;
            for(int t=0;t<50;t++){
            delete memory[t];
            }
        delete []memory;
        cout<<"Thank you for using Tinyshell."<<endl;
        return 0;
        }
        //extra function : exit the process.  && This command cannot be combined.
        char *temp1=strtok(usercin,"|");
        int i=0;
        while(temp1){
            strcpy(memory[i],temp1);
            temp1=strtok(NULL,"|");
            i++;
        }
        //use strtok to break the chars when meeting | .
        int l=1;
        char *temp2=strtok(memory[0]," ");
        while(temp2){
            int j=0;
            for(;j<500;j++){
                strcpy(argv[j],temp2);
                temp2=strtok(NULL," ");
                if(!temp2){
                    break;
                }
            }
            temp2=strtok(memory[l]," ");
            l++;
            argc=j+1;
            if(strcmp(argv[0],"echo")==0){
                doEcho(argc,argv);
                if(!temp2){
                    cout<<gTerm.strout;
                }
                else{
                    strcpy(gTerm.strin,gTerm.strout);
                    memset(gTerm.strout,0,sizeof(gTerm.strout));
                }
            }
            else if(strcmp(argv[0],"diff")==0){
                doDiff(argc,argv);
                if(!temp2){
                    cout<<gTerm.strout;
                }
                else{
                    strcpy(gTerm.strin,gTerm.strout);
                    memset(gTerm.strout,0,sizeof(gTerm.strout));
                }
            }
            else if(strcmp(argv[0],"grep")==0){
                doGrep(argc,argv);
                if(!temp2){
                    cout<<gTerm.strout;
                }
                else{
                    strcpy(gTerm.strin,gTerm.strout);
                    memset(gTerm.strout,0,sizeof(gTerm.strout));
                }
            }
            else if(strcmp(argv[0],"tee")==0){
                doTee(argc,argv);
                if(!temp2){
                    cout<<gTerm.strout;
                }
                else{
                    strcpy(gTerm.strin,gTerm.strout);
                    memset(gTerm.strout,0,sizeof(gTerm.strout));
                }
            }
            else if(strcmp(argv[0],"cat")==0){
                doCat(argc,argv);
                if(!temp2){
                    cout<<gTerm.strout;
                }
                else{
                    strcpy(gTerm.strin,gTerm.strout);
                    memset(gTerm.strout,0,sizeof(gTerm.strout));
                }
            }
            else if(strcmp(argv[0],"cp")==0){
                doCp(argc,argv);
                if(strcmp(argv[argc-1],"-")==0&&!temp2){
                    cout<<gTerm.strout;
                }
                else if(strcmp(argv[argc-1],"-")==0&&temp2){
                    strcpy(gTerm.strin,gTerm.strout);
                    memset(gTerm.strout,0,sizeof(gTerm.strout));
                }
                else if(strcmp(argv[argc-1],"--help")==0){
                    cout<<gTerm.strout;
                }
            }
            else if(strcmp(argv[0],"cd")==0){
                doCd(argc,argv);
                if(strcmp(argv[argc-1],"--help")==0){
                    cout<<gTerm.strout;
                }
            }
            else if(strcmp(argv[0],"pwd")==0){
                doPwd(argc,argv);
                if(!temp2){
                    cout<<gTerm.strout;
                }
                else{
                    strcpy(gTerm.strin,gTerm.strout);
                    memset(gTerm.strout,0,sizeof(gTerm.strout));
                }
            }
            else{
                strcat(wrong,wrong1);
                strcat(wrong,argv[0]);
                strcat(wrong,wrong1);
                cerr<<"\e[91;1m"<<"Error"<<"\e[0m"<<","<<"Command"<<" "<<wrong<<" "<<"not found."<<endl;
                strcpy(wrong,"");
            }
            for(int i=0;i<argc;i++){
                memset(argv[i],0,sizeof(argv[i]));
            }
            //after a single order,clean argv.
        }
        memset(gTerm.strin,0,sizeof(gTerm.strin));
        memset(gTerm.strout,0,sizeof(gTerm.strout));
        memset(usercin,0,sizeof(usercin));
        //after a full command clean all the store.
    }
    return 0;
}
