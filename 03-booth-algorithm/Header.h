#pragma once
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const unsigned BITS = 32;
const uint32_t VSE_1 = 0xFFFFFFFF;

vector<uint32_t> iz_hex_v_string(const string& hex);
vector<uint32_t> from_int64_t(int64_t n);
vector<uint32_t> rasshirenie(const vector<uint32_t>& a, size_t n);
vector<uint32_t> slojenie(const vector<uint32_t>& a, const vector<uint32_t>& b);
vector<uint32_t> inversiya(const vector<uint32_t>& a);
vector<uint32_t> sdvig_vlevo(const vector<uint32_t>& a, unsigned sdvig);
vector<uint32_t> sdvig_vpravo_log(const vector<uint32_t>& a, unsigned sdvig);
vector<uint32_t> sdvig_vparavo_arif(const vector<uint32_t>& a, unsigned sdvig);
vector<uint32_t> sdvig_vparavo_arif_bez_normalize(const vector<uint32_t>& a, unsigned sdvig);
void dobav(vector<uint32_t>& P, const vector<uint32_t>& X, size_t k);
vector<uint32_t> algorithm_Buta(const vector<uint32_t>& a, const vector<uint32_t>& b);
