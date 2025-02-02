#pragma once

#include <set>
#include "SigTree.h"

namespace sig_ma {
//------------------

class FoundPacker {

public:
	FoundPacker(long offs, sig_ma::PckrSign* sig) : offset(offs), signaturePtr(sig) { }

	long offset;
	sig_ma::PckrSign* signaturePtr; // do not delete it - belongs to SignFinder

	bool operator== (const FoundPacker& f2) { return (this->offset == f2.offset && this->signaturePtr == f2.signaturePtr);}
};

enum match_direction {
	FIXED,
	FRONT_TO_BACK,
	BACK_TO_FRONT
};


class SigFinder
{
public:
	SigFinder(void) {}
	~SigFinder(void){}

	PckrSign* getFirstMatch(char *buf, long buf_size, long start_offset = 0, match_direction md = FIXED);

	matched getMatching(char *buf, long buf_size, long start_offset, match_direction md = FIXED);

	size_t loadSignatures(const std::string &fname);

	std::set<PckrSign*>& signatures() { return tree.all_signatures; };
	std::vector<PckrSign*>& signaturesVec() { return tree.signaturesVec; }

protected:
	SigTree tree;
};
//---
}; //namespace sig_ma
//------------------