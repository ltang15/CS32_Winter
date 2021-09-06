#include "ScoreList.h"

ScoreList::ScoreList()      // Create an empty score list.
{}

bool ScoreList::add(unsigned long score)
// If the score is valid (a value from 0 to 100) and the score list
// has room for it, add it to the score list and return true.
// Otherwise, leave the score list unchanged and return false.
{
	if (score > 100 || m_score.size() >= DEFAULT_MAX_ITEMS)
		return false;

	m_score.insert(score);
	return true;
}

bool ScoreList::remove(unsigned long score)
// Remove one instance of the specified score from the score list.
// Return true if a score was removed; otherwise false.
{
	if (m_score.find(score) == -1)
		return false;

	int pos;
	pos = m_score.find(score);
	m_score.erase(pos);
	return true;
}

int ScoreList::size() const  // Return the number of scores in the list.
{
	return m_score.size();
}

unsigned long ScoreList::minimum() const
// Return the lowest-valued score in the score list.  If the list is
// empty, return NO_SCORE.
{
	if (m_score.empty())
		return NO_SCORE;

	unsigned long lowest;
	m_score.get (0, lowest); // set the first element is minimum
	for (int i = 0; i < m_score.size(); i++)
	{
		unsigned long val;
		m_score.get(i, val);
		if (val < lowest)
			lowest = val;
	}

	return lowest;
}
unsigned long ScoreList::maximum() const
// Return the highest-valued score in the score list.  If the list is
// empty, return NO_SCORE.
{
	if (m_score.empty())
		return NO_SCORE;

	unsigned long highest;

	int size = m_score.size();
	m_score.get(size - 1, highest);// set the last element is maximum
	for (int i = size - 1; i >= 0; i--)
	{
		unsigned long val;
		m_score.get(i, val);
		if (val > highest)
			highest = val;
	}

	return highest;
}