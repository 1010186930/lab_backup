#include <QCoreApplication>
#include<iostream>
#include "liblious_linux_pc.h"
#include "liblious_linux_pc_global.h"
#include "internal.h"
#include "lib_depend/internal.h"
#include "lib_depend/progname.h"
#include "lib_depend/unistr.h"
#include "lib_depend/version-etc.h"
#include <string>
#include <QDebug>
#include <cstring>
using namespace std;
string widcharto01dot(widechar const* chars,const int len)
{
    char lib[64][7] = { "000000","100000","010000","110000","001000","101000","011000","111000",
                        "000100","100100","010100","110100","001100","101100","011100","111100",
                        "000010","100010","010010","110010","001010","101010","011010","111010" ,
                        "000110","100110","010110","110110","001110","101110","011110","111110" ,
                        "000001","100001","010001","110001","001001","101001","011001","111001" ,
                        "000101","100101","010101","110101","001101","101101","011101","111101" ,
                        "000011","100011","010011","110011","001011","101011","011011","111011" ,
                        "000111","100111","010111","110111","001111","101111","011111","111111" };

    string dotout="";
    //printf("盲文01点序：\n");

    for (int i = 0; i < len; i++)
    {


        if (32768 <= chars[i]&&chars[i]<=32831) {
            //cout << chars[i] << endl;

            int subscript = chars[i] - 32768;
            for (size_t j = 0; j < 6; j++)
            {
                dotout= dotout+lib[subscript][j];
            }


        }
        else {
           printf("#找不到%u#", chars[i]);
           for (size_t j = 0; j < 6; j++)
           {
               dotout = dotout + lib[0][j];
           }

        }


    }
    return dotout;
}
char* widchartoascii(widechar const* chars, const int len, char* ascii) {

    char lib[64]= { ' ','a','1','b','\'','k','2','l',
                   '`','c','i','f','/','m','s','p',
                   '"','e','3','h','9','o','6','r',
                   '^','d','j','g','>','n','t','q',
                   ',','*','5','<','-','u','8','v',
                   '.','%','[','$','+','x','!','&',
                   ';',':','4','\\','0','z','7','(',
                   '_','?','w',']','#','y',')','=',
    };
    //char ascii[MAXSTRING];

    //printf("盲文ascii码：\n");
    for (int i = 0; i < len; i++)
    {
        if (32768 <= chars[i] && chars[i] <= 32831) {

            int subscript = chars[i] - 32768;

            ascii[i]=lib[subscript];

        }
        else {
            printf("\n#找不到%u#\n", chars[i]);
            ascii[i] = lib[0];

        }
    }
    return 0;
}

void translate_input_plus(int forward_translation, char* table_name, FILE* input
                          ,int flag_N,QList<QString> &s_dot
                          ,QStringList &s_ascii
                          ,QStringList &s_unicode
                          ,QStringList &s_number) {

    s_dot.clear();
    s_ascii.clear();
    s_unicode.clear();
    s_number.clear();
    char charbuf[MAXSTRING] = { 0 };
    char hyphens[MAXSTRING] = { 0 };
    uint8_t* outputbuf;
    size_t outlen;
    widechar inbuf[MAXSTRING] = { 0 };
    formtype *type=0x0000;
    widechar transbuf[MAXSTRING];
    int inlen;
    int translen;
    int k;
    int ch;
    int result;
    while (1) {
        translen = MAXSTRING;
        k = 0;
        //while ((ch = fgetc(input)) != '\n' && ch != EOF && k < MAXSTRING - 1)//回车也可以翻译
        int MaxSize = MAXSTRING / 4;
        while ((ch = fgetc(input)) != EOF && k < MaxSize -1)

        {
            if ((k == MaxSize - 4) && ch >= 240) { //防止将四字节的符号切分
                    //printf("%d\n", ch);
                    fseek(input,-1,1 );
                    break;
                }
            if ((k == MaxSize - 3) && ch >= 224) {//防止将三字节的符号切分
                //printf("%d\n", ch);
                fseek(input, -1, 1);
                break;
            }
            if ((k == MaxSize - 2) && ch >= 192) {//防止将二字节的符号切分
               //printf("%d\n", ch);
                fseek(input, -1, 1);
                break;
            }
            if (k == MaxSize - 2) {
                fseek(input, -1, 1);
            }

            charbuf[k++] = ch;
            //printf("%d\n", ch);

            }

        if (ch == EOF&&k == 0) break;
        charbuf[k] = 0;

        inlen = _lou_extParseChars(charbuf, inbuf);


        if (forward_translation)
            result = lou_translateString(
                table_name, inbuf, &inlen, transbuf, &translen, type, NULL, 4);
        else
            result = lou_backTranslateString(
                table_name, inbuf, &inlen, transbuf, &translen, NULL, NULL, 0);
        if (!result) break;

        //#ifdef WIDECHARS_ARE_UCS4
        outputbuf = u32_to_u8(transbuf, translen, NULL, &outlen);//将得到的32位无符号整型转换为8位
        //#else
               // outputbuf = u16_to_u8(transbuf, translen, NULL, &outlen);

          //_lou_showString(widechar const* chars, int length, int forceHex);const char *EXPORT_CALL

        char outstring[MAXSTRING*6] = { 0 };
        strcpy(outstring, _lou_showString(transbuf, translen, 2));//返回盲文字符对应十六进制的字符集
        QString str_outstring = QString::fromUtf8(outstring);
        s_unicode.append(str_outstring);



        char dotshow[MAXSTRING*6] = {0};
        strcpy(dotshow,_lou_showDots(transbuf, translen));//获得盲文数字点序
        QString str_dotshow = QString::fromUtf8(dotshow);
        s_number.append(str_dotshow);




        char asciiout[MAXSTRING] = {0};
        widchartoascii(transbuf, translen,asciiout);
       //转为盲文ASCII码
        QString str_asciiout = QString::fromUtf8(asciiout);
        s_ascii.append(str_asciiout);




        string dotout="";
        dotout=widcharto01dot(transbuf, translen);//转为01点序
        QString q_dotout = QString::fromStdString(dotout);
        s_dot.append(q_dotout);




        free(outputbuf);

    }

    lou_free();
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList m_s_dot;
    QStringList m_s_ascii;
    QStringList m_s_unicode;
    QStringList m_s_number;
    m_s_dot.clear();
    m_s_ascii.clear();
    m_s_unicode.clear();
    m_s_number.clear();
    Liblious_linux_pc liblious;
    FILE *fp = NULL;
    int flag_n;
    fp = fopen("./trans_temp.txt", "r");
    QString demo_s;
    char *demo;
    demo_s = "./tables/zh-chn.ctb";
    QByteArray ba = demo_s.toLatin1(); // must
    demo=ba.data();
    translate_input_plus(1,demo,fp,flag_n,m_s_dot,
                m_s_ascii,
                m_s_unicode,
                m_s_number);
    for(int i=0;i<m_s_dot.size();i++)
    {
       qDebug()<<m_s_dot.at(i);
    }
    for(int i=0;i<m_s_number.size();i++)
    {
       qDebug()<<m_s_number.at(i);
    }
    return a.exec();
}
