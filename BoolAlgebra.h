#pragma once

#include <vector>
#include <string>
#include <map>
#include "List.h"

typedef std::pair<std::string, bool> BoolVar;   // variable and inversion
typedef NodeList<NodeList<std::string>> PolinomShehalkina;

class Vars : public std::vector<std::string>
{
public:
    bool contains(std::string& var);
};

class Kortesh : public std::map<std::string, bool>
{
public:
    Kortesh(Vars vars);
};

class EK : public NodeList<BoolVar>
{
public:
    bool check(Kortesh* kort);
};

class ED : public NodeList<BoolVar>
{
public:
    bool check(Kortesh* kort);
};

class DNF : public NodeList<EK>
{
public:
    bool check(Kortesh* kort);
};

class KNF : public NodeList<ED>
{
public:
    bool check(Kortesh* kort);
};

template<typename NormalForm>
PolinomShehalkina genPolinom(NormalForm BooleanExpression);

#include "BoolAlgebra.ipp"