#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "htptb.c"
#define BOOL				char
#define bool				BOOL
#define TRUE				1
#define FALSE				0
#define MAX_CWORD_LEN			18				//��Ĵ�
#define MAX_SWORD_LEN			256				//��ľ���
#define MAX_SPY_LEN			60                  //���ƴ��
#define	MAX_CDIM			90                  //�������ֽڵ�����������С����Ĳ�ֵ�������ж��Ƿ��ں��ֱ��뷶Χ
#define	MAX_WORD			10000               //������10000���ֽ������һ��з�
#define	MAX_DATA            48000               //һ��������ä���ֽ���

//�����������ĵ���
char *arrayEnglishStop[] = {
"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", 
"1", "2", "3", "4", "5", "6", "7", "8", "9", "0",  
"about", "above", "after", "again", "all", "also", "am", "an", "and", "any", "are", "as", "at", 
"back", "be", "been", "before", "behind", "being", "below", "but", "by", 
"can", "click", "do", "does", "done", "each", "else", "etc", "ever", "every", 
"few", "for", "from", "generally", "get", "go", "gone", "has", "have", "hello", "here", "how", 
"if", "in", "into", "is", "just", "keep", "later", "let", "like", "lot", "lots", "made", 
"make", "makes", "many", "may", "me", "more", "most", "much", "must", "my", "need", "no", "not", 
"now", "of", "often", "on", "only", "or", "other", "others", "our", "out", "over", "please", "put", 
"so", "some", "such", "than", "that", "the", "their", "them", "then", "there", "these", "they", 
"this", "try", "to", "up", "us", "very", "want", "was", "we", "well", "what", "when", "where", 
"which", "why", "will", "with", "within", "you", "your", "yourself"
};

//�ʵ�����ʱ,�ֻ�ʲ���Ҫ����
char *arrayChineseStop[] = {
"��","��","ô","��","˵","��","��","��","��",
"��","��","��","��","��","��","��","��","��",
"�","��","��","��","��","��","Ϊ","��ӭ"
};



//�����ż����ֵı�����,ע�� + - " ���������ţ���Ϊ��������ʱ����Ҫͨ�����ǽ������������ж�

char arrayAsciiSymbol[] ={'!','\\','*','(',')','-','_','+','=','{','}','[',']',':',';','\'','\"',',','<','>','.','?','/','|','@','#','$','%','^','&'};


//���ִʵ�
typedef struct _WORD_NODE
{
	char	strWord[MAX_CWORD_LEN+1];
	char    strPY[MAX_SPY_LEN];
	// todo ,�������� �����֣������֣��ĸ��֣�����ֵ����飬��������������
	struct  _WORD_NODE	*nextWord;
	}WORD_NODE;    //����ṹ������

struct _CH_DICT {
	WORD_NODE	*lstWord;
}CH_DICT[MAX_CDIM][MAX_CDIM];    //����ṹ���ά����������ʵ�


char strText[MAX_WORD];  //���������Ŵ��ļ��ж�����ַ���
char SEG_LIST[3/2*MAX_WORD];  //���������ŷִʺ�ľ䴮
char strPy[MAX_SPY_LEN];
int WNUM_IN = 0;
int WNUM_OUT = 0;



char  *strTrim(char str[]) //�Զ����ַ�����Ԥ����������ַ��ǿո񡢻س����з��ȣ�ȥ���������ַ����еĿո񡢻��е�
{
  int firstchar=0;
  int endpos=0;
  int i;
  int firstpos=0;

  for(i=0;str[i]!='\0';i++){
    if(str[i]==' ' || str[i] == '\r' || str [i] == '\n' || str [i]=='\t'){
      if(firstchar==0) firstpos++;
    }
    else{
      endpos=i;
      firstchar=1;
    }
  }

  for(i=firstpos;i<=endpos;i++)
    str[i-firstpos]=str[i];    //ȥ���������ַ����еĿո񡢻��е�
  str[i-firstpos]='\0';

  return str;
}

int addDictWord(char *strWord , int len) //�洢�ִʹ����е�һ���ֽں����һ���ֽ���ͬ�Ĵʣ��Ƕ�̬���顣
{
	unsigned char firstChar,lastChar;
	WORD_NODE* curLst;
	
	WORD_NODE* newWord ,*curTmp ;
	
	firstChar = strWord[0] ;
	lastChar  = strWord[len-1];
	
	if (firstChar < 161 || lastChar < 161 )	//�������ִʵ䣬��������ַǺ��ֻ��Ǻ��ֵ�ȫ�Ƿ���
		  return -1;
	
	newWord = (WORD_NODE*)malloc(sizeof(WORD_NODE));
	if ( newWord == NULL)
		return -1;
	strcpy(newWord->strWord,strWord);
	newWord->nextWord = NULL;
	
	firstChar -= 161 ;
	lastChar  -= 161 ;      //���ʴ���һ���ֽں����һ���ֽ�˳�������
	curLst = CH_DICT[firstChar][lastChar].lstWord;

	if( curLst == NULL)		//reinit list;
	{
		CH_DICT[firstChar][lastChar].lstWord = newWord ;

		return 0;
	}
	curTmp = curLst ;    //curLst��Ӧλ�����Ѿ������˳��ָ�������
	while(curTmp -> nextWord != NULL )
	{
		curTmp = curTmp->nextWord;
	}

	curTmp -> nextWord = newWord ;
	
	return 0;
}

/* int addDictWord1(char *strWord ,char *strpy, int len)
{
	unsigned char firstChar,lastChar;
	WORD_NODE* curLst;
	
	WORD_NODE* newWord ,*curTmp ;
	
	firstChar = strWord[0] ;
	lastChar  = strWord[len-1];
	
	if (firstChar < 161 || lastChar < 161 )	//�������ִʵ䣬��������ַǺ��ֻ��Ǻ��ֵ�ȫ�Ƿ���
	{  return -1;}
	
	newWord = (WORD_NODE*)malloc(sizeof(WORD_NODE));
	if ( newWord == NULL)
	{		return -1;}
		strcpy(newWord->strWord,strWord);
	strcpy(newWord->strPY,strpy);
	newWord->nextWord = NULL;
	firstChar -= 161 ;
	lastChar  -= 161 ;      //���ʴ���һ���ֽں����һ���ֽ�˳�������
	curLst = CH_DICT[firstChar][lastChar].lstWord;
	
	if( curLst == NULL)		//reinit list;
	{
		CH_DICT[firstChar][lastChar].lstWord = newWord ;
		return 0;
	}
	
	curTmp = curLst ;    //curLst��Ӧλ�����Ѿ������˳��ָ�������

	while(curTmp -> nextWord != NULL )
	{
		curTmp = curTmp->nextWord;
} 

	curTmp -> nextWord = newWord ;
	return 0;
} */


void freeDict() //���addDictWord������CH_DICT[i][j].lstWord ����
{
	int i ,j ;
	WORD_NODE *curLst,*curTmp ,*tmp;
	
	for ( i = 0 ; i < MAX_CDIM ; i ++ )
	  for ( j = 0 ; j < MAX_CDIM ; j ++ ) {
			curLst = CH_DICT[i][j].lstWord;
			curTmp = curLst;
			while ( curTmp != NULL ) {
				tmp = curTmp ;
				curTmp = curTmp -> nextWord ;
				free(tmp);
				tmp = ( WORD_NODE *)NULL;
			}
			CH_DICT[i][j].lstWord = (WORD_NODE *)NULL;
	  } 
}
   

void addSegWord( unsigned char *strWord, int len) //����ִʵõ�������ֽ���
{
//	const char *cstrPy = ( const char * ) ( char * ) strPy;
	strcat(SEG_LIST , (char*)strWord);
	strcat(SEG_LIST , "|");
	WNUM_OUT = WNUM_OUT + len + 1;
}

int freeSeg() //��\0����btmp���У�����btmp������
{
    memset(btmp,'\0',sizeof(btmp));
    memset(SEG_LIST,'\0',sizeof(SEG_LIST));
    memset(strText,'\0',sizeof(strText));		
	return 0;
}   

BOOL searchWord( unsigned char *strWord,int len ) //����ƥ��
{
	WORD_NODE *curLst,*curTmp;
	unsigned char firstChar,lastChar;

	firstChar = strWord[0] ;
	lastChar  = strWord[len-1];

	firstChar -= 161 ;
	lastChar  -= 161 ;
	curLst = CH_DICT[firstChar][lastChar].lstWord;
	curTmp = curLst;
	if(!strcmp("����",(char*)strWord)||!strcmp("����",(char*)strWord)||!strcmp("���İ�",(char*)strWord)) curTmp=NULL; //������Ƨ�ֵ���curTmp�������硰�����֣�����������Ĵ���
	while ( curTmp != NULL ) {			
		if ( strcmp((char *)strWord,curTmp->strWord) == 0)
		{			strcpy(strPy,curTmp->strPY);
		return TRUE;}
		curTmp = curTmp -> nextWord ;
	}
	return FALSE;
}

int segWord ( unsigned char *strText  , int iWordLen , BOOL bChinese )//����ƥ���㷨
{
	int i = 0 ,j = 0 , k = 0 , l = 0 , temp=0 , Lft=0 , n=0;
	char np[2]="";
	unsigned char strChar[MAX_CWORD_LEN+1],strChar1[5],strChar2[5],strChar3[7];
	unsigned char SegWord[100][MAX_CWORD_LEN+1];
	BOOL	bFound = FALSE;	
	i = iWordLen  ; 
	if ( FALSE == bChinese )//�Ǻ��ִ�����Ӣ�Ļ�����
	{			
		//��� �Ƿ���stop������
			addSegWord(strText,iWordLen);
		if(!strcmp((char*)strText,""))
		{
			result=ftb((char*)strText);//��ӻ��з�
			strcat(btmp,result); 
			memset(result,'\0',sizeof(result));
			}
		else	{ 
		for(j=0;j<strlen((char*)strText);j++){ 
			memcpy(np,strText+j,1);			
			result=ftb((char*)np);
			strcat(btmp,result);
			memset(result,'\0',sizeof(result));
			memset(np,'\0',sizeof(np));	}
    	strncat(btmp, "000000", 6);
		}
				return 0;	
	}
	while ( i > 1 ) 
	{		//i��ʾȡ���ľ����л�δƥ�����������
		for ( j = MAX_CWORD_LEN ; j >= 2 ; j -=2 )
		{					//���ʳ�������
			if ( i < j )     //���ӵĳ���С�����ʳ�ʱ�������´�ѭ����Сj
				continue;   
			l = 0 ;
			Lft=strlen((char *)strText)-j-temp;//��ȥƥ�䵽�Ĵ�

/*			for ( k=temp , l=0 ; k<temp+j ; k++, l++)
			strChar[l] = strText[k];
			strChar[l] = '\0';       */

			for ( k=Lft , l=0 ; k<Lft+j ; k++, l++)  //�������
			strChar[l] = strText[k];
			strChar[l] = '\0'; 
			if ( 2 == j )  {	//��������
			strcpy((char*)SegWord[n++],(char*)strChar);
			//	addSegWord(strChar,2);
//	result=ptb(getcnchar((char*)strChar));strcat(btmp,result);memset(result,'\0',sizeof(result));
//	strncat(btmp, "000000", 6);//	printf("%s\n",strChar);
							i -= 2 ;
							temp+=j;
							break;
			} 
			bFound = searchWord(strChar , l );  //ƥ��ʵ�
			if ( TRUE == bFound ) {		
				i -= j;
				temp+=j;
				strcpy((char*)SegWord[n++],(char*)strChar);
//				addSegWord(strChar,2);
//              CH_br((char*)strChar); 
                //PH_br(strPy);    //����ƴ��תä��

			 memset(strPy,'\0',sizeof(strPy));
				break; 
			} else {			
				//1.�Ƿ�ȫ��������
				//2.�Ƿ�ȫ������
				//3.�����һ�����ǡ����ϡ�����Ĭ��Ϊ����
				//4.�ж���������
			}
		} // end for j
	} // end while $i > 0 */
		for(n-=1;n>=0;n--){   
			addSegWord(SegWord[n],strlen((char*)SegWord[n])); 
			if(strlen((char*)SegWord[n])==2)
			{ 	HZ_br((char*)SegWord[n]); }
			else  { CH_br((char*)SegWord[n]);}
		}
		return 0;
}

void initSegList()//ÿ�εķִ�����
{
	int i ;
    for ( i = 0 ; i < MAX_WORD ; i ++ )
    		SEG_LIST[i]='\0';
}

int loadDict(char *strFilename) //�Էִʿ���а������ֽں�ĩ�ֽڴ洢
{
	int 	len = 0 , i ,j ;
	FILE 	*fpDict = NULL;
	unsigned char firstChar,lastChar;
	char	sLine[128];

    for ( i = 0 ; i < MAX_CDIM ; i ++ ) {
    	for ( j = 0 ; j < MAX_CDIM ; j ++ ) {
    		CH_DICT[i][j].lstWord = (WORD_NODE *)NULL;
    	}
    }
	fpDict = fopen(strFilename,"r");
	if ( fpDict == ( FILE *)NULL ) {
		 printf("open dict file %s error !\n",strFilename);
		 return -1;	
	}
	while ( !feof(fpDict)) {
		fgets(sLine,128,fpDict);
		strTrim(sLine);
		len = strlen(sLine);
		if ( len < 1 || len > MAX_CWORD_LEN )
			printf("%s error!\n",sLine);
		addDictWord(sLine,len);		
	}	
    fclose(fpDict);
    
    return 0;
}

// ��ȡ���ƴ���Ⲣ�洢
/*int loadDict1(char *strFilename,char *pyFilename)
{
	int 	len = 0 , i ,j ;
	FILE 	*fpDict1 = NULL;
	FILE 	*fpDict2 = NULL;
	unsigned char firstChar,lastChar;
	char	sLine[128];
	char	Spy[128];

    for ( i = 0 ; i < MAX_CDIM ; i ++ ) {
    	for ( j = 0 ; j < MAX_CDIM ; j ++ ) {
    		CH_DICT[i][j].lstWord = (WORD_NODE *)NULL;
    	}
    }
	fpDict1 = fopen(strFilename,"r");
	fpDict2 = fopen(pyFilename,"r");
	if ( fpDict1 == ( FILE *)NULL ) {
		 printf("open dict file %s error !\n",strFilename);
		 return -1;	
	}
	while ( !feof(fpDict2)) {
		fgets(sLine,128,fpDict1);
		fgets(Spy,128,fpDict2);
		strTrim(sLine);
		len = strlen(sLine);
		if ( len < 1 || len > MAX_CWORD_LEN )
			printf("%s error!\n",sLine);
				addDictWord1(sLine,Spy,len);
		p++;
	}	
	 fclose(fpDict1);
    fclose(fpDict2);
    return 0;
}  */


BOOL isEnglishStop(unsigned char *strWord)
{
	//arrayEnglishStop
	return  FALSE ;
}
inline BOOL  isAsciiSymbol (char cChar)
{
	int i = 0 ;
	
	for ( i = 0 ; i < sizeof(arrayAsciiSymbol) ; i ++ ) 
		 if ( cChar == arrayAsciiSymbol[i])
		 		return TRUE;
	return FALSE;
}

int segSentence (char *strText ,BOOL bSpace ) 
{	
	int 		iTextLen 	= strlen(strText) ;
	int 		iWordLen=  0 ;			
	int			i		= 0 ;
	int         j=0;
	int         a=0;
	int			iNexti		= 0 ;
	BOOL		bSep	  	= FALSE ;//�Ƿ��Ƿָ���������һ���ʽ���
	BOOL		bChinese	= FALSE ;//��һ����Ч�ַ����ͣ�
						//false:Ӣ�� true: Chinese
	BOOL		bFound		= FALSE ;
	BOOL        bSymbol		= FALSE ;//�Ƿ��Ǳ��
	unsigned 	char    strWord[MAX_SWORD_LEN + 1]; 		//��ǰ��
	unsigned	char	strChar[3];	//
	unsigned 	char	cChar;			//
	char np[2]="";
	
	memset(strWord,0,sizeof(strWord));
	strChar[0] = '\0';
	  	for ( i = 0 ; i < iTextLen ; i ++ ) {
		cChar    = (unsigned char )strText[i];
		if (128 > cChar) {					//Ӣ���ַ�
			/****�����ո���ָ� ****/
				if ( ' ' == cChar || '\t' == cChar || '\r' == cChar || '\n' == cChar ){
				if ( TRUE == bChinese ) {			//���ǰ��һ����Ч�ַ���Chinese
					if ( TRUE == bSpace && (' ' == cChar || '\t' == cChar)) 
						bSep = TRUE ;			
					else continue ;				//����ȡ��һ���ַ�����Ϊ���ֵĴʿ��Ի��л��ÿո����
				} else  {
					bSep = TRUE ;
				}
			} else { 						
				bSymbol = isAsciiSymbol(cChar);	//�ж��Ƿ���Ӣ�ı��
				bSep = bSymbol;
			}     //ȷ��bSep
			if ( (TRUE == bSep || TRUE == bChinese ) &&  iWordLen >= 0 ) {			//һ�����ʽ���
				if ( iWordLen > MAX_SWORD_LEN )
					 iWordLen = MAX_SWORD_LEN;
				strWord[iWordLen] = '\0';    //�ҵ�һ����ԶϿ��Ļ����Ըþ仰���зִ�
				segWord(strWord,iWordLen,bChinese);
				iWordLen = 0 ;
				if ( bSymbol == TRUE ) {
					strWord[0] = cChar;
					strWord[1] = '\0';
					addSegWord(strWord,1);
		result=ftb((char*)strWord);strcat(btmp,result);memset(result,'\0',sizeof(result));	
									}   //�Ա����зָ����
			} 
			if ( FALSE == bSep ) {
				strWord[iWordLen] = cChar;
							//ͬһ�����ʵ���ĸ,����һ��
				iWordLen ++ ;
			}
			bChinese = FALSE ;     //ȷ��bChinese
		} else {							//�����ַ�Chinese
			if ( FALSE == bChinese && FALSE == bSep && 0 < iWordLen ) {//��ǰ��Ӣ�ģ��������֣��͵�Ӣ�ĵ��ʽ���
				if ( iWordLen > MAX_SWORD_LEN )
					 iWordLen = MAX_SWORD_LEN;
				strWord[iWordLen] = '\0';
				bFound = isEnglishStop(strWord);
				if ( FALSE == bFound ) { //��strWord�𿪳ɵ����ֽ��ٽ���ä��ת��
		/*		    addSegWord(strWord,1);
					for(j=0;j<strlen((char*)strWord);j++){ 
							memcpy(np,strWord+j,1);			
						result=ftb((char*)np);strcat(btmp,result);memset(result,'\0',sizeof(result));memset(np,'\0',sizeof(np));	}
						strncat(btmp, "000000", 6); */
					segWord(strWord,iWordLen,bChinese);
							} // end if 
				iWordLen = 0 ;
			} 

			iNexti	= i + 1 ;
			if ( iNexti <  iTextLen ) {
				if ( 128 > ((unsigned char)strText[iNexti]) ) {		//���ַ�<=128����������ַ�
					continue ;					
				}
			} else {						//���һ���ַ��Ǵ���128�ĵ��ַ�
				break;
			}
			
			strChar[0] = strText[i];
			strChar[1] = strText[i+1];
			strChar[2] = '\0';
						//�Ƿ��п���>128���ַ���ֻ��һ���ַ����������Ҫ�����жϣ�����Ĭ��һ���������������ַ�ͬʱ����
			bChinese	= TRUE ;				//�Ǻ���Chinese
			i ++ ;						//ֻ��Ҫ��1
			
			if (strChar[0] == 0xa1 && strChar[1] == 0xa1 ) {				//Chinese�ո�,16����:A1,A1
				if ( TRUE == bSpace )
					bSep = TRUE ;
				else continue ;					//����Chinese�ո�
			}else if ( strChar[0] < 176 ) {//���ı��ȷǺ����ַ�
				bSep = TRUE ;
				bSymbol = TRUE ;
			}else bSep = FALSE;
			
			if ( TRUE == bSep &&  iWordLen >= 0 ) {
				if ( iWordLen > MAX_SWORD_LEN )
					 iWordLen = MAX_SWORD_LEN;
				strWord[iWordLen] = '\0';
				segWord(strWord,iWordLen,bChinese);
				iWordLen = 0 ;
				if ( bSymbol == TRUE ) {
					addSegWord(strChar,2);
					if(!strcmp((char*)strChar,"��")) {	result=ptb(getcnchar((char*)strChar));strcat(btmp,result);memset(result,'\0',sizeof(result));
				strncat(btmp, "000000", 6);} else
				{	result=ftb((char*)strChar); strcat(btmp,result);memset(result,'\0',sizeof(result));	}
								}   //�Ա����зָ����
			} 
			if ( FALSE == bSep ) {
				strWord[iWordLen++] = strChar[0];
				strWord[iWordLen++] = strChar[1];
			}
		} // end if ord
	} // end for $i 
	
	if ( 0 < iWordLen ) {						//����δ����ĵ���
		if ( iWordLen > MAX_SWORD_LEN )
			 iWordLen = MAX_SWORD_LEN;
		strWord[iWordLen] = '\0';
		segWord(strWord,iWordLen,bChinese);
		iWordLen = 0 ;	
	}
	return 0;
}

int main()//int argc,char *argv[])
{
   	FILE 	*fpIn = NULL;
	FILE 	*fpdataOut = NULL;
	FILE 	*fpfcOut = NULL;
	int i ;

    for ( i = 0 ; i < MAX_WORD ; i ++ )
    		strText[i]='\0';

	fpIn = fopen("d:\\output\\input.txt","r");
	if( fpIn==( FILE *)NULL){
		printf("input.txt cannot be  opened\n");
		return -1;
	}

//	fseek(fpIn,0,SEEK_END);
//	WNUM_IN = ftell ( fpIn ) ;
//	rewind(fpIn);
//	fread ( strText , WNUM_IN , 1 , fpIn );
//	fclose(fpIn);
	fpdataOut = fopen("d:\\output\\data.txt","w");
	if( fpdataOut==( FILE *)NULL){
		printf("data.txt cannot be  created\n");
		return -1;
	} 
	fpfcOut = fopen("d:\\output\\output.txt","w");
	if( fpfcOut==( FILE *)NULL){
		printf("output.txt cannot be  created\n");
		return -1;
	} 
	printf("����ʵ�\n");
	loadDict("d:\\output\\ziguang.txt");
//	loadDict("d:\\output\\ziguang.txt","d:\\output\\ƴ��.txt");
	initSegList();
	printf("��ʼ����\n");
	while(1) {
		fgets(strText,10001,fpIn);//i++;
        segSentence (strText ,FALSE ) ;
		fwrite ( SEG_LIST , WNUM_OUT , 1 , fpfcOut );
        fputc('\n',fpfcOut);
        WNUM_OUT=0;
        fputs(btmp,fpdataOut);
        fputc('\n',fpdataOut);
    	freeSeg(); 
		if(feof ( fpIn ) )
			break;
	}
	fclose(fpIn);
	fclose(fpdataOut);
    fclose(fpfcOut);
    freeDict();
    printf("������ä����\n");
	return 0 ;
}

