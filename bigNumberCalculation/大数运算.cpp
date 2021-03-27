#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <vector>
using namespace std;

class calculation
{
private:
    string str1;
    vector<int> vector1;
public:
    calculation operator+(calculation const & var) const //加法符号重载
    {
        calculation temp;
        if (vector1.size() < var.vector1.size())
        {
            for (int i = 0; i < vector1.size(); ++i)
            {
                temp.vector1.push_back(vector1[i] + var.vector1[i]);
            }
            for (int i = vector1.size(); i < var.vector1.size(); i++)
            {
                temp.vector1.push_back(var.vector1[i]);
            }
        }
        else
        {
            for (int i = 0; i < var.vector1.size(); ++i)
            {
                temp.vector1.push_back(vector1[i] + var.vector1[i]);
            }
            for (int i = var.vector1.size(); i < vector1.size(); i++)
            {
                temp.vector1.push_back(vector1[i]);
            }
        }
        for (int i = 0; i <temp.vector1.size()-1; i++)
        {
            if (temp.vector1[i] > 9)
            {
                temp.vector1[i+1] += 1;
                temp.vector1[i] -= 10;
            }
        }
        return temp;
    }
    calculation operator-(calculation const & var) const//减法符号重载
    {
        calculation temp;
        int flag;
        calculation changeVec,changeVar;
        changeVec.vector1 = vector1;
        changeVar.vector1 = var.vector1;
        if (changeVec.vector1.size() < changeVar.vector1.size()) //根据位数不同选择不同算法，确保是大数减去小数
        {
            for (int i = 0; i < changeVec.vector1.size(); ++i)
            {
                if (changeVar.vector1[i]< changeVec.vector1[i])
                {
                    temp.vector1.push_back(changeVar.vector1[i]+10- changeVec.vector1[i]);
                    changeVar.vector1[i+1] -= 1;
                }
                else
                {
                    temp.vector1.push_back(changeVar.vector1[i] - changeVec.vector1[i]);
                }
            }
            for (int i = changeVec.vector1.size(); i < changeVar.vector1.size(); i++)
            {
                temp.vector1.push_back(changeVar.vector1[i]);
            }
            for (flag = temp.vector1.size() - 1; flag >= 0 && temp.vector1[flag] == 0; flag--);
            temp.vector1[flag] *= -1;
        }
        else if (changeVec.vector1.size() > changeVar.vector1.size())
        {
            for (int i = 0; i < changeVar.vector1.size(); ++i)
            {
                if (changeVec.vector1[i] < changeVar.vector1[i])
                {
                    temp.vector1.push_back(changeVec.vector1[i] + 10 - changeVar.vector1[i]);
                    changeVec.vector1[i + 1] -= 1;
                }
                else
                {
                    temp.vector1.push_back(changeVec.vector1[i] - changeVar.vector1[i]);
                }
            }
            for (int i = changeVar.vector1.size(); i < changeVec.vector1.size(); i++)
            {
                temp.vector1.push_back(changeVec.vector1[i]);
            }
        }
        else if (changeVec.vector1.size() == changeVar.vector1.size())//在位数相同时进行高位到低位依次比对，确认数字大小
        {
            int bigger = 0;
            for (int i = changeVec.vector1.size() - 1; i >= 0; i--)
            {
                if (changeVec.vector1[i] > changeVar.vector1[i])
                {
                    bigger = 0;
                    break;
                }
                else if(changeVec.vector1[i] < changeVar.vector1[i])
                {
                    bigger = 1;
                    break;
                }
            }
            if (bigger == 0) 
            {
                for (int i = 0; i < changeVar.vector1.size(); ++i)
                {
                    if (changeVec.vector1[i] < changeVar.vector1[i])
                    {
                        temp.vector1.push_back(changeVec.vector1[i] + 10 - changeVar.vector1[i]);
                        changeVec.vector1[i + 1] -= 1;
                    }
                    else
                    {
                        temp.vector1.push_back(changeVec.vector1[i] - changeVar.vector1[i]);
                    }
                }
            }   
            else if(bigger==1)
            {
                for (int i = 0; i < changeVec.vector1.size(); ++i)
                {
                    if (changeVar.vector1[i] < changeVec.vector1[i])
                    {
                        temp.vector1.push_back(var.vector1[i] + 10 - changeVec.vector1[i]);
                        changeVar.vector1[i + 1] -= 1;
                    }
                    else
                    {
                        temp.vector1.push_back(var.vector1[i] - changeVec.vector1[i]);
                    }
                }
                for (flag = temp.vector1.size() - 1; flag > 0 && temp.vector1[flag] == 0; flag--);
                temp.vector1[flag] *= -1;
            }
        }
        return temp;
    }
    calculation operator*(calculation const & var) const//乘法符号重载
    {
        calculation temp;
        vector<int> tempVec(var.vector1.size() + vector1.size(), 0);
        for (int i = 0; i < vector1.size(); i++)
        {
            for (int n = 0; n < var.vector1.size(); n++)
            {
                tempVec[i + n] += (vector1[i] * var.vector1[n]);//第n位与第i位相乘所在位数是i+n（从零开始计数）
            }
        }
        for (int i = 0; i < tempVec.size() - 1; i++)
        {
            if (tempVec[i] > 9)
            {
                tempVec[i + 1] += tempVec[i] / 10;
                tempVec[i] %= 10;
            }
        }
        temp.vector1.swap(tempVec);
        return temp;
    }
    calculation operator/(calculation const & var) const//除法符号重载
    {
        calculation changeVec, changeVar;
        changeVec.vector1 = vector1;
        changeVar.vector1 = var.vector1;
        calculation temp;
        calculation check= changeVec;
        calculation save = changeVec;
        int flag = 0;
        vector<int> tempVec(vector1.size(), 0);
        int longDeff= vector1.size() - var.vector1.size();
        if (longDeff > 0)//如果位数不同乘以十的倍数进行比对
        {
            for (longDeff = vector1.size() - var.vector1.size(); longDeff > 0; longDeff--)
            {
                changeVar.vector1.insert(changeVar.vector1.begin(), 0);
            }
        }
        for(longDeff = vector1.size() - var.vector1.size(); longDeff>=0;longDeff--)//逐步减少自己添加的零
        {
            save = check - changeVar;
            for (flag = save.vector1.size() - 1; flag > 0 && save.vector1[flag] == 0; flag--);
            while( save.vector1[flag] >= 0)
            {
                tempVec[longDeff] +=1;
                check=check - changeVar;
                save = check - changeVar;
                for (flag = save.vector1.size() - 1; flag > 0 && save.vector1[flag] == 0; flag--);
            }
            changeVar.vector1.erase(changeVar.vector1.begin(), changeVar.vector1.begin() + 1);
        }
        temp.vector1.swap(tempVec);
        return temp;
    }
    calculation operator%(calculation const & var) const//取模符号重载，与除法只有一行不同，把除法中舍弃的数据赋值给了temp
    {
        calculation changeVec, changeVar;
        changeVec.vector1 = vector1;
        changeVar.vector1 = var.vector1;
        calculation temp;
        calculation check = changeVec;
        calculation save = changeVec;
        int flag = 0;
        vector<int> tempVec(vector1.size(), 0);
        int longDeff = vector1.size() - var.vector1.size();
        if (longDeff > 0)
        {
            for (longDeff = vector1.size() - var.vector1.size(); longDeff > 0; longDeff--)
            {
                changeVar.vector1.insert(changeVar.vector1.begin(), 0);
            }
        }
        for (longDeff = vector1.size() - var.vector1.size(); longDeff >= 0; longDeff--)
        {
            save = check - changeVar;
            for (flag = save.vector1.size() - 1; flag > 0 && save.vector1[flag] == 0; flag--);
            while (save.vector1[flag] >= 0)
            {
                check = check - changeVar;
                save = check - changeVar;
                for (flag = save.vector1.size() - 1; flag > 0 && save.vector1[flag] == 0; flag--);
            }
            changeVar.vector1.erase(changeVar.vector1.begin(), changeVar.vector1.begin() + 1);
        }
        temp.vector1.swap(check.vector1 );
        return temp;
    }
    void toString()//将运算结束后的vector进行输出，并未特意转化为string类型
    {
        int flag=0;
        for (flag = this->vector1.size() - 1; flag > 0 && this->vector1[flag] == 0; flag--);
        for (int i = flag; i>=0; --i)
        {
            cout<< this->vector1[i];
        }
        cout << endl;
    }
    calculation (string strin1)//有参初始化，主要运用于对输入数据初始化
    {
        str1 = strin1;
        for (int i = 0; i < str1.size(); i++)
        {
            if ((int)str1[i] >= 48 && (int)str1[i] <= 57)
            {
                vector1.push_back((int)str1[i] - 48);
            }
            else
            {
                cout << "ERROR:请输入正确的数字" << endl;
                break;
            }
         
        }
    }
    calculation()//无参初始化
    {
        str1 = '0';
        vector1.clear();
    }
    void reverse()//反转vector内数据
    {
        int len = this->vector1.size();
        int i = 0, j = len - 1;
        while (i <= j)
        {
            swap(this->vector1[i], this->vector1[j]);
            i++;
            j--;
        }
    }
};

int main()
{
    string s1, s2;
    cout << "请输入两个数字，中间用空格进行分割，本程序会依次进行加、减、乘、除、取模运算" << endl;
    cin >> s1 >> s2;
    calculation r1(s1);
    calculation r2(s2);
    r1.reverse();
    r2.reverse();
    (r1 + r2).toString();
    (r1 - r2).toString();
    (r1 * r2).toString();
    (r1 / r2).toString();
    (r1 % r2).toString();
    return 0;
}
