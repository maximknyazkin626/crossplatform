#include "Knyazkin_utils.h"
#include "pch.h"
#include "Knyazkin_player.h"
#include "Knyazkin_coach.h"
#include <sstream>
CArchive& operator << (CArchive& ar, string& s)
{
	ar << CString(s.c_str());
	return ar;
}

CArchive& operator >> (CArchive& ar, string& s)
{
	CString tmp;
	ar >> tmp;
	s = tmp;
	return ar;
}