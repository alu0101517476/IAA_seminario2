#ifndef SMILE_DIAGCASELIBRARY_H
#define SMILE_DIAGCASELIBRARY_H

// {{SMILE_PUBLIC_HEADER}}

class DSL_diagSession;

#include <vector>
#include <string>

struct DSL_diagCase
{
	typedef std::pair<std::string,std::string> Item;  // (nodeId,outcomeId)

	DSL_diagCase() : entropyCostRatio(-1), maxEntropyCostRatio(-1) {}

	std::string title;
	std::string comment;
	std::string modelName;
	std::vector<Item> pursuedFaults;
	std::vector<Item> evidence;
	double entropyCostRatio;
	double maxEntropyCostRatio;
};

//-----------------------------------

class DSL_diagCaseLibrary
{
public:
	DSL_diagCaseLibrary(DSL_diagSession *session);

	int ReadFile(const char* filename);
	int WriteFile(const char* filename) const;

	const std::vector<DSL_diagCase>& GetCases() const { return cases; }

	const DSL_diagCase& GetCase(int caseIndex) const { return cases[caseIndex]; }
	DSL_diagCase& GetCase(int caseIndex) { return cases[caseIndex]; }
	int FindCase(const char* caseTitle) const;
	int AddCase(const DSL_diagCase& newCase);
	int DeleteCase(int caseIndex);

	void InstantiateCase(const DSL_diagCase& thisOne);
	void SaveCurrentCase(DSL_diagCase& here);
	int ConsistentCase(const DSL_diagCase& thisOne, bool ignoreModelName) const;

	bool EvidenceValid(const std::string& evNode, const std::string& evState, std::pair<int, int>& handles) const;
	bool EvidenceValid(const DSL_diagCase::Item& item, std::pair<int, int>& handles) const { return EvidenceValid(item.first, item.second, handles); }
	bool FaultValid(const std::string& faultNode, const std::string& faultState, std::pair<int, int>& handles) const;
	bool FaultValid(const DSL_diagCase::Item& item, std::pair<int, int>& handles) const { return FaultValid(item.first, item.second, handles); }

	static void GetContinuousFaultIds(std::string& low, std::string& high);

#ifndef SMILE_NO_V1_COMPATIBILITY
	// BACKWARD COMPATIBILITY ONLY
	int ReadCaseLibrary(const char* filename) { return ReadFile(filename); }
	int WriteCaseLibrary(const char* filename) const { return WriteFile(filename); }
#endif

private:
	void FillCaseWithEvidence(DSL_diagCase& here);
	void FillCaseWithPursuedFaults(DSL_diagCase& here);

	std::vector<DSL_diagCase> cases;
	DSL_diagSession *session;
};


#endif
