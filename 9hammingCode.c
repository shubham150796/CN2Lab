#include <iostream>
using namespace std;


int main() {
    int input,data[10],recv[10],i,s,s0,s1,s2,pos=-1;
    cout<<"enter 4bit dataword:  ";
    cin>>input;
    
    for(i=3;i<=6;i++)
    {data[i]=input%10;
        input=input/10;}
    
    data[0]=data[5]^data[4]^data[3];
    data[1]=data[6]^data[5]^data[4];
    data[2]=data[4]^data[3]^data[6];
    
    cout<<"codeword =";
    for(i=6;i>=0;i--)
        cout<<data[i];
    
    cout<<"\nenter received codeword : ";
    cin>>input;
    
    for(i=0;i<7;i++)
    {recv[i]=input%10;
        input=input/10;}
    
    s0=recv[5]^recv[4]^recv[3]^recv[0];
    s1=recv[6]^recv[5]^recv[4]^recv[1];
     s2=recv[4]^recv[3]^recv[6]^recv[2];
    s=4*s2+2*s1+s0;
    
    
    switch(s)
    {
        case 0:cout<<"\nno error";
            break;
        case 5: pos=0;break;
        case 7:pos=1;break;
        case 3:pos=2;break;
        case 6:pos=3;break;
        default:cout<<"\nerror in redundant bit";break;
    }
    if(pos!=-1)
    {
        cout<<"\nError in bit position:"<< pos+3;
        if(recv[pos+3]==0)
            recv[pos+3]=1;
        else
            recv[pos+3]=0;
    }
    cout<<"\nthe dataword is:";
    for(i=6;i>=3;i--)
        cout<<recv[i];
    cout<<endl;
}

