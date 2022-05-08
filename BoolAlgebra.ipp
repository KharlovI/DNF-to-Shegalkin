#pragma once
#include "BoolAlgebra.h"

bool Vars::contains(std::string& var)
{
    for (int i = 0; i < this->size(); i++)
    {
        if (this->at(i).find(var) != std::string::npos)
            return true;
    }
    return false;
}

Kortesh::Kortesh(Vars vars)
{
    for (auto i : vars)
    {
        std::pair<std::string, bool> var;
        var.first = i; var.second = false;
        this->insert(var);
    }
}

bool EK::check(Kortesh* kort)
{
    Node* varIter = this->head;
    while (varIter != nullptr)
    {
        if (kort->at(varIter->data->first) && !(varIter->data->second) ||
            !kort->at(varIter->data->first) && (varIter->data->second))
            varIter = varIter->next;
        else
            return false;
    }
    return true;
}

bool ED::check(Kortesh* kort)
{
    Node* varIter = this->head;
    while (varIter != nullptr)
    {
        if (kort->at(varIter->data->first) && !(varIter->data->second) ||
            !kort->at(varIter->data->first) && (varIter->data->second))
            return true;
        else
            varIter = varIter->next;
    }
    return false;
}

bool DNF::check(Kortesh* kort)
{
    Node* curEk = this->head;
    while (curEk != nullptr)
    {
        if (curEk->data->check(kort))
            return true;
        curEk = curEk->next;
    }
    return false;
}

bool KNF::check(Kortesh* kort)
{
    Node* curEd = this->head;
    while (curEd != nullptr)
    {
        if (!curEd->data->check(kort))
            return false;
        curEd = curEd->next;
    }
    return true;
}

template<typename NormalForm>
Vars getDifferentVars(NormalForm BooleanExpression)
{
    Vars vars;
    for (u_int64 i = 0; i < BooleanExpression.size(); i++)
        for (u_int64 j = 0; j < BooleanExpression[i].size(); j++)
            if (!vars.contains(BooleanExpression[i][j].first))
                vars.push_back(BooleanExpression[i][j].first);
    return vars;
}

void genKortesh(u_int64 base, Kortesh* kortesh)
{
    for (auto it = kortesh->rbegin(); it != kortesh->rend(); it++)
    {
        it->second = base % 2;
        base /= 2;
    }
}

template<typename NormalForm>
std::vector<bool> genResultTable(NormalForm BooleanExpression)
{
    Vars vars = getDifferentVars(BooleanExpression);

    u_int64 resultVecSize = pow(2, vars.size());
    std::vector<bool> resultVec;

    Kortesh* kort = new Kortesh(vars);
    for (u_int64 i = 0; i < resultVecSize; i++)
    {
        genKortesh(i, kort);
        bool isTrue = BooleanExpression.check(kort);
        resultVec.push_back(isTrue);
    }
    delete kort;
    return resultVec;
}

template<typename NormalForm>
inline PolinomShehalkina genPolinom(NormalForm BooleanExpression)
{
    std::vector<bool> results = genResultTable(BooleanExpression);
    
    for (u_int64 divider = 2; divider <= results.size(); divider *= 2)
    {
        u_int64 step = divider / 2;
        u_int64 cur = step;
        while (cur < results.size())
        {
            while (cur % divider != 0)
            {
                results.at(cur) = (results.at(cur) + results.at(cur - step)) % 2;
                cur++;
            }
            cur += step;
        }
    }
    PolinomShehalkina polinom;

    if (results[0])
    {
        std::string* one = new std::string("1");
        NodeList<std::string>* listOne = new NodeList<std::string>;
        listOne->append(one);
        polinom.append(listOne);
    }

    Vars difVars = getDifferentVars(BooleanExpression);
    Kortesh kort(difVars);
    for (int i = 1; i < results.size(); i++)
    {
        if (results[i])
        {
            NodeList<std::string>* dodanok = new NodeList<std::string>;
            genKortesh(i, &kort);
            for (auto j : kort)
            {
                if (j.second)
                {
                    std::string* str = new std::string(j.first);
                    dodanok->append(str);
                }
            }
            polinom.append(dodanok);
        }
    }
    return polinom;
}