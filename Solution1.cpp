#include <bits/stdc++.h>
using namespace std;

int get_next_position(long long current_hash, int start_position, const vector<long long>& hash_suffixes, int num_cards) {
    for (int i = start_position; i <= num_cards; i += 2)
        if (hash_suffixes[i] == current_hash)
            return i;
    return -1;
}

vector<bool> get_suffix(int start_index, int num_cards, int num_types, const vector<int>& card_deck) {
    vector<bool> suffix(num_types);
    for (int i = start_index; i < num_cards; i++) 
        suffix[card_deck[i]] = !suffix[card_deck[i]];
    return suffix;
}

int MaxCoins(int num_cards, int num_types, const vector<int>& card_deck) {
    mt19937_64 random_generator(12341234);
    vector<int> cards = card_deck;
    vector<int> max_coins(num_cards + 1);
    vector<vector<bool>> odd_parity(num_cards + 1, vector<bool>(num_types));
    vector<bool> full_odd_parity(num_types);
    vector<long long> values(num_types);
    vector<long long> hash_suffixes(num_cards + 1);
    
    long long current_hash = 0;
    int maximum_score = 0;

    for (int i = 0; i < num_types; i++)
        while (values[i] == 0)
            values[i] = random_generator();

    for (int i = 0; i < num_cards; i++) 
        cards[i]--;

    for (int i = 0; i < num_cards; i++) {
        current_hash ^= values[cards[i]];
        if (full_odd_parity[cards[i]]) 
            maximum_score++;
        full_odd_parity[cards[i]] = !full_odd_parity[cards[i]];
        odd_parity[i + 1] = full_odd_parity;
        hash_suffixes[i + 1] = current_hash;
    }

    for (int i = num_types; i <= num_cards; i++)
        max_coins[i] = 1e9;

    long long initial_hash = 0ll;
    for (int i = 0; i < num_types; i++) 
        initial_hash ^= values[i];

    int position = get_next_position(initial_hash, num_types, hash_suffixes, num_cards);
    if (position == -1) 
        return maximum_score;

    max_coins[position] = 0;
    int min_additional_moves = 1e9;

    for (int p = num_types; p <= num_cards; p += 2) {
        if (max_coins[p] > 1e8) continue;

        vector<bool> suffix = get_suffix(p, num_cards, num_types, cards);
        vector<int> odd_types, even_types;
        for (int j = 0; j < num_types; j++)
            if (suffix[j])
                even_types.push_back(j);
            else
                odd_types.push_back(j);

        int odd_size = odd_types.size();
        int even_size = even_types.size();
        bool proceed = true;

        for (int i = 0; i < odd_size && proceed; i++)
            for (int j = 0; j < i && proceed; j++) {
                int x = odd_types[i];
                int y = odd_types[j];
                int additional_moves = 0;
                long long hash = hash_suffixes[p] ^ values[x] ^ values[y];
                int pos = get_next_position(hash, p, hash_suffixes, num_cards);
                if (pos == -1) {
                    proceed = false;
                    min_additional_moves = min(min_additional_moves, max_coins[p] + additional_moves);
                } else {
                    max_coins[pos] = min(max_coins[pos], max_coins[p] + additional_moves);
                }
            }

        for (int i = 0; i < odd_size && proceed; i++)
            for (int j = 0; j < even_size && proceed; j++) {
                int x = odd_types[i];
                int y = even_types[j];
                int additional_moves = 1;
                long long hash = hash_suffixes[p] ^ values[x] ^ values[y];
                int pos = get_next_position(hash, p, hash_suffixes, num_cards);
                if (pos == -1) {
                    proceed = false;
                    min_additional_moves = min(min_additional_moves, max_coins[p] + additional_moves);
                } else {
                    max_coins[pos] = min(max_coins[pos], max_coins[p] + additional_moves);
                }
            }

        for (int i = 0; i < even_size && proceed; i++)
            for (int j = 0; j < i && proceed; j++) {
                int x = even_types[i];
                int y = even_types[j];
                int additional_moves = 2;
                long long hash = hash_suffixes[p] ^ values[x] ^ values[y];
                int pos = get_next_position(hash, p, hash_suffixes, num_cards);
                if (pos == -1) {
                    proceed = false;
                    min_additional_moves = min(min_additional_moves, max_coins[p] + additional_moves);
                } else {
                    max_coins[pos] = min(max_coins[pos], max_coins[p] + additional_moves);
                }
            }
    }
    return maximum_score - min_additional_moves;
}

int main() {
    // TEST
    vector<int> deck_1 = {1, 1, 2, 2, 3, 3};
    int n_1 = 6, k_1 = 6;
    assert(MaxCoins(n_1, k_1, deck_1) == 3);
    // TEST_END

    // TEST
    vector<int> deck_2 = {1, 1, 1, 2, 2, 2, 3, 3, 3};
    int n_2 = 9, k_2 = 6;
    assert(MaxCoins(n_2, k_2, deck_2) == 3);
    // TEST_END

    // TEST
    vector<int> deck_3 = {1, 2, 3, 4, 5, 6, 7, 8};
    int n_3 = 8, k_3 = 6;
    assert(MaxCoins(n_3, k_3, deck_3) == 0);
    // TEST_END

    // TEST
    vector<int> deck_4 = {1, 2, 1, 2, 3, 3, 4, 4};
    int n_4 = 8, k_4 = 6;
    assert(MaxCoins(n_4, k_4, deck_4) == 4);
    // TEST_END

    // TEST
    vector<int> deck_5 = {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8};
    int n_5 = 16, k_5 = 6;
    assert(MaxCoins(n_5, k_5, deck_5) == 6); 
    // TEST_END

    // TEST
    vector<int> deck_6 = {1, 1, 1, 1, 1, 1, 1, 1};
    int n_6 = 8, k_6 = 6;
    assert(MaxCoins(n_6, k_6, deck_6) == 4);
    // TEST_END
    return 0;
    
}

