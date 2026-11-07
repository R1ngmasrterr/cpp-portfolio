#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Header.h"

using namespace std;

vector<uint32_t> iz_hex_v_string(const string& hex) {
    vector<uint32_t> res;
    string s = hex;
    if (s.length() >= 2 && (s.substr(0, 2) == "0x" || s.substr(0, 2) == "0X")) s = s.substr(2);
    if (s.length() % 2 == 1) s = "0" + s;
    if (s.length() == 0) return { 0 };

    size_t i = s.length();
    while (i > 0) {
        size_t start = (i >= 8) ? i - 8 : 0;
        uint32_t sl = 0;
        for (size_t j = start; j < i; ++j) {
            char c = s[j];
            uint32_t val = 0;
            if (c >= '0' && c <= '9') val = c - '0';
            else if (c >= 'A' && c <= 'F') val = c - 'A' + 10;
            else if (c >= 'a' && c <= 'f') val = c - 'a' + 10;
            sl = (sl << 4) | val;
        }
        res.push_back(sl);
        if (i < 8) break;
        i -= 8;
    }
    while (res.size() > 1 && res.back() == 0) res.pop_back();
    return res;
}

vector<uint32_t> from_int64_t(int64_t n) {
    vector<uint32_t> res;
    if (n >= 0) {
        if (n == 0) {
            res.push_back(0);
            return res;
        }
        while (n > 0) {
            res.push_back(static_cast<uint32_t>(n & VSE_1));
            n >>= BITS;
        }
    } else {
        uint64_t mod_n = static_cast<uint64_t>(-n);
        vector<uint32_t> prom;
        while (mod_n > 0) {
            prom.push_back(static_cast<uint32_t>(mod_n & VSE_1));
            mod_n >>= BITS;
        }
        for (size_t i = 0; i < prom.size(); ++i) prom[i] = ~prom[i];
        uint64_t per = 1;
        for (size_t i = 0; i < prom.size() && per; ++i) {
            per += static_cast<uint64_t>(prom[i]);
            prom[i] = static_cast<uint32_t>(per);
            per >>= BITS;
        }
        return prom;
    }
    return res;
}

vector<uint32_t> rasshirenie(const vector<uint32_t>& a, size_t n) {
    if (a.size() >= n) return a;
    vector<uint32_t> prom(n, 0);
    for (size_t i = 0; i < a.size(); ++i) prom[i] = a[i];
    
    uint32_t znak = 0;
    if ((a.back() >> 31) != 0) znak = VSE_1;
    for (size_t i = a.size(); i < n; ++i) prom[i] = znak;
    return prom;
}

vector<uint32_t> slojenie(const vector<uint32_t>& a, const vector<uint32_t>& b) {
    size_t n = max(a.size(), b.size());
    vector<uint32_t> a_ext = rasshirenie(a, n + 2);
    vector<uint32_t> b_ext = rasshirenie(b, n + 2);
    vector<uint32_t> res;
    
    uint64_t per = 0;
    for (size_t i = 0; i < n + 2; ++i) {
        per += static_cast<uint64_t>(a_ext[i]) + static_cast<uint64_t>(b_ext[i]);
        res.push_back(static_cast<uint32_t>(per));
        per >>= BITS;
    }
    while (res.size() > 1) {
        uint32_t posl_sl = res.back();
        uint32_t predposl_sl = res[res.size() - 2];
        int znak_pred = (predposl_sl >> 31) & 1;
        if ((posl_sl == 0 && znak_pred == 0) || (posl_sl == VSE_1 && znak_pred == 1)) res.pop_back();
        else break;
    }
    return res;
}

vector<uint32_t> inversiya(const vector<uint32_t>& a) {
    if (a.size() == 1 && a[0] == 0) return { 0 };
    vector<uint32_t> res(a.size());
    for (size_t i = 0; i < a.size(); ++i) res[i] = ~a[i];
    
    uint64_t per = 1;
    for (size_t i = 0; i < res.size() && per; ++i) {
        per += static_cast<uint64_t>(res[i]);
        res[i] = static_cast<uint32_t>(per);
        per >>= BITS;
    }
    if (per) res.push_back(static_cast<uint32_t>(per));
    
    while (res.size() > 1) {
        uint32_t posl_s = res.back();
        uint32_t predposl_s = res[res.size() - 2];
        int znak = predposl_s >> 31;
        if ((posl_s == VSE_1 && znak == 1) || (posl_s == 0 && znak == 0)) res.pop_back();
        else break;
    }
    return res;
}

vector<uint32_t> sdvig_vlevo(const vector<uint32_t>& a, unsigned sdvig) {
    if (sdvig == 0) return a;
    size_t dop_sl = sdvig / BITS;
    unsigned dop_bit = sdvig % BITS;
    vector<uint32_t> res(a.size() + dop_sl + 1, 0);
    
    if (dop_bit == 0) {
        for (size_t i = 0; i < a.size(); ++i) res[i + dop_sl] = a[i];
    } else {
        uint32_t per = 0;
        for (size_t i = 0; i < a.size(); ++i) {
            res[i + dop_sl] = (a[i] << dop_bit) | per;
            per = a[i] >> (BITS - dop_bit);
        }
        res[a.size() + dop_sl] = per;
    }
    while (res.size() > 1 && res.back() == 0) res.pop_back();
    return res;
}

vector<uint32_t> sdvig_vpravo_log(const vector<uint32_t>& a, unsigned sdvig) {
    if (sdvig == 0) return a;
    size_t dop_sl = sdvig / BITS;
    unsigned dop_bit = sdvig % BITS;
    if (dop_sl >= a.size()) return { 0 };
    
    size_t new_razm = a.size() - dop_sl;
    vector<uint32_t> res(new_razm, 0);
    if (dop_bit == 0) {
        for (size_t i = 0; i < new_razm; ++i) res[i] = a[i + dop_sl];
    } else {
        uint32_t per = 0;
        for (size_t i = new_razm; i-- > 0;) {
            uint32_t w = a[i + dop_sl];
            res[i] = (w >> dop_bit) | (per << (BITS - dop_bit));
            per = w & ((1U << dop_bit) - 1);
        }
    }
    while (res.size() > 1 && res.back() == 0) res.pop_back();
    return res;
}

vector<uint32_t> sdvig_vparavo_arif_bez_normalize(const vector<uint32_t>& a, unsigned sdvig) {
    if (sdvig == 0) return a;
    size_t dop_sl = sdvig / BITS;
    unsigned dop_bit = sdvig % BITS;
    uint32_t znak = a.back() >> 31;
    
    if (dop_sl >= a.size()) {
        if (znak == 0) return { 0 };
        else return { VSE_1 };
    }
    size_t new_razm = a.size() - dop_sl;
    vector<uint32_t> res(new_razm, 0);
    
    if (dop_bit == 0) {
        for (size_t i = 0; i < new_razm; ++i) res[i] = a[i + dop_sl];
    } else {
        uint32_t per = znak;
        for (size_t i = new_razm; i-- > 0;) {
            uint32_t w = a[i + dop_sl];
            res[i] = (w >> dop_bit) | (per << (BITS - dop_bit));
            per = w & ((1U << dop_bit) - 1);
        }
    }
    return res;
}

vector<uint32_t> sdvig_vparavo_arif(const vector<uint32_t>& a, unsigned sdvig) {
    vector<uint32_t> res = sdvig_vparavo_arif_bez_normalize(a, sdvig);
    while (res.size() > 1) {
        uint32_t posl_s = res.back();
        uint32_t predposl_s = res[res.size() - 2];
        int znak = predposl_s >> 31;
        if ((posl_s == VSE_1 && znak == 1) || (posl_s == 0 && znak == 0)) res.pop_back();
        else break;
    }
    return res;
}

void dobav(vector<uint32_t>& P, const vector<uint32_t>& X, size_t k) {
    uint64_t per = 0;
    for (size_t i = 0; i < k; ++i) {
        per += static_cast<uint64_t>(P[k + i]) + static_cast<uint64_t>(X[i]);
        P[k + i] = static_cast<uint32_t>(per);
        per >>= BITS;
    }
    size_t ind = 2 * k;
    while (per && ind < P.size()) {
        per += P[ind];
        P[ind] = static_cast<uint32_t>(per);
        per >>= BITS;
        ind++;
    }
    if (per) P.push_back(static_cast<uint32_t>(per));
}

vector<uint32_t> algorithm_Buta(const vector<uint32_t>& a, const vector<uint32_t>& b) {
    size_t k = max(a.size(), b.size());
    vector<uint32_t> M = rasshirenie(a, k);
    vector<uint32_t> Q = rasshirenie(b, k);
    vector<uint32_t> S = rasshirenie(inversiya(M), k);
    vector<uint32_t> P(2 * k, 0);
    
    for (size_t i = 0; i < k; ++i) P[i] = Q[i];
    
    uint32_t q_posl = 0;
    for (size_t i = 0; i < k * BITS; ++i) {
        uint32_t q0 = P[0] & 1;
        uint32_t per = (q_posl << 1) | q0;
        
        if (per == 1) {
            dobav(P, S, k);
        } else if (per == 2) {
            dobav(P, M, k);
        }
        q_posl = q0;
        P = sdvig_vparavo_arif_bez_normalize(P, 1);
    }
    
    vector<uint32_t> res(P.begin(), P.begin() + 2 * k);
    while (res.size() > 1) {
        uint32_t posl_s = res.back();
        uint32_t predposl_s = res[res.size() - 2];
        int znak = predposl_s >> 31;
        if ((posl_s == VSE_1 && znak == 1) || (posl_s == 0 && znak == 0)) res.pop_back();
        else break;
    }
    return res;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Демонстрация алгоритма Бута для многократной точности." << endl;
    
    // Пример: умножение двух чисел (в шестнадцатеричном формате)
    string hex_a = "0x100000000"; // 4294967296
    string hex_b = "0x2";         // 2
    
    vector<uint32_t> a = iz_hex_v_string(hex_a);
    vector<uint32_t> b = iz_hex_v_string(hex_b);
    
    vector<uint32_t> result = algorithm_Buta(a, b);
    
    cout << "Операнд A: " << hex_a << endl;
    cout << "Операнд B: " << hex_b << endl;
    cout << "Результат (в hex): 0x";
    for (size_t i = result.size(); i-- > 0;) {
        cout << hex << result[i];
    }
    cout << endl;
    
    return 0;
}
