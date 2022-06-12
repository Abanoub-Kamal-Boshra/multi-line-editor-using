#include <stdio.h>
#include <stdlib.h>
#include "E:\ITI_IoT\08- c\tools\MyLibrary.h"

    ///------------------------------ multi line editor ----------------------------///


/// --------- Menu Macros ---------
#define NULL        '\0'
#define LINE_ARRAY_SIZE     50
#define highlight   0X70
#define normal      0X07
#define RIGHT       77
#define UP          72
#define DOWN        80
#define LEFT        75
#define HOME        71
#define END         79
#define ESC         27
#define ENTER       13
#define BACK_SPACE  8
#define DELETE      83



void main()
{
    char** PCurrent;
    //char *PFirst,*PCurrent,*PLast,*PTemp;

    char** MultiLineArr = (char**) malloc(sizeof(char*));
    MultiLineArr[0] = (char*) malloc(LINE_ARRAY_SIZE * sizeof(char));

    char character, EndFlag=0, XCurrent,YCurrent,XLast,YLast,XFirst,YFirst ,Temp1,Temp2;

    //PFirst=PCurrent=PLast=MultiLineArr[0];
    PCurrent = MultiLineArr;
    ///variables as index
    XCurrent=YCurrent=XLast=YLast=XFirst=YFirst=0;

    int* LastCharIndex = (int) malloc(sizeof(int));

    gotoxy(10,10);
    do
    {

        character = getch();
        if(character == 0 || character ==-32)   // check if extended key
            character = getch();

        switch(character)
        {
        case LEFT:  // to move the cursor left one digit
            //PCurrent[YCurrent][XCurrent]--;//PCurrent--;
            XCurrent--;

            if(XCurrent < XFirst)     // check if at the first digit in the line
            {
                //PCurrent = PFirst;
                XCurrent = XFirst;
            }
            gotoxy(10+XCurrent,10+YCurrent);
            break;
        case RIGHT:     // to move the cursor right one digit
            //PCurrent[YCurrent][XCurrent]++;//PCurrent++;
            XCurrent++;
            if(XCurrent >= (LINE_ARRAY_SIZE-1) || XCurrent >= XLast)   // check if the cursor at the end of the line or at the end of entered characters
            {
                //PCurrent = PLast;
                XCurrent = XLast;
            }
            gotoxy(10+XCurrent,10+YCurrent);
            break;
        case UP:
            YCurrent --;
            if(YCurrent<YFirst)
                YCurrent = YFirst;
            if(LastCharIndex[YCurrent] < XCurrent)
                XCurrent = LastCharIndex[YCurrent];
            XLast = LastCharIndex[YCurrent];
            gotoxy(10+XCurrent,10+YCurrent);
            break;
        case DOWN:
            YCurrent ++;
            if(YCurrent >= YLast)
                YCurrent = YLast;
            if(LastCharIndex[YCurrent] < XCurrent)
                XCurrent = LastCharIndex[YCurrent];
            XLast = LastCharIndex[YCurrent];
            gotoxy(10+XCurrent,10+YCurrent);
            break;
        case HOME:      // to move the cursor at the first digit in the line
            //PCurrent[YCurrent][XCurrent] = MultiLineArr;//PCurrent = PFirst;
            XCurrent = XFirst;
            YCurrent = YFirst;
            gotoxy(10+XCurrent,10+YCurrent);
            break;
 /*
        case END:       // to move the cursor at the last character entered in the line
            //PCurrent = PLast;
            XCurrent = XLast;
            YCurrent = YLast;
            gotoxy(10+XCurrent,10+YCurrent);
            break;
*/
        case ESC:       // to exit from the editor
            EndFlag =1;
            break;
        case ENTER:     // to
            if(XCurrent == XLast)
            {
                LastCharIndex[YCurrent] = XLast;
                YCurrent ++;
                YLast ++;
                XCurrent = XFirst;
                XLast = XFirst;
                MultiLineArr = realloc(MultiLineArr , (YCurrent+1)*sizeof(char*));
                gotoxy(10+XCurrent,10+YCurrent);
            }
            break;
/*
        case BACK_SPACE:    // to delete the back character from the cursor
            if( XCurrent==XLast && XCurrent !=0 )     // if the cursor at the end of entered characters
            {
                PCurrent--;
                PLast--;
                XCurrent--;
                XLast--;
                if(XCurrent < XFirst)     // if we delete all characters already
                {
                    PCurrent = PFirst;
                    XCurrent = XFirst;    // keep the cursor at the begin of the line
                }
                *PCurrent = NULL;

                clrscr();
                gotoxy(10,10);
                printf("%s",MultiLineArr[0]);
            }
            else if(XCurrent < XLast)     // to delete character inside the entered characters
            {
                PTemp = PCurrent;
                while(*PTemp != NULL)   // loop to shift all characters after the deleted char one digit left
                {
                    *PTemp = *(PTemp+1);
                    PTemp++;
                }
                PLast--;
                XLast--;
                clrscr();
                gotoxy(10,10);
                printf("%s",MultiLineArr[0]);
            }
            break;
        case DELETE:    // to delete front character from the cursor
            if( XCurrent==XLast );

            else if(XCurrent < XLast)
            {
                PTemp = PCurrent+1;
                while(*PTemp != NULL)   // loop to shift all characters after the deleted char one digit left
                {
                    *PTemp = *(PTemp+1);
                    PTemp++;
                }
                PLast--;
                XLast--;
                clrscr();
                gotoxy(10,10);
                printf("%s",MultiLineArr[0]);
            }
            break;
*/
        default:    // to print char on the screen and save it in the memory (array)
            if(XCurrent < LINE_ARRAY_SIZE)   // line boundary check
            {
                if( XCurrent==XLast )     // to insert a char at the last of entered characters
                {
                    PCurrent[YCurrent][XCurrent] = character;//*PCurrent= character;
                    PCurrent[YCurrent][XCurrent+1] = NULL;
                    //PCurrent++;
                    //PLast++;
                    //*PLast = '\0';

                    gotoxy(10+XCurrent , 10+YCurrent);
                    printf("%c", character);
                    XCurrent++;
                    XLast++;
                }
                /*
                else if(XCurrent < XLast)     // to insert a char inside the entered characters
                {
                    PTemp = PCurrent;
                    Temp1 = *PCurrent;
                    *PCurrent = character;
                    do      // loop to shift all characters after the inserted char one digit right
                    {
                        PTemp++;
                        Temp2=*PTemp;
                        *PTemp = Temp1 ;
                        Temp1 = Temp2;

                    }while(*PTemp != NULL);

                    PCurrent++;
                    PLast++;
                    XLast++;
                    XCurrent++;
                    clrscr();
                    gotoxy(10,10);
                    printf("%s",MultiLineArr[0]);


                }
                */
            }
            break;
        }

    }while(EndFlag == 0);

    free(MultiLineArr);
    free(LastCharIndex);

}
