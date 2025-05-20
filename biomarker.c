#include<stdio.h>
#include<string.h>
#define q 101
#define d 256

void rabinkarp(char*pattern,char*text){
    int m=strlen(pattern);
    int n=strlen(text);
    int i=0,j=0;
    int p=0,t=0; 
    int h=1;
    for(i=0;i<m-1;i++){
        h=(h*d)%q;
    }
    for(i=0;i<m;i++){
        p=(d*p+pattern[i])%q;
        t=(d*t+text[i])%q;
    }
    for(i=0;i<=n-m;i++){
        if(p==t){
            for(j=0;j<m;j++){
                if(text[i+j]!=pattern[j])break;
            }
            if(j==m)printf("%d\n",i);
        }
        if(i<n-m){
            t=(d*(t-text[i]*h)+text[i+m])%q;
            if(t<0)t=t+q;
        }
    }
}
int main() {
    char text[1000], pattern[100];

    printf("Enter DNA/Protein Sequence (Text): ");
    scanf("%s", text);

    printf("Enter Biomarker Sequence (Pattern): ");
    scanf("%s", pattern);

    rabinkarp(pattern, text);

    return 0;
}