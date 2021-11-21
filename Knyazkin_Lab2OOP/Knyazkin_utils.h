#pragma once
#include "pch.h"
CArchive& operator << (CArchive& ar, string& s);
CArchive& operator >> (CArchive& ar, string& s);