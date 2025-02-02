/*
 * Copyright (c) 2013 hasherezade
*/

#pragma once
#include <map>

#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>

#include "SigNode.h"
#include "PckrSign.h"

namespace sig_ma {
//------------------

struct matched {
	std::set<PckrSign*> signs;
	long match_offset;
};
//------------------

class SigTree
{
public:
	SigTree() : root(0, ROOT),  min_siglen(0), max_siglen(0) {}
	~SigTree() { clear(); }

	bool addPckrSign(PckrSign *sign);
	size_t loadFromFile(std::ifstream& input);

	matched getMatching(char *buf, size_t buf_len, bool skipNOPs);

	long getMinLen() { return min_siglen; }
	long getMaxLen() { return max_siglen; }

protected:
	void insertPckrSign(PckrSign* sign);

	//---
	std::map<SigNode*, PckrSign*> nodeToSign;
	std::set<PckrSign*> all_signatures;
	std::vector<PckrSign*> signaturesVec;
	SigNode root;
	
	long min_siglen;
	long max_siglen;

private:
	void clear(); //destroys all the signatures!

friend class SigFinder;
};
//-----------------------
}; // namespace sig_ma
