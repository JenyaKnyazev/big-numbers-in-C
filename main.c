#include <stdio.h>
#include <stdlib.h>
/*
    made by Jenya Knyazev
*/
/*
    the pointer to char its to represents big numbers as a char arrays every char represents one digit
*/
char *p=NULL;
char *p2=NULL;
char *result=NULL;
int p_size=0;
int p2_size=0;
/*
    scanning string from buffer and put it in the pointer and return the length
    the length including the '\0' end of string
    the buffer need to be clean before using this function
*/
int scan_string(char **str){
    *str=NULL;
    int length=0;
    char ch;
    do{
        ch=getchar();
        length++;
        *str=(char *)realloc(*str,sizeof(char)*length);
        *((*str)+length-1)=ch;
    }while(ch!='\n');
    *((*str)+length-1)='\0';
    return length;
}
/*
    just removing the 48 from characters to make it easy for calculations
*/
void char_to_int(char *s){
    while(*s!='\0'){
        if(*s>='0'&&*s<='9')
            *s=*s-48;
        s++;
    }
}
/*
    just adding 48 to the integer digits to return it to char
*/
void int_to_char(char *s,int length){
    length--;
    while(length){
        if(*(s+length-1)>=0&&*(s+length-1)<=9)
            *(s+length-1)=*(s+length-1)+48;
        length--;
    }
}
/*
    increasing the length of the array by one shift the array to the right and
    add one empty digit to the left
*/
void add_one_digit_to_left(char **s,int *length){
    *s=(char*)realloc(*s,++(*length)*sizeof(char));
    int l=*length;
    while(l>1){
        *((*s)+l-1)=*((*s)+(l)-2);
        l--;
    }
    **s=0;
}
/*
    its part of calculation
*/
void refresh(char **s,int *length){
    int i=1;
    while(i<=(*length) ){
        int n=(*((*s)+(*length)-i))/10;
        *((*s)+(*length)-i)=(*((*s)+(*length)-i))%10;
        if(n){
            if(i==(*length) )
                add_one_digit_to_left(s,length);
            (*((*s)+(*length)-i-1))+=n;
        }
        i++;
    }
}
/*
    create and return a copy of string
*/
char * copy(char *s,int length){
    char *res=(char*)malloc(sizeof(char)*length);
    while(length>0){
        res[length-1]=s[length-1];
        length--;
    }
    return res;
}
/*
    its do the arithmetic plus on two arrays of chars and return the result
*/
char * plus(char *s,char *s2,int *length_s1,int length_s2){
    char_to_int(s);
    char_to_int(s2);
    char *res=copy(s,*length_s1);
    int i,r;
    while(*length_s1<length_s2)
        add_one_digit_to_left(&res,length_s1);
    for(i=*length_s1-1,r=length_s2-1;i>=0&&r>=0;i--,r--)
        res[i]+=s2[r];
    refresh(&res,length_s1);
    int_to_char(res,*length_s1);
    return res;
}
void remove_all_zero_digits_from_left(char **s,int *length){
    int i;
    while(*length>1&&**s==0||**s=='0'&&*length>2){
        for(i=0;i<*length-1;i++)
            *((*s)+i)=*(*s+i+1);
        *s=(char*)realloc(*s,--(*length)*sizeof(char) );
    }
}
/*
    its part of calculation of minus arithmetic
*/
void refresh2(char **s,int *length){
    int i;
    for(i=0;i<(*length)-2;i++){
        *((*s)+i)-=1;
        *((*s)+i+1)+=10;
    }
    refresh(s,length);
    remove_all_zero_digits_from_left(s,length);
}
/*
    compare to arrays of chars if the first biggest return   if the second return -1
    if the equals return 0
*/
int compare_str(char *s,char *s2,int length_s,int length_s2){
    int i;
    while(*s=='0'){
        s++;
        length_s--;
    }
    while(*s2=='0'){
        s2++;
        length_s2--;
    }
    if(length_s>length_s2)
        return 1;
    if(length_s2>length_s)
        return -1;
    for(i=0;i<length_s;i++){
        if(s[i]>s2[i])
            return 1;
        if(s2[i]>s[i])
            return-1;
    }
    return 0;
}
/*
    its arithmetic minus between two arrays of chars and return the result
*/
char * minus(char *s,char *s2,int *length_s,int length_s2){
    char *res,*m;
    int i,r,length_res=*length_s,length_m;
    if(compare_str(s,s2,*length_s,length_s2)!=1){
        res=(char*)malloc(sizeof(char)*2);
        res[0]='0';
        res[1]='\0';
        *length_s=2;
        return res;
    }
    res=copy(s,*length_s);
    for(i=length_res-2,r=length_s2-2;i>=0&&r>=0;i--,r--)
        res[i]-=s2[r];
    char_to_int(res);
    refresh2(&res,&length_res);
    *length_s=length_res;
    int_to_char(res,length_res);

    return res;
}
/*
    arithmetic operation multiply on two arrays of chars
*/
char * multiply(char *s,char *s2,int length_s,int length_s2){
    char *res=copy(s,length_s),*m=copy(s2,length_s2);
    int length_res=length_s;
    if(compare_str(s,"0",length_s,2)==0||compare_str(s2,"0",length_s2,2)==0)
        return "0";
    char *one=(char*)malloc(sizeof(char)*2);
    one[0]='1';
    one[1]='\0';
    while(compare_str(m,one,length_s2,2)==1){
        res=plus(res,s,&length_res,length_s);
        m=minus(m,one,&length_s2,2);
        int_to_char(one,2);
    }
    return res;
}
char * multiply2(char *s,char *s2,int length_s,int length_s2){
    char *res=(char*)malloc(sizeof(char)*(length_s+length_s2-1));
    int r=length_s-2,i=length_s2-2,j,k,length=length_s2+length_s-1;
    for(k=0;k<length;k++)
        res[k]=0;
    char_to_int(s);
    char_to_int(s2);
    for(k=0;r>=0;r--,k++){
        for(i=length_s2-2,j=0;i>=0;i--,j++)
            *(res+length-(k+j)-2)+=s[r]*s2[i];
        refresh(&res,&length);
    }
    remove_all_zero_digits_from_left(&res,&length);
    int_to_char(s,length_s);
    int_to_char(s2,length_s2);
    int_to_char(res,length);

    return res;
}
char * division(char *s,char *s2,int length_s,int length_s2){
    char *res=(char*)malloc(sizeof(char)*2),*one=(char*)malloc(sizeof(char)*2);
    int length_res=2;
    res[0]='0';
    res[1]='\0';
    one[0]='1';
    one[1]='\0';
    if(compare_str(s,"0",length_s,2)==0)
        return "0";
    if(compare_str(s2,"0",length_s2,2)==0)
        return "Cannot divide be zero\n";
    while(compare_str(s,s2,length_s,length_s2)==1){
        res=plus(res,one,&length_res,2);
        s=minus(s,s2,&length_s,length_s2);
        int_to_char(s2,length_s2);
    }
    res=plus(res,one,&length_res,2);
    return res;
}
void clean_buff(){
    char ch;
    do{
        ch=getchar();
    }while(ch!='\n');
}
void add_to_end(char **s,char ch,int *length){
    if(*length==0){
        (*length)++;
        *s=NULL;
    }
    (*s)=(char*)realloc(*s,(++(*length))*sizeof(char));
    (*((*s)+*(length)-1))=0;
    (*((*s)+(*length)-2))=ch;
}
char * division2(char *s,char *s2,int length_s,int length_s2){
    char *res,*temp;
    int i,length=1,length_res=1;
    int n=0;
    res=(char*)malloc(sizeof(char)*1);
    temp=(char*)malloc(sizeof(char)*1);
    res[0]='\0';
    temp[0]='\0';
    for(i=0;i<length_s-1;){
        add_to_end(&temp,*(s+i),&length);
        i++;
        while(i<length_s-1&&compare_str(temp,s2,length,length_s2)==-1){
            add_to_end(&temp,*(s+i),&length);
            i++;
            add_to_end(&res,'0',&length_res);
        }
        n=0;
        while(compare_str(temp,s2,length,length_s2)!=-1){
            temp=minus(temp,s2,&length,length_s2);
            n++;
        }
        if(n){
            add_to_end(&res,n+48,&length_res);
        }else
            add_to_end(&res,'0',&length_res);
    }
    remove_all_zero_digits_from_left(&res,&length_res);
    free(temp);
    return res;
}
void run(){
    char ch,*res;
    printf("Arithmetic calculations on big numbers floating point not supported\n");
    while(1){
        printf("Enter arithmetic operator like + - / *\nExit enter @\n");
        scanf("%c",&ch);
        clean_buff();
        if(ch=='@')
            break;
        puts("Enter first number\n");
        p_size=scan_string(&p);
        puts("Enter second number\n");
        p2_size=scan_string(&p2);
        switch(ch){
            case '+':
                res=plus(p,p2,&p_size,p2_size);
                break;
            case '-':
                res=minus(p,p2,&p_size,p2_size);
                break;
            case '*':
                res=multiply2(p,p2,p_size,p2_size);
                break;
            case '/':
                res=division2(p,p2,p_size,p2_size);
                break;
        }
        printf("\nResult = %s\n\n",res);
    }
}
int main(){
    run();
    //while(getchar()!='\n');
    getchar();
    return 0;
}

























