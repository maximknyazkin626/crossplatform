#pragma once
class Knyazkin_player : public CObject
{
public:
    DECLARE_SERIAL(Knyazkin_player);
    Knyazkin_player();
    ~Knyazkin_player();
    virtual void ReadPlayers();
    virtual void PrintPlayers();
    string FirstName;
    string LastName;
    int Age = 0;
    string Country;
    virtual void Serialize(CArchive& ar);
    friend CArchive& operator >> (CArchive& ar, string& s);
    friend CArchive& operator << (CArchive& ar, string& s);
};
