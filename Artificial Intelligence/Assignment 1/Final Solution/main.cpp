#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>
using namespace std;

vector<string> v;

int e;

//int found=0;

struct pQ
{
	list<int> path;
	int cost;
	bool operator>(const pQ& rhs) const
	{
		return cost > rhs.cost;
	}
};

class mycomparison
{
public:
	bool operator() (pQ p1, pQ p2) const
	{
		//by default comparing the integer values
		return (p1>p2);
	}
};

class Graph
{
	int V;
	vector<int> *adj;
	vector<int> *wgt;
public:
	Graph(int V);
	void addEdge(int v, int w, int wgt);
	void UCF(int s, int t);
	void displayPath(struct pQ f);
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new vector<int>[V];
	wgt = new vector<int>[V];
}

void Graph::addEdge(int v, int w, int wt) {
	adj[v].push_back(w);
	wgt[v].push_back(wt);

	//non-directed graph
	adj[w].push_back(v);
	wgt[w].push_back(wt);
}

void Graph::UCF(int s, int t)
{
	int current=0, pos=0;
	typedef priority_queue<pQ,vector<pQ>,mycomparison> mypq_type;
	mypq_type pq;

	pQ vstart;

	vstart.path.push_back(s);
	vstart.cost = 0;

	vector<int>::iterator i;
	pq.push(vstart);

	int indicator=0;

	while(!pq.empty())
	{

	   if(indicator<=(e*100))
	  {
		pQ currentPQ, tempPQ;
		current = pq.top().path.back();
		currentPQ = pq.top();
		// cout<<current<<" "<<currentPQ.cost<<endl;
		pq.pop();
		if(current == t)
		{
			cout<<endl;
			cout<<"Path found"<<endl;
			//cout<<indicator;
			displayPath(currentPQ);
			exit(0);

		}
		else{
			for (i = adj[current].begin(); i != adj[current].end(); ++i)
			{
				tempPQ = currentPQ;
				tempPQ.path.push_back(*i);
				pos = find(adj[current].begin(), adj[current].end(), *i) - adj[current].begin();
				tempPQ.cost += wgt[current].at(pos);
				pq.push(tempPQ);
			}
		}

		 indicator++;

		}

		 else
		  {
		 break;
		 //cout<<indicator;
		 }
	}
}

void Graph::displayPath(struct pQ p)
{
  list<int>::iterator i;
	cout<<"Route is : ";
  for (i = p.path.begin(); i != p.path.end(); ++i)
  {

    cout<<"->"<<v[*i];
    //cout<<"Path cost : "<<p.cost;
  }
	cout<<endl;
  cout<<"Distance: "<<p.cost;
  cout<<endl;
}

int main()
{
	int n, c, a,b;
	string start,end,filename;



	int vstart = 0, vend = 0;

	cout<<"Enter File Name: "<<endl;
	cin>>filename;

	std::ifstream myfile(filename.c_str());

    // new lines will be skipped unless we stop it from happening:
      myfile.unsetf(std::ios_base::skipws);

    // To get number of edges from file
        e = std::count(
        std::istream_iterator<char>(myfile),
        std::istream_iterator<char>(),
        '\n');
        //cout<<e<<endl;

    //To find out number vertices/cities

       ifstream myfile1(filename.c_str());
       string line;
       int x=e-1;
       while (getline (myfile1,line) && x>0 )
       {
          istringstream iss(line);
          string s;
          int x1=2;
           while(getline( iss, s, ' ' ) && x1>0)
          {
           //cout<<s.c_str() <<"\t";
           if(find(v.begin(), v.end(), s.c_str())==v.end())
            v.push_back(s.c_str());

           x1--;
          }

          //cout<<endl;
          x--;
       }
       myfile.close();

	n=v.size();
	//cout<<n;

	Graph g(n);
	//cout<<"list of edges in the format : v1 v2 weight:"<<endl;
	x=e-1;
	ifstream myfile2(filename.c_str());
	while ( getline (myfile2,line) && x>0 )
       {
          istringstream iss(line);
          string s;
          int x1=0;
           while(getline( iss, s, ' ' ))
          {


             if(x1==0)
             {
               vector<string>::iterator it = std::find(v.begin(), v.end(), s.c_str());
               a = std::distance(v.begin(), it);
             }

             else if(x1==1)
             {
               vector<string>::iterator it = std::find(v.begin(), v.end(), s.c_str());
               b = std::distance(v.begin(), it);
             }


             else
              c=atoi(s.c_str());

           x1++;
          }
          g.addEdge(a, b, c);
          //cout<<a<<"\t"<<b<<"\t"<<c<<endl;

          x--;
       }
       myfile.close();



	cout<<"Enter the start vertex: ";
	cin>>start;
	cout<<"Enter the end vertex: ";
	cin>>end;

	if(find(v.begin(), v.end(), start)!=v.end() && find(v.begin(), v.end(), end)!=v.end( ) )
    {
     vector<string>::iterator it = std::find(v.begin(), v.end(), start);
     vstart=std::distance(v.begin(), it);

     it = std::find(v.begin(), v.end(), end);
     vend=std::distance(v.begin(), it);

	 g.UCF(vstart, vend);




         cout<<"No path exists"<<endl;
         cout<<"Distance : infinity"<<endl;


    }
	else{
         cout<<"Source or destination entered does not exists in graph"<<endl;
	}
	return 0;
}
