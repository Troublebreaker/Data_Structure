#include"CMap.h"
#include<iostream>

#include<vector>

using namespace std;

CMap::CMap(int capacity)
{
	m_iCapacity = capacity;
	m_iNodeCount = 0;
	m_pNodeArray = new Node[m_iCapacity];

	m_pMatrix = new int[m_iCapacity*m_iCapacity];
	memset(m_pMatrix,0,m_iCapacity*m_iCapacity*sizeof(int));
}
 
CMap:: ~CMap()
{
	delete[] m_pNodeArray;
	delete[]m_pMatrix;

}

bool CMap::addNode(Node* pNode)
{
	m_pNodeArray[m_iNodeCount] = pNode->m_cData;
	m_iNodeCount++;
	return true;

}

void CMap::resetNode()
{
	for (int i = 0; i < m_iNodeCount; i++)
	{
		m_pNodeArray[i].m_bIsVisited = false;
	}
}

bool CMap::setValueToMatrixForDirectedGraph(int row, int col, int val)
{
	m_pMatrix[row*m_iCapacity+col] = val;
	return true;
}
bool CMap::setValueToMatrixForUndirectedGraph(int row,int col,int val)
{
	m_pMatrix[row*m_iCapacity + col] = val;
	m_pMatrix[col*m_iCapacity + row] = val;

	return true;
}

void CMap::printMatrix()
{
	cout << "  ";
	for (int j = 0; j < m_iCapacity; ++j)
	{
		cout << m_pNodeArray[j].m_cData<<' ';
	}
	cout << endl;
	for (int i = 0; i < m_iCapacity; ++i)
	{
		cout << m_pNodeArray[i].m_cData << ' ';
		for (int k = 0; k < m_iCapacity; ++k)
		{

			cout << m_pMatrix[i*m_iCapacity + k] << ' ';
		}
		cout << endl;

	}
}


bool CMap::getValueFromMatrix(int row, int col, int& val)
{
	val = m_pMatrix[row*m_iCapacity + col];

	return true;
}

//深度优先遍历
void CMap::depthFirstTraverse(int nodeIndex)
{
	int value = 0;
	cout << m_pNodeArray[nodeIndex].m_cData<<' ';
	m_pNodeArray[nodeIndex].m_bIsVisited = true;

	for (int i = 0; i < m_iCapacity; ++i)
	{
		getValueFromMatrix(nodeIndex,i,value);
		if (value == 1)
		{
			if (m_pNodeArray[i].m_bIsVisited)
			{
				continue;
			}
			else
			{
				depthFirstTraverse(i);
			}
		}
		else
		{
			continue;
		}
	}
}

//广度优先遍历
void CMap::breadFirstTraverse(int nodeIndex)
{
	cout << m_pNodeArray[nodeIndex].m_cData << ' ';
	m_pNodeArray[nodeIndex].m_bIsVisited = true;

	vector<int>curVec;
	curVec.push_back(nodeIndex);

	breadthFirstTraverseImpl(curVec);

}
//广度优先遍历实现函数
void CMap::breadthFirstTraverseImpl(vector<int>preVec)
{
	int value = 0;
	vector<int>curVec;

	for (int j = 0; j < (int)preVec.size(); ++j)
	{
		for (int i = 0; i < m_iCapacity; ++i)
		{
			getValueFromMatrix(preVec[j],i,value);
			if (value == 0)
			{
				continue;
			}
			else
			{
				if (m_pNodeArray[i].m_bIsVisited)
				{
					continue;
				}
				else
				{
					cout << m_pNodeArray[i].m_cData << ' ';
					m_pNodeArray[i].m_bIsVisited = true;
					curVec.push_back(i);		
				}

			}

		}
	}

	if (curVec.size() == 0)
	{
		return;
	}
	else
	{
		breadthFirstTraverseImpl(curVec);
	}


}
