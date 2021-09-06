#include "Sequence.h"

Sequence::Sequence() // no parameter constructor
	:m_size(0)
{
	
	head = &dummy; // points head pointers to dummy node

	// prev and next ptrs points to head(dummy node)
	head->m_next = head;
	head->m_prev = head;
	
}
Sequence::Sequence(const Sequence& other)// Copy constructor
	
{
	head = &dummy;
	head->m_next = head;
	head->m_prev = head;
	for (int i = 0; i<other.size(); i++)
	{
		ItemType get_value;
		other.get(i,get_value);
		this->insert(i, get_value);		
		
	}
	m_size = other.size();
}
Sequence& Sequence::operator=(const Sequence& rhs)// Assignment operator
{

	
	if (this != &rhs)
	{
		
		Sequence temp(rhs);
		swap(temp);
	}
	return *this;

}
Sequence::~Sequence() // Destructor
{
	// if it's empty, do nothing
	if (empty())
		;

	Node* temp1 = head->m_next;
	Node* temp2 = head->m_next;

	while (temp2 != head)
	{
		temp2 = temp1->m_next;
		head->m_next = temp2;
		temp2->m_prev = head;
		delete temp1;
		temp1 = temp2;
	}

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
	// Insert value into the sequence so that it becomes the item at
	  // position pos.  The original item at position pos and those that
	  // follow it end up at positions one higher than they were at before.
	  // Return pos if 0 <= pos <= size() and the value could be
	  // inserted.  (It might not be, if the sequence has a fixed capacity,
	  // e.g., because it's implemented using a fixed-size array.)  Otherwise,
	  // leave the sequence unchanged and return -1.  Notice that
	  // if pos is equal to size(), the value is inserted at the end.

	if (pos <0 || pos > size())
		return -1;


	Node* new_node = new Node;
	new_node->m_data = value;

	if (empty())
	{
		// insert into empty list

		head->m_next = new_node;
		head->m_prev = new_node;
		new_node->m_next = head;
		new_node->m_prev = head;
		
		
	}
	else if (pos == 0 && !empty())
	{
		// insert at the beginning
		Node* temp = head->m_next;

		head->m_next = new_node;
		temp->m_prev = new_node;
		new_node->m_prev = head;
		new_node->m_next = temp;
	
	}
	
	else if (pos == size())
	{
		// insert  at the end

		Node* last_node = head->m_prev;
		last_node->m_next = new_node;
		new_node->m_next = head;
	
		new_node->m_prev = last_node;
		head->m_prev = new_node;
		
	
		
	}
	else
	{
		//insert in between
		Node* temp1 = head->m_next;
		Node* temp2 = temp1->m_next;
		int walker = 0;
		
		while (walker < pos -1 )
		{
			temp1 = temp1->m_next;
			temp2 = temp2->m_next;
			walker++;
		}

		temp1->m_next = new_node;
		new_node->m_next = temp2;
		temp2->m_prev = new_node;
		
	}

	m_size++;
	return pos;
}
int Sequence::insert(const ItemType& value)
{
	  // Let p be the smallest integer such that value <= the item at
	  // position p in the sequence; if no such item exists (i.e.,
	  // value > all items in the sequence), let p be size().  Insert
	  // value into the sequence so that it becomes the item in position
	  // p.  The original item at position p and those that follow it end
	  // up at positions one higher than before.  Return p if the value
	  // was actually inserted.  Return -1 if the value was not inserted
	 
	int counter = 0;
	Node* p;

	// getting the position where it satisfies the condition
	for (p = head->m_next; p != head && value > p->m_data; p=p->m_next)
		counter++;
	
	if (p == head) // not inserted
		return -1;

	int pos = insert(counter, value); // insert value at that position
	return pos;

}
bool Sequence::erase(int pos) 
{
	// If 0 <= pos < size(), remove the item at position pos from
	  // the sequence (so that all items that followed that item end up at
	  // positions one lower than they were at before), and return true.
	  // Otherwise, leave the sequence unchanged and return false.

	// invalid pos and empty sequence
	if (pos < 0 || pos >= size()|| empty())
		return false;


	
	int counter = 0;
	Node* p = head->m_next;

	// moving the pointers to the node at that position
	while (counter != pos)
	{
		p = p->m_next;
		counter++;
	}

	if (pos == size() - 1) 
	{
		// last node

		Node* temp = p->m_prev;
		temp->m_next = head;
		head->m_prev = temp;
		delete p;
	}

	else
	{
		//other cases

		Node* prev_item = p->m_prev;
		Node* next_item = p->m_next;
		prev_item->m_next = next_item;
		next_item->m_prev = prev_item;
		delete p;

	}
		
	m_size--;
	return true;
}
int Sequence::remove(const ItemType& value)
{
	// Erase all items from the sequence that == value.  Return the
	 // number of items removed (which will be 0 if no item == value).

	if (find(value) == -1)
		return 0;

	int items = 0;
	
	// Erase the node every time the function find the value
	while (find(value) != -1)
	{
		int pos = find(value);
		erase(pos);
		items++;
	}
	return items;
	

}

bool Sequence::set(int pos, const ItemType& value)
{
	// If 0 <= pos < size(), replace the item at position pos of the
	  // sequence with value and return true.  Otherwise, leave the sequence
	  // unchanged and return false.

	if (pos < 0 || pos >= size())
		return false;
	
	int counter = 0;
	for (Node* p = head->m_next; p != head; p = p->m_next)
	{
		if (counter == pos)
		{
			p->m_data = value; // insert value to the node
			
		}
		counter++;
	}

	return true;
}
bool Sequence::get(int pos, ItemType& value) const
{
	// If 0 <= pos < size(), copy into value the item at position pos
	  // of the sequence and return true.  Otherwise, leave value unchanged
	  // and return false.

	if (pos < 0 || pos >= size())
		return false;
	
	int counter = 0;
	for (Node* p = head->m_next; p != head; p=p->m_next)
	{
		if (counter == pos)
		{
			value = p->m_data; // get the value of that node
			
		}
		counter++;
	}

	return true;
}
int Sequence::find(const ItemType& value) const
{
	// Let p be the smallest integer such that value == the item at
	  // position p in the sequence; if no such item exists, let p be -1.
	  // Return p.

	int counter = 0;
	for (Node* p = head->m_next; p != head; p=p->m_next)
	{
		if (p->m_data == value)
			return counter; // return the position of the node contains that value

		counter++;
	}
	
	return -1;
}
void Sequence::swap(Sequence& other)
{
	// Exchange the contents of this sequence with the other one.
	
	//swap size
	int s = m_size;
	m_size = other.m_size;
	other.m_size = s;

	// swap list
	Node* temp_head = head;
	head = other.head;
	other.head = temp_head;

}


//testing purpose
//void Sequence::dump() const
//{
//	for (Node* p = head->m_next; p != head; p=p->m_next)
//	{
//		cerr << p->m_data << " ";
//	}
//	cerr << endl;
//
//}


int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	// if seq2 is a consecutive subsequence of seq1,
	// the function returns the earliest place in seq1 where that subsequence starts
	// if no such value exists or if seq2 is empty, the function returns -1.

	if (seq2.empty())
		return -1;

	ItemType s1; 
	ItemType s2;

	for (int i = 0; i < seq1.size(); i++)
	{
		if ((i + seq2.size()) > seq1.size())
			return -1;

		//Get the position of the element in seq1 which is equal to first element in seq 2
		seq1.get(i, s1);
		seq2.get(0, s2);

		if (s1 == s2)
		{
			for (int j = 1; j < seq2.size(); j++)
			{
				seq1.get(i + j, s1);
				seq2.get(j, s2);

				// s2 is not a consecutive of subsequence s1
				if (s1 != s2)
					return -1;
				
					
			}
			return i;
		}
	}
	return -1;

}
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) 
{
	// This function produces as a result a sequence that consists of the first item in seq1,
	// then the first in seq2, then the second in seq1, then the second in seq2,
	// If seq1 is empty, then when this function returns, result must consist of the sequence seq2
	// If seq2 is empty, then when this function returns, result must consist of the sequence seq1
	// If seq1 and seq2 are empty, then when this function returns, result must be empty.
	
	// if seq1 is empty, seq2 will be the result
	if (seq1.empty())
		result = seq2;
	// if seq2 is empty, seq1 will be the result
	if (seq2.empty())
		result = seq1;

	
	
	// Make the copies of seq1 and seq2
	Sequence copy_s1(seq1);
	Sequence copy_s2(seq2);

	// Empty the result if it's not empty
	if (!result.empty())
	{
		for (int i = 0; i < result.size();)
		{
			result.erase(i);
		}
	}


	ItemType s1, s2;
	int pos = 0;
	if (copy_s1.size() < copy_s2.size())
	{
		// s1 size < s2 size
		for (int i = 0; i < copy_s2.size(); i++)
		{
			if (copy_s1.get(i, s1))// get function returns false when it exceeds the size
			{
				result.insert(pos, s1);
				pos++;
			}

			if (copy_s2.get(i, s2))
			{
				result.insert(pos, s2);
				pos++;
			}
		}
	}
	else
	{
		// si size >= s2 size
		for (int j = 0; j < copy_s1.size(); j++)
		{
			if (copy_s1.get(j, s1))
			{
				result.insert(pos, s1);
				pos++;
			}

			if (copy_s2.get(j, s2))
			{
				result.insert(pos, s2);
				pos++;
			}
		}
	}
	

}
