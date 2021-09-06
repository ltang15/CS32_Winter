#include "Sequence.h"


Sequence::Sequence(): m_size(0)   // Create an empty sequence (i.e., one with no items)
{}

bool Sequence::empty() const  // Return true if the sequence is empty, otherwise false.
{
	if (m_size == 0)
		return true;
	return false;
}
int Sequence::size() const    // Return the number of items in the sequence.
{
	return m_size;
}
int Sequence::insert(int pos, const ItemType& value)
// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return pos if 0 <= pos <= size() and the value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// e.g., because it's implemented using a fixed-size array.)  Otherwise,
// leave the sequence unchanged and return -1.  Notice that
// if pos is equal to size(), the value is inserted at the end.
{
	if (pos < 0 || pos > size() || size()>= DEFAULT_MAX_ITEMS)
		return -1;

	m_size++;

	// elements shift to the right one position, starting from the one is inserted
	for (int i = size() - 1; i > pos; i--)
	{
			m_seq[i] = m_seq[i-1];
	}
	
	m_seq[pos] = value;

	return pos;
}
int Sequence::insert(const ItemType& value)
// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item in position
// p.  The original item at position p and those that follow it end
// up at positions one higher than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).
{
	// capacity is full
	if (m_size >= DEFAULT_MAX_ITEMS)
		return -1;

	int p = 0;
	bool flag = false;
	for (; p < size(); p++)
	{
		// Break the loop when smallest p is found
		if (value <= m_seq[p])
		{			
			flag = true;
			break;
		}
	}

	if (flag)
	{
		// Insert value at smallest p position, folowing elements shifts to the right
		m_size++;
		for (int i = size() - 1; i > p; i--)
		{
			m_seq[i] = m_seq[i - 1];
		}
	}
	else
	{
		// p is not found
		p = size();
		m_size++;
	}

	m_seq[p] = value; // Insert value at p position
	return p;

}
bool Sequence::erase(int pos)
// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed that item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.
{
	if (pos < 0 || pos >= size())
		return false;

	// elements shift to the left, starting at the position needs to be deleted
	for (int i = pos; i < size(); i++)
	{
		m_seq[i] = m_seq[i+1];
	}
	m_size--;
	return true;

}
int Sequence::remove(const ItemType& value)
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
{
	int items = 0; // counter for number of items removed

	for (int i = 0; i < size(); i++)
	{
		// Finding items = value
		if (m_seq[i] == value)
		{
			erase(i);
			items++;
			i = i -1;

		}
	}
	return items;
}

bool Sequence::get(int pos, ItemType& value) const
// If 0 <= pos < size(), copy into value the item at position pos
// of the sequence and return true.  Otherwise, leave value unchanged
// and return false.
{
	if (0 <= pos && pos < size())
	{
		value = m_seq[pos];
		return true;
	}
	return false;
}
bool Sequence::set(int pos, const ItemType& value)
// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
{
	if (0 <= pos && pos < size())
	{
		m_seq[pos] = value;
		return true;
	}
	return false;
}
int Sequence::find(const ItemType& value) const
// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.
{
	int p = 0;
	bool flag = false;
	for (int i = 0; i < size(); i++)
	{
		// item is found
		if (m_seq[i] == value)
		{
			p = i;
			flag = true;
			break;

		}
	}
	// item is not found
	if (flag == false)
		p = -1;

	return p;

}
void Sequence::swap(Sequence& other)
// Exchange the contents of this sequence with the other one.
{
	

	int n_1;
	n_1 = this-> size(); // size of old this sequence

	
	// Insert n_2 elements of other sequence right after n_1 elements of this sequence
	// forming a new this sequence containing n_1 elements and n_2 elements
	for (int i = 0; i < other.size(); i++)
	{
		this->insert(n_1 + i, other.m_seq[i]);
	}

	// Copy n_1 elements of this sequence to  other sequence
	// Now, other sequence contains n_1 elements of this sequence.
	other.m_size = n_1;
	for (int j = 0; j < n_1; j++)
	{
		other.m_seq[j] = m_seq[j];
	}

	// Delete n_1 elements of this sequence
	// Now, this sequence only have n_2 elements left

	for (int k = 0; k < n_1; k++)
	{
		this->erase(0); 		
	}

	
}

void Sequence::dump() const
{
	// displaying sequence
	for (int i = 0; i < size(); i++) 
	{
		cerr << m_seq[i] << " ";

	}
	cerr << endl;
}