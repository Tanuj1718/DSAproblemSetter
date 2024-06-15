#include <bits/stdc++.h>
using namespace std;

long long computeFactorial(int number) {
    const long long modulo = 1000000007;
    const int max_factorials = 1000000;
    long long factorialArray[max_factorials];

    factorialArray[0] = 1;
    for (int index = 1; index < number; index++) {
        factorialArray[index] = (index * factorialArray[index - 1]) % modulo;
    }
    return factorialArray[number];
}

long long CountPermutations(vector<int> arr, int moduloValue) {
    const long long modulo = 1000000007;
    const int max_factorials = 1000000;
    long long factorialArray[max_factorials];

    computeFactorial(1000000);
        
        int oddCount = 0;
        int evenCount = 0;
        int arrayLength = arr.size();
        for (int index = 0; index < arrayLength; index++) {
            int element = arr[index];
            if (element % 2 == 0)
                evenCount += 1;
            else
                oddCount += 1;
        }

        int oddPairs = (arrayLength + 1) / 2;
        int remaining = arrayLength - oddPairs;
        long long result = 0;

        if (moduloValue == 1) {
            if (oddPairs == oddCount)
                result = (factorialArray[oddCount] * factorialArray[evenCount]) % modulo;
            if (oddPairs == evenCount)
                result = (result + (factorialArray[evenCount] * factorialArray[oddCount]) % modulo) % modulo;
        } else {
            if (evenCount > 0 && oddCount > 0)
                result = 0;
            else
                result = factorialArray[arrayLength];
        }

        return result;
}

int main() {
    // TEST
    vector<int> array_1 = {1, 2, 3, 4};
    int k_1 = 1;
    assert(CountPermutations(array_1, k_1) == 8);
    // TEST_END

    // TEST
    vector<int> array_2 = {2, 4, 6, 8};
    int k_2 = 0;
    assert(CountPermutations(array_2, k_2) == 24); 
    // TEST_END

    // TEST
    vector<int> array_3 = {1, 3, 5, 7};
    int k_3 = 0;
    assert(CountPermutations(array_3, k_3) == 24);
    // TEST_END

    // TEST
    vector<int> array_4 = {1, 2};
    int k_4 = 1;
    assert(CountPermutations(array_4, k_4) == 2);
    // TEST_END

    // TEST
    vector<int> array_5 = {2, 3, 4, 5};
    int k_5 = 1;
    assert(CountPermutations(array_5, k_5) == 8);
    // TEST_END

    // TEST
    vector<int> array_6 = {1, 2, 3};
    int k_6 = 1;
    assert(CountPermutations(array_6, k_6) == 2);
    // TEST_END

    return 0;
}

