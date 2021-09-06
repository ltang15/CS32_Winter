#include "newSequence.h"

Sequence::Sequence()
	:m_size(0), m_capacity(DEFAULT_MAX_ITEMS)
{
	m_seq = new ItemType[DEFAULT_MAX_ITEMS]; // Allocate
}

Sequence::Sequence(int cap)
	: m_size(0), m_capacity(cap)
{
	// invalid capacity
	if (cap < 0)
		exit(1);

	m_seq = new ItemType[cap];
}
Sequence::Sequence(const Sequence& other)
{
	// 1. Copy all variables
	m_size = other.m_size;
	m_capacity = other.m_capacity;
	// 2. Allocate new space
	m_seq = new ItemType[m_capacity];
	// 3. Copy
	for (int i = 0; this->size(); i++)
	{
		m_seq[i] = other.m_seq[i];
	}
}

Sequence& Sequence::operator=(const Sequence& rhs)
{

	// Copy and swap
	if (this != &rhs)
	{
		Sequence temp(rhs);
		swap(temp);
	}
	return *this;
	
}
Sequence::~Sequence()
{
	delete [] m_seq;
}

bool Sequence::empty() const
{
	return m_size == 0;
}

int Sequence::size() const
{
	return m_size;
}
int Sequence::insert(int pos, const ItemType& value)
{
	if (pos < 0 || pos > size() || size() >= m_capacity)
		return -1;

	m_size++;

	for (int i = size() - 1; i > pos; i--)
	{
		m_seq[i] = m_seq[i - 1];
	}

	m_seq[pos] = value;

	return pos;
}

int Sequence::insert(const ItemType& value)
{
	if (m_size >= m_capacity)
		return -1;

	int p = 0;
	bool flag = false;
	for (; p < size(); p++)
	{
		if (value <= m_seq[p])
		{
			flag = true;
			break;
		}
	}

	if (flag)
	{
		m_size++;
		for (int i = size() - 1; i > p; i--)
		{
			m_seq[i] = m_seq[i - 1];
		}
	}
	else
	{
		p = size();
		m_size++;
	}

	m_seq[p] = value;
	return p;
}


bool Sequence::erase(int pos)
{

	if (pos < 0 || pos >= size())
		return false;

	for (int i = pos; i < size(); i++)
	{
		m_seq[i] = m_seq[i + 1];
	}
	m_size--;
	return true;

}

int Sequence::remove(const ItemType& value)
{
	int items = 0;

	for (int i = 0; i < size(); i++)
	{
		if (m_seq[i] == value)
		{
			erase(i);
			items++;
			i = i - 1;

		}
	}
	return items;
}

bool Sequence::get(int pos, ItemType& value) const
{
	if (0 <= pos && pos < size())
	{
		value = m_seq[pos];
		return true;
	}
	return false;
}


bool Sequence::set(int pos, const ItemType& value)
{
	if (0 <= pos && pos < size())
	{
		m_seq[pos] = value;
		return true;
	}
	return false;
}


int Sequence::find(const ItemType& value) const
{
	int p = 0;
	bool flag = false;
	for (int i = 0; i < size(); i++)
	{
		if (m_seq[i] == value)
		{
			p = i;
			flag = true;
			break;

		}
	}
	if (flag == false)
		p = -1;

	return p;
}

void Sequence::swap(Sequence& other)
{
	//Swap capacity
	int c = m_capacity;
	m_capacity = other.m_capacity;
	other.m_capacity = c;

	// Swap size

	int s = m_size;
	m_size = other.m_size;
	other.m_size = s;

	// Swap sequence elements(pointers)

	ItemType* temp;
	temp = m_seq;
	m_seq = other.m_seq;
	other.m_seq = temp;


}

void Sequence::dump() const
{
	for (int i = 0; i < size(); i++) 
	{
		cerr << m_seq[i] << " ";

	}
	cerr << endl;
}