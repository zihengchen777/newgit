#include<iostream>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fstream>




using namespace std;
#define TAKEIN "进入"
#define WAIT "等待"
#define RUN "运行"
#define FINISH "结束"


typedef struct pcb
{

   char Name[20];
   int runTime;
   int endTime;
   int startTime;
   int turnOverTime;//周转时间
   int userweightTurnOverTime;
   int arriverTime;
   char provessStatus[10];//进程状态


} pcb;

pcb pcbs[5];
int currentTime=0;
int processIndex=0;


class mainPcb{
private:
    pcb pcbs1,pcbs2,pcbs3,pcbs4,pcbs5;
public:
    void initialPcb(); //初始化
    void printfPcbsInfo(); //打印所有进程的所有信息
    void sortPcbs(); //按到达时间升序排列
    int selNectProcess(); //下一个进程的选择，条件：等待状态&&运行时间最短
    int isHasProcessArrive(); //检查在某个时间点有没有进程没有到达
    void runProcess(int pindex);  //运行
    void startProcess(); //开始
};
void mainPcb::initialPcb(){
    freopen("input.txt","r",stdin);
    cout<<"进程名\t"<<"到达时间\t"<<"运行时间\n";

    for(int index=0; index<5; index++)
    {
        cin>>pcbs[index].Name;
        cin>>pcbs[index].arriverTime;
        cin>>pcbs[index].runTime;
        pcbs[index].startTime=0;
        pcbs[index].endTime=0;
        pcbs[index].turnOverTime=0;
        pcbs[index].userweightTurnOverTime=0;
        strcpy(pcbs[index].provessStatus,TAKEIN);
        cout<<pcbs[index].Name<<"\t"<<pcbs[index].arriverTime<<"\t\t"<<pcbs[index].runTime<<"\n";

    }
}
void mainPcb::printfPcbsInfo()
{
    cout<<"当前时间为："<<currentTime<<"\n\n";
    cout<<"进程名"<<"\t"<<"到达时间"<<"\t"<<"运行时间"<<"\t"<<"开始时间"<<"\t"<<"结束时间"<<"\t"<<"周转时间"<<"\t"<<"带权周转时间"<<"\t"<<"状态"<<"\n";
    for(int index=0; index<5;index++)
    {
        cout<<pcbs[index].Name<<"\t"<<pcbs[index].arriverTime<<"\t\t"
        <<pcbs[index].runTime<<"\t\t"<<pcbs[index].startTime
        <<"\t\t"<<pcbs[index].endTime<<"\t\t"<<pcbs[index].turnOverTime
        <<"\t\t"<<pcbs[index].userweightTurnOverTime<<"\t\t"<<pcbs[index].provessStatus<<"\n";
    }
}

void mainPcb::sortPcbs()
{
  int minIndex=0,minValue=0;
    for(int i=0; i<5; i++)
    {
        minIndex=i;
        minValue=pcbs[i].arriverTime;
        for(int j=i; j<5; j++)
        {
            if(pcbs[j].arriverTime<minValue)
            {
                minValue=pcbs[j].arriverTime;
                minIndex=j;
            }
        }
        pcb temp=pcbs[minIndex];
        pcbs[minIndex]=pcbs[i];
        pcbs[i]=temp;
    }


}

int mainPcb::selNectProcess()
{
   int result=-1;
    int minTime=100;
    for(int index=0; index<5; index++)
    {
        if(strcmp(pcbs[index].provessStatus,WAIT)==0)
        {
            if(pcbs[index].runTime<minTime)
            {
                minTime=pcbs[index].runTime;
                result=index;
            }
        }
    }
    return result;
}
int mainPcb::isHasProcessArrive()
{
    int result=-1;
    for(int index=0; index<5; index++)
    {
        if(pcbs[index].arriverTime==currentTime)
        {
            result=index;
            strcpy(pcbs[index].provessStatus,WAIT);
        }
    }
    return result;


}
void mainPcb::runProcess(int pindex)
{

  int runTime=pcbs[pindex].runTime;

    pcbs[pindex].startTime=currentTime;
    pcbs[pindex].endTime=pcbs[pindex].startTime+pcbs[pindex].runTime;
    strcpy(pcbs[pindex].provessStatus,RUN);
    printfPcbsInfo();
    for(int k=1; k<=runTime; k++)
    {
        currentTime++;
        isHasProcessArrive();
        if(k==runTime)
        {

            strcpy(pcbs[pindex].provessStatus,FINISH);
            pcbs[pindex].turnOverTime=pcbs[pindex].endTime-pcbs[pindex].arriverTime;
            pcbs[pindex].userweightTurnOverTime=pcbs[pindex].turnOverTime*1.0/pcbs[pindex].runTime;
        }
        printfPcbsInfo();
    }
    processIndex++;
    currentTime--;


}

void mainPcb::startProcess()
{
  int firstArriveTime=pcbs[0].arriverTime;
    int nextIndex=0;
    printfPcbsInfo();
    while(1)
    {
        currentTime++;
        isHasProcessArrive();
        if(currentTime<firstArriveTime)
        {
            printfPcbsInfo();
        }
        else if(currentTime==firstArriveTime)
        {
            runProcess(0);
        }
        else
        {
            nextIndex=selNectProcess();
            if(nextIndex!=-1)
            {
                runProcess(nextIndex);
            }
            if(processIndex==5)
                break;
        }
    }

}

int main(){
           cout<<"======================这是短作业优先调度算法====================="<<"\n\n";
           mainPcb textpcb;
           textpcb.initialPcb();
           cout<<"=================================================================="<<"\n";
           textpcb.sortPcbs();
           textpcb.startProcess();
           return 0;
}
