#include<stdio.h>
#pragma warning(disable : 4996)

struct process
{
	int Name, Arrival, Burst, Waiting, Turnaround, Start,Finish;
};


void HoanVi(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void Input(process a[], int &n)
{
	printf("Moi nhap so luong process: ");
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		printf("Moi nhap ten, thoi gian den, burst time cua tien trinh thu %d: ", i + 1);
		scanf("%d%d%d", &a[i].Name, &a[i].Arrival, &a[i].Burst);
		a[i].Start = 0;
		a[i].Turnaround = 0;
		a[i].Waiting = 0;
		a[i].Finish = 0;
	}
}

void Output(process a[], int n, int b, int c)
{
	printf("\nPName\tResponse\tWaiting\tTurnaround");
	for (int i = 0; i < n; i++)
	{
		printf("\nP%d\t%d\t\t%d\t%d\t", a[i].Name,a[i].Start-a[i].Arrival,a[i].Waiting,a[i].Turnaround);
	}
	float arvw = (float)b / n;
	float arvt = (float)c / n;
	printf("\nAverage waiting time: %f", arvw);
	printf("\nAverage turnaroundtime: %f", arvt);
}

void IterchangeSortTime(process a[], int n)
{
	for (int i = 0; i < n - 1; ++i)
	{
		for(int j=i+1;j<n;++j)
			if (a[i].Arrival > a[j].Arrival)
			{
				HoanVi(a[i].Name, a[j].Name);
				HoanVi(a[i].Arrival, a[j].Arrival);
				HoanVi(a[i].Burst, a[j].Burst);
			}
	}
}

void IterchangeSortName(process a[], int n)
{
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i + 1; j < n; ++j)
			if (a[i].Name > a[j].Name)
			{
				HoanVi(a[i].Name, a[j].Name);
				HoanVi(a[i].Arrival, a[j].Arrival);
				HoanVi(a[i].Burst, a[j].Burst);
				HoanVi(a[i].Waiting, a[j].Waiting);
				HoanVi(a[i].Finish, a[j].Finish);
				HoanVi(a[i].Start, a[j].Start);
				HoanVi(a[i].Turnaround, a[j].Turnaround);
			}
	}
}

void Init(int Queue[], int n)
{
	for (int i = 0; i < n; ++i)
		Queue[i] = -1;
}

void Push(int Queue[], int &sl,int x)
{
	Queue[sl] = x;
	++sl;
}

int None(int Queue[])
{
	if (Queue[0] == -1)
		return 1;
	return 0;
}

void Equal(const process a, process& b)
{
	b.Arrival = a.Arrival;
	b.Burst = a.Burst;
	b.Name = a.Name;
	b.Finish = 0;
	b.Start = 0;
	b.Turnaround = 0;
	b.Waiting = 0;
}

void SapXep(process a[], int lc, int x)
{
	process tmp;
	Equal(a[lc], tmp);
	for (int i = lc-1; i > x; --i)
	{
		Equal(a[i], a[i + 1]);
	}
	Equal(tmp, a[x + 1]);
}

void SJF(process a[], int n, int &Twaiting, int &TTurnaround)
{
	IterchangeSortTime(a, n);
	int Queue[10];
	int slQue = 0;
	Init(Queue, 10);
	int x = 0;
	int time = a[x].Arrival;
	while (x < n + 1)
	{
		time +=a[x].Burst;
		for (int i = x + 1; i < n; ++i)
		{
			if (a[i].Arrival <= time)
			{
				Push(Queue, slQue,i);
			}
			else
				break;
		}
		if (None(Queue) == 1)
		{
			++x;
			time = a[x].Arrival;
		}
		else
		{
			int min = a[Queue[0]].Burst;
			int lc = 0;
			for (int i = 1; i < slQue; ++i)
			{
				if (a[Queue[i]].Burst < min)
				{
					min = a[Queue[i]].Burst;
					lc = i;
				}
			}
			SapXep(a, Queue[lc], x);
			++x;
			Init(Queue, 10);
			slQue = 0;
		}
	}

	for (int i = 0; i < n; ++i)
	{
		if (i == 0)
			a[i].Start = a[i].Arrival;
		else
			a[i].Start = a[i-1].Finish;
		a[i].Waiting = a[i].Start - a[i].Arrival;
		a[i].Finish = a[i].Start + a[i].Burst;
		a[i].Turnaround = a[i].Finish - a[i].Arrival;
		Twaiting += a[i].Waiting;
		TTurnaround += a[i].Turnaround;
	}
}

int main()
{
	int n;
	int Twaiting = 0;
	int TTurnaround = 0;
	process a[10];
	Input(a, n);
	SJF(a, n, Twaiting, TTurnaround);
	IterchangeSortName(a, n);
	Output(a, n,Twaiting,TTurnaround);
	return 0;
}