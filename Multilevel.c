#include<stdio.h>
int main(){
    int n;
    printf("Enter nuber of process: ");
    scanf("%d",&n);
    int sq[10];int uq[10];
    int pid[10],at[10],bt[10],type[10];
    int time=0;
    for(int i=1;i<=n;i++){
        printf("Enter at and bt for P%d: ",i);
        scanf("%d",&at[i]);scanf("%d",&bt[i]);
        printf("Enter the type of process: ");
        scanf("%d",&type[i]);
        pid[i] = i;
    }
    int a=1;int b=1;
    for(int i=1;i<=n;i++){
        if(type[i]==0){
            sq[a]=i;a++;
        }
        else{
            uq[b]=i;b++;
        }
    
    }
    int sl =a;
    int ul = b;
    int q,w,temp;
    for(int i=1;i<a-1;i++){
        for(int j=1;j<a-i;j++){
            q=sq[j];w=sq[j+1];
            if(at[q]>at[w]){
                temp=sq[j];
                sq[j]=sq[j+1];
                sq[j+1]=temp;
            }
        }
    }
    for (int i = 1; i < b-1; i++)
    {
        for (int j = 1; j < b - i; j++)
        {
            q = uq[j];
            w = uq[j + 1];
            if (at[q] > at[w])
            {
                temp = uq[j];
                uq[j] = uq[j + 1];
                uq[j + 1] = temp;
            }
        }
    }
   
    int start[10];int ct[10];int tat[10];int wt[10];
    for(int i=1;i<sl;i++){
        w=sq[i];
        if(time<at[w]){
            time=at[w];
        }
        start[w]=time;
        time=time+bt[w];
        ct[w]=time;
        tat[w]=ct[w]-at[w];
        wt[w]=tat[w]-bt[w];
    }

    for (int i = 1; i < ul; i++)
    {
        w = uq[i];
        if (time < at[w])
        {
            time = at[w];
        }
        start[w] = time;
        time = time + bt[w];
        ct[w] = time;
        tat[w] = ct[w] - at[w];
        wt[w] = tat[w] - bt[w];
    }

    printf("\nP#\tAT\tBT\tTYPE\tCT\tWT\tTAT");
    for(int i=1;i<=n;i++){
        printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d",pid[i],at[i],bt[i],type[i],ct[i],wt[i],tat[i]);
    }
    return 0;
}
    