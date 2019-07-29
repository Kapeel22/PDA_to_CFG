/*  C++ code for Conversion from PDA to CFG 
    AUTHOR = KAPEEL SURYAVANSHI             ENROLLMENT NUMBER = BT16CSE084 */
    
/*Please Note : The first line of input should be space separated consisting of states of PDA. Its following lines are transitions of PDA 
whose input is of form δ(q,0,Z) = (q,XZ)*/

#include<bits/stdc++.h>
#define breakline() cout<<"-------------------------------------------------------------------------\n"
using namespace std;

void generate_permutations(vector<string> states, vector<string> &temp,vector<vector<string> > &permutes,int k)
{
    if(k == 0)
    {
        permutes.push_back(temp);
    }
    else
    {
        for(int i=0 ; i<states.size() ; i++)
        {
            temp[k-1] = states[i];
            generate_permutations(states,temp,permutes,k-1);
        }
    }    
}

void print_permutes(string from_state, string input, string top_stack, string to_state, string push_stack, vector<string> states)
{
    int i,j;
    vector<string> temp(push_stack.size());
    vector<vector<string> > permutes;
    
    generate_permutations(states,temp,permutes,push_stack.size());

    for(i=0 ; i<permutes.size() ; i++)
    {
        cout<<"["<<from_state<<top_stack;
        cout<<permutes[i][0]<<"] -> "<<input<<" ["<<to_state<<push_stack[0];
        for(j=1 ; j<permutes[i].size() ; j++)
        {
            cout<<permutes[i][j]<<"] ["<<permutes[i][j]<<push_stack[j];
        }
        cout<<permutes[i][0]<<"]\n";
    }
}

void PDA_to_CFG(vector<string> &from_state, vector<string> &input, vector<string> &top_stack, vector<string> &to_state, vector<string> &push_stack, vector<string> states)
{
    int i,j,n = from_state.size();
    cout<<"Start State = S -> ";
    cout<<"["<<states[0]<<"Z"<<states[0]<<"]";
    for(i=1 ; i<states.size() ; i++)
    {
        cout<<" | ["<<states[0]<<"Z"<<states[i]<<"]";
    }
    cout<<endl;
    
    for(i=0 ; i<n ; i++)
    {
        cout<<"\nδ("<<from_state[i]<<","<<input[i]<<","<<top_stack[i]<<") = ("<<to_state[i]<<","<<push_stack[i]<<")\n";
        if(push_stack[i].compare("ε") == 0)
        {
            cout<<"["<<from_state[i]<<top_stack[i]<<to_state[i]<<"] -> "<<input[i]<<endl;
        }
        else
        {
            print_permutes(from_state[i],input[i],top_stack[i],to_state[i],push_stack[i],states);
        }
    }
    
    cout<<endl;
    for(i=0 ; i<states.size() ; i++)
    {
        for(j=0 ; j<states.size() ; j++)
        {
            cout<<"["<<states[i]<<"Z"<<states[j]<<"] -> ε\n";
        }
    }
}

int main()
{
    vector<string> from_state;
    vector<string> to_state;
    vector<string> top_stack;
    vector<string> input;
    vector<string> push_stack;
    vector<string> states;
    
    int i,j;
    vector<string> temp;
    string line,ch,t;
    ifstream fin;
    fin.open("pda_input");
    if(!fin)
    {
        cerr<<"Error in Opening File\n";
        exit(1);
    } 
    getline(fin,line);
    istringstream ss(line);
    while(ss >> ch)
    {
        states.push_back(ch);
    }
    while(getline(fin,line))
    {
        istringstream ss(line);
         
        ss>>ch;
        istringstream s2(ch);
        i=0;
        while(getline(s2,t,','))
        {
           if(i==0)
           {
                t.erase(t.begin(),t.begin()+3);
                from_state.push_back(t);
           } 
           else if(i==1)
           {
                input.push_back(t);
           }
           else if(i==2)
           {
                t.erase(t.end()-1,t.end());
                top_stack.push_back(t);
           }
           i++;
        }
        
        ss>>ch;
        ss>>ch;
        istringstream s3(ch);
        i=0;
        while(getline(s3,t,','))
        {
            if(i==0)
            {
                
                t.erase(t.begin(),t.begin()+1);
                to_state.push_back(t);
            }
            else if(i==1)
            {
                t.erase(t.end()-1,t.end());
                push_stack.push_back(t);   
            }
            i++;
        }
    }
    //breakline();
    cout<<"PDA given as input :\n";
    cout<<"States = ";
    for(i=0 ; i<states.size() ; i++)
    {
        cout<<states[i]<<" ";
    }
    cout<<endl;
    for( i=0 ; i<from_state.size() ; i++)
    {
        cout<<"δ("<<from_state[i]<<","<<input[i]<<","<<top_stack[i]<<") = ("<<to_state[i]<<","<<push_stack[i]<<")\n";
    }
    breakline();
    cout<<"Corresponding CFG :\n";
    PDA_to_CFG(from_state, input, top_stack, to_state, push_stack,states);

    return 0;   
}
