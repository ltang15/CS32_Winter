#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include "globals.h"

class History
{
public:
	// Constructor
	History(int nRows, int nCols);

	// Accessors
	bool record(int r, int c);
	void display() const;

private:
	int m_rows;
	int m_cols;
	int count[MAXROWS][MAXCOLS];

};

#endif