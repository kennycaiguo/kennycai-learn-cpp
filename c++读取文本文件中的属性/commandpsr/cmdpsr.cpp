#include"stdafx.h"
#include"cmdpsr.h"
#include<fstream>
#include<cstdio>
 

using namespace std;

CCmdParser::CCmdParser():totalScriptLines(0),currentLine(0),currentLineChar(0),m_script(0){}
CCmdParser::~CCmdParser(){Shutdown();}

//��������ű�
bool CCmdParser::LoadScriptFile(char* filename)
{
	 
	//if(!filename) return false;
	ifstream input,input2;
	char tempLine[MAX_LINE_SIZE];

	//��ȡ�ű��ļ���������
	input.open(filename);
	if(!input.is_open()) return false;
	Shutdown();
	while(!input.eof())
	{
		//input.getline(tempLine,MAX_LINE_SIZE,'\n');
		input.getline(tempLine,MAX_LINE_SIZE);
		totalScriptLines++;
	}
	totalScriptLines--;//ȥ��������
	//printf("total lines:%d\n",totalScriptLines);
	input.close();

	//read lines
	input2.open(filename);
	if(!input2.is_open()) return false;
	m_script = new char*[totalScriptLines];
	for(int i=0;i<totalScriptLines;i++)
	{
		//m_script[i]=new char[MAX_LINE_SIZE+1];
		char* tmp=new char[MAX_LINE_SIZE+1];
		//input2.getline(m_script[i],MAX_LINE_SIZE,'\n');
		input2.getline(tmp,MAX_LINE_SIZE);
		//printf("%s\n",tmp);
		//��ÿһ�����ݱ��浽vector
		m_contents.push_back(tmp);
	}
	input2.close();
	//printf("%s",m_script);
	/*for(vector<char*>::iterator it=m_contents.begin();it!=m_contents.end();it++)
	{
		printf("%s\n",*it);
	}*/
	return true;
}
//���������ȡ������
void CCmdParser::ParseCommand(char *destCommand)
{
	int commandSize=0;
	if(!destCommand) return;
	//�ж���Ч�ԣ������ǰ�б��������󣬾ͽ���
	if(currentLine>=totalScriptLines) return;
	//����Ѿ�������ĩβ���ͽ���
	if(currentLineChar>=(int)strlen(m_contents.at(currentLine))) return;
	//��ʼ�������ַ���
	destCommand[0]='\0';
	//�ж��Ƿ���ע��
	if(IsLineComment())
	{
		destCommand[0]='#';
	    destCommand[1]='\0';
	}
	while(currentLineChar<(int)strlen(m_contents.at(currentLine)))
	{
		//����жϿո���߽��������ͷ���
		/*if(m_script[currentLine][currentLineChar]==' ' ||
			m_script[currentLine][currentLineChar]=='\0') return;*/
		if(m_contents.at(currentLine)[currentLineChar]==' '||
			m_contents.at(currentLine)[currentLineChar]=='\0') return;

		//�����ݶ���destCommand
		destCommand[commandSize]=m_contents.at(currentLine)[currentLineChar];
		//�ƶ�ָ��
		commandSize++;
		currentLineChar++;
	}
	//������һ���ո�
	currentLineChar++;
	destCommand[commandSize]='\0';
	printf("%s\n",destCommand);
}

//��������
void  CCmdParser::ParseStringParam(char* destString)
{
	int paramSize=0;
	bool endQuoteFound = false;
	char* tmp=new char[MAX_PARAM_SIZE+1];
	//if(!destString) return;
   //�ж���Ч�ԣ������ǰ�б��������󣬾ͽ���
	if(currentLine>=totalScriptLines) return;
	//����Ѿ�������ĩβ���ͽ���
	if(currentLineChar>=(int)strlen(m_contents.at(currentLine))) return;
	
	destString[0]='\0';
	//������˫����
	/*if(m_contents.at(currentLine)[currentLineChar] =='"')
    {
               endQuoteFound = true;
			   currentLineChar+=2;
    }
	else*/
	currentLineChar++;
	//printf("%s\n",m_contents.at(currentLine));
	while(currentLineChar<(int)strlen(m_contents.at(currentLine)))
	{

		/*if(m_contents.at(currentLine)[currentLineChar] =='"')
            {
               endQuoteFound = true;
            }*/
		/*if(m_contents.at(currentLine)[currentLineChar]=='\0')
			break;*/
		
		tmp[paramSize]=m_contents.at(currentLine)[currentLineChar];
		//printf("%c",destString[paramSize]);
		paramSize++;
		currentLineChar++;
		/* if(m_contents.at(currentLine)[currentLineChar] =='"')
            {
               endQuoteFound = true;
               break;
            }
		if(m_contents.at(currentLine)[currentLineChar]=='\0')
			break;*/
		

	}
	//������˫����
	// if(endQuoteFound) currentLineChar += 2;
    // else 
    currentLineChar++;
	tmp[paramSize]='\0';
	//printf("tmp=%s\n,lenght of tmp=%d",tmp,strlen(tmp));
	 
	//ȥ��˫����
	char* p=new char[strlen(tmp)];
	int y=0;
	 for(int i=0;i<strlen(tmp);i++)
	 {
        if(tmp[i]==' '||tmp[i]=='"') 
		{
			continue;
		}
		p[y]=tmp[i];
		y++;
	 }
	 p[y]='\0';
	//printf("p=%s\n",p);
	strncpy(destString,p,strlen(p));
	
	destString[y]='\0';
	//printf("%s\n",destString);
}

bool  CCmdParser::ParseBoolParam()
{
	int paramSize=0;
	char tmp[MAX_PARAM_SIZE];
	bool boolval=false;
	//�ж���Ч��
	if(currentLine >= totalScriptLines) return false;
    if(currentLineChar >= (int)strlen(m_contents.at(currentLine))) return false;
	while(currentLineChar<(int)strlen(m_contents.at(currentLine)))
	{
		  
		/*if(m_contents.at(currentLine)[currentLineChar]==' '||
			m_contents.at(currentLine)[currentLineChar]=='\0')
			break;*/
		
		tmp[paramSize]=m_contents.at(currentLine)[currentLineChar];
		paramSize++;
		currentLineChar++;

	}
	//�����ո�
	currentLineChar++;
	tmp[paramSize]='\0';
	char res[MAX_PARAM_SIZE]={0};
	//strncpy(res,tmp+1,strlen(tmp));
	//ȥ���ո�
	int y=0;
	for(int i=0;i<strlen(tmp);i++)
	{
		if(tmp[i]==' ')
		{
			continue;
		}
		res[y]=tmp[i];
		y++;
	}
	res[y]='\0';
	//printf("%s:length:%d\n",res,strlen(res));
	char* truestr="true";
	
	if(strncmp(res,truestr,4)==0) 
	{
		//printf("equal\n");
		boolval=true;
		
	}
	else
	{
		//printf("not equal\n");
		boolval=false;
	}
	
	return boolval;
}

int  CCmdParser::ParseIntParam()
{
	int paramSize=0;
	char tmp[MAX_PARAM_SIZE];
	//�ж���Ч��
	if(currentLine >= totalScriptLines) return 0;
    if(currentLineChar >= (int)strlen(m_contents.at(currentLine))) return 0;
	while(currentLineChar<(int)strlen(m_contents.at(currentLine)))
	{
		  
		/*if(m_contents.at(currentLine)[currentLineChar]==' '||
			m_contents.at(currentLine)[currentLineChar]=='\0')
			break;*/
		
		tmp[paramSize]=m_contents.at(currentLine)[currentLineChar];
		paramSize++;
		currentLineChar++;

	}
	//�����ո�
	currentLineChar++;
	tmp[paramSize]='\0';
	//printf("%s\n",tmp);
	return atoi(tmp);
}
float CCmdParser::ParseFloatParam()
{
	int paramSize=0;
	char tmp[MAX_PARAM_SIZE];
	//�ж���Ч��
	if(currentLine >= totalScriptLines) return false;
    if(currentLineChar >= (int)strlen(m_contents.at(currentLine))) return false;
	while(currentLineChar<(int)strlen(m_contents.at(currentLine)))
	{
		  
		if(m_contents.at(currentLine)[currentLineChar]==' ')
			currentLineChar++;
		
		tmp[paramSize]=m_contents.at(currentLine)[currentLineChar];
		paramSize++;
		currentLineChar++;

	}
	//�����ո�
	currentLineChar++;
	tmp[paramSize]='\0';
	//printf("%s\n",tmp);
	return (float)atof(tmp);
}

//�ƶ�����ʼλ��
void CCmdParser::MoveToStart()
{
	currentLine = 0;
   currentLineChar=0;
}
void CCmdParser::MoveToNextLine()
{
      currentLine++;
	  currentLineChar=0;
}
	
	
//�ж��Ƿ���ע��
bool CCmdParser::IsLineComment()
{
	if(m_contents.at(currentLine)[0]=='#') return true;

	return false;
}

//get����
//��ȡ��ǰ�к�
int CCmdParser::GetCurrentLineNum()
{
	return currentLine;
}
//��ȡ������
int CCmdParser::GetTotalLines()
{
	return totalScriptLines;
}
//������
void CCmdParser::Shutdown()
{
	if(m_script)//����ָ�����ͷ������ָ�룬���ͷ������ָ��
	{
		for(int i=0;i<totalScriptLines;i++)
		{
			if(m_script[i])
			{
				delete[] m_script[i];
				m_script[i]=0;
			}
		}
		delete m_script;
		m_script=0;
	}
	currentLine=0;
	currentLineChar=0;
	totalScriptLines=0;
}