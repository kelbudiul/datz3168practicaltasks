#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>

using namespace std;

class ReviewerSystem {
private:
    unordered_map<string, set<int>> reviewerPseudonyms; // Map reviewer names to sets of pseudonyms
    unordered_map<int, string> pseudonymToReviewer; // Map pseudonyms to reviewer names

public:
    void insertReviewer(const string& name, int count, const vector<int>& pseudonyms) {
        if (reviewerPseudonyms.find(name) == reviewerPseudonyms.end()) {
            set<int> uniquePseudonyms(pseudonyms.begin(), pseudonyms.end());
            for (int pseudonym : uniquePseudonyms) {
                if (pseudonymToReviewer.find(pseudonym) != pseudonymToReviewer.end()) {
                    cout << "no" << endl;
                    return;
                }
            }
            /*For a new reviewer (not in the system), we create a set uniquePseudonyms containing 
            the pseudonyms provided in the input. This set automatically ensures uniqueness, 
            as it only keeps unique values.

            We then iterate through each pseudonym in uniquePseudonyms and check if it already 
            exists in the pseudonymToReviewer map. If any pseudonym is already in use by another reviewer, 
            we output "no" and exit the function.

            If all pseudonyms are unique, we proceed to add the reviewer to the system. 
            We insert the reviewer's name and pseudonyms into the respective data structures, 
            and output "ok".

            If the reviewer is already in the system, we check each new pseudonym to ensure it 
            is unique across all reviewers. If any pseudonym is already in use by another reviewer, 
            we output "no" and exit the function.

            If all new pseudonyms are unique, we insert the new pseudonyms into the existing reviewer's 
            set of pseudonyms, update the relevant mappings, and output "ok".*/

            reviewerPseudonyms[name] = uniquePseudonyms;
            for (int pseudonym : uniquePseudonyms) {
                pseudonymToReviewer[pseudonym] = name;
            }
            cout << "ok" << endl;
        } else {
            for (int pseudonym : pseudonyms) {
                if (pseudonymToReviewer.find(pseudonym) != pseudonymToReviewer.end()) {
                    cout << "no" << endl;
                    return;
                }
            }

            reviewerPseudonyms[name].insert(pseudonyms.begin(), pseudonyms.end());
            for (int pseudonym : pseudonyms) {
                pseudonymToReviewer[pseudonym] = name;
            }
            cout << "ok" << endl;
        }
    }

    void discardReviewer(int key) {
        if (pseudonymToReviewer.find(key) == pseudonymToReviewer.end()) {
            cout << "no" << endl;
        } else {
            string name = pseudonymToReviewer[key];
            reviewerPseudonyms[name].erase(key);
            pseudonymToReviewer.erase(key);
            cout << "ok" << endl;
        }
    }

    void lookupReviewer(int key) {
        if (pseudonymToReviewer.find(key) == pseudonymToReviewer.end()) {
            cout << "no" << endl;
        } else {
            string name = pseudonymToReviewer[key];
            cout << name << endl;
        }
    }
};

int main() {
    freopen("reviewers.in", "r", stdin);
    freopen("reviewers.out", "w", stdout);

    ReviewerSystem reviewerSystem;

    char operation;
    while (cin >> operation) {
        if (operation == 'I') {
            string name;
            int count;
            cin >> name >> count;
            vector<int> pseudonyms(count);
            for (int i = 0; i < count; ++i) {
                cin >> pseudonyms[i];
            }
            reviewerSystem.insertReviewer(name, count, pseudonyms);
        } else if (operation == 'D') {
            int key;
            cin >> key;
            reviewerSystem.discardReviewer(key);
        } else if (operation == 'L') {
            int key;
            cin >> key;
            reviewerSystem.lookupReviewer(key);
        }
    }

    fclose(stdin);
    fclose(stdout);

    return 0;
}
