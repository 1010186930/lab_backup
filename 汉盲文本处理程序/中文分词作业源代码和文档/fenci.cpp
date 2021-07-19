#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "htptb.c"
#define BOOL				char
#define bool				BOOL
#define TRUE				1
#define FALSE				0
#define MAX_CWORD_LEN			18				//最长的词
#define MAX_SWORD_LEN			256				//最长的句子
#define MAX_SPY_LEN			60                  //最长的拼音
#define	MAX_CDIM			90                  //汉字首字节的最大编码与最小编码的差值，用于判断是否在汉字编码范围
#define	MAX_WORD			10000               //用于在10000个字节数中找换行符
#define	MAX_DATA            48000               //一段中最大的盲文字节数

//不进行索引的单词
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

//词典索引时,字或词不需要索引
char *arrayChineseStop[] = {
"的","吗","么","啊","说","对","在","和","是",
"被","最","所","那","这","有","将","会","与",
"於","于","他","她","它","您","为","欢迎"
};



//标点符号及汉字的标点符号,注意 + - " 这三个符号，因为在搜索的时候需要通过他们进行异或等条件判断

char arrayAsciiSymbol[] ={'!','\\','*','(',')','-','_','+','=','{','}','[',']',':',';','\'','\"',',','<','>','.','?','/','|','@','#','$','%','^','&'};


//汉字词典
typedef struct _WORD_NODE
{
	char	strWord[MAX_CWORD_LEN+1];
	char    strPY[MAX_SPY_LEN];
	// todo ,可以增加 两个字，三个字，四个字，五个字的数组，这样查起来更快
	struct  _WORD_NODE	*nextWord;
	}WORD_NODE;    //定义结构体类型

struct _CH_DICT {
	WORD_NODE	*lstWord;
}CH_DICT[MAX_CDIM][MAX_CDIM];    //定义结构体二维数组变量：词典


char strText[MAX_WORD];  //定义数组存放从文件中读入的字符串
char SEG_LIST[3/2*MAX_WORD];  //定义数组存放分词后的句串
char strPy[MAX_SPY_LEN];
int WNUM_IN = 0;
int WNUM_OUT = 0;



char  *strTrim(char str[]) //对读入字符串的预处理，如果首字符是空格、回车或换行符等，去除待处理字符串中的空格、换行等
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
    str[i-firstpos]=str[i];    //去除待处理字符串中的空格、换行等
  str[i-firstpos]='\0';

  return str;
}

int addDictWord(char *strWord , int len) //存储分词过程中第一个字节和最后一个字节相同的词，是动态数组。
{
	unsigned char firstChar,lastChar;
	WORD_NODE* curLst;
	
	WORD_NODE* newWord ,*curTmp ;
	
	firstChar = strWord[0] ;
	lastChar  = strWord[len-1];
	
	if (firstChar < 161 || lastChar < 161 )	//建立汉字词典，不允许出现非汉字或是汉字的全角符号
		  return -1;
	
	newWord = (WORD_NODE*)malloc(sizeof(WORD_NODE));
	if ( newWord == NULL)
		return -1;
	strcpy(newWord->strWord,strWord);
	newWord->nextWord = NULL;
	
	firstChar -= 161 ;
	lastChar  -= 161 ;      //按词串第一个字节和最后一个字节顺序来存词
	curLst = CH_DICT[firstChar][lastChar].lstWord;

	if( curLst == NULL)		//reinit list;
	{
		CH_DICT[firstChar][lastChar].lstWord = newWord ;

		return 0;
	}
	curTmp = curLst ;    //curLst对应位置上已经存词则顺着指针向后找
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
	
	if (firstChar < 161 || lastChar < 161 )	//建立汉字词典，不允许出现非汉字或是汉字的全角符号
	{  return -1;}
	
	newWord = (WORD_NODE*)malloc(sizeof(WORD_NODE));
	if ( newWord == NULL)
	{		return -1;}
		strcpy(newWord->strWord,strWord);
	strcpy(newWord->strPY,strpy);
	newWord->nextWord = NULL;
	firstChar -= 161 ;
	lastChar  -= 161 ;      //按词串第一个字节和最后一个字节顺序来存词
	curLst = CH_DICT[firstChar][lastChar].lstWord;
	
	if( curLst == NULL)		//reinit list;
	{
		CH_DICT[firstChar][lastChar].lstWord = newWord ;
		return 0;
	}
	
	curTmp = curLst ;    //curLst对应位置上已经存词则顺着指针向后找

	while(curTmp -> nextWord != NULL )
	{
		curTmp = curTmp->nextWord;
} 

	curTmp -> nextWord = newWord ;
	return 0;
} */


void freeDict() //清空addDictWord（）的CH_DICT[i][j].lstWord 链表
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
   

void addSegWord( unsigned char *strWord, int len) //计算分词得到词语的字节数
{
//	const char *cstrPy = ( const char * ) ( char * ) strPy;
	strcat(SEG_LIST , (char*)strWord);
	strcat(SEG_LIST , "|");
	WNUM_OUT = WNUM_OUT + len + 1;
}

int freeSeg() //把\0添入btmp等中，用于btmp等清零
{
    memset(btmp,'\0',sizeof(btmp));
    memset(SEG_LIST,'\0',sizeof(SEG_LIST));
    memset(strText,'\0',sizeof(strText));		
	return 0;
}   

BOOL searchWord( unsigned char *strWord,int len ) //词语匹配
{
	WORD_NODE *curLst,*curTmp;
	unsigned char firstChar,lastChar;

	firstChar = strWord[0] ;
	lastChar  = strWord[len-1];

	firstChar -= 161 ;
	lastChar  -= 161 ;
	curLst = CH_DICT[firstChar][lastChar].lstWord;
	curTmp = curLst;
	if(!strcmp("鼕鼓",(char*)strWord)||!strcmp("三鼕",(char*)strWord)||!strcmp("鼕鼓罢",(char*)strWord)) curTmp=NULL; //个别生僻字导致curTmp出错，比如“鼕”字，因此做这样的处理
	while ( curTmp != NULL ) {			
		if ( strcmp((char *)strWord,curTmp->strWord) == 0)
		{			strcpy(strPy,curTmp->strPY);
		return TRUE;}
		curTmp = curTmp -> nextWord ;
	}
	return FALSE;
}

int segWord ( unsigned char *strText  , int iWordLen , BOOL bChinese )//逆向匹配算法
{
	int i = 0 ,j = 0 , k = 0 , l = 0 , temp=0 , Lft=0 , n=0;
	char np[2]="";
	unsigned char strChar[MAX_CWORD_LEN+1],strChar1[5],strChar2[5],strChar3[7];
	unsigned char SegWord[100][MAX_CWORD_LEN+1];
	BOOL	bFound = FALSE;	
	i = iWordLen  ; 
	if ( FALSE == bChinese )//非汉字串处理，英文或数字
	{			
		//检查 是否在stop数组里
			addSegWord(strText,iWordLen);
		if(!strcmp((char*)strText,""))
		{
			result=ftb((char*)strText);//添加换行符
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
	{		//i表示取出的句子中还未匹配出来的字数
		for ( j = MAX_CWORD_LEN ; j >= 2 ; j -=2 )
		{					//最大词长个汉字
			if ( i < j )     //句子的长度小于最大词长时，进入下次循环减小j
				continue;   
			l = 0 ;
			Lft=strlen((char *)strText)-j-temp;//减去匹配到的词

/*			for ( k=temp , l=0 ; k<temp+j ; k++, l++)
			strChar[l] = strText[k];
			strChar[l] = '\0';       */

			for ( k=Lft , l=0 ; k<Lft+j ; k++, l++)  //逆向最大
			strChar[l] = strText[k];
			strChar[l] = '\0'; 
			if ( 2 == j )  {	//单个汉字
			strcpy((char*)SegWord[n++],(char*)strChar);
			//	addSegWord(strChar,2);
//	result=ptb(getcnchar((char*)strChar));strcat(btmp,result);memset(result,'\0',sizeof(result));
//	strncat(btmp, "000000", 6);//	printf("%s\n",strChar);
							i -= 2 ;
							temp+=j;
							break;
			} 
			bFound = searchWord(strChar , l );  //匹配词典
			if ( TRUE == bFound ) {		
				i -= j;
				temp+=j;
				strcpy((char*)SegWord[n++],(char*)strChar);
//				addSegWord(strChar,2);
//              CH_br((char*)strChar); 
                //PH_br(strPy);    //词语拼音转盲文

			 memset(strPy,'\0',sizeof(strPy));
				break; 
			} else {			
				//1.是否全是外来词
				//2.是否全是数字
				//3.如果第一二字是”姓氏“，则默认为姓名
				//4.判断其它名字
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

void initSegList()//每段的分词链表
{
	int i ;
    for ( i = 0 ; i < MAX_WORD ; i ++ )
    		SEG_LIST[i]='\0';
}

int loadDict(char *strFilename) //对分词库进行按照首字节和末字节存储
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

// 读取词语、拼音库并存储
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
	BOOL		bSep	  	= FALSE ;//是否是分隔符或者是一个词结束
	BOOL		bChinese	= FALSE ;//上一个有效字符类型，
						//false:英文 true: Chinese
	BOOL		bFound		= FALSE ;
	BOOL        bSymbol		= FALSE ;//是否是标点
	unsigned 	char    strWord[MAX_SWORD_LEN + 1]; 		//当前词
	unsigned	char	strChar[3];	//
	unsigned 	char	cChar;			//
	char np[2]="";
	
	memset(strWord,0,sizeof(strWord));
	strChar[0] = '\0';
	  	for ( i = 0 ; i < iTextLen ; i ++ ) {
		cChar    = (unsigned char )strText[i];
		if (128 > cChar) {					//英文字符
			/****连续空格不算分隔 ****/
				if ( ' ' == cChar || '\t' == cChar || '\r' == cChar || '\n' == cChar ){
				if ( TRUE == bChinese ) {			//如果前面一个有效字符是Chinese
					if ( TRUE == bSpace && (' ' == cChar || '\t' == cChar)) 
						bSep = TRUE ;			
					else continue ;				//继续取下一个字符，因为汉字的词可以换行或用空格隔开
				} else  {
					bSep = TRUE ;
				}
			} else { 						
				bSymbol = isAsciiSymbol(cChar);	//判断是否是英文标点
				bSep = bSymbol;
			}     //确定bSep
			if ( (TRUE == bSep || TRUE == bChinese ) &&  iWordLen >= 0 ) {			//一个单词结束
				if ( iWordLen > MAX_SWORD_LEN )
					 iWordLen = MAX_SWORD_LEN;
				strWord[iWordLen] = '\0';    //找到一句可以断开的话，对该句话进行分词
				segWord(strWord,iWordLen,bChinese);
				iWordLen = 0 ;
				if ( bSymbol == TRUE ) {
					strWord[0] = cChar;
					strWord[1] = '\0';
					addSegWord(strWord,1);
		result=ftb((char*)strWord);strcat(btmp,result);memset(result,'\0',sizeof(result));	
									}   //对标点进行分隔输出
			} 
			if ( FALSE == bSep ) {
				strWord[iWordLen] = cChar;
							//同一个单词的字母,并在一起
				iWordLen ++ ;
			}
			bChinese = FALSE ;     //确定bChinese
		} else {							//处理字符Chinese
			if ( FALSE == bChinese && FALSE == bSep && 0 < iWordLen ) {//以前是英文，碰到汉字，就当英文单词结束
				if ( iWordLen > MAX_SWORD_LEN )
					 iWordLen = MAX_SWORD_LEN;
				strWord[iWordLen] = '\0';
				bFound = isEnglishStop(strWord);
				if ( FALSE == bFound ) { //对strWord拆开成单个字节再进行盲文转换
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
				if ( 128 > ((unsigned char)strText[iNexti]) ) {		//单字符<=128，不处理该字符
					continue ;					
				}
			} else {						//最后一个字符是大于128的单字符
				break;
			}
			
			strChar[0] = strText[i];
			strChar[1] = strText[i+1];
			strChar[2] = '\0';
						//是否有可能>128的字符，只有一个字符，如果有需要另外判断，现在默认一定会有至少两个字符同时出现
			bChinese	= TRUE ;				//是汉字Chinese
			i ++ ;						//只需要加1
			
			if (strChar[0] == 0xa1 && strChar[1] == 0xa1 ) {				//Chinese空格,16进制:A1,A1
				if ( TRUE == bSpace )
					bSep = TRUE ;
				else continue ;					//连续Chinese空格
			}else if ( strChar[0] < 176 ) {//中文标点等非汉字字符
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
					if(!strcmp((char*)strChar,"啅")) {	result=ptb(getcnchar((char*)strChar));strcat(btmp,result);memset(result,'\0',sizeof(result));
				strncat(btmp, "000000", 6);} else
				{	result=ftb((char*)strChar); strcat(btmp,result);memset(result,'\0',sizeof(result));	}
								}   //对标点进行分隔输出
			} 
			if ( FALSE == bSep ) {
				strWord[iWordLen++] = strChar[0];
				strWord[iWordLen++] = strChar[1];
			}
		} // end if ord
	} // end for $i 
	
	if ( 0 < iWordLen ) {						//还有未处理的单词
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
	printf("载入词典\n");
	loadDict("d:\\output\\ziguang.txt");
//	loadDict("d:\\output\\ziguang.txt","d:\\output\\拼音.txt");
	initSegList();
	printf("开始翻译\n");
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
    printf("结束汉盲翻译\n");
	return 0 ;
}

