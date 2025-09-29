// my_vector_stress200.cpp
#include "my_vector.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>

std::vector<std::string> failed_tests;

void push_fail(const std::string &s) {
    failed_tests.push_back(s);
    std::cout << "[FAIL REPORT] " << s << std::endl;
}

void check_bool(bool cond, const std::string &msg) {
    if (cond) {
        std::cout << "[PASS] " << msg << std::endl;
    } else {
        std::cout << "[FAIL] " << msg << std::endl;
        push_fail(msg);
    }
}

std::string vec_to_str(const std::vector<int> &v) {
    std::ostringstream oss;
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) oss << ' ';
        oss << v[i];
    }
    return oss.str();
}

std::string myvec_to_str(const MyVector &v) {
    std::ostringstream oss;
    for (size_t i = 0; i < v.size; ++i) {
        if (i) oss << ' ';
        oss << v.data[i];
    }
    return oss.str();
}

bool compare_ref_with_myvec(const std::vector<int> &ref, const MyVector &v, std::string &msg_out) {
    if (ref.size() != v.size) {
        std::ostringstream oss;
        oss << "SIZE_MISMATCH expected=" << ref.size() << " actual=" << v.size;
        msg_out = oss.str();
        return false;
    }
    for (size_t i = 0; i < ref.size(); ++i) {
        if (ref[i] != v.data[i]) {
            std::ostringstream oss;
            oss << "CONTENT_MISMATCH at idx=" << i
                << " expected=" << ref[i]
                << " actual=" << v.data[i];
            msg_out = oss.str();
            return false;
        }
    }
    // invariant: size <= capacity
    if (v.size > v.capacity) {
        std::ostringstream oss;
        oss << "INVARIANT_FAIL size(" << v.size << ") > capacity(" << v.capacity << ")";
        msg_out = oss.str();
        return false;
    }
    // if size > 0 then data should not be null (basic check)
    if (v.size > 0 && v.data == 0) {
        msg_out = "NULL_DATA_PTR while size>0";
        return false;
    }
    return true;
}

int main() {
    std::srand(12345); // deterministic
    const int LEVELS = 200;
    const int OPS_PER_LEVEL = 500; // each level ~500 random ops

    std::cout << "Starting HARD stress test: levels=" << LEVELS << " ops_per_level=" << OPS_PER_LEVEL << std::endl;

    for (int level = 1; level <= LEVELS; ++level) {
        MyVector v;
        // start with small capacity to force reallocs
        myvector_init(&v, 4 + (std::rand() % 8));
        std::vector<int> ref;
        bool level_failed = false;

        for (int op = 0; op < OPS_PER_LEVEL; ++op) {
            int code = std::rand() % 100;
            if (code < 50) {
                // push_back
                int val = std::rand();
                myvector_push_back(&v, val);
                ref.push_back(val);
            } else if (code < 65) {
                // pop_back
                if (ref.size() > 0) {
                    myvector_pop_back(&v);
                    ref.pop_back();
                } else {
                    // attempt pop on empty - still call to check robustness (may be UB in implementation)
                    // we avoid calling pop on truly empty vector to prevent undefined behavior if implementation doesn't guard
                    // (previous implementation simply decremented size; we skip to be safer)
                }
            } else if (code < 80) {
                // insert
                size_t idx = 0;
                if (ref.size() == 0) idx = 0;
                else idx = std::rand() % (ref.size() + 1);
                int val = std::rand();
                myvector_insert(&v, idx, val);
                // If implementation refuses insert into empty vector, insertion won't happen -> we still update ref only if v.size changed.
                // To detect that, we compare sizes afterwards.
                // But to keep ref consistent with intended behavior, attempt to simulate expected insertion:
                if (idx <= ref.size()) {
                    ref.insert(ref.begin() + idx, val);
                }
            } else if (code < 95) {
                // erase
                if (ref.size() > 0) {
                    size_t idx = std::rand() % ref.size();
                    myvector_erase(&v, idx);
                    ref.erase(ref.begin() + idx);
                } else {
                    // erase on empty - skip
                }
            } else if (code < 98) {
                // clear
                myvector_clear(&v);
                ref.clear();
            } else {
                // reinit/destroy cycle
                myvector_destroy(&v);
                // after destroy we expect data==nullptr,size==0,capacity==0 (if implementation follows corrected destroy)
                // but some implementations may not set data to nullptr; we'll check later
                myvector_init(&v, 1 + (std::rand() % 16));
                ref.clear();
            }

            // compare ref and myvector
            std::string err;
            bool ok = compare_ref_with_myvec(ref, v, err);
            if (!ok) {
                std::ostringstream oss;
                oss << "Level=" << level << " op=" << op << " ERR=" << err
                    << " | ref: [" << vec_to_str(ref) << "]"
                    << " | myvec: [" << myvec_to_str(v) << "]";
                push_fail(oss.str());
                level_failed = true;
                // do not break — continue to collect more info in the same level
            }
        } // end ops loop

        // final destroy check for this level
        myvector_destroy(&v);
        if (v.data != 0 || v.size != 0 || v.capacity != 0) {
            std::ostringstream oss;
            oss << "Level=" << level << " final destroy didn't clear struct: data=" << (void*)v.data
                << " size=" << v.size << " cap=" << v.capacity;
            push_fail(oss.str());
            level_failed = true;
        }

        if (!level_failed) {
            std::ostringstream oss;
            oss << "Level " << level << " finished OK";
            std::cout << "[LEVEL PASS] " << oss.str() << std::endl;
        } else {
            std::ostringstream oss;
            oss << "Level " << level << " had failures";
            std::cout << "[LEVEL FAIL] " << oss.str() << std::endl;
        }
    } // end levels

    // Summary
    std::cout << "\n=== HARD TEST REPORT ===" << std::endl;
    if (failed_tests.empty()) {
        std::cout << "✅ ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО (уровень 200) ✅" << std::endl;
    } else {
        std::cout << "❌ НАЙДЕНО " << failed_tests.size() << " ошибок. ПЕРВЫЕ 20 ОТЧЕТОВ:" << std::endl;
        for (size_t i = 0; i < failed_tests.size() && i < 20; ++i) {
            std::cout << " - " << failed_tests[i] << std::endl;
        }
    }

    return 0;
}
