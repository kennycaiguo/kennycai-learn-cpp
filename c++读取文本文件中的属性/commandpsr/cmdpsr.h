
#ifndef _CMDPSR_H_
#define _CMDPSR_H_
#include<vector>
using namespace std;//���������
#define MAX_COMMAND_SIZE   32
#define MAX_LINE_SIZE      3072
#define MAX_PARAM_SIZE     2048
 

class CCmdParser
{
public:
	CCmdParser();
	~CCmdParser();

	//��������ű�
	bool LoadScriptFile(char* filename); 
	//���������ȡ������
	void ParseCommand(char *destCommand);
	//��������
	void  ParseStringParam(char* destString);
	bool  ParseBoolParam();
	int   ParseIntParam();
	float ParseFloatParam();

	//�ƶ������׻�����һ��
	void MoveToStart();
	void MoveToNextLine();
	
	
	//�ж��Ƿ���ע��
	bool IsLineComment();

	//get����
	//��ȡ��ǰ�к�
	int GetCurrentLineNum();
	//��ȡ������
	int GetTotalLines();
	//������
	void Shutdown();
private:
	  int totalScriptLines;
      int currentLine;//��ǰ��
      int currentLineChar;//��ǰ�еĵ�ǰ��n���ַ�
      char **m_script;
	  vector<char*> m_contents;
};


#endif